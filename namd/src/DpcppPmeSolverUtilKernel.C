#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <stdio.h>
#include "DpcppUtils.h"
#include "DpcppPmeSolverUtilKernel.h"
#include <algorithm>

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>

#define SUB_GROUP_SIZE 32

// CCELEC is 1/ (4 pi eps ) in AKMA units, conversion from SI
// units: CCELEC = e*e*Na / (4*pi*eps*1Kcal*1A)
//
//      parameter :: CCELEC=332.0636D0 ! old value of dubious origin
//      parameter :: CCELEC=331.843D0  ! value from 1986-1987 CRC Handbook
//                                   ! of Chemistry and Physics
//  real(chm_real), parameter ::  &
//       CCELEC_amber    = 332.0522173D0, &
//       CCELEC_charmm   = 332.0716D0   , &
//       CCELEC_discover = 332.054D0    , &
//       CCELEC_namd     = 332.0636D0   
//const double ccelec = 332.0636;
//const double half_ccelec = 0.5*ccelec;
//const float ccelec_float = 332.0636f;

/*
// Structure into which virials are stored
// NOTE: This structure is only used for computing addresses
struct Virial_t {
  double sforce_dp[27][3];
  long long int sforce_fp[27][3];
  double virmat[9];
  // Energies start here ...
};
*/

// Local structure for scalar_sum -function for energy and virial reductions
struct RecipVirial_t {
  double energy;
  double virial[6];
};

__dpct_inline__ double expfunc(const double x) {
  return sycl::exp((double)x);
}

__dpct_inline__ float expfunc(const float x) {
  return sycl::exp((float)x);
}

//
// Performs scalar sum on data(nfft1, nfft2, nfft3)
// T = float or double
// T2 = float2 or double2
//
template <typename T, typename T2, bool calc_energy_virial, bool orderXYZ,
          bool doOrtho>
void scalar_sum_kernel(const int nfft1, const int nfft2, const int nfft3,
                       const int size1, const int size2, const int size3,
                       const T recip1x, const T recip1y, const T recip1z,
                       const T recip2x, const T recip2y, const T recip2z,
                       const T recip3x, const T recip3y, const T recip3z,
                       const T *prefac1, const T *prefac2, const T *prefac3,
                       const T pi_ewald, const T piv_inv, const int k2_00,
                       const int k3_00, T2 *data,
                       double *__restrict__ energy_recip,
                       double *__restrict__ virial, sycl::nd_item<3> item_ct1,
                       uint8_t *dpct_local) {
  // Shared memory required: sizeof(T)*(nfft1 + nfft2 + nfft3)
  auto sh_prefac = (T *)dpct_local;

  // Create pointers to shared memory
  T* sh_prefac1 = (T *)&sh_prefac[0];
  T* sh_prefac2 = (T *)&sh_prefac[nfft1];
  T* sh_prefac3 = (T *)&sh_prefac[nfft1 + nfft2];

  // Calculate start position (k1, k2, k3) for each thread
  unsigned int tid = item_ct1.get_group(2) * item_ct1.get_local_range().get(2) +
                     item_ct1.get_local_id(2);
  int k3 = tid/(size1*size2);
  tid -= k3*size1*size2;
  int k2 = tid/size1;
  int k1 = tid - k2*size1;

  // Starting position in data
  int pos = k1 + (k2 + k3*size2)*size1;

  // Move (k2, k3) to the global coordinate (k1_00 = 0 since this is the pencil direction)
  k2 += k2_00;
  k3 += k3_00;

  // Calculate limits w.r.t. global coordinates
  const int lim2 = size2 + k2_00;
  const int lim3 = size3 + k3_00;

  // Calculate increments (k1_inc, k2_inc, k3_inc)
  int tot_inc = item_ct1.get_local_range().get(2) * item_ct1.get_group_range(2);
  const int k3_inc = tot_inc/(size1*size2);
  tot_inc -= k3_inc*size1*size2;
  const int k2_inc = tot_inc/size1;
  const int k1_inc = tot_inc - k2_inc*size1;

  // Set data[0] = 0 for the global (0,0,0)
  if (k1 == 0 && k2 == 0 && k3 == 0) {
    T2 zero;
    zero.x() = (T)0;
    zero.y() = (T)0;
    data[0] = zero;
    // Increment position
    k1 += k1_inc;
    pos += k1_inc;
    if (k1 >= size1) {
      k1 -= size1;
      k2++;
    }
    k2 += k2_inc;
    pos += k2_inc*size1;
    if (k2 >= lim2) {
      k2 -= size2;
      k3++;
    }
    k3 += k3_inc;
    pos += k3_inc*size1*size2;
  }

  // Load prefac data into shared memory
  {
    int t = item_ct1.get_local_id(2);
    while (t < nfft1) {
      sh_prefac1[t] = prefac1[t];
      t += item_ct1.get_local_range().get(2);
    }
    t = item_ct1.get_local_id(2);
    while (t < nfft2) {
      sh_prefac2[t] = prefac2[t];
      t += item_ct1.get_local_range().get(2);
    }
    t = item_ct1.get_local_id(2);
    while (t < nfft3) {
      sh_prefac3[t] = prefac3[t];
      t += item_ct1.get_local_range().get(2);
    }
  }
  item_ct1.barrier();
 

  double energy = 0.0;
  double virial0 = 0.0;
  double virial1 = 0.0;
  double virial2 = 0.0;
  double virial3 = 0.0;
  double virial4 = 0.0;
  double virial5 = 0.0;

  // If nfft1 is odd, set nfft1_half to impossible value so that
  // the second condition in "if ( (k1 == 0) || (k1 == nfft1_half) )" 
  // is never satisfied
  const int nfft1_half = ((nfft1 & 1) == 0) ? nfft1/2 : -1;
  const int nfft2_half = nfft2/2;
  const int nfft3_half = nfft3/2;

  while (k3 < lim3) {

    T2 q = data[pos];

    int k2s = (k2 <= nfft2_half) ? k2 : k2 - nfft2;
    int k3s = (k3 <= nfft3_half) ? k3 : k3 - nfft3;

    T m1, m2, m3;
    if (doOrtho) {
      m1 = recip1x*k1;
      m2 = recip2y*k2s;
      m3 = recip3z*k3s;
    } else {
      m1 = recip1x*k1 + recip2x*k2s + recip3x*k3s;
      m2 = recip1y*k1 + recip2y*k2s + recip3y*k3s;
      m3 = recip1z*k1 + recip2z*k2s + recip3z*k3s;
    }

    T msq = m1*m1 + m2*m2 + m3*m3;
    T msq_inv = ((T)1)/msq;

    T theta3 = sh_prefac1[k1]*sh_prefac2[k2]*sh_prefac3[k3];
    T q2 = ((T)2) * (q.x() * q.x() + q.y() * q.y()) * theta3;
    if ( (k1 == 0) || (k1 == nfft1_half) ) q2 *= ((T)0.5);
    T xp3 = expfunc(-pi_ewald*msq)*piv_inv;
    T C = xp3*msq_inv;
    T theta = theta3*C;

    if (calc_energy_virial) {
      T fac = q2*C;
      T vir = ((T)2)*(pi_ewald + msq_inv);
      energy += fac;
      virial0 += (double)(fac*(vir*m1*m1 - ((T)1)));
      virial1 += (double)(fac*vir*m1*m2);
      virial2 += (double)(fac*vir*m1*m3);
      virial3 += (double)(fac*(vir*m2*m2 - ((T)1)));
      virial4 += (double)(fac*vir*m2*m3);
      virial5 += (double)(fac*(vir*m3*m3 - ((T)1)));
    }

    q.x() *= theta;
    q.y() *= theta;
    data[pos] = q;
    
    // Increment position
    k1 += k1_inc;
    pos += k1_inc;
    if (k1 >= size1) {
      k1 -= size1;
      k2++;
    }
    k2 += k2_inc;
    pos += k2_inc*size1;
    if (k2 >= lim2) {
      k2 -= size2;
      k3++;
    }
    k3 += k3_inc;
    pos += k3_inc*size2*size1;
  }

  auto sg = item_ct1.get_sub_group();

  // Reduce energy and virial
  if (calc_energy_virial) {
    const int tid = item_ct1.get_local_id(2) & (sg.get_local_range().get(0) - 1);
    const int base = (item_ct1.get_local_id(2) / sg.get_local_range().get(0));
    volatile RecipVirial_t* sh_ev = (RecipVirial_t *)sh_prefac;
    // Reduce within warps
    for (int d = sg.get_local_range().get(0) / 2; d >= 1; d /= 2) {
      // TODO: Potential precision/performance issues with DPCT calls
      energy += dpct::cast_ints_to_double(
          sg.shuffle(dpct::cast_double_to_int(energy, true), tid + d),
          sg.shuffle(dpct::cast_double_to_int(energy, false), tid + d));
      virial0 += dpct::cast_ints_to_double(
          sg.shuffle(dpct::cast_double_to_int(virial0, true), tid + d),
          sg.shuffle(dpct::cast_double_to_int(virial0, false), tid + d));
      virial1 += dpct::cast_ints_to_double(
          sg.shuffle(dpct::cast_double_to_int(virial1, true), tid + d),
          sg.shuffle(dpct::cast_double_to_int(virial1, false), tid + d));
      virial2 += dpct::cast_ints_to_double(
          sg.shuffle(dpct::cast_double_to_int(virial2, true), tid + d),
          sg.shuffle(dpct::cast_double_to_int(virial2, false), tid + d));
      virial3 += dpct::cast_ints_to_double(
          sg.shuffle(dpct::cast_double_to_int(virial3, true), tid + d),
          sg.shuffle(dpct::cast_double_to_int(virial3, false), tid + d));
      virial4 += dpct::cast_ints_to_double(
          sg.shuffle(dpct::cast_double_to_int(virial4, true), tid + d),
          sg.shuffle(dpct::cast_double_to_int(virial4, false), tid + d));
      virial5 += dpct::cast_ints_to_double(
          sg.shuffle(dpct::cast_double_to_int(virial5, true), tid + d),
          sg.shuffle(dpct::cast_double_to_int(virial5, false), tid + d));
    }
    // Reduce between warps
    // NOTE: this BLOCK_SYNC is needed because we're using a single shared memory buffer
    item_ct1.barrier();
    if (tid == 0) {
      sh_ev[base].energy = energy;
      sh_ev[base].virial[0] = virial0;
      sh_ev[base].virial[1] = virial1;
      sh_ev[base].virial[2] = virial2;
      sh_ev[base].virial[3] = virial3;
      sh_ev[base].virial[4] = virial4;
      sh_ev[base].virial[5] = virial5;
    }
    item_ct1.barrier();
    if (base == 0) {
      energy = (tid < item_ct1.get_local_range().get(2) / sg.get_local_range().get(0))
                   ? sh_ev[tid].energy : 0.0;
      virial0 = (tid < item_ct1.get_local_range().get(2) / sg.get_local_range().get(0))
                    ? sh_ev[tid].virial[0] : 0.0;
      virial1 = (tid < item_ct1.get_local_range().get(2) / sg.get_local_range().get(0))
                    ? sh_ev[tid].virial[1] : 0.0;
      virial2 = (tid < item_ct1.get_local_range().get(2) / sg.get_local_range().get(0))
                    ? sh_ev[tid].virial[2] : 0.0;
      virial3 = (tid < item_ct1.get_local_range().get(2) / sg.get_local_range().get(0))
                    ? sh_ev[tid].virial[3] : 0.0;
      virial4 = (tid < item_ct1.get_local_range().get(2) / sg.get_local_range().get(0))
                    ? sh_ev[tid].virial[4] : 0.0;
      virial5 = (tid < item_ct1.get_local_range().get(2) / sg.get_local_range().get(0))
                    ? sh_ev[tid].virial[5] : 0.0;
      for (int d = sg.get_local_range().get(0) / 2; d >= 1; d /= 2) {
        // TODO: Potential precision/performance issues with DPCT calls
        energy += dpct::cast_ints_to_double(
            sg.shuffle(dpct::cast_double_to_int(energy, true), tid + d),
            sg.shuffle(dpct::cast_double_to_int(energy, false), tid + d));
        virial0 += dpct::cast_ints_to_double(
            sg.shuffle(dpct::cast_double_to_int(virial0, true), tid + d),
            sg.shuffle(dpct::cast_double_to_int(virial0, false), tid + d));
        virial1 += dpct::cast_ints_to_double(
            sg.shuffle(dpct::cast_double_to_int(virial1, true), tid + d),
            sg.shuffle(dpct::cast_double_to_int(virial1, false), tid + d));
        virial2 += dpct::cast_ints_to_double(
            sg.shuffle(dpct::cast_double_to_int(virial2, true), tid + d),
            sg.shuffle(dpct::cast_double_to_int(virial2, false), tid + d));
        virial3 += dpct::cast_ints_to_double(
            sg.shuffle(dpct::cast_double_to_int(virial3, true), tid + d),
            sg.shuffle(dpct::cast_double_to_int(virial3, false), tid + d));
        virial4 += dpct::cast_ints_to_double(
            sg.shuffle(dpct::cast_double_to_int(virial4, true), tid + d),
            sg.shuffle(dpct::cast_double_to_int(virial4, false), tid + d));
        virial5 += dpct::cast_ints_to_double(
            sg.shuffle(dpct::cast_double_to_int(virial5, true), tid + d),
            sg.shuffle(dpct::cast_double_to_int(virial5, false), tid + d));
      }
    }

    if (item_ct1.get_local_id(2) == 0) {
      dpct::atomic_fetch_add(energy_recip, energy * 0.5);
      virial0 *= -0.5;
      virial1 *= -0.5;
      virial2 *= -0.5;
      virial3 *= -0.5;
      virial4 *= -0.5;
      virial5 *= -0.5;
      dpct::atomic_fetch_add(&virial[0], virial0);
      dpct::atomic_fetch_add(&virial[1], virial1);
      dpct::atomic_fetch_add(&virial[2], virial2);
      dpct::atomic_fetch_add(&virial[3], virial3);
      dpct::atomic_fetch_add(&virial[4], virial4);
      dpct::atomic_fetch_add(&virial[5], virial5);
    }

  }
}

template <typename T>
__dpct_inline__ void write_grid(const float val, const int ind, T *data) {
  dpct::atomic_fetch_add(&data[ind], (T)val);
}

//
// General version for any order
//
template <typename T, int order>
__dpct_inline__ void calc_one_theta(const T w, T *theta) {

  theta[order-1] = ((T)0);
  theta[1] = w;
  theta[0] = ((T)1) - w;

#pragma unroll
  for (int k=3;k <= order-1;k++) {
    T div = ((T)1) / (T)(k-1);
    theta[k-1] = div*w*theta[k-2];
#pragma unroll
    for (int j=1;j <= k-2;j++) {
      theta[k-j-1] = div*((w+j)*theta[k-j-2] + (k-j-w)*theta[k-j-1]);
    }
    theta[0] = div*(((T)1) - w)*theta[0];
  }
      
  //--- one more recursion
  T div = ((T)1) / (T)(order-1);
  theta[order-1] = div*w*theta[order-2];
#pragma unroll
  for (int j=1;j <= order-2;j++) {
    theta[order-j-1] = div*((w+j)*theta[order-j-2] + (order-j-w)*theta[order-j-1]);
  }
    
  theta[0] = div*(((T)1) - w)*theta[0];
}

//
// Calculate theta and dtheta for general order bspline
//
template <typename T, typename T3, int order>
__dpct_inline__ void calc_theta_dtheta(T wx, T wy, T wz, T3 *theta,
                                       T3 *dtheta) {

  theta[order - 1].x() = ((T)0);
  theta[order - 1].y() = ((T)0);
  theta[order - 1].z() = ((T)0);
  theta[1].x() = wx;
  theta[1].y() = wy;
  theta[1].z() = wz;
  theta[0].x() = ((T)1) - wx;
  theta[0].y() = ((T)1) - wy;
  theta[0].z() = ((T)1) - wz;

#pragma unroll
  for (int k=3;k <= order-1;k++) {
    T div = ((T)1) / (T)(k-1);
    theta[k - 1].x() = div * wx * theta[k - 2].x();
    theta[k - 1].y() = div * wy * theta[k - 2].y();
    theta[k - 1].z() = div * wz * theta[k - 2].z();
#pragma unroll
    for (int j=1;j <= k-2;j++) {
      theta[k - j - 1].x() = div * ((wx + j) * theta[k - j - 2].x() +
                                    (k - j - wx) * theta[k - j - 1].x());
      theta[k - j - 1].y() = div * ((wy + j) * theta[k - j - 2].y() +
                                    (k - j - wy) * theta[k - j - 1].y());
      theta[k - j - 1].z() = div * ((wz + j) * theta[k - j - 2].z() +
                                    (k - j - wz) * theta[k - j - 1].z());
    }
    theta[0].x() = div * (((T)1) - wx) * theta[0].x();
    theta[0].y() = div * (((T)1) - wy) * theta[0].y();
    theta[0].z() = div * (((T)1) - wz) * theta[0].z();
  }

  //--- perform standard b-spline differentiation
  dtheta[0].x() = -theta[0].x();
  dtheta[0].y() = -theta[0].y();
  dtheta[0].z() = -theta[0].z();
#pragma unroll
  for (int j=2;j <= order;j++) {
    dtheta[j - 1].x() = theta[j - 2].x() - theta[j - 1].x();
    dtheta[j - 1].y() = theta[j - 2].y() - theta[j - 1].y();
    dtheta[j - 1].z() = theta[j - 2].z() - theta[j - 1].z();
  }
      
  //--- one more recursion
  T div = ((T)1) / (T)(order-1);
  theta[order - 1].x() = div * wx * theta[order - 2].x();
  theta[order - 1].y() = div * wy * theta[order - 2].y();
  theta[order - 1].z() = div * wz * theta[order - 2].z();
#pragma unroll
  for (int j=1;j <= order-2;j++) {
    theta[order - j - 1].x() =
        div * ((wx + j) * theta[order - j - 2].x() +
               (order - j - wx) * theta[order - j - 1].x());
    theta[order - j - 1].y() =
        div * ((wy + j) * theta[order - j - 2].y() +
               (order - j - wy) * theta[order - j - 1].y());
    theta[order - j - 1].z() =
        div * ((wz + j) * theta[order - j - 2].z() +
               (order - j - wz) * theta[order - j - 1].z());
  }

  theta[0].x() = div * (((T)1) - wx) * theta[0].x();
  theta[0].y() = div * (((T)1) - wy) * theta[0].y();
  theta[0].z() = div * (((T)1) - wz) * theta[0].z();
}

//
// Spreads the charge on the grid. Calculates theta and dtheta on the fly
// blockDim.x                   = Number of atoms each block loads
// blockDim.y*blockDim.x/order3 = Number of atoms we spread at once
//
template <typename AT, int order, bool periodicY, bool periodicZ>
void
spread_charge_kernel(const sycl::float4 *xyzq, const int ncoord,
                     const int nfftx, const int nffty, const int nfftz,
                     const int xsize, const int ysize, const int zsize,
                     const int xdim, const int y00, const int z00, AT *data,
                     sycl::nd_item<3> item_ct1, int *sh_ix, int *sh_iy,
                     int *sh_iz, float *sh_thetax, float *sh_thetay,
                     float *sh_thetaz) {

  // Shared memory use:
  // order = 4: 1920 bytes
  // order = 6: 2688 bytes
  // order = 8: 3456 bytes
/* DPCT_ORIG   __shared__ int sh_ix[32];*/
/* DPCT_ORIG   __shared__ int sh_iy[32];*/
/* DPCT_ORIG   __shared__ int sh_iz[32];*/
/* DPCT_ORIG   __shared__ float sh_thetax[order*32];*/
/* DPCT_ORIG   __shared__ float sh_thetay[order*32];*/
/* DPCT_ORIG   __shared__ float sh_thetaz[order*32];*/

  // Process atoms pos to pos_end-1 (blockDim.x)
  const unsigned int pos =
      item_ct1.get_group(2) * item_ct1.get_local_range().get(2) +
      item_ct1.get_local_id(2);
  const unsigned int pos_end = sycl::min(
      (unsigned int)((item_ct1.get_group(2) + 1) * item_ct1.get_local_range(2)),
      (unsigned int)ncoord);

  if (pos < pos_end && item_ct1.get_local_id(1) == 0) {

    sycl::float4 xyzqi = xyzq[pos];
    float x = xyzqi.x();
    float y = xyzqi.y();
    float z = xyzqi.z();
    float q = xyzqi.w();

    float frx = ((float)nfftx)*x;
    float fry = ((float)nffty)*y;
    float frz = ((float)nfftz)*z;

    int frxi = (int)frx;
    int fryi = (int)fry;
    int frzi = (int)frz;

    float wx = frx - (float)frxi;
    float wy = fry - (float)fryi;
    float wz = frz - (float)frzi;

    if (!periodicY && y00 == 0 && fryi >= ysize) fryi -= nffty;
    if (!periodicZ && z00 == 0 && frzi >= zsize) frzi -= nfftz;

    sh_ix[item_ct1.get_local_id(2)] = frxi;
    sh_iy[item_ct1.get_local_id(2)] = fryi - y00;
    sh_iz[item_ct1.get_local_id(2)] = frzi - z00;

    float theta[order];

    calc_one_theta<float, order>(wx, theta);
#pragma unroll
    for (int i = 0; i < order; i++)
        sh_thetax[item_ct1.get_local_id(2) * order + i] = q * theta[i];

    calc_one_theta<float, order>(wy, theta);
#pragma unroll
    for (int i = 0; i < order; i++)
        sh_thetay[item_ct1.get_local_id(2) * order + i] = theta[i];

    calc_one_theta<float, order>(wz, theta);
#pragma unroll
    for (int i = 0; i < order; i++)
        sh_thetaz[item_ct1.get_local_id(2) * order + i] = theta[i];
  }

  item_ct1.barrier();

  // Grid point location, values of (ix0, iy0, iz0) are in range 0..order-1
  // NOTE: Only tid=0...order*order*order-1 do any computation
  const int order3 = ((order * order * order - 1) /
                          item_ct1.get_sub_group().get_local_range().get(0) +
                      1) *
                     item_ct1.get_sub_group().get_local_range().get(0);
  const int tid =
      (item_ct1.get_local_id(2) +
       item_ct1.get_local_id(1) * item_ct1.get_local_range().get(2)) %
      order3; // 0...order3-1
  const int x0 = tid % order;
  const int y0 = (tid / order) % order;
  const int z0 = tid / (order*order);

  // Loop over atoms pos..pos_end-1
  int iadd = item_ct1.get_local_range().get(2) *
             item_ct1.get_local_range().get(1) / order3;
  int i = (item_ct1.get_local_id(2) +
           item_ct1.get_local_id(1) * item_ct1.get_local_range().get(2)) /
          order3;
  int iend =
      pos_end - item_ct1.get_group(2) * item_ct1.get_local_range().get(2);
  for (;i < iend;i += iadd) {
    int x = sh_ix[i] + x0;
    int y = sh_iy[i] + y0;
    int z = sh_iz[i] + z0;
      
    if (x >= nfftx) x -= nfftx;

    if (periodicY  && (y >= nffty)) y -= nffty;
    if (!periodicY && (y < 0 || y >= ysize)) continue;

    if (periodicZ  && (z >= nfftz)) z -= nfftz;
    if (!periodicZ && (z < 0 || z >= zsize)) continue;
      
    // Get position on the grid
    int ind = x + xdim*(y + ysize*(z));
    
    // Here we unroll the 6x6x6 loop with 216 threads.
    // NOTE: We use 7*32=224 threads to do this
    // Calculate interpolated charge value and store it to global memory

    if (tid < order*order*order)
      write_grid<AT>(sh_thetax[i*order+x0]*sh_thetay[i*order+y0]*sh_thetaz[i*order+z0], ind, data);
  }

}

//-----------------------------------------------------------------------------------------
// Generic version can not be used
template <typename T>
__dpct_inline__ void gather_force_store(const float fx, const float fy,
                                        const float fz, const int stride,
                                        const int pos, T *force) {
}

// Template specialization for "float"
template <>
__dpct_inline__ void gather_force_store<float>(const float fx, const float fy,
                                               const float fz, const int stride,
                                               const int pos, float *force) {
  // Store into non-strided float XYZ array
  force[pos]          = fx;
  force[pos+stride]   = fy;
  force[pos+stride*2] = fz;
}

// Template specialization for "float3"
template <>
__dpct_inline__
    void
    gather_force_store<sycl::float3>(const float fx, const float fy,
                                     const float fz, const int stride,
                                     const int pos,
                                     sycl::float3 *force) {
  // Store into non-strided "float3" array
  force[pos].x() = fx;
  force[pos].y() = fy;
  force[pos].z() = fz;
}
//-----------------------------------------------------------------------------------------

// Per atom data structure for the gather_force -kernels
template <typename T, int order>
struct gather_t {
  int ix;
  int iy;
  int iz;
  T charge;
  T thetax[order];
  T thetay[order];
  T thetaz[order];
  T dthetax[order];
  T dthetay[order];
  T dthetaz[order];
  float f1;
  float f2;
  float f3;
};

//
// Gathers forces from the grid
// blockDim.x            = Number of atoms each block loads
// blockDim.x*blockDim.y = Total number of threads per block
//
template <typename CT, typename FT, int order, bool periodicY, bool periodicZ>
void gather_force(
    const sycl::float4 *xyzq, const int ncoord, const int nfftx,
    const int nffty, const int nfftz, const int xsize, const int ysize,
    const int zsize, const int xdim, const int y00, const int z00,
    // const float recip1, const float recip2, const float recip3,
    const float *data, // NOTE: data is used for loads when __CUDA_ARCH__ >= 350
    // TODO: const dpct::image_accessor_ext<dpct_placeholder, 1> gridTexObj,
    const int stride, FT *force, sycl::nd_item<3> item_ct1,
    gather_t<CT, order> *shmem) {

  const int tid =
      item_ct1.get_local_id(2) +
      item_ct1.get_local_id(1) * item_ct1.get_local_range().get(2); // 0...63

  // Shared memory
/* DPCT_ORIG   __shared__ gather_t<CT, order> shmem[32];*/

  const int pos = item_ct1.get_group(2) * item_ct1.get_local_range().get(2) +
                  item_ct1.get_local_id(2);
  const int pos_end = sycl::min(
      (unsigned int)((item_ct1.get_group(2) + 1) * item_ct1.get_local_range(2)),
      (unsigned int)ncoord);

  // Load atom data into shared memory
  if (pos < pos_end && item_ct1.get_local_id(1) == 0) {

    sycl::float4 xyzqi = xyzq[pos];
    float x = xyzqi.x();
    float y = xyzqi.y();
    float z = xyzqi.z();
    float q = xyzqi.w();

    float frx = ((float)nfftx)*x;
    float fry = ((float)nffty)*y;
    float frz = ((float)nfftz)*z;

    int frxi = (int)frx;
    int fryi = (int)fry;
    int frzi = (int)frz;

    float wx = frx - (float)frxi;
    float wy = fry - (float)fryi;
    float wz = frz - (float)frzi;

    if (!periodicY && y00 == 0 && fryi >= ysize) fryi -= nffty;
    if (!periodicZ && z00 == 0 && frzi >= zsize) frzi -= nfftz;

    shmem[item_ct1.get_local_id(2)].ix = frxi;
    shmem[item_ct1.get_local_id(2)].iy = fryi - y00;
    shmem[item_ct1.get_local_id(2)].iz = frzi - z00;
    shmem[item_ct1.get_local_id(2)].charge = q;

    sycl::float3 theta_tmp[order];
    sycl::float3 dtheta_tmp[order];
    calc_theta_dtheta<float, sycl::float3, order>(wx, wy, wz, theta_tmp,
                                                  dtheta_tmp);

#pragma unroll
    for (int i = 0; i < order; i++) shmem[item_ct1.get_local_id(2)].thetax[i] =
        theta_tmp[i].x();

#pragma unroll
    for (int i = 0; i < order; i++) shmem[item_ct1.get_local_id(2)].thetay[i] =
        theta_tmp[i].y();

#pragma unroll
    for (int i = 0; i < order; i++) shmem[item_ct1.get_local_id(2)].thetaz[i] =
        theta_tmp[i].z();

#pragma unroll
    for (int i = 0; i < order; i++) shmem[item_ct1.get_local_id(2)].dthetax[i] =
        dtheta_tmp[i].x();

#pragma unroll
    for (int i = 0; i < order; i++) shmem[item_ct1.get_local_id(2)].dthetay[i] =
        dtheta_tmp[i].y();

#pragma unroll
    for (int i = 0; i < order; i++) shmem[item_ct1.get_local_id(2)].dthetaz[i] =
        dtheta_tmp[i].z();
  }
  item_ct1.barrier();

  // We divide the order x order x order cube into 8 sub-cubes.
  // These sub-cubes are taken care by a single thread
  // The size of the sub-cubes is:
  // order=4 : 2x2x2
  // order=6 : 3x3x3
  // order=8 : 4x4x4
  const int nsc = (order == 4) ? 2 : ((order == 6) ? 3 : 4);
  // Calculate the starting index on the sub-cube for this thread
  // tid = 0...63
  const int t = (tid % 8);         // sub-cube index (0...7)
  // t = (tx0 + ty0*2 + tz0*4)/nsc
  // (tx0, ty0, tz0) gives the starting index of the 3x3x3 sub-cube
  const int tz0 = (t / 4)*nsc;
  const int ty0 = ((t / 2) % 2)*nsc;
  const int tx0 = (t % 2)*nsc;

  //
  // Calculate forces for 32 atoms. We have 32*2 = 64 threads
  // Loop is iterated 4 times:
  //                         (iterations)
  // Threads 0...7   = atoms 0, 8,  16, 24
  // Threads 8...15  = atoms 1, 9,  17, 25
  // Threads 16...31 = atoms 2, 10, 18, 26
  //                ...
  // Threads 56...63 = atoms 7, 15, 23, 31
  //

  int base = tid/8;
  const int base_end =
      pos_end - item_ct1.get_group(2) * item_ct1.get_local_range().get(2);

  // Make sure to mask out any threads that are not running the loop.
  // This will happen if the number of atoms is not a multiple of 32.
  auto sg = item_ct1.get_sub_group();
  unsigned long warp_mask = WARP_BALLOT(sg, base < base_end);

  while (base < base_end) {

    float f1 = 0.0f;
    float f2 = 0.0f;
    float f3 = 0.0f;
    int ix0 = shmem[base].ix;
    int iy0 = shmem[base].iy;
    int iz0 = shmem[base].iz;

    // Each thread calculates a nsc x nsc x nsc sub-cube
#pragma unroll
    for (int i=0;i < nsc*nsc*nsc;i++) {
      int tz = tz0 + (i/(nsc*nsc));
      int ty = ty0 + ((i/nsc) % nsc);
      int tx = tx0 + (i % nsc);

      int ix = ix0 + tx;
      int iy = iy0 + ty;
      int iz = iz0 + tz;
      if (ix >= nfftx) ix -= nfftx;

      if (periodicY  && (iy >= nffty)) iy -= nffty;
      if (!periodicY && (iy < 0 || iy >= ysize)) continue;

      if (periodicZ  && (iz >= nfftz)) iz -= nfftz;
      if (!periodicZ && (iz < 0 || iz >= zsize)) continue;

      int ind = ix + (iy + iz*ysize)*xdim;

      // TODO: Use texture memory and read-only cache
      float q0 = data[ind];

      float thx0 = shmem[base].thetax[tx];
      float thy0 = shmem[base].thetay[ty];
      float thz0 = shmem[base].thetaz[tz];
      float dthx0 = shmem[base].dthetax[tx];
      float dthy0 = shmem[base].dthetay[ty];
      float dthz0 = shmem[base].dthetaz[tz];
      f1 += dthx0 * thy0 * thz0 * q0;
      f2 += thx0 * dthy0 * thz0 * q0;
      f3 += thx0 * thy0 * dthz0 * q0;
    }

    //-------------------------

    // Reduce
    const int i = item_ct1.get_local_id(2) & 7;

    f1 += WARP_SHUFFLE_MASK(sg, warp_mask, f1, i + 4, 8);
    f2 += WARP_SHUFFLE_MASK(sg, warp_mask, f2, i + 4, 8);
    f3 += WARP_SHUFFLE_MASK(sg, warp_mask, f3, i + 4, 8);

    f1 += WARP_SHUFFLE_MASK(sg, warp_mask, f1, i + 2, 8);
    f2 += WARP_SHUFFLE_MASK(sg, warp_mask, f2, i + 2, 8);
    f3 += WARP_SHUFFLE_MASK(sg, warp_mask, f3, i + 2, 8);

    f1 += WARP_SHUFFLE_MASK(sg, warp_mask, f1, i + 1, 8);
    f2 += WARP_SHUFFLE_MASK(sg, warp_mask, f2, i + 1, 8);
    f3 += WARP_SHUFFLE_MASK(sg, warp_mask, f3, i + 1, 8);

    if (i == 0) {
      shmem[base].f1 = f1;
      shmem[base].f2 = f2;
      shmem[base].f3 = f3;
    }

    base += 8;
    warp_mask = WARP_BALLOT(sg, (base < base_end));
  }

  // Write forces
  item_ct1.barrier();
  if (pos < pos_end && item_ct1.get_local_id(1) == 0) {
    float f1 = shmem[item_ct1.get_local_id(2)].f1;
    float f2 = shmem[item_ct1.get_local_id(2)].f2;
    float f3 = shmem[item_ct1.get_local_id(2)].f3;
    float q = -shmem[item_ct1.get_local_id(2)].charge; //*ccelec_float;
    // float fx = q*recip1*f1*nfftx;
    // float fy = q*recip2*f2*nffty;
    // float fz = q*recip3*f3*nfftz;
    float fx = q*f1*nfftx;
    float fy = q*f2*nffty;
    float fz = q*f3*nfftz;
    gather_force_store<FT>(fx, fy, fz, stride, pos, force);
  }

}

const int TILEDIM = 32;
const int TILEROWS = 8;

template <typename T>
__dpct_inline__ void transpose_xyz_yzx_device(
    const int x_in, const int y_in, const int z_in, const int x_out,
    const int y_out, const int nx, const int ny, const int nz,
    const int xsize_in, const int ysize_in, const int ysize_out,
    const int zsize_out, const T *data_in, T *data_out,
    sycl::nd_item<3> item_ct1, dpct::accessor<T, dpct::local, 2> tile) {

  // Read (x,y) data_in into tile (shared memory)
  for (int j=0;j < TILEDIM;j += TILEROWS)
    if ((x_in < nx) && (y_in + j < ny) && (z_in < nz))
      tile[item_ct1.get_local_id(1) + j][item_ct1.get_local_id(2)] =
          data_in[x_in + (y_in + j + z_in * ysize_in) * xsize_in];

  item_ct1.barrier();

  // Write (y,x) tile into data_out
  const int z_out = z_in;
  for (int j=0;j < TILEDIM;j += TILEROWS)
    if ((x_out + j < nx) && (y_out < ny) && (z_out < nz))
      data_out[y_out + (z_out + (x_out + j) * zsize_out) * ysize_out] =
          tile[item_ct1.get_local_id(2)][item_ct1.get_local_id(1) + j];
}

//
// Transposes a 3d matrix out-of-place: data_in(x, y, z) -> data_out(y, z, x)
//
template <typename T>
void transpose_xyz_yzx_kernel(const int nx, const int ny, const int nz,
                              const int xsize_in, const int ysize_in,
                              const int ysize_out, const int zsize_out,
                              const T *data_in, T *data_out,
                              sycl::nd_item<3> item_ct1,
                              dpct::accessor<T, dpct::local, 2> tile) {

  int x_in = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(2);
  int y_in = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(1);
  int z_in = item_ct1.get_group(0) + item_ct1.get_local_id(0);

  int x_out = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(1);
  int y_out = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(2);

  transpose_xyz_yzx_device<T>(x_in, y_in, z_in, x_out, y_out, nx, ny, nz,
                              xsize_in, ysize_in, ysize_out, zsize_out, data_in,
                              data_out, item_ct1, tile);

/*
  // Shared memory
  __shared__ T tile[TILEDIM][TILEDIM+1];

  int x = blockIdx.x * TILEDIM + threadIdx.x;
  int y = blockIdx.y * TILEDIM + threadIdx.y;
  int z = blockIdx.z           + threadIdx.z;

  // Read (x,y) data_in into tile (shared memory)
  for (int j=0;j < TILEDIM;j += TILEROWS)
    if ((x < nx) && (y + j < ny) && (z < nz))
      tile[threadIdx.y + j][threadIdx.x] = data_in[x + (y + j + z*ysize_in)*xsize_in];

  item_ct1.barrier();

  // Write (y,x) tile into data_out
  x = blockIdx.x * TILEDIM + threadIdx.y;
  y = blockIdx.y * TILEDIM + threadIdx.x;
  for (int j=0;j < TILEDIM;j += TILEROWS)
    if ((x + j < nx) && (y < ny) && (z < nz))
      data_out[y + (z + (x+j)*zsize_out)*ysize_out] = tile[threadIdx.x][threadIdx.y + j];
*/
}

//
// Transposes a batch of 3d matrices out-of-place: data_in(x, y, z) -> data_out(y, z, x)
// Batch index bi is encoded in blockIdx.z, where 
// blockIdx.z = 0...nz-1 are for batch 1
// blockIdx.z = nz...2*nz-1 are for batch 2
// ...
// gridDim.z = nz*numBatches
//
template <typename T>
void batchTranspose_xyz_yzx_kernel(const TransposeBatch<T> *batches,
                                   const int ny, const int nz,
                                   const int xsize_in, const int ysize_in,
                                   sycl::nd_item<3> item_ct1,
                                   dpct::accessor<T, dpct::local, 2> tile) {

  int x_in = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(2);
  int y_in = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(1);
  int z_in = (item_ct1.get_group(0) % nz) + item_ct1.get_local_id(0);

  int x_out = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(1);
  int y_out = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(2);

  int bi = item_ct1.get_group(0) / nz;

  TransposeBatch<T> batch = batches[bi];
  int nx        = batch.nx;
  int ysize_out = batch.ysize_out;
  int zsize_out = batch.zsize_out;
  T* data_in    = batch.data_in;
  T* data_out   = batch.data_out;

  transpose_xyz_yzx_device<T>(x_in, y_in, z_in, x_out, y_out, nx, ny, nz,
                              xsize_in, ysize_in, ysize_out, zsize_out, data_in,
                              data_out, item_ct1, tile);
}

/*
//
// Transposes a 3d matrix out-of-place: data_in(x, y, z) -> data_out(y, z, x)
//
template <typename T>
__forceinline__ __device__
void transpose_xyz_yzx_dev(
  const int blockz,
  const int nx, const int ny, const int nz,
  const int xsize_in, const int ysize_in,
  const int xsize_out, const int ysize_out,
  const T* data_in, T* data_out) {

  // Shared memory
  __shared__ T tile[TILEDIM][TILEDIM+1];

  int x = blockIdx.x * TILEDIM + threadIdx.x;
  int y = blockIdx.y * TILEDIM + threadIdx.y;
  // int z = blockIdx.z           + threadIdx.z;
  int z = blockz               + threadIdx.z;

  // Read (x,y) data_in into tile (shared memory)
  for (int j=0;j < TILEDIM;j += TILEROWS)
    if ((x < nx) && (y + j < ny) && (z < nz))
      tile[threadIdx.y + j][threadIdx.x] = data_in[x + (y + j + z*ysize_in)*xsize_in];

  item_ct1.barrier();

  // Write (y,x) tile into data_out
  x = blockIdx.x * TILEDIM + threadIdx.y;
  y = blockIdx.y * TILEDIM + threadIdx.x;
  for (int j=0;j < TILEDIM;j += TILEROWS)
    if ((x + j < nx) && (y < ny) && (z < nz))
      data_out[y + (z + (x+j)*ysize_out)*xsize_out] = tile[threadIdx.x][threadIdx.y + j];

}

//
// Transposes a 3d matrix out-of-place: data_in(x, y, z) -> data_out(y, z, x)
// (nx, ny, nz)                     = size of the transposed volume
// (xsize_in, ysize_in, zsize_in)   = size of the input data
// into nblock memory blocks
//
template <typename T>
__global__ void transpose_xyz_yzx_kernel(
  const int nblock,
  const int nx, const int ny, const int nz,
  const int xsize_in, const int ysize_in,
  const int xsize_out, const int ysize_out,
  const T* data_in, T* data_out) {

  const int iblock = blockIdx.z/nz;

  if (iblock < nblock) {
    transpose_xyz_yzx_dev(blockIdx.z % nz, nx, ny, nz,
      xsize_in, ysize_in, xsize_out, ysize_out,
      data_in, data_out);
  }

}
*/

template <typename T>
__dpct_inline__ void transpose_xyz_zxy_device(
    const int x_in, const int y_in, const int z_in, const int x_out,
    const int z_out, const int nx, const int ny, const int nz,
    const int xsize_in, const int ysize_in, const int zsize_out,
    const int xsize_out, const T *data_in, T *data_out,
    sycl::nd_item<3> item_ct1, dpct::accessor<T, dpct::local, 2> tile) {

  // Read (x,z) data_in into tile (shared memory)
  for (int k=0;k < TILEDIM;k += TILEROWS)
    if ((x_in < nx) && (y_in < ny) && (z_in + k < nz))
      tile[item_ct1.get_local_id(1) + k][item_ct1.get_local_id(2)] =
          data_in[x_in + (y_in + (z_in + k) * ysize_in) * xsize_in];

  item_ct1.barrier();

  // Write (z,x) tile into data_out
  const int y_out = y_in;
  for (int k=0;k < TILEDIM;k += TILEROWS)
    if ((x_out + k < nx) && (y_out < ny) && (z_out < nz))
      data_out[z_out + (x_out + k + y_out * xsize_out) * zsize_out] =
          tile[item_ct1.get_local_id(2)][item_ct1.get_local_id(1) + k];
}

//
// Transposes a 3d matrix out-of-place: data_in(x, y, z) -> data_out(z, x, y)
//
template <typename T>
void transpose_xyz_zxy_kernel(const int nx, const int ny, const int nz,
                              const int xsize_in, const int ysize_in,
                              const int zsize_out, const int xsize_out,
                              const T *data_in, T *data_out,
                              sycl::nd_item<3> item_ct1,
                              dpct::accessor<T, dpct::local, 2> tile) {

  int x_in = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(2);
  int y_in = item_ct1.get_group(0) + item_ct1.get_local_id(0);
  int z_in = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(1);

  int x_out = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(1);
  int z_out = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(2);

  transpose_xyz_zxy_device<T>(x_in, y_in, z_in, x_out, z_out, nx, ny, nz,
                              xsize_in, ysize_in, zsize_out, xsize_out, data_in,
                              data_out, item_ct1, tile);
}

//
// Transposes a batch of 3d matrices out-of-place: data_in(x, y, z) -> data_out(z, x, y)
// Batch index bi is encoded in blockIdx.z, where 
// blockIdx.z = 0...ny-1 are for batch 1
// blockIdx.z = ny...2*ny-1 are for batch 2
// ...
// gridDim.z = ny*numBatches
//
template <typename T>
void batchTranspose_xyz_zxy_kernel(const TransposeBatch<T> *batches,
                                   const int ny, const int nz,
                                   const int xsize_in, const int ysize_in,
                                   sycl::nd_item<3> item_ct1,
                                   dpct::accessor<T, dpct::local, 2> tile) {

  int x_in = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(2);
  int y_in = (item_ct1.get_group(0) % ny) + item_ct1.get_local_id(0);
  int z_in = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(1);

  int x_out = item_ct1.get_group(2) * TILEDIM + item_ct1.get_local_id(1);
  int z_out = item_ct1.get_group(1) * TILEDIM + item_ct1.get_local_id(2);

  int bi = item_ct1.get_group(0) / ny;

  TransposeBatch<T> batch = batches[bi];
  int nx        = batch.nx;
  int zsize_out = batch.zsize_out;
  int xsize_out = batch.xsize_out;
  T* data_in    = batch.data_in;
  T* data_out   = batch.data_out;

  transpose_xyz_zxy_device<T>(x_in, y_in, z_in, x_out, z_out, nx, ny, nz,
                              xsize_in, ysize_in, zsize_out, xsize_out, data_in,
                              data_out, item_ct1, tile);
}

//#######################################################################################
//#######################################################################################
//#######################################################################################

void spread_charge(
    const sycl::float4 *atoms, const int numAtoms, const int nfftx,
    const int nffty, const int nfftz, const int xsize, const int ysize,
    const int zsize, const int xdim, const int y00, const int z00,
    const bool periodicY, const bool periodicZ,
    float *data, const int order, sycl::queue *stream) {

  sycl::range<3> nthread(1, 1, 1), nblock(1, 1, 1);

  AC_TAG("spread_charge");
  sycl::float4* f4atoms = (sycl::float4*)atoms;
  AC_DEVICE_FLOAT4(*stream, "pre_spread_charge", f4atoms, numAtoms);
  AC_DEVICE(*stream, "pre_spread_charge", data, xsize*ysize*zsize);

  switch(order) {
  case 4:
    nthread[2] = 32;
    nthread[1] = 4;
    nthread[0] = 1;
    nblock[2] = (numAtoms - 1) / nthread[2] + 1;
    nblock[1] = 1;
    nblock[0] = 1;
    if (periodicY && periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(4 * 32), cgh);

        cgh.parallel_for<class spread_charge_order4_periodicYZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 4, true, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else if (periodicY)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(4 * 32), cgh);

        cgh.parallel_for<class spread_charge_order4_periodicY_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 4, true, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else if (periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(4 * 32), cgh);

        cgh.parallel_for<class spread_charge_order4_periodicZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 4, false, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(4 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(4 * 32), cgh);

        cgh.parallel_for<class spread_charge_order4_other_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 4, false, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    break;

  case 6:
    nthread[2] = 32;
    nthread[1] = 7;
    nthread[0] = 1;
    nblock[2] = (numAtoms - 1) / nthread[2] + 1;
    nblock[1] = 1;
    nblock[0] = 1;
    if (periodicY && periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(6 * 32), cgh);

        cgh.parallel_for<class spread_charge_order6_periodicYZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 6, true, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else if (periodicY)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(6 * 32), cgh);

        cgh.parallel_for<class spread_charge_order6_periodicY_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 6, true, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else if (periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(6 * 32), cgh);

        cgh.parallel_for<class spread_charge_order6_periodicZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 6, false, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(6 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(6 * 32), cgh);

        cgh.parallel_for<class spread_charge_order6_other_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 6, false, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    break;

  case 8:
    nthread[2] = 32;
    nthread[1] = 16;
    nthread[0] = 1;
    nblock[2] = (numAtoms - 1) / nthread[2] + 1;
    nblock[1] = 1;
    nblock[0] = 1;
    if (periodicY && periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(8 * 32), cgh);

        cgh.parallel_for<class spread_charge_order8_periodicYZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 8, true, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else if (periodicY)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(8 * 32), cgh);

        cgh.parallel_for<class spread_charge_order8_periodicY_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 8, true, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else if (periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(8 * 32), cgh);

        cgh.parallel_for<class spread_charge_order8_periodicZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 8, false, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    else
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_ix_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iy_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<int, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_iz_acc_ct1(sycl::range<1>(32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetax_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetay_acc_ct1(sycl::range<1>(8 * 32), cgh);
        sycl::accessor<float, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            sh_thetaz_acc_ct1(sycl::range<1>(8 * 32), cgh);

        cgh.parallel_for<class spread_charge_order8_other_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              spread_charge_kernel<float, 8, false, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data, item_ct1, sh_ix_acc_ct1.get_pointer(),
                  sh_iy_acc_ct1.get_pointer(), sh_iz_acc_ct1.get_pointer(),
                  sh_thetax_acc_ct1.get_pointer(),
                  sh_thetay_acc_ct1.get_pointer(),
                  sh_thetaz_acc_ct1.get_pointer());
            });
      });
    break;

  default:
    char str[128];
    sprintf(str, "spread_charge, order %d not implemented",order);
    dpcppNAMD_bug(str);
  }

  stream->wait();
  AC_DEVICE_FLOAT4(*stream, "post_spread_charge", f4atoms, numAtoms);
  AC_DEVICE(*stream, "post_spread_charge", data, xsize*ysize*zsize);
}

void scalar_sum(const bool orderXYZ, const int nfft1, const int nfft2,
                const int nfft3, const int size1, const int size2,
                const int size3, const double kappa, const float recip1x,
                const float recip1y, const float recip1z, const float recip2x,
                const float recip2y, const float recip2z, const float recip3x,
                const float recip3y, const float recip3z, const double volume,
                const float *prefac1, const float *prefac2,
                const float *prefac3, const int k2_00, const int k3_00,
                const bool doEnergyVirial, double *energy, double *virial,
                sycl::float2 *data,
                sycl::queue *stream) {

  int nthread = 256;
  int nblock = 256;

  int shmem_size = sizeof(float)*(nfft1 + nfft2 + nfft3);
  if (doEnergyVirial) {
    const int warpSize = 32;
    shmem_size = std::max(shmem_size,
                          (int)((nthread / warpSize) * sizeof(RecipVirial_t)));
  }

  float piv_inv = (float)(1.0/(M_PI*volume));
  float fac = (float)(M_PI*M_PI/(kappa*kappa));

  AC_TAG("scalar_sum");

  if (doEnergyVirial) {
    AC_DEVICE(*stream, "pre_scalar_sum", energy, 1);
    AC_DEVICE(*stream, "pre_scalar_sum", virial, 9);
    AC_DEVICE_FLOAT2(*stream, "pre_scalar_sum", data, size1*size2*size3);

    if (orderXYZ) {
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<uint8_t, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            dpct_local_acc_ct1(sycl::range<1>(shmem_size), cgh);

        cgh.parallel_for<class scalar_sum_virial_orderXYZ_name>(
            sycl::nd_range<3>(sycl::range<3>(1, 1, nblock) *
                                  sycl::range<3>(1, 1, nthread),
                              sycl::range<3>(1, 1, nthread)),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              scalar_sum_kernel<float, sycl::float2, true, true, false>(
                  nfft1, nfft2, nfft3, size1, size2, size3, recip1x, recip1y,
                  recip1z, recip2x, recip2y, recip2z, recip3x, recip3y, recip3z,
                  prefac1, prefac2, prefac3, fac, piv_inv, k2_00, k3_00, data,
                  energy, virial, item_ct1, dpct_local_acc_ct1.get_pointer());
            });
      });
    } else {
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<uint8_t, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            dpct_local_acc_ct1(sycl::range<1>(shmem_size), cgh);

        cgh.parallel_for<class scalar_sum_virial_other_name>(
            sycl::nd_range<3>(sycl::range<3>(1, 1, nblock) *
                                  sycl::range<3>(1, 1, nthread),
                              sycl::range<3>(1, 1, nthread)),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              scalar_sum_kernel<float, sycl::float2, true, false, false>(
                  nfft1, nfft2, nfft3, size1, size2, size3, recip1x, recip1y,
                  recip1z, recip2x, recip2y, recip2z, recip3x, recip3y, recip3z,
                  prefac1, prefac2, prefac3, fac, piv_inv, k2_00, k3_00, data,
                  energy, virial, item_ct1, dpct_local_acc_ct1.get_pointer());
            });
      });
    }

    stream->wait();
    AC_DEVICE(*stream, "post_scalar_sum", energy, 1);
    AC_DEVICE(*stream, "post_scalar_sum", virial, 9);
    AC_DEVICE_FLOAT2(*stream, "post_scalar_sum", data, size1*size2*size3);
  } else {
    AC_DEVICE_FLOAT2(*stream, "pre_scalar_sum", data, size1*size2*size3);

    if (orderXYZ) {
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<uint8_t, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            dpct_local_acc_ct1(sycl::range<1>(shmem_size), cgh);

        cgh.parallel_for<class scalar_sum_novirial_orderXYZ_name>(
            sycl::nd_range<3>(sycl::range<3>(1, 1, nblock) *
                                  sycl::range<3>(1, 1, nthread),
                              sycl::range<3>(1, 1, nthread)),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              scalar_sum_kernel<float, sycl::float2, false, true, false>(
                  nfft1, nfft2, nfft3, size1, size2, size3, recip1x, recip1y,
                  recip1z, recip2x, recip2y, recip2z, recip3x, recip3y, recip3z,
                  prefac1, prefac2, prefac3, fac, piv_inv, k2_00, k3_00, data,
                  NULL, NULL, item_ct1, dpct_local_acc_ct1.get_pointer());
            });
      });
    } else {
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<uint8_t, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            dpct_local_acc_ct1(sycl::range<1>(shmem_size), cgh);

        cgh.parallel_for<class scalar_sum_novirial_other_name>(
            sycl::nd_range<3>(sycl::range<3>(1, 1, nblock) *
                                  sycl::range<3>(1, 1, nthread),
                              sycl::range<3>(1, 1, nthread)),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              scalar_sum_kernel<float, sycl::float2, false, false, false>(
                  nfft1, nfft2, nfft3, size1, size2, size3, recip1x, recip1y,
                  recip1z, recip2x, recip2y, recip2z, recip3x, recip3y, recip3z,
                  prefac1, prefac2, prefac3, fac, piv_inv, k2_00, k3_00, data,
                  NULL, NULL, item_ct1, dpct_local_acc_ct1.get_pointer());
            });
      });
    }

    stream->wait();
    AC_DEVICE_FLOAT2(*stream, "post_scalar_sum", data, size1*size2*size3);
  }
}

void gather_force(
    const sycl::float4 *atoms, const int numAtoms,
    // const float recip11, const float recip22, const float recip33,
    const int nfftx, const int nffty, const int nfftz, const int xsize,
    const int ysize, const int zsize, const int xdim, const int y00,
    const int z00, const bool periodicY, const bool periodicZ,
    const float *data, const int order, sycl::float3 *force,
    const dpct::image_wrapper_base_p gridTexObj,
    sycl::queue *stream) {

  sycl::range<3> nthread(1, 2, 32);
  sycl::range<3> nblock(1, 1, (numAtoms - 1) / nthread[2] + 1);
  // dim3 nblock(npatch, 1, 1);

  AC_TAG("gather_force");
  sycl::float4* f4atoms = (sycl::float4*)atoms;
  float* fdata = (float*)data;
  sycl::float3* f3force = (sycl::float3*)force;
  AC_DEVICE_FLOAT4(*stream, "pre_gather_force", f4atoms, numAtoms);
  AC_DEVICE(*stream, "pre_gather_force", fdata, xsize*ysize*zsize);
  AC_DEVICE_FLOAT3(*stream, "pre_gather_force", f3force, numAtoms);

  switch(order) {
    case 4:
    if (periodicY && periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 4>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        /* TODO: Use texture memory (same for all other kernel calls)
        auto gridTexObj_acc = static_cast<dpct::image_wrapper<
            dpct_placeholder, 1> *>(gridTexObj)->get_access(cgh);
        auto gridTexObj_smpl = gridTexObj->get_sampler();
        */

        cgh.parallel_for<class gather_force_order4_periodicYZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 4, true, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  //dpct::image_accessor_ext<dpct_placeholder, 1>(gridTexObj_smpl, gridTexObj_acc),
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else if (periodicY)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 4>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order4_periodicY_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 4, true, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else if (periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 4>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order4_periodicZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 4, false, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 4>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order4_other_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 4, false, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    break;

    case 6:
    if (periodicY && periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 6>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order6_periodicYZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 6, true, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else if (periodicY)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 6>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order6_periodicY_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 6, true, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else if (periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 6>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order6_periodicZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 6, false, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 6>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order6_other_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 6, false, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    break;
 
    case 8:
    if (periodicY && periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 8>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order8_periodicYZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 8, true, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else if (periodicY)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 8>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order8_periodicY_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 8, true, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else if (periodicZ)
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 8>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order8_periodicZ_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 8, false, true>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    else
      stream->submit([&](sycl::handler &cgh) {
        sycl::accessor<gather_t<float, 8>, 1, sycl::access::mode::read_write,
                       sycl::access::target::local>
            shmem_acc_ct1(sycl::range<1>(32), cgh);

        cgh.parallel_for<class gather_force_order8_other_name>(
            sycl::nd_range<3>(nblock * nthread, nthread),
            [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
              gather_force<float, sycl::float3, 8, false, false>(
                  atoms, numAtoms, nfftx, nffty, nfftz, xsize, ysize, zsize,
                  xdim, y00, z00, data,
                  1, force, item_ct1, shmem_acc_ct1.get_pointer());
            });
      });
    break;

    default:
    char str[128];
    sprintf(str, "gather_force, order %d not implemented",order);
    dpcppNAMD_bug(str);
  }

  stream->wait();
  AC_DEVICE_FLOAT4(*stream, "post_gather_force", f4atoms, numAtoms);
  AC_DEVICE(*stream, "post_gather_force", fdata, xsize*ysize*zsize);
  AC_DEVICE_FLOAT3(*stream, "post_gather_force", f3force, numAtoms);
}

//
// Transpose
//
void transpose_xyz_yzx(const int nx, const int ny, const int nz,
                       const int xsize_in, const int ysize_in,
                       const int ysize_out, const int zsize_out,
                       const sycl::float2 *data_in, sycl::float2 *data_out,
                       sycl::queue *stream) {

  sycl::range<3> numthread(1, TILEROWS, TILEDIM);
  sycl::range<3> numblock(nz, (ny - 1) / TILEDIM + 1, (nx - 1) / TILEDIM + 1);

  stream->submit([&](sycl::handler &cgh) {
    sycl::range<2> tile_range_ct1(32 /*TILEDIM*/, 33 /*TILEDIM+1*/);

    sycl::accessor<sycl::float2, 2, sycl::access::mode::read_write,
                   sycl::access::target::local>
        tile_acc_ct1(tile_range_ct1, cgh);

    cgh.parallel_for<class transpose_xyz_yzx_name>(sycl::nd_range<3>(numblock * numthread, numthread),
                     [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
                       transpose_xyz_yzx_kernel<sycl::float2>(
                           nx, ny, nz, xsize_in, ysize_in, ysize_out, zsize_out,
                           data_in, data_out, item_ct1,
                           dpct::accessor<sycl::float2, dpct::local, 2>(
                               tile_acc_ct1, tile_range_ct1));
                     });
  });

}

//
// Batched transpose
//
void batchTranspose_xyz_yzx(
    const int numBatches, TransposeBatch<sycl::float2> *batches,
    const int max_nx, const int ny, const int nz,
    const int xsize_in, const int ysize_in, sycl::queue *stream) {

  sycl::range<3> numthread(1, TILEROWS, TILEDIM);
  sycl::range<3> numblock(nz * numBatches, (ny - 1) / TILEDIM + 1,
                          (max_nx - 1) / TILEDIM + 1);

  AC_TAG("batchTranspose_xyz_yzx");
  for (int i = 0; i < numBatches; i++) {
    AC_DEVICE_FLOAT2(*stream, std::string("pre_batchTranspose_xyz_yzx_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_in, max_nx*ny*nz);
    AC_DEVICE_FLOAT2(*stream, std::string("pre_batchTranspose_xyz_yzx_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_out, max_nx*ny*nz);
  }

  stream->submit([&](sycl::handler &cgh) {
    sycl::range<2> tile_range_ct1(32 /*TILEDIM*/, 33 /*TILEDIM+1*/);

    sycl::accessor<sycl::float2, 2, sycl::access::mode::read_write,
                   sycl::access::target::local>
        tile_acc_ct1(tile_range_ct1, cgh);

    cgh.parallel_for<class batchTranpose_xyz_yzx_name>(sycl::nd_range<3>(numblock * numthread, numthread),
                     [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
                       batchTranspose_xyz_yzx_kernel<sycl::float2>(
                           batches, ny, nz, xsize_in, ysize_in, item_ct1,
                           dpct::accessor<sycl::float2, dpct::local, 2>(
                               tile_acc_ct1, tile_range_ct1));
                     });
  });

  stream->wait();
  for (int i = 0; i < numBatches; i++) {
    AC_DEVICE_FLOAT2(*stream, std::string("post_batchTranspose_xyz_yzx_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_in, max_nx*ny*nz);
    AC_DEVICE_FLOAT2(*stream, std::string("post_batchTranspose_xyz_yzx_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_out, max_nx*ny*nz);
  }
}

//
// Transpose
//
void transpose_xyz_zxy(const int nx, const int ny, const int nz,
                       const int xsize_in, const int ysize_in,
                       const int zsize_out, const int xsize_out,
                       const sycl::float2 *data_in, sycl::float2 *data_out,
                       sycl::queue *stream) {

  sycl::range<3> numthread(1, TILEROWS, TILEDIM);
  sycl::range<3> numblock(ny, (nz - 1) / TILEDIM + 1, (nx - 1) / TILEDIM + 1);

  stream->submit([&](sycl::handler &cgh) {
    sycl::range<2> tile_range_ct1(32 /*TILEDIM*/, 33 /*TILEDIM+1*/);

    sycl::accessor<sycl::float2, 2, sycl::access::mode::read_write,
                   sycl::access::target::local>
        tile_acc_ct1(tile_range_ct1, cgh);

    cgh.parallel_for<class transpose_xyz_zxy_name>(sycl::nd_range<3>(numblock * numthread, numthread),
                     [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
                       transpose_xyz_zxy_kernel<sycl::float2>(
                           nx, ny, nz, xsize_in, ysize_in, zsize_out, xsize_out,
                           data_in, data_out, item_ct1,
                           dpct::accessor<sycl::float2, dpct::local, 2>(
                               tile_acc_ct1, tile_range_ct1));
                     });
  });

}

//
// Batched transpose
//
void batchTranspose_xyz_zxy(
    const int numBatches, TransposeBatch<sycl::float2> *batches,
    const int max_nx, const int ny, const int nz, const int xsize_in,
    const int ysize_in,
    sycl::queue *stream) {

  sycl::range<3> numthread(1, TILEROWS, TILEDIM);
  sycl::range<3> numblock(ny * numBatches, (nz - 1) / TILEDIM + 1,
                          (max_nx - 1) / TILEDIM + 1);

  AC_TAG("batchTranspose_xyz_zxy");
  for (int i = 0; i < numBatches; i++) {
    AC_DEVICE_FLOAT2(*stream, std::string("pre_batchTranspose_xyz_zxy_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_in, max_nx*ny*nz);
    AC_DEVICE_FLOAT2(*stream, std::string("pre_batchTranspose_xyz_zxy_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_out, max_nx*ny*nz);
  }

  stream->submit([&](sycl::handler &cgh) {
    sycl::range<2> tile_range_ct1(32 /*TILEDIM*/, 33 /*TILEDIM+1*/);

    sycl::accessor<sycl::float2, 2, sycl::access::mode::read_write,
                   sycl::access::target::local>
        tile_acc_ct1(tile_range_ct1, cgh);

    cgh.parallel_for<class batchTranspose_xyz_zxy_name>(sycl::nd_range<3>(numblock * numthread, numthread),
                     [=](sycl::nd_item<3> item_ct1) [[intel::reqd_sub_group_size(SUB_GROUP_SIZE)]] {
                       batchTranspose_xyz_zxy_kernel<sycl::float2>(
                           batches, ny, nz, xsize_in, ysize_in, item_ct1,
                           dpct::accessor<sycl::float2, dpct::local, 2>(
                               tile_acc_ct1, tile_range_ct1));
                     });
  });

  stream->wait();
  for (int i = 0; i < numBatches; i++) {
    AC_DEVICE_FLOAT2(*stream, std::string("post_batchTranspose_xyz_zxy_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_in, max_nx*ny*nz);
    AC_DEVICE_FLOAT2(*stream, std::string("post_batchTranspose_xyz_zxy_batch_") + std::to_string(i), (sycl::float2*)batches[i].data_out, max_nx*ny*nz);
  }
}

#endif // NAMD_DPCPP
