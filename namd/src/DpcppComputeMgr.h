#ifndef DPCPPCOMPUTEMGR_H
#define DPCPPCOMPUTEMGR_H
#include <vector>
#include "DpcppUtils.h"
#include "DpcppComputeMgr.decl.h"
#include "DpcppNonbondedTables.h"
#include "DpcppComputeNonbonded.h"
#include "DpcppComputeBonded.h"
#ifdef NAMD_DPCPP

class DpcppComputeMgr : public CBase_DpcppComputeMgr {
public:
  // DpcppComputeMgr_SDAG_CODE;
  DpcppComputeMgr();
  DpcppComputeMgr(CkMigrateMessage *);
  ~DpcppComputeMgr();
  void initialize(CkQdMsg *msg);
  void initialize_devices(CkQdMsg *msg);
  void update();
  static DpcppComputeMgr* getDpcppComputeMgr();
  DpcppComputeNonbonded* createDpcppComputeNonbonded(ComputeID c);
  DpcppComputeNonbonded* getDpcppComputeNonbonded();
  DpcppComputeBonded* createDpcppComputeBonded(ComputeID c, ComputeMgr* computeMgr);
  DpcppComputeBonded* getDpcppComputeBonded();
private:

  // Number of CUDA devices on this node that are used in computation
  int numDevices;
  std::vector<DpcppNonbondedTables*> dpcppNonbondedTablesList;
  std::vector<DpcppComputeNonbonded*> dpcppComputeNonbondedList;
  std::vector<DpcppComputeBonded*> dpcppComputeBondedList;
};

#else // NAMD_DPCPP

class DpcppComputeMgr : public CBase_DpcppComputeMgr {
};

#endif // NAMD_DPCP
#endif // DPCPPCOMPUTEMGR_H
