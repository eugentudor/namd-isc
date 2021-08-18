#include "NamdTypes.h"
#include "common.h"
#include "Node.h"
#include "DpcppComputeMgr.h"

#include "DpcppDevice.h"
#ifdef NAMD_DPCPP
#ifdef WIN32
#define __thread __declspec(thread)
#endif
extern __thread DpcppDevice *dpcppDevice;

//
// Class constructor
//
DpcppComputeMgr::DpcppComputeMgr() {
	// __sdag_init();
  numDevices = 0;
  // numNodesContributed = 0;
  // numDevicesMax = 0;
}

//
// Class constructor
//
DpcppComputeMgr::DpcppComputeMgr(CkMigrateMessage *) {
	// __sdag_init();
  NAMD_bug("DpcppComputeMgr cannot be migrated");
  numDevices = 0;
  // numNodesContributed = 0;
  // numDevicesMax = 0;
}

//
// Class destructor
//
DpcppComputeMgr::~DpcppComputeMgr() {
  for (int i=0;i < numDevices;i++) {
    if (dpcppNonbondedTablesList[i] != NULL) delete dpcppNonbondedTablesList[i];
    if (dpcppComputeNonbondedList[i] != NULL) delete dpcppComputeNonbondedList[i];
    if (dpcppComputeBondedList[i] != NULL) delete dpcppComputeBondedList[i];
  }
}

//
// Initialize manager
// This gets called on rank 0 of each node
//
void DpcppComputeMgr::initialize(CkQdMsg *msg) {
	if (msg != NULL) delete msg;

	numDevices = dpcppDevice->getDeviceCount();

  // Create pointers to devices
  dpcppNonbondedTablesList.resize(numDevices, NULL);
  dpcppComputeNonbondedList.resize(numDevices, NULL);
  dpcppComputeBondedList.resize(numDevices, NULL);

  // Create CUDA non-bonded tables for all devices that are used for computation
  for (int i=0;i < dpcppDevice->getNumDevice();i++) {
    int deviceID = dpcppDevice->getDeviceIDbyRank(i);
    dpcppNonbondedTablesList[deviceID] = new DpcppNonbondedTables(deviceID);
  }
}

//
// Update nonbonded tables
// Should be called only on rank 0 of each node
//
void DpcppComputeMgr::update() {
  if ( CkMyRank() ) NAMD_bug("DpcppComputeMgr::update() should be called only by rank 0");
  for (int i=0;  i < dpcppDevice->getNumDevice();  i++) {
    int deviceID = dpcppDevice->getDeviceIDbyRank(i);
    // calls update function from DpcppNonbondedTables
    dpcppNonbondedTablesList[deviceID]->updateTables();
  }
}

DpcppComputeMgr* DpcppComputeMgr::getDpcppComputeMgr() {
  // Get pointer to DpcppComputeMgr on this node
  CProxy_DpcppComputeMgr DpcppComputeMgrProxy = CkpvAccess(BOCclass_group).dpcppComputeMgr;
  DpcppComputeMgr* DpcppComputeMgr = DpcppComputeMgrProxy.ckLocalBranch();
  if (DpcppComputeMgr == NULL)
    NAMD_bug("getDpcppComputeMgr, unable to locate local branch of BOC entry DpcppComputeMgr");
  return DpcppComputeMgr;
}

//
// Creates DpcppComputeNonbonded object
//
DpcppComputeNonbonded* DpcppComputeMgr::createDpcppComputeNonbonded(ComputeID c) {
  int deviceID = dpcppDevice->getDeviceID();
  if (dpcppComputeNonbondedList.at(deviceID) != NULL)
    NAMD_bug("DpcppComputeMgr::createDpcppComputeNonbonded called twice");
  if (dpcppNonbondedTablesList.at(deviceID) == NULL)
    NAMD_bug("DpcppComputeMgr::createDpcppComputeNonbonded, non-bonded CUDA tables not created");
  bool doStreaming = !dpcppDevice->getNoStreaming() && !Node::Object()->simParameters->GBISOn;
  dpcppComputeNonbondedList[deviceID] = new DpcppComputeNonbonded(c, deviceID, *dpcppNonbondedTablesList[deviceID], doStreaming);
  return dpcppComputeNonbondedList[deviceID];
}

//
// Returns DpcppComputeNonbonded for this Pe
//
DpcppComputeNonbonded* DpcppComputeMgr::getDpcppComputeNonbonded() {
  // Get device ID for this Pe
  int deviceID = dpcppDevice->getDeviceID();
  DpcppComputeNonbonded* p = dpcppComputeNonbondedList[deviceID];
  if (p == NULL)
    NAMD_bug("DpcppComputeMgr::getDpcppComputeNonbonded(), device not created yet");
  return p;
}

//
// Creates DpcppComputeBonded object
//
DpcppComputeBonded* DpcppComputeMgr::createDpcppComputeBonded(ComputeID c, ComputeMgr* computeMgr) {
  int deviceID = dpcppDevice->getDeviceID();
  if (dpcppComputeBondedList.at(deviceID) != NULL)
    NAMD_bug("DpcppComputeMgr::createDpcppComputeBonded called twice");
  if (dpcppNonbondedTablesList.at(deviceID) == NULL)
    NAMD_bug("DpcppComputeMgr::createDpcppComputeNonbonded, non-bonded CUDA tables not created");
  dpcppComputeBondedList[deviceID] = new DpcppComputeBonded(c, computeMgr, deviceID, *dpcppNonbondedTablesList[deviceID]);
  return dpcppComputeBondedList[deviceID];
}

//
// Returns DpcppComputeBonded for this Pe
//
DpcppComputeBonded* DpcppComputeMgr::getDpcppComputeBonded() {
  // Get device ID for this Pe
  int deviceID = dpcppDevice->getDeviceID();
  DpcppComputeBonded* p = dpcppComputeBondedList[deviceID];
  if (p == NULL)
    NAMD_bug("DpcppComputeMgr::getDpcppComputeBonded(), device not created yet");
  return p;
}

#endif // NAMD_DPCPP

#include "DpcppComputeMgr.def.h"
