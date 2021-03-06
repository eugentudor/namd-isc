#ifndef DPCPPCOMPUTEPME_H
#define DPCPPCOMPUTEPME_H

#include <vector>
#include <list>
#include "PmeBase.h"

#include "PatchTypes.h"       // Results
#include "Compute.h"
#include "Box.h"
#include "OwnerBox.h"
#include "DpcppComputePmeMgr.decl.h"

#ifdef NAMD_DPCPP
class HomePatch;

class DpcppComputePme : public Compute {
public:
  DpcppComputePme(ComputeID c, PatchIDList& pids);
  DpcppComputePme(ComputeID c, PatchID pid);
  virtual ~DpcppComputePme();
  void initialize();
  void atomUpdate();
  int noWork();
  void doWork();
  bool storePmeForceMsg(PmeForceMsg *msg);
private:
  struct PatchRecord {
    PatchRecord() {
      pmeForceMsg = NULL;
      patch = NULL;
      positionBox = NULL;
      avgPositionBox = NULL;
      forceBox = NULL;
    }
    // Message that contains the pointers to forces
    PmeForceMsg* pmeForceMsg;
    // Home pencil
    int homePencilY;
    int homePencilZ;
    int homePencilNode;
    // Pointer to patch
    Patch *patch;
    // Patch ID
    PatchID patchID;
    // Boxes
    Box<Patch,CompAtom> *positionBox;
    Box<Patch,CompAtom> *avgPositionBox;
    Box<Patch,Results> *forceBox;
  };

  double calcSelfEnergy(int numAtoms, CompAtom *x);
  void sendAtoms();
  void recvForces();
  void setupActivePencils();

  CmiNodeLock lock;
  int patchCounter;

  std::vector<PatchRecord> patches;

  SubmitReduction *reduction;

  bool sendAtomsDone;

  PmeGrid pmeGrid;

  DpcppComputePmeMgr *mgr;

  CProxy_DpcppComputePmeMgr dpcppComputePmeMgrProxy;

  bool atomsChanged;

};
#endif // NAMD_DPCPP

#endif // DPCPPCOMPUTEPME_H
