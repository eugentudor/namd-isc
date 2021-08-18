





/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */


/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeDevice::sendAtomsToNeighbor_3_closure : public SDAG::Closure {
            int y;
            int z;
            int atomIval;


      sendAtomsToNeighbor_3_closure() {
        init();
      }
      sendAtomsToNeighbor_3_closure(CkMigrateMessage*) {
        init();
      }
            int & getP0() { return y;}
            int & getP1() { return z;}
            int & getP2() { return atomIval;}
      void pup(PUP::er& __p) {
        __p | y;
        __p | z;
        __p | atomIval;
        packClosure(__p);
      }
      virtual ~sendAtomsToNeighbor_3_closure() {
      }
      PUPable_decl(SINGLE_ARG(sendAtomsToNeighbor_3_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeDevice::gatherForce_5_closure : public SDAG::Closure {
      

      gatherForce_5_closure() {
        init();
      }
      gatherForce_5_closure(CkMigrateMessage*) {
        init();
      }
            void pup(PUP::er& __p) {
        packClosure(__p);
      }
      virtual ~gatherForce_5_closure() {
      }
      PUPable_decl(SINGLE_ARG(gatherForce_5_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeDevice::mergeForcesOnPatch_7_closure : public SDAG::Closure {
            int homePatchIndex;


      mergeForcesOnPatch_7_closure() {
        init();
      }
      mergeForcesOnPatch_7_closure(CkMigrateMessage*) {
        init();
      }
            int & getP0() { return homePatchIndex;}
      void pup(PUP::er& __p) {
        __p | homePatchIndex;
        packClosure(__p);
      }
      virtual ~mergeForcesOnPatch_7_closure() {
      }
      PUPable_decl(SINGLE_ARG(mergeForcesOnPatch_7_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */






/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::recvPencils_4_closure : public SDAG::Closure {
            CProxy_DpcppPmePencilXYZ xyz;


      recvPencils_4_closure() {
        init();
      }
      recvPencils_4_closure(CkMigrateMessage*) {
        init();
      }
            CProxy_DpcppPmePencilXYZ & getP0() { return xyz;}
      void pup(PUP::er& __p) {
        __p | xyz;
        packClosure(__p);
      }
      virtual ~recvPencils_4_closure() {
      }
      PUPable_decl(SINGLE_ARG(recvPencils_4_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::recvPencils_5_closure : public SDAG::Closure {
            CProxy_DpcppPmePencilXY xy;
            CProxy_DpcppPmePencilZ z;


      recvPencils_5_closure() {
        init();
      }
      recvPencils_5_closure(CkMigrateMessage*) {
        init();
      }
            CProxy_DpcppPmePencilXY & getP0() { return xy;}
            CProxy_DpcppPmePencilZ & getP1() { return z;}
      void pup(PUP::er& __p) {
        __p | xy;
        __p | z;
        packClosure(__p);
      }
      virtual ~recvPencils_5_closure() {
      }
      PUPable_decl(SINGLE_ARG(recvPencils_5_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::recvPencils_6_closure : public SDAG::Closure {
            CProxy_DpcppPmePencilX x;
            CProxy_DpcppPmePencilY y;
            CProxy_DpcppPmePencilZ z;


      recvPencils_6_closure() {
        init();
      }
      recvPencils_6_closure(CkMigrateMessage*) {
        init();
      }
            CProxy_DpcppPmePencilX & getP0() { return x;}
            CProxy_DpcppPmePencilY & getP1() { return y;}
            CProxy_DpcppPmePencilZ & getP2() { return z;}
      void pup(PUP::er& __p) {
        __p | x;
        __p | y;
        __p | z;
        packClosure(__p);
      }
      virtual ~recvPencils_6_closure() {
      }
      PUPable_decl(SINGLE_ARG(recvPencils_6_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::recvAtomFiler_8_closure : public SDAG::Closure {
            CProxy_PmeAtomFiler filer;


      recvAtomFiler_8_closure() {
        init();
      }
      recvAtomFiler_8_closure(CkMigrateMessage*) {
        init();
      }
            CProxy_PmeAtomFiler & getP0() { return filer;}
      void pup(PUP::er& __p) {
        __p | filer;
        packClosure(__p);
      }
      virtual ~recvAtomFiler_8_closure() {
      }
      PUPable_decl(SINGLE_ARG(recvAtomFiler_8_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::skip_9_closure : public SDAG::Closure {
      

      skip_9_closure() {
        init();
      }
      skip_9_closure(CkMigrateMessage*) {
        init();
      }
            void pup(PUP::er& __p) {
        packClosure(__p);
      }
      virtual ~skip_9_closure() {
      }
      PUPable_decl(SINGLE_ARG(skip_9_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::initializePatches_11_closure : public SDAG::Closure {
      

      initializePatches_11_closure() {
        init();
      }
      initializePatches_11_closure(CkMigrateMessage*) {
        init();
      }
            void pup(PUP::er& __p) {
        packClosure(__p);
      }
      virtual ~initializePatches_11_closure() {
      }
      PUPable_decl(SINGLE_ARG(initializePatches_11_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::incTotalPatchCount_12_closure : public SDAG::Closure {
      

      incTotalPatchCount_12_closure() {
        init();
      }
      incTotalPatchCount_12_closure(CkMigrateMessage*) {
        init();
      }
            void pup(PUP::er& __p) {
        packClosure(__p);
      }
      virtual ~incTotalPatchCount_12_closure() {
      }
      PUPable_decl(SINGLE_ARG(incTotalPatchCount_12_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY

    struct Closure_DpcppComputePmeMgr::registerNeighbor_14_closure : public SDAG::Closure {
            int y;
            int z;


      registerNeighbor_14_closure() {
        init();
      }
      registerNeighbor_14_closure(CkMigrateMessage*) {
        init();
      }
            int & getP0() { return y;}
            int & getP1() { return z;}
      void pup(PUP::er& __p) {
        __p | y;
        __p | z;
        packClosure(__p);
      }
      virtual ~registerNeighbor_14_closure() {
      }
      PUPable_decl(SINGLE_ARG(registerNeighbor_14_closure));
    };
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */



/* DEFS: message PmeAtomMsg{
DpcppAtom atoms[];
}
;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_PmeAtomMsg::operator new(size_t s){
  return PmeAtomMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_PmeAtomMsg::operator new(size_t s, int* sz){
  return PmeAtomMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_PmeAtomMsg::operator new(size_t s, int* sz,const int pb){
  return PmeAtomMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_PmeAtomMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return PmeAtomMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_PmeAtomMsg::operator new(size_t s, int sz0) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeAtomMsg::alloc(__idx, s, sizes, 0, GroupDepNum{});
}
void *CMessage_PmeAtomMsg::operator new(size_t s, int sz0, const int p) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeAtomMsg::alloc(__idx, s, sizes, p, GroupDepNum{});
}
void *CMessage_PmeAtomMsg::operator new(size_t s, int sz0, const int p, const GroupDepNum groupDepNum) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeAtomMsg::alloc(__idx, s, sizes, p, groupDepNum);
}
void* CMessage_PmeAtomMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  if(sizes==0)
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0];
  else
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0] + ALIGN_DEFAULT(sizeof(DpcppAtom)*sizes[0]);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[1], pb, groupDepNum);
}
CMessage_PmeAtomMsg::CMessage_PmeAtomMsg() {
PmeAtomMsg *newmsg = (PmeAtomMsg *)this;
  newmsg->atoms = (DpcppAtom *) ((char *)newmsg + CkpvAccess(_offsets)[0]);
}
void CMessage_PmeAtomMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_PmeAtomMsg::pack(PmeAtomMsg *msg) {
  msg->atoms = (DpcppAtom *) ((char *)msg->atoms - (char *)msg);
  return (void *) msg;
}
PmeAtomMsg* CMessage_PmeAtomMsg::unpack(void* buf) {
  PmeAtomMsg *msg = (PmeAtomMsg *) buf;
  msg->atoms = (DpcppAtom *) ((size_t)msg->atoms + (char *)msg);
  return msg;
}
int CMessage_PmeAtomMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message PmeForceMsg{
DpcppForce force[];
}
;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_PmeForceMsg::operator new(size_t s){
  return PmeForceMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_PmeForceMsg::operator new(size_t s, int* sz){
  return PmeForceMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_PmeForceMsg::operator new(size_t s, int* sz,const int pb){
  return PmeForceMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_PmeForceMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return PmeForceMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_PmeForceMsg::operator new(size_t s, int sz0) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeForceMsg::alloc(__idx, s, sizes, 0, GroupDepNum{});
}
void *CMessage_PmeForceMsg::operator new(size_t s, int sz0, const int p) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeForceMsg::alloc(__idx, s, sizes, p, GroupDepNum{});
}
void *CMessage_PmeForceMsg::operator new(size_t s, int sz0, const int p, const GroupDepNum groupDepNum) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeForceMsg::alloc(__idx, s, sizes, p, groupDepNum);
}
void* CMessage_PmeForceMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  if(sizes==0)
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0];
  else
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0] + ALIGN_DEFAULT(sizeof(DpcppForce)*sizes[0]);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[1], pb, groupDepNum);
}
CMessage_PmeForceMsg::CMessage_PmeForceMsg() {
PmeForceMsg *newmsg = (PmeForceMsg *)this;
  newmsg->force = (DpcppForce *) ((char *)newmsg + CkpvAccess(_offsets)[0]);
}
void CMessage_PmeForceMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_PmeForceMsg::pack(PmeForceMsg *msg) {
  msg->force = (DpcppForce *) ((char *)msg->force - (char *)msg);
  return (void *) msg;
}
PmeForceMsg* CMessage_PmeForceMsg::unpack(void* buf) {
  PmeForceMsg *msg = (PmeForceMsg *) buf;
  msg->force = (DpcppForce *) ((size_t)msg->force + (char *)msg);
  return msg;
}
int CMessage_PmeForceMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message PmeLaunchMsg;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_PmeLaunchMsg::operator new(size_t s){
  return PmeLaunchMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_PmeLaunchMsg::operator new(size_t s, int* sz){
  return PmeLaunchMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_PmeLaunchMsg::operator new(size_t s, int* sz,const int pb){
  return PmeLaunchMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_PmeLaunchMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return PmeLaunchMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_PmeLaunchMsg::operator new(size_t s, const int p) {
  return PmeLaunchMsg::alloc(__idx, s, 0, p, GroupDepNum{});
}
void *CMessage_PmeLaunchMsg::operator new(size_t s, const int p, const GroupDepNum groupDepNum) {
  return PmeLaunchMsg::alloc(__idx, s, 0, p, groupDepNum);
}
void* CMessage_PmeLaunchMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[0], pb, groupDepNum);
}
CMessage_PmeLaunchMsg::CMessage_PmeLaunchMsg() {
PmeLaunchMsg *newmsg = (PmeLaunchMsg *)this;
}
void CMessage_PmeLaunchMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_PmeLaunchMsg::pack(PmeLaunchMsg *msg) {
  return (void *) msg;
}
PmeLaunchMsg* CMessage_PmeLaunchMsg::unpack(void* buf) {
  PmeLaunchMsg *msg = (PmeLaunchMsg *) buf;
  return msg;
}
int CMessage_PmeLaunchMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message PmeAtomPencilMsg{
DpcppAtom atoms[];
}
;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_PmeAtomPencilMsg::operator new(size_t s){
  return PmeAtomPencilMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_PmeAtomPencilMsg::operator new(size_t s, int* sz){
  return PmeAtomPencilMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_PmeAtomPencilMsg::operator new(size_t s, int* sz,const int pb){
  return PmeAtomPencilMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_PmeAtomPencilMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return PmeAtomPencilMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_PmeAtomPencilMsg::operator new(size_t s, int sz0) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeAtomPencilMsg::alloc(__idx, s, sizes, 0, GroupDepNum{});
}
void *CMessage_PmeAtomPencilMsg::operator new(size_t s, int sz0, const int p) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeAtomPencilMsg::alloc(__idx, s, sizes, p, GroupDepNum{});
}
void *CMessage_PmeAtomPencilMsg::operator new(size_t s, int sz0, const int p, const GroupDepNum groupDepNum) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeAtomPencilMsg::alloc(__idx, s, sizes, p, groupDepNum);
}
void* CMessage_PmeAtomPencilMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  if(sizes==0)
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0];
  else
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0] + ALIGN_DEFAULT(sizeof(DpcppAtom)*sizes[0]);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[1], pb, groupDepNum);
}
CMessage_PmeAtomPencilMsg::CMessage_PmeAtomPencilMsg() {
PmeAtomPencilMsg *newmsg = (PmeAtomPencilMsg *)this;
  newmsg->atoms = (DpcppAtom *) ((char *)newmsg + CkpvAccess(_offsets)[0]);
}
void CMessage_PmeAtomPencilMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_PmeAtomPencilMsg::pack(PmeAtomPencilMsg *msg) {
  msg->atoms = (DpcppAtom *) ((char *)msg->atoms - (char *)msg);
  return (void *) msg;
}
PmeAtomPencilMsg* CMessage_PmeAtomPencilMsg::unpack(void* buf) {
  PmeAtomPencilMsg *msg = (PmeAtomPencilMsg *) buf;
  msg->atoms = (DpcppAtom *) ((size_t)msg->atoms + (char *)msg);
  return msg;
}
int CMessage_PmeAtomPencilMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message PmeForcePencilMsg{
DpcppForce force[];
}
;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_PmeForcePencilMsg::operator new(size_t s){
  return PmeForcePencilMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_PmeForcePencilMsg::operator new(size_t s, int* sz){
  return PmeForcePencilMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_PmeForcePencilMsg::operator new(size_t s, int* sz,const int pb){
  return PmeForcePencilMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_PmeForcePencilMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return PmeForcePencilMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_PmeForcePencilMsg::operator new(size_t s, int sz0) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeForcePencilMsg::alloc(__idx, s, sizes, 0, GroupDepNum{});
}
void *CMessage_PmeForcePencilMsg::operator new(size_t s, int sz0, const int p) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeForcePencilMsg::alloc(__idx, s, sizes, p, GroupDepNum{});
}
void *CMessage_PmeForcePencilMsg::operator new(size_t s, int sz0, const int p, const GroupDepNum groupDepNum) {
  int sizes[1];
  sizes[0] = sz0;
  return PmeForcePencilMsg::alloc(__idx, s, sizes, p, groupDepNum);
}
void* CMessage_PmeForcePencilMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  if(sizes==0)
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0];
  else
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0] + ALIGN_DEFAULT(sizeof(DpcppForce)*sizes[0]);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[1], pb, groupDepNum);
}
CMessage_PmeForcePencilMsg::CMessage_PmeForcePencilMsg() {
PmeForcePencilMsg *newmsg = (PmeForcePencilMsg *)this;
  newmsg->force = (DpcppForce *) ((char *)newmsg + CkpvAccess(_offsets)[0]);
}
void CMessage_PmeForcePencilMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_PmeForcePencilMsg::pack(PmeForcePencilMsg *msg) {
  msg->force = (DpcppForce *) ((char *)msg->force - (char *)msg);
  return (void *) msg;
}
PmeForcePencilMsg* CMessage_PmeForcePencilMsg::unpack(void* buf) {
  PmeForcePencilMsg *msg = (PmeForcePencilMsg *) buf;
  msg->force = (DpcppForce *) ((size_t)msg->force + (char *)msg);
  return msg;
}
int CMessage_PmeForcePencilMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: group PmeAtomFiler: IrrGroup{
PmeAtomFiler();
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_PmeAtomFiler::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: PmeAtomFiler();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: PmeAtomFiler();
 */
CkGroupID CProxy_PmeAtomFiler::ckNew(const CkEntryOptions *impl_e_opts)
{
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  UsrToEnv(impl_msg)->setMsgtype(BocInitMsg);
  CkGroupID gId = CkCreateGroup(CkIndex_PmeAtomFiler::__idx, CkIndex_PmeAtomFiler::idx_PmeAtomFiler_void(), impl_msg);
  return gId;
}

// Entry point registration function
int CkIndex_PmeAtomFiler::reg_PmeAtomFiler_void() {
  int epidx = CkRegisterEp("PmeAtomFiler()",
      _call_PmeAtomFiler_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_PmeAtomFiler::_call_PmeAtomFiler_void(void* impl_msg, void* impl_obj_void)
{
  PmeAtomFiler* impl_obj = static_cast<PmeAtomFiler*>(impl_obj_void);
  new (impl_obj_void) PmeAtomFiler();
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: PmeAtomFiler();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_PmeAtomFiler::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeGroup);
  CkRegisterBase(__idx, CkIndex_IrrGroup::__idx);
   CkRegisterGroupIrr(__idx,PmeAtomFiler::isIrreducible());
  // REG: PmeAtomFiler();
  idx_PmeAtomFiler_void();
  CkRegisterDefaultCtor(__idx, idx_PmeAtomFiler_void());

}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: nodegroup DpcppComputePmeDevice: NodeGroup{
DpcppComputePmeDevice();
void recvAtoms(PmeAtomMsg* impl_msg);
void sendAtomsToNeighbor(int y, int z, int atomIval);
void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
void gatherForce();
void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
void mergeForcesOnPatch(int homePatchIndex);
void sendForcesToPatch(PmeForceMsg* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_DpcppComputePmeDevice::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputePmeDevice();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeDevice::recvAtoms(PmeAtomMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendAtomsToNeighbor(int y, int z, int atomIval);
 */
void CProxyElement_DpcppComputePmeDevice::sendAtomsToNeighbor(int y, int z, int atomIval, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int y, int z, int atomIval
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|y;
    implP|z;
    implP|atomIval;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|y;
    implP|z;
    implP|atomIval;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeDevice::recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void gatherForce();
 */
void CProxyElement_DpcppComputePmeDevice::gatherForce(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeDevice::recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void mergeForcesOnPatch(int homePatchIndex);
 */
void CProxyElement_DpcppComputePmeDevice::mergeForcesOnPatch(int homePatchIndex, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int homePatchIndex
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|homePatchIndex;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|homePatchIndex;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendForcesToPatch(PmeForceMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeDevice::sendForcesToPatch(PmeForceMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputePmeDevice();
 */
CkGroupID CProxy_DpcppComputePmeDevice::ckNew(const CkEntryOptions *impl_e_opts)
{
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  UsrToEnv(impl_msg)->setMsgtype(NodeBocInitMsg);
  CkGroupID gId = CkCreateNodeGroup(CkIndex_DpcppComputePmeDevice::__idx, CkIndex_DpcppComputePmeDevice::idx_DpcppComputePmeDevice_void(), impl_msg);
  return gId;
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_DpcppComputePmeDevice_void() {
  int epidx = CkRegisterEp("DpcppComputePmeDevice()",
      _call_DpcppComputePmeDevice_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_DpcppComputePmeDevice_void(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  new (impl_obj_void) DpcppComputePmeDevice();
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
void CProxy_DpcppComputePmeDevice::recvAtoms(PmeAtomMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_recvAtoms_PmeAtomMsg() {
  int epidx = CkRegisterEp("recvAtoms(PmeAtomMsg* impl_msg)",
      _call_recvAtoms_PmeAtomMsg, CMessage_PmeAtomMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)PmeAtomMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_recvAtoms_PmeAtomMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  impl_obj->recvAtoms((PmeAtomMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendAtomsToNeighbor(int y, int z, int atomIval);
 */
void CProxy_DpcppComputePmeDevice::sendAtomsToNeighbor(int y, int z, int atomIval, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int y, int z, int atomIval
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|y;
    implP|z;
    implP|atomIval;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|y;
    implP|z;
    implP|atomIval;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_sendAtomsToNeighbor_marshall3() {
  int epidx = CkRegisterEp("sendAtomsToNeighbor(int y, int z, int atomIval)",
      _call_sendAtomsToNeighbor_marshall3, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_sendAtomsToNeighbor_marshall3);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_sendAtomsToNeighbor_marshall3);

  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_sendAtomsToNeighbor_marshall3(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: int y, int z, int atomIval*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<int> y;
  implP|y;
  PUP::detail::TemporaryObjectHolder<int> z;
  implP|z;
  PUP::detail::TemporaryObjectHolder<int> atomIval;
  implP|atomIval;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->sendAtomsToNeighbor(std::move(y.t), std::move(z.t), std::move(atomIval.t));
}
int CkIndex_DpcppComputePmeDevice::_callmarshall_sendAtomsToNeighbor_marshall3(char* impl_buf, void* impl_obj_void) {
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  envelope *env = UsrToEnv(impl_buf);
  /*Unmarshall pup'd fields: int y, int z, int atomIval*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<int> y;
  implP|y;
  PUP::detail::TemporaryObjectHolder<int> z;
  implP|z;
  PUP::detail::TemporaryObjectHolder<int> atomIval;
  implP|atomIval;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->sendAtomsToNeighbor(std::move(y.t), std::move(z.t), std::move(atomIval.t));
  return implP.size();
}
void CkIndex_DpcppComputePmeDevice::_marshallmessagepup_sendAtomsToNeighbor_marshall3(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: int y, int z, int atomIval*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<int> y;
  implP|y;
  PUP::detail::TemporaryObjectHolder<int> z;
  implP|z;
  PUP::detail::TemporaryObjectHolder<int> atomIval;
  implP|atomIval;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("y");
  implDestP|y;
  if (implDestP.hasComments()) implDestP.comment("z");
  implDestP|z;
  if (implDestP.hasComments()) implDestP.comment("atomIval");
  implDestP|atomIval;
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeDevice::sendAtomsToNeighbor_3_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
void CProxy_DpcppComputePmeDevice::recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_recvAtomsFromNeighbor_PmeAtomPencilMsg() {
  int epidx = CkRegisterEp("recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)",
      _call_recvAtomsFromNeighbor_PmeAtomPencilMsg, CMessage_PmeAtomPencilMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)PmeAtomPencilMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_recvAtomsFromNeighbor_PmeAtomPencilMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  impl_obj->recvAtomsFromNeighbor((PmeAtomPencilMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void gatherForce();
 */
void CProxy_DpcppComputePmeDevice::gatherForce(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_gatherForce_void() {
  int epidx = CkRegisterEp("gatherForce()",
      _call_gatherForce_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_gatherForce_void(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  impl_obj->gatherForce();
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeDevice::gatherForce_5_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
void CProxy_DpcppComputePmeDevice::recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_recvForcesFromNeighbor_PmeForcePencilMsg() {
  int epidx = CkRegisterEp("recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)",
      _call_recvForcesFromNeighbor_PmeForcePencilMsg, CMessage_PmeForcePencilMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)PmeForcePencilMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_recvForcesFromNeighbor_PmeForcePencilMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  impl_obj->recvForcesFromNeighbor((PmeForcePencilMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void mergeForcesOnPatch(int homePatchIndex);
 */
void CProxy_DpcppComputePmeDevice::mergeForcesOnPatch(int homePatchIndex, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int homePatchIndex
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|homePatchIndex;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|homePatchIndex;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_mergeForcesOnPatch_marshall7() {
  int epidx = CkRegisterEp("mergeForcesOnPatch(int homePatchIndex)",
      _call_mergeForcesOnPatch_marshall7, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_mergeForcesOnPatch_marshall7);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_mergeForcesOnPatch_marshall7);

  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_mergeForcesOnPatch_marshall7(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: int homePatchIndex*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<int> homePatchIndex;
  implP|homePatchIndex;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->mergeForcesOnPatch(std::move(homePatchIndex.t));
}
int CkIndex_DpcppComputePmeDevice::_callmarshall_mergeForcesOnPatch_marshall7(char* impl_buf, void* impl_obj_void) {
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  envelope *env = UsrToEnv(impl_buf);
  /*Unmarshall pup'd fields: int homePatchIndex*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<int> homePatchIndex;
  implP|homePatchIndex;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->mergeForcesOnPatch(std::move(homePatchIndex.t));
  return implP.size();
}
void CkIndex_DpcppComputePmeDevice::_marshallmessagepup_mergeForcesOnPatch_marshall7(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: int homePatchIndex*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<int> homePatchIndex;
  implP|homePatchIndex;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("homePatchIndex");
  implDestP|homePatchIndex;
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeDevice::mergeForcesOnPatch_7_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendForcesToPatch(PmeForceMsg* impl_msg);
 */
void CProxy_DpcppComputePmeDevice::sendForcesToPatch(PmeForceMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeDevice::reg_sendForcesToPatch_PmeForceMsg() {
  int epidx = CkRegisterEp("sendForcesToPatch(PmeForceMsg* impl_msg)",
      _call_sendForcesToPatch_PmeForceMsg, CMessage_PmeForceMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)PmeForceMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeDevice::_call_sendForcesToPatch_PmeForceMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeDevice* impl_obj = static_cast<DpcppComputePmeDevice*>(impl_obj_void);
  impl_obj->sendForcesToPatch((PmeForceMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputePmeDevice();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeDevice::recvAtoms(PmeAtomMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeDevice::idx_recvAtoms_PmeAtomMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendAtomsToNeighbor(int y, int z, int atomIval);
 */
void CProxySection_DpcppComputePmeDevice::sendAtomsToNeighbor(int y, int z, int atomIval, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int y, int z, int atomIval
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|y;
    implP|z;
    implP|atomIval;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|y;
    implP|z;
    implP|atomIval;
  }
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeDevice::idx_sendAtomsToNeighbor_marshall3(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeDevice::recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeDevice::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void gatherForce();
 */
void CProxySection_DpcppComputePmeDevice::gatherForce(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeDevice::idx_gatherForce_void(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeDevice::recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeDevice::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void mergeForcesOnPatch(int homePatchIndex);
 */
void CProxySection_DpcppComputePmeDevice::mergeForcesOnPatch(int homePatchIndex, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int homePatchIndex
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|homePatchIndex;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|homePatchIndex;
  }
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeDevice::idx_mergeForcesOnPatch_marshall7(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendForcesToPatch(PmeForceMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeDevice::sendForcesToPatch(PmeForceMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeDevice::idx_sendForcesToPatch_PmeForceMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_DpcppComputePmeDevice::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeGroup);
  CkRegisterBase(__idx, CkIndex_NodeGroup::__idx);
   CkRegisterGroupIrr(__idx,DpcppComputePmeDevice::isIrreducible());
  // REG: DpcppComputePmeDevice();
  idx_DpcppComputePmeDevice_void();
  CkRegisterDefaultCtor(__idx, idx_DpcppComputePmeDevice_void());

  // REG: void recvAtoms(PmeAtomMsg* impl_msg);
  idx_recvAtoms_PmeAtomMsg();

  // REG: void sendAtomsToNeighbor(int y, int z, int atomIval);
  idx_sendAtomsToNeighbor_marshall3();

  // REG: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
  idx_recvAtomsFromNeighbor_PmeAtomPencilMsg();

  // REG: void gatherForce();
  idx_gatherForce_void();

  // REG: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
  idx_recvForcesFromNeighbor_PmeForcePencilMsg();

  // REG: void mergeForcesOnPatch(int homePatchIndex);
  idx_mergeForcesOnPatch_marshall7();

  // REG: void sendForcesToPatch(PmeForceMsg* impl_msg);
  idx_sendForcesToPatch_PmeForceMsg();

}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message RegisterPatchMsg;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_RegisterPatchMsg::operator new(size_t s){
  return RegisterPatchMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_RegisterPatchMsg::operator new(size_t s, int* sz){
  return RegisterPatchMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_RegisterPatchMsg::operator new(size_t s, int* sz,const int pb){
  return RegisterPatchMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_RegisterPatchMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return RegisterPatchMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_RegisterPatchMsg::operator new(size_t s, const int p) {
  return RegisterPatchMsg::alloc(__idx, s, 0, p, GroupDepNum{});
}
void *CMessage_RegisterPatchMsg::operator new(size_t s, const int p, const GroupDepNum groupDepNum) {
  return RegisterPatchMsg::alloc(__idx, s, 0, p, groupDepNum);
}
void* CMessage_RegisterPatchMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[0], pb, groupDepNum);
}
CMessage_RegisterPatchMsg::CMessage_RegisterPatchMsg() {
RegisterPatchMsg *newmsg = (RegisterPatchMsg *)this;
}
void CMessage_RegisterPatchMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_RegisterPatchMsg::pack(RegisterPatchMsg *msg) {
  return (void *) msg;
}
RegisterPatchMsg* CMessage_RegisterPatchMsg::unpack(void* buf) {
  RegisterPatchMsg *msg = (RegisterPatchMsg *) buf;
  return msg;
}
int CMessage_RegisterPatchMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message NumDevicesMsg;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_NumDevicesMsg::operator new(size_t s){
  return NumDevicesMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_NumDevicesMsg::operator new(size_t s, int* sz){
  return NumDevicesMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_NumDevicesMsg::operator new(size_t s, int* sz,const int pb){
  return NumDevicesMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_NumDevicesMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return NumDevicesMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_NumDevicesMsg::operator new(size_t s, const int p) {
  return NumDevicesMsg::alloc(__idx, s, 0, p, GroupDepNum{});
}
void *CMessage_NumDevicesMsg::operator new(size_t s, const int p, const GroupDepNum groupDepNum) {
  return NumDevicesMsg::alloc(__idx, s, 0, p, groupDepNum);
}
void* CMessage_NumDevicesMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[0], pb, groupDepNum);
}
CMessage_NumDevicesMsg::CMessage_NumDevicesMsg() {
NumDevicesMsg *newmsg = (NumDevicesMsg *)this;
}
void CMessage_NumDevicesMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_NumDevicesMsg::pack(NumDevicesMsg *msg) {
  return (void *) msg;
}
NumDevicesMsg* CMessage_NumDevicesMsg::unpack(void* buf) {
  NumDevicesMsg *msg = (NumDevicesMsg *) buf;
  return msg;
}
int CMessage_NumDevicesMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */


/* DEFS: message RecvDeviceMsg{
CProxy_DpcppComputePmeDevice dev[];
}
;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_RecvDeviceMsg::operator new(size_t s){
  return RecvDeviceMsg::alloc(__idx, s, 0, 0, GroupDepNum{});
}
void *CMessage_RecvDeviceMsg::operator new(size_t s, int* sz){
  return RecvDeviceMsg::alloc(__idx, s, sz, 0, GroupDepNum{});
}
void *CMessage_RecvDeviceMsg::operator new(size_t s, int* sz,const int pb){
  return RecvDeviceMsg::alloc(__idx, s, sz, pb, GroupDepNum{});
}
void *CMessage_RecvDeviceMsg::operator new(size_t s, int* sz,const int pb, const GroupDepNum groupDepNum){
  return RecvDeviceMsg::alloc(__idx, s, sz, pb, groupDepNum);
}
void *CMessage_RecvDeviceMsg::operator new(size_t s, int sz0) {
  int sizes[1];
  sizes[0] = sz0;
  return RecvDeviceMsg::alloc(__idx, s, sizes, 0, GroupDepNum{});
}
void *CMessage_RecvDeviceMsg::operator new(size_t s, int sz0, const int p) {
  int sizes[1];
  sizes[0] = sz0;
  return RecvDeviceMsg::alloc(__idx, s, sizes, p, GroupDepNum{});
}
void *CMessage_RecvDeviceMsg::operator new(size_t s, int sz0, const int p, const GroupDepNum groupDepNum) {
  int sizes[1];
  sizes[0] = sz0;
  return RecvDeviceMsg::alloc(__idx, s, sizes, p, groupDepNum);
}
void* CMessage_RecvDeviceMsg::alloc(int msgnum, size_t sz, int *sizes, int pb, GroupDepNum groupDepNum) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  if(sizes==0)
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0];
  else
    CkpvAccess(_offsets)[1] = CkpvAccess(_offsets)[0] + ALIGN_DEFAULT(sizeof(CProxy_DpcppComputePmeDevice)*sizes[0]);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[1], pb, groupDepNum);
}
CMessage_RecvDeviceMsg::CMessage_RecvDeviceMsg() {
RecvDeviceMsg *newmsg = (RecvDeviceMsg *)this;
  newmsg->dev = (CProxy_DpcppComputePmeDevice *) ((char *)newmsg + CkpvAccess(_offsets)[0]);
}
void CMessage_RecvDeviceMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_RecvDeviceMsg::pack(RecvDeviceMsg *msg) {
  msg->dev = (CProxy_DpcppComputePmeDevice *) ((char *)msg->dev - (char *)msg);
  return (void *) msg;
}
RecvDeviceMsg* CMessage_RecvDeviceMsg::unpack(void* buf) {
  RecvDeviceMsg *msg = (RecvDeviceMsg *) buf;
  msg->dev = (CProxy_DpcppComputePmeDevice *) ((size_t)msg->dev + (char *)msg);
  return msg;
}
int CMessage_RecvDeviceMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: nodegroup DpcppComputePmeMgr: NodeGroup{
DpcppComputePmeMgr();
void initialize_pencils(CkQdMsg* impl_msg);
void activate_pencils(CkQdMsg* impl_msg);
void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
void recvDevices(RecvDeviceMsg* impl_msg);
void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
void skip();
void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
void initializePatches();
void incTotalPatchCount();
void registerPatch(RegisterPatchMsg* impl_msg);
void registerNeighbor(int y, int z);
void recvAtoms(PmeAtomMsg* impl_msg);
void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_DpcppComputePmeMgr::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputePmeMgr();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initialize_pencils(CkQdMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::initialize_pencils(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void activate_pencils(CkQdMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::activate_pencils(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
 */
void CProxyElement_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilXYZ &xyz, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilXYZ &xyz
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXYZ>::type>::type &)xyz;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXYZ>::type>::type &)xyz;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
 */
void CProxyElement_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXY>::type>::type &)xy;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXY>::type>::type &)xy;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
 */
void CProxyElement_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilX>::type>::type &)x;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilY>::type>::type &)y;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilX>::type>::type &)x;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilY>::type>::type &)y;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvDevices(RecvDeviceMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::recvDevices(RecvDeviceMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
 */
void CProxyElement_DpcppComputePmeMgr::recvAtomFiler(const CProxy_PmeAtomFiler &filer, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_PmeAtomFiler &filer
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_PmeAtomFiler>::type>::type &)filer;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_PmeAtomFiler>::type>::type &)filer;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void skip();
 */
void CProxyElement_DpcppComputePmeMgr::skip(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initializePatches();
 */
void CProxyElement_DpcppComputePmeMgr::initializePatches(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void incTotalPatchCount();
 */
void CProxyElement_DpcppComputePmeMgr::incTotalPatchCount(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void registerPatch(RegisterPatchMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::registerPatch(RegisterPatchMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void registerNeighbor(int y, int z);
 */
void CProxyElement_DpcppComputePmeMgr::registerNeighbor(int y, int z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int y, int z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|y;
    implP|z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|y;
    implP|z;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::recvAtoms(PmeAtomMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
void CProxyElement_DpcppComputePmeMgr::recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputePmeMgr();
 */
CkGroupID CProxy_DpcppComputePmeMgr::ckNew(const CkEntryOptions *impl_e_opts)
{
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  UsrToEnv(impl_msg)->setMsgtype(NodeBocInitMsg);
  CkGroupID gId = CkCreateNodeGroup(CkIndex_DpcppComputePmeMgr::__idx, CkIndex_DpcppComputePmeMgr::idx_DpcppComputePmeMgr_void(), impl_msg);
  return gId;
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_DpcppComputePmeMgr_void() {
  int epidx = CkRegisterEp("DpcppComputePmeMgr()",
      _call_DpcppComputePmeMgr_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_DpcppComputePmeMgr_void(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  new (impl_obj_void) DpcppComputePmeMgr();
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initialize_pencils(CkQdMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::initialize_pencils(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_initialize_pencils_CkQdMsg() {
  int epidx = CkRegisterEp("initialize_pencils(CkQdMsg* impl_msg)",
      _call_initialize_pencils_CkQdMsg, CMessage_CkQdMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)CkQdMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_initialize_pencils_CkQdMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  impl_obj->initialize_pencils((CkQdMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void activate_pencils(CkQdMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::activate_pencils(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_activate_pencils_CkQdMsg() {
  int epidx = CkRegisterEp("activate_pencils(CkQdMsg* impl_msg)",
      _call_activate_pencils_CkQdMsg, CMessage_CkQdMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)CkQdMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_activate_pencils_CkQdMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  impl_obj->activate_pencils((CkQdMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
 */
void CProxy_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilXYZ &xyz, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilXYZ &xyz
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXYZ>::type>::type &)xyz;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXYZ>::type>::type &)xyz;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvPencils_marshall4() {
  int epidx = CkRegisterEp("recvPencils(const CProxy_DpcppPmePencilXYZ &xyz)",
      _call_recvPencils_marshall4, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_recvPencils_marshall4);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_recvPencils_marshall4);

  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvPencils_marshall4(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilXYZ &xyz*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilXYZ> xyz;
  implP|xyz;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvPencils(std::move(xyz.t));
}
int CkIndex_DpcppComputePmeMgr::_callmarshall_recvPencils_marshall4(char* impl_buf, void* impl_obj_void) {
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  envelope *env = UsrToEnv(impl_buf);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilXYZ &xyz*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilXYZ> xyz;
  implP|xyz;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvPencils(std::move(xyz.t));
  return implP.size();
}
void CkIndex_DpcppComputePmeMgr::_marshallmessagepup_recvPencils_marshall4(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilXYZ &xyz*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilXYZ> xyz;
  implP|xyz;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("xyz");
  implDestP|xyz;
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_4_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
 */
void CProxy_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXY>::type>::type &)xy;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXY>::type>::type &)xy;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvPencils_marshall5() {
  int epidx = CkRegisterEp("recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z)",
      _call_recvPencils_marshall5, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_recvPencils_marshall5);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_recvPencils_marshall5);

  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvPencils_marshall5(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilXY> xy;
  implP|xy;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilZ> z;
  implP|z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvPencils(std::move(xy.t), std::move(z.t));
}
int CkIndex_DpcppComputePmeMgr::_callmarshall_recvPencils_marshall5(char* impl_buf, void* impl_obj_void) {
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  envelope *env = UsrToEnv(impl_buf);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilXY> xy;
  implP|xy;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilZ> z;
  implP|z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvPencils(std::move(xy.t), std::move(z.t));
  return implP.size();
}
void CkIndex_DpcppComputePmeMgr::_marshallmessagepup_recvPencils_marshall5(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilXY> xy;
  implP|xy;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilZ> z;
  implP|z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("xy");
  implDestP|xy;
  if (implDestP.hasComments()) implDestP.comment("z");
  implDestP|z;
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_5_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
 */
void CProxy_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilX>::type>::type &)x;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilY>::type>::type &)y;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilX>::type>::type &)x;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilY>::type>::type &)y;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvPencils_marshall6() {
  int epidx = CkRegisterEp("recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z)",
      _call_recvPencils_marshall6, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_recvPencils_marshall6);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_recvPencils_marshall6);

  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvPencils_marshall6(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilX> x;
  implP|x;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilY> y;
  implP|y;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilZ> z;
  implP|z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvPencils(std::move(x.t), std::move(y.t), std::move(z.t));
}
int CkIndex_DpcppComputePmeMgr::_callmarshall_recvPencils_marshall6(char* impl_buf, void* impl_obj_void) {
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  envelope *env = UsrToEnv(impl_buf);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilX> x;
  implP|x;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilY> y;
  implP|y;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilZ> z;
  implP|z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvPencils(std::move(x.t), std::move(y.t), std::move(z.t));
  return implP.size();
}
void CkIndex_DpcppComputePmeMgr::_marshallmessagepup_recvPencils_marshall6(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilX> x;
  implP|x;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilY> y;
  implP|y;
  PUP::detail::TemporaryObjectHolder<CProxy_DpcppPmePencilZ> z;
  implP|z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("x");
  implDestP|x;
  if (implDestP.hasComments()) implDestP.comment("y");
  implDestP|y;
  if (implDestP.hasComments()) implDestP.comment("z");
  implDestP|z;
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_6_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvDevices(RecvDeviceMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::recvDevices(RecvDeviceMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvDevices_RecvDeviceMsg() {
  int epidx = CkRegisterEp("recvDevices(RecvDeviceMsg* impl_msg)",
      _call_recvDevices_RecvDeviceMsg, CMessage_RecvDeviceMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)RecvDeviceMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvDevices_RecvDeviceMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  impl_obj->recvDevices((RecvDeviceMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
 */
void CProxy_DpcppComputePmeMgr::recvAtomFiler(const CProxy_PmeAtomFiler &filer, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_PmeAtomFiler &filer
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_PmeAtomFiler>::type>::type &)filer;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_PmeAtomFiler>::type>::type &)filer;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvAtomFiler_marshall8() {
  int epidx = CkRegisterEp("recvAtomFiler(const CProxy_PmeAtomFiler &filer)",
      _call_recvAtomFiler_marshall8, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_recvAtomFiler_marshall8);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_recvAtomFiler_marshall8);

  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvAtomFiler_marshall8(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_PmeAtomFiler &filer*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_PmeAtomFiler> filer;
  implP|filer;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvAtomFiler(std::move(filer.t));
}
int CkIndex_DpcppComputePmeMgr::_callmarshall_recvAtomFiler_marshall8(char* impl_buf, void* impl_obj_void) {
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  envelope *env = UsrToEnv(impl_buf);
  /*Unmarshall pup'd fields: const CProxy_PmeAtomFiler &filer*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_PmeAtomFiler> filer;
  implP|filer;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  impl_obj->recvAtomFiler(std::move(filer.t));
  return implP.size();
}
void CkIndex_DpcppComputePmeMgr::_marshallmessagepup_recvAtomFiler_marshall8(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: const CProxy_PmeAtomFiler &filer*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<CProxy_PmeAtomFiler> filer;
  implP|filer;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("filer");
  implDestP|filer;
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvAtomFiler_8_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void skip();
 */
void CProxy_DpcppComputePmeMgr::skip(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_skip_void() {
  int epidx = CkRegisterEp("skip()",
      _call_skip_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_skip_void(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  impl_obj->skip();
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::skip_9_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_initializeDevicesAndAtomFiler_NumDevicesMsg() {
  int epidx = CkRegisterEp("initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg)",
      _call_initializeDevicesAndAtomFiler_NumDevicesMsg, CMessage_NumDevicesMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)NumDevicesMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_initializeDevicesAndAtomFiler_NumDevicesMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  if(CmiTryLock(impl_obj->__nodelock)) {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(),impl_msg,CkMyNode(),impl_obj->CkGetNodeGroupID());
    return;
  }
  impl_obj->initializeDevicesAndAtomFiler((NumDevicesMsg*)impl_msg);
  CmiUnlock(impl_obj->__nodelock);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initializePatches();
 */
void CProxy_DpcppComputePmeMgr::initializePatches(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_initializePatches_void() {
  int epidx = CkRegisterEp("initializePatches()",
      _call_initializePatches_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_initializePatches_void(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  if(CmiTryLock(impl_obj->__nodelock)) {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(),impl_msg,CkMyNode(),impl_obj->CkGetNodeGroupID());
    return;
  }
  impl_obj->initializePatches();
  CmiUnlock(impl_obj->__nodelock);
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::initializePatches_11_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void incTotalPatchCount();
 */
void CProxy_DpcppComputePmeMgr::incTotalPatchCount(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_incTotalPatchCount_void() {
  int epidx = CkRegisterEp("incTotalPatchCount()",
      _call_incTotalPatchCount_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_incTotalPatchCount_void(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  if(CmiTryLock(impl_obj->__nodelock)) {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(),impl_msg,CkMyNode(),impl_obj->CkGetNodeGroupID());
    return;
  }
  impl_obj->incTotalPatchCount();
  CmiUnlock(impl_obj->__nodelock);
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::incTotalPatchCount_12_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void registerPatch(RegisterPatchMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::registerPatch(RegisterPatchMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_registerPatch_RegisterPatchMsg() {
  int epidx = CkRegisterEp("registerPatch(RegisterPatchMsg* impl_msg)",
      _call_registerPatch_RegisterPatchMsg, CMessage_RegisterPatchMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)RegisterPatchMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_registerPatch_RegisterPatchMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  if(CmiTryLock(impl_obj->__nodelock)) {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(),impl_msg,CkMyNode(),impl_obj->CkGetNodeGroupID());
    return;
  }
  impl_obj->registerPatch((RegisterPatchMsg*)impl_msg);
  CmiUnlock(impl_obj->__nodelock);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void registerNeighbor(int y, int z);
 */
void CProxy_DpcppComputePmeMgr::registerNeighbor(int y, int z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int y, int z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|y;
    implP|z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|y;
    implP|z;
  }
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_registerNeighbor_marshall14() {
  int epidx = CkRegisterEp("registerNeighbor(int y, int z)",
      _call_registerNeighbor_marshall14, CkMarshallMsg::__idx, __idx, 0+CK_EP_NOKEEP);
  CkRegisterMarshallUnpackFn(epidx, _callmarshall_registerNeighbor_marshall14);
  CkRegisterMessagePupFn(epidx, _marshallmessagepup_registerNeighbor_marshall14);

  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_registerNeighbor_marshall14(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  if(CmiTryLock(impl_obj->__nodelock)) {
    impl_msg = CkCopyMsg(&impl_msg);
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(),impl_msg,CkMyNode(),impl_obj->CkGetNodeGroupID());
    return;
  }
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  PUP::fromMem implP(impl_buf);
  Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* genClosure = new Closure_DpcppComputePmeMgr::registerNeighbor_14_closure();
  implP|genClosure->y;
  implP|genClosure->z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  impl_obj->registerNeighbor(genClosure);
  genClosure->deref();
  CmiUnlock(impl_obj->__nodelock);
}
int CkIndex_DpcppComputePmeMgr::_callmarshall_registerNeighbor_marshall14(char* impl_buf, void* impl_obj_void) {
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  envelope *env = UsrToEnv(impl_buf);
  PUP::fromMem implP(impl_buf);
  Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* genClosure = new Closure_DpcppComputePmeMgr::registerNeighbor_14_closure();
  implP|genClosure->y;
  implP|genClosure->z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  impl_obj->registerNeighbor(genClosure);
  genClosure->deref();
  return implP.size();
}
void CkIndex_DpcppComputePmeMgr::_marshallmessagepup_registerNeighbor_marshall14(PUP::er &implDestP,void *impl_msg) {
  CkMarshallMsg *impl_msg_typed=(CkMarshallMsg *)impl_msg;
  char *impl_buf=impl_msg_typed->msgBuf;
  envelope *env = UsrToEnv(impl_msg_typed);
  /*Unmarshall pup'd fields: int y, int z*/
  PUP::fromMem implP(impl_buf);
  PUP::detail::TemporaryObjectHolder<int> y;
  implP|y;
  PUP::detail::TemporaryObjectHolder<int> z;
  implP|z;
  impl_buf+=CK_ALIGN(implP.size(),16);
  /*Unmarshall arrays:*/
  if (implDestP.hasComments()) implDestP.comment("y");
  implDestP|y;
  if (implDestP.hasComments()) implDestP.comment("z");
  implDestP|z;
}
PUPable_def(SINGLE_ARG(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure))
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::recvAtoms(PmeAtomMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvAtoms_PmeAtomMsg() {
  int epidx = CkRegisterEp("recvAtoms(PmeAtomMsg* impl_msg)",
      _call_recvAtoms_PmeAtomMsg, CMessage_PmeAtomMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)PmeAtomMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvAtoms_PmeAtomMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  impl_obj->recvAtoms((PmeAtomMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvAtomsFromNeighbor_PmeAtomPencilMsg() {
  int epidx = CkRegisterEp("recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)",
      _call_recvAtomsFromNeighbor_PmeAtomPencilMsg, CMessage_PmeAtomPencilMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)PmeAtomPencilMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvAtomsFromNeighbor_PmeAtomPencilMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  if(CmiTryLock(impl_obj->__nodelock)) {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(),impl_msg,CkMyNode(),impl_obj->CkGetNodeGroupID());
    return;
  }
  impl_obj->recvAtomsFromNeighbor((PmeAtomPencilMsg*)impl_msg);
  CmiUnlock(impl_obj->__nodelock);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
void CProxy_DpcppComputePmeMgr::recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputePmeMgr::reg_recvForcesFromNeighbor_PmeForcePencilMsg() {
  int epidx = CkRegisterEp("recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)",
      _call_recvForcesFromNeighbor_PmeForcePencilMsg, CMessage_PmeForcePencilMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)PmeForcePencilMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputePmeMgr::_call_recvForcesFromNeighbor_PmeForcePencilMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputePmeMgr* impl_obj = static_cast<DpcppComputePmeMgr*>(impl_obj_void);
  if(CmiTryLock(impl_obj->__nodelock)) {
    CkSendMsgNodeBranch(CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(),impl_msg,CkMyNode(),impl_obj->CkGetNodeGroupID());
    return;
  }
  impl_obj->recvForcesFromNeighbor((PmeForcePencilMsg*)impl_msg);
  CmiUnlock(impl_obj->__nodelock);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputePmeMgr();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initialize_pencils(CkQdMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::initialize_pencils(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_initialize_pencils_CkQdMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void activate_pencils(CkQdMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::activate_pencils(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_activate_pencils_CkQdMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
 */
void CProxySection_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilXYZ &xyz, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilXYZ &xyz
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXYZ>::type>::type &)xyz;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXYZ>::type>::type &)xyz;
  }
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall4(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
 */
void CProxySection_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXY>::type>::type &)xy;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilXY>::type>::type &)xy;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
  }
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall5(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
 */
void CProxySection_DpcppComputePmeMgr::recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilX>::type>::type &)x;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilY>::type>::type &)y;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilX>::type>::type &)x;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilY>::type>::type &)y;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_DpcppPmePencilZ>::type>::type &)z;
  }
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvPencils_marshall6(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvDevices(RecvDeviceMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::recvDevices(RecvDeviceMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvDevices_RecvDeviceMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
 */
void CProxySection_DpcppComputePmeMgr::recvAtomFiler(const CProxy_PmeAtomFiler &filer, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: const CProxy_PmeAtomFiler &filer
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_PmeAtomFiler>::type>::type &)filer;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    //Have to cast away const-ness to get pup routine
    implP|(typename std::remove_cv<typename std::remove_reference<CProxy_PmeAtomFiler>::type>::type &)filer;
  }
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvAtomFiler_marshall8(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void skip();
 */
void CProxySection_DpcppComputePmeMgr::skip(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_skip_void(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_initializeDevicesAndAtomFiler_NumDevicesMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initializePatches();
 */
void CProxySection_DpcppComputePmeMgr::initializePatches(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_initializePatches_void(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void incTotalPatchCount();
 */
void CProxySection_DpcppComputePmeMgr::incTotalPatchCount(const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_incTotalPatchCount_void(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void registerPatch(RegisterPatchMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::registerPatch(RegisterPatchMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_registerPatch_RegisterPatchMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void registerNeighbor(int y, int z);
 */
void CProxySection_DpcppComputePmeMgr::registerNeighbor(int y, int z, const CkEntryOptions *impl_e_opts)
{
  ckCheck();
  //Marshall: int y, int z
  int impl_off=0;
  { //Find the size of the PUP'd data
    PUP::sizer implP;
    implP|y;
    implP|z;
    impl_off+=implP.size();
  }
  CkMarshallMsg *impl_msg=CkAllocateMarshallMsg(impl_off,impl_e_opts);
  { //Copy over the PUP'd data
    PUP::toMem implP((void *)impl_msg->msgBuf);
    implP|y;
    implP|z;
  }
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_registerNeighbor_marshall14(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::recvAtoms(PmeAtomMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvAtoms_PmeAtomMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
void CProxySection_DpcppComputePmeMgr::recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputePmeMgr::idx_recvForcesFromNeighbor_PmeForcePencilMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_DpcppComputePmeMgr::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeGroup);
  CkRegisterBase(__idx, CkIndex_NodeGroup::__idx);
   CkRegisterGroupIrr(__idx,DpcppComputePmeMgr::isIrreducible());
  // REG: DpcppComputePmeMgr();
  idx_DpcppComputePmeMgr_void();
  CkRegisterDefaultCtor(__idx, idx_DpcppComputePmeMgr_void());

  // REG: void initialize_pencils(CkQdMsg* impl_msg);
  idx_initialize_pencils_CkQdMsg();

  // REG: void activate_pencils(CkQdMsg* impl_msg);
  idx_activate_pencils_CkQdMsg();

  // REG: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
  idx_recvPencils_marshall4();

  // REG: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
  idx_recvPencils_marshall5();

  // REG: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
  idx_recvPencils_marshall6();

  // REG: void recvDevices(RecvDeviceMsg* impl_msg);
  idx_recvDevices_RecvDeviceMsg();

  // REG: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
  idx_recvAtomFiler_marshall8();

  // REG: void skip();
  idx_skip_void();

  // REG: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
  idx_initializeDevicesAndAtomFiler_NumDevicesMsg();

  // REG: void initializePatches();
  idx_initializePatches_void();

  // REG: void incTotalPatchCount();
  idx_incTotalPatchCount_void();

  // REG: void registerPatch(RegisterPatchMsg* impl_msg);
  idx_registerPatch_RegisterPatchMsg();

  // REG: void registerNeighbor(int y, int z);
  idx_registerNeighbor_marshall14();

  // REG: void recvAtoms(PmeAtomMsg* impl_msg);
  idx_recvAtoms_PmeAtomMsg();

  // REG: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
  idx_recvAtomsFromNeighbor_PmeAtomPencilMsg();

  // REG: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
  idx_recvForcesFromNeighbor_PmeForcePencilMsg();

  DpcppComputePmeMgr::__sdag_register(); // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::initializeDevicesAndAtomFiler(NumDevicesMsg* gen0) {
  _TRACE_END_EXECUTE(); 
  if (!__dep.get()) _sdag_init();
  CmiReference(UsrToEnv(gen0));
  _slist_0(gen0);
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _sdagEP, CkMyPe(), 0, NULL, this); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::initializeDevicesAndAtomFiler_end(NumDevicesMsg* gen0) {
  CmiFree(UsrToEnv(gen0));
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_0(NumDevicesMsg* gen0) {
  _serial_0(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_0_end(NumDevicesMsg* gen0) {
  initializeDevicesAndAtomFiler_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_serial_0(NumDevicesMsg* gen0) {
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_DpcppComputePmeMgr_serial_0()), CkMyPe(), 0, NULL, this); 
  {
    NumDevicesMsg*& msg = gen0;
    { // begin serial block
#line 46 "inc/DpcppComputePmeMgr.ci"

        if (CkMyNode() != 0)
          NAMD_bug("DpcppComputePmeMgr::initializeDevicesAndAtomFiler can only be called on root node");
        numNodesContributed++;
        numDevicesMax = (numDevicesMax >= msg->numDevices) ? numDevicesMax : msg->numDevices;
        delete msg;
        if (numNodesContributed == CkNumNodes()) {
          createDevicesAndAtomFiler();
        }
      
#line 3138 "DpcppComputePmeMgr.def.h"
    } // end serial block
  }
  _TRACE_END_EXECUTE(); 
  _slist_0_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::initializePatches() {
  _TRACE_END_EXECUTE(); 
  if (!__dep.get()) _sdag_init();
  _slist_1();
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _sdagEP, CkMyPe(), 0, NULL, this); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::initializePatches_end() {
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_1() {
  _serial_1();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_1_end() {
  initializePatches_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_serial_1() {
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_DpcppComputePmeMgr_serial_1()), CkMyPe(), 0, NULL, this); 
  { // begin serial block
#line 58 "inc/DpcppComputePmeMgr.ci"

        int i;
        for (i=0;i < numDevices;i++) {
          deviceProxy[i][CkMyNode()].ckLocalBranch()->initializePatches(numHomePatchesList[i]);
        }
      
#line 3188 "DpcppComputePmeMgr.def.h"
  } // end serial block
  _TRACE_END_EXECUTE(); 
  _slist_1_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::incTotalPatchCount() {
  _TRACE_END_EXECUTE(); 
  if (!__dep.get()) _sdag_init();
  _slist_2();
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _sdagEP, CkMyPe(), 0, NULL, this); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::incTotalPatchCount_end() {
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_2() {
  _serial_2();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_2_end() {
  incTotalPatchCount_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_serial_2() {
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_DpcppComputePmeMgr_serial_2()), CkMyPe(), 0, NULL, this); 
  { // begin serial block
#line 66 "inc/DpcppComputePmeMgr.ci"

        if (CkMyNode() != 0)
          NAMD_bug("DpcppComputePmeMgr::incTotalPatchCount can only be called on root node");
        numTotalPatches++;
        if (numTotalPatches == PatchMap::Object()->numPatches()) {
          thisProxy.initializePatches();
        }
      
#line 3239 "DpcppComputePmeMgr.def.h"
  } // end serial block
  _TRACE_END_EXECUTE(); 
  _slist_2_end();
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::registerPatch(RegisterPatchMsg* gen0) {
  _TRACE_END_EXECUTE(); 
  if (!__dep.get()) _sdag_init();
  CmiReference(UsrToEnv(gen0));
  _slist_3(gen0);
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _sdagEP, CkMyPe(), 0, NULL, this); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::registerPatch_end(RegisterPatchMsg* gen0) {
  CmiFree(UsrToEnv(gen0));
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_3(RegisterPatchMsg* gen0) {
  _serial_3(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_3_end(RegisterPatchMsg* gen0) {
  registerPatch_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_serial_3(RegisterPatchMsg* gen0) {
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_DpcppComputePmeMgr_serial_3()), CkMyPe(), 0, NULL, this); 
  {
    RegisterPatchMsg*& msg = gen0;
    { // begin serial block
#line 76 "inc/DpcppComputePmeMgr.ci"

        int device = getDevice(msg->i, msg->j);
        numHomePatchesList[device]++;
        delete msg;
        thisProxy[0].incTotalPatchCount();
      
#line 3292 "DpcppComputePmeMgr.def.h"
    } // end serial block
  }
  _TRACE_END_EXECUTE(); 
  _slist_3_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::registerNeighbor(int y, int z){
  Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* genClosure = new Closure_DpcppComputePmeMgr::registerNeighbor_14_closure();
  genClosure->getP0() = y;
  genClosure->getP1() = z;
  registerNeighbor(genClosure);
  genClosure->deref();
}

#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::registerNeighbor(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0) {
  _TRACE_END_EXECUTE(); 
  if (!__dep.get()) _sdag_init();
  _slist_4(gen0);
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _sdagEP, CkMyPe(), 0, NULL, this); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::registerNeighbor_end(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0) {
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_4(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0) {
  _serial_4(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_4_end(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0) {
  registerNeighbor_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_serial_4(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0) {
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_DpcppComputePmeMgr_serial_4()), CkMyPe(), 0, NULL, this); 
  {
    int& y = gen0->getP0();
    int& z = gen0->getP1();
    { // begin serial block
#line 84 "inc/DpcppComputePmeMgr.ci"

        int device = getDevice(y, z);
        deviceProxy[device].ckLocalBranch()->registerNeighbor();
      
#line 3353 "DpcppComputePmeMgr.def.h"
    } // end serial block
  }
  _TRACE_END_EXECUTE(); 
  _slist_4_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::recvAtomsFromNeighbor(PmeAtomPencilMsg* gen0) {
  _TRACE_END_EXECUTE(); 
  if (!__dep.get()) _sdag_init();
  CmiReference(UsrToEnv(gen0));
  _slist_5(gen0);
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _sdagEP, CkMyPe(), 0, NULL, this); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::recvAtomsFromNeighbor_end(PmeAtomPencilMsg* gen0) {
  CmiFree(UsrToEnv(gen0));
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_5(PmeAtomPencilMsg* gen0) {
  _serial_5(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_5_end(PmeAtomPencilMsg* gen0) {
  recvAtomsFromNeighbor_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_serial_5(PmeAtomPencilMsg* gen0) {
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_DpcppComputePmeMgr_serial_5()), CkMyPe(), 0, NULL, this); 
  {
    PmeAtomPencilMsg*& msg = gen0;
    { // begin serial block
#line 91 "inc/DpcppComputePmeMgr.ci"

        int device = getDevice(msg->y, msg->z);
        deviceProxy[device].ckLocalBranch()->recvAtomsFromNeighbor(msg);
      
#line 3405 "DpcppComputePmeMgr.def.h"
    } // end serial block
  }
  _TRACE_END_EXECUTE(); 
  _slist_5_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::recvForcesFromNeighbor(PmeForcePencilMsg* gen0) {
  _TRACE_END_EXECUTE(); 
  if (!__dep.get()) _sdag_init();
  CmiReference(UsrToEnv(gen0));
  _slist_6(gen0);
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, _sdagEP, CkMyPe(), 0, NULL, this); 
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::recvForcesFromNeighbor_end(PmeForcePencilMsg* gen0) {
  CmiFree(UsrToEnv(gen0));
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_6(PmeForcePencilMsg* gen0) {
  _serial_6(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_slist_6_end(PmeForcePencilMsg* gen0) {
  recvForcesFromNeighbor_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_serial_6(PmeForcePencilMsg* gen0) {
  _TRACE_BEGIN_EXECUTE_DETAILED(-1, -1, (_sdag_idx_DpcppComputePmeMgr_serial_6()), CkMyPe(), 0, NULL, this); 
  {
    PmeForcePencilMsg*& msg = gen0;
    { // begin serial block
#line 97 "inc/DpcppComputePmeMgr.ci"

        int device = getDevice(msg->y, msg->z);
        deviceProxy[device].ckLocalBranch()->recvForcesFromNeighbor(msg);
      
#line 3457 "DpcppComputePmeMgr.def.h"
    } // end serial block
  }
  _TRACE_END_EXECUTE(); 
  _slist_6_end(gen0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_sdag_init() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  __dep.reset(new SDAG::Dependency(0,0));
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::__sdag_init() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::_sdag_pup(PUP::er &p) {  // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  p|__dep;
}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void DpcppComputePmeMgr::__sdag_register() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  (void)_sdag_idx_DpcppComputePmeMgr_serial_0();
  (void)_sdag_idx_DpcppComputePmeMgr_serial_1();
  (void)_sdag_idx_DpcppComputePmeMgr_serial_2();
  (void)_sdag_idx_DpcppComputePmeMgr_serial_3();
  (void)_sdag_idx_DpcppComputePmeMgr_serial_4();
  (void)_sdag_idx_DpcppComputePmeMgr_serial_5();
  (void)_sdag_idx_DpcppComputePmeMgr_serial_6();
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_4_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_5_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_6_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvAtomFiler_8_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::skip_9_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::initializePatches_11_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::incTotalPatchCount_12_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_4_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_5_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvPencils_6_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::recvAtomFiler_8_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::skip_9_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::initializePatches_11_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::incTotalPatchCount_12_closure));
  PUPable_reg(SINGLE_ARG(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure));
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_idx_DpcppComputePmeMgr_serial_0() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  static int epidx = _sdag_reg_DpcppComputePmeMgr_serial_0();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_reg_DpcppComputePmeMgr_serial_0() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  return CkRegisterEp("DpcppComputePmeMgr_serial_0", NULL, 0, CkIndex_DpcppComputePmeMgr::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_idx_DpcppComputePmeMgr_serial_1() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  static int epidx = _sdag_reg_DpcppComputePmeMgr_serial_1();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_reg_DpcppComputePmeMgr_serial_1() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  return CkRegisterEp("DpcppComputePmeMgr_serial_1", NULL, 0, CkIndex_DpcppComputePmeMgr::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_idx_DpcppComputePmeMgr_serial_2() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  static int epidx = _sdag_reg_DpcppComputePmeMgr_serial_2();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_reg_DpcppComputePmeMgr_serial_2() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  return CkRegisterEp("DpcppComputePmeMgr_serial_2", NULL, 0, CkIndex_DpcppComputePmeMgr::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_idx_DpcppComputePmeMgr_serial_3() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  static int epidx = _sdag_reg_DpcppComputePmeMgr_serial_3();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_reg_DpcppComputePmeMgr_serial_3() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  return CkRegisterEp("DpcppComputePmeMgr_serial_3", NULL, 0, CkIndex_DpcppComputePmeMgr::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_idx_DpcppComputePmeMgr_serial_4() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  static int epidx = _sdag_reg_DpcppComputePmeMgr_serial_4();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_reg_DpcppComputePmeMgr_serial_4() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  return CkRegisterEp("DpcppComputePmeMgr_serial_4", NULL, 0, CkIndex_DpcppComputePmeMgr::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_idx_DpcppComputePmeMgr_serial_5() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  static int epidx = _sdag_reg_DpcppComputePmeMgr_serial_5();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_reg_DpcppComputePmeMgr_serial_5() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  return CkRegisterEp("DpcppComputePmeMgr_serial_5", NULL, 0, CkIndex_DpcppComputePmeMgr::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_idx_DpcppComputePmeMgr_serial_6() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  static int epidx = _sdag_reg_DpcppComputePmeMgr_serial_6();
  return epidx;
}
#endif /* CK_TEMPLATES_ONLY */


#ifndef CK_TEMPLATES_ONLY
int DpcppComputePmeMgr::_sdag_reg_DpcppComputePmeMgr_serial_6() { // Potentially missing DpcppComputePmeMgr_SDAG_CODE in your class definition?
  return CkRegisterEp("DpcppComputePmeMgr_serial_6", NULL, 0, CkIndex_DpcppComputePmeMgr::__idx, 0);
}
#endif /* CK_TEMPLATES_ONLY */



#ifndef CK_TEMPLATES_ONLY
void _registerDpcppComputePmeMgr(void)
{
  static int _done = 0; if(_done) return; _done = 1;
  _registerDpcppPmeSolver();

/* REG: message PmeAtomMsg{
DpcppAtom atoms[];
}
;
*/
CMessage_PmeAtomMsg::__register("PmeAtomMsg", sizeof(PmeAtomMsg),(CkPackFnPtr) PmeAtomMsg::pack,(CkUnpackFnPtr) PmeAtomMsg::unpack);

/* REG: message PmeForceMsg{
DpcppForce force[];
}
;
*/
CMessage_PmeForceMsg::__register("PmeForceMsg", sizeof(PmeForceMsg),(CkPackFnPtr) PmeForceMsg::pack,(CkUnpackFnPtr) PmeForceMsg::unpack);

/* REG: message PmeLaunchMsg;
*/
CMessage_PmeLaunchMsg::__register("PmeLaunchMsg", sizeof(PmeLaunchMsg),(CkPackFnPtr) PmeLaunchMsg::pack,(CkUnpackFnPtr) PmeLaunchMsg::unpack);

/* REG: message PmeAtomPencilMsg{
DpcppAtom atoms[];
}
;
*/
CMessage_PmeAtomPencilMsg::__register("PmeAtomPencilMsg", sizeof(PmeAtomPencilMsg),(CkPackFnPtr) PmeAtomPencilMsg::pack,(CkUnpackFnPtr) PmeAtomPencilMsg::unpack);

/* REG: message PmeForcePencilMsg{
DpcppForce force[];
}
;
*/
CMessage_PmeForcePencilMsg::__register("PmeForcePencilMsg", sizeof(PmeForcePencilMsg),(CkPackFnPtr) PmeForcePencilMsg::pack,(CkUnpackFnPtr) PmeForcePencilMsg::unpack);

/* REG: group PmeAtomFiler: IrrGroup{
PmeAtomFiler();
};
*/
  CkIndex_PmeAtomFiler::__register("PmeAtomFiler", sizeof(PmeAtomFiler));

/* REG: nodegroup DpcppComputePmeDevice: NodeGroup{
DpcppComputePmeDevice();
void recvAtoms(PmeAtomMsg* impl_msg);
void sendAtomsToNeighbor(int y, int z, int atomIval);
void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
void gatherForce();
void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
void mergeForcesOnPatch(int homePatchIndex);
void sendForcesToPatch(PmeForceMsg* impl_msg);
};
*/
  CkIndex_DpcppComputePmeDevice::__register("DpcppComputePmeDevice", sizeof(DpcppComputePmeDevice));

/* REG: message RegisterPatchMsg;
*/
CMessage_RegisterPatchMsg::__register("RegisterPatchMsg", sizeof(RegisterPatchMsg),(CkPackFnPtr) RegisterPatchMsg::pack,(CkUnpackFnPtr) RegisterPatchMsg::unpack);

/* REG: message NumDevicesMsg;
*/
CMessage_NumDevicesMsg::__register("NumDevicesMsg", sizeof(NumDevicesMsg),(CkPackFnPtr) NumDevicesMsg::pack,(CkUnpackFnPtr) NumDevicesMsg::unpack);


/* REG: message RecvDeviceMsg{
CProxy_DpcppComputePmeDevice dev[];
}
;
*/
CMessage_RecvDeviceMsg::__register("RecvDeviceMsg", sizeof(RecvDeviceMsg),(CkPackFnPtr) RecvDeviceMsg::pack,(CkUnpackFnPtr) RecvDeviceMsg::unpack);

/* REG: nodegroup DpcppComputePmeMgr: NodeGroup{
DpcppComputePmeMgr();
void initialize_pencils(CkQdMsg* impl_msg);
void activate_pencils(CkQdMsg* impl_msg);
void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
void recvDevices(RecvDeviceMsg* impl_msg);
void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
void skip();
void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
void initializePatches();
void incTotalPatchCount();
void registerPatch(RegisterPatchMsg* impl_msg);
void registerNeighbor(int y, int z);
void recvAtoms(PmeAtomMsg* impl_msg);
void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
};
*/
  CkIndex_DpcppComputePmeMgr::__register("DpcppComputePmeMgr", sizeof(DpcppComputePmeMgr));

}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_PmeAtomFiler::virtual_pup(PUP::er &p) {
    recursive_pup<PmeAtomFiler>(dynamic_cast<PmeAtomFiler*>(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_DpcppComputePmeDevice::virtual_pup(PUP::er &p) {
    recursive_pup<DpcppComputePmeDevice>(dynamic_cast<DpcppComputePmeDevice*>(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_DpcppComputePmeMgr::virtual_pup(PUP::er &p) {
    recursive_pup<DpcppComputePmeMgr>(dynamic_cast<DpcppComputePmeMgr*>(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
