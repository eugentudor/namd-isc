#ifndef DPCPPCOMPUTENONBONDEDKERNEL_H
#define DPCPPCOMPUTENONBONDEDKERNEL_H
#include "DpcppUtils.h"
#include "DpcppTileListKernel.h"
#include "DpcppNonbondedTables.h"

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>

#define MAX_CONST_EXCLUSIONS 2048  // cache size is 8k

class DpcppComputeNonbondedKernel {

using float3 = sycl::float3;
using queue = sycl::queue;
using int2 = sycl::int2;
using float4 = sycl::float4;
//using = sycl::;

private:

  const int deviceID;
  DpcppNonbondedTables& dpcppNonbondedTables;
  const bool doStreaming;

  // Exclusions
  unsigned int* overflowExclusions;
  int overflowExclusionsSize;

  int2* exclIndexMaxDiff;
  int exclIndexMaxDiffSize;

  // Atom indices
  int* atomIndex;
  int atomIndexSize;

  // VdW types
  int* vdwTypes;
  int vdwTypesSize;

  unsigned int* patchNumCount;
  int patchNumCountSize;

  int* patchReadyQueue;
  int patchReadyQueueSize;

public:
  DpcppComputeNonbondedKernel(int deviceID, DpcppNonbondedTables& dpcppNonbondedTables, bool doStreaming);
  ~DpcppComputeNonbondedKernel();

  void updateVdwTypesExcl(const int atomStorageSize, const int* h_vdwTypes,
    const int2* h_exclIndexMaxDiff, const int* h_atomIndex, queue myQ);

  void nonbondedForce(DpcppTileListKernel& tlKernel,
    const int atomStorageSize, const bool doPairlist,
    const bool doEnergy, const bool doVirial, const bool doSlow,
    const float3 lata, const float3 latb, const float3 latc,
    const float4* h_xyzq, const float cutoff2, 
    float4* d_forces, float4* d_forcesSlow,
    float4* h_forces, float4* h_forcesSlow,
    queue myQ);

  void reduceVirialEnergy(DpcppTileListKernel& tlKernel,
    const int atomStorageSize, const bool doEnergy, const bool doVirial, const bool doSlow, const bool doGBIS,
    float4* d_forces, float4* d_forcesSlow,
    VirialEnergy* d_virialEnergy, queue myQ);

  void getVirialEnergy(VirialEnergy* h_virialEnergy, queue myQ);

  void bindExclusions(int numExclusions, unsigned int* exclusion_bits);

  int* getPatchReadyQueue();
};

#endif // NAMD_DPCPP
#endif // DPCPPCOMPUTENONBONDEDKERNEL_H
