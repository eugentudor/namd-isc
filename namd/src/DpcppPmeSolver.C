#include "Node.h"
#include "Priorities.h"
#include "ComputeNonbondedUtil.h"
#include "DpcppPmeSolverUtil.h"
#include "DpcppComputePmeMgr.h"
#include "DpcppComputePmeMgr.decl.h"
#include "DpcppPmeSolver.h"
#include "DpcppDevice.h"

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>

#ifdef WIN32
#define __thread __declspec(thread)
#endif
extern __thread DpcppDevice *dpcppDevice;
//#define DISABLE_P2P

void DpcppPmePencilXYZ::initialize(DpcppPmeXYZInitMsg *msg) {
  pmeGrid = msg->pmeGrid;
  delete msg;
}

//
// DPC++ specific initialization
//
void DpcppPmePencilXYZ::initializeDevice(InitDeviceMsg *msg) {
  // Store device proxy
  deviceProxy = msg->deviceProxy;
  delete msg;
  int deviceID = deviceProxy.ckLocalBranch()->getDeviceID();
  sycl::queue *stream = &(deviceProxy.ckLocalBranch()->getStream());
  CProxy_DpcppComputePmeMgr mgrProxy = deviceProxy.ckLocalBranch()->getMgrProxy();
  // Setup fftCompute and pmeKSpaceCompute
  fftCompute = new DpcppFFTCompute(deviceID, stream);
  pmeKSpaceCompute = new DpcppPmeKSpaceCompute(pmeGrid, Perm_cX_Y_Z, 0, 0, 
    ComputeNonbondedUtil::ewaldcof, deviceID, stream);
}

void DpcppPmePencilXYZ::backwardDone() {
  deviceProxy[CkMyNode()].gatherForce();
  ((DpcppPmeKSpaceCompute *)pmeKSpaceCompute)->energyAndVirialSetCallback(this);

  // ((DpcppPmeKSpaceCompute *)pmeKSpaceCompute)->waitEnergyAndVirial();
  // submitReductions();
  // deviceProxy[CkMyNode()].gatherForce();
}

void DpcppPmePencilXYZ::energyAndVirialDone() {
  submitReductions();
  // deviceProxy[CkMyNode()].gatherForce();
}

//###########################################################################
//###########################################################################
//###########################################################################

void DpcppPmePencilXY::initialize(DpcppPmeXYInitMsg *msg) {
  pmeGrid = msg->pmeGrid;
  pmePencilZ = msg->pmePencilZ;
  zMap = msg->zMap;

  delete msg;

  initBlockSizes();
}

DpcppPmePencilXY::~DpcppPmePencilXY() {
  // No need to destroy DPC++ events
}

//
// DPC++ specific initialization
//
void DpcppPmePencilXY::initializeDevice(InitDeviceMsg *msg) try {
  // Store device proxy
  deviceProxy = msg->deviceProxy;
  delete msg;
  deviceID = deviceProxy.ckLocalBranch()->getDeviceID();
  stream = &(deviceProxy.ckLocalBranch()->getStream());
  CProxy_DpcppComputePmeMgr mgrProxy = deviceProxy.ckLocalBranch()->getMgrProxy();
  // Setup fftCompute and pmeKSpaceCompute
  fftCompute = new DpcppFFTCompute(deviceID, stream);
  pmeTranspose = new DpcppPmeTranspose(pmeGrid, Perm_cX_Y_Z, 0, thisIndex.z, deviceID, stream);  

  deviceBuffers.resize(pmeGrid.xBlocks, DeviceBuffer(-1, false, NULL));
  numDeviceBuffers = 0;

  // Create event. NOTE: Events are tied to devices
  // Event creation is redundant in DPC++
  dpcppDevice->setDeviceID(deviceID);
  eventCreated = true;

/*
  bool useMultiGPUfft = true;
  bool allDeviceOnSameNode = true;
  for (int x=0;x < pmeGrid.xBlocks;x++) {
    int pe = zMap.ckLocalBranch()->procNum(0, CkArrayIndex3D(x,0,0));
    allDeviceOnSameNode &= (CkNodeOf(pe) == CkMyNode());
  }

  if (useMultiGPUfft && allDeviceOnSameNode && pmeGrid.xBlocks > 1) {



  } else {
*/

  for (int x=0;x < pmeGrid.xBlocks;x++) {
    int pe = zMap.ckLocalBranch()->procNum(0, CkArrayIndex3D(x,0,0));
    if (CkNodeOf(pe) == CkMyNode()) {
      // Get device ID on a device on this node
      int deviceID0 = mgrProxy.ckLocalBranch()->getDeviceIDPencilZ(x, 0);
      // Check for Peer-to-Peer access
      int canAccessPeer = 0;
      if (deviceID != deviceID0) {
        dpcppDevice->setDeviceID(deviceID);
        // TODO: Peer GPU access disabled
        //cudaCheck(cudaDeviceCanAccessPeer(&canAccessPeer, deviceID, deviceID0));
#ifdef DISABLE_P2P
        canAccessPeer = 0;
#endif
        if (canAccessPeer) {
          unsigned int flags = 0;
          // TODO: Peer GPU access disabled
          //cudaCheck(cudaDeviceEnablePeerAccess(deviceID0, flags));
          // fprintf(stderr, "device %d can access device %d\n", deviceID, deviceID0);
        }
      }
      numDeviceBuffers++;
      deviceBuffers[x] = DeviceBuffer(deviceID0, canAccessPeer, NULL);
      pmePencilZ(x,0,0).getDeviceBuffer(thisIndex.z, (deviceID0 == deviceID) || canAccessPeer, thisProxy);
    }
  }

  // }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// DPC++ specific start
//
void DpcppPmePencilXY::start(const CkCallback &cb) {
  thisProxy[thisIndex].recvDeviceBuffers(cb);
}

void DpcppPmePencilXY::setDeviceBuffers() {
  std::vector<sycl::float2*> dataPtrs(pmeGrid.xBlocks, (sycl::float2*)0);
  for (int x=0;x < pmeGrid.xBlocks;x++) {
    if (deviceBuffers[x].data != NULL) {
      if (deviceBuffers[x].deviceID == deviceID || deviceBuffers[x].isPeerDevice) {
        // Device buffer on same device => directly transpose into destination pencil
        dataPtrs[x] = deviceBuffers[x].data;
        // Otherwise, when device buffer on different device on same node => transpose locally and then 
        // use cudaMemcpy3DPeerAsync to perform the copying
      }
    }
  }
  ((DpcppPmeTranspose *)pmeTranspose)->setDataPtrsZXY(dataPtrs, (sycl::float2 *)fftCompute->getDataDst());
}

sycl::float2 *DpcppPmePencilXY::getData(const int i, const bool sameDevice) {
  sycl::float2 *data;
#ifndef P2P_ENABLE_3D
  if (sameDevice) {
    int i0, i1, j0, j1, k0, k1;
    getBlockDim(pmeGrid, Perm_cX_Y_Z, i, 0, 0, i0, i1, j0, j1, k0, k1);
    data = (sycl::float2 *)fftCompute->getDataDst() + i0;
  } else {
    data = ((DpcppPmeTranspose *)pmeTranspose)->getBuffer(i);
  }
#else
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, Perm_cX_Y_Z, i, 0, 0, i0, i1, j0, j1, k0, k1);
  data = (sycl::float2 *)fftCompute->getDataDst() + i0;
#endif
  return data;
}

void DpcppPmePencilXY::backwardDone() {
  deviceProxy[CkMyNode()].gatherForce();
}

void DpcppPmePencilXY::forwardDone() try {
  // Transpose locally
  pmeTranspose->transposeXYZtoZXY((sycl::float2 *)fftCompute->getDataDst());

  // Direct Device-To-Device communication within node
  if (numDeviceBuffers > 0) {
    // Copy data
    for (int x=0;x < pmeGrid.xBlocks;x++) {
      if (deviceBuffers[x].data != NULL) {
        if (deviceBuffers[x].deviceID != deviceID && !deviceBuffers[x].isPeerDevice) {
          ((DpcppPmeTranspose *)pmeTranspose)->copyDataToPeerDeviceZXY(x, deviceBuffers[x].deviceID,
            Perm_Z_cX_Y, deviceBuffers[x].data);
        }
      }
    }
    // Record event for this pencil
    event = stream->single_task<class DpcppPmePencilXY_empty_task>([=](){});
    // Send empty message
    for (int x=0;x < pmeGrid.xBlocks;x++) {
      if (deviceBuffers[x].data != NULL) {
        PmeBlockMsg* msg = new (0, PRIORITY_SIZE) PmeBlockMsg();
        msg->dataSize = 0;
        msg->x = x;
        msg->y = thisIndex.y;
        msg->z = thisIndex.z;
        msg->doEnergy = doEnergy;
        msg->doVirial = doVirial;
        msg->lattice  = lattice;
        msg->numStrayAtoms = numStrayAtoms;
        pmePencilZ(x,0,0).recvBlock(msg);
      }
    }
  }

  // Copy-Via-Host communication
  for (int x=0;x < pmeGrid.xBlocks;x++) {
    if (deviceBuffers[x].data == NULL) {
      PmeBlockMsg* msg = new (blockSizes[x], PRIORITY_SIZE) PmeBlockMsg();
      msg->dataSize = blockSizes[x];
      msg->x = x;
      msg->y = thisIndex.y;
      msg->z = thisIndex.z;
      msg->doEnergy = doEnergy;
      msg->doVirial = doVirial;
      msg->lattice  = lattice;
      msg->numStrayAtoms = numStrayAtoms;
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToHost(x, msg->data, msg->dataSize);
      ((DpcppPmeTranspose *)pmeTranspose)->waitStreamSynchronize();
      pmePencilZ(x,0,0).recvBlock(msg);
    }
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmePencilXY::recvDataFromZ(PmeBlockMsg *msg) {
  if (msg->dataSize != 0) {
    // Buffer is coming from a different node
    ((DpcppPmeTranspose *)pmeTranspose)->copyDataHostToDevice(msg->x, msg->data, (sycl::float2 *)fftCompute->getDataDst());
  } else {
    // Buffer is coming from the same node
    // Wait for event that was recorded on the sending pencil
    // device ID = deviceBuffers[msg->x].deviceID
    // event     = deviceBuffers[msg->x].event
    //cudaCheck(cudaStreamWaitEvent(stream, deviceBuffers[msg->x].event, 0));
    // TODO: No equivalent in SYCL for cudaStreamWaitEvent
    deviceBuffers[msg->x].event.wait();
#ifndef P2P_ENABLE_3D
    if (deviceBuffers[msg->x].data != NULL && deviceBuffers[msg->x].deviceID != deviceID && !deviceBuffers[msg->x].isPeerDevice) {
      // Data is in temporary device buffer, copy it into final fft-buffer
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToDevice(msg->x, (sycl::float2 *)fftCompute->getDataDst());
    }
#endif
  }
  delete msg;
}

//###########################################################################
//###########################################################################
//###########################################################################

void DpcppPmePencilX::initialize(DpcppPmeXInitMsg *msg) {
  pmeGrid = msg->pmeGrid;
  pmePencilY = msg->pmePencilY;
  yMap = msg->yMap;

  delete msg;

  initBlockSizes();

}

DpcppPmePencilX::~DpcppPmePencilX() {
  // No need to destroy DPC++ events
}

//
// DPC++ specific initialization
//
void DpcppPmePencilX::initializeDevice(InitDeviceMsg *msg) try {
  // Store device proxy
  deviceProxy = msg->deviceProxy;
  delete msg;
  deviceID = deviceProxy.ckLocalBranch()->getDeviceID();
  stream = &(deviceProxy.ckLocalBranch()->getStream());
  CProxy_DpcppComputePmeMgr mgrProxy = deviceProxy.ckLocalBranch()->getMgrProxy();
  // Setup fftCompute and pmeKSpaceCompute
  fftCompute = new DpcppFFTCompute(deviceID, stream);
  pmeTranspose = new DpcppPmeTranspose(pmeGrid, Perm_cX_Y_Z, thisIndex.y, thisIndex.z, deviceID, stream);  

  // Create event. NOTE: Events are tied to devices
  // Event creation is redundant in DPC++
  dpcppDevice->setDeviceID(deviceID);
  eventCreated = true;

  deviceBuffers.resize(pmeGrid.xBlocks, DeviceBuffer(-1, false, NULL));
  numDeviceBuffers = 0;

  for (int x=0;x < pmeGrid.xBlocks;x++) {
    int pe = yMap.ckLocalBranch()->procNum(0, CkArrayIndex3D(x,0,thisIndex.z));
    if (CkNodeOf(pe) == CkMyNode()) {
      int deviceID0 = mgrProxy.ckLocalBranch()->getDeviceIDPencilY(x, thisIndex.z);
      numDeviceBuffers++;
      deviceBuffers[x] = DeviceBuffer(deviceID0, false, NULL);
      pmePencilY(x,0,thisIndex.z).getDeviceBuffer(thisIndex.y, (deviceID0 == deviceID), thisProxy);
    }
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// DPC++ specific start
//
void DpcppPmePencilX::start(const CkCallback &cb) {
  thisProxy[thisIndex].recvDeviceBuffers(cb);
}

//
// Setup direct device buffers
//
void DpcppPmePencilX::setDeviceBuffers() {
  std::vector<sycl::float2*> dataPtrs(pmeGrid.xBlocks, (sycl::float2*)0);
  for (int x=0;x < pmeGrid.xBlocks;x++) {
    if (deviceBuffers[x].data != NULL) {
      if (deviceBuffers[x].deviceID == deviceID) {
        // Device buffer on same device => directly transpose into destination pencil
        dataPtrs[x] = deviceBuffers[x].data;
        // Otherwise, when device buffer on different device on same node => transpose locally and then 
        // use cudaMemcpy3DPeerAsync to perform the copying
      }
    }
  }
  ((DpcppPmeTranspose *)pmeTranspose)->setDataPtrsYZX(dataPtrs, (sycl::float2 *)fftCompute->getDataDst());
}

sycl::float2 *DpcppPmePencilX::getData(const int i, const bool sameDevice) {
  sycl::float2 *data;
#ifndef P2P_ENABLE_3D
  if (sameDevice) {
    int i0, i1, j0, j1, k0, k1;
    getBlockDim(pmeGrid, Perm_cX_Y_Z, i, 0, 0, i0, i1, j0, j1, k0, k1);
    data = (sycl::float2 *)fftCompute->getDataDst() + i0;
  } else {
    data = ((DpcppPmeTranspose *)pmeTranspose)->getBuffer(i);
  }
#else
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, Perm_cX_Y_Z, i, 0, 0, i0, i1, j0, j1, k0, k1);
  data = (sycl::float2 *)fftCompute->getDataDst() + i0;
#endif
  return data;
}

void DpcppPmePencilX::backwardDone() {
  deviceProxy[CkMyNode()].gatherForce();
}

void DpcppPmePencilX::forwardDone() try {
  if (pmeTranspose == NULL)
    NAMD_bug("DpcppPmePencilX::forwardDone, pmeTranspose not initialized");
  if (blockSizes.size() == 0)
    NAMD_bug("DpcppPmePencilX::forwardDone, blockSizes not initialized");
  // Transpose locally
  pmeTranspose->transposeXYZtoYZX((sycl::float2 *)fftCompute->getDataDst());

  // Send data to y-pencils that share the same z-coordinate. There are pmeGrid.xBlocks of them
  // Direct-Device-To-Device communication
  if (numDeviceBuffers > 0) {
    // Copy data
    for (int x=0;x < pmeGrid.xBlocks;x++) {
      if (deviceBuffers[x].data != NULL) {
        if (deviceBuffers[x].deviceID != deviceID) {
          ((DpcppPmeTranspose *)pmeTranspose)->copyDataToPeerDeviceYZX(x, deviceBuffers[x].deviceID,
            Perm_Y_Z_cX, deviceBuffers[x].data);
        }
      }
    }
    // Record event for this pencil
    event = stream->single_task<class DpcppPmePencilX_empty_task>([=](){});
    // Send empty messages
    for (int x=0;x < pmeGrid.xBlocks;x++) {
      if (deviceBuffers[x].data != NULL) {
        PmeBlockMsg* msg = new (0, PRIORITY_SIZE) PmeBlockMsg();
        msg->dataSize = 0;
        msg->x = x;
        msg->y = thisIndex.y;
        msg->z = thisIndex.z;
        msg->doEnergy = doEnergy;
        msg->doVirial = doVirial;
        msg->lattice  = lattice;
        msg->numStrayAtoms = numStrayAtoms;
        pmePencilY(x,0,thisIndex.z).recvBlock(msg);     
      }
    }
  }

  // Copy-To-Host communication
  for (int x=0;x < pmeGrid.xBlocks;x++) {
    if (deviceBuffers[x].data == NULL) {
      PmeBlockMsg* msg = new (blockSizes[x], PRIORITY_SIZE) PmeBlockMsg();
      msg->dataSize = blockSizes[x];
      msg->x = x;
      msg->y = thisIndex.y;
      msg->z = thisIndex.z;
      msg->doEnergy = doEnergy;
      msg->doVirial = doVirial;
      msg->lattice  = lattice;
      msg->numStrayAtoms = numStrayAtoms;
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToHost(x, msg->data, msg->dataSize);
      ((DpcppPmeTranspose *)pmeTranspose)->waitStreamSynchronize();
      pmePencilY(x,0,thisIndex.z).recvBlock(msg);
    }
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmePencilX::recvDataFromY(PmeBlockMsg *msg) {
  if (msg->dataSize != 0) {
    // Buffer is coming from a different node
    ((DpcppPmeTranspose *)pmeTranspose)->copyDataHostToDevice(msg->x, msg->data, (sycl::float2 *)fftCompute->getDataDst());
  } else {
    // Buffer is coming from the same node
    // Wait for event that was recorded on the sending pencil
    // device ID = deviceBuffers[msg->x].deviceID
    // event     = deviceBuffers[msg->x].event
    //cudaCheck(cudaStreamWaitEvent(stream, deviceBuffers[msg->x].event, 0));
    // TODO: No equivalent in SYCL for cudaStreamWaitEvent
    deviceBuffers[msg->x].event.wait();
#ifndef P2P_ENABLE_3D
    if (deviceBuffers[msg->x].data != NULL && deviceBuffers[msg->x].deviceID != deviceID) {
      // Data is in temporary device buffer, copy it into final fft-buffer
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToDevice(msg->x, (sycl::float2 *)fftCompute->getDataDst());
    }
#endif
  }
  delete msg;
}

//###########################################################################
//###########################################################################
//###########################################################################

void DpcppPmePencilY::initialize(DpcppPmeXInitMsg *msg) {
  pmeGrid = msg->pmeGrid;
  pmePencilX = msg->pmePencilX;
  pmePencilZ = msg->pmePencilZ;
  xMap = msg->xMap;
  zMap = msg->zMap;

  delete msg;

  initBlockSizes();
}

DpcppPmePencilY::~DpcppPmePencilY() {
  // No need to destroy DPC++ events
}

//
// DPC++ specific initialization
//
void DpcppPmePencilY::initializeDevice(InitDeviceMsg2 *msg) try {
  // Get device proxy
  // CProxy_DpcppComputePmeDevice deviceProxy = msg->deviceProxy;
  deviceID = msg->deviceID;
  stream = msg->stream;
  CProxy_DpcppComputePmeMgr mgrProxy = msg->mgrProxy;
  delete msg;
  // deviceID = deviceProxy.ckLocalBranch()->getDeviceID();
  // cudaStream_t stream = deviceProxy.ckLocalBranch()->getStream();
  // CProxy_DpcppComputePmeMgr mgrProxy = deviceProxy.ckLocalBranch()->getMgrProxy();
  // Setup fftCompute and pmeKSpaceCompute
  fftCompute = new DpcppFFTCompute(deviceID, stream);
  pmeTranspose = new DpcppPmeTranspose(pmeGrid, Perm_Y_Z_cX, thisIndex.z, thisIndex.x, deviceID, stream);

  // Create event. NOTE: Events are tied to devices
  // Event creation is redundant in DPC++
  dpcppDevice->setDeviceID(deviceID);
  eventCreated = true;

  deviceBuffersZ.resize(pmeGrid.yBlocks, DeviceBuffer(-1, false, NULL));
  deviceBuffersX.resize(pmeGrid.yBlocks, DeviceBuffer(-1, false, NULL));
  numDeviceBuffersZ = 0;
  numDeviceBuffersX = 0;

  for (int y=0;y < pmeGrid.yBlocks;y++) {
    int pe;
    pe = zMap.ckLocalBranch()->procNum(0, CkArrayIndex3D(thisIndex.x, y, 0));
    if (CkNodeOf(pe) == CkMyNode()) {
      int deviceID0 = mgrProxy.ckLocalBranch()->getDeviceIDPencilZ(thisIndex.x, y);
      numDeviceBuffersZ++;
      deviceBuffersZ[y] = DeviceBuffer(deviceID0, false, NULL);
      pmePencilZ(thisIndex.x, y, 0).getDeviceBuffer(thisIndex.z, (deviceID0 == deviceID), thisProxy);
    }
    pe = xMap.ckLocalBranch()->procNum(0, CkArrayIndex3D(0, y, thisIndex.z));
    if (CkNodeOf(pe) == CkMyNode()) {
      int deviceID0 = mgrProxy.ckLocalBranch()->getDeviceIDPencilX(y, thisIndex.z);
      numDeviceBuffersX++;
      deviceBuffersX[y] = DeviceBuffer(deviceID0, false, NULL);
      pmePencilX(0, y, thisIndex.z).getDeviceBuffer(thisIndex.x, (deviceID0 == deviceID), thisProxy);
    }
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// DPC++ specific start
//
void DpcppPmePencilY::start(const CkCallback &cb) {
  thisProxy[thisIndex].recvDeviceBuffers(cb);
}

//
// Setup direct device buffers
//
void DpcppPmePencilY::setDeviceBuffers() {
  std::vector<sycl::float2*> dataPtrsYZX(pmeGrid.yBlocks, (sycl::float2*)0);
  std::vector<sycl::float2*> dataPtrsZXY(pmeGrid.yBlocks, (sycl::float2*)0);
  for (int y=0;y < pmeGrid.yBlocks;y++) {
    if (deviceBuffersZ[y].data != NULL) {
      if (deviceBuffersZ[y].deviceID == deviceID) {
        dataPtrsYZX[y] = deviceBuffersZ[y].data;
      }
    }
    if (deviceBuffersX[y].data != NULL) {
      if (deviceBuffersX[y].deviceID == deviceID) {
        dataPtrsZXY[y] = deviceBuffersX[y].data;
      }
    }
  }
  ((DpcppPmeTranspose *)pmeTranspose)->setDataPtrsYZX(dataPtrsYZX, (sycl::float2 *)fftCompute->getDataDst());
  ((DpcppPmeTranspose *)pmeTranspose)->setDataPtrsZXY(dataPtrsZXY, (sycl::float2 *)fftCompute->getDataSrc());
}

sycl::float2 *DpcppPmePencilY::getDataForX(const int i, const bool sameDevice) {
  sycl::float2 *data;
#ifndef P2P_ENABLE_3D
  if (sameDevice) {
    int i0, i1, j0, j1, k0, k1;
    getBlockDim(pmeGrid, Perm_Y_Z_cX, i, 0, 0, i0, i1, j0, j1, k0, k1);
    data = (sycl::float2 *)fftCompute->getDataSrc() + i0;
  } else {
    data = ((DpcppPmeTranspose *)pmeTranspose)->getBuffer(i);
  }
#else
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, Perm_Y_Z_cX, i, 0, 0, i0, i1, j0, j1, k0, k1);
  data = (sycl::float2 *)fftCompute->getDataSrc() + i0;
#endif
  return data;
}

sycl::float2 *DpcppPmePencilY::getDataForZ(const int i, const bool sameDevice) {
  sycl::float2 *data;
#ifndef P2P_ENABLE_3D
  if (sameDevice) {
    int i0, i1, j0, j1, k0, k1;
    getBlockDim(pmeGrid, Perm_Y_Z_cX, i, 0, 0, i0, i1, j0, j1, k0, k1);
    data = (sycl::float2 *)fftCompute->getDataDst() + i0;
  } else {
    data = ((DpcppPmeTranspose *)pmeTranspose)->getBuffer(i);
  }
#else
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, Perm_Y_Z_cX, i, 0, 0, i0, i1, j0, j1, k0, k1);
  data = (sycl::float2 *)fftCompute->getDataDst() + i0;
#endif
  return data;
}

void DpcppPmePencilY::backwardDone() try {
  // Transpose locally
  pmeTranspose->transposeXYZtoZXY((sycl::float2 *)fftCompute->getDataSrc());

  // Send data to x-pencils that share the same x-coordinate. There are pmeGrid.yBlocks of them
  // Direct-Device-To-Device communication
  if (numDeviceBuffersX > 0) {
    for (int y=0;y < pmeGrid.yBlocks;y++) {
      if (deviceBuffersX[y].data != NULL) {
        if (deviceBuffersX[y].deviceID != deviceID) {
          ((DpcppPmeTranspose *)pmeTranspose)->copyDataToPeerDeviceZXY(y, deviceBuffersX[y].deviceID,
            Perm_cX_Y_Z, deviceBuffersX[y].data);
        }
      }
    }
    // Record event for this pencil
    event = stream->single_task<class DpcppPmePencilY_backward_empty_task>([=](){});
    // Send empty message
    for (int y=0;y < pmeGrid.yBlocks;y++) {
      if (deviceBuffersX[y].data != NULL) {
        PmeBlockMsg* msg = new (0, PRIORITY_SIZE) PmeBlockMsg();
        msg->dataSize = 0;
        msg->x = thisIndex.x;
        msg->y = y;
        msg->z = thisIndex.z;
        pmePencilX(0,y,thisIndex.z).recvBlock(msg);
      }
    }
  }

  // Copy via host
  for (int y=0;y < pmeGrid.yBlocks;y++) {
    if (deviceBuffersX[y].data == NULL) {
      PmeBlockMsg* msg = new (blockSizes[y], PRIORITY_SIZE) PmeBlockMsg();
      msg->dataSize = blockSizes[y];
      msg->x = thisIndex.x;
      msg->y = y;
      msg->z = thisIndex.z;
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToHost(y, msg->data, msg->dataSize);
      ((DpcppPmeTranspose *)pmeTranspose)->waitStreamSynchronize();
      pmePencilX(0,y,thisIndex.z).recvBlock(msg);
    }
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmePencilY::forwardDone() try {
  if (pmeTranspose == NULL)
    NAMD_bug("DpcppPmePencilY::forwardDone, pmeTranspose not initialized");
  if (blockSizes.size() == 0)
    NAMD_bug("DpcppPmePencilY::forwardDone, blockSizes not initialized");

  // Transpose locally
  pmeTranspose->transposeXYZtoYZX((sycl::float2 *)fftCompute->getDataDst());

  // Send data to z-pencils that share the same x-coordinate. There are pmeGrid.yBlocks of them
  // Direct-Device-To-Device communication
  if (numDeviceBuffersZ > 0) {
    for (int y=0;y < pmeGrid.yBlocks;y++) {
      if (deviceBuffersZ[y].data != NULL) {
        if (deviceBuffersZ[y].deviceID != deviceID) {
          ((DpcppPmeTranspose *)pmeTranspose)->copyDataToPeerDeviceYZX(y, deviceBuffersZ[y].deviceID,
            Perm_Z_cX_Y, deviceBuffersZ[y].data);
        }
      }
    }
    // Record event for this pencil
    event = stream->single_task<class DpcppPmePencilY_forward_empty_task>([=](){});
    // Send empty message
    for (int y=0;y < pmeGrid.yBlocks;y++) {
      if (deviceBuffersZ[y].data != NULL) {
        PmeBlockMsg* msg = new (0, PRIORITY_SIZE) PmeBlockMsg();
        msg->dataSize = 0;
        msg->x = thisIndex.x;
        msg->y = y;
        msg->z = thisIndex.z;
        msg->doEnergy = doEnergy;
        msg->doVirial = doVirial;
        msg->lattice  = lattice;
        msg->numStrayAtoms = numStrayAtoms;
        pmePencilZ(thisIndex.x,y,0).recvBlock(msg);
      }
    }
  }

  // Copy-To-Host communication
  for (int y=0;y < pmeGrid.yBlocks;y++) {
    if (deviceBuffersZ[y].data == NULL) {
      PmeBlockMsg* msg = new (blockSizes[y], PRIORITY_SIZE) PmeBlockMsg();
      msg->dataSize = blockSizes[y];
      msg->x = thisIndex.x;
      msg->y = y;
      msg->z = thisIndex.z;
      msg->doEnergy = doEnergy;
      msg->doVirial = doVirial;
      msg->lattice  = lattice;
      msg->numStrayAtoms = numStrayAtoms;
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToHost(y, msg->data, msg->dataSize);
      ((DpcppPmeTranspose *)pmeTranspose)->waitStreamSynchronize();
      pmePencilZ(thisIndex.x,y,0).recvBlock(msg);
    }
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmePencilY::recvDataFromX(PmeBlockMsg *msg) {
  if (msg->dataSize != 0) {
    // Buffer is coming from a different node
    ((DpcppPmeTranspose *)pmeTranspose)->copyDataHostToDevice(msg->y, msg->data, (sycl::float2 *)fftCompute->getDataSrc());
  } else {
    // Buffer is coming from the same node
    // Wait for event that was recorded on the sending pencil
    // device ID = deviceBuffersX[msg->y].deviceID
    // event     = deviceBuffersX[msg->y].event
    //cudaCheck(cudaStreamWaitEvent(stream, deviceBuffersX[msg->y].event, 0));
    // TODO: No equivalent in SYCL for cudaStreamWaitEvent
    deviceBuffersX[msg->y].event.wait();
#ifndef P2P_ENABLE_3D
    if (deviceBuffersX[msg->y].data != NULL && deviceBuffersX[msg->y].deviceID != deviceID) {
      // Data is in temporary device buffer, copy it into final fft-buffer
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToDevice(msg->y, (sycl::float2 *)fftCompute->getDataSrc());
    }
#endif
  }
  delete msg;
}

void DpcppPmePencilY::recvDataFromZ(PmeBlockMsg *msg) {
  if (msg->dataSize != 0) {
    // Buffer is coming from a different node
    ((DpcppPmeTranspose *)pmeTranspose)->copyDataHostToDevice(msg->y, msg->data, (sycl::float2 *)fftCompute->getDataDst());
  } else {
    // Buffer is coming from the same node
    // Wait for event that was recorded on the sending pencil
    // device ID = deviceBuffersZ[msg->y].deviceID
    // event     = deviceBuffersZ[msg->y].event
    //cudaCheck(cudaStreamWaitEvent(stream, deviceBuffersZ[msg->y].event, 0));
    // TODO: No equivalent in SYCL for cudaStreamWaitEvent
    deviceBuffersZ[msg->y].event.wait();
#ifndef P2P_ENABLE_3D
    if (deviceBuffersZ[msg->y].data != NULL && deviceBuffersZ[msg->y].deviceID != deviceID) {
      // Data is in temporary device buffer, copy it into final fft-buffer
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToDevice(msg->y, (sycl::float2 *)fftCompute->getDataDst());
    }
#endif
  }
  delete msg;
}

//###########################################################################
//###########################################################################
//###########################################################################

void DpcppPmePencilZ::initialize(DpcppPmeXInitMsg *msg) {
  useXYslab = false;
  pmeGrid = msg->pmeGrid;
  pmePencilY = msg->pmePencilY;
  yMap = msg->yMap;

  delete msg;

  initBlockSizes();
}

void DpcppPmePencilZ::initialize(DpcppPmeXYInitMsg *msg) {
  useXYslab = true;
  pmeGrid = msg->pmeGrid;
  pmePencilXY = msg->pmePencilXY;
  xyMap = msg->xyMap;

  delete msg;

  initBlockSizes();
}

DpcppPmePencilZ::~DpcppPmePencilZ() {
  // No need to destroy DPC++ events
}

//
// DPC++ specific initialization
//
void DpcppPmePencilZ::initializeDevice(InitDeviceMsg2 *msg) try {
  // Get device proxy
  // CProxy_DpcppComputePmeDevice deviceProxy = msg->deviceProxy;
  deviceID = msg->deviceID;
  stream = msg->stream;
  CProxy_DpcppComputePmeMgr mgrProxy = msg->mgrProxy;
  delete msg;
  // deviceID = deviceProxy.ckLocalBranch()->getDeviceID();
  // cudaStream_t stream = deviceProxy.ckLocalBranch()->getStream();
  // CProxy_ComputePmeCUDAMgr mgrProxy = deviceProxy.ckLocalBranch()->getMgrProxy();
  // Setup fftCompute and pmeKSpaceCompute
  fftCompute = new DpcppFFTCompute(deviceID, stream);
  pmeTranspose = new DpcppPmeTranspose(pmeGrid, Perm_Z_cX_Y, thisIndex.x, thisIndex.y, deviceID, stream);
  pmeKSpaceCompute = new DpcppPmeKSpaceCompute(pmeGrid, Perm_Z_cX_Y, thisIndex.x, thisIndex.y,
    ComputeNonbondedUtil::ewaldcof, deviceID, stream);

  // Create event. NOTE: Events are tied to devices
  // Event creation is redundant in DPC++
  dpcppDevice->setDeviceID(deviceID);
  eventCreated = true;

  deviceBuffers.resize(pmeGrid.zBlocks, DeviceBuffer(-1, false, NULL));
  numDeviceBuffers = 0;

  if (useXYslab) {
    for (int z=0;z < pmeGrid.zBlocks;z++) {
      int pe = xyMap.ckLocalBranch()->procNum(0, CkArrayIndex3D(0,0,z));
      if (CkNodeOf(pe) == CkMyNode()) {
        int deviceID0 = mgrProxy.ckLocalBranch()->getDeviceIDPencilX(0, z);
        // Check for Peer-to-Peer access
        int canAccessPeer = 0;
        if (deviceID != deviceID0) {
          dpcppDevice->setDeviceID(deviceID);
          // TODO: Peer GPU access disabled
          //cudaCheck(cudaDeviceCanAccessPeer(&canAccessPeer, deviceID, deviceID0));
        }
#ifdef DISABLE_P2P
        canAccessPeer = 0;
#endif
        numDeviceBuffers++;
        deviceBuffers[z] = DeviceBuffer(deviceID0, canAccessPeer, NULL);
        pmePencilXY(0,0,z).getDeviceBuffer(thisIndex.x, (deviceID0 == deviceID) || canAccessPeer, thisProxy);
      }
    }
  } else {
    for (int z=0;z < pmeGrid.zBlocks;z++) {
      int pe = yMap.ckLocalBranch()->procNum(0, CkArrayIndex3D(thisIndex.x,0,z));
      if (CkNodeOf(pe) == CkMyNode()) {
        int deviceID0 = mgrProxy.ckLocalBranch()->getDeviceIDPencilY(thisIndex.x, z);
        numDeviceBuffers++;
        deviceBuffers[z] = DeviceBuffer(deviceID0, false, NULL);
        pmePencilY(thisIndex.x,0,z).getDeviceBuffer(thisIndex.y, (deviceID0 == deviceID), thisProxy);
      }
    }
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// DPC++ specific start
//
void DpcppPmePencilZ::start(const CkCallback &cb) {
  thisProxy[thisIndex].recvDeviceBuffers(cb);
}

void DpcppPmePencilZ::setDeviceBuffers() {
  std::vector<sycl::float2*> dataPtrs(pmeGrid.zBlocks, (sycl::float2*)0);
  for (int z=0;z < pmeGrid.zBlocks;z++) {
    if (deviceBuffers[z].data != NULL) {
      if (deviceBuffers[z].deviceID == deviceID || deviceBuffers[z].isPeerDevice) {
        dataPtrs[z] = deviceBuffers[z].data;
      }
    }
  }
  if (useXYslab) {
    ((DpcppPmeTranspose *)pmeTranspose)->setDataPtrsYZX(dataPtrs, (sycl::float2 *)fftCompute->getDataSrc());
  } else {
    ((DpcppPmeTranspose *)pmeTranspose)->setDataPtrsZXY(dataPtrs, (sycl::float2 *)fftCompute->getDataSrc());
  }
}

sycl::float2 *DpcppPmePencilZ::getData(const int i, const bool sameDevice) {
  sycl::float2 *data;
#ifndef P2P_ENABLE_3D
  if (sameDevice) {
    int i0, i1, j0, j1, k0, k1;
    getBlockDim(pmeGrid, Perm_Z_cX_Y, i, 0, 0, i0, i1, j0, j1, k0, k1);
    data = (sycl::float2 *)fftCompute->getDataSrc() + i0;
  } else {
    data = ((DpcppPmeTranspose *)pmeTranspose)->getBuffer(i);
  }
#else
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, Perm_Z_cX_Y, i, 0, 0, i0, i1, j0, j1, k0, k1);
  data = (sycl::float2 *)fftCompute->getDataSrc() + i0;
#endif
  return data;
}

void DpcppPmePencilZ::backwardDone() try {
  // Transpose locally
  if (useXYslab) {
    pmeTranspose->transposeXYZtoYZX((sycl::float2 *)fftCompute->getDataSrc());
  } else {
    pmeTranspose->transposeXYZtoZXY((sycl::float2 *)fftCompute->getDataSrc());
  }

  if (useXYslab) {
    // Direct-Device-To-Device communication
    if (numDeviceBuffers > 0) {
      for (int z=0;z < pmeGrid.zBlocks;z++) {
        if (deviceBuffers[z].data != NULL) {
          if (deviceBuffers[z].deviceID != deviceID && !deviceBuffers[z].isPeerDevice) {
            ((DpcppPmeTranspose *)pmeTranspose)->copyDataToPeerDeviceYZX(z, deviceBuffers[z].deviceID,
              Perm_cX_Y_Z, deviceBuffers[z].data);
          }
        }
      }
      // Record event for this pencil
      event = stream->single_task<class DpcppPmePencilZ_backward_empty_task_1>([=](){});
      // Send empty message
      for (int z=0;z < pmeGrid.zBlocks;z++) {
        if (deviceBuffers[z].data != NULL) {
          PmeBlockMsg* msg = new (0, PRIORITY_SIZE) PmeBlockMsg();
          msg->dataSize = 0;
          msg->x = thisIndex.x;
          msg->y = thisIndex.y;
          msg->z = z;
          pmePencilXY(0,0,z).recvBlock(msg);
        }
      }
    }

    // Copy-To-Host communication
    for (int z=0;z < pmeGrid.zBlocks;z++) {
      if (deviceBuffers[z].data == NULL) {
        PmeBlockMsg* msg = new (blockSizes[z], PRIORITY_SIZE) PmeBlockMsg();
        msg->dataSize = blockSizes[z];
        msg->x = thisIndex.x;
        msg->y = thisIndex.y;
        msg->z = z;
        ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToHost(z, msg->data, msg->dataSize);
        ((DpcppPmeTranspose *)pmeTranspose)->waitStreamSynchronize();
        pmePencilXY(0,0,z).recvBlock(msg);
      }
    }
  } else {
    // Send data to y-pencils that share the same x-coordinate. There are pmeGrid.zBlocks of them
    // Direct-Device-To-Device communication
    if (numDeviceBuffers > 0) {
      for (int z=0;z < pmeGrid.zBlocks;z++) {
        if (deviceBuffers[z].data != NULL) {
          if (deviceBuffers[z].deviceID != deviceID) {
            ((DpcppPmeTranspose *)pmeTranspose)->copyDataToPeerDeviceZXY(z, deviceBuffers[z].deviceID,
              Perm_Y_Z_cX, deviceBuffers[z].data);
          }
        }
      }
      // Record event for this pencil
      event = stream->single_task<class DpcppPmePencilZ_backward_empty_task_2>([=](){});
      // Send empty message
      for (int z=0;z < pmeGrid.zBlocks;z++) {
        if (deviceBuffers[z].data != NULL) {
          PmeBlockMsg* msg = new (0, PRIORITY_SIZE) PmeBlockMsg();
          msg->dataSize = 0;
          msg->x = thisIndex.x;
          msg->y = thisIndex.y;
          msg->z = z;
          pmePencilY(thisIndex.x,0,z).recvBlock(msg);
        }
      }
    }

    // Copy-To-Host communication
    for (int z=0;z < pmeGrid.zBlocks;z++) {
      if (deviceBuffers[z].data == NULL) {
        PmeBlockMsg* msg = new (blockSizes[z], PRIORITY_SIZE) PmeBlockMsg();
        msg->dataSize = blockSizes[z];
        msg->x = thisIndex.x;
        msg->y = thisIndex.y;
        msg->z = z;
        ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToHost(z, msg->data, msg->dataSize);
        ((DpcppPmeTranspose *)pmeTranspose)->waitStreamSynchronize();
        pmePencilY(thisIndex.x,0,z).recvBlock(msg);
      }
    }
  }

  // Submit reductions
  ((DpcppPmeKSpaceCompute *)pmeKSpaceCompute)->energyAndVirialSetCallback(this);
  // ((DpcppPmeKSpaceCompute *)pmeKSpaceCompute)->waitEnergyAndVirial();
  // submitReductions();
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmePencilZ::energyAndVirialDone() {
  submitReductions();
}

void DpcppPmePencilZ::recvDataFromY(PmeBlockMsg *msg) {
  // NOTE: No need to synchronize stream here since memory copies are in the stream
  if (msg->dataSize != 0) {
    // Buffer is coming from a different node
    ((DpcppPmeTranspose *)pmeTranspose)->copyDataHostToDevice(msg->z, msg->data, (sycl::float2 *)fftCompute->getDataSrc());
  } else {
    // Buffer is coming from the same node
    // Wait for event that was recorded on the sending pencil
    // device ID = deviceBuffers[msg->z].deviceID
    // event     = deviceBuffers[msg->z].event
    //cudaCheck(cudaStreamWaitEvent(stream, deviceBuffers[msg->z].event, 0));
    // TODO: No equivalent in SYCL for cudaStreamWaitEvent
    deviceBuffers[msg->z].event.wait();
#ifndef P2P_ENABLE_3D
    if (deviceBuffers[msg->z].data != NULL && deviceBuffers[msg->z].deviceID != deviceID && !deviceBuffers[msg->z].isPeerDevice) {
      // Data is in temporary device buffer, copy it into final fft-buffer
      ((DpcppPmeTranspose *)pmeTranspose)->copyDataDeviceToDevice(msg->z, (sycl::float2 *)fftCompute->getDataSrc());
    }
#endif
  }
  delete msg;
}
#endif // NAMD_DPCPP

#include "DpcppPmeSolver.def.h"
#include <chrono>
