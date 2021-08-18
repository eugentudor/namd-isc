#ifndef DPCPPPMESOLVERUTILKERNEL_H
#define DPCPPPMESOLVERUTILKERNEL_H

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>

void spread_charge(
    const sycl::float4 *atoms, const int numAtoms, const int nfftx,
    const int nffty, const int nfftz, const int xsize, const int ysize,
    const int zsize, const int xdim, const int y00, const int z00,
    const bool periodicY, const bool periodicZ,
    float *data, const int order, sycl::queue *stream);

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
                // const int cuda_arch,
                sycl::queue *stream);

void gather_force(
    const sycl::float4 *atoms, const int numAtoms,
    // const float recip11, const float recip22, const float recip33,
    const int nfftx, const int nffty, const int nfftz, const int xsize,
    const int ysize, const int zsize, const int xdim, const int y00,
    const int z00, const bool periodicY, const bool periodicZ,
    const float *data, const int order, sycl::float3 *force,
    const dpct::image_wrapper_base_p gridTexObj,
    sycl::queue *stream);

// void calc_sum_charge_squared(const float4 *atoms, const int numAtoms, double* sum_charge_squared,
//   cudaStream_t stream);

template <typename T>
struct TransposeBatch {
  T* data_in;
  T* data_out;
  int nx;
  int zsize_out;
  int xsize_out;
  int ysize_out;
};

void transpose_xyz_yzx(const int nx, const int ny, const int nz,
                       const int xsize_in, const int ysize_in,
                       const int ysize_out, const int zsize_out,
                       const sycl::float2 *data_in, sycl::float2 *data_out,
                       sycl::queue *stream);

void batchTranspose_xyz_yzx(
    const int numBatches, TransposeBatch<sycl::float2> *batches,
    const int max_nx, const int ny, const int nz,
    const int xsize_in, const int ysize_in, sycl::queue *stream);

void transpose_xyz_zxy(const int nx, const int ny, const int nz,
                       const int xsize_in, const int ysize_in,
                       const int zsize_out, const int xsize_out,
                       const sycl::float2 *data_in, sycl::float2 *data_out,
                       sycl::queue *stream);

void batchTranspose_xyz_zxy(
    const int numBatches, TransposeBatch<sycl::float2> *batches,
    const int max_nx, const int ny, const int nz,
    const int xsize_in, const int ysize_in,
    sycl::queue *stream);

#endif // NAMD_DPCPP

#endif // DPCPPPMESOLVERUTILKERNEL_H
