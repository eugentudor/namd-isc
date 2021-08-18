#ifndef DPCPPCOMPUTEPMEMGR_H
#define DPCPPCOMPUTEPMEMGR_H

#include <vector>

#include "PmeBase.h"
#include "PmeSolver.h"
#include "PmeSolverUtil.h"
#include "DpcppComputePmeMgr.decl.h"
#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>
#endif

#ifdef NAMD_DPCPP
class DpcppComputePme;

//
// Base class for thread safe atom storage
//
class PmeAtomStorage {
public:
  PmeAtomStorage(const bool useIndex) : useIndex(useIndex) {
    numAtoms = 0;
    atomCapacity = 0;
    atom = NULL;
    atomIndexCapacity = 0;
    atomIndex = NULL;
    overflowStart = 0;
    overflowEnd = 0;
    overflowAtomCapacity = 0;
    overflowAtom = NULL;
    overflowAtomIndexCapacity = 0;
    overflowAtomIndex = NULL;
    lock_ = CmiCreateLock();
  }
  virtual ~PmeAtomStorage() {
    CmiDestroyLock(lock_);
  }

  int addAtoms(const int natom, const DpcppAtom* src) {
    return addAtoms_(natom, src, NULL);
  }

  int addAtomsWithIndex(const int natom, const DpcppAtom* src, const int* index) {
    return addAtoms_(natom, src, index);
  }

  // Finish up, must be called after "done" is returned by addAtoms.
  // Only the last thread that gets the "done" signal from addAtoms can enter here.
  void finish() {
    if (overflowEnd-overflowStart > 0) {
      resize_((void **)&atom, numAtoms, atomCapacity, sizeof(DpcppAtom));
      if (useIndex) resize_((void **)&atomIndex, numAtoms, atomIndexCapacity, sizeof(int));
      memcpy_(atom+overflowStart, overflowAtom, (overflowEnd - overflowStart)*sizeof(DpcppAtom));
      if (useIndex) memcpy_(atomIndex+overflowStart, overflowAtomIndex, (overflowEnd - overflowStart)*sizeof(int));
      overflowStart = 0;
      overflowEnd = 0;
    }
  }

  // Clear and reset storage to initial stage.
  // Only the last thread that gets the "done" signal from addAtoms can enter here.
  void clear() {
    patchPos.clear();
    numAtoms = 0;    
  }

  // Return pointer to atom data
  DpcppAtom* getAtoms() {
    return atom;
  }

  // Return pointer to patch positions
  int* getPatchPos() {
    return patchPos.data();
  }

  int getNumPatches() {
    return patchPos.size();
  }

  int getNumAtoms() {
    return numAtoms;
  }

  int* getAtomIndex() {
    if (!useIndex)
      NAMD_bug("PmeAtomStorage::getAtomIndex, no indexing enabled");
    return atomIndex;
  }

protected:
  // Atom array
  DpcppAtom* atom;
  // Atom index array
  int* atomIndex;
  // Overflow atom array
  DpcppAtom* overflowAtom;
  // Overflow atom index array
  int* overflowAtomIndex;

private:
  // If true, uses indexed atom arrays
  const bool useIndex;
  // Node lock
  CmiNodeLock lock_;
  // Data overflow
  int overflowAtomCapacity;
  int overflowAtomIndexCapacity;
  int overflowStart;
  int overflowEnd;
  // Number of atoms currently in storage
  int numAtoms;
  // Atom patch position
  std::vector<int> patchPos;
  // Atom array capacity
  int atomCapacity;
  // Atom index array capacity
  int atomIndexCapacity;

  // Resize array with 1.5x extra storage
  void resize_(void **array, int sizeRequested, int& arrayCapacity, const int sizeofType) {
    // If array is not NULL and has enough capacity => we have nothing to do
    if (*array != NULL && arrayCapacity >= sizeRequested) return;

    // Otherwise, allocate new array
    int newArrayCapacity = (int)(sizeRequested*1.5);
    void* newArray = alloc_(sizeofType*newArrayCapacity);

    if (*array != NULL) {
      // We have old array => copy contents to new array
      memcpy_(newArray, *array, arrayCapacity*sizeofType);
      // De-allocate old array
      dealloc_(*array);
    }

    // Set new capacity and array pointer
    arrayCapacity = newArrayCapacity;
    *array = newArray;
  }

  virtual void memcpy_(void *dst, const void* src, const int size) {
    memcpy(dst, src, size);
  }

  virtual void copyWithIndex_(DpcppAtom* dst, const DpcppAtom* src, const int natom, const int* indexSrc) {
    for (int i=0;i < natom;i++) dst[i] = src[indexSrc[i]];
  }

  // Allocate array of size bytes
  virtual void* alloc_(const int size)=0;

  // Deallocate array
  virtual void dealloc_(void *p)=0;

  // Add atoms in thread-safe manner.
  // Returns the patch index where the atoms were added
  int addAtoms_(const int natom, const DpcppAtom* src, const int* index) {
    CmiLock(lock_);
    // Accumulate position for patches:
    // atoms for patch i are in the range [ patchPos[i-1], patchPos[i]-1 ]
    int patchInd = patchPos.size();
    int ppos = (patchInd == 0) ? natom : patchPos[patchInd-1] + natom;
    patchPos.push_back(ppos);
    int pos = numAtoms;
    bool overflow = false;
    numAtoms += natom;
    // Check for overflow
    if (numAtoms > atomCapacity || (useIndex && numAtoms > atomIndexCapacity)) {
      // number of atoms exceeds capacity, store into overflow buffer
      // Note: storing to overflow should be very infrequent, most likely only
      // in the initial call
      if (overflowEnd-overflowStart == 0) {
        overflowStart = pos;
        overflowEnd = pos;
      }
      overflowEnd += natom;
      if (overflowEnd-overflowStart > overflowAtomCapacity) {
        resize_((void **)&overflowAtom, overflowEnd-overflowStart, overflowAtomCapacity, sizeof(DpcppAtom));
      }
      if (useIndex && overflowEnd-overflowStart > overflowAtomIndexCapacity) {
        resize_((void **)&overflowAtomIndex, overflowEnd-overflowStart, overflowAtomIndexCapacity, sizeof(int));
      }
      if (index != NULL) {
        if (useIndex) memcpy_(overflowAtomIndex+overflowEnd-overflowStart-natom, index, natom*sizeof(int));
        copyWithIndex_(overflowAtom+overflowEnd-overflowStart-natom, src, natom, index);
      } else {
        memcpy_(overflowAtom+overflowEnd-overflowStart-natom, src, natom*sizeof(DpcppAtom));
      }
      overflow = true;
    }
    CmiUnlock(lock_);
    // If no overflow, copy to final position
    if (!overflow) {
      if (index != NULL) {
        if (useIndex) memcpy_(atomIndex+pos, index, natom*sizeof(int));
        copyWithIndex_(atom+pos, src, natom, index);
      } else {
        memcpy_(atom+pos, src, natom*sizeof(DpcppAtom));
      }
    }
    return patchInd;
  }

};

class PmeAtomMsg : public CMessage_PmeAtomMsg {
public:
  DpcppAtom *atoms;
  int numAtoms;
  int i, j;
  DpcppComputePme* compute;
  int pe;
  bool doEnergy, doVirial;
  Lattice lattice;
  // int miny, minz;
};

class PmeForceMsg : public CMessage_PmeForceMsg {
public:
  DpcppForce *force;
  int pe;
  int numAtoms;
  int numStrayAtoms;
  bool zeroCopy;
  DpcppComputePme* compute;
};

class PmeLaunchMsg : public CMessage_PmeLaunchMsg {
public:
  DpcppForce* force;
  int natom;
  int pe;
  DpcppComputePme* compute;
};

class RegisterPatchMsg : public CMessage_RegisterPatchMsg {
public:
  int i, j;
};

class NumDevicesMsg : public CMessage_NumDevicesMsg {
public:
  NumDevicesMsg(int numDevices) : numDevices(numDevices) {}
  int numDevices;
};

class PmeAtomPencilMsg : public CMessage_PmeAtomPencilMsg {
public:
  DpcppAtom* atoms;
  int numAtoms;
  int y, z;
  int srcY, srcZ;
  bool doEnergy, doVirial;
  Lattice lattice;
};

class PmeForcePencilMsg : public CMessage_PmeForcePencilMsg {
public:
  DpcppForce* force;
  int numAtoms;
  int y, z;
  int srcY, srcZ;
};

class CProxy_DpcppComputePmeDevice;
class RecvDeviceMsg : public CMessage_RecvDeviceMsg {
public:
  CProxy_DpcppComputePmeDevice* dev;
  int numDevicesMax;
};

class PmeAtomFiler : public CBase_PmeAtomFiler {
public:
  PmeAtomFiler();
  PmeAtomFiler(CkMigrateMessage *);
  ~PmeAtomFiler();
  void fileAtoms(const int numAtoms, const DpcppAtom* atoms, Lattice &lattice, const PmeGrid &pmeGrid,
    const int pencilIndexY, const int pencilIndexZ, const int ylo, const int yhi, const int zlo, const int zhi);
  // static inline int yBlock(int p) {return p % 3;}
  // static inline int zBlock(int p) {return p / 3;}
  int getNumAtoms(int p) {return pencilSize[p];}
  int* getAtomIndex(int p) {return pencil[p];}
private:
  // 9 Pencils + 1 Stay atom pencil
  int pencilSize[9+1];
  int pencilCapacity[9+1];
  int* pencil[9+1];
};


class CProxy_DpcppComputePmeMgr;
class DpcppComputePmeDevice : public CBase_DpcppComputePmeDevice {
public:
  // DpcppComputePmeDevice_SDAG_CODE;
  DpcppComputePmeDevice();
  DpcppComputePmeDevice(CkMigrateMessage *m);
  ~DpcppComputePmeDevice();
  void initialize(PmeGrid& pmeGrid_in, int pencilIndexY_in, int pencilIndexZ_in,
    int deviceID_in, int pmePencilType_in, CProxy_DpcppComputePmeMgr mgrProxy_in,
    CProxy_PmeAtomFiler pmeAtomFiler_in);
  int getDeviceID();
  sycl::queue& getStream();
  CProxy_DpcppComputePmeMgr getMgrProxy();
  void setPencilProxy(CProxy_DpcppPmePencilXYZ pmePencilXYZ_in);
  void setPencilProxy(CProxy_DpcppPmePencilXY pmePencilXY_in);
  void setPencilProxy(CProxy_DpcppPmePencilX pmePencilX_in);
  void activate_pencils();
  void initializePatches(int numHomePatches_in);
  void registerNeighbor();
  void recvAtoms(PmeAtomMsg *msg);
  void sendAtomsToNeighbors();
  void sendAtomsToNeighbor(int y, int z, int atomIval);
  void recvAtomsFromNeighbor(PmeAtomPencilMsg *msg);
  void registerRecvAtomsFromNeighbor();
  void spreadCharge();
  void gatherForce();
  void gatherForceDone();
  void sendForcesToNeighbors();
  void recvForcesFromNeighbor(PmeForcePencilMsg *msg);
  void mergeForcesOnPatch(int homePatchIndex);
  void sendForcesToPatch(PmeForceMsg *forceMsg);

  void gatherForceDoneSubset(int first, int last);

private:
  // Store updated lattice
  Lattice lattice;
  // Store virial and energy flags
  bool doVirial, doEnergy;
  // PME grid definiton
  PmeGrid pmeGrid;
  // PME pencil type
  int pmePencilType;
  // Neighboring pencil bounds, [-1,1]
  int ylo, yhi, zlo, zhi;
  // Size of the neighboring pencil grid, maximum value 3. yNBlocks = yhi - ylo + 1
  int yNBlocks, zNBlocks;
  // Number of home patches for this device
  int numHomePatches;
  // Pencil location for this device
  int pencilIndexY, pencilIndexZ;

  // Number of neighbors expected to provide atoms including self
  int numNeighborsExpected;

  // Number of stray atoms
  int numStrayAtoms;

  // Node locks
  CmiNodeLock lock_numHomePatchesMerged;
  CmiNodeLock lock_numPencils;
  CmiNodeLock lock_numNeighborsRecv;
  CmiNodeLock lock_recvAtoms;

  int atomI, forceI;

  //----------------------------------------------------------------------------------
  // Book keeping
  // NOTE: We keep two copies of pmeAtomStorage and homePatchIndexList so that forces can be
  //       merged while next patch of atoms is already being received
  //----------------------------------------------------------------------------------
  // Storage for each pencil on the yNBlocks x zNBlocks grid
  std::vector< PmeAtomStorage* > pmeAtomStorage[2];
  std::vector<bool> pmeAtomStorageAllocatedHere;

  // Size numHomePatches:
  // Tells how many pencils have contributed to home patch
  std::vector<int> numPencils[2];

  // Pencil location
  struct PencilLocation {
    // Pencil index
    int pp;
    // Patch location in the pencil
    int pencilPatchIndex;
    PencilLocation(int pp, int pencilPatchIndex) : pp(pp), pencilPatchIndex(pencilPatchIndex) {}
  };

  // Size numHomePatches
  std::vector< std::vector<PencilLocation> > plList[2];

  // Size numHomePatches
  std::vector< PmeForceMsg* > homePatchForceMsgs[2];

  // // Size numHomePatches
  // std::vector<int> numHomeAtoms[2];

  std::vector< std::vector<int> > homePatchIndexList[2];

  // Number of neighbors from which we have received atoms
  int numNeighborsRecv;

  // Number of home patches we have received atom from
  int numHomePatchesRecv;

  // Number of home patches we have merged forces for
  int numHomePatchesMerged;

  // Size yNBlocks*zNBlocks
  std::vector< PmeForcePencilMsg* > neighborForcePencilMsgs;
  // std::vector< PmeForcePencil > neighborForcePencils;

  // Size yNBlocks*zNBlocks
  std::vector<int> neighborPatchIndex;
  //----------------------------------------------------------------------------------

  // DPCPP queue
  sycl::queue stream;
  bool streamCreated;
  // Device ID
  int deviceID;
  // Charge spreading and force gathering
  PmeRealSpaceCompute* pmeRealSpaceCompute;
  // Host memory force array
  int forceCapacity;
  DpcppForce* force;

  // Proxy for the manager
  CProxy_DpcppComputePmeMgr mgrProxy;

  // Atom filer proxy
  CProxy_PmeAtomFiler pmeAtomFiler;

  // Pencil proxy
  CProxy_DpcppPmePencilXYZ pmePencilXYZ;
  CProxy_DpcppPmePencilXY pmePencilXY;
  CProxy_DpcppPmePencilX pmePencilX;

  // For event tracing
  double beforeWalltime;
};

class DpcppComputePmeMgr : public CBase_DpcppComputePmeMgr {
public:
  DpcppComputePmeMgr_SDAG_CODE;
	DpcppComputePmeMgr();
  DpcppComputePmeMgr(CkMigrateMessage *);
	~DpcppComputePmeMgr();
  void setupPencils();
  void initialize(CkQdMsg *msg);
  void initialize_pencils(CkQdMsg *msg);
  void activate_pencils(CkQdMsg *msg);
  PmeGrid getPmeGrid() {return pmeGrid;}
  int getNode(int i, int j);
  int getDevice(int i, int j);
  int getDevicePencilY(int i, int j);
  int getDevicePencilZ(int i, int j);
  int getDeviceIDPencilX(int i, int j);
  int getDeviceIDPencilY(int i, int j);
  int getDeviceIDPencilZ(int i, int j);
  void recvPencils(CProxy_DpcppPmePencilXYZ xyz);
  void recvPencils(CProxy_DpcppPmePencilXY xy, CProxy_DpcppPmePencilZ z);
  void recvPencils(CProxy_DpcppPmePencilX x, CProxy_DpcppPmePencilY y, CProxy_DpcppPmePencilZ z);

  void createDevicesAndAtomFiler();
  void recvDevices(RecvDeviceMsg* msg);
  void recvAtomFiler(CProxy_PmeAtomFiler filer);
  void skip();
  void recvAtoms(PmeAtomMsg *msg);
  void getHomePencil(PatchID patchID, int& homey, int& homez);
  int getHomeNode(PatchID patchID);

  bool isPmePe(int pe);
  bool isPmeNode(int node);
  bool isPmeDevice(int deviceID);

  static DpcppComputePmeMgr* Object() {
    CProxy_DpcppComputePmeMgr mgrProxy(CkpvAccess(BOCclass_group).dpcppComputePmeMgr);
    return mgrProxy.ckLocalBranch();    
  }
protected:

private:
  void restrictToMaxPMEPencils();

  // ---------------------------------------------
  // For .ci file
  // Counter for determining numDevicesMax
  int numNodesContributed;
  int numDevicesMax;

  // Number of home patches for each device on this manager
  std::vector<int> numHomePatchesList;

  // Counter for "registerPatchDone"
  int numTotalPatches;
  // ---------------------------------------------

  // PME pencil type: 1=column, 2=slab, 3=box
  int pmePencilType;

	PmeGrid pmeGrid;

  // Number of DPCPP devices on this node that are used for PME computation
  int numDevices;

  std::vector<int> xPes;
  std::vector<int> yPes;
  std::vector<int> zPes;

  // List of pencil coordinates (i,j) for each device held by this node
  struct IJ {
    int i, j;
  };
  std::vector<IJ> ijPencilX;
  std::vector<IJ> ijPencilY;
  std::vector<IJ> ijPencilZ;

  struct NodeDevice {
    int node;
    int device;
  };
  std::vector<NodeDevice> nodeDeviceList;

  // Atom filer proxy
  CProxy_PmeAtomFiler pmeAtomFiler;

  // Device proxies
  std::vector<CProxy_DpcppComputePmeDevice> deviceProxy;

  // Extra devices
  struct ExtraDevice {
    int deviceID;
    sycl::queue stream;
  };
  std::vector<ExtraDevice> extraDevices;

  // Pencil proxies
  CProxy_DpcppPmePencilXYZ pmePencilXYZ;
  CProxy_DpcppPmePencilXY pmePencilXY;
  CProxy_DpcppPmePencilX pmePencilX;
  CProxy_DpcppPmePencilY pmePencilY;
  CProxy_DpcppPmePencilZ pmePencilZ;

};
#else // NAMD_DPCPP
class DpcppComputePmeMgr : public CBase_DpcppComputePmeMgr {
};
#endif // NAMD_DPCPP

#endif // DPCPPCOMPUTEPMEMGR_H
