
#include <stdio.h>
#include "common.h"
#include <fstream>
#include <limits>
#include "charm++.h"
#include "DpcppUtils.h"

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>

using namespace sycl;

#ifdef WIN32
#define __thread __declspec(thread)
#endif

void dpcppDie(const char *msg, int err) {
  char host[128];
  gethostname(host, 128);  host[127] = 0;
  char devstr[128] = "";
  int devnum;
  char errmsg[1024];
  if (err == 0) {
    sprintf(errmsg,"DPC++ error %s on Pe %d (%s%s)", msg, CkMyPe(), host, devstr);
  } else {
    sprintf(errmsg,"DPC++ error %s on Pe %d (%s%s): %s", msg, CkMyPe(), host, devstr, "dpcppGetErrorString not supported"/*dpcppGetErrorString(err)*/);    
  }
  NAMD_die(errmsg);
}

void dpcppNAMD_bug(const char *msg) {NAMD_bug(msg);}

void dpcpp_affinity_initialize() {
  // TODO: check whether this is relevant for DPC++
  // TODO: check whether DPC++ needs to initialize single offload device
}

//----------------------------------------------------------------------------------------

void clear_device_array_async_T(void *data, const int ndata, queue &myQ, const size_t sizeofT) {
  myQ.memset((void*)(data), 0, sizeofT*ndata);
}

void clear_device_array_T(void *data, const int ndata, const size_t sizeofT) {
  getDefaultQ().memset((void*)(data), 0, sizeofT*ndata).wait();
}

//----------------------------------------------------------------------------------------
//
// Allocate page-locked host memory
// pp = memory pointer
// len = length of the array
//
void allocate_host_T(void **pp, const int len, const size_t sizeofT) {
  *((void **)pp) = malloc_host(sizeofT*len, getDefaultQ());
}

//----------------------------------------------------------------------------------------
//
// Allocate gpu memory
// pp = memory pointer
// len = length of the array
//
void allocate_device_T(void **pp, const int len, const size_t sizeofT) {
  *((void **)pp) = malloc_device(sizeofT*len, getDefaultQ());
}

//----------------------------------------------------------------------------------------
//
// Deallocate gpu memory
// pp = memory pointer
//
void deallocate_device_T(void **pp) {
  
  if (*pp != NULL) {
    free((void *)(*pp), getDefaultQ());
    *pp = NULL;
  }

}

//----------------------------------------------------------------------------------------
//
// Deallocate page-locked host memory
// pp = memory pointer
//
void deallocate_host_T(void **pp) {
  
  if (*pp != NULL) {
    free((void *)(*pp), getDefaultQ());
    *pp = NULL;
  }

}

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
bool reallocate_device_T(void **pp, int *curlen, const int newlen, const float fac, const size_t sizeofT) {
  if (*pp != NULL && *curlen < newlen) {
    free((void *)(*pp), getDefaultQ());
    *pp = NULL;
  }

  if (*pp == NULL) {
    if (fac > 1.0f) {
      *curlen = (int)(((double)(newlen))*(double)fac);
    } else {
      *curlen = newlen;
    }
    *((void **)pp) = malloc_device(sizeofT*(*curlen), getDefaultQ());
    return true;
  }

  return false;
}

//----------------------------------------------------------------------------------------
//
// Allocate & re-allocate page-locked host memory
// pp = memory pointer
// curlen = current length of the array
// newlen = new required length of the array
// fac = extra space allocation factor: in case of re-allocation new length will be fac*newlen
// returns true if reallocation happened
//
bool reallocate_host_T(void **pp, int *curlen, const int newlen, 
		       const float fac, const size_t sizeofT) {

  if (*pp != NULL && *curlen < newlen) {
    free((void *)(*pp), getDefaultQ());
    *pp = NULL;
  }

  if (*pp == NULL) {
    if (fac > 1.0f) {
      *curlen = (int)(((double)(newlen))*(double)fac);
    } else {
      *curlen = newlen;
    }
    *((void **)pp) = malloc_host(sizeofT*(*curlen), getDefaultQ());
    return true;
  }

  return false;
}

//----------------------------------------------------------------------------------------
//
// Copies memory Host -> Device
//
void copy_HtoD_async_T(const void *h_array, void *d_array, int array_len, queue &myQ,
           const size_t sizeofT) {
  myQ.memcpy((void*)(d_array), (void*)(h_array), sizeofT*array_len);
}

void copy_HtoD_T(const void *h_array, void *d_array, int array_len,
     const size_t sizeofT) {
  getDefaultQ().memcpy((void*)(d_array), (void*)(h_array), sizeofT*array_len).wait();
}

//----------------------------------------------------------------------------------------
//
// Copies memory Device -> Host
//
void copy_DtoH_async_T(const void *d_array, void *h_array, const int array_len, queue &myQ,
           const size_t sizeofT) {
  myQ.memcpy((void*)(h_array), (void*)(d_array), sizeofT*array_len);
}

void copy_DtoH_T(const void *d_array, void *h_array, const int array_len, const size_t sizeofT) {
  getDefaultQ().memcpy((void*)(h_array), (void*)(d_array), sizeofT*array_len).wait();
}

//----------------------------------------------------------------------------------------
//
// Copies memory Device -> Device
//
void copy_DtoD_async_T(const void *d_src, void *d_dst, const int array_len, queue &myQ,
           const size_t sizeofT) {
  myQ.memcpy((void*)(d_dst), (void*)(d_src), sizeofT*array_len);
}

void copy_DtoD_T(const void *d_src, void *d_dst, const int array_len, const size_t sizeofT) {
  getDefaultQ().memcpy((void*)(d_dst), (void*)(d_src), sizeofT*array_len).wait();
}


// TODO: Enable the following functionds as needed
//----------------------------------------------------------------------------------------
//
// Copies memory between two devices Device -> Device
//
void copy_PeerDtoD_async_T(const int src_dev, const int dst_dev,
  const void *d_src, void *d_dst, const int array_len, queue myQ,
  const size_t sizeofT)
{ //TODO
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
  size_t sizeofT, queue myQ) 
{ //TODO
}


//----------------------------------------------------------------------------------------
//
// Copies 3D memory block Device -> Host
////
//void copy3D_DtoH_T(void* src_data, void* dst_data,
//  int src_x0, int src_y0, int src_z0,
//  size_t src_xsize, size_t src_ysize,
//  int dst_x0, int dst_y0, int dst_z0,
//  size_t dst_xsize, size_t dst_ysize,
//  size_t width, size_t height, size_t depth,
//  size_t sizeofT, queue myQ) 
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
  size_t sizeofT, queue myQ)
{ //TODO
}

//----------------------------------------------------------------------------------------
//
// Copies 3D memory block between devices Device -> Device
//
//void copy3D_PeerDtoD_T(int src_dev, int dst_dev,
//  void* src_data, void* dst_data,
//  int src_x0, int src_y0, int src_z0,
//  size_t src_xsize, size_t src_ysize,
//  int dst_x0, int dst_y0, int dst_z0,
//  size_t dst_xsize, size_t dst_ysize,
//  size_t width, size_t height, size_t depth,
//  size_t sizeofT, queue myQ) {
#endif // NAMD_DPCPP
