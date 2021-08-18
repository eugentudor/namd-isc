#include "DpcppComputeNonbondedKernel.h"
#include "DpcppTileListKernel.h"
#include "DpcppDevice.h"
#include "DpcppUtils.h"
#include "NamdTypes.h"
#include <cmath>
#include <algorithm>

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>

using namespace sycl;
using namespace sycl::ONEAPI;

#ifdef WIN32
#define __thread __declspec(thread)
#endif

extern __thread DpcppDevice *dpcppDevice;

#define ROTATE_UP(data, i) select(sg.shuffle_up(data, AVXSIZE-i), sg.shuffle_down(data,i), (int)((AVXSIZE-i-sg.get_local_linear_id())>=0))

#define OVERALLOC 1.2f

void NAMD_die(const char *);

unsigned int constExclusions[MAX_CONST_EXCLUSIONS];

#define NONBONDKERNEL_NUM_WARP 4

template<bool doEnergy, bool doSlow>
NAMD_INLINE void calcForceEnergy(const float r2, const float qi, const float qj,
  const float3 dxyz, 
  const int vdwtypei, const int vdwtypej, const float2* __restrict__ vdwCoefTable,
  float4* d_forceTable, float4* d_energyTable,     // jhr
  int feTableSize, int vdwCoefTableSize,           // jhr
  float3& iforce, float3& iforceSlow, float3& jforce, float3& jforceSlow,
  float& energyVdw, float& energyElec, float& energySlow, nd_item<3> item_ct1) {

  int vdwIndex = vdwtypej + vdwtypei;
  float2 ljab = vdwCoefTable[vdwIndex];
  float rinv = rsqrt(r2);
  float4 fi;
  float fSlow = qi * qj;

  if (doEnergy) {
    fi = linear_interp_cudata_float4(d_energyTable, rinv, feTableSize);
    energyVdw  += ljab.x() * fi.z() + ljab.y() * fi.y();
    energyElec += fSlow * fi.x();
    if (doSlow) energySlow += fSlow * fi.w();
  }

  fi = linear_interp_cudata_float4(d_forceTable, rinv, feTableSize);
  float f = ljab.x() * fi.z() + ljab.y() * fi.y() + fSlow * fi.x();

  float3 fxyz;
  fxyz = dxyz *f;
  iforce += fxyz;
  jforce -= fxyz;

  if (doSlow) {
    fSlow *= fi.w();
    cl::sycl::float3 fxyzSlow;
    fxyzSlow = dxyz * fSlow;
    iforceSlow += fxyzSlow;
    jforceSlow -= fxyzSlow;
  }
}

template<bool doSlow>
NAMD_INLINE void storeForces(const int pos, const float3 force, const float3 forceSlow,
  float4* __restrict__ devForces, float4* __restrict__ devForcesSlow) {

  ATOMIC_ADD_FLOAT(devForces[pos].x(), force.x());
  ATOMIC_ADD_FLOAT(devForces[pos].y(), force.y());
  ATOMIC_ADD_FLOAT(devForces[pos].z(), force.z());
  if (doSlow) {
    ATOMIC_ADD_FLOAT(devForcesSlow[pos].x(), forceSlow.x());
    ATOMIC_ADD_FLOAT(devForcesSlow[pos].y(), forceSlow.y());
    ATOMIC_ADD_FLOAT(devForcesSlow[pos].z(), forceSlow.z());
  }
}

template<bool doSlow>
NAMD_INLINE void storeForces(const int pos, const float3 force, const float3 forceSlow,
  float3* __restrict__ forces, float3* __restrict__ forcesSlow) {
  ATOMIC_ADD_FLOAT(forces[pos].x(), force.x());
  ATOMIC_ADD_FLOAT(forces[pos].y(), force.y());
  ATOMIC_ADD_FLOAT(forces[pos].z(), force.z());
  if (doSlow) {
    ATOMIC_ADD_FLOAT(forcesSlow[pos].x(), forceSlow.x());
    ATOMIC_ADD_FLOAT(forcesSlow[pos].y(), forceSlow.y());
    ATOMIC_ADD_FLOAT(forcesSlow[pos].z(), forceSlow.z());
  }
}

template<bool doPairlist>
NAMD_INLINE void shuffleNext(float& xyzq_j_w, int& vdwtypej, int& jatomIndex, int& jexclMaxdiff, int& jexclIndex,nd_item<3> item_ct1) {
  auto sg = item_ct1.get_sub_group();
  xyzq_j_w = ROTATE_UP(xyzq_j_w, 1);
  vdwtypej = ROTATE_UP(vdwtypej, 1);
  if (doPairlist) {
    jatomIndex = ROTATE_UP(jatomIndex, 1);
    jexclIndex = ROTATE_UP(jexclIndex, 1);
    jexclMaxdiff = ROTATE_UP(jexclMaxdiff, 1);
  }
}

template<bool doPairlist>
NAMD_INLINE void shuffleNext(float& xyzq_j_w, int& vdwtypej, int& jatomIndex, nd_item<3> item_ct1) {
  auto sg = item_ct1.get_sub_group();
  xyzq_j_w = ROTATE_UP(xyzq_j_w, 1);
  vdwtypej = ROTATE_UP(vdwtypej, 1);
  if (doPairlist) {
    jatomIndex = ROTATE_UP(jatomIndex, 1);
  }
}

template<bool doSlow>
NAMD_INLINE void shuffleNext(float3& jforce, float3& jforceSlow, nd_item<3> item_ct1) {
  auto sg = item_ct1.get_sub_group();
  jforce.x() = ROTATE_UP(jforce.x(), 1);
  jforce.y() = ROTATE_UP(jforce.y(), 1);
  jforce.z() = ROTATE_UP(jforce.z(), 1);
  if (doSlow) {
    jforceSlow.x() = ROTATE_UP(jforceSlow.x(), 1);
    jforceSlow.y() = ROTATE_UP(jforceSlow.y(), 1);
    jforceSlow.z() = ROTATE_UP(jforceSlow.z(), 1);
  }
}

//
// Returns the lower estimate for the distance between a bounding box and a set of atoms
//
NAMD_INLINE float distsq(const BoundingBox a, const float4 b) {

  float dx = max(0.0f, fabs(a.xyz.x() - b.x()) - a.wxyz.x());
  float dy = max(0.0f, fabs(a.xyz.y() - b.y()) - a.wxyz.y());
  float dz = max(0.0f, fabs(a.xyz.z() - b.z()) - a.wxyz.z());
  return dx*dx + dy*dy + dz*dz;
}

#define LARGE_FLOAT (float)(1.0e10)

//
// Nonbonded force kernel
//
template <bool doEnergy, bool doVirial, bool doSlow, bool doPairlist, bool doStreaming>
 void
nonbondedForceKernel(
  const int start,  int numTileLists, const TileList* __restrict__ tileLists,
  TileExcl* __restrict__ tileExcls, const int* __restrict__ tileJatomStart,
  const int vdwCoefTableWidth, const float2* __restrict__ vdwCoefTable,
  const int* __restrict__ vdwTypes, const float3 lata, const float3 latb,
  const float3 latc, const float4* __restrict__ xyzq, const float cutoff2,
  float4* d_forceTable, float4* d_energyTable, int feTableSize, int vdwCoefTableSize,
  const int atomStorageSize, const float plcutoff2, const PatchPairRecord* __restrict__ patchPairs,
  const int* __restrict__ atomIndex, const int2* __restrict__ exclIndexMaxDiff,
  const unsigned int* __restrict__ overflowExclusions, unsigned int* __restrict__ tileListDepth,
  int* __restrict__ tileListOrder, int* __restrict__ jtiles, TileListStat* __restrict__ tileListStat,
  const BoundingBox* __restrict__ boundingBoxes,
  float4* __restrict__ devForces, float4* __restrict__ devForcesSlow, const int numPatches,
  unsigned int* __restrict__ patchNumCount, const DpcppPatchRecord* __restrict__ dpcppPatches,
  float4* __restrict__ mapForces, float4* __restrict__ mapForcesSlow, int* __restrict__ mapPatchReadyQueue,
  int* __restrict__ outputOrder, TileListVirialEnergy* __restrict__ virialEnergy,
  buffer<unsigned int, 1> exclusionsBuffer, queue &myQ,  int rangeSize, int workGroupSize) {

  myQ.submit(
    [&](handler &cgh) {
    auto constExclusions = exclusionsBuffer.get_access<access::mode::read_write>(cgh);
   cgh.parallel_for<class nonbondedForceKernel_offload>(
   nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
   [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {

  auto sg = item_ct1.get_sub_group();
  // Single warp takes care of one list of tiles
  // for (int itileList = (threadIdx.x + blockDim.x*blockIdx.x)/AVXSIZE;itileList < numTileLists;itileList += blockDim.x*gridDim.x/AVXSIZE)
//  int itileList = start + item_ct1.get_local_id(2)/AVXSIZE + item_ct1.get_local_range().get(2)/AVXSIZE*item_ct1.get_group(2);
    const int tid = item_ct1.get_local_id(2);
    const int gid = item_ct1.get_global_id(2);

//  int itileList = start + item_ct1.get_global_id(2)/AVXSIZE;
  int itileList = start + item_ct1.get_group().get_id(2) * (workGroupSize / AVXSIZE) + sg.get_group_linear_id();
  if (itileList < numTileLists)
  {
    float3 iforce;
    float3 iforceSlow;
    float energyVdw, energyElec, energySlow;
    int nexcluded;
    unsigned int itileListLen;
    int2 patchInd;
    int2 patchNumList;

    // Start computation
    {
      // Warp index (0...warpsize-1)
      const int wid = item_ct1.get_local_id(2) % AVXSIZE;

      TileList tmp = tileLists[itileList];
      int iatomStart = tmp.iatomStart;
      int jtileStart = tmp.jtileStart;
      int jtileEnd   = tmp.jtileEnd;
//      patchInd     = tmp.patchInd;
//      patchNumList = tmp.patchNumList;

      float3 sh;
      sh= tmp.offsetXYZ.x() * lata + tmp.offsetXYZ.y() * latb + tmp.offsetXYZ.z() * latc;
      // DH - set zeroShift flag if magnitude of shift vector is zero
      bool zeroShift = !(sycl::dot(sh, sh) > 0.0f);

      int iatomSize, iatomFreeSize, jatomSize, jatomFreeSize;
      if (doPairlist) {
        PatchPairRecord PPStmp = patchPairs[itileList];
        iatomSize     = PPStmp.iatomSize;
        iatomFreeSize = PPStmp.iatomFreeSize;
        jatomSize     = PPStmp.jatomSize;
        jatomFreeSize = PPStmp.jatomFreeSize;
      }

      // Write to global memory here to avoid register spilling
      if (doVirial) {
        if (wid == 0) {
          virialEnergy[itileList].sh = sh;
        }
      }

      // Load i-atom data (and shift coordinates)
      float4 xyzq_i = xyzq[iatomStart + wid];
      xyzq_i.x() += sh.x();
      xyzq_i.y() += sh.y();
      xyzq_i.z() += sh.z();
#if 1
      int vdwtypei = vdwTypes[iatomStart + wid]*vdwCoefTableWidth;
#else
      int vdwtypei = sg.load((sycl::multi_ptr<int, sycl::access::address_space::global_space>)(int *)&(vdwTypes[iatomStart]));
      vdwtypei *= vdwCoefTableWidth;
#endif

      // Load i-atom data (and shift coordinates)
      BoundingBox boundingBoxI;
      if (doPairlist) {
        boundingBoxI = boundingBoxes[iatomStart/AVXSIZE];
        boundingBoxI.xyz += sh;
      }

      // Get i-atom global index
      int iatomIndex;
      if (doPairlist) {
#if 1
      iatomIndex = atomIndex[iatomStart + wid];
#else
      iatomIndex = sg.load((sycl::multi_ptr<int, sycl::access::address_space::global_space>)(int *)&(atomIndex[iatomStart]));
#endif

      }

      // i-forces in registers
      iforce = float3(0.0f);

      // float3 iforceSlow;
      if (doSlow) {
        iforceSlow = float3(0.0f);
      }

      // float energyVdw, energyElec, energySlow;
      if (doEnergy) {
        energyVdw = 0.0f;
        energyElec = 0.0f;
        if (doSlow) energySlow = 0.0f;
      }

      // Number of exclusions
      // NOTE: Lowest bit is used as indicator bit for tile pairs:
      //       bit 0 tile has no atoms within pairlist cutoff
      //       bit 1 tile has atoms within pairlist cutoff
      // int nexcluded;
      if (doPairlist) nexcluded = 0;

      // Number of i loops and free atoms
      int nfreei;
      if (doPairlist) {
        int nloopi = min((int)(iatomSize - iatomStart), AVXSIZE);
        nfreei = max(iatomFreeSize - iatomStart, 0);
        if (wid >= nloopi) {
          xyzq_i.x() = -LARGE_FLOAT;
          xyzq_i.y() = -LARGE_FLOAT;
          xyzq_i.z() = -LARGE_FLOAT;
        }
      }

      // tile list stuff
      // int itileListLen;
      // int minJatomStart;
      if (doPairlist) {
        // minJatomStart = tileJatomStart[jtileStart];
        itileListLen = 0;
      }

      // Exclusion index and maxdiff
      int iexclIndex, iexclMaxdiff;
      if (doPairlist) {
#if 1
        int2 tmp = exclIndexMaxDiff[iatomStart + wid];
#else
        int2 tmp = sg.load((sycl::multi_ptr<cl::sycl::int2, sycl::access::address_space::global_space>)(cl::sycl::int2 *)&(exclIndexMaxDiff[iatomStart]));
#endif
        iexclIndex   = tmp.x();
        iexclMaxdiff = tmp.y();
      }


      for (int jtile=jtileStart;jtile <= jtileEnd;jtile++) {

        // Load j-atom starting index and exclusion mask
        int jatomStart = tileJatomStart[jtile];

        float4 xyzq_j = xyzq[jatomStart + wid];

        // Check for early bail
        if (doPairlist) {
          float r2bb = distsq(boundingBoxI, xyzq_j);
          if (all_of(sg, r2bb > plcutoff2)) {
            continue;
          }
        }
        unsigned int excl = (doPairlist) ? 0 : tileExcls[jtile].excl[wid];
#if 1
        int vdwtypej = vdwTypes[jatomStart + wid];
#else
        int vdwtypej = sg.load((sycl::multi_ptr<int, sycl::access::address_space::global_space>)(int *)&(vdwTypes[jatomStart]));
#endif

        // Get i-atom global index
        int jatomIndex;
        if (doPairlist) {
#if 1
          jatomIndex = atomIndex[jatomStart + wid];
#else
          jatomIndex = sg.load((sycl::multi_ptr<int, sycl::access::address_space::global_space>)(int *)&(atomIndex[jatomStart]));
#endif
        }

        // Number of j loops and free atoms
        int nfreej;
        if (doPairlist) {
          int nloopj = min((int)(jatomSize - jatomStart), AVXSIZE);
          nfreej = max(jatomFreeSize - jatomStart, 0);
          //if (nfreei == 0 && nfreej == 0) continue;
          if (wid >= nloopj) {
            xyzq_j.x() = LARGE_FLOAT;
            xyzq_j.y() = LARGE_FLOAT;
            xyzq_j.z() = LARGE_FLOAT;
          }
        }

        // DH - self requires that zeroShift is also set
        const bool self = zeroShift && (iatomStart == jatomStart);
        const int modval = (self) ? 2*AVXSIZE-1 : AVXSIZE-1;

        float3 jforce =float3(0.0f);
        
        float3 jforceSlow;
        if (doSlow) {
          jforceSlow = float3(0.0f);
        }

        int t = (self) ? 1 : 0;

        if (doPairlist) {
          // Build pair list
          // NOTE: Pairlist update, we must also include the diagonal since this is used
          //       in GBIS phase 2.
          // Clear the lowest (indicator) bit
          nexcluded &= (~1);

          // For self tiles, do the diagonal term (t=0).
          // NOTE: No energies are computed here, since this self-diagonal term is only for GBIS phase 2
          if (self) {
            int j = (0 + wid) & modval;
            // NOTE: __shfl() operation can give non-sense here because j may be >= AVXSIZE.
            //       However, if (j < AVXSIZE ..) below makes sure that these non-sense
            //       results are not actually every used
            float dx =ROTATE_UP(xyzq_j.x(), t) - xyzq_i.x();
            float dy =ROTATE_UP(xyzq_j.y(), t) - xyzq_i.y();
            float dz =ROTATE_UP(xyzq_j.z(), t) - xyzq_i.z();

            float r2 = dx*dx + dy*dy + dz*dz;

            if (j < AVXSIZE && r2 < plcutoff2) {
              // We have atom pair within the pairlist cutoff => Set indicator bit
              nexcluded |= 1;
            }
            shuffleNext<doPairlist>(xyzq_j.w(), vdwtypej, jatomIndex, item_ct1);
          }

          for (;t < AVXSIZE;t++) {
            int j = (t + wid) & modval;

            float3 dxyz;
            dxyz.x() =ROTATE_UP(xyzq_j.x(), t) - xyzq_i.x();
            dxyz.y() =ROTATE_UP(xyzq_j.y(), t) - xyzq_i.y();
            dxyz.z() =ROTATE_UP(xyzq_j.z(), t) - xyzq_i.z();
            float r2 = sycl::dot(dxyz, dxyz);

            excl >>= 1;

            if (j < AVXSIZE && r2 < plcutoff2) {
              // We have atom pair within the pairlist cutoff => Set indicator bit
              nexcluded |= 1;
              if (j < nfreej || wid < nfreei) {
                bool excluded = false;
                int indexdiff = jatomIndex - iatomIndex;
                if ( abs(indexdiff) <= iexclMaxdiff) {
                  indexdiff += iexclIndex;
                  int indexword = ((unsigned int) indexdiff) >> 5;

                  indexword = (indexword < MAX_CONST_EXCLUSIONS)?constExclusions[indexword]: overflowExclusions[indexword];
                  excluded = ((indexword & (1<<(indexdiff&31))) != 0);
                }
                if (excluded) nexcluded += 2;
//                if (!excluded) excl |= 0x80000000;
//                if (!excluded) excl |= 0x8000;
                if (!excluded) excl |= (1 << (AVXSIZE-1));
                if (!excluded && r2 < cutoff2) {
                  calcForceEnergy<doEnergy, doSlow>(r2, xyzq_i.w(), xyzq_j.w(), dxyz,
                    vdwtypei, vdwtypej,
                    vdwCoefTable,
                    d_forceTable, d_energyTable,     // jhr
                    feTableSize, vdwCoefTableSize,           // jhr
                    iforce, iforceSlow, jforce, jforceSlow, energyVdw, energyElec, energySlow, item_ct1);
                }
              }
            }
            shuffleNext<doPairlist>(xyzq_j.w(), vdwtypej, jatomIndex, item_ct1);
            shuffleNext<doSlow>(jforce, jforceSlow, item_ct1);
          } // t
        } else {
          // Just compute forces
          if (self) {
            excl >>= 1;
            xyzq_j.x() = ROTATE_UP(xyzq_j.x(), 1);
            xyzq_j.y() = ROTATE_UP(xyzq_j.y(), 1);
            xyzq_j.z() = ROTATE_UP(xyzq_j.z(), 1);
            shuffleNext<doPairlist>(xyzq_j.w(), vdwtypej, jatomIndex, item_ct1);
          }
          for (;t < AVXSIZE;t++) {
            if ((excl & 1)) {
              float3 dxyz;
              dxyz.x() = xyzq_j.x() - xyzq_i.x();
              dxyz.y() = xyzq_j.y() - xyzq_i.y();
              dxyz.z() = xyzq_j.z() - xyzq_i.z();

              float r2 = sycl::dot(dxyz, dxyz);

              if (r2 < cutoff2) {
                calcForceEnergy<doEnergy, doSlow>(r2, xyzq_i.w(), xyzq_j.w(), dxyz,
                  vdwtypei, vdwtypej,
                  vdwCoefTable,
                    d_forceTable, d_energyTable,     // jhr
                    feTableSize, vdwCoefTableSize,           // jhr
                  iforce, iforceSlow, jforce, jforceSlow, energyVdw, energyElec, energySlow, item_ct1);
              } // (r2 < cutoff2)
            } // (excl & 1)
            excl >>= 1;
            xyzq_j.x() = ROTATE_UP(xyzq_j.x(), 1);
            xyzq_j.y() = ROTATE_UP(xyzq_j.y(), 1);
            xyzq_j.z() = ROTATE_UP(xyzq_j.z(), 1);
            shuffleNext<doPairlist>(xyzq_j.w(), vdwtypej, jatomIndex, item_ct1);
            shuffleNext<doSlow>(jforce, jforceSlow, item_ct1);
          } // t
        }

        // Write j-forces
//{
//int pos = jatomStart + wid;
//if(pos==3 && jforce.z()!=0.){
//PRINTF("%05d:jtile [%04d:%04d] DevForces[%d].z= %f   jforce.z=%f\n", jtile, gid, tid, pos, devForces[pos].z(), jforce.z() );
//}
//}
        storeForces<doSlow>(jatomStart + wid, jforce, jforceSlow, devForces, devForcesSlow);

        // Write exclusions
        if (doPairlist && any_of(sg, nexcluded & 1)) {
          int anyexcl = (65536 | any_of(sg, excl));
          // Mark this jtile as non-empty:
          //  VdW:      1 if tile has atom pairs within pairlist cutoff and some these atoms interact
          //  GBIS: 65536 if tile has atom pairs within pairlist cutoff but not necessary interacting (i.e. these atoms are fixed or excluded)
          if (wid == 0) jtiles[jtile] = anyexcl;
          // Store exclusions
//if(jtile==1 && wid==4) PRINTF("###### 0  %05d:jtile [%04d:%04d] TileExcls:%u\n", jtile, gid, tid, excl);

#if 1
          tileExcls[jtile].excl[wid] = excl;
#else
          sg.store((sycl::multi_ptr<unsigned int, sycl::access::address_space::global_space>)(unsigned int *)&(tileExcls[jtile].excl[0]), excl);
#endif
          // itileListLen:
          // lower 16 bits number of tiles with atom pairs within pairlist cutoff that interact
          // upper 16 bits number of tiles with atom pairs within pairlist cutoff (but not necessary interacting)
          itileListLen += anyexcl;
          // NOTE, this minJatomStart is only stored once for the first tile list entry
          // minJatomStart = min(minJatomStart, jatomStart);
        }

      } // jtile

      // Write i-forces
//auto pos=iatomStart+wid;
      storeForces<doSlow>(iatomStart + wid, iforce, iforceSlow, devForces, devForcesSlow);
    }
    // Done with computation

    // Save pairlist stuff
    if (doPairlist) {

      // Warp index (0...warpsize-1)
      const int wid = item_ct1.get_local_id(2) % AVXSIZE;

      if (wid == 0) {
        // minJatomStart is in range [0 ... atomStorageSize-1]
        //int atom0 = (minJatomStart)/AVXSIZE;
        // int atom0 = 0;
        // int storageOffset = atomStorageSize/AVXSIZE;
        // int itileListLen = 0;
        // for (int jtile=jtileStart;jtile <= jtileEnd;jtile++) itileListLen += jtiles[jtile];
        // Store 0 if itileListLen == 0
        // tileListDepth[itileList] = (itileListLen > 0)*(itileListLen*storageOffset + atom0);
        tileListDepth[itileList] = itileListLen;
        tileListOrder[itileList] = itileList;
        // Number of active tilelists with tile with atom pairs within pairlist cutoff that interact
        if ((itileListLen & 65535) > 0) ATOMIC_ADD(int, tileListStat->numTileLists, 1);
        // Number of active tilelists with tiles with atom pairs within pairlist cutoff (but not necessary interacting)
        if (itileListLen > 0) ATOMIC_ADD(int, tileListStat->numTileListsGBIS, 1);
        // NOTE: always numTileListsGBIS >= numTileLists
      }

      // Remove indicator bit
      nexcluded >>= 1;
      // reduce_all not needed here. Reduce to lane 0 is sufficient
      int nexcludedWarp = reduce(sg, nexcluded, plus<>());
      if (wid == 0) ATOMIC_ADD(int, tileListStat->numExcluded, nexcludedWarp);
    }

    if (doVirial) {
      // Warp index (0...warpsize-1)
      const int wid = item_ct1.get_local_id(2) % AVXSIZE;

      // reduce_all not needed here. Reduce to lane 0 would be sufficient
      float3 iforceSum;
      iforceSum.x() = reduce(sg, iforce.x(), plus<>());
      iforceSum.y() = reduce(sg, iforce.y(), plus<>());
      iforceSum.z() = reduce(sg, iforce.z(), plus<>());

      if (wid == 0) {
        virialEnergy[itileList].force = iforceSum;
      }

      if (doSlow) {
        // reduce_all not needed here. Reduce to lane 0 would be sufficient
        iforceSum.x() = reduce(sg, iforceSlow.x(), plus<>());
        iforceSum.y() = reduce(sg, iforceSlow.y(), plus<>());
        iforceSum.z() = reduce(sg, iforceSlow.z(), plus<>());
        if (wid == 0) {
          virialEnergy[itileList].forceSlow = iforceSum;
        }
      }
    }

    // Reduce energy
    if (doEnergy) {
      // NOTE: We must hand write these warp-wide reductions to avoid excess register spillage
      //       (Why does CUB suck here?)
      energyVdw  = reduce(sg, energyVdw,  plus<>());
      energyElec = reduce(sg, energyElec, plus<>());
      if (doSlow) energySlow = reduce(sg, energySlow, plus<>());

      if (item_ct1.get_local_id(2) % AVXSIZE == 0) {
        virialEnergy[itileList].energyVdw  = energyVdw;
        virialEnergy[itileList].energyElec = energyElec;
        if (doSlow) virialEnergy[itileList].energySlow = energySlow;
      }
    }

    if (doStreaming) {
      // Make sure devForces and devForcesSlow have been written into device memory
      sg.barrier();
      atomic_fence(ONEAPI::memory_order::acq_rel, memory_scope::work_group); // May need memory_scope::device

      TileList tmp = tileLists[itileList];
      patchInd     = tmp.patchInd;
      patchNumList = tmp.patchNumList;

      int patchDone[2] = {false, false};
      const int wid = item_ct1.get_local_id(2) % AVXSIZE;
      if (wid == 0) {
        int patchCountOld0 = ATOMIC_FETCH_ADD(unsigned int, patchNumCount[patchInd.x()], (unsigned int)(1));
        if(patchCountOld0 + 1 == patchNumList.x()){
          patchDone[0] = true;
          patchNumCount[patchInd.x()]=0;
        } 
        if (patchInd.x() != patchInd.y()) {
          int patchCountOld1 = ATOMIC_FETCH_ADD(unsigned int, patchNumCount[patchInd.y()], (unsigned int)(1));
          if(patchCountOld1 + 1 == patchNumList.y()){
            patchDone[1] = true;
            patchNumCount[patchInd.y()]=0;
          }
        }
      }

      patchDone[0] = any_of(sg, patchDone[0]);
      patchDone[1] = any_of(sg, patchDone[1]);

      if (patchDone[0]) {
        // Patch 1 is done, write onto host-mapped memory
        DpcppPatchRecord patch = dpcppPatches[patchInd.x()];
        int start = patch.atomStart;
        int end   = start + patch.numAtoms;
        for (int i=start+wid;i < end;i+=AVXSIZE) {
          mapForces[i] = devForces[i];
          if (doSlow){
            mapForcesSlow[i] = devForcesSlow[i];
          }
        }
      }
      if (patchDone[1]) {
        // Patch 2 is done
        DpcppPatchRecord patch = dpcppPatches[patchInd.y()];
        int start = patch.atomStart;
        int end   = start + patch.numAtoms;
        for (int i=start+wid;i < end;i+=AVXSIZE) {
          mapForces[i] = devForces[i];
          if (doSlow){
            mapForcesSlow[i] = devForcesSlow[i];
          }
        }
      }

      if (patchDone[0] || patchDone[1]) {
        // Make sure mapForces and mapForcesSlow are up-to-date
        sg.barrier();
        atomic_fence(ONEAPI::memory_order::acq_rel, memory_scope::system);

        // Add patch into "patchReadyQueue"
        if (wid == 0) {
          if (patchDone[0]) {
            int ind = ATOMIC_FETCH_ADD(int, tileListStat->patchReadyQueueCount, 1);
            mapPatchReadyQueue[ind] = patchInd.x();
          }
          if (patchDone[1]) {
            int ind = ATOMIC_FETCH_ADD(int, tileListStat->patchReadyQueueCount, 1);
            mapPatchReadyQueue[ind] = patchInd.y();
          }
        }
      }
    }

    if (doStreaming && outputOrder != NULL && item_ct1.get_local_id(2) % AVXSIZE == 0) {
      int index = ATOMIC_FETCH_ADD(int, tileListStat->outputOrderIndex, 1);
      outputOrder[index] = itileList;
    }

  } // if (itileList < numTileLists)


  }); // cgs.parallel_for
  }); // q.submit
//  myQ.wait();
}

//
// Finish up - reduce virials from nonbonded kernel
//
#define REDUCENONBONDEDVIRIALKERNEL_NUM_WARP 32
 void reduceNonbondedVirialKernel(const bool doSlow,
  const int atomStorageSize,
  const float4* __restrict__ xyzq,
  const float4* __restrict__ devForces, const float4* __restrict__ devForcesSlow,
  VirialEnergy* __restrict__ virialEnergy, nd_item<3> item_ct1) {
  auto group =  item_ct1.get_group();

  for (int ibase = item_ct1.get_group(2)*item_ct1.get_local_range().get(2);ibase < atomStorageSize;ibase += item_ct1.get_local_range().get(2)*item_ct1.get_group_range(2))
  {
    int i = ibase + item_ct1.get_local_id(2);

    // Set to zero to avoid nan*0
    float4 pos;
    pos.x() = 0.0f;
    pos.y() = 0.0f;
    pos.z() = 0.0f;
    float4 force, forceSlow;
    force.x() = 0.0f;
    force.y() = 0.0f;
    force.z() = 0.0f;
    forceSlow.x() = 0.0f;
    forceSlow.y() = 0.0f;
    forceSlow.z() = 0.0f;
    if (i < atomStorageSize) {
      pos = xyzq[i];
      force = devForces[i];
      if (doSlow) forceSlow = devForcesSlow[i];
    }
    // Reduce across the entire thread block
    float vxxt = force.x()*pos.x();
    float vxyt = force.x()*pos.y();
    float vxzt = force.x()*pos.z();
    float vyxt = force.y()*pos.x();
    float vyyt = force.y()*pos.y();
    float vyzt = force.y()*pos.z();
    float vzxt = force.z()*pos.x();
    float vzyt = force.z()*pos.y();
    float vzzt = force.z()*pos.z();
    // atomicAdd(&virialEnergy->virial[0], (double)vxx);
    // atomicAdd(&virialEnergy->virial[1], (double)vxy);
    // atomicAdd(&virialEnergy->virial[2], (double)vxz);
    // atomicAdd(&virialEnergy->virial[3], (double)vyx);
    // atomicAdd(&virialEnergy->virial[4], (double)vyy);
    // atomicAdd(&virialEnergy->virial[5], (double)vyz);
    // atomicAdd(&virialEnergy->virial[6], (double)vzx);
    // atomicAdd(&virialEnergy->virial[7], (double)vzy);
    // atomicAdd(&virialEnergy->virial[8], (double)vzz);

    volatile float vxx = reduce(group, vxxt, plus<>());
    volatile float vxy = reduce(group, vxyt, plus<>());
    volatile float vxz = reduce(group, vxzt, plus<>());
    volatile float vyx = reduce(group, vyxt, plus<>());
    volatile float vyy = reduce(group, vyyt, plus<>());
    volatile float vyz = reduce(group, vyzt, plus<>());
    volatile float vzx = reduce(group, vzxt, plus<>());
    volatile float vzy = reduce(group, vzyt, plus<>());
    volatile float vzz = reduce(group, vzzt, plus<>());

    if (item_ct1.get_local_id(2) == 0) {
      ATOMIC_ADD(double, virialEnergy->virial[0], (double)vxx);
      ATOMIC_ADD(double, virialEnergy->virial[1], (double)vxy);
      ATOMIC_ADD(double, virialEnergy->virial[2], (double)vxz);
      ATOMIC_ADD(double, virialEnergy->virial[3], (double)vyx);
      ATOMIC_ADD(double, virialEnergy->virial[4], (double)vyy);
      ATOMIC_ADD(double, virialEnergy->virial[5], (double)vyz);
      ATOMIC_ADD(double, virialEnergy->virial[6], (double)vzx);
      ATOMIC_ADD(double, virialEnergy->virial[7], (double)vzy);
      ATOMIC_ADD(double, virialEnergy->virial[8], (double)vzz);
    }

    if (doSlow) {
      // if (isnan(forceSlow.x) || isnan(forceSlow.y) || isnan(forceSlow.z))
      float vxxSlowt = forceSlow.x()*pos.x();
      float vxySlowt = forceSlow.x()*pos.y();
      float vxzSlowt = forceSlow.x()*pos.z();
      float vyxSlowt = forceSlow.y()*pos.x();
      float vyySlowt = forceSlow.y()*pos.y();
      float vyzSlowt = forceSlow.y()*pos.z();
      float vzxSlowt = forceSlow.z()*pos.x();
      float vzySlowt = forceSlow.z()*pos.y();
      float vzzSlowt = forceSlow.z()*pos.z();
      // atomicAdd(&virialEnergy->virialSlow[0], (double)vxxSlow);
      // atomicAdd(&virialEnergy->virialSlow[1], (double)vxySlow);
      // atomicAdd(&virialEnergy->virialSlow[2], (double)vxzSlow);
      // atomicAdd(&virialEnergy->virialSlow[3], (double)vyxSlow);
      // atomicAdd(&virialEnergy->virialSlow[4], (double)vyySlow);
      // atomicAdd(&virialEnergy->virialSlow[5], (double)vyzSlow);
      // atomicAdd(&virialEnergy->virialSlow[6], (double)vzxSlow);
      // atomicAdd(&virialEnergy->virialSlow[7], (double)vzySlow);
      // atomicAdd(&virialEnergy->virialSlow[8], (double)vzzSlow);
      volatile float vxxSlow = reduce(group, vxxSlowt, plus<>());
      volatile float vxySlow = reduce(group, vxySlowt, plus<>());
      volatile float vxzSlow = reduce(group, vxzSlowt, plus<>());
      volatile float vyxSlow = reduce(group, vyxSlowt, plus<>());
      volatile float vyySlow = reduce(group, vyySlowt, plus<>());
      volatile float vyzSlow = reduce(group, vyzSlowt, plus<>());
      volatile float vzxSlow = reduce(group, vzxSlowt, plus<>());
      volatile float vzySlow = reduce(group, vzySlowt, plus<>());
      volatile float vzzSlow = reduce(group, vzzSlowt, plus<>());

      if (item_ct1.get_local_id(2) == 0) {
        ATOMIC_ADD(double, virialEnergy->virialSlow[0], (double)vxxSlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[1], (double)vxySlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[2], (double)vxzSlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[3], (double)vyxSlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[4], (double)vyySlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[5], (double)vyzSlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[6], (double)vzxSlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[7], (double)vzySlow);
        ATOMIC_ADD(double, virialEnergy->virialSlow[8], (double)vzzSlow);
      }
    }
  }

}

#define REDUCEVIRIALENERGYKERNEL_NUM_WARP 32
 void reduceVirialEnergyKernel(
  const bool doEnergy, const bool doVirial, const bool doSlow,
  const int numTileLists,
  const TileListVirialEnergy* __restrict__ tileListVirialEnergy,
  VirialEnergy* __restrict__ virialEnergy, nd_item<3> item_ct1) {
  auto group =  item_ct1.get_group();

  for (int ibase = item_ct1.get_group(2)*item_ct1.get_local_range().get(2);ibase < numTileLists;ibase += item_ct1.get_local_range().get(2)*item_ct1.get_group_range(2))
  {
    int itileList = ibase + item_ct1.get_local_id(2);
    TileListVirialEnergy ve;
    if (itileList < numTileLists) {
      ve = tileListVirialEnergy[itileList];
    } else {
      // Set to zero to avoid nan*0
      if (doVirial) {
        ve.sh = float3(0.0f);
        ve.force = float3(0.0f);
        ve.forceSlow = float3(0.0f);
      }
      if (doEnergy) {
        ve.energyVdw = 0.0;
        ve.energyElec = 0.0;
        ve.energySlow = 0.0;
        // ve.energyGBIS = 0.0;
      }
    }

    if (doVirial) {
      float vxxt = ve.force.x()*ve.sh.x();
      float vxyt = ve.force.x()*ve.sh.y();
      float vxzt = ve.force.x()*ve.sh.z();
      float vyxt = ve.force.y()*ve.sh.x();
      float vyyt = ve.force.y()*ve.sh.y();
      float vyzt = ve.force.y()*ve.sh.z();
      float vzxt = ve.force.z()*ve.sh.x();
      float vzyt = ve.force.z()*ve.sh.y();
      float vzzt = ve.force.z()*ve.sh.z();

      float vxx = reduce(group, vxxt, plus<>());
      float vxy = reduce(group, vxyt, plus<>());
      float vxz = reduce(group, vxzt, plus<>());
      float vyx = reduce(group, vyxt, plus<>());
      float vyy = reduce(group, vyyt, plus<>());
      float vyz = reduce(group, vyzt, plus<>());
      float vzx = reduce(group, vzxt, plus<>());
      float vzy = reduce(group, vzyt, plus<>());
      float vzz = reduce(group, vzzt, plus<>());

      if (item_ct1.get_local_id(2) == 0) {
        ATOMIC_ADD(double, virialEnergy->virial[0], (double)vxx);
        ATOMIC_ADD(double, virialEnergy->virial[1], (double)vxy);
        ATOMIC_ADD(double, virialEnergy->virial[2], (double)vxz);
        ATOMIC_ADD(double, virialEnergy->virial[3], (double)vyx);
        ATOMIC_ADD(double, virialEnergy->virial[4], (double)vyy);
        ATOMIC_ADD(double, virialEnergy->virial[5], (double)vyz);
        ATOMIC_ADD(double, virialEnergy->virial[6], (double)vzx);
        ATOMIC_ADD(double, virialEnergy->virial[7], (double)vzy);
        ATOMIC_ADD(double, virialEnergy->virial[8], (double)vzz);
      }

      if (doSlow) {
        vxxt = ve.forceSlow.x()*ve.sh.x();
        vxyt = ve.forceSlow.x()*ve.sh.y();
        vxzt = ve.forceSlow.x()*ve.sh.z();
        vyxt = ve.forceSlow.y()*ve.sh.x();
        vyyt = ve.forceSlow.y()*ve.sh.y();
        vyzt = ve.forceSlow.y()*ve.sh.z();
        vzxt = ve.forceSlow.z()*ve.sh.x();
        vzyt = ve.forceSlow.z()*ve.sh.y();
        vzzt = ve.forceSlow.z()*ve.sh.z();

        float vxx = reduce(group, vxxt, plus<>());
        float vxy = reduce(group, vxyt, plus<>());
        float vxz = reduce(group, vxzt, plus<>());
        float vyx = reduce(group, vyxt, plus<>());
        float vyy = reduce(group, vyyt, plus<>());
        float vyz = reduce(group, vyzt, plus<>());
        float vzx = reduce(group, vzxt, plus<>());
        float vzy = reduce(group, vzyt, plus<>());
        float vzz = reduce(group, vzzt, plus<>());

        if (item_ct1.get_local_id(2) == 0) {
          ATOMIC_ADD(double, virialEnergy->virialSlow[0], (double)vxx);
          ATOMIC_ADD(double, virialEnergy->virialSlow[1], (double)vxy);
          ATOMIC_ADD(double, virialEnergy->virialSlow[2], (double)vxz);
          ATOMIC_ADD(double, virialEnergy->virialSlow[3], (double)vyx);
          ATOMIC_ADD(double, virialEnergy->virialSlow[4], (double)vyy);
          ATOMIC_ADD(double, virialEnergy->virialSlow[5], (double)vyz);
          ATOMIC_ADD(double, virialEnergy->virialSlow[6], (double)vzx);
          ATOMIC_ADD(double, virialEnergy->virialSlow[7], (double)vzy);
          ATOMIC_ADD(double, virialEnergy->virialSlow[8], (double)vzz);
        }
      }
    }

    if (doEnergy) {
      volatile double energyVdw = reduce(group, ve.energyVdw, plus<>());
      volatile double energyElec = reduce(group, ve.energyElec, plus<>());

      if (item_ct1.get_local_id(2) == 0) {
          ATOMIC_ADD(double, virialEnergy->energyVdw, (double)energyVdw);
          ATOMIC_ADD(double, virialEnergy->energyElec, (double)energyElec);
      }
      if (doSlow) {
        volatile double energySlow = reduce(group, ve.energySlow, plus<>());

        if (item_ct1.get_local_id(2) == 0) ATOMIC_ADD(double, virialEnergy->energySlow, (double)energySlow);
      }
      // if (doGBIS) {
      //   double energyGBIS = BlockReduce(tempStorage).Sum(ve.energyGBIS); BLOCK_SYNC;
      //   if (threadIdx.x == 0) atomicAdd(&virialEnergy->energyGBIS, (double)energyGBIS);
      // }
    }
  }
}

#define REDUCEGBISENERGYKERNEL_NUM_WARP 32
 void reduceGBISEnergyKernel(const int numTileLists,
  const TileListVirialEnergy* __restrict__ tileListVirialEnergy,
  VirialEnergy* __restrict__ virialEnergy, nd_item<3> item_ct1) {
  auto group =  item_ct1.get_group();

  for (int ibase = item_ct1.get_group(2)*item_ct1.get_local_range().get(2);ibase < numTileLists;ibase += item_ct1.get_local_range().get(2)*item_ct1.get_group_range(2))
  {
    int itileList = ibase + item_ct1.get_local_id(2);
    double energyGBISt = 0.0;
    if (itileList < numTileLists) {
      energyGBISt = tileListVirialEnergy[itileList].energyGBIS;
    }

    volatile double energyGBIS = reduce(group, energyGBISt, plus<>());
    if (item_ct1.get_local_id(2) == 0) ATOMIC_ADD(double, virialEnergy->energyGBIS, (double)energyGBIS);
  }

}

// ##############################################################################################
// ##############################################################################################
// ##############################################################################################

DpcppComputeNonbondedKernel::DpcppComputeNonbondedKernel(int deviceID, DpcppNonbondedTables& dpcppNonbondedTables,
  bool doStreaming) : deviceID(deviceID), dpcppNonbondedTables(dpcppNonbondedTables), doStreaming(doStreaming) {
  
  dpcppDevice->setDeviceID(deviceID);

  overflowExclusions = NULL;
  overflowExclusionsSize = 0;

  exclIndexMaxDiff = NULL;
  exclIndexMaxDiffSize = 0;

  atomIndex = NULL;
  atomIndexSize = 0;

  vdwTypes = NULL;
  vdwTypesSize = 0;

  patchNumCount = NULL;
  patchNumCountSize = 0;

  patchReadyQueue = NULL;
  patchReadyQueueSize = 0;

}

DpcppComputeNonbondedKernel::~DpcppComputeNonbondedKernel() {
  dpcppDevice->setDeviceID(deviceID);
  if (overflowExclusions != NULL) deallocate_device<unsigned int>(&overflowExclusions);
  if (exclIndexMaxDiff != NULL) deallocate_device<int2>(&exclIndexMaxDiff);
  if (atomIndex != NULL) deallocate_device<int>(&atomIndex);
  if (vdwTypes != NULL) deallocate_device<int>(&vdwTypes);
  if (patchNumCount != NULL) deallocate_device<unsigned int>(&patchNumCount);
  if (patchReadyQueue != NULL) deallocate_host<int>(&patchReadyQueue);
}

void DpcppComputeNonbondedKernel::updateVdwTypesExcl(const int atomStorageSize, const int* h_vdwTypes,
  const int2* h_exclIndexMaxDiff, const int* h_atomIndex, queue myQ) {

  myQ.wait();
  reallocate_device<int>(&vdwTypes, &vdwTypesSize, atomStorageSize, OVERALLOC);
  reallocate_device<int2>(&exclIndexMaxDiff, &exclIndexMaxDiffSize, atomStorageSize, OVERALLOC);
  reallocate_device<int>(&atomIndex, &atomIndexSize, atomStorageSize, OVERALLOC);
  clear_device_array(vdwTypes, vdwTypesSize, myQ); // temporary to comare CUDA baseline
  clear_device_array(exclIndexMaxDiff, exclIndexMaxDiffSize, myQ); // temporary to comare CUDA baseline
  clear_device_array(atomIndex, atomIndexSize, myQ); // temporary to comare CUDA baseline


  copy_HtoD(h_vdwTypes, vdwTypes, atomStorageSize, myQ);
  copy_HtoD(h_exclIndexMaxDiff, exclIndexMaxDiff, atomStorageSize, myQ);
  copy_HtoD(h_atomIndex, atomIndex, atomStorageSize, myQ);
}

int* DpcppComputeNonbondedKernel::getPatchReadyQueue() {
  if (!doStreaming) {
    NAMD_die("DpcppComputeNonbondedKernel::getPatchReadyQueue() called on non-streaming kernel");
  }
  return patchReadyQueue;
}

void DpcppComputeNonbondedKernel::nonbondedForce(DpcppTileListKernel& tlKernel,
  const int atomStorageSize, const bool doPairlist,
  const bool doEnergy, const bool doVirial, const bool doSlow,
  const float3 lata, const float3 latb, const float3 latc,
  const float4* h_xyzq, const float cutoff2, 
  float4* d_forces, float4* d_forcesSlow,
  float4* h_forces, float4* h_forcesSlow,
  queue myQ) {
//try {

  if (!doPairlist) copy_HtoD(h_xyzq, tlKernel.get_xyzq(), atomStorageSize, myQ);

  clear_device_array<float4>(d_forces, atomStorageSize, myQ);
  if (doSlow) clear_device_array<float4>(d_forcesSlow, atomStorageSize, myQ);

  tlKernel.clearTileListStat(myQ);
//  clear_device_array<TileListStat>(tlKernel.getTileListStatDevPtr(), 1, myQ);

  // --- streaming ----
  float4 *m_forces = NULL;
  float4 *m_forcesSlow = NULL;
  int* m_patchReadyQueue = NULL;
  int numPatches = 0;
  unsigned int* patchNumCountPtr = NULL;
  if (doStreaming) {
    numPatches = tlKernel.getNumPatches();
    myQ.wait();
    if (reallocate_device<unsigned int>(&patchNumCount, &patchNumCountSize, numPatches)) {
      // If re-allocated, clear array
      clear_device_array<unsigned int>(patchNumCount, numPatches, myQ);
    }
    patchNumCountPtr = patchNumCount;
    bool re = reallocate_host<int>(&patchReadyQueue, &patchReadyQueueSize, numPatches);
    if (re) {
      // If re-allocated, re-set to "-1"
      for (int i=0;i < numPatches;i++) patchReadyQueue[i] = -1;
    }
/* DPCT_ORIG     cudaCheck(cudaHostGetDevicePointer(&m_patchReadyQueue, patchReadyQueue, 0));*/
    m_patchReadyQueue = patchReadyQueue;
/* DPCT_ORIG     cudaCheck(cudaHostGetDevicePointer(&m_forces, h_forces, 0));*/
    m_forces = h_forces;
/* DPCT_ORIG     cudaCheck(cudaHostGetDevicePointer(&m_forcesSlow, h_forcesSlow, 0));*/
    m_forcesSlow = h_forcesSlow;
  }
  // -----------------

  if (doVirial || doEnergy) {
    tlKernel.setTileListVirialEnergyLength(tlKernel.getNumTileLists());
  }

  int shMemSize = 0;

  int* outputOrderPtr = tlKernel.getOutputOrder();

  int numTileLists = tlKernel.getNumTileLists();

 #include "array_debug/ac_pre_nonbondedForceKernel.h"
  
  buffer<unsigned int, 1>  exclusionsBuffer(constExclusions, range<1>{MAX_CONST_EXCLUSIONS});
  int nwarp = NONBONDKERNEL_NUM_WARP;
  int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), AVXSIZE*nwarp);
  int start = 0;
  while (start < tlKernel.getNumTileLists())
  {

    int nleft = tlKernel.getNumTileLists() - start;
    int rangeSize = ((nleft-1)/nwarp+1)*workGroupSize;


#define CALL(DOENERGY, DOVIRIAL, DOSLOW, DOPAIRLIST, DOSTREAMING) \
    nonbondedForceKernel<DOENERGY, DOVIRIAL, DOSLOW, DOPAIRLIST, DOSTREAMING> \
    (start, numTileLists, tlKernel.getTileLists(), tlKernel.getTileExcls(), tlKernel.getTileJatomStart(), \
    dpcppNonbondedTables.getVdwCoefTableWidth(), dpcppNonbondedTables.getVdwCoefTable(), \
    vdwTypes, lata, latb, latc, tlKernel.get_xyzq(), cutoff2, \
    dpcppNonbondedTables.getForceTable(),  dpcppNonbondedTables.getEnergyTable(), \
    dpcppNonbondedTables.getfeTableSize()-1, dpcppNonbondedTables.getvdwTableSize()-1, \
    atomStorageSize, tlKernel.get_plcutoff2(), tlKernel.getPatchPairs(), atomIndex, exclIndexMaxDiff, overflowExclusions, \
    tlKernel.getTileListDepth(), tlKernel.getTileListOrder(), tlKernel.getJtiles(), tlKernel.getTileListStatDevPtr(), \
    tlKernel.getBoundingBoxes(), d_forces, d_forcesSlow, \
    numPatches, patchNumCountPtr, tlKernel.getDpcppPatches(), m_forces, m_forcesSlow, m_patchReadyQueue, \
    outputOrderPtr, tlKernel.getTileListVirialEnergy(), exclusionsBuffer, myQ, rangeSize, workGroupSize);

    if (doStreaming) {
      if (!doEnergy && !doVirial && !doSlow && !doPairlist) CALL(0, 0, 0, 0, 1);
      if (!doEnergy && !doVirial &&  doSlow && !doPairlist) CALL(0, 0, 1, 0, 1);
      if (!doEnergy &&  doVirial && !doSlow && !doPairlist) CALL(0, 1, 0, 0, 1);
      if (!doEnergy &&  doVirial &&  doSlow && !doPairlist) CALL(0, 1, 1, 0, 1);
      if ( doEnergy && !doVirial && !doSlow && !doPairlist) CALL(1, 0, 0, 0, 1);
      if ( doEnergy && !doVirial &&  doSlow && !doPairlist) CALL(1, 0, 1, 0, 1);
      if ( doEnergy &&  doVirial && !doSlow && !doPairlist) CALL(1, 1, 0, 0, 1);
      if ( doEnergy &&  doVirial &&  doSlow && !doPairlist) CALL(1, 1, 1, 0, 1);

      if (!doEnergy && !doVirial && !doSlow &&  doPairlist) CALL(0, 0, 0, 1, 1);
      if (!doEnergy && !doVirial &&  doSlow &&  doPairlist) CALL(0, 0, 1, 1, 1);
      if (!doEnergy &&  doVirial && !doSlow &&  doPairlist) CALL(0, 1, 0, 1, 1);
      if (!doEnergy &&  doVirial &&  doSlow &&  doPairlist) CALL(0, 1, 1, 1, 1);
      if ( doEnergy && !doVirial && !doSlow &&  doPairlist) CALL(1, 0, 0, 1, 1);
      if ( doEnergy && !doVirial &&  doSlow &&  doPairlist) CALL(1, 0, 1, 1, 1);
      if ( doEnergy &&  doVirial && !doSlow &&  doPairlist) CALL(1, 1, 0, 1, 1);
      if ( doEnergy &&  doVirial &&  doSlow &&  doPairlist) CALL(1, 1, 1, 1, 1);
    } else {
      if (!doEnergy && !doVirial && !doSlow && !doPairlist) CALL(0, 0, 0, 0, 0);
      if (!doEnergy && !doVirial &&  doSlow && !doPairlist) CALL(0, 0, 1, 0, 0);
      if (!doEnergy &&  doVirial && !doSlow && !doPairlist) CALL(0, 1, 0, 0, 0);
      if (!doEnergy &&  doVirial &&  doSlow && !doPairlist) CALL(0, 1, 1, 0, 0);
      if ( doEnergy && !doVirial && !doSlow && !doPairlist) CALL(1, 0, 0, 0, 0);
      if ( doEnergy && !doVirial &&  doSlow && !doPairlist) CALL(1, 0, 1, 0, 0);
      if ( doEnergy &&  doVirial && !doSlow && !doPairlist) CALL(1, 1, 0, 0, 0);
      if ( doEnergy &&  doVirial &&  doSlow && !doPairlist) CALL(1, 1, 1, 0, 0);

      if (!doEnergy && !doVirial && !doSlow &&  doPairlist) CALL(0, 0, 0, 1, 0);
      if (!doEnergy && !doVirial &&  doSlow &&  doPairlist) CALL(0, 0, 1, 1, 0);
      if (!doEnergy &&  doVirial && !doSlow &&  doPairlist) CALL(0, 1, 0, 1, 0);
      if (!doEnergy &&  doVirial &&  doSlow &&  doPairlist) CALL(0, 1, 1, 1, 0);
      if ( doEnergy && !doVirial && !doSlow &&  doPairlist) CALL(1, 0, 0, 1, 0);
      if ( doEnergy && !doVirial &&  doSlow &&  doPairlist) CALL(1, 0, 1, 1, 0);
      if ( doEnergy &&  doVirial && !doSlow &&  doPairlist) CALL(1, 1, 0, 1, 0);
      if ( doEnergy &&  doVirial &&  doSlow &&  doPairlist) CALL(1, 1, 1, 1, 0);
    }

    start += rangeSize*nwarp/workGroupSize;
  }


#include "array_debug/ac_post_nonbondedForceKernel.h"

}
//catch (exception const &exc) {
//  std::cerr << exc.what() << "EOE at line " << __LINE__ << std::endl;
//  std::exit(1);
//}

//
// Perform virial and energy reductions for non-bonded force calculation
//
void DpcppComputeNonbondedKernel::reduceVirialEnergy(DpcppTileListKernel& tlKernel,
  const int atomStorageSize, const bool doEnergy, const bool doVirial, const bool doSlow, const bool doGBIS,
  float4* d_forces, float4* d_forcesSlow,
  VirialEnergy* d_virialEnergy, queue myQ) {
//try {

  if (doEnergy || doVirial) {
    clear_device_array<VirialEnergy>(d_virialEnergy, 1, myQ);
  }

  if (doVirial)
  {
//    int nthread = std::min(dpcppDevice->getMaxWorkGroupSize(), REDUCENONBONDEDVIRIALKERNEL_NUM_WARP*AVXSIZE);

    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), REDUCENONBONDEDVIRIALKERNEL_NUM_WARP*AVXSIZE);
    int rangeSize = ((atomStorageSize-1)/workGroupSize+1)*workGroupSize;

    auto tlKernel_get_xyzq =tlKernel.get_xyzq(); 
#include "array_debug/ac_pre_reducenonbondedvirialkernel.h"

    // Ignore args:
    // compared before NBF calc kernel tlKernel.get_xyzq()
    // compared after NBF calc kernel: d_forces, d_forcesSlow
    {
      myQ.submit(
        [&](handler &cgh) {
          cgh.parallel_for<class reduceNonbondedVirialKernel_f2dab6>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {
              reduceNonbondedVirialKernel(doSlow, atomStorageSize, tlKernel_get_xyzq, d_forces, d_forcesSlow, d_virialEnergy, item_ct1);
            });
        });
//  myQ.wait();
    }
#include "array_debug/ac_post_reducenonbondedvirialkernel.h"
  }

  if (doVirial || doEnergy)
  {
    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), REDUCEVIRIALENERGYKERNEL_NUM_WARP*AVXSIZE); 
    int rangeSize = ((tlKernel.getTileListVirialEnergyLength()-1)/workGroupSize+1)*workGroupSize;

    auto tlKernel_getTileListVirialEnergyLength = tlKernel.getTileListVirialEnergyLength();
    auto tlKernel_getTileListVirialEnergy = (tlKernel_getTileListVirialEnergyLength) ? tlKernel.getTileListVirialEnergy(): NULL;

#include "array_debug/ac_pre_reducevirialenergykernel.h"
    {
      myQ.submit(
        [&](handler &cgh) {
          cgh.parallel_for<class reduceVirialEnergyKernel_24746d>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {
              reduceVirialEnergyKernel(doEnergy, doVirial, doSlow, tlKernel_getTileListVirialEnergyLength, tlKernel_getTileListVirialEnergy, d_virialEnergy, item_ct1);
            });
        });
//  myQ.wait();
    }
#include "array_debug/ac_post_reducevirialenergykernel.h"

  }  

  if (doGBIS && doEnergy)
  {
//    int nthread = std::min(dpcppDevice->getMaxWorkGroupSize(), REDUCEGBISENERGYKERNEL_NUM_WARP*AVXSIZE);
//    int nblock = (tlKernel.getTileListVirialEnergyGBISLength()-1)/nthread+1;

    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), REDUCEGBISENERGYKERNEL_NUM_WARP*AVXSIZE);
    int rangeSize = ((tlKernel.getTileListVirialEnergyGBISLength()-1)/workGroupSize+1)*workGroupSize;

    auto tlKernel_getTileListVirialEnergyGBISLength = tlKernel.getTileListVirialEnergyGBISLength();
    auto tlKernel_getTileListVirialEnergy = tlKernel.getTileListVirialEnergy();
    {
      myQ.submit(
        [&](handler &cgh) {
          cgh.parallel_for<class reduceGBISEnergyKernel_b32de7>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
              reduceGBISEnergyKernel(tlKernel_getTileListVirialEnergyGBISLength, tlKernel_getTileListVirialEnergy, d_virialEnergy, item_ct1);
            });
        });
    }
  }

}
//catch (exception const &exc) {
//  std::cerr << exc.what() << "EOE at line " << __LINE__ << std::endl;
//  std::exit(1);
//}

void DpcppComputeNonbondedKernel::bindExclusions(int numExclusions, unsigned int* exclusion_bits) {
	int nconst = ( numExclusions < MAX_CONST_EXCLUSIONS ? numExclusions : MAX_CONST_EXCLUSIONS );
  //TODO: Copy the data frp, exlusion_bits to the global Host array
  // unsigned int constExclusions[MAX_CONST_EXCLUSIONS];
  memcpy(constExclusions, (void*)(exclusion_bits), nconst*sizeof(unsigned int));

  reallocate_device<unsigned int>(&overflowExclusions, &overflowExclusionsSize, numExclusions);
  copy_HtoD_sync(exclusion_bits, overflowExclusions, numExclusions);
}

#endif // NAMD_DPCPP
