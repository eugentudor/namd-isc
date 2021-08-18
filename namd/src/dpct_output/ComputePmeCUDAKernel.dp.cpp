#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>
#include "ComputePmeCUDAKernel.h"
#include "CudaUtils.h"

void NAMD_die(const char *);

#ifdef NAMD_CUDA

/* DPCT_ORIG #include <cuda.h>*/

/* DPCT_ORIG #if defined(__CUDA_ARCH__) && __CUDA_ARCH__ < 200*/
#if defined(DPCT_COMPATIBILITY_TEMP) && DPCT_COMPATIBILITY_TEMP < 200
// allow linking, must prevent execution elsewhere
__device__ void atomicAdd(float *, float) { }
#endif

// must run with at least order**2 threads
#define warps_per_block 8
#define atoms_per_warp 4
#define atoms_per_block (atoms_per_warp * warps_per_block)


static const float order_4_coeffs[4][4] =
{{1, -3, 3, -1}, {0, 3, -6, 3}, {0, 3, 0, -3}, {0, 1, 4, 1}};
// divide by 3! = 6

static const float order_6_coeffs[6][6] =
{{1, -5, 10, -10, 5, -1}, {0, 5, -20, 30, -20, 5}, {0, 10, -20, 0,
  20, -10}, {0, 10, 20, -60, 20, 10}, {0, 5, 50, 0, -50, -5}, {0, 1,
  26, 66, 26, 1}};
// divide by 5! = 120

static const float order_8_coeffs[8][8] =
{{1, -7, 21, -35, 35, -21, 7, -1}, {0, 7, -42, 105, -140, 105, -42,
  7}, {0, 21, -84, 105, 0, -105, 84, -21}, {0, 35, 0, -315, 560, -315,
   0, 35}, {0, 35, 280, -665, 0, 665, -280, -35}, {0, 21, 504,
  315, -1680, 315, 504, 21}, {0, 7, 392, 1715,
  0, -1715, -392, -7}, {0, 1, 120, 1191, 2416, 1191, 120, 1}};
// divide by 7! = 5040

void cuda_init_bspline_coeffs(float **c, float **dc, int order) {
  dpct::device_ext &dev_ct1 = dpct::get_current_device();
  sycl::queue &q_ct1 = dev_ct1.default_queue();
  float *coeffs = new float[order*order];
  float *dcoeffs = new float[order*order];
  double divisor;
  static const float *scoeffs;
  switch ( order ) {
  case 4:
    scoeffs = &order_4_coeffs[0][0];
    divisor = 6;
    break;
  case 6:
    scoeffs = &order_6_coeffs[0][0];
    divisor = 120;
    break;
  case 8:
    scoeffs = &order_8_coeffs[0][0];
    divisor = 5040;
    break;
  default:
    NAMD_die("unsupported PMEInterpOrder");
  }
  double sum = 0;
  for ( int i=0, p=order-1; i<order; ++i,--p ) {
    for ( int j=0; j<order; ++j ) {
      double c = scoeffs[i*order+(order-1-j)];  // reverse order
      sum += c;
      c /= divisor;
      coeffs[i*order+j] = c;
      dcoeffs[i*order+j] = (double)p * c;
    }
  }
  if ( sum != divisor )
    NAMD_die("cuda_init_bspline_coeffs static data checksum error");
/* DPCT_ORIG   cudaMalloc((void**) c, order*order*sizeof(float));*/
  *c = sycl::malloc_device<float>(order * order, q_ct1);
/* DPCT_ORIG   cudaMalloc((void**) dc, order*order*sizeof(float));*/
  *dc = sycl::malloc_device<float>(order * order, q_ct1);
/* DPCT_ORIG   cudaMemcpy(*c, coeffs, order*order*sizeof(float),
 * cudaMemcpyHostToDevice);*/
  q_ct1.memcpy(*c, coeffs, order * order * sizeof(float)).wait();
/* DPCT_ORIG   cudaMemcpy(*dc, dcoeffs, order*order*sizeof(float),
 * cudaMemcpyHostToDevice);*/
  q_ct1.memcpy(*dc, dcoeffs, order * order * sizeof(float)).wait();
  delete [] coeffs;
  delete [] dcoeffs;
}

#define BSPLINE_DEFS                                                           \
/* DPCT_ORIG   __shared__ union { \*/                                          \
  union {                                                                      \
    float a2d[order][order];                                                   \
    float a1d[order * order];                                                  \
  } bspline_coeffs;                                                            \
/* DPCT_ORIG   __shared__ volatile union { \*/                                 \
  volatile union {                                                             \
    float a2d[atoms_per_warp][7];                                              \
    float a1d[atoms_per_warp * 7];                                             \
  } atoms[warps_per_block];                                                    \
/* DPCT_ORIG   if ( threadIdx.x < order*order ) { \*/                          \
  if (item_ct1.get_local_id(2) < order * order) {                              \
/* DPCT_ORIG     bspline_coeffs.a1d[threadIdx.x] = coeffs[threadIdx.x]; \*/    \
    bspline_coeffs->a1d[item_ct1.get_local_id(2)] =                            \
        coeffs[item_ct1.get_local_id(2)];                                      \
  }                                                                            \
  BLOCK_SYNC;

// simplify warp-synchronous operations
/* DPCT_ORIG #define WARP (threadIdx.x>>5)*/
#define WARP (item_ct1.get_local_id(2) >> 5)
/* DPCT_ORIG #define THREAD (threadIdx.x&31)*/
#define THREAD (item_ct1.get_local_id(2) & 31)
/* DPCT_ORIG #define FX bspline_factors[threadIdx.x>>5][0]*/
#define FX bspline_factors[item_ct1.get_local_id(2) >> 5][0]
/* DPCT_ORIG #define FY bspline_factors[threadIdx.x>>5][1]*/
#define FY bspline_factors[item_ct1.get_local_id(2) >> 5][1]
/* DPCT_ORIG #define FZ bspline_factors[threadIdx.x>>5][2]*/
#define FZ bspline_factors[item_ct1.get_local_id(2) >> 5][2]

/* DPCT_ORIG #define FX2 bspline_2factors[threadIdx.x>>5][0]*/
#define FX2 bspline_2factors[item_ct1.get_local_id(2) >> 5][0]
/* DPCT_ORIG #define FY2 bspline_2factors[threadIdx.x>>5][1]*/
#define FY2 bspline_2factors[item_ct1.get_local_id(2) >> 5][1]
/* DPCT_ORIG #define FZ2 bspline_2factors[threadIdx.x>>5][2]*/
#define FZ2 bspline_2factors[item_ct1.get_local_id(2) >> 5][2]

/* DPCT_ORIG #define ATOM atoms[threadIdx.x>>5].a2d[i_atom]*/
#define ATOM atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom]
/* DPCT_ORIG #define AQ atoms[threadIdx.x>>5].a2d[i_atom][3]*/
#define AQ atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][3]
/* DPCT_ORIG #define AI atoms[threadIdx.x>>5].a2d[i_atom][4]*/
#define AI atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][4]
/* DPCT_ORIG #define AJ atoms[threadIdx.x>>5].a2d[i_atom][5]*/
#define AJ atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][5]
/* DPCT_ORIG #define AK atoms[threadIdx.x>>5].a2d[i_atom][6]*/
#define AK atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][6]

template <int order>
/* DPCT_ORIG __global__ void cuda_pme_charges_dev(*/
void cuda_pme_charges_dev(
    const float *__restrict__ coeffs, float *const *__restrict__ q_arr,
    int *__restrict__ f_arr, int *__restrict__ fz_arr,
    float *__restrict__ a_data, int n_atoms, int K1, int K2, int K3,
    sycl::nd_item<3> item_ct1, uint8_t *bspline_coeffs_ct1,
    dpct::accessor<volatile float, dpct::local, 3> bspline_factors)
{
/* DPCT_ORIG   BSPLINE_DEFS
  __shared__ volatile float bspline_factors[warps_per_block][3][order];*/
   type_ct1 int atoms_this_warp = atoms_per_warp;
  {
/* DPCT_ORIG     int aidx = blockIdx.x * atoms_per_block + WARP *
 * atoms_per_warp;*/
    int aidx = item_ct1.get_group(2) * atoms_per_block + WARP * atoms_per_warp;
    if ( aidx + atoms_per_warp > n_atoms ) {
      atoms_this_warp = n_atoms - aidx;  // may be negative
      if ( atoms_this_warp < 0 ) atoms_this_warp = 0;
    }
    if ( THREAD < atoms_this_warp*7 ) {
      atoms[WARP].a1d[THREAD] = a_data[aidx*7+THREAD];
    }
  }
  for ( int i_atom=0; i_atom < atoms_this_warp; ++i_atom ) {
    WARP_SYNC(WARP_FULL_MASK);  // done writing atoms, reading bspline_factors (FX,FY,FZ)
    float aq=AQ;
    int ai=(int)AI;
    int aj=(int)AJ;
    int ak=(int)AK;
    if ( THREAD < 3 * order ) {
      const float af = ATOM[THREAD/order];  // x, y, or z
/* DPCT_ORIG       float f = bspline_coeffs.a2d[0][THREAD % order];*/
      float f = bspline_coeffs->a2d[0][THREAD % order];
      for ( int i=1; i<order; ++i ) {
/* DPCT_ORIG         f = af * f + bspline_coeffs.a2d[i][THREAD % order];*/
        f = af * f + bspline_coeffs->a2d[i][THREAD % order];
      }
      bspline_factors[WARP][THREAD/order][THREAD % order] = f;
    }
    WARP_SYNC(WARP_FULL_MASK);  // done writing bspline_factors
    for ( int i=THREAD; i < order*order; i+=32 ) {
      int ti = i/order;
      int tj = i%order;
      int gti = ti + ai;  if ( gti >= K1 ) gti -= K1;
      int gtj = tj + aj;  if ( gtj >= K2 ) gtj -= K2;
      f_arr[gti * K2 + gtj] = 1;
    }
    if ( THREAD < order ) {
      int gtk = ak;  if ( gtk >= K3 ) gtk -= K3;
      gtk += THREAD;  // padded to increase coalescing (maybe, but reduces re-use)
      fz_arr[gtk] = 1;
    }
    for ( int i=THREAD; i < order*order*order; i+=32 ) {
      int ti = i/(order*order);
      int tj = (i/order)%order;
      int tk = i%order;
      float val = aq * FX[ti] * FY[tj] * FZ[tk];
      int gti = ti + ai;  if ( gti >= K1 ) gti -= K1;
      int gtj = tj + aj;  if ( gtj >= K2 ) gtj -= K2;
      int gtk = ak;  if ( gtk >= K3 ) gtk -= K3;
      gtk += tk;  // padded to increase coalescing (maybe, but reduces re-use)
      float *dest = q_arr[gti * K2 + gtj];  // could load as constant
/* DPCT_ORIG        if ( dest ) atomicAdd(dest+gtk,val);*/
       if (dest) dpct::atomic_fetch_add(dest + gtk, val);
    }
  } // i_atom
}

template <int order>
/* DPCT_ORIG __global__ void cuda_pme_forces_dev(*/
void cuda_pme_forces_dev(
    const float *__restrict__ coeffs, float *const *__restrict__ q_arr,
    float *const *__restrict__ afn_g, int K1, int K2, int K3,
    sycl::nd_item<3> item_ct1, float **afn_s, uint8_t *bspline_coeffs_ct1,
    volatile union *force_output,
    dpct::accessor<sycl::float2, dpct::local, 3> bspline_2factors,
    volatile union *force_reduction)
{
/* DPCT_ORIG   __shared__ float *afn_s[3];*/

/* DPCT_ORIG   if ( threadIdx.x < 3 ) afn_s[threadIdx.x] =
 * afn_g[3*blockIdx.y+threadIdx.x];*/
  if (item_ct1.get_local_id(2) < 3) afn_s[item_ct1.get_local_id(2)] =
      afn_g[3 * item_ct1.get_group(1) + item_ct1.get_local_id(2)];
/* DPCT_ORIG   BSPLINE_DEFS
  __shared__ volatile union {
    float a2d[atoms_per_warp][3];
    float a1d[atoms_per_warp*3];
  } force_output[warps_per_block];*/
  BSPLINE_DEFS

/* DPCT_ORIG   __shared__ float2 bspline_2factors[warps_per_block][3][order];*/

/* DPCT_ORIG   __shared__ volatile union {
    float a2d[32][3];
    float a1d[32*3];
  } force_reduction[warps_per_block];*/

  int atoms_this_warp = atoms_per_warp;
  {
    const int n_atoms = afn_s[2] - afn_s[1];
/* DPCT_ORIG     int aidx = blockIdx.x * atoms_per_block + WARP *
 * atoms_per_warp;*/
    int aidx = item_ct1.get_group(2) * atoms_per_block + WARP * atoms_per_warp;
    if ( aidx + atoms_per_warp > n_atoms ) {
      atoms_this_warp = n_atoms - aidx;  // may be negative
      if ( atoms_this_warp < 0 ) atoms_this_warp = 0;
    }
    if ( THREAD < atoms_this_warp*7 ) {
      atoms[WARP].a1d[THREAD] = afn_s[0][aidx*7+THREAD];
    }
    WARP_SYNC(WARP_FULL_MASK);  // done writing atoms
  }
  for ( int i_atom=0; i_atom < atoms_this_warp; ++i_atom ) {
    float aq=AQ;
    int ai=(int)AI;
    int aj=(int)AJ;
    int ak=(int)AK;
    if ( THREAD < 3 * order ) {
      const float af = ATOM[THREAD/order];  // x, y, or z
      float df = 0.f;
/* DPCT_ORIG       float c = bspline_coeffs.a2d[0][THREAD % order];*/
      float c = bspline_coeffs->a2d[0][THREAD % order];
      float f = c;
      for ( int i=1; i<order; ++i ) {
        df = af * df - (order-i) * c;
/* DPCT_ORIG         c = bspline_coeffs.a2d[i][THREAD % order];*/
        c = bspline_coeffs->a2d[i][THREAD % order];
        f = af * f + c;
      }
/* DPCT_ORIG       bspline_2factors[WARP][THREAD/order][THREAD % order] =
 * make_float2(f,df);*/
      bspline_2factors[WARP][THREAD / order][THREAD % order] =
          sycl::float2(f, df);
    }
/* DPCT_ORIG     __threadfence_block();  */
    item_ct1.mem_fence();       // bspline_2factors not declared volatile
    WARP_SYNC(WARP_FULL_MASK);  // done writing bspline_2factors (FX2,FY2,FZ2)
    float force_x = 0.f;
    float force_y = 0.f;
    float force_z = 0.f;

    for ( int i=THREAD; i < order*order*order; i+=32 ) {
      int ti = i/(order*order);
      int tj = (i/order)%order;
      int tk = i%order;

/* DPCT_ORIG       const float2 fx2 = FX2[ti];*/
      const sycl::float2 fx2 = FX2[ti];
/* DPCT_ORIG       const float2 fy2 = FY2[tj];*/
      const sycl::float2 fy2 = FY2[tj];
/* DPCT_ORIG       const float2 fz2 = FZ2[tk];*/
      const sycl::float2 fz2 = FZ2[tk];

/* DPCT_ORIG       const float fx = fx2.x;*/
      const float fx = fx2.x();
/* DPCT_ORIG       const float fy = fy2.x;*/
      const float fy = fy2.x();
/* DPCT_ORIG       const float fz = fz2.x;*/
      const float fz = fz2.x();
/* DPCT_ORIG       const float dfx = fx2.y;*/
      const float dfx = fx2.y();
/* DPCT_ORIG       const float dfy = fy2.y;*/
      const float dfy = fy2.y();
/* DPCT_ORIG       const float dfz = fz2.y;*/
      const float dfz = fz2.y();

      float dx = K1 * aq * dfx * fy * fz;
      float dy = K2 * aq * fx * dfy * fz;
      float dz = K3 * aq * fx * fy * dfz;

      int gti = ti + ai;  if ( gti >= K1 ) gti -= K1;
      int gtj = tj + aj;  if ( gtj >= K2 ) gtj -= K2;
      int gtk = ak;  if ( gtk >= K3 ) gtk -= K3;

      gtk += tk;  // padded to increase coalescing (maybe, but reduces re-use)
      const float * __restrict__ src = q_arr[gti * K2 + gtj];  // could load as constant
/* DPCT_ORIG       float pot = src ? src[gtk] : __int_as_float(0x7fffffff);  */
      float pot = src ? src[gtk]
                      : sycl::detail::bit_cast<float>(0x7fffffff); // CUDA NaN
      force_x += dx * pot;
      force_y += dy * pot;
      force_z += dz * pot;
    }
    force_reduction[WARP].a2d[THREAD][0] = force_x;
    force_reduction[WARP].a2d[THREAD][1] = force_y;
    force_reduction[WARP].a2d[THREAD][2] = force_z;
    WARP_SYNC(WARP_FULL_MASK);  // done writing force_reduction
    if ( THREAD < 24 ) {
      force_reduction[WARP].a1d[THREAD] += force_reduction[WARP].a1d[THREAD + 24]
                                         + force_reduction[WARP].a1d[THREAD + 48]
                                         + force_reduction[WARP].a1d[THREAD + 72];
    }
    WARP_SYNC(WARP_FULL_MASK);  // done writing force_reduction
    if ( THREAD < 6 ) {
      force_reduction[WARP].a1d[THREAD] += force_reduction[WARP].a1d[THREAD + 6]
                                         + force_reduction[WARP].a1d[THREAD + 12]
                                         + force_reduction[WARP].a1d[THREAD + 18];
    }
    WARP_SYNC(WARP_FULL_MASK);  // done writing force_reduction
    if ( THREAD < 3 ) {
      force_output[WARP].a2d[i_atom][THREAD] = force_reduction[WARP].a1d[THREAD]
                                             + force_reduction[WARP].a1d[THREAD + 3];
    }
  } // i_atom
  WARP_SYNC(WARP_FULL_MASK);  // done writing force_output
  if ( THREAD < atoms_this_warp*3 ) {
/* DPCT_ORIG     int aidx = blockIdx.x * atoms_per_block + WARP *
 * atoms_per_warp;*/
    int aidx = item_ct1.get_group(2) * atoms_per_block + WARP * atoms_per_warp;
    afn_s[1][aidx*3+THREAD] = force_output[WARP].a1d[THREAD];
  }
}

CUDA_PME_CHARGES_PROTOTYPE {
  int nblocks = (n_atoms + atoms_per_block - 1) / atoms_per_block;
  if ( ! nblocks ) return;

#define CALL(ORDER)                                                            \
 if (order == ORDER)                                                           \
  /* DPCT_ORIG                                                                 \
     cuda_pme_charges_dev<ORDER><<<nblocks,32*warps_per_block,0,stream>>>(     \
                          coeffs, q_arr, f_arr, fz_arr, a_data, n_atoms, K1,   \
     K2, K3)*/                                                                         \
  stream->submit([&](sycl::handler &cgh) {                                     \
   sycl::range<3> bspline_factors_range_ct1(8 /*warps_per_block*/, 3, ORDER);  \
                                                                               \
   /*                                                                          \
   DPCT1054:4: The type of variable bspline_coeffs is declared in device       \
   function with the name type_ct1. Adjust the code to make the type_ct1       \
   declaration visible at the accessor declaration point.                      \
   */                                                                          \
   sycl::accessor<uint8_t[sizeof(type_ct1)], 0,                                \
                  sycl::access::mode::read_write, sycl::access::target::local> \
       bspline_coeffs_ct1_acc_ct1(cgh);                                        \
   sycl::accessor<float, 3, sycl::access::mode::read_write,                    \
                  sycl::access::target::local>                                 \
       bspline_factors_acc_ct1(bspline_factors_range_ct1, cgh);                \
                                                                               \
   auto coeffs_ct0 = coeffs;                                                   \
   auto q_arr_ct1 = q_arr;                                                     \
   auto f_arr_ct2 = f_arr;                                                     \
   auto fz_arr_ct3 = fz_arr;                                                   \
   auto a_data_ct4 = a_data;                                                   \
   auto n_atoms_ct5 = n_atoms;                                                 \
   auto K1_ct6 = K1;                                                           \
   auto K2_ct7 = K2;                                                           \
   auto K3_ct8 = K3;                                                           \
                                                                               \
   cgh.parallel_for(                                                           \
       sycl::nd_range<3>(sycl::range<3>(1, 1, nblocks) *                       \
                             sycl::range<3>(1, 1, 32 * warps_per_block),       \
                         sycl::range<3>(1, 1, 32 * warps_per_block)),          \
       [=](sycl::nd_item<3> item_ct1) {                                        \
        cuda_pme_charges_dev<ORDER>(                                           \
            coeffs_ct0, q_arr_ct1, f_arr_ct2, fz_arr_ct3, a_data_ct4,          \
            n_atoms_ct5, K1_ct6, K2_ct7, K3_ct8, item_ct1,                     \
            bspline_coeffs_ct1_acc_ct1.get_pointer(),                          \
            dpct::accessor<float, dpct::local, 3>(bspline_factors_acc_ct1,     \
                                                  bspline_factors_range_ct1)); \
       });                                                                     \
  });
  CALL(4);
  else CALL(6);
  else CALL(8);
  else NAMD_die("unsupported PMEInterpOrder");
#undef CALL
}

#ifdef CUDA_VERSION
#if CUDA_VERSION < 4020
void dummy() { }
#define cudaFuncSetSharedMemConfig(X,Y) dummy()
#endif
#endif


CUDA_PME_FORCES_PROTOTYPE {
  int nblocks = (maxn + atoms_per_block - 1) / atoms_per_block;
  if ( (! nblocks) || (! dimy) ) return;

/*
DPCT1027:2: The call to cudaFuncSetSharedMemConfig was replaced with 0, because
DPC++ currently does not support configuring shared memory on devices.
*/
#define CALL(ORDER)                                                                         \
 if (order == ORDER)                                                                        \
  /* DPCT_ORIG                                                                              \
   * cudaFuncSetSharedMemConfig(cuda_pme_forces_dev<ORDER>,cudaSharedMemBankSizeEightByte), \
   * \*/                                                                                    \
  0, /* DPCT_ORIG                                                                           \
        cuda_pme_forces_dev<ORDER><<<dim3(nblocks,dimy),32*warps_per_block,0,stream>>>(     \
                             coeffs, q_arr, afn, K1, K2,                                    \
        K3)*/                                                                               \
      stream->submit([&](sycl::handler &cgh) {                                              \
       sycl::range<3> bspline_2factors_range_ct1(8 /*warps_per_block*/, 3,                  \
                                                 ORDER);                                    \
                                                                                            \
       sycl::accessor<float *, 1, sycl::access::mode::read_write,                           \
                      sycl::access::target::local>                                          \
           afn_s_acc_ct1(sycl::range<1>(3), cgh);                                           \
       /*                                                                                   \
       DPCT1054:5: The type of variable bspline_coeffs is declared in device                \
       function with the name type_ct2. Adjust the code to make the type_ct2                \
       declaration visible at the accessor declaration point.                               \
       */                                                                                   \
       sycl::accessor<uint8_t[sizeof(type_ct2)], 0,                                         \
                      sycl::access::mode::read_write,                                       \
                      sycl::access::target::local>                                          \
           bspline_coeffs_ct1_acc_ct1(cgh);                                                 \
       sycl::accessor<union, 1, sycl::access::mode::read_write,                             \
                      sycl::access::target::local>                                          \
           force_output_acc_ct1(sycl::range<1>(8 /*warps_per_block*/), cgh);                \
       sycl::accessor<sycl::float2, 3, sycl::access::mode::read_write,                      \
                      sycl::access::target::local>                                          \
           bspline_2factors_acc_ct1(bspline_2factors_range_ct1, cgh);                       \
       sycl::accessor<union, 1, sycl::access::mode::read_write,                             \
                      sycl::access::target::local>                                          \
           force_reduction_acc_ct1(sycl::range<1>(8 /*warps_per_block*/),                   \
                                   cgh);                                                    \
                                                                                            \
       auto coeffs_ct0 = coeffs;                                                            \
       auto q_arr_ct1 = q_arr;                                                              \
       auto afn_ct2 = afn;                                                                  \
       auto K1_ct3 = K1;                                                                    \
       auto K2_ct4 = K2;                                                                    \
       auto K3_ct5 = K3;                                                                    \
                                                                                            \
       cgh.parallel_for(                                                                    \
           sycl::nd_range<3>(sycl::range<3>(1, dimy, nblocks) *                             \
                                 sycl::range<3>(1, 1, 32 * warps_per_block),                \
                             sycl::range<3>(1, 1, 32 * warps_per_block)),                   \
           [=](sycl::nd_item<3> item_ct1) {                                                 \
            cuda_pme_forces_dev<ORDER>(                                                     \
                coeffs_ct0, q_arr_ct1, afn_ct2, K1_ct3, K2_ct4, K3_ct5,                     \
                item_ct1, afn_s_acc_ct1.get_pointer(),                                      \
                bspline_coeffs_ct1_acc_ct1.get_pointer(),                                   \
                force_output_acc_ct1.get_pointer(),                                         \
                dpct::accessor<sycl::float2, dpct::local, 3>(                               \
                    bspline_2factors_acc_ct1, bspline_2factors_range_ct1),                  \
                force_reduction_acc_ct1.get_pointer());                                     \
           });                                                                              \
      });
  CALL(4);
  else CALL(6);
  else CALL(8);
  else NAMD_die("unsupported PMEInterpOrder");
#undef CALL
}

#endif // NAMD_CUDA
