/******************************************************************************
*
* Copyright 2020 Intel Corporation.
*
* This software and the related documents are Intel copyrighted materials,
* and your use of them is governed by the express license under which they
* were provided to you ("License"). Unless the License provides otherwise,
* you may not use, modify, copy, publish, distribute, disclose or transmit
* this software or the related documents without Intel's prior written
* permission.

* This software and the related documents are provided as is, with no express
* or implied warranties, other than those that are expressly stated in the
* License.
*****************************************************************************/

#ifndef ARRAY_COMPARE_UTIL_H
#define  ARRAY_COMPARE_UTIL_H

#include <numeric>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <CL/sycl.hpp>

#ifndef AC_ROOT_DIR 
//#define AC_ROOT_DIR ("log/")
//#define AC_ROOT_DIR ("/localdisk/work/tmalas/dump_namd/")
#define AC_ROOT_DIR ("/nfs/pdx/home/tmalas/dump_namd/tiny/")
#endif

#define LOG_LIMITS (100)

//#define AC_COMP
//#define AC_LOG
//#define AC_TAGS

#if defined(AC_LOG) || defined(AC_COMP)
namespace {
template <typename T>
void compareHostArray(T * data,  size_t len, std::string path, std::string name, int structLen=1, bool fullPrint=false){
//  if(fullPrint)
    std::cout << "Comparing: "<< name << std::endl;
  if(len%structLen != 0) {
    std::cout << "ERROR: provided buffer size not modulus  struct size\n";
    return;
  }
  // Get reference file size
  auto fullPath = path +"/" + name;
  std::ifstream refFile(fullPath,std::ios::in|std::ios::binary);
  refFile.ignore( std::numeric_limits<std::streamsize>::max() );
  size_t ref_size = refFile.gcount();
  if(ref_size == 0) {
    std::cout << "ERROR: Reference file does not exist or empty\n" << fullPath << std::endl;
    return;
  }
  if(len==0) {
    std::cout << "Comparing: "<< name << " - Not comparing, array size 0. Ref size:" << ref_size << std::endl;
    return;
  }
  std::vector<T> fileBuf;
  fileBuf.reserve(ref_size/sizeof(T));
  auto size = len*sizeof(T);
  if(size != ref_size) {
    std::cout << "WARNING: Reference file size does not match: ref="<< ref_size << " current=" << size<< " in:" << name << std::endl;
    len = std::min(size, ref_size)/sizeof(T);
  }
  // Read reference data 
  refFile.clear();
  refFile.seekg(0);
  refFile.read((char *)fileBuf.data(), ref_size);
  refFile.close();
  // Compare reference with current data
  std::vector<T> errBuf;
  std::vector<int> idxBuf;
  int limitCtr=0;
  for(int idx=0; idx<len; idx++){
    int i = idx/structLen;
    int j = idx%structLen;

    T err;
    if(std::is_same<float, T>::value || std::is_same<double, T>::value) {
      err = data[idx]? (data[idx]-fileBuf[idx])/data[idx]: fileBuf[idx];
      err = std::fabs(err);
    } else {
      err = data[idx]-fileBuf[idx];
      err = err>0? err: -err;
    }

    if (fullPrint){
      std::cout << "Diff at idx: " <<  i << ":" << j <<
                 " ref: " <<std::setw(14)<< fileBuf[idx] <<
                 " val: " <<std::setw(14) << data[idx] <<
                 " Relative Err: " <<std::setw(14) << err << std::endl;
    } else if (fileBuf[idx] != data[idx]) {
      if  (!(std::is_same<float, T>::value && err < 1e-4)
        && !(std::is_same<double, T>::value && err < 1e-4)) {
        errBuf.push_back(err);
        idxBuf.push_back(idx);
      }
    }
    if (limitCtr++ > LOG_LIMITS) break;
    /*
    if (!(std::is_same<float, T>::value || std::is_same<double, T>::value))
      std::cout << "Diff at idx: " <<  i << ":" << j <<
                 " ref: " <<std::setw(14)<< fileBuf[idx] <<
                 " val: " <<std::setw(14) << data[idx] <<
                 " Relative Err: " <<std::setw(14) << err << std::endl;
                 */
  }
  std::cout << errBuf.size() << " values different!" << std::endl;
  if(errBuf.size() > 0 && !fullPrint){
//    std::cout << "Comparing: "<< name << std::endl;
    std::vector<int> idxOrder(errBuf.size());
    std::iota(idxOrder.begin(),idxOrder.end(),0);
    if(std::is_same<float, T>::value || std::is_same<double, T>::value) {
      std::sort(idxOrder.begin(), idxOrder.end(), [&errBuf](int i1, int i2){return errBuf[i1] > errBuf[i2];});
    }
    int limitCtr2=0;
    for(auto &it: idxOrder){
      if(limitCtr2++ > LOG_LIMITS) break; 
      int idx = idxBuf[it];
      auto err = errBuf[it];
      int i = idx/structLen;
      int j = idx%structLen;
      std::cout << "Diff at idx: " <<  i << ":" << j <<
               " ref: " <<std::setw(14)<< fileBuf[idx] <<
               " val: " <<std::setw(14) << data[idx] <<
               " Relative Err: " << std::setw(14) << std::scientific << err << std::endl;
    }
  }

}

template <typename baseType, size_t structLen, typename containerType, typename Accessor>
void compareHostArray(containerType *containerBuf, size_t len, std::string path, std::string name, Accessor A){
  if(len==0) {
    std::cout << "Comparing: "<< name << " - Not comparing, array size 0" << std::endl;
    return;
  }
  size_t baseLen = structLen*len;
  std::vector<baseType> baseBuf;
  baseBuf.reserve(baseLen);
  for(int i=0; i<len; i++) A(containerBuf[i], baseBuf);
  compareHostArray(&baseBuf[0], baseBuf.size(), path, name, structLen);
}

template <typename T>
void compareDeviceArray(sycl::queue q, T * d_data,  size_t len, std::string path, std::string name){
  if(len==0) {
    std::cout << "Comparing: "<< name << " - Not comparing, array size 0" << std::endl;
    return;
  }
  T * hostBuf = new T[len];
  q.memcpy((void*)(hostBuf), (void*)(d_data), sizeof(T)*len).wait();
  compareHostArray(hostBuf, len, path, name);
  delete [] hostBuf;
}

template <typename baseType, size_t structLen, typename containerType, typename Accessor>
void compareDeviceArray(sycl::queue q, containerType *d_container, size_t len, std::string path, std::string name, Accessor A, bool fullPrint=false){
  if(len==0) {
    std::cout << "Comparing: "<< name << " - Not comparing, array size 0" << std::endl;
    return;
  }
  containerType * containerBuf = new containerType[len];
  q.memcpy((void*)(containerBuf), (void*)(d_container), sizeof(containerType)*len).wait();
  size_t baseLen = structLen*len;
  std::vector<baseType> baseBuf;
  baseBuf.reserve(baseLen);
  for(int i=0; i<len; i++) A(containerBuf[i], baseBuf);
  compareHostArray(&baseBuf[0], baseBuf.size(), path, name, structLen, fullPrint);
  delete [] containerBuf;
}


template <typename containerType>
void loadDeviceArray(sycl::queue q, containerType *d_container, size_t arraySize, std::string path, std::string name){
  int len = arraySize*sizeof(containerType);
  auto fullPath = path +"/" + name;
  std::ifstream refFile(fullPath,std::ios::in|std::ios::binary);
  refFile.ignore( std::numeric_limits<std::streamsize>::max() );
  size_t ref_size = refFile.gcount();
  if(ref_size == 0) {
    std::cout << "ERROR: Reference file does not exist or empty\n";
    return;
  }
  if(len==0) {
    std::cout << "Comparing: "<< name << " - Not comparing, array size 0. Ref size:" << ref_size << std::endl;
    return;
  }
  std::vector<char> fileBuf;
  fileBuf.reserve(ref_size);
  if(len != ref_size) {
    std::cout << "WARNING: Reference file size does not match: ref="<< ref_size << " current=" << len << " in:" << name << std::endl;
  }
  // Read reference data 
  refFile.clear();
  refFile.seekg(0);
  refFile.read((char *)fileBuf.data(), ref_size);
  refFile.close();
  q.memcpy((void*)(d_container), (void*)(fileBuf.data()), ref_size).wait();
  q.wait();
}

template <>
void loadDeviceArray<sycl::float3>(sycl::queue q, sycl::float3 *d_container, size_t arraySize, std::string path, std::string name){
  int len = arraySize*12; // XXX: instead of sizeof(sycl::float3) which is 16
  auto fullPath = path +"/" + name;
  std::ifstream refFile(fullPath,std::ios::in|std::ios::binary);
  refFile.ignore( std::numeric_limits<std::streamsize>::max() );
  size_t ref_size = refFile.gcount();
  if(ref_size == 0) {
    std::cout << "ERROR: Reference file does not exist or empty\n";
    return;
  }
  if(len==0) {
    std::cout << "Comparing: "<< name << " - Not comparing, array size 0. Ref size:" << ref_size << std::endl;
    return;
  }
  std::vector<char> fileBuf;
  fileBuf.reserve(ref_size);
  if(len != ref_size) {
    std::cout << "WARNING: Reference file size does not match: ref="<< ref_size << " current=" << len << " in:" << name << std::endl;
  }
  // Read reference data
  refFile.clear();
  refFile.seekg(0);
  refFile.read((char *)fileBuf.data(), ref_size);
  refFile.close();
  std::vector<float> fvec;
  fvec.reserve(arraySize*3);
  memcpy((void*)fvec.data(), (void*)fileBuf.data(), ref_size);
  std::vector<sycl::float3> h_container;
  h_container.reserve(arraySize);
  for (int i = 0; i < arraySize; i++) {
    h_container.push_back(sycl::float3(fvec[3*i], fvec[3*i+1], fvec[3*i+2]));
  }
  q.memcpy((void*)(d_container), (void*)(h_container.data()), arraySize * sizeof(sycl::float3)).wait();
  q.wait();
}


template <typename T>
void logHostArray(T * data,  size_t len, std::string path, std::string name){
  std::string fullPath = path +"/" + name;
  size_t size = len*sizeof(T);
  std::ofstream logFile(fullPath.c_str(), std::ofstream::binary);
  logFile.write((char *)data, size);
  logFile.close();
}
template <typename baseType, typename containerType, typename Accessor>
void logHostArray(containerType *containerBuf, size_t len, std::string path, std::string name, Accessor A){
  std::vector<baseType> baseBuf;
  for(int i=0; i<len; i++) A(containerBuf[i], baseBuf);
  logHostArray(&baseBuf[0], baseBuf.size(), path, name);
}


template <typename T>
void logDeviceArray(sycl::queue q, T * d_data,  size_t len, std::string path, std::string name){
  T * tmpBuf = new T[len];
  q.memcpy((void*)(tmpBuf), (void*)(d_data), sizeof(T)*len).wait();
  logHostArray(tmpBuf, len, path, name);
  free(tmpBuf);
}
template <typename baseType, typename containerType, typename Accessor>
void logDeviceArray(sycl::queue q, containerType *d_container, size_t len, std::string path, std::string name, Accessor A){
  containerType * containerBuf = new containerType[len];
  q.memcpy((void*)(containerBuf), (void*)(d_container), sizeof(containerType)*len).wait();
  std::vector<baseType> baseBuf;
  for(int i=0; i<len; i++) A(containerBuf[i], baseBuf);
  logHostArray(&baseBuf[0], baseBuf.size(), path, name);
  free(containerBuf);
}
} // namespace
#endif // defined(AC_LOG) || defined(AC_COMP)


#define AC_LOAD_DEVICE(q, tag, array, size) { \
    static int counter=0; \
    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
    loadDeviceArray(q, array, size, AC_ROOT_DIR, fname); }


#ifdef AC_COMP
#define AC_DEVICE(q, tag, array, size) { \
    static int counter=0; \
    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
    compareDeviceArray(q, array, size, AC_ROOT_DIR , fname); }

#define AC_DEVICE_STRUCT(q, tag, array, size, type, structSize, captureList) { \
    static int counter=0; \
    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
    compareDeviceArray<type, structSize>(q, array, size, AC_ROOT_DIR , fname, [](const auto st, auto &v) {captureList});  }


#elif defined(AC_LOG)
#define AC_DEVICE(q, tag, array, size) { \
    static int counter=0; \
    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
    logDeviceArray(q, array, size, AC_ROOT_DIR , fname);   }

#define AC_DEVICE_STRUCT(q, tag, array, size, type, structSize, captureList) { \
    static int counter=0; \
    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
    logDeviceArray<type>(q, array, size, AC_ROOT_DIR, fname, [](const auto st, auto &v) {captureList}); }


#else
#define AC_DEVICE(q, tag, array, size)
#define AC_DEVICE_STRUCT(q, tag, array, size, type, structSize, captureList)
#endif

#if defined(AC_LOG) || defined(AC_COMP)
#define AC_ADD(x) (v.push_back(st.x))
#define AC_ADDV4(var) {v.push_back(st.var.x()); v.push_back(st.var.y()); v.push_back(st.var.z()); v.push_back(st.var.w());}
#define AC_ADDV3(var) {v.push_back(st.var.x()); v.push_back(st.var.y()); v.push_back(st.var.z());}
#define AC_ADDV2(var) {v.push_back(st.var.x()); v.push_back(st.var.y());}
#define AC_TAG(tag)  {                                 \
  static int counter=0; \
  std::cout << "Call#: " << ++counter << " " << tag << std::endl;  }
#define AC_DEVICE_FLOAT4(q, tag, array, size) { \
  AC_DEVICE_STRUCT(q, tag, array, size, float, 4, AC_ADD(x());AC_ADD(y());AC_ADD(z());AC_ADD(w());); }
#define AC_DEVICE_FLOAT3(q, tag, array, size) { \
  AC_DEVICE_STRUCT(q, tag, array, size, float, 3, AC_ADD(x());AC_ADD(y());AC_ADD(z());); }
#define AC_DEVICE_FLOAT2(q, tag, array, size) { \
  AC_DEVICE_STRUCT(q, tag, array, size, float, 2, AC_ADD(x());AC_ADD(y());); }
#define AC_DEVICE_FLOAT2_FULLPRINT(q, tag, array, size) { \
  AC_DEVICE_STRUCT_FULLPRINT(q, tag, array, size, float, 2, AC_ADD(x());AC_ADD(y());); }
#define AC_DEVICE_INT2(q, tag, array, size) { \
  AC_DEVICE_STRUCT(q, tag, array, size, int, 2, AC_ADD(x());AC_ADD(y());); }

#else
#define AC_ADD(x)
#define AC_ADDV2(x)
#define AC_ADDV3(x)
#define AC_ADDV4(x)
#define AC_DEVICE_FLOAT4(q, tag, array, size)
#define AC_DEVICE_FLOAT3(q, tag, array, size)
#define AC_DEVICE_FLOAT2(q, tag, array, size)
#define AC_DEVICE_FLOAT2_FULLPRINT(q, tag, array, size)
#define AC_DEVICE_INT2(q, tag, array, size)
#define AC_TAG(tag)
#endif

#ifdef AC_TAGS
#ifdef AC_TAG
#undef AC_TAG
#endif
#define AC_TAG(tag)  {                                 \
  static int counter=0; \
  std::cout << "Call#: " << ++counter << " " << tag << std::endl;  }
#endif

//#ifdef AC_ENABLED
//#define AC_TAG(tag)  {                                 \
//  static int counter=0; \
//  std::cout << "Call#: " << ++counter << " " << tag << std::endl;  }
//
//#define AC_COMP_HOST(tag, array, size) { \
//    static int counter=0; \
//    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
//    compareHostArray(array, size, AC_ROOT_DIR , fname); }
//
//#define AC_COMP_HOST_STRUCT(tag, array, size, type, structSize, captureList) { \
//    static int counter=0; \
//    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
//    compareHostArray<type, structSize>(array, size, AC_ROOT_DIR , fname, [](const auto st, auto &v) {captureList}); }
//
//#define AC_COMP_DEVICE(q, tag, array, size) { \
//    static int counter=0; \
//    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
//    compareDeviceArray(q, array, size, AC_ROOT_DIR , fname); }
//
//#define AC_COMP_DEVICE_STRUCT(q, tag, array, size, type, structSize, captureList) { \
//    static int counter=0; \
//    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
//    compareDeviceArray<type, structSize>(q, array, size, AC_ROOT_DIR , fname, [](const auto st, auto &v) {captureList});  }
//
//#define AC_COMP_DEVICE_STRUCT_FULLPRINT(q, tag, array, size, type, structSize, captureList) { \
//    static int counter=0; \
//    std::string fname = (std::string)(tag)+"_"+#array+"_call_"+std::to_string(++counter)+".bin";  \
//    compareDeviceArray<type, structSize>(q, array, size, AC_ROOT_DIR , fname, [](const auto st, auto &v) {captureList}, true);  }
// 
//#define AC_COMP_DEVICE_FLOAT4(q, tag, array, size) { \
//  AC_COMP_DEVICE_STRUCT(q, tag, array, size, float, 4, AC_ADD(x());AC_ADD(y());AC_ADD(z());AC_ADD(w());); }
//#define AC_COMP_DEVICE_FLOAT2(q, tag, array, size) { \
//  AC_COMP_DEVICE_STRUCT(q, tag, array, size, float, 2, AC_ADD(x());AC_ADD(y());); }
//#define AC_COMP_DEVICE_FLOAT2_FULLPRINT(q, tag, array, size) { \
//  AC_COMP_DEVICE_STRUCT_FULLPRINT(q, tag, array, size, float, 2, AC_ADD(x());AC_ADD(y());); }
//#define AC_COMP_DEVICE_INT2(q, tag, array, size) { \
//  AC_COMP_DEVICE_STRUCT(q, tag, array, size, int, 2, AC_ADD(x());AC_ADD(y());); }
//
//
//#else
//#define AC_TAG(tag)
//#define AC_COMP_HOST(tag, array, size)
//#define AC_COMP_HOST_STRUCT(tag, array, size, type, structSize, captureList)
//#define AC_COMP_DEVICE(q, tag, array, size)
//#define AC_COMP_DEVICE_STRUCT(q, tag, array, size, type, structSize, captureList)
//#define AC_COMP_DEVICE_FLOAT4(q, tag, array, size)
//#define AC_COMP_DEVICE_FLOAT2(q, tag, array, size)
//#define AC_COMP_DEVICE_INT2(q, tag, array, size)
//
//#endif


#endif //ARRAY_COMPARE_UTIL_H
