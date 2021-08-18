#include "DpcppComputePmeKernel.h"
#include "DpcppUtils.h"

void NAMD_die(const char *);

#ifdef NAMD_DPCPP

#define SUB_GROUP_SIZE 32 // To ensure same sub-group (warp) size as CUDA

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

void dpcpp_init_bspline_coeffs(float **c, float **dc, int order, sycl::queue &queue) {
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
      double c = scoeffs[i*order+(order-1-j)]; // reverse order
      sum += c;
      c /= divisor;
      coeffs[i*order+j] = c;
      dcoeffs[i*order+j] = (double)p * c;
    }
  }
  if ( sum != divisor )
    NAMD_die("dpcpp_init_bspline_coeffs static data checksum error");
  *c = sycl::malloc_device<float>(order * order, queue);
  *dc = sycl::malloc_device<float>(order * order, queue);
  queue.memcpy(*c, coeffs, order * order * sizeof(float)).wait();
  queue.memcpy(*dc, dcoeffs, order * order * sizeof(float)).wait();
  delete [] coeffs;
  delete [] dcoeffs;
}

// Data structures used in local memory
template <int order>
union bspline_coeffs_t {
  float a2d[order][order];
  float a1d[order*order];
};

union atoms_t {
  float a2d[atoms_per_warp][7];
  float a1d[atoms_per_warp*7];
};

union force_output_t {
  float a2d[atoms_per_warp][3];
  float a1d[atoms_per_warp*3];
};

union force_reduction_t {
  float a2d[32][3];
  float a1d[32*3];
};

// Shared memory allocations have been moved outside the kernels
#define BSPLINE_DEFS \
  if (item_ct1.get_local_id(2) < order * order) { \
    bspline_coeffs->a1d[item_ct1.get_local_id(2)] = \
        coeffs[item_ct1.get_local_id(2)]; \
  } \
  item_ct1.barrier();

// simplify warp-synchronous operations
#define WARP (item_ct1.get_local_id(2) >> 5)
#define THREAD (item_ct1.get_local_id(2) & 31)
#define FX bspline_factors[item_ct1.get_local_id(2) >> 5][0]
#define FY bspline_factors[item_ct1.get_local_id(2) >> 5][1]
#define FZ bspline_factors[item_ct1.get_local_id(2) >> 5][2]

#define FX2 bspline_2factors[item_ct1.get_local_id(2) >> 5][0]
#define FY2 bspline_2factors[item_ct1.get_local_id(2) >> 5][1]
#define FZ2 bspline_2factors[item_ct1.get_local_id(2) >> 5][2]

#define ATOM atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom]
#define AQ atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][3]
#define AI atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][4]
#define AJ atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][5]
#define AK atoms[item_ct1.get_local_id(2) >> 5].a2d[i_atom][6]


template <int order>
void dpcpp_pme_charges_dev(
    const float *__restrict__ coeffs, float *const *__restrict__ q_arr,
    int *__restrict__ f_arr, int *__restrict__ fz_arr,
    float *__restrict__ a_data, int n_atoms, int K1, int K2, int K3,
    sycl::nd_item<3> item_ct1, bspline_coeffs_t<order> *bspline_coeffs,
    volatile atoms_t *atoms, dpct::accessor<volatile float, dpct::local, 3> bspline_factors) {
  auto sg = item_ct1.get_sub_group();
  BSPLINE_DEFS
  int atoms_this_warp = atoms_per_warp;
  {
    int aidx = item_ct1.get_group(2) * atoms_per_block + WARP * atoms_per_warp;
    if ( aidx + atoms_per_warp > n_atoms ) {
      atoms_this_warp = n_atoms - aidx; // may be negative
      if ( atoms_this_warp < 0 ) atoms_this_warp = 0;
    }
    if ( THREAD < atoms_this_warp*7 ) {
      atoms[WARP].a1d[THREAD] = a_data[aidx*7+THREAD];
    }
  }
  for ( int i_atom=0; i_atom < atoms_this_warp; ++i_atom ) {
    sg.barrier(); // done writing atoms, reading bspline_factors (FX,FY,FZ)
    float aq=AQ;
    int ai=(int)AI;
    int aj=(int)AJ;
    int ak=(int)AK;
    if ( THREAD < 3 * order ) {
      const float af = ATOM[THREAD/order];  // x, y, or z
      float f = bspline_coeffs->a2d[0][THREAD % order];
      for ( int i=1; i<order; ++i ) {
        f = af * f + bspline_coeffs->a2d[i][THREAD % order];
      }
      bspline_factors[WARP][THREAD/order][THREAD % order] = f;
    }
    sg.barrier(); // done writing bspline_factors
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
      if (dest) ATOMIC_ADD(float, *(dest + gtk), val);
    }
  } // i_atom
}

template <int order>
void dpcpp_pme_forces_dev(
    const float *__restrict__ coeffs, float *const *__restrict__ q_arr,
    float *const *__restrict__ afn_g, int K1, int K2, int K3,
    sycl::nd_item<3> item_ct1, float **afn_s,
    bspline_coeffs_t<order> *bspline_coeffs, volatile atoms_t *atoms,
    volatile force_output_t *force_output,
    dpct::accessor<sycl::float2, dpct::local, 3> bspline_2factors,
    volatile force_reduction_t *force_reduction) {
  auto sg = item_ct1.get_sub_group();
  if (item_ct1.get_local_id(2) < 3) {
    afn_s[item_ct1.get_local_id(2)] =
      afn_g[3 * item_ct1.get_group(1) + item_ct1.get_local_id(2)];
  }
  BSPLINE_DEFS
  int atoms_this_warp = atoms_per_warp;
  {
    const int n_atoms = afn_s[2] - afn_s[1];
    int aidx = item_ct1.get_group(2) * atoms_per_block + WARP * atoms_per_warp;
    if ( aidx + atoms_per_warp > n_atoms ) {
      atoms_this_warp = n_atoms - aidx; // may be negative
      if ( atoms_this_warp < 0 ) atoms_this_warp = 0;
    }
    if ( THREAD < atoms_this_warp*7 ) {
      atoms[WARP].a1d[THREAD] = afn_s[0][aidx*7+THREAD];
    }
    sg.barrier(); // done writing atoms
  }
  for ( int i_atom=0; i_atom < atoms_this_warp; ++i_atom ) {
    float aq=AQ;
    int ai=(int)AI;
    int aj=(int)AJ;
    int ak=(int)AK;
    if ( THREAD < 3 * order ) {
      const float af = ATOM[THREAD/order]; // x, y, or z
      float df = 0.f;
      float c = bspline_coeffs->a2d[0][THREAD % order];
      float f = c;
      for ( int i=1; i<order; ++i ) {
        df = af * df - (order-i) * c;
        c = bspline_coeffs->a2d[i][THREAD % order];
        f = af * f + c;
      }
      bspline_2factors[WARP][THREAD / order][THREAD % order] =
          sycl::float2(f, df);
    }
    item_ct1.mem_fence(); // bspline_2factors not declared volatile
    sg.barrier(); // done writing bspline_2factors (FX2,FY2,FZ2)
    float force_x = 0.f;
    float force_y = 0.f;
    float force_z = 0.f;

    for ( int i=THREAD; i < order*order*order; i+=32 ) {
      int ti = i/(order*order);
      int tj = (i/order)%order;
      int tk = i%order;

      const sycl::float2 fx2 = FX2[ti];
      const sycl::float2 fy2 = FY2[tj];
      const sycl::float2 fz2 = FZ2[tk];

      const float fx = fx2.x();
      const float fy = fy2.x();
      const float fz = fz2.x();
      const float dfx = fx2.y();
      const float dfy = fy2.y();
      const float dfz = fz2.y();

      float dx = K1 * aq * dfx * fy * fz;
      float dy = K2 * aq * fx * dfy * fz;
      float dz = K3 * aq * fx * fy * dfz;

      int gti = ti + ai;  if ( gti >= K1 ) gti -= K1;
      int gtj = tj + aj;  if ( gtj >= K2 ) gtj -= K2;
      int gtk = ak;  if ( gtk >= K3 ) gtk -= K3;

      gtk += tk; // padded to increase coalescing (maybe, but reduces re-use)
      const float * __restrict__ src = q_arr[gti * K2 + gtj]; // could load as constant
      float pot = src ? src[gtk]
                      : sycl::detail::bit_cast<float>(0x7fffffff); // CUDA NaN
      force_x += dx * pot;
      force_y += dy * pot;
      force_z += dz * pot;
    }
    force_reduction[WARP].a2d[THREAD][0] = force_x;
    force_reduction[WARP].a2d[THREAD][1] = force_y;
    force_reduction[WARP].a2d[THREAD][2] = force_z;
    sg.barrier(); // done writing force_reduction
    if ( THREAD < 24 ) {
      force_reduction[WARP].a1d[THREAD] += force_reduction[WARP].a1d[THREAD + 24]
                                         + force_reduction[WARP].a1d[THREAD + 48]
                                         + force_reduction[WARP].a1d[THREAD + 72];
    }
    sg.barrier(); // done writing force_reduction
    if ( THREAD < 6 ) {
      force_reduction[WARP].a1d[THREAD] += force_reduction[WARP].a1d[THREAD + 6]
                                         + force_reduction[WARP].a1d[THREAD + 12]
                                         + force_reduction[WARP].a1d[THREAD + 18];
    }
    sg.barrier(); // done writing force_reduction
    if ( THREAD < 3 ) {
      force_output[WARP].a2d[i_atom][THREAD] = force_reduction[WARP].a1d[THREAD]
                                             + force_reduction[WARP].a1d[THREAD + 3];
    }
  } // i_atom
  sg.barrier(); // done writing force_output
  if ( THREAD < atoms_this_warp*3 ) {
    int aidx = item_ct1.get_group(2) * atoms_per_block + WARP * atoms_per_warp;
    afn_s[1][aidx*3+THREAD] = force_output[WARP].a1d[THREAD];
  }
}

// Templated kernel name
template <int order>
class dpcpp_pme_charges_dev_name;

DPCPP_PME_CHARGES_PROTOTYPE {
  int nblocks = (n_atoms + atoms_per_block - 1) / atoms_per_block;
  if ( ! nblocks ) return;

  queue.submit([&](sycl::handler &cgh) {
      // Local memory allocations
      sycl::accessor<bspline_coeffs_t<order>, 0, sycl::access::mode::read_write,
      sycl::access::target::local> bspline_coeffs_acc(cgh);

      sycl::range<1> atoms_range(atoms_per_block);
      sycl::accessor<volatile atoms_t, 1, sycl::access::mode::read_write,
      sycl::access::target::local> atoms_acc(atoms_range, cgh);

      sycl::range<3> bspline_factors_range(warps_per_block, 3, order);
      sycl::accessor<volatile float, 3, sycl::access::mode::read_write,
      sycl::access::target::local> bspline_factors_acc(bspline_factors_range, cgh);

      // Kernel invocation
      cgh.parallel_for<dpcpp_pme_charges_dev_name<order>>(
          sycl::nd_range<3>(sycl::range<3>(1, 1, nblocks) *
            sycl::range<3>(1, 1, 32 * warps_per_block),
            sycl::range<3>(1, 1, 32 * warps_per_block)),
          [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
          dpcpp_pme_charges_dev<order>(coeffs, q_arr, f_arr, fz_arr, a_data,
              n_atoms, K1, K2, K3, item_ct1, bspline_coeffs_acc.get_pointer(),
              atoms_acc.get_pointer(),
              dpct::accessor<volatile float, dpct::local, 3>(bspline_factors_acc,
                                                             bspline_factors_range));
      });
  });
}

// Template instantiations
template void dpcpp_pme_charges<4>(const float *coeffs, float *const *q_arr, int *f_arr,
                                   int *fz_arr, float *a_data, int n_atoms, int K1, int K2,
                                   int K3, sycl::queue& queue);
template void dpcpp_pme_charges<6>(const float *coeffs, float *const *q_arr, int *f_arr,
                                   int *fz_arr, float *a_data, int n_atoms, int K1, int K2,
                                   int K3, sycl::queue& queue);
template void dpcpp_pme_charges<8>(const float *coeffs, float *const *q_arr, int *f_arr,
                                   int *fz_arr, float *a_data, int n_atoms, int K1, int K2,
                                   int K3, sycl::queue& queue);

// Templated kernel name
template <int order>
class dpcpp_pme_forces_dev_name;

DPCPP_PME_FORCES_PROTOTYPE {
  int nblocks = (maxn + atoms_per_block - 1) / atoms_per_block;
  if ( (! nblocks) || (! dimy) ) return;

  queue.submit([&](sycl::handler &cgh) {
      // Local memory allocations
      sycl::accessor<bspline_coeffs_t<order>, 0, sycl::access::mode::read_write,
      sycl::access::target::local> bspline_coeffs_acc(cgh);

      sycl::range<1> atoms_range(atoms_per_block);
      sycl::accessor<volatile atoms_t, 1, sycl::access::mode::read_write,
      sycl::access::target::local> atoms_acc(atoms_range, cgh);

      sycl::accessor<float*, 1, sycl::access::mode::read_write,
      sycl::access::target::local> afn_s_acc(sycl::range<1>(3), cgh);

      sycl::range<1> force_output_range(warps_per_block);
      sycl::accessor<volatile force_output_t, 1, sycl::access::mode::read_write,
      sycl::access::target::local> force_output_acc(force_output_range, cgh);

      sycl::range<3> bspline_2factors_range(warps_per_block, 3, order);
      sycl::accessor<sycl::float2, 3, sycl::access::mode::read_write,
      sycl::access::target::local> bspline_2factors_acc(
          bspline_2factors_range, cgh);

      sycl::range<1> force_reduction_range(warps_per_block);
      sycl::accessor<volatile force_reduction_t, 1, sycl::access::mode::read_write,
      sycl::access::target::local> force_reduction_acc(force_reduction_range, cgh);

      // Kernel invocation
      cgh.parallel_for<dpcpp_pme_forces_dev_name<order>>(
          sycl::nd_range<3>(sycl::range<3>(1, dimy, nblocks) *
            sycl::range<3>(1, 1, 32 * warps_per_block),
            sycl::range<3>(1, 1, 32 * warps_per_block)),
          [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
          dpcpp_pme_forces_dev<order>(coeffs, q_arr, afn, K1, K2, K3, item_ct1,
              afn_s_acc.get_pointer(), bspline_coeffs_acc.get_pointer(),
              atoms_acc.get_pointer(), force_output_acc.get_pointer(),
              dpct::accessor<sycl::float2, dpct::local, 3>(
                bspline_2factors_acc, bspline_2factors_range),
              force_reduction_acc.get_pointer());
      });
  });
}

// Template instantiations
template void dpcpp_pme_forces<4>(const float *coeffs, float *const *q_arr,
    float *const *afn, int dimy, int maxn, int K1, int K2, int K3,
    sycl::queue& queue);
template void dpcpp_pme_forces<6>(const float *coeffs, float *const *q_arr,
    float *const *afn, int dimy, int maxn, int K1, int K2, int K3,
    sycl::queue& queue);
template void dpcpp_pme_forces<8>(const float *coeffs, float *const *q_arr,
    float *const *afn, int dimy, int maxn, int K1, int K2, int K3,
    sycl::queue& queue);

#endif // NAMD_DPCPP
