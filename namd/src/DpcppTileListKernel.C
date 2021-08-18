#ifdef NAMD_DPCPP
#include <oneapi/dpl/execution>
#include <oneapi/dpl/algorithm>
#endif

#include "DpcppUtils.h"
#include "DpcppTileListKernel.h"
#include "DpcppDevice.h"
#include "NamdTypes.h"

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <oneapi/dpl/iterator>

using namespace sycl;
using namespace sycl::ONEAPI;

#ifdef WIN32
#define __thread __declspec(thread)
#endif
extern __thread DpcppDevice *dpcppDevice;

#define OVERALLOC 1.2f

void NAMD_die(const char *);

//
// Calculate the number of lists that contribute to each patch
//
 void calcPatchNumLists(const int numTileLists, const int numPatches,
  const TileList* __restrict__ tileLists, int* __restrict__ patchNumLists, nd_item<3> item_ct1) {

  for (int i = item_ct1.get_global_id(2);i < numTileLists;i += item_ct1.get_global_range(2))
  {
    int2 patchInd = tileLists[i].patchInd;
    ATOMIC_ADD(int, patchNumLists[patchInd.x()], 1);
    if (patchInd.x() != patchInd.y()) ATOMIC_ADD(int, patchNumLists[patchInd.y()], 1);
  }

}

//
// Write patchNumList back to tile list and
// Find empty patches into emptyPatches[0 ... numEmptyPatches-1]
//
 void setPatchNumLists_findEmptyPatches(const int numTileLists,
  TileList* __restrict__ tileLists, const int* __restrict__ patchNumLists,
  const int numPatches, int* __restrict__ numEmptyPatches, int* __restrict__ emptyPatches, nd_item<3> item_ct1) {

  for (int i = item_ct1.get_global_id(2);i < numTileLists;i += item_ct1.get_global_range(2))
  {
    int2 patchInd = tileLists[i].patchInd;
    int2 patchNumList = int2(patchNumLists[patchInd.x()], patchNumLists[patchInd.y()]);
    tileLists[i].patchNumList = patchNumList;
  }

  for (int i = item_ct1.get_global_id(2) ;i < numPatches;i += item_ct1.get_global_range(2))
  {
    if (patchNumLists[i] == 0) {
      int ind = ATOMIC_FETCH_ADD(int, *numEmptyPatches, 1);
      emptyPatches[ind] = i;
    }
  }

}

//
// Builds a sort key that removes zeros but keeps the order otherwise the same
//
 void buildRemoveZerosSortKey(const int numTileLists,
  const unsigned int* __restrict__ tileListDepth, const int begin_bit, unsigned int* __restrict__ sortKey, nd_item<3> item_ct1) {

  for (int itileList = item_ct1.get_global_id(2);itileList < numTileLists;itileList += item_ct1.get_global_range(2))
  {
    int depth = (tileListDepth[itileList] >> begin_bit) & 65535;
    sortKey[itileList] = (depth == 0) ? numTileLists : itileList;
  }

}

 void setupSortKey(const int numTileLists, const int maxTileListLen,
  const TileList* __restrict__ tileLists, const unsigned int* __restrict__ tileListDepth,
  const int begin_bit, const unsigned int* __restrict__ sortKeys, unsigned int* __restrict__ sortKey, nd_item<3> item_ct1) {

  for (int itileList = item_ct1.get_global_id(2);itileList < numTileLists;itileList += item_ct1.get_global_range(2))
  {
    int icompute = tileLists[itileList].icompute;
    int depth = min((unsigned int)((tileListDepth[itileList] >> begin_bit) & 65535), (unsigned int)(maxTileListLen));
    int i = icompute*maxTileListLen + (depth - 1);
    sortKey[itileList] = (depth == 0) ? 0x7fffffff : sortKeys[i];
  }

}

//template <int width>
//void localSort(const int n, const int begin_bit, const int num_bit,
//               unsigned int *__restrict__ keys, int *__restrict__ vals,
//               sycl::nd_item<3> item_ct1,
//               typename BlockRadixSort::TempStorage *tempStorage) {
//}



 void storeInReverse(const int numTileListsSrc, const int begin_bit,
  const int* __restrict__ outputOrder, const int* __restrict__ tileListPos,
  const int* __restrict__ tileListOrderSrc,
  const unsigned int* __restrict__ tileListDepthSrc,
  int* __restrict__ tileListOrderDst,
  unsigned int* __restrict__ tileListDepthDst, nd_item<3> item_ct1) {

  for (int i = item_ct1.get_global_id(2);i < numTileListsSrc;i += item_ct1.get_global_range(2))
  {
    int j = outputOrder[numTileListsSrc - i - 1];
    if ( ((tileListDepthSrc[j] >> begin_bit) & 65535) > 0 ) {
      int k = tileListPos[i];
      tileListDepthDst[k] = tileListDepthSrc[j];
      tileListOrderDst[k] = j; //tileListOrderSrc[j];
    }
  }
}

//
// Bit shift tileListDepth so that only lower 16 bits are used
//
 void bitshiftTileListDepth(const int numTileLists, const int begin_bit,
  const int* __restrict__ outputOrder, const unsigned int* __restrict__ tileListDepthSrc,
  unsigned int* __restrict__ tileListDepthDst, nd_item<3> item_ct1) {

  for (int i = item_ct1.get_global_id(2);i < numTileLists;i+=item_ct1.get_global_range(2))
  {
    int j = outputOrder[numTileLists - i - 1];
    tileListDepthDst[i] = ((tileListDepthSrc[j] >> begin_bit) & 65535) == 0 ? 0 : 1;
  }

}

 void initMinMaxListLen(const int numComputes, const int maxTileListLen,
  int2* __restrict__ minmaxListLen, nd_item<3> item_ct1) {

  int2 val;
  val.x() = maxTileListLen+1;
  val.y() = 0;
  for (int i = item_ct1.get_global_id(2);i < numComputes;i += item_ct1.get_global_range(2))
  {
    minmaxListLen[i] = val;
  }

}

//
// Build sortKeys[], values are in range 0 ... numTileListsDst-1
//
 void buildSortKeys(const int numTileListsDst, const int maxTileListLen,
  const TileList* __restrict__ tileListsSrc,
  const int* __restrict__ tileListOrderDst,
  const unsigned int* __restrict__ tileListDepthDst,
  int2* __restrict__ minmaxListLen, unsigned int* __restrict__ sortKeys, nd_item<3> item_ct1) {

  for (int i = item_ct1.get_global_id(2);i < numTileListsDst;i += item_ct1.get_global_range(2))
  {
    int k = tileListOrderDst[i];
    int icompute = tileListsSrc[k].icompute;
    int depth    = tileListDepthDst[i] & 65535;
    // depth is in range [1 ... maxTileListLen]
    int j        = icompute*maxTileListLen + (depth-1);
    sortKeys[j] = i;
    int2 minmax = minmaxListLen[icompute];
    int2 minmaxOrig = minmax;
    if (minmax.x() > depth) minmax.x() = depth;
    if (minmax.y() < depth) minmax.y() = depth;
    if (minmax.x() != minmaxOrig.x()) {
      ONEAPI::atomic_ref< int, ONEAPI::memory_order::relaxed, ONEAPI::memory_scope::device, access::address_space::global_space>(minmaxListLen[icompute].x()).fetch_min(minmax.x());
    }
    if (minmax.y() != minmaxOrig.y()) {
      ONEAPI::atomic_ref< int, ONEAPI::memory_order::relaxed, ONEAPI::memory_scope::device, access::address_space::global_space>(minmaxListLen[icompute].y()).fetch_max(minmax.y());
    }
  }

}

 void fillSortKeys(const int numComputes, const int maxTileListLen,
  const int2* __restrict__ minmaxListLen, unsigned int* __restrict__ sortKeys, nd_item<3> item_ct1) {

  for (int i = item_ct1.get_global_id(2)/AVXSIZE;i < numComputes;i+=item_ct1.get_global_range(2)/AVXSIZE) {
    const int wid = item_ct1.get_local_id(2) % AVXSIZE;
    int2 minmax = minmaxListLen[i];
    int minlen = minmax.x();
    int maxlen = minmax.y();
    // minlen, maxlen are in range [1 ... maxTileListLen]
    // as long as i is in tileListsSrc[].icompute above
    if ( maxlen < minlen ) {
      minlen = 1;
      maxlen = maxTileListLen;
    }
    unsigned int minKey = sortKeys[i*maxTileListLen + minlen-1];
    unsigned int maxKey = sortKeys[i*maxTileListLen + maxlen-1];
    unsigned int aveKey = (maxKey + minKey)/2;
    for (int j=wid;j < minlen-1;j+=AVXSIZE) {
      sortKeys[i*maxTileListLen + j] = minKey;
    }
    for (int j=maxlen+wid;j < maxTileListLen;j+=AVXSIZE) {
      sortKeys[i*maxTileListLen + j] = maxKey;
    }
    for (int j=wid;j < maxTileListLen;j+=AVXSIZE) {
      if (sortKeys[i*maxTileListLen + j] == 0) {
        sortKeys[i*maxTileListLen + j] = aveKey;
      }
    }
  }

}

//
// Calculate bounding boxes for sets of AVXSIZE=32 atoms
//
#define BOUNDINGBOXKERNEL_NUM_WARP 8
void buildBoundingBoxesKernel(const int atomStorageSize, const float4* __restrict__ xyzq,
  BoundingBox* __restrict__ boundingBoxes, nd_item<3> item_ct1) {

  auto sg = item_ct1.get_sub_group();
  int sid = sg.get_local_id();
  const int gGroupId = item_ct1.get_global_id(2) / AVXSIZE;

  // Loop with group-aligned index to avoid group-divergence
  for (int igroup = gGroupId*AVXSIZE; igroup < atomStorageSize; igroup+=item_ct1.get_global_range(2)) {
    // Full atom index
    const int i = igroup + sid;
    // Bounding box index
    const int ibb = i/AVXSIZE;

    float4 xyzq_i = xyzq[min(atomStorageSize-1, i)];

    float3 minxyz, maxxyz;

    minxyz.x() = ONEAPI::reduce(sg, (float) xyzq_i.x(), ONEAPI::minimum<>());
    minxyz.y() = ONEAPI::reduce(sg, (float) xyzq_i.y(), ONEAPI::minimum<>());
    minxyz.z() = ONEAPI::reduce(sg, (float) xyzq_i.z(), ONEAPI::minimum<>());
    maxxyz.x() = ONEAPI::reduce(sg, (float) xyzq_i.x(), ONEAPI::maximum<>());
    maxxyz.y() = ONEAPI::reduce(sg, (float) xyzq_i.y(), ONEAPI::maximum<>());
    maxxyz.z() = ONEAPI::reduce(sg, (float) xyzq_i.z(), ONEAPI::maximum<>());

    if (sid == 0) {
      BoundingBox boundingBox;
      boundingBox.xyz.x() = 0.5f*(minxyz.x() + maxxyz.x());
      boundingBox.xyz.y()= 0.5f*(minxyz.y() + maxxyz.y());
      boundingBox.xyz.z()= 0.5f*(minxyz.z() + maxxyz.z());
      boundingBox.wxyz.x()= 0.5f*(maxxyz.x() - minxyz.x());
      boundingBox.wxyz.y()= 0.5f*(maxxyz.y() - minxyz.y());
      boundingBox.wxyz.z()= 0.5f*(maxxyz.z() - minxyz.z());
      boundingBoxes[ibb] = boundingBox;
    }
  }
}

//
// Returns the lower estimate for the distance between two bounding boxes
//
NAMD_INLINE float distsq(const BoundingBox a, const BoundingBox b) {
  float3 dxyz = max(float3(0.0f), fabs(a.xyz - b.xyz) - a.wxyz - b.wxyz);
  return dot(dxyz, dxyz);
}

#define TILELISTKERNELNEW_NUM_WARP 4
//
// NOTE: Executed on a single thread block
//
 void calcTileListPosKernel(const int numComputes,
  const DpcppComputeRecord* __restrict__ computes,
  const DpcppPatchRecord* __restrict__ patches,
  int* __restrict__ tilePos, nd_item<3> item_ct1, int * shTilePos0){

  auto group =  item_ct1.get_group();

  int nthread = item_ct1.get_local_range(2);

  if (item_ct1.get_local_id(2) == nthread-1) {
    shTilePos0[0] = 0;
  }
  item_ct1.barrier();

  for (int base=0;base < numComputes;base+=nthread) {
    int k = base + item_ct1.get_local_id(2);

    int numTiles1 = (k < numComputes) ? (patches[computes[k].patchInd.x()].numAtoms-1)/AVXSIZE+1 : 0;

    // Calculate positions in tile list and jtile list
    int tilePosVal;
        tilePosVal = ONEAPI::exclusive_scan(group, numTiles1, ONEAPI::plus<>());

    // Store into global memory
    if (k < numComputes) {
      tilePos[k] = (int)shTilePos0[0] + tilePosVal;
    }

    item_ct1.barrier();
    // Store block end position
    if (item_ct1.get_local_id(2) == nthread-1) {
      shTilePos0[0] += tilePosVal + numTiles1;
    }
  }
}


template<int nthread>
 void updatePatchesKernel(const int numComputes,
  const int* __restrict__ tilePos,
  const DpcppComputeRecord* __restrict__ computes,
  const DpcppPatchRecord* __restrict__ patches,
  TileList* __restrict__ tileLists, nd_item<3> item_ct1) {

  const int tid = item_ct1.get_local_id(2) % nthread;

  // nthread threads takes care of one compute
  for (int k = item_ct1.get_global_id(2)/nthread;k < numComputes;k+=item_ct1.get_global_range(2)/nthread)
  {
    DpcppComputeRecord compute = computes[k];
    float3 offsetXYZ = compute.offsetXYZ;
    int2 patchInd = compute.patchInd;
    int numTiles1 = (patches[patchInd.x()].numAtoms-1)/AVXSIZE+1;
    int itileList0 = tilePos[k];
    for (int i=tid;i < numTiles1;i+=nthread) {
      tileLists[itileList0 + i].offsetXYZ = offsetXYZ;
      tileLists[itileList0 + i].patchInd  = patchInd;
      tileLists[itileList0 + i].icompute  = k;
    }
  }

}

NAMD_INLINE int buildTileListsBBKernel_shmem_sizePerThread(const int maxTileListLen) {
  // Size in bytes
  int size = (
    maxTileListLen*sizeof(char)
    );
  return size;
}


 void
buildTileListsBBKernel(const int numTileLists,
  TileList* __restrict__ tileLists,
  const DpcppPatchRecord* __restrict__ patches,
  const int* __restrict__ tileListPos,
  const float3 lata, const float3 latb, const float3 latc,
  const float cutoff2, const int maxTileListLen,
  const BoundingBox* __restrict__ boundingBoxes,
  int* __restrict__ tileJatomStart,
  const int tileJatomStartSize,
  unsigned int* __restrict__ tileListDepth,
  int* __restrict__ tileListOrder,
  PatchPairRecord* __restrict__ patchPairs,
  TileListStat* __restrict__ tileListStat, nd_item<3> item_ct1, char *d_local) {

  auto sg = item_ct1.get_sub_group();

  char * sh_buffer = d_local;
  int sizePerThread = buildTileListsBBKernel_shmem_sizePerThread(maxTileListLen);
  int pos = item_ct1.get_local_id(2)*sizePerThread;
  volatile char* sh_tile = (char*)&sh_buffer[pos];
  const int tid = item_ct1.get_global_id(2);

  // Loop with warp-aligned index to avoid warp-divergence
  // Temporary: disable the loop over items when larger than the NDRange size for WG barrier in warp intrinsics
  for (int iwarp = (item_ct1.get_global_id(2)/AVXSIZE)*AVXSIZE; iwarp < numTileLists;iwarp += item_ct1.get_global_range(2)) {

    // Use one thread per tile list
    const int wid = sg.get_local_id(); //item_ct1.get_local_id(2) % AVXSIZE;
    const int itileList = iwarp + wid;

    int i;
    int itileListLen = 0;
    DpcppPatchRecord patch1;
    DpcppPatchRecord patch2;
    float3 offsetXYZ;
    int2 patchInd;
    int numTiles2;
    int icompute;

    if (itileList < numTileLists) {
      offsetXYZ = tileLists[itileList].offsetXYZ;
      patchInd  = tileLists[itileList].patchInd;
      icompute  = tileLists[itileList].icompute;
      // Get i-column
      i = itileList - tileListPos[icompute];

      float3 shxyz = offsetXYZ.x() * lata + offsetXYZ.y()* latb + offsetXYZ.z() * latc;
      // DH - set zeroShift flag if magnitude of shift vector is zero
      bool zeroShift = ! (dot(shxyz, shxyz) > 0);

      // Load patches
      patch1 = patches[patchInd.x()];
      patch2 = patches[patchInd.y()];
      // int numTiles1 = (patch1.numAtoms-1)/AVXSIZE+1;
      numTiles2 = (patch2.numAtoms-1)/AVXSIZE+1;
      int tileStart1 = patch1.atomStart/AVXSIZE;
      int tileStart2 = patch2.atomStart/AVXSIZE;

      // DH - self requires that zeroShift is also set
      bool self = zeroShift && (tileStart1 == tileStart2);

      // Load i-atom data (and shift coordinates)
      BoundingBox boundingBoxI = boundingBoxes[i + tileStart1];
      boundingBoxI.xyz += shxyz;

      for (int j=0;j < numTiles2;j++) {
        sh_tile[j] = 0;
        if (!self || j >= i) {
          BoundingBox boundingBoxJ = boundingBoxes[j + tileStart2];
          float r2bb = distsq(boundingBoxI, boundingBoxJ);
          if (r2bb < cutoff2) {
            sh_tile[j] = 1;
            itileListLen++;
          }
        }
      }

      tileListDepth[itileList] = (unsigned int)itileListLen;
      tileListOrder[itileList] = itileList;
    }

    int active = (itileListLen > 0);
    int activePos;
    int itileListPos;

    activePos    = ONEAPI::exclusive_scan(sg, active, ONEAPI::plus<>());
    itileListPos = ONEAPI::exclusive_scan(sg, itileListLen, ONEAPI::plus<>());

    int jtileStart, numJtiles;

    // Last thread in the warp knows the total number
    if (wid == AVXSIZE-1) {

      ATOMIC_ADD(int, tileListStat->numTileLists, activePos + active);
      numJtiles = itileListPos + itileListLen;

      jtileStart = ATOMIC_FETCH_ADD(int, tileListStat->numJtiles, numJtiles);

    }
    numJtiles  = sg.shuffle(numJtiles, AVXSIZE-1);
    jtileStart = sg.shuffle(jtileStart, AVXSIZE-1);

    if (jtileStart + numJtiles > tileJatomStartSize) {
      // tileJatomStart out of memory, exit
      if (wid == 0) tileListStat->tilesSizeExceeded = true;
      return;
    }

    int jStart = itileListPos;
    int jEnd = sg.shuffle_down(itileListPos, 1);

//if (jtileStart + numJtiles <= tileJatomStartSize) {
    if (wid == AVXSIZE-1) jEnd = numJtiles;

    if (itileListLen > 0) {
      // Setup tileLists[]
      TileList TLtmp;
      TLtmp.iatomStart = patch1.atomStart + i*AVXSIZE;
      TLtmp.jtileStart = jtileStart + jStart;
      TLtmp.jtileEnd   = jtileStart + jEnd - 1;
      TLtmp.patchInd   = patchInd;
      TLtmp.offsetXYZ  = offsetXYZ;
      TLtmp.icompute   = icompute;
      TLtmp.patchNumList.x() = 0;
      TLtmp.patchNumList.y() = 0;
      tileLists[itileList] = TLtmp;
      // PatchPair
      PatchPairRecord patchPair;
      patchPair.iatomSize     = patch1.atomStart + patch1.numAtoms;
      patchPair.iatomFreeSize = patch1.atomStart + patch1.numFreeAtoms;
      patchPair.jatomSize     = patch2.atomStart + patch2.numAtoms;
      patchPair.jatomFreeSize = patch2.atomStart + patch2.numFreeAtoms;
      patchPairs[itileList] = patchPair;

      // Write tiles
      int jtile = jtileStart + jStart;
      for (int j=0;j < numTiles2;j++) {
        if (sh_tile[j]) {
          tileJatomStart[jtile] = patch2.atomStart + j*AVXSIZE;
          jtile++;
        }
      }

    }

//} //if (jtileStart + numJtiles <= tileJatomStartSize)
  }

}

#define REPACKTILELISTSKERNEL_NUM_WARP 32
 void
repackTileListsKernel(
  const int numTileLists,
  const int begin_bit,
  const int* __restrict__ tileListPos,
  const int* __restrict__ tileListOrder,
  const int* __restrict__ jtiles,
  const TileList* __restrict__ tileListsSrc, 
  TileList* __restrict__ tileListsDst,
  const PatchPairRecord* __restrict__ patchPairsSrc,
  PatchPairRecord* __restrict__ patchPairsDst,
  const int* __restrict__ tileJatomStartSrc,
  int* __restrict__ tileJatomStartDst,
  const TileExcl* __restrict__ tileExclsSrc,
  TileExcl* __restrict__ tileExclsDst,
  nd_item<3> item_ct1) {

  auto sg = item_ct1.get_sub_group();

  const int wid = item_ct1.get_local_id(2) % AVXSIZE;

//if(item_ct1.get_local_id(2)==0) PRINTF("numTileLists:%d  item_ct1.get_global_range(2)/AVXSIZE:%d numTileListsPadded:%d listsPerGroup:%d       %d\n", numTileLists, (int)item_ct1.get_global_range(2)/AVXSIZE, numTileListsPadded, listsPerGroup, (int)(numTileLists % listsPerGroup));
//
//  // Temporary: allow all threads to execute and mask only final results writing to allow workgroup barriers
  // One warp does one tile list
  for (int i = item_ct1.get_global_id(2)/AVXSIZE;i < numTileLists; i+=item_ct1.get_global_range(2)/AVXSIZE)
  {
     
    int j = tileListOrder[i];
    int start = tileListPos[i];
    int end   = tileListPos[i+1]-1;
    if (wid == 0 && patchPairsSrc != NULL) patchPairsDst[i] = patchPairsSrc[j];
    // TileList
    int startOld   = tileListsSrc[j].jtileStart;
    int endOld     = tileListsSrc[j].jtileEnd;
    int iatomStart = tileListsSrc[j].iatomStart;
    float3 offsetXYZ;
    offsetXYZ.x()  = tileListsSrc[j].offsetXYZ.x();
    offsetXYZ.y()  = tileListsSrc[j].offsetXYZ.y();
    offsetXYZ.z()  = tileListsSrc[j].offsetXYZ.z();
    int2 patchInd = tileListsSrc[j].patchInd;
    int icompute = tileListsSrc[j].icompute;
    if (wid == 0) {
      TileList tileList;
      tileList.iatomStart = iatomStart;
      tileList.offsetXYZ  = offsetXYZ;
      tileList.jtileStart = start;
      tileList.jtileEnd   = end;
      tileList.patchInd   = patchInd;
      tileList.icompute   = icompute;
      tileList.patchNumList = 0; // Not initialized in CUDA
      tileListsDst[i] = tileList;
    }

    if (jtiles == NULL) {
      // No jtiles, simple copy will do
      int jtile = start;
      for (int jtileOld=startOld;jtileOld <= endOld;jtileOld+=AVXSIZE,jtile+=AVXSIZE) {
        if (jtileOld + wid <= endOld) {
          tileJatomStartDst[jtile + wid] = tileJatomStartSrc[jtileOld + wid];
        }
      }
      if (tileExclsSrc != NULL) {
        int jtile = start;
        for (int jtileOld=startOld;jtileOld <= endOld;jtileOld++,jtile++) {
          tileExclsDst[jtile].excl[wid] = tileExclsSrc[jtileOld].excl[wid];
        }
      }
    } else {
      int jtile0 = start;
      for (int jtileOld=startOld;jtileOld <= endOld;jtileOld+=AVXSIZE) {
        int t = jtileOld + wid;
        int jtile = (t <= endOld) ? jtiles[t] : 0;
        jtile >>= begin_bit;
        jtile &= 65535;

        int jtilePos;

        jtilePos = ONEAPI::exclusive_scan(sg, jtile, ONEAPI::plus<>());

        if (jtile) tileJatomStartDst[jtile0+jtilePos] = tileJatomStartSrc[t];

        if (tileExclsSrc != NULL) {
          unsigned long b;
          int predicate = jtile;
          {
            unsigned long vote = (predicate!=0) ? 0x1<<(int)sg.get_local_id() : 0;
            b = ONEAPI::reduce(sg, vote, ONEAPI::plus<>());
          }
          while (b != 0) {
            // k = index of thread that has data
            int k=0;
            for(k=0; k<64; k++){
              if( b & ((unsigned int)1<<k) ){
                break;
              }
            }
            tileExclsDst[jtile0].excl[wid] = tileExclsSrc[jtileOld + k].excl[wid];
            // remove 1 bit and advance jtile0
            b ^= ((unsigned int)1 << k);
            jtile0++;
          }
        } else {
          unsigned long b;
          int predicate = jtile;
          {
            unsigned long vote = (predicate!=0) ? 0x1<<(int)sg.get_local_id() : 0;
            b = ONEAPI::reduce(sg, vote, ONEAPI::plus<>());
          }
          jtile0 += popcount(b);
        }
      }
    }
  }
}

//
// NOTE: Executed on a single thread block
// oobKey = out-of-bounds key value
//
#define SORTTILELISTSKERNEL_NUM_THREAD 128//512
#define SORTTILELISTSKERNEL_ITEMS_PER_THREAD 22
template <typename keyT, typename valT, bool ascend>
//__launch_bounds__ (SORTTILELISTSKERNEL_NUM_THREAD, 1) 
void sortTileListsKernel(const int numTileListsSrc, const int numTileListsDst,
  const int begin_bit, const int end_bit, const keyT oobKey,
  keyT* __restrict__ tileListDepthSrc, keyT* __restrict__ tileListDepthDst,
  valT* __restrict__ tileListOrderSrc, valT* __restrict__ tileListOrderDst) {
}

 void reOrderTileListDepth(const int numTileLists, const int* __restrict__ tileListOrder,
  unsigned int* __restrict__ tileListDepthSrc, unsigned int* __restrict__ tileListDepthDst, nd_item<3> item_ct1) {

  for (int i = item_ct1.get_global_id(2);i < numTileLists;i+=item_ct1.get_global_range(2))
  {
    int j = tileListOrder[i];
    tileListDepthDst[i] = tileListDepthSrc[j];
  }

}

//
// Bit shift tileListDepth so that only lower 16 bits are used
//
 void bitshiftTileListDepth(const int numTileLists, const int begin_bit,
  unsigned int* __restrict__ tileListDepth, nd_item<3> item_ct1) {

  for (int itileList = item_ct1.get_global_id(2); itileList < numTileLists; itileList+=item_ct1.get_global_range(2))
  {
    unsigned int a = tileListDepth[itileList];
    a >>= begin_bit;
    a &= 65535;
    tileListDepth[itileList] = a;
  }

}

// ##############################################################################################
// ##############################################################################################
// ##############################################################################################

DpcppTileListKernel::DpcppTileListKernel(int deviceID, bool doStreaming) :
deviceID(deviceID), doStreaming(doStreaming) {

  dpcppDevice->setDeviceID(deviceID);

  activeBuffer = 1;

  numPatches = 0;
  numComputes = 0;

  dpcppPatches = NULL;
  dpcppPatchesSize = 0;

  dpcppComputes = NULL;
  dpcppComputesSize = 0;

  patchNumLists = NULL;
  patchNumListsSize = 0;

  emptyPatches = NULL;
  emptyPatchesSize = 0;
  h_emptyPatches = NULL;
  h_emptyPatchesSize = 0;
  numEmptyPatches = 0;

  sortKeySrc = NULL;
  sortKeySrcSize = 0;
  sortKeyDst = NULL;
  sortKeyDstSize = 0;

  tileLists1 = NULL;
  tileLists1Size = 0;
  tileLists2 = NULL;
  tileLists2Size = 0;

  patchPairs1 = NULL;
  patchPairs1Size = 0;
  patchPairs2 = NULL;
  patchPairs2Size = 0;

  tileJatomStart1 = NULL;
  tileJatomStart1Size = 0;
  tileJatomStart2 = NULL;
  tileJatomStart2Size = 0;

  boundingBoxes = NULL;
  boundingBoxesSize = 0;

  tileListDepth1 = NULL;
  tileListDepth1Size = 0;
  tileListDepth2 = NULL;
  tileListDepth2Size = 0;

  tileListOrder1 = NULL;
  tileListOrder1Size = 0;
  tileListOrder2 = NULL;
  tileListOrder2Size = 0;

  tileExcls1 = NULL;
  tileExcls1Size = 0;
  tileExcls2 = NULL;
  tileExcls2Size = 0;

  xyzq = NULL;
  xyzqSize = 0;

  allocate_device<TileListStat>(&d_tileListStat, 1);
  allocate_host<TileListStat>(&h_tileListStat, 1);

  tileListPos = NULL;
  tileListPosSize = 0;
  tempStorage = NULL;
  tempStorageSize = 0;

  jtiles = NULL;
  jtilesSize = 0;

  tilePos = NULL;
  tilePosSize = 0;

  tileListsGBIS = NULL;
  tileListsGBISSize = 0;

  tileJatomStartGBIS = NULL;
  tileJatomStartGBISSize = 0;

  tileListVirialEnergy = NULL;
  tileListVirialEnergySize = 0;

  atomStorageSize = 0;
  numTileLists = 0;
  numTileListsGBIS = 0;
  numJtiles = 1;

  outputOrder = NULL;
  outputOrderSize = 0;
  doOutputOrder = false;

  minmaxListLen = NULL;
  minmaxListLenSize = 0;

  sortKeys = NULL;
  sortKeysSize = 0;
  sortKeys_endbit = 0;

  tileListStatEventRecord = false;
}

DpcppTileListKernel::~DpcppTileListKernel() {
  dpcppDevice->setDeviceID(deviceID);
  deallocate_device<TileListStat>(&d_tileListStat);
  deallocate_host<TileListStat>(&h_tileListStat);
  //
  if (patchNumLists != NULL) deallocate_device<int>(&patchNumLists);
  if (emptyPatches != NULL) deallocate_device<int>(&emptyPatches);
  if (h_emptyPatches != NULL) deallocate_host<int>(&h_emptyPatches);
  if (sortKeySrc != NULL) deallocate_device<unsigned int>(&sortKeySrc);
  if (sortKeyDst != NULL) deallocate_device<unsigned int>(&sortKeyDst);
  //
  if (dpcppPatches != NULL) deallocate_device<DpcppPatchRecord>(&dpcppPatches);
  if (dpcppComputes != NULL) deallocate_device<DpcppComputeRecord>(&dpcppComputes);
  if (patchPairs1 != NULL) deallocate_device<PatchPairRecord>(&patchPairs1);
  if (patchPairs2 != NULL) deallocate_device<PatchPairRecord>(&patchPairs2);
  if (tileLists1 != NULL) deallocate_device<TileList>(&tileLists1);
  if (tileLists2 != NULL) deallocate_device<TileList>(&tileLists2);
  if (tileJatomStart1 != NULL) deallocate_device<int>(&tileJatomStart1);
  if (tileJatomStart2 != NULL) deallocate_device<int>(&tileJatomStart2);
  if (boundingBoxes != NULL) deallocate_device<BoundingBox>(&boundingBoxes);
  if (tileListDepth1 != NULL) deallocate_device<unsigned int>(&tileListDepth1);
  if (tileListDepth2 != NULL) deallocate_device<unsigned int>(&tileListDepth2);
  if (tileListOrder1 != NULL) deallocate_device<int>(&tileListOrder1);
  if (tileListOrder2 != NULL) deallocate_device<int>(&tileListOrder2);
  if (tileListPos != NULL) deallocate_device<int>(&tileListPos);
  if (tileExcls1 != NULL) deallocate_device<TileExcl>(&tileExcls1);
  if (tileExcls2 != NULL) deallocate_device<TileExcl>(&tileExcls2);
  if (tempStorage != NULL) deallocate_device<char>(&tempStorage);
  if (jtiles != NULL) deallocate_device<int>(&jtiles);
  if (tilePos != NULL) deallocate_device<int>(&tilePos);

  if (tileListsGBIS != NULL) deallocate_device<TileList>(&tileListsGBIS);
  if (tileJatomStartGBIS != NULL) deallocate_device<int>(&tileJatomStartGBIS);

  if (tileListVirialEnergy != NULL) deallocate_device<TileListVirialEnergy>(&tileListVirialEnergy);

  if (xyzq != NULL) deallocate_device<float4>(&xyzq);

  if (sortKeys != NULL) deallocate_device<unsigned int>(&sortKeys);
  if (minmaxListLen != NULL) deallocate_device<int2>(&minmaxListLen);

}

void DpcppTileListKernel::prepareTileList(queue myQ) {
  clear_device_array<int>(jtiles, numJtiles, myQ);
}

void DpcppTileListKernel::clearTileListStat(queue myQ) {
  // clear tileListStat, for patchReadyQueueCount, which is set equal to the number of empty patches
  memset(h_tileListStat, 0, sizeof(TileListStat));
  h_tileListStat->patchReadyQueueCount = getNumEmptyPatches();
  copy_HtoD(h_tileListStat, d_tileListStat, 1, myQ);
}

void DpcppTileListKernel::finishTileList(queue myQ) {
  copy_DtoH(d_tileListStat, h_tileListStat, 1, myQ);
myQ.wait();
  tileListStatEvent= myQ.single_task<class tileListStatEvent_empty_task>([=](){});
  tileListStatEventRecord = true;
}

void DpcppTileListKernel::updateComputes(const int numComputesIn,
  const DpcppComputeRecord* h_dpcppComputes, queue myQ) {

  numComputes = numComputesIn;


  myQ.wait();
  reallocate_device<DpcppComputeRecord>(&dpcppComputes, &dpcppComputesSize, numComputes);
  copy_HtoD<DpcppComputeRecord>(h_dpcppComputes, dpcppComputes, numComputes, myQ);

  if (doStreaming) doOutputOrder = true;
}

void DpcppTileListKernel::writeTileList(const char* filename, const int numTileLists,
  const TileList* d_tileLists, queue myQ) {

  TileList* h_tileLists = new TileList[numTileLists];
  copy_DtoH(d_tileLists, h_tileLists, numTileLists, myQ);
myQ.wait();
  FILE* handle = fopen(filename,"wt");
  for (int itileList=0;itileList < numTileLists;itileList++) {
    TileList tmp = h_tileLists[itileList];
    fprintf(handle, "%d %d %d %f %f %f %d %d %d %d\n",
      tmp.iatomStart, tmp.jtileStart, tmp.jtileEnd, tmp.offsetXYZ.x(), tmp.offsetXYZ.y(),
      tmp.offsetXYZ.z(), tmp.patchInd.x(), tmp.patchInd.y(), tmp.patchNumList.x(), tmp.patchNumList.y());
  }
  fclose(handle);
  delete [] h_tileLists;
}

void DpcppTileListKernel::writeTileJatomStart(const char* filename, const int numJtiles,
  const int* d_tileJatomStart, queue myQ) {

  int* h_tileJatomStart = new int[numJtiles];
  copy_DtoH(d_tileJatomStart, h_tileJatomStart, numJtiles, myQ);
myQ.wait();
  FILE* handle = fopen(filename,"wt");
  for (int i=0;i < numJtiles;i++) {
    fprintf(handle, "%d\n", h_tileJatomStart[i]);
  }
  fclose(handle);
  delete [] h_tileJatomStart;
}

void DpcppTileListKernel::buildTileLists(const int numTileListsPrev,
  const int numPatchesIn, const int atomStorageSizeIn, const int maxTileListLenIn,
  const float3 lata, const float3 latb, const float3 latc,
  const DpcppPatchRecord* h_dpcppPatches, const float4* h_xyzq,
  const float plcutoff2In, const size_t maxShmemPerBlock,
  queue myQ) {
//try {

  numPatches = numPatchesIn;
  atomStorageSize = atomStorageSizeIn;
  maxTileListLen = maxTileListLenIn;
  plcutoff2 = plcutoff2In;

  myQ.wait();
  if (doStreaming) {
    // Re-allocate patchNumLists
    reallocate_device<int>(&patchNumLists, &patchNumListsSize, numPatches);
    reallocate_device<int>(&emptyPatches, &emptyPatchesSize, numPatches+1);
    reallocate_host<int>(&h_emptyPatches, &h_emptyPatchesSize, numPatches+1);
  }

  // Re-allocate (tileLists1, patchPairs1
  reallocate_device<TileList>(&tileLists1, &tileLists1Size, numTileListsPrev, OVERALLOC);
  clear_device_array(tileLists1, tileLists1Size, myQ); // temporary to comare CUDA baseline
  reallocate_device<PatchPairRecord>(&patchPairs1, &patchPairs1Size, numTileListsPrev, OVERALLOC);
  clear_device_array(patchPairs1, patchPairs1Size, myQ); // temporary to comare CUDA baseline

  // Copy dpcppPatches to device
  reallocate_device<DpcppPatchRecord>(&dpcppPatches, &dpcppPatchesSize, numPatches);
  copy_HtoD(h_dpcppPatches, dpcppPatches, numPatches, myQ);

  // Re-allocate temporary storage
  reallocate_device<int>(&tilePos, &tilePosSize, numComputes, OVERALLOC);
  clear_device_array(tilePos, tilePosSize, myQ); // temporary to comare CUDA baseline
  // Calculate tile list positions (tilePos)
  {
    {
      int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
      int rangeSize = workGroupSize;
#include "array_debug/ac_pre_calctilelistposkernel.h"

      myQ.submit(
        [&](handler &cgh) {
          accessor<int, 1, access::mode::read_write, access::target::local> shTilePos0_acc_ct1(range<1>(1), cgh);

          auto numComputes2=numComputes;
          auto dpcppComputes2=dpcppComputes;
          auto dpcppPatches2=dpcppPatches;
          auto tilePos2=tilePos;
          cgh.parallel_for<class calcTileListPosKernel_b35e35>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
              calcTileListPosKernel(numComputes2, dpcppComputes2, dpcppPatches2, tilePos2, item_ct1, shTilePos0_acc_ct1.get_pointer());
            });
        }); //myQ.wait();
    }
#include "array_debug/ac_post_calctilelistposkernel.h"

  }
#include "array_debug/ac_pre_updatepatcheskernel.h"
  // Build (tileLists1.patchInd, tileLists1.offsetXYZ)
  {
    {
      int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 512);
      int rangeSize = ((numComputes-1)/(workGroupSize/AVXSIZE)+1)*workGroupSize;

      myQ.submit(
        [&](handler &cgh) {

          auto numComputes2=numComputes;
          auto tilePos2=tilePos;
          auto dpcppComputes2=dpcppComputes;
          auto dpcppPatches2=dpcppPatches;
          auto tileLists12=tileLists1;

          cgh.parallel_for<class updatePatchesKernel_1769b6>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
              updatePatchesKernel<AVXSIZE>(numComputes2, tilePos2, dpcppComputes2, dpcppPatches2, tileLists12, item_ct1);
            });
        }); //myQ.wait();
    }
  }
#include "array_debug/ac_post_updatepatcheskernel.h"

  // ---------------------------------------------------------------------------------------------


  // NOTE: tileListDepth2 and tileListOrder2 must have at least same size as
  // tileListDepth2 and tileListOrder2 since they're used in sorting
  myQ.wait();
  reallocate_device<unsigned int>(&tileListDepth2, &tileListDepth2Size, numTileListsPrev + 1, OVERALLOC);
  reallocate_device<int>(&tileListOrder2, &tileListOrder2Size, numTileListsPrev, OVERALLOC);
  clear_device_array(tileListDepth2, tileListDepth2Size, myQ); // temporary to comare CUDA baseline
  clear_device_array(tileListOrder2, tileListOrder2Size, myQ); // temporary to comare CUDA baseline

  // Allocate with +1 to include last term in the exclusive sum
  reallocate_device<unsigned int>(&tileListDepth1, &tileListDepth1Size, numTileListsPrev + 1, OVERALLOC);
  clear_device_array(tileListDepth1, tileListDepth1Size, myQ); // temporary to comare CUDA baseline

  reallocate_device<int>(&tileListOrder1, &tileListOrder1Size, numTileListsPrev, OVERALLOC);
  clear_device_array(tileListOrder1, tileListOrder1Size, myQ); // temporary to comare CUDA baseline

  reallocate_device<float4>(&xyzq, &xyzqSize, atomStorageSize, OVERALLOC);

  copy_HtoD(h_xyzq, xyzq, atomStorageSize, myQ);

  // Fills in boundingBoxes[0 ... numBoundingBoxes-1]
  {
    int numBoundingBoxes = atomStorageSize/AVXSIZE;
    reallocate_device<BoundingBox>(&boundingBoxes, &boundingBoxesSize, numBoundingBoxes, OVERALLOC);
    clear_device_array(boundingBoxes, boundingBoxesSize, myQ); // temporary to comare CUDA baseline

    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), AVXSIZE*BOUNDINGBOXKERNEL_NUM_WARP);
    int rangeSize = ((atomStorageSize-1)/workGroupSize+1)*workGroupSize;

    {
#include "array_debug/ac_pre_buildboundingboxeskernel.h"
 
      myQ.submit(
        [&](handler &cgh) {
          auto atomStorageSize2=atomStorageSize;
          auto xyzq2=xyzq;
          auto boundingBoxes2=boundingBoxes;
          cgh.parallel_for<class buildBoundingBoxesKernel_a0d9f1>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {

              buildBoundingBoxesKernel(atomStorageSize2, xyzq2, boundingBoxes2, item_ct1);
            });
        }); //myQ.wait();
#include "array_debug/ac_post_buildboundingboxeskernel.h"

    }

  }


  {
    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), AVXSIZE*TILELISTKERNELNEW_NUM_WARP);
    int rangeSize = ((numTileListsPrev-1)/workGroupSize+1)*workGroupSize;

    int shmem_size = buildTileListsBBKernel_shmem_sizePerThread(maxTileListLen)*workGroupSize;
    if(shmem_size > maxShmemPerBlock){
//      NAMD_die(
    std::cout << "ERROR: DpcppTileListKernel::buildTileLists, maximum shared memory allocation exceeded. Too many atoms in a patch" << " shmem_size:" << shmem_size << " maxShmemPerBlock:" << maxShmemPerBlock << " workGroupSize:" << workGroupSize << " maxTileListLen:" << maxTileListLen  << std::endl;
    }

    // NOTE: In the first call numJtiles = 1. buildTileListsBBKernel will return and
    //       tell the required size in h_tileListStat->numJtiles. In subsequent calls,
    //       re-allocation only happens when the size is exceeded.
    h_tileListStat->tilesSizeExceeded = true;
    int reallocCount = 0;
    while (h_tileListStat->tilesSizeExceeded) {
      myQ.wait();
      reallocate_device<int>(&tileJatomStart1, &tileJatomStart1Size, numJtiles, OVERALLOC);
      clear_device_array(tileJatomStart1, tileJatomStart1Size, myQ); // temporary to comare CUDA baseline

      clearTileListStat(myQ);
      {

#include "array_debug/ac_pre_buildtilelistsbbkernel.h"
        myQ.submit(
          [&](handler &cgh) {
            accessor<char, 1, access::mode::read_write, access::target::local> d_local_acc_ct1(range<1>(shmem_size), cgh);
            auto tileLists12=tileLists1;
            auto dpcppPatches2=dpcppPatches;
            auto tilePos2=tilePos;
            auto plcutoff22=plcutoff2;
            auto maxTileListLen2=maxTileListLen;
            auto boundingBoxes2=boundingBoxes;
            auto tileJatomStart12=tileJatomStart1;
            auto tileJatomStart1Size2=tileJatomStart1Size;
            auto tileListDepth12=tileListDepth1;
            auto tileListOrder12=tileListOrder1;
            auto patchPairs12=patchPairs1;
            auto d_tileListStat2=d_tileListStat;

            cgh.parallel_for<class buildTileListsBBKernel_6ff215>(
              nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
              [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {
                buildTileListsBBKernel(numTileListsPrev, tileLists12, dpcppPatches2, tilePos2, lata, latb, latc, plcutoff22, maxTileListLen2, boundingBoxes2, tileJatomStart12, tileJatomStart1Size2, tileListDepth12, tileListOrder12, patchPairs12, d_tileListStat2, item_ct1, d_local_acc_ct1.get_pointer());
              });
          }); //myQ.wait();

#include "array_debug/ac_post_buildtilelistsbbkernel.h"

      }
      // get (numATileLists, numJtiles, tilesSizeExceeded)
      copy_DtoH(d_tileListStat, h_tileListStat, 1, myQ);
myQ.wait();

      numJtiles = h_tileListStat->numJtiles;

      if (h_tileListStat->tilesSizeExceeded) {
        reallocCount++;
        if (reallocCount > 1) {
          NAMD_die("DpcppTileListKernel::buildTileLists, multiple reallocations detected");
        }
      }
    }

    numTileLists = h_tileListStat->numTileLists;

    myQ.wait();
    reallocate_device<int>(&jtiles, &jtilesSize, numJtiles, OVERALLOC);
    clear_device_array(jtiles, jtilesSize, myQ); // temporary to comare CUDA baseline
  }

  // Re-allocate tileListVirialEnergy.
  // NOTE: Since numTileLists here is an upper estimate (since it's based on bounding boxes),
  //       we're quaranteed to have enough space
  reallocate_device<TileListVirialEnergy>(&tileListVirialEnergy, &tileListVirialEnergySize, numTileLists, OVERALLOC);
  clear_device_array(tileListVirialEnergy, tileListVirialEnergySize, myQ); // temporary to comare CUDA baseline

  reallocate_device<TileList>(&tileLists2, &tileLists2Size, numTileLists, OVERALLOC);
  reallocate_device<PatchPairRecord>(&patchPairs2, &patchPairs2Size, numTileLists, OVERALLOC);
  reallocate_device<int>(&tileJatomStart2, &tileJatomStart2Size, numJtiles, OVERALLOC);
  reallocate_device<TileExcl>(&tileExcls1, &tileExcls1Size, numJtiles, OVERALLOC);
  reallocate_device<TileExcl>(&tileExcls2, &tileExcls2Size, numJtiles, OVERALLOC);
  clear_device_array(tileLists2, tileLists2Size, myQ); // temporary to comare CUDA baseline
  clear_device_array(patchPairs2, patchPairs2Size, myQ); // temporary to comare CUDA baseline
  clear_device_array(tileJatomStart2, tileJatomStart2Size, myQ); // temporary to comare CUDA baseline
  clear_device_array(tileExcls1, tileExcls1Size, myQ); // temporary to comare CUDA baseline
  clear_device_array(tileExcls2, tileExcls2Size, myQ); // temporary to comare CUDA baseline

  int numTileListsSrc = numTileListsPrev;
  int numJtilesSrc    = numJtiles;
  int numTileListsDst = numTileLists;
  int numJtilesDst    = numJtiles;


  // Sort tiles
  sortTileLists(
    false,
    0, false,
    numTileListsSrc, numJtilesSrc,
    PtrSize<TileList>(tileLists1, tileLists1Size), PtrSize<int>(tileJatomStart1, tileJatomStart1Size),
    PtrSize<unsigned int>(tileListDepth1, tileListDepth1Size), PtrSize<int>(tileListOrder1, tileListOrder1Size),
    PtrSize<PatchPairRecord>(patchPairs1, patchPairs1Size), PtrSize<TileExcl>(NULL, 0),
    numTileListsDst, numJtilesDst,
    PtrSize<TileList>(tileLists2, tileLists2Size), PtrSize<int>(tileJatomStart2, tileJatomStart2Size),
    PtrSize<unsigned int>(tileListDepth2, tileListDepth2Size), PtrSize<int>(tileListOrder2, tileListOrder2Size),
    PtrSize<PatchPairRecord>(patchPairs2, patchPairs2Size), PtrSize<TileExcl>(NULL, 0),
    myQ);

  // Set active buffer to 2
  setActiveBuffer(2);

  if (doOutputOrder) {
    myQ.wait();
    reallocate_device<int>(&outputOrder, &outputOrderSize, numTileLists, OVERALLOC);
  }
}
//catch (exception const &exc) {
//  std::cerr << exc.what() << "EOE at line " << __LINE__ << std::endl;
//  std::exit(1);
//}

//
// Returns integer log2(a) rounded up
//
int ilog2(int a) {
  // if (a < 0)
  //   NAMD_die("DpcppTileListKernel, ilog2: negative input value not valid");
  int k = 1;
  while (a >>= 1) k++;
  return k;
}

//
// Sort tile lists
//
void DpcppTileListKernel::sortTileLists(
  const bool useJtiles,
  const int begin_bit, const bool highDepthBitsSetIn,
  // Source
  const int numTileListsSrc, const int numJtilesSrc,
  PtrSize<TileList> tileListsSrc, PtrSize<int> tileJatomStartSrc,
  PtrSize<unsigned int> tileListDepthSrc, PtrSize<int> tileListOrderSrc,
  PtrSize<PatchPairRecord> patchPairsSrc, PtrSize<TileExcl> tileExclsSrc,
  // Destination
  const int numTileListsDst, const int numJtilesDst,
  PtrSize<TileList> tileListsDst, PtrSize<int> tileJatomStartDst,
  PtrSize<unsigned int> tileListDepthDst, PtrSize<int> tileListOrderDst,
  PtrSize<PatchPairRecord> patchPairsDst, PtrSize<TileExcl> tileExclsDst,
  queue myQ) {
//try {

  bool doShiftDown = (begin_bit != 0 || highDepthBitsSetIn);

  // if (numTileListsDst == 0)
  //   NAMD_die("DpcppTileListKernel::sortTileLists, numTileListsDst = 0");

  // Check that the array sizes are adequate
  if (numTileListsSrc > tileListsSrc.size || numJtilesSrc > tileJatomStartSrc.size ||
    numTileListsSrc > tileListDepthSrc.size || numTileListsSrc > tileListOrderSrc.size ||
    (patchPairsSrc.ptr != NULL && numTileListsSrc > patchPairsSrc.size) ||
    (tileExclsSrc.ptr != NULL && numJtilesSrc > tileExclsSrc.size))
    NAMD_die("DpcppTileListKernel::sortTileLists, Src allocated too small");

  if (numTileListsDst > tileListsDst.size || numJtilesDst > tileJatomStartDst.size ||
    numTileListsSrc > tileListDepthDst.size || numTileListsSrc > tileListOrderDst.size ||
    (patchPairsDst.ptr != NULL && numTileListsDst > patchPairsDst.size) ||
    (tileExclsDst.ptr != NULL && numJtilesDst > tileExclsDst.size))
    NAMD_die("DpcppTileListKernel::sortTileLists, Dst allocated too small");

  if (begin_bit != 0 && begin_bit != 16)
    NAMD_die("DpcppTileListKernel::sortTileLists, begin_bit must be 0 or 16");

  // Number of bits needed in the sort
  int num_bit = ilog2(maxTileListLen);
  if (num_bit > 16)
    NAMD_die("DpcppTileListKernel::sortTileLists, num_bit overflow");
  int end_bit = begin_bit + num_bit;

  if (doStreaming)
  {
    // ----------------------------------------------------------------------------------------
    if (doOutputOrder && useJtiles) {
      // outputOrder has been produced, put tile lists back in reverse order and produce sortKeys
      // NOTE: This is done very infrequently, typically only once when the MD run starts.

      // Calculate position from depth
      {
        // -----------------------------------------------------------------------------
        // Bit shift & mask tileListDepthDst such that only lower 16 bits are occupied
        // -----------------------------------------------------------------------------
        if (doShiftDown)
        {
          int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
          int rangeSize = ((numTileListsDst-1)/workGroupSize+1)*workGroupSize;

          AC_TAG("bitshifttilelistdepth0");

          myQ.submit(
            [&](handler &cgh) {
              auto outputOrder_ct2 = outputOrder;
              cgh.parallel_for<class bitshiftTileListDepth_1cd6a6>(
                nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
                [=](nd_item<3> item_ct1) {
                  bitshiftTileListDepth(numTileListsSrc, begin_bit, outputOrder_ct2,
                  tileListDepthSrc.ptr, tileListDepthDst.ptr, item_ct1);
              });
          }); //myQ.wait();

          AC_DEVICE(myQ, "post_bitshifttilelistdepth0", tileListDepthDst.ptr, tileListDepthDst.size);

        }

        myQ.wait();
        reallocate_device<int>(&tileListPos, &tileListPosSize, numTileListsSrc, OVERALLOC);
        clear_device_array(tileListPos, tileListPosSize, myQ); // temporary to comare CUDA baseline

        // --------------------------------------------------------------------
        // Compute itileList positions to store tileLists
        // ExclusiveSum(tileListDepthDst[0...numTileListsDst-1])
        // --------------------------------------------------------------------
        {
          AC_TAG("ExclusiveScanKernel1");
          AC_DEVICE(myQ, "pre_ExclusiveScanKernel1", tileListDepthDst.ptr, tileListDepthDst.size);

          oneapi::dpl::exclusive_scan(oneapi::dpl::execution::make_device_policy(myQ), tileListDepthDst.ptr, tileListDepthDst.ptr+numTileListsSrc, tileListPos, 0);
//          myQ.wait();

          AC_DEVICE(myQ, "post_ExclusiveScanKernel1", tileListPos, tileListPosSize);
        }

      }

      // Store in reverse order from outputOrder
      {
        int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
        int rangeSize = ((numTileListsDst-1)/workGroupSize+1)*workGroupSize;

        AC_TAG("storeInReverse");

        myQ.submit(
          [&](handler &cgh) {
          auto outputOrder_ct2 = outputOrder;
          auto tileListPos_ct3 = tileListPos;

          cgh.parallel_for<class storeInReverse_23432f>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
            storeInReverse(numTileListsSrc, begin_bit, outputOrder_ct2, tileListPos_ct3,
             tileListOrderSrc.ptr, tileListDepthSrc.ptr, tileListOrderDst.ptr, tileListDepthDst.ptr, item_ct1);
          });
        }); //myQ.wait();

//        AC_LOAD_DEVICE(myQ, "post_storeInReverse", tileListOrderDst.ptr, numTileListsSrc);
//        AC_LOAD_DEVICE(myQ, "post_storeInReverse", tileListDepthDst.ptr, numTileListsSrc);
        AC_DEVICE(myQ, "post_storeInReverse", tileListOrderDst.ptr, numTileListsSrc);
        AC_DEVICE(myQ, "post_storeInReverse", tileListDepthDst.ptr, numTileListsSrc);
      }

      // Build sortKeys
      {
        maxTileListLen_sortKeys = maxTileListLen;

        myQ.wait();
        reallocate_device<unsigned int>(&sortKeys, &sortKeysSize, numComputes*maxTileListLen);
        clear_device_array<unsigned int>(sortKeys, numComputes*maxTileListLen, myQ);

        // Re-allocate and initialize minmaxListLen
        {
          reallocate_device<int2>(&minmaxListLen, &minmaxListLenSize, numComputes);

          int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
          int rangeSize = ((numComputes - 1)/workGroupSize+1)*workGroupSize;

          AC_TAG("initMinMaxListLen");

          myQ.submit(
            [&](handler &cgh) {
            auto numComputes_ct0 = numComputes;
            auto maxTileListLen_ct1 = maxTileListLen;
            auto minmaxListLen_ct2 = minmaxListLen;

            cgh.parallel_for<class initMinMaxListLen_23jkr4n>(
              nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
              [=](nd_item<3> item_ct1) {
                  initMinMaxListLen(numComputes_ct0, maxTileListLen_ct1, minmaxListLen_ct2, item_ct1);
            });
          }); //myQ.wait();

          AC_DEVICE_INT2(myQ, "post_initMinMaxListLen", minmaxListLen, minmaxListLenSize);

        }

        // Build sortKeys and calculate minmaxListLen
        {
          int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
          int rangeSize = ((numTileListsDst- 1)/workGroupSize+1)*workGroupSize;

          AC_TAG("buildSortKeys");

          myQ.submit(
            [&](handler &cgh) {
            auto maxTileListLen_ct1 = maxTileListLen;
            auto minmaxListLen_ct5 = minmaxListLen;
            auto sortKeys_ct6 = sortKeys;

            cgh.parallel_for<class buildSortKeys_rvre7>(
              nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
              [=](nd_item<3> item_ct1) {
                buildSortKeys(numTileListsDst, maxTileListLen_ct1, tileListsSrc.ptr, tileListOrderDst.ptr,
                   tileListDepthDst.ptr, minmaxListLen_ct5, sortKeys_ct6, item_ct1);
            });
          }); //myQ.wait();
 
//          AC_LOAD_DEVICE(myQ, "post_buildSortKeys", minmaxListLen, minmaxListLenSize);
//          AC_LOAD_DEVICE(myQ, "post_buildSortKeys", sortKeys, sortKeysSize);
          AC_DEVICE_INT2(myQ, "post_buildSortKeys", minmaxListLen, minmaxListLenSize);
          AC_DEVICE(myQ, "post_buildSortKeys", sortKeys, sortKeysSize);

          // Maximum value in sortKeys[] is numTileListsDst - 1
          sortKeys_endbit = ilog2(numTileListsDst);
        }

        // Fill in missing sortKeys using minmaxListLen
        {
          int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
          int nsubgroups = workGroupSize/AVXSIZE;
          int rangeSize = ((numComputes- 1)/nsubgroups+1)*workGroupSize;

          AC_TAG("fillSortKeys");

          myQ.submit(
            [&](handler &cgh) {
            auto numComputes_ct0 = numComputes;
            auto maxTileListLen_ct1 = maxTileListLen;
            auto minmaxListLen_ct2 = minmaxListLen;
            auto sortKeys_ct3 = sortKeys;

            cgh.parallel_for<class fillSortKeys_fe87er>(
              nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
              [=](nd_item<3> item_ct1) {
// TODO: Mostly need to add subgroup size here
                fillSortKeys(numComputes_ct0, maxTileListLen_ct1, minmaxListLen_ct2, sortKeys_ct3, item_ct1);
            });
          }); //myQ.wait();
          AC_DEVICE(myQ, "post_fillSortKeys", sortKeys, sortKeysSize);

        }

      }

      doOutputOrder = false;

    } else if (doOutputOrder) {
      // OutputOrder will be produced in next pairlist non-bond kernel.
      // This time just remove zero length lists
      // NOTE: This is done very infrequently, typically only once when the MD run starts.

      int endbit_tmp = ilog2(numTileListsSrc);

      // Remove zeros
      {
        myQ.wait();
        reallocate_device<unsigned int>(&sortKeySrc, &sortKeySrcSize, numTileListsSrc, OVERALLOC);
        reallocate_device<unsigned int>(&sortKeyDst, &sortKeyDstSize, numTileListsSrc, OVERALLOC);
        clear_device_array(sortKeySrc, sortKeySrcSize, myQ); // temporary to comare CUDA baseline
        clear_device_array(sortKeyDst, sortKeyDstSize, myQ); // temporary to comare CUDA baseline

        int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
        int rangeSize = ((numTileListsSrc- 1)/workGroupSize+1)*workGroupSize;

        AC_TAG("buildRemoveZerosSortKey");
        myQ.submit(
          [&](handler &cgh) {
          auto sortKeySrc_ct3 = sortKeySrc;

          cgh.parallel_for<class buildRemoveZerosSortKey_dsves8328>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
              buildRemoveZerosSortKey(numTileListsSrc, tileListDepthSrc.ptr, begin_bit, sortKeySrc_ct3, item_ct1);
          });
        });
myQ.wait();
        AC_DEVICE(myQ, "post_buildRemoveZerosSortKey", sortKeys, sortKeysSize);
      }

//      if (numTileListsSrc <= SORTTILELISTSKERNEL_NUM_THREAD*SORTTILELISTSKERNEL_ITEMS_PER_THREAD)
//      {
//        int workGroupSize = SORTTILELISTSKERNEL_NUM_THREAD;
//        int rangeSize = workGroupSize;
//        unsigned int oobKey = numTileListsSrc;
//        myQ.submit(
//          [&](handler &cgh) {
//  /*
//          DPCT1054:137: The type of variable tempStorage is declared in device
//          function with the name type_ct1. Adjust the code to make the
//          type_ct1 declaration visible at the accessor declaration point.
//          */
//          sycl::accessor<uint8_t[sizeof(type_ct1)], 0,
//                         sycl::access::mode::read_write,
//                         sycl::access::target::local>
//              tempStorage_ct1_acc_ct1(cgh);
//
//          auto sortKeySrc_ct5 = sortKeySrc;
//          auto sortKeyDst_ct6 = sortKeyDst;
//
//          cgh.parallel_for<class sortTileListsKernel_sfver877>(
//            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
//            [=](nd_item<3> item_ct1) {
//              sortTileListsKernel<unsigned int, int, true>( numTileListsSrc, numTileListsDst, 0,
//                endbit_tmp, oobKey, sortKeySrc_ct5, sortKeyDst_ct6, tileListOrderSrc.ptr,
//                tileListOrderDst.ptr, item_ct1, tempStorage_ct1_acc_ct1.get_pointer());
//          });
//        }); // myQ.wait();
//      }
//      else
//      {
        // Long list, sort on multiple thread blocks
//        size_t size = 0;
//        cudaCheck(cub::DeviceRadixSort::SortPairs(NULL, size,
//          sortKeySrc, sortKeyDst, tileListOrderSrc.ptr, tileListOrderDst.ptr,
//          numTileListsSrc, 0, endbit_tmp, myQ));
//        // Make sure tempStorage doesn't remain NULL
//        if (size == 0) size = 128;
//        reallocate_device<char>(&tempStorage, &tempStorageSize, size, 1.5f);
//        size = tempStorageSize;
//        cudaCheck(cub::DeviceRadixSort::SortPairs((void *)tempStorage, size,
//          sortKeySrc, sortKeyDst, tileListOrderSrc.ptr, tileListOrderDst.ptr,
//          numTileListsSrc, 0, endbit_tmp, myQ));

        AC_TAG("sortTileListsKernel1");
        AC_DEVICE(myQ, "pre_sortTileListsKernel1", sortKeySrc, numTileListsSrc);
        AC_DEVICE(myQ, "pre_sortTileListsKernel1", sortKeyDst, numTileListsDst);
        AC_DEVICE(myQ, "pre_sortTileListsKernel1", tileListOrderSrc.ptr, numTileListsSrc);
        AC_DEVICE(myQ, "pre_sortTileListsKernel1", tileListOrderDst.ptr, numTileListsDst);

        copy_DtoD(sortKeySrc, sortKeyDst, numTileListsSrc, myQ);
        copy_DtoD(tileListOrderSrc.ptr, tileListOrderDst.ptr, numTileListsSrc, myQ);
        myQ.wait();
        auto first = oneapi::dpl::make_zip_iterator(sortKeyDst, tileListOrderDst.ptr);
        auto last = first + std::distance(sortKeyDst, sortKeyDst + numTileListsSrc);
        std::sort(oneapi::dpl::execution::make_device_policy(myQ), first, last,
          [](const auto &it1, const auto &it2){using std::get; return get<0>(it1) < get<0>(it2);});

//        AC_LOAD_DEVICE(myQ, "post_sortTileListsKernel1", sortKeyDst, numTileListsDst);
//        AC_LOAD_DEVICE(myQ, "post_sortTileListsKernel1", tileListOrderDst.ptr, numTileListsDst);

        AC_DEVICE(myQ, "post_sortTileListsKernel1", sortKeySrc, numTileListsSrc);
        AC_DEVICE(myQ, "post_sortTileListsKernel1", sortKeyDst, numTileListsDst);
        AC_DEVICE(myQ, "post_sortTileListsKernel1", tileListOrderSrc.ptr, numTileListsSrc);
        AC_DEVICE(myQ, "post_sortTileListsKernel1", tileListOrderDst.ptr, numTileListsDst);

//        myQ.wait();
//      }

      // Re-order tileListDepth using tileListOrderDst
      {
        int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
        int rangeSize = ((numTileListsDst- 1)/workGroupSize+1)*workGroupSize;

        AC_TAG("reOrderTileListDepth1");
        myQ.submit(
          [&](handler &cgh) {
          cgh.parallel_for<class reOrderTileListDepth_sdfv87sd>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
              reOrderTileListDepth(numTileListsDst, tileListOrderDst.ptr,
                tileListDepthSrc.ptr, tileListDepthDst.ptr, item_ct1);
          });
        }); //
        AC_DEVICE(myQ, "post_reOrderTileListDepth1", tileListDepthDst.ptr, numTileListsDst);
      }

    } else {
      // This is done during regular MD cycle

      if (sortKeys_endbit <= 0)
        NAMD_die("CudaTileListKernel::sortTileLists, sortKeys not produced or invalid sortKeys_endbit");

      // Setup sort keys
      {
        myQ.wait();
        reallocate_device<unsigned int>(&sortKeySrc, &sortKeySrcSize, numTileListsSrc, OVERALLOC);
        reallocate_device<unsigned int>(&sortKeyDst, &sortKeyDstSize, numTileListsSrc, OVERALLOC);

        int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
        int rangeSize = ((numTileListsSrc- 1)/workGroupSize+1)*workGroupSize;

        AC_TAG("setupSortKey");
        myQ.submit(
          [&](handler &cgh) {
          auto maxTileListLen_sortKeys_ct1 = maxTileListLen_sortKeys;
          auto sortKeys_ct5 = sortKeys;
          auto sortKeySrc_ct6 = sortKeySrc;

          cgh.parallel_for<class setupSortKey_d987vdf>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
              setupSortKey(numTileListsSrc, maxTileListLen_sortKeys_ct1,
                           tileListsSrc.ptr, tileListDepthSrc.ptr, begin_bit,
                           sortKeys_ct5, sortKeySrc_ct6, item_ct1);
          });
        });
myQ.wait();
        AC_DEVICE(myQ, "post_setupSortKey", sortKeySrc, numTileListsSrc);

      }

      // Global sort
//      if (numTileListsSrc <= SORTTILELISTSKERNEL_NUM_THREAD*SORTTILELISTSKERNEL_ITEMS_PER_THREAD)
//      // if (false)
//      {
//        // Short list, sort withing a single thread block
//        int nthread = SORTTILELISTSKERNEL_NUM_THREAD;
//        int nblock = 1;
//
//        unsigned int oobKey = (2 << sortKeys_endbit) - 1;
///* DPCT_ORIG         sortTileListsKernel <unsigned int, int, true> <<< nblock,
//   nthread, 0, myQ >>> (numTileListsSrc, numTileListsDst, 0, sortKeys_endbit,
//   oobKey, sortKeySrc, sortKeyDst, tileListOrderSrc.ptr,
//   tileListOrderDst.ptr);*/
//        /*
//        DPCT1049:118: The workgroup size passed to the SYCL kernel may exceed
//        the limit. To get the device limit, query
//        info::device::max_work_group_size. Adjust the workgroup size if needed.
//        */
//        myQ->submit([&](sycl::handler &cgh) {
//          /*
//          DPCT1054:138: The type of variable tempStorage is declared in device
//          function with the name type_ct1. Adjust the code to make the
//          type_ct1 declaration visible at the accessor declaration point.
//          */
//          sycl::accessor<uint8_t[sizeof(type_ct1)], 0,
//                         sycl::access::mode::read_write,
//                         sycl::access::target::local>
//              tempStorage_ct1_acc_ct1(cgh);
//
//          auto sortKeys_endbit_ct3 = sortKeys_endbit;
//          auto sortKeySrc_ct5 = sortKeySrc;
//          auto sortKeyDst_ct6 = sortKeyDst;
//
//          cgh.parallel_for(sycl::nd_range<3>(sycl::range<3>(1, 1, nblock) *
//                                                 sycl::range<3>(1, 1, nthread),
//                                             sycl::range<3>(1, 1, nthread)),
//                           [=](sycl::nd_item<3> item_ct1) {
//                             sortTileListsKernel<unsigned int, int, true>(
//                                 numTileListsSrc, numTileListsDst, 0,
//                                 sortKeys_endbit_ct3, oobKey, sortKeySrc_ct5,
//                                 sortKeyDst_ct6, tileListOrderSrc.ptr,
//                                 tileListOrderDst.ptr, item_ct1,
//                                 tempStorage_ct1_acc_ct1.get_pointer());
//                           });
//        });
///* DPCT_ORIG         cudaCheck(cudaGetLastError());*/
//        /*
//        DPCT1010:119: SYCL uses exceptions to report errors and does not use the
//        error codes. The call was replaced with 0. You need to rewrite this
//        code.
//        */
//        cudaCheck(0);
//      }
//      else
//      {
        // Long list, sort on multiple thread blocks
//        size_t size = 0;
//        cudaCheck(cub::DeviceRadixSort::SortPairs(NULL, size,
//          sortKeySrc, sortKeyDst, tileListOrderSrc.ptr, tileListOrderDst.ptr,
//          numTileListsSrc, 0, sortKeys_endbit, myQ));
//        // Make sure tempStorage doesn't remain NULL
//        if (size == 0) size = 128;
//        reallocate_device<char>(&tempStorage, &tempStorageSize, size, 1.5f);
//        size = tempStorageSize;
//        cudaCheck(cub::DeviceRadixSort::SortPairs((void *)tempStorage, size,
//          sortKeySrc, sortKeyDst, tileListOrderSrc.ptr, tileListOrderDst.ptr,
//          numTileListsSrc, 0, sortKeys_endbit, myQ));

        AC_TAG("sortTileListsKernel2");
        AC_DEVICE(myQ, "pre_sortTileListsKernel2", sortKeySrc, numTileListsSrc);
        AC_DEVICE(myQ, "pre_sortTileListsKernel2", sortKeyDst, numTileListsDst);
        AC_DEVICE(myQ, "pre_sortTileListsKernel2", tileListOrderSrc.ptr, numTileListsSrc);
        AC_DEVICE(myQ, "pre_sortTileListsKernel2", tileListOrderDst.ptr, numTileListsDst);

        copy_DtoD(sortKeySrc, sortKeyDst, numTileListsSrc, myQ);
        copy_DtoD(tileListOrderSrc.ptr, tileListOrderDst.ptr, numTileListsSrc, myQ);
        myQ.wait();
        auto first = oneapi::dpl::make_zip_iterator(sortKeyDst, tileListOrderDst.ptr);
        auto last = first + std::distance(sortKeyDst, sortKeyDst + numTileListsSrc);
        std::sort(oneapi::dpl::execution::make_device_policy(myQ), first, last,
          [](const auto &it1, const auto &it2){using std::get; return get<0>(it1) < get<0>(it2);});

        AC_DEVICE(myQ, "post_sortTileListsKernel2", sortKeySrc, numTileListsSrc);
        AC_DEVICE(myQ, "post_sortTileListsKernel2", sortKeyDst, numTileListsDst);
        AC_DEVICE(myQ, "post_sortTileListsKernel2", tileListOrderSrc.ptr, numTileListsSrc);
        AC_DEVICE(myQ, "post_sortTileListsKernel2", tileListOrderDst.ptr, numTileListsDst);

//        myQ.wait();
//      }

      // Re-order tileListDepth using tileListOrderDst
      {
        int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
        int rangeSize = ((numTileListsDst - 1)/workGroupSize+1)*workGroupSize;

        AC_TAG("reOrderTileListDepth2");
        myQ.submit(
          [&](handler &cgh) {
          cgh.parallel_for<class reOrderTileListDepth_fw897e>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
            reOrderTileListDepth(numTileListsDst, tileListOrderDst.ptr, tileListDepthSrc.ptr, tileListDepthDst.ptr, item_ct1);
          });
        });
        AC_DEVICE(myQ, "post_reOrderTileListDepth2", tileListDepthDst.ptr, numTileListsDst);

      }

      // Local sort
      {
//        int workGroupSize = AVXSIZE
//        int rangeSize = ((numTileListsDst- 1)/workGroupSize+1)*workGroupSize;
//        myQ.submit(
//          [&](handler &cgh) {
//          sycl::accessor<typename BlockRadixSort::TempStorage, 0,
//                         sycl::access::mode::read_write,
//                         sycl::access::target::local>
//              tempStorage_acc_ct1(cgh);
//
//          cgh.parallel_for<class localSort_v9ds8f7>(
//            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
//            [=](nd_item<3> item_ct1) {
//              localSort<AVXSIZE>(numTileListsDst, begin_bit, num_bit, tileListDepthDst.ptr,
//                tileListOrderDst.ptr, item_ct1, tempStorage_acc_ct1.get_pointer());
//          });
//        }); //myQ.wait();

        AC_TAG("localSort");

//        auto first = oneapi::dpl::make_zip_iterator(tileListDepthDst.ptr, tileListOrderDst.ptr);
//        auto last = first + std::distance(sortKeyDst, sortKeyDst + numTileListsDst);
//        std::sort(oneapi::dpl::execution::make_device_policy(myQ), first, last,
//          [](const auto &it1, const auto &it2){using std::get; return get<0>(it1) > get<0>(it2);});


        AC_DEVICE(myQ, "pre_localSort", tileListDepthDst.ptr, numTileListsDst);
        AC_DEVICE(myQ, "pre_localSort", tileListOrderDst.ptr, numTileListsDst);
        {
          int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
          int rangeSize = ((numTileListsDst - 1)/workGroupSize+1)*workGroupSize;
          myQ.submit(
            [&](handler &cgh) {
            auto d_key = tileListDepthDst.ptr;
            auto d_val = tileListOrderDst.ptr;
            auto n = numTileListsDst; 
            auto begin_bit_ct = begin_bit;
            cgh.parallel_for<class localSort_pre>(
              nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
              [=](nd_item<3> item_ct1) {

                for (int i = item_ct1.get_global_id(2);i < n;i+=item_ct1.get_global_range(2))
                {
                  d_key[i] = {(i < n) ? ((d_key[i] >> begin_bit_ct) & 65535) : 0};
                  d_val[i] = {(i < n) ? d_val[i] : 0};
                }
            });
          }); //  myQ.wait();
        }
        {

          int workGroupSize = AVXSIZE;
          int rangeSize = ((numTileListsDst - 1)/workGroupSize+1)*workGroupSize;
          myQ.submit( [&](handler &cgh) {
            auto d_key = tileListDepthDst.ptr;
            auto d_val = tileListOrderDst.ptr;
            cgh.parallel_for<class localSortKernel>(
              nd_range<1>(range<1>(rangeSize), range<1>(workGroupSize)),
              [=](nd_item<1> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {

                auto sg = item_ct1.get_sub_group();
                int sid = sg.get_local_id();
                int gid = item_ct1.get_global_id(0);
                int tid = item_ct1.get_local_id(0);

                int tkey, tval;
                if(sid == 0) {
                  for(int i=gid; i<gid+AVXSIZE;i++){
                    for(int j=i+1; j<gid+AVXSIZE;j++){
                      if(d_key[i] < d_key[j]){ 
                        tkey = d_key[i]; d_key[i] = d_key[j]; d_key[j] = tkey;
                        tval = d_val[i]; d_val[i] = d_val[j]; d_val[j] = tval;
                      }
                    }
                  }
                } 
            });
          });
        }

//        AC_LOAD_DEVICE(myQ, "post_localSort", tileListDepthDst.ptr, numTileListsDst);
//        AC_LOAD_DEVICE(myQ, "post_localSort", tileListOrderDst.ptr, numTileListsDst);
        AC_DEVICE(myQ, "post_localSort", tileListDepthDst.ptr, numTileListsDst);
        AC_DEVICE(myQ, "post_localSort", tileListOrderDst.ptr, numTileListsDst);

//        myQ.wait();
        // No need to shift any more
        doShiftDown = false;
      }

    }
    // ----------------------------------------------------------------------------------------


  } // (doStreaming)
  else
  {
    // --------------------------------------------------------------------
    // Sort {tileListDepthSrc, tileListOrderSrc}[0 ... numTileListsSrc-1]
    //   => {tileListDepthDst, tileListOrderDst}[0 ... numTileListsSrc-1]
    // --------------------------------------------------------------------
//    if (numTileListsSrc <= SORTTILELISTSKERNEL_NUM_THREAD*SORTTILELISTSKERNEL_ITEMS_PER_THREAD)
//    {
      int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), SORTTILELISTSKERNEL_NUM_THREAD);
      int rangeSize = workGroupSize;
      {
#include "array_debug/ac_pre_sorttilelistskernel.h"
        size_t nSrc = numTileListsSrc;
        size_t nDst = numTileListsDst;
        int nDiff = nSrc-nDst;
        copy_DtoD(tileListDepthSrc.ptr, tileListDepthDst.ptr, numTileListsSrc, myQ);
        copy_DtoD(tileListOrderSrc.ptr, tileListOrderDst.ptr, numTileListsSrc, myQ);
        myQ.wait();
        auto first = oneapi::dpl::make_zip_iterator(tileListDepthDst.ptr, tileListOrderDst.ptr);
        auto last = first + std::distance(tileListDepthDst.ptr, tileListDepthDst.ptr+numTileListsSrc);
        std::sort(oneapi::dpl::execution::make_device_policy(myQ), first, last,
          [](const auto &it1, const auto &it2){using std::get; return get<0>(it1) > get<0>(it2);});
//        myQ.wait();

#include "array_debug/ac_post_sorttilelistskernel.h"


      }

//    }
//    else
//    {
//      // Long list, sort on multiple thread blocks
//      size_t size = 0;
//      dpcppCheck(cub::DeviceRadixSort::SortPairsDescending(NULL, size,
//        tileListDepthSrc.ptr, tileListDepthDst.ptr, tileListOrderSrc.ptr, tileListOrderDst.ptr,
//        numTileListsSrc, begin_bit, end_bit, myQ));
//      // Make sure tempStorage doesn't remain NULL
//      if (size == 0) size = 128;
//      reallocate_device<char>(&tempStorage, &tempStorageSize, size, 1.5f);
//      size = tempStorageSize;
//      dpcppCheck(cub::DeviceRadixSort::SortPairsDescending((void *)tempStorage, size,
//        tileListDepthSrc.ptr, tileListDepthDst.ptr, tileListOrderSrc.ptr, tileListOrderDst.ptr,
//        numTileListsSrc, begin_bit, end_bit, myQ));
//    }
  }

  // -----------------------------------------------------------------------------
  // Bit shift & mask tileListDepthDst such that only lower 16 bits are occupied
  // -----------------------------------------------------------------------------
  if (doShiftDown)
  {
    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 1024);
    int rangeSize = ((numTileListsDst-1)/workGroupSize+1)*workGroupSize;

    {
#include "array_debug/ac_pre_bitshifttilelistdepth.h"
      myQ.submit(
        [&](handler &cgh) {
          cgh.parallel_for<class bitshiftTileListDepth_1cd6a6>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) {
              bitshiftTileListDepth(numTileListsDst, begin_bit, tileListDepthDst.ptr, item_ct1);
            });
        }); //myQ.wait();
#include "array_debug/ac_post_bitshifttilelistdepth.h"
    }
  }

  // Allocate with +1 to include last term in the exclusive sum
  myQ.wait();
  reallocate_device<int>(&tileListPos, &tileListPosSize, numTileListsDst+1, OVERALLOC);
  clear_device_array(tileListPos, tileListPosSize, myQ); // temporary to comare CUDA baseline

  // --------------------------------------------------------------------
  // Compute itileList positions to store tileLists
  // ExclusiveSum(tileListDepthDst[0...numTileListsDst+1])
  // NOTE: tileListDepthDst[numTileListsDst] is not accessed
  //       since this is an exclusive sum. But with this trick,
  //       tileListPos[numTileListsDst] will contain the total number
  //       of tile lists
  // --------------------------------------------------------------------
  {
#include "array_debug/ac_pre_exclusivedcankernel.h"

    oneapi::dpl::exclusive_scan(oneapi::dpl::execution::make_device_policy(myQ), tileListDepthDst.ptr, tileListDepthDst.ptr+numTileListsDst+1, tileListPos, 0);
//    myQ.wait();

#include "array_debug/ac_post_exclusivedcankernel.h"
  }

  // --------------------------------------------------------------------
  // Re-package to
  // tileListsDst[0 ... numTileListsDst-1], tileJatomStartDst[0 ... numJtilesDst-1]
  // patchPairDst[]
  // tileJatomStartDst[]
  // tileExclsDst[0 ... numJtilesDst-1]
  // --------------------------------------------------------------------
  {
    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), AVXSIZE*REPACKTILELISTSKERNEL_NUM_WARP);
    int nwarp = REPACKTILELISTSKERNEL_NUM_WARP;
    int rangeSize = ((numTileListsDst-1)/nwarp+1)*workGroupSize;

#include "array_debug/ac_pre_repacktilelistskernel.h"
    {
      myQ.submit(
        [&](handler &cgh) {
          auto tileListPos2=tileListPos;
          auto jtiles2= (useJtiles) ? jtiles : NULL;
          auto tileListOrderDst_ptr=tileListOrderDst.ptr;
          auto tileListsSrc_ptr= (tileListsSrc.size) ? tileListsSrc.ptr : NULL;
          auto tileListsDst_ptr= (tileListsDst.size) ? tileListsDst.ptr : NULL;
          auto patchPairsSrc_ptr= (patchPairsSrc.size) ? patchPairsSrc.ptr : NULL;
          auto patchPairsDst_ptr= (patchPairsDst.size) ? patchPairsDst.ptr : NULL;
          auto tileJatomStartSrc_ptr= (tileJatomStartSrc.size) ? tileJatomStartSrc.ptr : NULL;
          auto tileJatomStartDst_ptr= (tileJatomStartDst.size) ? tileJatomStartDst.ptr : NULL;
          auto tileExclsSrc_ptr= (tileExclsSrc.size) ? tileExclsSrc.ptr : NULL;
          auto tileExclsDst_ptr= (tileExclsDst.size) ? tileExclsDst.ptr : NULL;


          cgh.parallel_for<class repackTileListsKernel_eb99b6>(
            nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
            [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {
              repackTileListsKernel( numTileListsDst, begin_bit, tileListPos2, tileListOrderDst_ptr, jtiles2, tileListsSrc_ptr, tileListsDst_ptr, patchPairsSrc_ptr, patchPairsDst_ptr, tileJatomStartSrc_ptr, tileJatomStartDst_ptr, tileExclsSrc_ptr, tileExclsDst_ptr, item_ct1);
            });
        }); //myQ.wait();
    }
#include "array_debug/ac_post_repacktilelistskernel.h"

  }

  // Count the number of tileLists that contribute to each patch
  if (doStreaming)
  {
    clear_device_array<int>(patchNumLists, numPatches, myQ);

    // Fill in patchNumLists[0...numPatches-1]
//    int nthread = 512;
/* DPCT_ORIG     int nblock = min(deviceCUDA->getMaxNumBlocks(),
 * (numTileListsDst-1)/nthread+1);*/
/* DPCT_ORIG     calcPatchNumLists <<< nblock, nthread, 0, myQ >>>
    (numTileListsDst, numPatches, tileListsDst.ptr, patchNumLists);*/
    int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), 512);
    int rangeSize = ((numTileListsDst-1)/workGroupSize+1)*workGroupSize;

    myQ.submit( [&](handler &cgh) {
      auto numPatches_ct1 = numPatches;
      auto patchNumLists_ct3 = patchNumLists;

      cgh.parallel_for<class updatePatchesKernel_1769b6>(
        nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
        [=](nd_item<3> item_ct1) {
 
        calcPatchNumLists(numTileListsDst, numPatches_ct1, tileListsDst.ptr, patchNumLists_ct3,item_ct1);
      });
    });

    // Use emptyPatches[numPatches] as the count variable
    clear_device_array<int>(&emptyPatches[numPatches], 1, myQ);

    // Fill in tileListsDst[0...numTileListsDst-1].patchNumLists
    // and find empty patches into emptyPatches[0 ... numEmptyPatches - 1]
/* DPCT_ORIG     setPatchNumLists_findEmptyPatches <<< nblock, nthread, 0,
   myQ >>> (numTileListsDst, tileListsDst.ptr, patchNumLists, numPatches,
   &emptyPatches[numPatches], emptyPatches);*/
    myQ.submit( [&](handler &cgh) {
      auto patchNumLists_ct2 = patchNumLists;
      auto numPatches_ct3 = numPatches;
      auto emptyPatches_numPatches_ct4 = &emptyPatches[numPatches];
      auto emptyPatches_ct5 = emptyPatches;

      cgh.parallel_for<class updatePatchesKernel_1769b6>(
        nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
        [=](nd_item<3> item_ct1) {
        setPatchNumLists_findEmptyPatches( numTileListsDst, tileListsDst.ptr, patchNumLists_ct2, numPatches_ct3, emptyPatches_numPatches_ct4, emptyPatches_ct5, item_ct1);
      });
    });
    

    // // Copy emptyPatches[0 ... numPatches] to host
    copy_DtoH<int>(emptyPatches, h_emptyPatches, numPatches+1, myQ);
myQ.wait();

    numEmptyPatches = h_emptyPatches[numPatches];
  }
}
//catch (exception const &exc) {
//  std::cerr << exc.what() << "EOE at File " << __FILE__ << ":" << __LINE__ << std::endl;
//  std::exit(1);
//}

//
// Re-sort tile lists after pairlist refinement. Can only be called after finishTileList() has finished copying
//
void DpcppTileListKernel::reSortTileLists(const bool doGBIS, queue myQ) {
  // Store previous number of active lists
  int numTileListsPrev = numTileLists;

  // Wait for finishTileList() to stop copying
  if (!tileListStatEventRecord)
    NAMD_die("DpcppTileListKernel::reSortTileLists, tileListStatEvent not recorded");
  tileListStatEvent.wait();

  // Get numTileLists, numTileListsGBIS, and numExcluded
  {
    numTileLists     = h_tileListStat->numTileLists;
    numTileListsGBIS = h_tileListStat->numTileListsGBIS;
    numExcluded      = h_tileListStat->numExcluded;
  }

  sortTileLists(true, 0, true,
    numTileListsPrev, numJtiles,
    PtrSize<TileList>(tileLists2, tileLists2Size), PtrSize<int>(tileJatomStart2, tileJatomStart2Size),
    PtrSize<unsigned int>(tileListDepth2, tileListDepth2Size), PtrSize<int>(tileListOrder2, tileListOrder2Size),
    PtrSize<PatchPairRecord>(NULL, 0), PtrSize<TileExcl>(tileExcls2, tileExcls2Size),
    numTileLists, numJtiles,
    PtrSize<TileList>(tileLists1, tileLists1Size), PtrSize<int>(tileJatomStart1, tileJatomStart1Size),
    PtrSize<unsigned int>(tileListDepth1, tileListDepth1Size), PtrSize<int>(tileListOrder1, tileListOrder1Size),
    PtrSize<PatchPairRecord>(NULL, 0), PtrSize<TileExcl>(tileExcls1, tileExcls1Size),
    myQ);

  // NOTE:
  // Only {tileList1, tileJatomStart1, tileExcl1} are used from here on,
  // the rest {tileListDepth1, tileListOrder1, patchPairs1} may be re-used by the GBIS sorting

  if (doGBIS) {
    // GBIS is used => produce a second tile list
    // GBIS tile list in {tileListGBIS, tileJatomStartGBIS, patchPairs1}
    myQ.wait();
    reallocate_device<TileList>(&tileListsGBIS, &tileListsGBISSize, numTileListsGBIS, OVERALLOC);
    reallocate_device<int>(&tileJatomStartGBIS, &tileJatomStartGBISSize, numJtiles, OVERALLOC);

    sortTileLists(true, 16, true,
      numTileListsPrev, numJtiles,
      PtrSize<TileList>(tileLists2, tileLists2Size), PtrSize<int>(tileJatomStart2, tileJatomStart2Size),
      PtrSize<unsigned int>(tileListDepth2, tileListDepth2Size), PtrSize<int>(tileListOrder2, tileListOrder2Size),
      PtrSize<PatchPairRecord>(patchPairs2, patchPairs2Size), PtrSize<TileExcl>(NULL, 0),
      numTileListsGBIS, numJtiles,
      PtrSize<TileList>(tileListsGBIS, tileListsGBISSize), PtrSize<int>(tileJatomStartGBIS, tileJatomStartGBISSize),
      PtrSize<unsigned int>(tileListDepth1, tileListDepth1Size), PtrSize<int>(tileListOrder1, tileListOrder1Size),
      PtrSize<PatchPairRecord>(patchPairs1, patchPairs1Size), PtrSize<TileExcl>(NULL, 0),
      myQ);
  }

  // Set active buffer to be 1
  setActiveBuffer(1);

}

void DpcppTileListKernel::setTileListVirialEnergyLength(int len) {
  if (len > tileListVirialEnergySize) {
    NAMD_die("DpcppTileListKernel::setTileListVirialEnergyLength, size overflow");
  }
  tileListVirialEnergyLength = len;
}

void DpcppTileListKernel::setTileListVirialEnergyGBISLength(int len) {
  if (len > tileListVirialEnergySize) {
    NAMD_die("DpcppTileListKernel::setTileListVirialEnergyGBISLength, size overflow");
  }
  tileListVirialEnergyGBISLength = len;
}


#endif // NAMD_DPCPP
