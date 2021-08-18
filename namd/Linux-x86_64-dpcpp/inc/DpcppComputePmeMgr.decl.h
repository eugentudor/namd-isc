#ifndef _DECL_DpcppComputePmeMgr_H_
#define _DECL_DpcppComputePmeMgr_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
#include "DpcppPmeSolver.decl.h"

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message PmeAtomMsg{
DpcppAtom atoms[];
}
;
 */
class PmeAtomMsg;
class CMessage_PmeAtomMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_PmeAtomMsg();
    static void *pack(PmeAtomMsg *p);
    static PmeAtomMsg* unpack(void* p);
    void *operator new(size_t, int);
    void *operator new(size_t, int, const int);
    void *operator new(size_t, int, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, int){dealloc(p);}
    void operator delete(void *p, int, const int){dealloc(p);}
    void operator delete(void *p, int, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message PmeForceMsg{
DpcppForce force[];
}
;
 */
class PmeForceMsg;
class CMessage_PmeForceMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_PmeForceMsg();
    static void *pack(PmeForceMsg *p);
    static PmeForceMsg* unpack(void* p);
    void *operator new(size_t, int);
    void *operator new(size_t, int, const int);
    void *operator new(size_t, int, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, int){dealloc(p);}
    void operator delete(void *p, int, const int){dealloc(p);}
    void operator delete(void *p, int, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message PmeLaunchMsg;
 */
class PmeLaunchMsg;
class CMessage_PmeLaunchMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_PmeLaunchMsg();
    static void *pack(PmeLaunchMsg *p);
    static PmeLaunchMsg* unpack(void* p);
    void *operator new(size_t, const int);
    void *operator new(size_t, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, const int){dealloc(p);}
    void operator delete(void *p, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message PmeAtomPencilMsg{
DpcppAtom atoms[];
}
;
 */
class PmeAtomPencilMsg;
class CMessage_PmeAtomPencilMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_PmeAtomPencilMsg();
    static void *pack(PmeAtomPencilMsg *p);
    static PmeAtomPencilMsg* unpack(void* p);
    void *operator new(size_t, int);
    void *operator new(size_t, int, const int);
    void *operator new(size_t, int, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, int){dealloc(p);}
    void operator delete(void *p, int, const int){dealloc(p);}
    void operator delete(void *p, int, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message PmeForcePencilMsg{
DpcppForce force[];
}
;
 */
class PmeForcePencilMsg;
class CMessage_PmeForcePencilMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_PmeForcePencilMsg();
    static void *pack(PmeForcePencilMsg *p);
    static PmeForcePencilMsg* unpack(void* p);
    void *operator new(size_t, int);
    void *operator new(size_t, int, const int);
    void *operator new(size_t, int, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, int){dealloc(p);}
    void operator delete(void *p, int, const int){dealloc(p);}
    void operator delete(void *p, int, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

/* DECLS: group PmeAtomFiler: IrrGroup{
PmeAtomFiler();
};
 */
 class PmeAtomFiler;
 class CkIndex_PmeAtomFiler;
 class CProxy_PmeAtomFiler;
 class CProxyElement_PmeAtomFiler;
 class CProxySection_PmeAtomFiler;
/* --------------- index object ------------------ */
class CkIndex_PmeAtomFiler:public CkIndex_IrrGroup{
  public:
    typedef PmeAtomFiler local_t;
    typedef CkIndex_PmeAtomFiler index_t;
    typedef CProxy_PmeAtomFiler proxy_t;
    typedef CProxyElement_PmeAtomFiler element_t;
    typedef CProxySection_PmeAtomFiler section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: PmeAtomFiler();
     */
    // Entry point registration at startup
    
    static int reg_PmeAtomFiler_void();
    // Entry point index lookup
    
    inline static int idx_PmeAtomFiler_void() {
      static int epidx = reg_PmeAtomFiler_void();
      return epidx;
    }

    
    static int ckNew() { return idx_PmeAtomFiler_void(); }
    
    static void _call_PmeAtomFiler_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_PmeAtomFiler_void(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxyElement_PmeAtomFiler: public CProxyElement_IrrGroup{
  public:
    typedef PmeAtomFiler local_t;
    typedef CkIndex_PmeAtomFiler index_t;
    typedef CProxy_PmeAtomFiler proxy_t;
    typedef CProxyElement_PmeAtomFiler element_t;
    typedef CProxySection_PmeAtomFiler section_t;


    /* TRAM aggregators */

    CProxyElement_PmeAtomFiler(void) {
    }
    CProxyElement_PmeAtomFiler(const IrrGroup *g) : CProxyElement_IrrGroup(g){
    }
    CProxyElement_PmeAtomFiler(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_IrrGroup(_gid,_onPE,CK_DELCTOR_ARGS){
    }
    CProxyElement_PmeAtomFiler(CkGroupID _gid,int _onPE) : CProxyElement_IrrGroup(_gid,_onPE){
    }

    int ckIsDelegated(void) const
    { return CProxyElement_IrrGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_IrrGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_IrrGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_IrrGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxyElement_IrrGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxyElement_IrrGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxyElement_IrrGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_IrrGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_IrrGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_IrrGroup::ckSetReductionClient(cb); }
int ckGetGroupPe(void) const
{return CProxyElement_IrrGroup::ckGetGroupPe();}

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_IrrGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_IrrGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_IrrGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxyElement_IrrGroup::ckSetGroupID(g);
    }
    PmeAtomFiler* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static PmeAtomFiler* ckLocalBranch(CkGroupID gID) {
      return (PmeAtomFiler*)CkLocalBranch(gID);
    }
/* DECLS: PmeAtomFiler();
 */
    

};
PUPmarshall(CProxyElement_PmeAtomFiler)
/* ---------------- collective proxy -------------- */
class CProxy_PmeAtomFiler: public CProxy_IrrGroup{
  public:
    typedef PmeAtomFiler local_t;
    typedef CkIndex_PmeAtomFiler index_t;
    typedef CProxy_PmeAtomFiler proxy_t;
    typedef CProxyElement_PmeAtomFiler element_t;
    typedef CProxySection_PmeAtomFiler section_t;

    CProxy_PmeAtomFiler(void) {
    }
    CProxy_PmeAtomFiler(const IrrGroup *g) : CProxy_IrrGroup(g){
    }
    CProxy_PmeAtomFiler(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_IrrGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_PmeAtomFiler(CkGroupID _gid) : CProxy_IrrGroup(_gid){  }
    CProxyElement_PmeAtomFiler operator[](int onPE) const
      {return CProxyElement_PmeAtomFiler(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

    int ckIsDelegated(void) const
    { return CProxy_IrrGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_IrrGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_IrrGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_IrrGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxy_IrrGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxy_IrrGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxy_IrrGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_IrrGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_IrrGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_IrrGroup::ckSetReductionClient(cb); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_IrrGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_IrrGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_IrrGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxy_IrrGroup::ckSetGroupID(g);
    }
    PmeAtomFiler* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static PmeAtomFiler* ckLocalBranch(CkGroupID gID) {
      return (PmeAtomFiler*)CkLocalBranch(gID);
    }
/* DECLS: PmeAtomFiler();
 */
    
    static CkGroupID ckNew(const CkEntryOptions *impl_e_opts=NULL);

};
PUPmarshall(CProxy_PmeAtomFiler)
/* ---------------- section proxy -------------- */
class CProxySection_PmeAtomFiler: public CProxySection_IrrGroup{
  public:
    typedef PmeAtomFiler local_t;
    typedef CkIndex_PmeAtomFiler index_t;
    typedef CProxy_PmeAtomFiler proxy_t;
    typedef CProxyElement_PmeAtomFiler element_t;
    typedef CProxySection_PmeAtomFiler section_t;

    CProxySection_PmeAtomFiler(void) {
    }
    CProxySection_PmeAtomFiler(const IrrGroup *g) : CProxySection_IrrGroup(g){
    }
    CProxySection_PmeAtomFiler(const CkGroupID &_gid,const int *_pelist,int _npes, CK_DELCTOR_PARAM) : CProxySection_IrrGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_PmeAtomFiler(const CkGroupID &_gid,const int *_pelist,int _npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_IrrGroup(_gid,_pelist,_npes,factor){  }
    CProxySection_PmeAtomFiler(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_IrrGroup(n,_gid,_pelist,_npes,factor){  }
    CProxySection_PmeAtomFiler(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, CK_DELCTOR_PARAM) : CProxySection_IrrGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

    int ckIsDelegated(void) const
    { return CProxySection_IrrGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_IrrGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_IrrGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_IrrGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxySection_IrrGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxySection_IrrGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxySection_IrrGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_IrrGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_IrrGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_IrrGroup::ckSetReductionClient(cb); }
inline int ckGetNumSections() const
{ return CProxySection_IrrGroup::ckGetNumSections(); }
inline CkSectionInfo &ckGetSectionInfo()
{ return CProxySection_IrrGroup::ckGetSectionInfo(); }
inline CkSectionID *ckGetSectionIDs()
{ return CProxySection_IrrGroup::ckGetSectionIDs(); }
inline CkSectionID &ckGetSectionID()
{ return CProxySection_IrrGroup::ckGetSectionID(); }
inline CkSectionID &ckGetSectionID(int i)
{ return CProxySection_IrrGroup::ckGetSectionID(i); }
inline CkGroupID ckGetGroupIDn(int i) const
{ return CProxySection_IrrGroup::ckGetGroupIDn(i); }
inline const int *ckGetElements() const
{ return CProxySection_IrrGroup::ckGetElements(); }
inline const int *ckGetElements(int i) const
{ return CProxySection_IrrGroup::ckGetElements(i); }
inline int ckGetNumElements() const
{ return CProxySection_IrrGroup::ckGetNumElements(); } 
inline int ckGetNumElements(int i) const
{ return CProxySection_IrrGroup::ckGetNumElements(i); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_IrrGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_IrrGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_IrrGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxySection_IrrGroup::ckSetGroupID(g);
    }
    PmeAtomFiler* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static PmeAtomFiler* ckLocalBranch(CkGroupID gID) {
      return (PmeAtomFiler*)CkLocalBranch(gID);
    }
/* DECLS: PmeAtomFiler();
 */
    

};
PUPmarshall(CProxySection_PmeAtomFiler)
#define PmeAtomFiler_SDAG_CODE 
typedef CBaseT1<Group, CProxy_PmeAtomFiler>CBase_PmeAtomFiler;

/* DECLS: nodegroup DpcppComputePmeDevice: NodeGroup{
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
 class DpcppComputePmeDevice;
 class CkIndex_DpcppComputePmeDevice;
 class CProxy_DpcppComputePmeDevice;
 class CProxyElement_DpcppComputePmeDevice;
 class CProxySection_DpcppComputePmeDevice;
/* --------------- index object ------------------ */
class CkIndex_DpcppComputePmeDevice:public CkIndex_NodeGroup{
  public:
    typedef DpcppComputePmeDevice local_t;
    typedef CkIndex_DpcppComputePmeDevice index_t;
    typedef CProxy_DpcppComputePmeDevice proxy_t;
    typedef CProxyElement_DpcppComputePmeDevice element_t;
    typedef CProxySection_DpcppComputePmeDevice section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppComputePmeDevice();
     */
    // Entry point registration at startup
    
    static int reg_DpcppComputePmeDevice_void();
    // Entry point index lookup
    
    inline static int idx_DpcppComputePmeDevice_void() {
      static int epidx = reg_DpcppComputePmeDevice_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppComputePmeDevice_void(); }
    
    static void _call_DpcppComputePmeDevice_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppComputePmeDevice_void(void* impl_msg, void* impl_obj);
    /* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvAtoms_PmeAtomMsg();
    // Entry point index lookup
    
    inline static int idx_recvAtoms_PmeAtomMsg() {
      static int epidx = reg_recvAtoms_PmeAtomMsg();
      return epidx;
    }

    
    inline static int idx_recvAtoms(void (DpcppComputePmeDevice::*)(PmeAtomMsg* impl_msg) ) {
      return idx_recvAtoms_PmeAtomMsg();
    }


    
    static int recvAtoms(PmeAtomMsg* impl_msg) { return idx_recvAtoms_PmeAtomMsg(); }
    
    static void _call_recvAtoms_PmeAtomMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvAtoms_PmeAtomMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void sendAtomsToNeighbor(int y, int z, int atomIval);
     */
    // Entry point registration at startup
    
    static int reg_sendAtomsToNeighbor_marshall3();
    // Entry point index lookup
    
    inline static int idx_sendAtomsToNeighbor_marshall3() {
      static int epidx = reg_sendAtomsToNeighbor_marshall3();
      return epidx;
    }

    
    inline static int idx_sendAtomsToNeighbor(void (DpcppComputePmeDevice::*)(int y, int z, int atomIval) ) {
      return idx_sendAtomsToNeighbor_marshall3();
    }


    
    static int sendAtomsToNeighbor(int y, int z, int atomIval) { return idx_sendAtomsToNeighbor_marshall3(); }
    
    static void _call_sendAtomsToNeighbor_marshall3(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_sendAtomsToNeighbor_marshall3(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_sendAtomsToNeighbor_marshall3(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_sendAtomsToNeighbor_marshall3(PUP::er &p,void *msg);
    /* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvAtomsFromNeighbor_PmeAtomPencilMsg();
    // Entry point index lookup
    
    inline static int idx_recvAtomsFromNeighbor_PmeAtomPencilMsg() {
      static int epidx = reg_recvAtomsFromNeighbor_PmeAtomPencilMsg();
      return epidx;
    }

    
    inline static int idx_recvAtomsFromNeighbor(void (DpcppComputePmeDevice::*)(PmeAtomPencilMsg* impl_msg) ) {
      return idx_recvAtomsFromNeighbor_PmeAtomPencilMsg();
    }


    
    static int recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg) { return idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(); }
    
    static void _call_recvAtomsFromNeighbor_PmeAtomPencilMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvAtomsFromNeighbor_PmeAtomPencilMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void gatherForce();
     */
    // Entry point registration at startup
    
    static int reg_gatherForce_void();
    // Entry point index lookup
    
    inline static int idx_gatherForce_void() {
      static int epidx = reg_gatherForce_void();
      return epidx;
    }

    
    inline static int idx_gatherForce(void (DpcppComputePmeDevice::*)() ) {
      return idx_gatherForce_void();
    }


    
    static int gatherForce() { return idx_gatherForce_void(); }
    
    static void _call_gatherForce_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_gatherForce_void(void* impl_msg, void* impl_obj);
    /* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvForcesFromNeighbor_PmeForcePencilMsg();
    // Entry point index lookup
    
    inline static int idx_recvForcesFromNeighbor_PmeForcePencilMsg() {
      static int epidx = reg_recvForcesFromNeighbor_PmeForcePencilMsg();
      return epidx;
    }

    
    inline static int idx_recvForcesFromNeighbor(void (DpcppComputePmeDevice::*)(PmeForcePencilMsg* impl_msg) ) {
      return idx_recvForcesFromNeighbor_PmeForcePencilMsg();
    }


    
    static int recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg) { return idx_recvForcesFromNeighbor_PmeForcePencilMsg(); }
    
    static void _call_recvForcesFromNeighbor_PmeForcePencilMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvForcesFromNeighbor_PmeForcePencilMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void mergeForcesOnPatch(int homePatchIndex);
     */
    // Entry point registration at startup
    
    static int reg_mergeForcesOnPatch_marshall7();
    // Entry point index lookup
    
    inline static int idx_mergeForcesOnPatch_marshall7() {
      static int epidx = reg_mergeForcesOnPatch_marshall7();
      return epidx;
    }

    
    inline static int idx_mergeForcesOnPatch(void (DpcppComputePmeDevice::*)(int homePatchIndex) ) {
      return idx_mergeForcesOnPatch_marshall7();
    }


    
    static int mergeForcesOnPatch(int homePatchIndex) { return idx_mergeForcesOnPatch_marshall7(); }
    
    static void _call_mergeForcesOnPatch_marshall7(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_mergeForcesOnPatch_marshall7(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_mergeForcesOnPatch_marshall7(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_mergeForcesOnPatch_marshall7(PUP::er &p,void *msg);
    /* DECLS: void sendForcesToPatch(PmeForceMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_sendForcesToPatch_PmeForceMsg();
    // Entry point index lookup
    
    inline static int idx_sendForcesToPatch_PmeForceMsg() {
      static int epidx = reg_sendForcesToPatch_PmeForceMsg();
      return epidx;
    }

    
    inline static int idx_sendForcesToPatch(void (DpcppComputePmeDevice::*)(PmeForceMsg* impl_msg) ) {
      return idx_sendForcesToPatch_PmeForceMsg();
    }


    
    static int sendForcesToPatch(PmeForceMsg* impl_msg) { return idx_sendForcesToPatch_PmeForceMsg(); }
    
    static void _call_sendForcesToPatch_PmeForceMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_sendForcesToPatch_PmeForceMsg(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxyElement_DpcppComputePmeDevice: public CProxyElement_NodeGroup{
  public:
    typedef DpcppComputePmeDevice local_t;
    typedef CkIndex_DpcppComputePmeDevice index_t;
    typedef CProxy_DpcppComputePmeDevice proxy_t;
    typedef CProxyElement_DpcppComputePmeDevice element_t;
    typedef CProxySection_DpcppComputePmeDevice section_t;


    /* TRAM aggregators */

    CProxyElement_DpcppComputePmeDevice(void) {
    }
    CProxyElement_DpcppComputePmeDevice(const IrrGroup *g) : CProxyElement_NodeGroup(g){
    }
    CProxyElement_DpcppComputePmeDevice(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_NodeGroup(_gid,_onPE,CK_DELCTOR_ARGS){
    }
    CProxyElement_DpcppComputePmeDevice(CkGroupID _gid,int _onPE) : CProxyElement_NodeGroup(_gid,_onPE){
    }

    int ckIsDelegated(void) const
    { return CProxyElement_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxyElement_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxyElement_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxyElement_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_NodeGroup::ckSetReductionClient(cb); }
int ckGetGroupPe(void) const
{return CProxyElement_NodeGroup::ckGetGroupPe();}

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxyElement_NodeGroup::ckSetGroupID(g);
    }
    DpcppComputePmeDevice* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputePmeDevice* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputePmeDevice*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputePmeDevice();
 */
    

/* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
    
    void recvAtoms(PmeAtomMsg* impl_msg);

/* DECLS: void sendAtomsToNeighbor(int y, int z, int atomIval);
 */
    
    void sendAtomsToNeighbor(int y, int z, int atomIval, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
    
    void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);

/* DECLS: void gatherForce();
 */
    
    void gatherForce(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
    
    void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);

/* DECLS: void mergeForcesOnPatch(int homePatchIndex);
 */
    
    void mergeForcesOnPatch(int homePatchIndex, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void sendForcesToPatch(PmeForceMsg* impl_msg);
 */
    
    void sendForcesToPatch(PmeForceMsg* impl_msg);

};
PUPmarshall(CProxyElement_DpcppComputePmeDevice)
/* ---------------- collective proxy -------------- */
class CProxy_DpcppComputePmeDevice: public CProxy_NodeGroup{
  public:
    typedef DpcppComputePmeDevice local_t;
    typedef CkIndex_DpcppComputePmeDevice index_t;
    typedef CProxy_DpcppComputePmeDevice proxy_t;
    typedef CProxyElement_DpcppComputePmeDevice element_t;
    typedef CProxySection_DpcppComputePmeDevice section_t;

    CProxy_DpcppComputePmeDevice(void) {
    }
    CProxy_DpcppComputePmeDevice(const IrrGroup *g) : CProxy_NodeGroup(g){
    }
    CProxy_DpcppComputePmeDevice(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_NodeGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_DpcppComputePmeDevice(CkGroupID _gid) : CProxy_NodeGroup(_gid){  }
    CProxyElement_DpcppComputePmeDevice operator[](int onPE) const
      {return CProxyElement_DpcppComputePmeDevice(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

    int ckIsDelegated(void) const
    { return CProxy_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxy_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxy_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxy_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_NodeGroup::ckSetReductionClient(cb); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxy_NodeGroup::ckSetGroupID(g);
    }
    DpcppComputePmeDevice* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputePmeDevice* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputePmeDevice*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputePmeDevice();
 */
    
    static CkGroupID ckNew(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
    
    void recvAtoms(PmeAtomMsg* impl_msg);

/* DECLS: void sendAtomsToNeighbor(int y, int z, int atomIval);
 */
    
    void sendAtomsToNeighbor(int y, int z, int atomIval, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
    
    void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);

/* DECLS: void gatherForce();
 */
    
    void gatherForce(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
    
    void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);

/* DECLS: void mergeForcesOnPatch(int homePatchIndex);
 */
    
    void mergeForcesOnPatch(int homePatchIndex, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void sendForcesToPatch(PmeForceMsg* impl_msg);
 */
    
    void sendForcesToPatch(PmeForceMsg* impl_msg);

};
PUPmarshall(CProxy_DpcppComputePmeDevice)
/* ---------------- section proxy -------------- */
class CProxySection_DpcppComputePmeDevice: public CProxySection_NodeGroup{
  public:
    typedef DpcppComputePmeDevice local_t;
    typedef CkIndex_DpcppComputePmeDevice index_t;
    typedef CProxy_DpcppComputePmeDevice proxy_t;
    typedef CProxyElement_DpcppComputePmeDevice element_t;
    typedef CProxySection_DpcppComputePmeDevice section_t;

    CProxySection_DpcppComputePmeDevice(void) {
    }
    CProxySection_DpcppComputePmeDevice(const IrrGroup *g) : CProxySection_NodeGroup(g){
    }
    CProxySection_DpcppComputePmeDevice(const CkGroupID &_gid,const int *_pelist,int _npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_DpcppComputePmeDevice(const CkGroupID &_gid,const int *_pelist,int _npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(_gid,_pelist,_npes,factor){  }
    CProxySection_DpcppComputePmeDevice(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,factor){  }
    CProxySection_DpcppComputePmeDevice(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

    int ckIsDelegated(void) const
    { return CProxySection_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxySection_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxySection_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxySection_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_NodeGroup::ckSetReductionClient(cb); }
inline int ckGetNumSections() const
{ return CProxySection_NodeGroup::ckGetNumSections(); }
inline CkSectionInfo &ckGetSectionInfo()
{ return CProxySection_NodeGroup::ckGetSectionInfo(); }
inline CkSectionID *ckGetSectionIDs()
{ return CProxySection_NodeGroup::ckGetSectionIDs(); }
inline CkSectionID &ckGetSectionID()
{ return CProxySection_NodeGroup::ckGetSectionID(); }
inline CkSectionID &ckGetSectionID(int i)
{ return CProxySection_NodeGroup::ckGetSectionID(i); }
inline CkGroupID ckGetGroupIDn(int i) const
{ return CProxySection_NodeGroup::ckGetGroupIDn(i); }
inline const int *ckGetElements() const
{ return CProxySection_NodeGroup::ckGetElements(); }
inline const int *ckGetElements(int i) const
{ return CProxySection_NodeGroup::ckGetElements(i); }
inline int ckGetNumElements() const
{ return CProxySection_NodeGroup::ckGetNumElements(); } 
inline int ckGetNumElements(int i) const
{ return CProxySection_NodeGroup::ckGetNumElements(i); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxySection_NodeGroup::ckSetGroupID(g);
    }
    DpcppComputePmeDevice* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputePmeDevice* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputePmeDevice*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputePmeDevice();
 */
    

/* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
    
    void recvAtoms(PmeAtomMsg* impl_msg);

/* DECLS: void sendAtomsToNeighbor(int y, int z, int atomIval);
 */
    
    void sendAtomsToNeighbor(int y, int z, int atomIval, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
    
    void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);

/* DECLS: void gatherForce();
 */
    
    void gatherForce(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
    
    void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);

/* DECLS: void mergeForcesOnPatch(int homePatchIndex);
 */
    
    void mergeForcesOnPatch(int homePatchIndex, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void sendForcesToPatch(PmeForceMsg* impl_msg);
 */
    
    void sendForcesToPatch(PmeForceMsg* impl_msg);

};
PUPmarshall(CProxySection_DpcppComputePmeDevice)
#define DpcppComputePmeDevice_SDAG_CODE 
typedef CBaseT1<NodeGroup, CProxy_DpcppComputePmeDevice>CBase_DpcppComputePmeDevice;

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message RegisterPatchMsg;
 */
class RegisterPatchMsg;
class CMessage_RegisterPatchMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_RegisterPatchMsg();
    static void *pack(RegisterPatchMsg *p);
    static RegisterPatchMsg* unpack(void* p);
    void *operator new(size_t, const int);
    void *operator new(size_t, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, const int){dealloc(p);}
    void operator delete(void *p, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message NumDevicesMsg;
 */
class NumDevicesMsg;
class CMessage_NumDevicesMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_NumDevicesMsg();
    static void *pack(NumDevicesMsg *p);
    static NumDevicesMsg* unpack(void* p);
    void *operator new(size_t, const int);
    void *operator new(size_t, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, const int){dealloc(p);}
    void operator delete(void *p, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

class CProxy_DpcppComputePmeDevice;

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message RecvDeviceMsg{
CProxy_DpcppComputePmeDevice dev[];
}
;
 */
class RecvDeviceMsg;
class CMessage_RecvDeviceMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*, const int, const GroupDepNum);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*, const int, const GroupDepNum){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int, GroupDepNum);
    static void dealloc(void *p);
    CMessage_RecvDeviceMsg();
    static void *pack(RecvDeviceMsg *p);
    static RecvDeviceMsg* unpack(void* p);
    void *operator new(size_t, int);
    void *operator new(size_t, int, const int);
    void *operator new(size_t, int, const int, const GroupDepNum);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, int){dealloc(p);}
    void operator delete(void *p, int, const int){dealloc(p);}
    void operator delete(void *p, int, const int, const GroupDepNum){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

/* DECLS: nodegroup DpcppComputePmeMgr: NodeGroup{
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
 class DpcppComputePmeMgr;
 class CkIndex_DpcppComputePmeMgr;
 class CProxy_DpcppComputePmeMgr;
 class CProxyElement_DpcppComputePmeMgr;
 class CProxySection_DpcppComputePmeMgr;
/* --------------- index object ------------------ */
class CkIndex_DpcppComputePmeMgr:public CkIndex_NodeGroup{
  public:
    typedef DpcppComputePmeMgr local_t;
    typedef CkIndex_DpcppComputePmeMgr index_t;
    typedef CProxy_DpcppComputePmeMgr proxy_t;
    typedef CProxyElement_DpcppComputePmeMgr element_t;
    typedef CProxySection_DpcppComputePmeMgr section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppComputePmeMgr();
     */
    // Entry point registration at startup
    
    static int reg_DpcppComputePmeMgr_void();
    // Entry point index lookup
    
    inline static int idx_DpcppComputePmeMgr_void() {
      static int epidx = reg_DpcppComputePmeMgr_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppComputePmeMgr_void(); }
    
    static void _call_DpcppComputePmeMgr_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppComputePmeMgr_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize_pencils(CkQdMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_pencils_CkQdMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_pencils_CkQdMsg() {
      static int epidx = reg_initialize_pencils_CkQdMsg();
      return epidx;
    }

    
    inline static int idx_initialize_pencils(void (DpcppComputePmeMgr::*)(CkQdMsg* impl_msg) ) {
      return idx_initialize_pencils_CkQdMsg();
    }


    
    static int initialize_pencils(CkQdMsg* impl_msg) { return idx_initialize_pencils_CkQdMsg(); }
    
    static void _call_initialize_pencils_CkQdMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_pencils_CkQdMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void activate_pencils(CkQdMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_activate_pencils_CkQdMsg();
    // Entry point index lookup
    
    inline static int idx_activate_pencils_CkQdMsg() {
      static int epidx = reg_activate_pencils_CkQdMsg();
      return epidx;
    }

    
    inline static int idx_activate_pencils(void (DpcppComputePmeMgr::*)(CkQdMsg* impl_msg) ) {
      return idx_activate_pencils_CkQdMsg();
    }


    
    static int activate_pencils(CkQdMsg* impl_msg) { return idx_activate_pencils_CkQdMsg(); }
    
    static void _call_activate_pencils_CkQdMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_activate_pencils_CkQdMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
     */
    // Entry point registration at startup
    
    static int reg_recvPencils_marshall4();
    // Entry point index lookup
    
    inline static int idx_recvPencils_marshall4() {
      static int epidx = reg_recvPencils_marshall4();
      return epidx;
    }

    
    inline static int idx_recvPencils(void (DpcppComputePmeMgr::*)(const CProxy_DpcppPmePencilXYZ &xyz) ) {
      return idx_recvPencils_marshall4();
    }


    
    static int recvPencils(const CProxy_DpcppPmePencilXYZ &xyz) { return idx_recvPencils_marshall4(); }
    
    static void _call_recvPencils_marshall4(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvPencils_marshall4(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvPencils_marshall4(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvPencils_marshall4(PUP::er &p,void *msg);
    /* DECLS: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
     */
    // Entry point registration at startup
    
    static int reg_recvPencils_marshall5();
    // Entry point index lookup
    
    inline static int idx_recvPencils_marshall5() {
      static int epidx = reg_recvPencils_marshall5();
      return epidx;
    }

    
    inline static int idx_recvPencils(void (DpcppComputePmeMgr::*)(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z) ) {
      return idx_recvPencils_marshall5();
    }


    
    static int recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z) { return idx_recvPencils_marshall5(); }
    
    static void _call_recvPencils_marshall5(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvPencils_marshall5(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvPencils_marshall5(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvPencils_marshall5(PUP::er &p,void *msg);
    /* DECLS: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
     */
    // Entry point registration at startup
    
    static int reg_recvPencils_marshall6();
    // Entry point index lookup
    
    inline static int idx_recvPencils_marshall6() {
      static int epidx = reg_recvPencils_marshall6();
      return epidx;
    }

    
    inline static int idx_recvPencils(void (DpcppComputePmeMgr::*)(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z) ) {
      return idx_recvPencils_marshall6();
    }


    
    static int recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z) { return idx_recvPencils_marshall6(); }
    
    static void _call_recvPencils_marshall6(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvPencils_marshall6(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvPencils_marshall6(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvPencils_marshall6(PUP::er &p,void *msg);
    /* DECLS: void recvDevices(RecvDeviceMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvDevices_RecvDeviceMsg();
    // Entry point index lookup
    
    inline static int idx_recvDevices_RecvDeviceMsg() {
      static int epidx = reg_recvDevices_RecvDeviceMsg();
      return epidx;
    }

    
    inline static int idx_recvDevices(void (DpcppComputePmeMgr::*)(RecvDeviceMsg* impl_msg) ) {
      return idx_recvDevices_RecvDeviceMsg();
    }


    
    static int recvDevices(RecvDeviceMsg* impl_msg) { return idx_recvDevices_RecvDeviceMsg(); }
    
    static void _call_recvDevices_RecvDeviceMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDevices_RecvDeviceMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
     */
    // Entry point registration at startup
    
    static int reg_recvAtomFiler_marshall8();
    // Entry point index lookup
    
    inline static int idx_recvAtomFiler_marshall8() {
      static int epidx = reg_recvAtomFiler_marshall8();
      return epidx;
    }

    
    inline static int idx_recvAtomFiler(void (DpcppComputePmeMgr::*)(const CProxy_PmeAtomFiler &filer) ) {
      return idx_recvAtomFiler_marshall8();
    }


    
    static int recvAtomFiler(const CProxy_PmeAtomFiler &filer) { return idx_recvAtomFiler_marshall8(); }
    
    static void _call_recvAtomFiler_marshall8(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvAtomFiler_marshall8(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvAtomFiler_marshall8(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvAtomFiler_marshall8(PUP::er &p,void *msg);
    /* DECLS: void skip();
     */
    // Entry point registration at startup
    
    static int reg_skip_void();
    // Entry point index lookup
    
    inline static int idx_skip_void() {
      static int epidx = reg_skip_void();
      return epidx;
    }

    
    inline static int idx_skip(void (DpcppComputePmeMgr::*)() ) {
      return idx_skip_void();
    }


    
    static int skip() { return idx_skip_void(); }
    
    static void _call_skip_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_skip_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initializeDevicesAndAtomFiler_NumDevicesMsg();
    // Entry point index lookup
    
    inline static int idx_initializeDevicesAndAtomFiler_NumDevicesMsg() {
      static int epidx = reg_initializeDevicesAndAtomFiler_NumDevicesMsg();
      return epidx;
    }

    
    inline static int idx_initializeDevicesAndAtomFiler(void (DpcppComputePmeMgr::*)(NumDevicesMsg* impl_msg) ) {
      return idx_initializeDevicesAndAtomFiler_NumDevicesMsg();
    }


    
    static int initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg) { return idx_initializeDevicesAndAtomFiler_NumDevicesMsg(); }
    
    static void _call_initializeDevicesAndAtomFiler_NumDevicesMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initializeDevicesAndAtomFiler_NumDevicesMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initializePatches();
     */
    // Entry point registration at startup
    
    static int reg_initializePatches_void();
    // Entry point index lookup
    
    inline static int idx_initializePatches_void() {
      static int epidx = reg_initializePatches_void();
      return epidx;
    }

    
    inline static int idx_initializePatches(void (DpcppComputePmeMgr::*)() ) {
      return idx_initializePatches_void();
    }


    
    static int initializePatches() { return idx_initializePatches_void(); }
    
    static void _call_initializePatches_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initializePatches_void(void* impl_msg, void* impl_obj);
    /* DECLS: void incTotalPatchCount();
     */
    // Entry point registration at startup
    
    static int reg_incTotalPatchCount_void();
    // Entry point index lookup
    
    inline static int idx_incTotalPatchCount_void() {
      static int epidx = reg_incTotalPatchCount_void();
      return epidx;
    }

    
    inline static int idx_incTotalPatchCount(void (DpcppComputePmeMgr::*)() ) {
      return idx_incTotalPatchCount_void();
    }


    
    static int incTotalPatchCount() { return idx_incTotalPatchCount_void(); }
    
    static void _call_incTotalPatchCount_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_incTotalPatchCount_void(void* impl_msg, void* impl_obj);
    /* DECLS: void registerPatch(RegisterPatchMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_registerPatch_RegisterPatchMsg();
    // Entry point index lookup
    
    inline static int idx_registerPatch_RegisterPatchMsg() {
      static int epidx = reg_registerPatch_RegisterPatchMsg();
      return epidx;
    }

    
    inline static int idx_registerPatch(void (DpcppComputePmeMgr::*)(RegisterPatchMsg* impl_msg) ) {
      return idx_registerPatch_RegisterPatchMsg();
    }


    
    static int registerPatch(RegisterPatchMsg* impl_msg) { return idx_registerPatch_RegisterPatchMsg(); }
    
    static void _call_registerPatch_RegisterPatchMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_registerPatch_RegisterPatchMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void registerNeighbor(int y, int z);
     */
    // Entry point registration at startup
    
    static int reg_registerNeighbor_marshall14();
    // Entry point index lookup
    
    inline static int idx_registerNeighbor_marshall14() {
      static int epidx = reg_registerNeighbor_marshall14();
      return epidx;
    }

    
    inline static int idx_registerNeighbor(void (DpcppComputePmeMgr::*)(int y, int z) ) {
      return idx_registerNeighbor_marshall14();
    }


    
    static int registerNeighbor(int y, int z) { return idx_registerNeighbor_marshall14(); }
    
    static void _call_registerNeighbor_marshall14(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_registerNeighbor_marshall14(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_registerNeighbor_marshall14(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_registerNeighbor_marshall14(PUP::er &p,void *msg);
    /* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvAtoms_PmeAtomMsg();
    // Entry point index lookup
    
    inline static int idx_recvAtoms_PmeAtomMsg() {
      static int epidx = reg_recvAtoms_PmeAtomMsg();
      return epidx;
    }

    
    inline static int idx_recvAtoms(void (DpcppComputePmeMgr::*)(PmeAtomMsg* impl_msg) ) {
      return idx_recvAtoms_PmeAtomMsg();
    }


    
    static int recvAtoms(PmeAtomMsg* impl_msg) { return idx_recvAtoms_PmeAtomMsg(); }
    
    static void _call_recvAtoms_PmeAtomMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvAtoms_PmeAtomMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvAtomsFromNeighbor_PmeAtomPencilMsg();
    // Entry point index lookup
    
    inline static int idx_recvAtomsFromNeighbor_PmeAtomPencilMsg() {
      static int epidx = reg_recvAtomsFromNeighbor_PmeAtomPencilMsg();
      return epidx;
    }

    
    inline static int idx_recvAtomsFromNeighbor(void (DpcppComputePmeMgr::*)(PmeAtomPencilMsg* impl_msg) ) {
      return idx_recvAtomsFromNeighbor_PmeAtomPencilMsg();
    }


    
    static int recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg) { return idx_recvAtomsFromNeighbor_PmeAtomPencilMsg(); }
    
    static void _call_recvAtomsFromNeighbor_PmeAtomPencilMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvAtomsFromNeighbor_PmeAtomPencilMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvForcesFromNeighbor_PmeForcePencilMsg();
    // Entry point index lookup
    
    inline static int idx_recvForcesFromNeighbor_PmeForcePencilMsg() {
      static int epidx = reg_recvForcesFromNeighbor_PmeForcePencilMsg();
      return epidx;
    }

    
    inline static int idx_recvForcesFromNeighbor(void (DpcppComputePmeMgr::*)(PmeForcePencilMsg* impl_msg) ) {
      return idx_recvForcesFromNeighbor_PmeForcePencilMsg();
    }


    
    static int recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg) { return idx_recvForcesFromNeighbor_PmeForcePencilMsg(); }
    
    static void _call_recvForcesFromNeighbor_PmeForcePencilMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvForcesFromNeighbor_PmeForcePencilMsg(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxyElement_DpcppComputePmeMgr: public CProxyElement_NodeGroup{
  public:
    typedef DpcppComputePmeMgr local_t;
    typedef CkIndex_DpcppComputePmeMgr index_t;
    typedef CProxy_DpcppComputePmeMgr proxy_t;
    typedef CProxyElement_DpcppComputePmeMgr element_t;
    typedef CProxySection_DpcppComputePmeMgr section_t;


    /* TRAM aggregators */

    CProxyElement_DpcppComputePmeMgr(void) {
    }
    CProxyElement_DpcppComputePmeMgr(const IrrGroup *g) : CProxyElement_NodeGroup(g){
    }
    CProxyElement_DpcppComputePmeMgr(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_NodeGroup(_gid,_onPE,CK_DELCTOR_ARGS){
    }
    CProxyElement_DpcppComputePmeMgr(CkGroupID _gid,int _onPE) : CProxyElement_NodeGroup(_gid,_onPE){
    }

    int ckIsDelegated(void) const
    { return CProxyElement_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxyElement_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxyElement_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxyElement_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_NodeGroup::ckSetReductionClient(cb); }
int ckGetGroupPe(void) const
{return CProxyElement_NodeGroup::ckGetGroupPe();}

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxyElement_NodeGroup::ckSetGroupID(g);
    }
    DpcppComputePmeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputePmeMgr* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputePmeMgr*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputePmeMgr();
 */
    

/* DECLS: void initialize_pencils(CkQdMsg* impl_msg);
 */
    
    void initialize_pencils(CkQdMsg* impl_msg);

/* DECLS: void activate_pencils(CkQdMsg* impl_msg);
 */
    
    void activate_pencils(CkQdMsg* impl_msg);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvDevices(RecvDeviceMsg* impl_msg);
 */
    
    void recvDevices(RecvDeviceMsg* impl_msg);

/* DECLS: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
 */
    
    void recvAtomFiler(const CProxy_PmeAtomFiler &filer, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void skip();
 */
    
    void skip(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
 */
    
    void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);

/* DECLS: void initializePatches();
 */
    
    void initializePatches(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void incTotalPatchCount();
 */
    
    void incTotalPatchCount(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void registerPatch(RegisterPatchMsg* impl_msg);
 */
    
    void registerPatch(RegisterPatchMsg* impl_msg);

/* DECLS: void registerNeighbor(int y, int z);
 */
    
    void registerNeighbor(int y, int z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
    
    void recvAtoms(PmeAtomMsg* impl_msg);

/* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
    
    void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);

/* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
    
    void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);

};
PUPmarshall(CProxyElement_DpcppComputePmeMgr)
/* ---------------- collective proxy -------------- */
class CProxy_DpcppComputePmeMgr: public CProxy_NodeGroup{
  public:
    typedef DpcppComputePmeMgr local_t;
    typedef CkIndex_DpcppComputePmeMgr index_t;
    typedef CProxy_DpcppComputePmeMgr proxy_t;
    typedef CProxyElement_DpcppComputePmeMgr element_t;
    typedef CProxySection_DpcppComputePmeMgr section_t;

    CProxy_DpcppComputePmeMgr(void) {
    }
    CProxy_DpcppComputePmeMgr(const IrrGroup *g) : CProxy_NodeGroup(g){
    }
    CProxy_DpcppComputePmeMgr(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_NodeGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_DpcppComputePmeMgr(CkGroupID _gid) : CProxy_NodeGroup(_gid){  }
    CProxyElement_DpcppComputePmeMgr operator[](int onPE) const
      {return CProxyElement_DpcppComputePmeMgr(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

    int ckIsDelegated(void) const
    { return CProxy_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxy_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxy_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxy_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_NodeGroup::ckSetReductionClient(cb); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxy_NodeGroup::ckSetGroupID(g);
    }
    DpcppComputePmeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputePmeMgr* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputePmeMgr*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputePmeMgr();
 */
    
    static CkGroupID ckNew(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initialize_pencils(CkQdMsg* impl_msg);
 */
    
    void initialize_pencils(CkQdMsg* impl_msg);

/* DECLS: void activate_pencils(CkQdMsg* impl_msg);
 */
    
    void activate_pencils(CkQdMsg* impl_msg);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvDevices(RecvDeviceMsg* impl_msg);
 */
    
    void recvDevices(RecvDeviceMsg* impl_msg);

/* DECLS: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
 */
    
    void recvAtomFiler(const CProxy_PmeAtomFiler &filer, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void skip();
 */
    
    void skip(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
 */
    
    void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);

/* DECLS: void initializePatches();
 */
    
    void initializePatches(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void incTotalPatchCount();
 */
    
    void incTotalPatchCount(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void registerPatch(RegisterPatchMsg* impl_msg);
 */
    
    void registerPatch(RegisterPatchMsg* impl_msg);

/* DECLS: void registerNeighbor(int y, int z);
 */
    
    void registerNeighbor(int y, int z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
    
    void recvAtoms(PmeAtomMsg* impl_msg);

/* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
    
    void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);

/* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
    
    void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);

};
PUPmarshall(CProxy_DpcppComputePmeMgr)
/* ---------------- section proxy -------------- */
class CProxySection_DpcppComputePmeMgr: public CProxySection_NodeGroup{
  public:
    typedef DpcppComputePmeMgr local_t;
    typedef CkIndex_DpcppComputePmeMgr index_t;
    typedef CProxy_DpcppComputePmeMgr proxy_t;
    typedef CProxyElement_DpcppComputePmeMgr element_t;
    typedef CProxySection_DpcppComputePmeMgr section_t;

    CProxySection_DpcppComputePmeMgr(void) {
    }
    CProxySection_DpcppComputePmeMgr(const IrrGroup *g) : CProxySection_NodeGroup(g){
    }
    CProxySection_DpcppComputePmeMgr(const CkGroupID &_gid,const int *_pelist,int _npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_DpcppComputePmeMgr(const CkGroupID &_gid,const int *_pelist,int _npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(_gid,_pelist,_npes,factor){  }
    CProxySection_DpcppComputePmeMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,factor){  }
    CProxySection_DpcppComputePmeMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

    int ckIsDelegated(void) const
    { return CProxySection_NodeGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_NodeGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_NodeGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_NodeGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxySection_NodeGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxySection_NodeGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxySection_NodeGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_NodeGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_NodeGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_NodeGroup::ckSetReductionClient(cb); }
inline int ckGetNumSections() const
{ return CProxySection_NodeGroup::ckGetNumSections(); }
inline CkSectionInfo &ckGetSectionInfo()
{ return CProxySection_NodeGroup::ckGetSectionInfo(); }
inline CkSectionID *ckGetSectionIDs()
{ return CProxySection_NodeGroup::ckGetSectionIDs(); }
inline CkSectionID &ckGetSectionID()
{ return CProxySection_NodeGroup::ckGetSectionID(); }
inline CkSectionID &ckGetSectionID(int i)
{ return CProxySection_NodeGroup::ckGetSectionID(i); }
inline CkGroupID ckGetGroupIDn(int i) const
{ return CProxySection_NodeGroup::ckGetGroupIDn(i); }
inline const int *ckGetElements() const
{ return CProxySection_NodeGroup::ckGetElements(); }
inline const int *ckGetElements(int i) const
{ return CProxySection_NodeGroup::ckGetElements(i); }
inline int ckGetNumElements() const
{ return CProxySection_NodeGroup::ckGetNumElements(); } 
inline int ckGetNumElements(int i) const
{ return CProxySection_NodeGroup::ckGetNumElements(i); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_NodeGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_NodeGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_NodeGroup::pup(p);
    }
    void ckSetGroupID(CkGroupID g) {
      CProxySection_NodeGroup::ckSetGroupID(g);
    }
    DpcppComputePmeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputePmeMgr* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputePmeMgr*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputePmeMgr();
 */
    

/* DECLS: void initialize_pencils(CkQdMsg* impl_msg);
 */
    
    void initialize_pencils(CkQdMsg* impl_msg);

/* DECLS: void activate_pencils(CkQdMsg* impl_msg);
 */
    
    void activate_pencils(CkQdMsg* impl_msg);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilXYZ &xyz, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilXY &xy, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z);
 */
    
    void recvPencils(const CProxy_DpcppPmePencilX &x, const CProxy_DpcppPmePencilY &y, const CProxy_DpcppPmePencilZ &z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvDevices(RecvDeviceMsg* impl_msg);
 */
    
    void recvDevices(RecvDeviceMsg* impl_msg);

/* DECLS: void recvAtomFiler(const CProxy_PmeAtomFiler &filer);
 */
    
    void recvAtomFiler(const CProxy_PmeAtomFiler &filer, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void skip();
 */
    
    void skip(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);
 */
    
    void initializeDevicesAndAtomFiler(NumDevicesMsg* impl_msg);

/* DECLS: void initializePatches();
 */
    
    void initializePatches(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void incTotalPatchCount();
 */
    
    void incTotalPatchCount(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void registerPatch(RegisterPatchMsg* impl_msg);
 */
    
    void registerPatch(RegisterPatchMsg* impl_msg);

/* DECLS: void registerNeighbor(int y, int z);
 */
    
    void registerNeighbor(int y, int z, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvAtoms(PmeAtomMsg* impl_msg);
 */
    
    void recvAtoms(PmeAtomMsg* impl_msg);

/* DECLS: void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);
 */
    
    void recvAtomsFromNeighbor(PmeAtomPencilMsg* impl_msg);

/* DECLS: void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);
 */
    
    void recvForcesFromNeighbor(PmeForcePencilMsg* impl_msg);

};
PUPmarshall(CProxySection_DpcppComputePmeMgr)
#define DpcppComputePmeMgr_SDAG_CODE                                           \
public:                                                                        \
  void initializeDevicesAndAtomFiler(NumDevicesMsg msg);                       \
  void initializeDevicesAndAtomFiler(NumDevicesMsg* gen0);                     \
private:                                                                       \
  void initializeDevicesAndAtomFiler_end(NumDevicesMsg* gen0);                 \
  void _slist_0(NumDevicesMsg* gen0);                                          \
  void _slist_0_end(NumDevicesMsg* gen0);                                      \
  void _serial_0(NumDevicesMsg* gen0);                                         \
public:                                                                        \
  void initializePatches();                                                    \
private:                                                                       \
  void initializePatches_end();                                                \
  void _slist_1();                                                             \
  void _slist_1_end();                                                         \
  void _serial_1();                                                            \
public:                                                                        \
  void incTotalPatchCount();                                                   \
private:                                                                       \
  void incTotalPatchCount_end();                                               \
  void _slist_2();                                                             \
  void _slist_2_end();                                                         \
  void _serial_2();                                                            \
public:                                                                        \
  void registerPatch(RegisterPatchMsg msg);                                    \
  void registerPatch(RegisterPatchMsg* gen0);                                  \
private:                                                                       \
  void registerPatch_end(RegisterPatchMsg* gen0);                              \
  void _slist_3(RegisterPatchMsg* gen0);                                       \
  void _slist_3_end(RegisterPatchMsg* gen0);                                   \
  void _serial_3(RegisterPatchMsg* gen0);                                      \
public:                                                                        \
  void registerNeighbor(int y, int z);                                         \
  void registerNeighbor(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0);\
private:                                                                       \
  void registerNeighbor_end(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0);\
  void _slist_4(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0);\
  void _slist_4_end(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0);\
  void _serial_4(Closure_DpcppComputePmeMgr::registerNeighbor_14_closure* gen0);\
public:                                                                        \
  void recvAtomsFromNeighbor(PmeAtomPencilMsg msg);                            \
  void recvAtomsFromNeighbor(PmeAtomPencilMsg* gen0);                          \
private:                                                                       \
  void recvAtomsFromNeighbor_end(PmeAtomPencilMsg* gen0);                      \
  void _slist_5(PmeAtomPencilMsg* gen0);                                       \
  void _slist_5_end(PmeAtomPencilMsg* gen0);                                   \
  void _serial_5(PmeAtomPencilMsg* gen0);                                      \
public:                                                                        \
  void recvForcesFromNeighbor(PmeForcePencilMsg msg);                          \
  void recvForcesFromNeighbor(PmeForcePencilMsg* gen0);                        \
private:                                                                       \
  void recvForcesFromNeighbor_end(PmeForcePencilMsg* gen0);                    \
  void _slist_6(PmeForcePencilMsg* gen0);                                      \
  void _slist_6_end(PmeForcePencilMsg* gen0);                                  \
  void _serial_6(PmeForcePencilMsg* gen0);                                     \
public:                                                                        \
public:                                                                        \
  SDAG::dep_ptr __dep;                                                         \
  void _sdag_init();                                                           \
  void __sdag_init();                                                          \
public:                                                                        \
  void _sdag_pup(PUP::er &p);                                                  \
  void __sdag_pup(PUP::er &p) { }                                              \
  static void __sdag_register();                                               \
  static int _sdag_idx_DpcppComputePmeMgr_serial_0();                          \
  static int _sdag_reg_DpcppComputePmeMgr_serial_0();                          \
  static int _sdag_idx_DpcppComputePmeMgr_serial_1();                          \
  static int _sdag_reg_DpcppComputePmeMgr_serial_1();                          \
  static int _sdag_idx_DpcppComputePmeMgr_serial_2();                          \
  static int _sdag_reg_DpcppComputePmeMgr_serial_2();                          \
  static int _sdag_idx_DpcppComputePmeMgr_serial_3();                          \
  static int _sdag_reg_DpcppComputePmeMgr_serial_3();                          \
  static int _sdag_idx_DpcppComputePmeMgr_serial_4();                          \
  static int _sdag_reg_DpcppComputePmeMgr_serial_4();                          \
  static int _sdag_idx_DpcppComputePmeMgr_serial_5();                          \
  static int _sdag_reg_DpcppComputePmeMgr_serial_5();                          \
  static int _sdag_idx_DpcppComputePmeMgr_serial_6();                          \
  static int _sdag_reg_DpcppComputePmeMgr_serial_6();                          \

typedef CBaseT1<NodeGroup, CProxy_DpcppComputePmeMgr>CBase_DpcppComputePmeMgr;







/* ---------------- method closures -------------- */
class Closure_PmeAtomFiler {
  public:

};

/* ---------------- method closures -------------- */
class Closure_DpcppComputePmeDevice {
  public:



    struct sendAtomsToNeighbor_3_closure;



    struct gatherForce_5_closure;



    struct mergeForcesOnPatch_7_closure;


};





/* ---------------- method closures -------------- */
class Closure_DpcppComputePmeMgr {
  public:




    struct recvPencils_4_closure;


    struct recvPencils_5_closure;


    struct recvPencils_6_closure;



    struct recvAtomFiler_8_closure;


    struct skip_9_closure;



    struct initializePatches_11_closure;


    struct incTotalPatchCount_12_closure;



    struct registerNeighbor_14_closure;




};

extern void _registerDpcppComputePmeMgr(void);
#endif
