#ifndef _DECL_BroadcastMgr_H_
#define _DECL_BroadcastMgr_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message BroadcastMsg;
 */
class BroadcastMsg;
class CMessage_BroadcastMsg:public CkMessage{
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
    CMessage_BroadcastMsg();
    static void *pack(BroadcastMsg *p);
    static BroadcastMsg* unpack(void* p);
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

/* DECLS: group BroadcastMgr: IrrGroup{
BroadcastMgr();
void recvBroadcast(BroadcastMsg* impl_msg);
};
 */
 class BroadcastMgr;
 class CkIndex_BroadcastMgr;
 class CProxy_BroadcastMgr;
 class CProxyElement_BroadcastMgr;
 class CProxySection_BroadcastMgr;
/* --------------- index object ------------------ */
class CkIndex_BroadcastMgr:public CkIndex_IrrGroup{
  public:
    typedef BroadcastMgr local_t;
    typedef CkIndex_BroadcastMgr index_t;
    typedef CProxy_BroadcastMgr proxy_t;
    typedef CProxyElement_BroadcastMgr element_t;
    typedef CProxySection_BroadcastMgr section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: BroadcastMgr();
     */
    // Entry point registration at startup
    
    static int reg_BroadcastMgr_void();
    // Entry point index lookup
    
    inline static int idx_BroadcastMgr_void() {
      static int epidx = reg_BroadcastMgr_void();
      return epidx;
    }

    
    static int ckNew() { return idx_BroadcastMgr_void(); }
    
    static void _call_BroadcastMgr_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_BroadcastMgr_void(void* impl_msg, void* impl_obj);
    /* DECLS: void recvBroadcast(BroadcastMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvBroadcast_BroadcastMsg();
    // Entry point index lookup
    
    inline static int idx_recvBroadcast_BroadcastMsg() {
      static int epidx = reg_recvBroadcast_BroadcastMsg();
      return epidx;
    }

    
    inline static int idx_recvBroadcast(void (BroadcastMgr::*)(BroadcastMsg* impl_msg) ) {
      return idx_recvBroadcast_BroadcastMsg();
    }


    
    static int recvBroadcast(BroadcastMsg* impl_msg) { return idx_recvBroadcast_BroadcastMsg(); }
    
    static void _call_recvBroadcast_BroadcastMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvBroadcast_BroadcastMsg(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxyElement_BroadcastMgr: public CProxyElement_IrrGroup{
  public:
    typedef BroadcastMgr local_t;
    typedef CkIndex_BroadcastMgr index_t;
    typedef CProxy_BroadcastMgr proxy_t;
    typedef CProxyElement_BroadcastMgr element_t;
    typedef CProxySection_BroadcastMgr section_t;


    /* TRAM aggregators */

    CProxyElement_BroadcastMgr(void) {
    }
    CProxyElement_BroadcastMgr(const IrrGroup *g) : CProxyElement_IrrGroup(g){
    }
    CProxyElement_BroadcastMgr(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_IrrGroup(_gid,_onPE,CK_DELCTOR_ARGS){
    }
    CProxyElement_BroadcastMgr(CkGroupID _gid,int _onPE) : CProxyElement_IrrGroup(_gid,_onPE){
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
    BroadcastMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static BroadcastMgr* ckLocalBranch(CkGroupID gID) {
      return (BroadcastMgr*)CkLocalBranch(gID);
    }
/* DECLS: BroadcastMgr();
 */
    

/* DECLS: void recvBroadcast(BroadcastMsg* impl_msg);
 */
    
    void recvBroadcast(BroadcastMsg* impl_msg);

};
PUPmarshall(CProxyElement_BroadcastMgr)
/* ---------------- collective proxy -------------- */
class CProxy_BroadcastMgr: public CProxy_IrrGroup{
  public:
    typedef BroadcastMgr local_t;
    typedef CkIndex_BroadcastMgr index_t;
    typedef CProxy_BroadcastMgr proxy_t;
    typedef CProxyElement_BroadcastMgr element_t;
    typedef CProxySection_BroadcastMgr section_t;

    CProxy_BroadcastMgr(void) {
    }
    CProxy_BroadcastMgr(const IrrGroup *g) : CProxy_IrrGroup(g){
    }
    CProxy_BroadcastMgr(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_IrrGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_BroadcastMgr(CkGroupID _gid) : CProxy_IrrGroup(_gid){  }
    CProxyElement_BroadcastMgr operator[](int onPE) const
      {return CProxyElement_BroadcastMgr(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

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
    BroadcastMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static BroadcastMgr* ckLocalBranch(CkGroupID gID) {
      return (BroadcastMgr*)CkLocalBranch(gID);
    }
/* DECLS: BroadcastMgr();
 */
    
    static CkGroupID ckNew(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBroadcast(BroadcastMsg* impl_msg);
 */
    
    void recvBroadcast(BroadcastMsg* impl_msg);
    
    void recvBroadcast(BroadcastMsg* impl_msg, int npes, int *pes);
    
    void recvBroadcast(BroadcastMsg* impl_msg, CmiGroup &grp);

};
PUPmarshall(CProxy_BroadcastMgr)
/* ---------------- section proxy -------------- */
class CProxySection_BroadcastMgr: public CProxySection_IrrGroup{
  public:
    typedef BroadcastMgr local_t;
    typedef CkIndex_BroadcastMgr index_t;
    typedef CProxy_BroadcastMgr proxy_t;
    typedef CProxyElement_BroadcastMgr element_t;
    typedef CProxySection_BroadcastMgr section_t;

    CProxySection_BroadcastMgr(void) {
    }
    CProxySection_BroadcastMgr(const IrrGroup *g) : CProxySection_IrrGroup(g){
    }
    CProxySection_BroadcastMgr(const CkGroupID &_gid,const int *_pelist,int _npes, CK_DELCTOR_PARAM) : CProxySection_IrrGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_BroadcastMgr(const CkGroupID &_gid,const int *_pelist,int _npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_IrrGroup(_gid,_pelist,_npes,factor){  }
    CProxySection_BroadcastMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_IrrGroup(n,_gid,_pelist,_npes,factor){  }
    CProxySection_BroadcastMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, CK_DELCTOR_PARAM) : CProxySection_IrrGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

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
    BroadcastMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static BroadcastMgr* ckLocalBranch(CkGroupID gID) {
      return (BroadcastMgr*)CkLocalBranch(gID);
    }
/* DECLS: BroadcastMgr();
 */
    

/* DECLS: void recvBroadcast(BroadcastMsg* impl_msg);
 */
    
    void recvBroadcast(BroadcastMsg* impl_msg);

};
PUPmarshall(CProxySection_BroadcastMgr)
#define BroadcastMgr_SDAG_CODE 
typedef CBaseT1<Group, CProxy_BroadcastMgr>CBase_BroadcastMgr;


/* ---------------- method closures -------------- */
class Closure_BroadcastMgr {
  public:


};

extern void _registerBroadcastMgr(void);
#endif
