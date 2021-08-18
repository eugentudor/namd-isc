#ifndef _DECL_DpcppComputeMgr_H_
#define _DECL_DpcppComputeMgr_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
/* DECLS: nodegroup DpcppComputeMgr: NodeGroup{
DpcppComputeMgr();
void initialize(CkQdMsg* impl_msg);
};
 */
 class DpcppComputeMgr;
 class CkIndex_DpcppComputeMgr;
 class CProxy_DpcppComputeMgr;
 class CProxyElement_DpcppComputeMgr;
 class CProxySection_DpcppComputeMgr;
/* --------------- index object ------------------ */
class CkIndex_DpcppComputeMgr:public CkIndex_NodeGroup{
  public:
    typedef DpcppComputeMgr local_t;
    typedef CkIndex_DpcppComputeMgr index_t;
    typedef CProxy_DpcppComputeMgr proxy_t;
    typedef CProxyElement_DpcppComputeMgr element_t;
    typedef CProxySection_DpcppComputeMgr section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppComputeMgr();
     */
    // Entry point registration at startup
    
    static int reg_DpcppComputeMgr_void();
    // Entry point index lookup
    
    inline static int idx_DpcppComputeMgr_void() {
      static int epidx = reg_DpcppComputeMgr_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppComputeMgr_void(); }
    
    static void _call_DpcppComputeMgr_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppComputeMgr_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize(CkQdMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_CkQdMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_CkQdMsg() {
      static int epidx = reg_initialize_CkQdMsg();
      return epidx;
    }

    
    inline static int idx_initialize(void (DpcppComputeMgr::*)(CkQdMsg* impl_msg) ) {
      return idx_initialize_CkQdMsg();
    }


    
    static int initialize(CkQdMsg* impl_msg) { return idx_initialize_CkQdMsg(); }
    
    static void _call_initialize_CkQdMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_CkQdMsg(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxyElement_DpcppComputeMgr: public CProxyElement_NodeGroup{
  public:
    typedef DpcppComputeMgr local_t;
    typedef CkIndex_DpcppComputeMgr index_t;
    typedef CProxy_DpcppComputeMgr proxy_t;
    typedef CProxyElement_DpcppComputeMgr element_t;
    typedef CProxySection_DpcppComputeMgr section_t;


    /* TRAM aggregators */

    CProxyElement_DpcppComputeMgr(void) {
    }
    CProxyElement_DpcppComputeMgr(const IrrGroup *g) : CProxyElement_NodeGroup(g){
    }
    CProxyElement_DpcppComputeMgr(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_NodeGroup(_gid,_onPE,CK_DELCTOR_ARGS){
    }
    CProxyElement_DpcppComputeMgr(CkGroupID _gid,int _onPE) : CProxyElement_NodeGroup(_gid,_onPE){
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
    DpcppComputeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputeMgr* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputeMgr*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputeMgr();
 */
    

/* DECLS: void initialize(CkQdMsg* impl_msg);
 */
    
    void initialize(CkQdMsg* impl_msg);

};
PUPmarshall(CProxyElement_DpcppComputeMgr)
/* ---------------- collective proxy -------------- */
class CProxy_DpcppComputeMgr: public CProxy_NodeGroup{
  public:
    typedef DpcppComputeMgr local_t;
    typedef CkIndex_DpcppComputeMgr index_t;
    typedef CProxy_DpcppComputeMgr proxy_t;
    typedef CProxyElement_DpcppComputeMgr element_t;
    typedef CProxySection_DpcppComputeMgr section_t;

    CProxy_DpcppComputeMgr(void) {
    }
    CProxy_DpcppComputeMgr(const IrrGroup *g) : CProxy_NodeGroup(g){
    }
    CProxy_DpcppComputeMgr(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_NodeGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_DpcppComputeMgr(CkGroupID _gid) : CProxy_NodeGroup(_gid){  }
    CProxyElement_DpcppComputeMgr operator[](int onPE) const
      {return CProxyElement_DpcppComputeMgr(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

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
    DpcppComputeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputeMgr* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputeMgr*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputeMgr();
 */
    
    static CkGroupID ckNew(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initialize(CkQdMsg* impl_msg);
 */
    
    void initialize(CkQdMsg* impl_msg);

};
PUPmarshall(CProxy_DpcppComputeMgr)
/* ---------------- section proxy -------------- */
class CProxySection_DpcppComputeMgr: public CProxySection_NodeGroup{
  public:
    typedef DpcppComputeMgr local_t;
    typedef CkIndex_DpcppComputeMgr index_t;
    typedef CProxy_DpcppComputeMgr proxy_t;
    typedef CProxyElement_DpcppComputeMgr element_t;
    typedef CProxySection_DpcppComputeMgr section_t;

    CProxySection_DpcppComputeMgr(void) {
    }
    CProxySection_DpcppComputeMgr(const IrrGroup *g) : CProxySection_NodeGroup(g){
    }
    CProxySection_DpcppComputeMgr(const CkGroupID &_gid,const int *_pelist,int _npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_DpcppComputeMgr(const CkGroupID &_gid,const int *_pelist,int _npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(_gid,_pelist,_npes,factor){  }
    CProxySection_DpcppComputeMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,factor){  }
    CProxySection_DpcppComputeMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, CK_DELCTOR_PARAM) : CProxySection_NodeGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

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
    DpcppComputeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static DpcppComputeMgr* ckLocalBranch(CkGroupID gID) {
      return (DpcppComputeMgr*)CkLocalNodeBranch(gID);
    }
/* DECLS: DpcppComputeMgr();
 */
    

/* DECLS: void initialize(CkQdMsg* impl_msg);
 */
    
    void initialize(CkQdMsg* impl_msg);

};
PUPmarshall(CProxySection_DpcppComputeMgr)
#define DpcppComputeMgr_SDAG_CODE 
typedef CBaseT1<NodeGroup, CProxy_DpcppComputeMgr>CBase_DpcppComputeMgr;

/* ---------------- method closures -------------- */
class Closure_DpcppComputeMgr {
  public:


};

extern void _registerDpcppComputeMgr(void);
#endif
