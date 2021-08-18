#ifndef DPCPPUTILS_H
#define DPCPPUTILS_H

#include <stdio.h>
#include "DpcppDevice.h"
#include "NamdTypes.h"


#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>

#include "array_debug_dpcpp_util.h"

#define AVXSIZE 16

#ifdef __SYCL_DEVICE_ONLY__
  #define CL_CONSTANT __attribute__((opencl_constant))
#else
  #define CL_CONSTANT
#endif

#define PRINTF(format, ...) { \
                            static const CL_CONSTANT char _format[] = format; \
                            sycl::ONEAPI::experimental::printf(_format, ## __VA_ARGS__); \
                            }


#define ATOMIC_ADD(T, data, val)  (sycl::ONEAPI::atomic_ref< T, sycl::ONEAPI::memory_order::relaxed, sycl::ONEAPI::memory_scope::device, sycl::access::address_space::global_space>((data)) += (val));

//template <class T> 
//NAMD_INLINE void atomicAddNAMD(T* data, T val) {sycl::ONEAPI::atomic_ref< T, sycl::ONEAPI::memory_order::relaxed, sycl::ONEAPI::memory_scope::device, sycl::access::address_space::global_space>(data) += val;}

#define ATOMIC_FETCH_ADD(T, data, val)  sycl::ONEAPI::atomic_ref< T, sycl::ONEAPI::memory_order::relaxed, sycl::ONEAPI::memory_scope::device, sycl::access::address_space::global_space>(data).fetch_add(val);

#define ATOMIC_EXCHANGE(T, data, expected, desired)  sycl::ONEAPI::atomic_ref< T, sycl::ONEAPI::memory_order::relaxed, sycl::ONEAPI::memory_scope::device, sycl::access::address_space::global_space>(data).compare_exchange_weak(expected, desired)

#define ATOMIC_ADD_FLOAT(o, v) ATOMIC_ADD(float, o, v)
//#ifdef __SYCL_DEVICE_ONLY__
//SYCL_EXTERNAL float atomic_fetch_add(volatile __attribute__((opencl_global)) _Atomic float *p, float val);
//#define ATOMIC_ADD_FLOAT(o, v) \
//  atomic_fetch_add((volatile __attribute__((opencl_global)) _Atomic float *)(&o), v)
//#else
//inline float atomic_fetch_add(volatile _Atomic float *p, float val) { return val; };
//#define ATOMIC_ADD_FLOAT(o, v) ATOMIC_ADD(float, o, v)
//#endif

template <typename T>
NAMD_INLINE T warp_shuffle(const sycl::ONEAPI::sub_group& sg, unsigned long mask,
                                  T var, int srcLane, int width) {
  int partition_id = sg.get_local_id() / width;
  int id = sg.get_local_id();
  srcLane = (mask & (0x1 << id)) ? (srcLane % width) : (id % width);
  srcLane += partition_id * width;
  return sg.shuffle(var, srcLane);
}
NAMD_INLINE unsigned long warp_ballot(const sycl::ONEAPI::sub_group& sg, int pred) {
  unsigned long vote = (pred != 0) ? 0x1 << (int)sg.get_local_id() : 0;
  return sycl::ONEAPI::reduce(sg, vote, sycl::ONEAPI::plus<>());
}

#define WARP_SHUFFLE_MASK(SG, MASK, VAR, LANE, WIDTH) \
  warp_shuffle(SG, MASK, VAR, LANE, WIDTH)
#define WARP_BALLOT(SG, P)       warp_ballot(SG, P)


NAMD_INLINE sycl::float4 linear_interp_cudata_float4(const sycl::float4 *__restrict__ mytable, const float rinv, const int tsize)
{
    const float table_rinv = rinv > 1.f ? 1.f : rinv;
    const float table_f = tsize * table_rinv;
    const int table_i = (int) table_f;
    const float table_diff = table_f - table_i;

    return mytable[table_i] + (mytable[table_i + 1] - mytable[table_i]) * table_diff;
}

void dpcppDie(const char *msg, int err=0);

void dpcppNAMD_bug(const char *msg);

void clear_device_array_async_T(void *data, const int ndata, sycl::queue &myQ, const size_t sizeofT);
void clear_device_array_T(void *data, const int ndata, const size_t sizeofT);

template <class T>
void clear_device_array(T *data, const int ndata, sycl::queue &myQ) {
  clear_device_array_async_T(data, ndata, myQ, sizeof(T));
}

template <class T>
void clear_device_array_sync(T *data, const int ndata) {
  clear_device_array_T(data, ndata, sizeof(T));
}

void allocate_host_T(void **pp, const int len, const size_t sizeofT);
//----------------------------------------------------------------------------------------
//
// Allocate page-locked host memory
// pp = memory pointer
// len = length of the array
//
template <class T>
void allocate_host(T **pp, const int len) {
  allocate_host_T((void **)pp, len, sizeof(T));
}


void allocate_device_T(void **pp, const int len, const size_t sizeofT);
//----------------------------------------------------------------------------------------
//
// Allocate gpu memory
// pp = memory pointer
// len = length of the array
//
template <class T>
void allocate_device(T **pp, const int len) {
  allocate_device_T((void **)pp, len, sizeof(T));
}


void deallocate_device_T(void **pp);
//----------------------------------------------------------------------------------------
//
// Deallocate gpu memory
// pp = memory pointer
//
template <class T>
void deallocate_device(T **pp) {
  deallocate_device_T((void **)pp);
}
//----------------------------------------------------------------------------------------

bool reallocate_device_T(void **pp, int *curlen, const int newlen, const float fac, const size_t sizeofT);
//----------------------------------------------------------------------------------------
//
// Allocate & re-allocate device memory
// pp = memory pointer
// curlen = current length of the array
// newlen = new required length of the array
// fac = extra space allocation factor: in case of re-allocation new length will be fac*newlen
//
// returns true if reallocation happened
//
template <class T>
bool reallocate_device(T **pp, int *curlen, const int newlen, const float fac=1.0f) {
  return reallocate_device_T((void **)pp, curlen, newlen, fac, sizeof(T));
}
//----------------------------------------------------------------------------------------
bool reallocate_host_T(void **pp, int *curlen, const int newlen, const float fac, 
		       const size_t sizeofT);
//----------------------------------------------------------------------------------------
//
// Allocate & re-allocate pinned host memory
// pp = memory pointer
// curlen = current length of the array
// newlen = new required length of the array
// fac = extra space allocation factor: in case of re-allocation new length will be fac*newlen
// flag = allocation type:
//        dpcppHostAllocDefault = default type, emulates dpcppMallocHost
//        dpcppHostAllocMapped  = maps allocation into DPC++ address space
//
// returns true if reallocation happened
//
template <class T>
bool reallocate_host(T **pp, int *curlen, const int newlen,
		     const float fac=1.0f) {
  return reallocate_host_T((void **)pp, curlen, newlen, fac, sizeof(T));
}

void deallocate_host_T(void **pp);
//----------------------------------------------------------------------------------------
//
// Deallocate page-locked host memory
// pp = memory pointer
//
template <class T>
void deallocate_host(T **pp) {
  deallocate_host_T((void **)pp);
}
//----------------------------------------------------------------------------------------

void copy_HtoD_async_T(const void *h_array, void *d_array, int array_len, sycl::queue &myQ,
           const size_t sizeofT);
void copy_HtoD_T(const void *h_array, void *d_array, int array_len,
     const size_t sizeofT);
void copy_DtoH_async_T(const void *d_array, void *h_array, const int array_len, sycl::queue &myQ,
           const size_t sizeofT);
void copy_DtoH_T(const void *d_array, void *h_array, const int array_len, const size_t sizeofT);

void copy_DtoD_async_T(const void *d_src, void *d_dst, const int array_len, sycl::queue &myQ,
           const size_t sizeofT);
void copy_DtoD_T(const void *d_src, void *d_dst, const int array_len, const size_t sizeofT);

//----------------------------------------------------------------------------------------
//
// Copies memory Host -> Device
//
template <class T>
void copy_HtoD(const T *h_array, T *d_array, int array_len, sycl::queue &myQ) {
  copy_HtoD_async_T(h_array, d_array, array_len, myQ, sizeof(T));
}

//----------------------------------------------------------------------------------------
//
// Copies memory Host -> Device using synchronous calls
//
template <class T>
void copy_HtoD_sync(const T *h_array, T *d_array, int array_len) {
  copy_HtoD_T(h_array, d_array, array_len, sizeof(T));
}

//----------------------------------------------------------------------------------------
//
// Copies memory Device -> Host
//
template <class T>
void copy_DtoH(const T *d_array, T *h_array, const int array_len, sycl::queue &myQ) {
  copy_DtoH_async_T(d_array, h_array, array_len, myQ, sizeof(T));
}
//----------------------------------------------------------------------------------------
//
// Copies memory Device -> Host using synchronous calls
//
template <class T>
void copy_DtoH_sync(const T *d_array, T *h_array, const int array_len) {
  copy_DtoH_T(d_array, h_array, array_len, sizeof(T));
}
//----------------------------------------------------------------------------------------
//
// Copies memory Device -> Device
//
template <class T>
void copy_DtoD(const T *d_src, T *h_dst, const int array_len, sycl::queue &myQ) {
  copy_DtoD_async_T(d_src, h_dst, array_len, myQ, sizeof(T));
}
//----------------------------------------------------------------------------------------
//
// Copies memory Device -> Device using synchronous calls
//
template <class T>
void copy_DtoD_sync(const T *d_src, T *h_dst, const int array_len) {
  copy_DtoD_T(d_src, h_dst, array_len, sizeof(T));
}

//----------------------------------------------------------------------------------------
//
// Copies memory between two peer devices Device -> Device
//
void copy_PeerDtoD_async_T(const int src_dev, const int dst_dev,
  const void *d_src, void *d_dst, const int array_len, sycl::queue &myQ,
  const size_t sizeofT);

template <class T>
void copy_PeerDtoD(const int src_dev, const int dst_dev,
  const T *d_src, T *d_dst, const int array_len, sycl::queue &myQ) {
  copy_PeerDtoD_async_T(src_dev, dst_dev, d_src, d_dst, array_len, myQ, sizeof(T));
}

//----------------------------------------------------------------------------------------
//
// Copies 3D memory block Host -> Device
//
void copy3D_HtoD_T(void* src_data, void* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  size_t sizeofT, sycl::queue &myQ);

template <class T>
void copy3D_HtoD(T* src_data, T* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  sycl::queue &myQ) {
  copy3D_HtoD_T(src_data, dst_data,
    src_x0, src_y0, src_z0,
    src_xsize, src_ysize,
    dst_x0, dst_y0, dst_z0,
    dst_xsize, dst_ysize,
    width, height, depth,
    sizeof(T), myQ);
}

//----------------------------------------------------------------------------------------
//
// Copies 3D memory block Device -> Host
//
void copy3D_DtoH_T(void* src_data, void* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  size_t sizeofT, sycl::queue &myQ);

template <class T>
void copy3D_DtoH(T* src_data, T* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  sycl::queue &myQ) {
  copy3D_DtoH_T(src_data, dst_data,
    src_x0, src_y0, src_z0,
    src_xsize, src_ysize,
    dst_x0, dst_y0, dst_z0,
    dst_xsize, dst_ysize,
    width, height, depth,
    sizeof(T), myQ);
}

//----------------------------------------------------------------------------------------
//
// Copies 3D memory block Device -> Device
//
void copy3D_DtoD_T(void* src_data, void* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  size_t sizeofT, sycl::queue &myQ);

template <class T>
void copy3D_DtoD(T* src_data, T* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  sycl::queue &myQ) {
  copy3D_DtoD_T(src_data, dst_data,
    src_x0, src_y0, src_z0,
    src_xsize, src_ysize,
    dst_x0, dst_y0, dst_z0,
    dst_xsize, dst_ysize,
    width, height, depth,
    sizeof(T), myQ);
}

//----------------------------------------------------------------------------------------
//
// Copies 3D memory block between two peer devices Device -> Device
//
void copy3D_PeerDtoD_T(int src_dev, int dst_dev,
  void* src_data, void* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  size_t sizeofT, sycl::queue &myQ);

template <class T>
void copy3D_PeerDtoD(int src_dev, int dst_dev,
  T* src_data, T* dst_data,
  int src_x0, int src_y0, int src_z0,
  size_t src_xsize, size_t src_ysize,
  int dst_x0, int dst_y0, int dst_z0,
  size_t dst_xsize, size_t dst_ysize,
  size_t width, size_t height, size_t depth,
  sycl::queue &myQ) {
  copy3D_PeerDtoD_T(src_dev, dst_dev,
    src_data, dst_data,
    src_x0, src_y0, src_z0,
    src_xsize, src_ysize,
    dst_x0, dst_y0, dst_z0,
    dst_xsize, dst_ysize,
    width, height, depth,
    sizeof(T), myQ);
}
#endif // NAMD_DPCPP

#endif // DPCPPUTILS_H
