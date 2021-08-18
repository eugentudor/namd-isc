#ifndef _DECL_DpcppPmeSolver_H_
#define _DECL_DpcppPmeSolver_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
#include "PmeSolver.decl.h"

#ifndef GROUPDEPNUM_DECLARED
# define GROUPDEPNUM_DECLARED
struct GroupDepNum
{
  int groupDepNum;
  explicit GroupDepNum(int g = 0) : groupDepNum{g} { }
  operator int() const { return groupDepNum; }
};
#endif
/* DECLS: message DpcppPmeXYZInitMsg;
 */
class DpcppPmeXYZInitMsg;
class CMessage_DpcppPmeXYZInitMsg:public CkMessage{
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
    CMessage_DpcppPmeXYZInitMsg();
    static void *pack(DpcppPmeXYZInitMsg *p);
    static DpcppPmeXYZInitMsg* unpack(void* p);
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
/* DECLS: message DpcppPmeXYInitMsg;
 */
class DpcppPmeXYInitMsg;
class CMessage_DpcppPmeXYInitMsg:public CkMessage{
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
    CMessage_DpcppPmeXYInitMsg();
    static void *pack(DpcppPmeXYInitMsg *p);
    static DpcppPmeXYInitMsg* unpack(void* p);
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
/* DECLS: message DpcppPmeXInitMsg;
 */
class DpcppPmeXInitMsg;
class CMessage_DpcppPmeXInitMsg:public CkMessage{
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
    CMessage_DpcppPmeXInitMsg();
    static void *pack(DpcppPmeXInitMsg *p);
    static DpcppPmeXInitMsg* unpack(void* p);
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
/* DECLS: message InitDeviceMsg;
 */
class InitDeviceMsg;
class CMessage_InitDeviceMsg:public CkMessage{
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
    CMessage_InitDeviceMsg();
    static void *pack(InitDeviceMsg *p);
    static InitDeviceMsg* unpack(void* p);
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
/* DECLS: message InitDeviceMsg2;
 */
class InitDeviceMsg2;
class CMessage_InitDeviceMsg2:public CkMessage{
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
    CMessage_InitDeviceMsg2();
    static void *pack(InitDeviceMsg2 *p);
    static InitDeviceMsg2* unpack(void* p);
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
/* DECLS: message DeviceDataMsg;
 */
class DeviceDataMsg;
class CMessage_DeviceDataMsg:public CkMessage{
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
    CMessage_DeviceDataMsg();
    static void *pack(DeviceDataMsg *p);
    static DeviceDataMsg* unpack(void* p);
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

/* DECLS: array DpcppPmePencilXYZ: PmePencilXYZ{
DpcppPmePencilXYZ();
void initialize(DpcppPmeXYZInitMsg* impl_msg);
void initializeDevice(InitDeviceMsg* impl_msg);
DpcppPmePencilXYZ(CkMigrateMessage* impl_msg);
};
 */
 class DpcppPmePencilXYZ;
 class CkIndex_DpcppPmePencilXYZ;
 class CProxy_DpcppPmePencilXYZ;
 class CProxyElement_DpcppPmePencilXYZ;
 class CProxySection_DpcppPmePencilXYZ;
/* --------------- index object ------------------ */
class CkIndex_DpcppPmePencilXYZ:public CkIndex_PmePencilXYZ{
  public:
    typedef DpcppPmePencilXYZ local_t;
    typedef CkIndex_DpcppPmePencilXYZ index_t;
    typedef CProxy_DpcppPmePencilXYZ proxy_t;
    typedef CProxyElement_DpcppPmePencilXYZ element_t;
    typedef CProxySection_DpcppPmePencilXYZ section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppPmePencilXYZ();
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilXYZ_void();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilXYZ_void() {
      static int epidx = reg_DpcppPmePencilXYZ_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppPmePencilXYZ_void(); }
    
    static void _call_DpcppPmePencilXYZ_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilXYZ_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize(DpcppPmeXYZInitMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_DpcppPmeXYZInitMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_DpcppPmeXYZInitMsg() {
      static int epidx = reg_initialize_DpcppPmeXYZInitMsg();
      return epidx;
    }

    
    inline static int idx_initialize(void (DpcppPmePencilXYZ::*)(DpcppPmeXYZInitMsg* impl_msg) ) {
      return idx_initialize_DpcppPmeXYZInitMsg();
    }


    
    static int initialize(DpcppPmeXYZInitMsg* impl_msg) { return idx_initialize_DpcppPmeXYZInitMsg(); }
    
    static void _call_initialize_DpcppPmeXYZInitMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_DpcppPmeXYZInitMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initializeDevice_InitDeviceMsg();
    // Entry point index lookup
    
    inline static int idx_initializeDevice_InitDeviceMsg() {
      static int epidx = reg_initializeDevice_InitDeviceMsg();
      return epidx;
    }

    
    inline static int idx_initializeDevice(void (DpcppPmePencilXYZ::*)(InitDeviceMsg* impl_msg) ) {
      return idx_initializeDevice_InitDeviceMsg();
    }


    
    static int initializeDevice(InitDeviceMsg* impl_msg) { return idx_initializeDevice_InitDeviceMsg(); }
    
    static void _call_initializeDevice_InitDeviceMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initializeDevice_InitDeviceMsg(void* impl_msg, void* impl_obj);
    /* DECLS: DpcppPmePencilXYZ(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilXYZ_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilXYZ_CkMigrateMessage() {
      static int epidx = reg_DpcppPmePencilXYZ_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_DpcppPmePencilXYZ_CkMigrateMessage(); }
    
    static void _call_DpcppPmePencilXYZ_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilXYZ_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_DpcppPmePencilXYZ : public CProxyElement_PmePencilXYZ{
  public:
    typedef DpcppPmePencilXYZ local_t;
    typedef CkIndex_DpcppPmePencilXYZ index_t;
    typedef CProxy_DpcppPmePencilXYZ proxy_t;
    typedef CProxyElement_DpcppPmePencilXYZ element_t;
    typedef CProxySection_DpcppPmePencilXYZ section_t;

    using array_index_t = CkArrayIndex1D;

    /* TRAM aggregators */

    CProxyElement_DpcppPmePencilXYZ(void) {
    }
    CProxyElement_DpcppPmePencilXYZ(const ArrayElement *e) : CProxyElement_PmePencilXYZ(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_PmePencilXYZ::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_PmePencilXYZ::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_PmePencilXYZ::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxyElement_PmePencilXYZ::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_PmePencilXYZ::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_PmePencilXYZ::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_PmePencilXYZ::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_PmePencilXYZ::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_PmePencilXYZ::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_PmePencilXYZ::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_PmePencilXYZ::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxyElement_PmePencilXYZ::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxyElement_PmePencilXYZ::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_PmePencilXYZ::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_PmePencilXYZ::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_PmePencilXYZ::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_PmePencilXYZ::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilXYZ::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilXYZ::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_PmePencilXYZ::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_PmePencilXYZ::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_PmePencilXYZ::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_PmePencilXYZ::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_PmePencilXYZ::ckGetIndex(); }

    DpcppPmePencilXYZ *ckLocal(void) const
    { return (DpcppPmePencilXYZ *)CProxyElement_PmePencilXYZ::ckLocal(); }

    CProxyElement_DpcppPmePencilXYZ(const CkArrayID &aid,const CkArrayIndex1D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilXYZ(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilXYZ(const CkArrayID &aid,const CkArrayIndex1D &idx)
        :CProxyElement_PmePencilXYZ(aid,idx)
    {
}

    CProxyElement_DpcppPmePencilXYZ(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilXYZ(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilXYZ(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_PmePencilXYZ(aid,idx)
    {
}
/* DECLS: DpcppPmePencilXYZ();
 */
    
    void insert(int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void initialize(DpcppPmeXYZInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYZInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: DpcppPmePencilXYZ(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxyElement_DpcppPmePencilXYZ)
/* ---------------- collective proxy -------------- */
 class CProxy_DpcppPmePencilXYZ : public CProxy_PmePencilXYZ{
  public:
    typedef DpcppPmePencilXYZ local_t;
    typedef CkIndex_DpcppPmePencilXYZ index_t;
    typedef CProxy_DpcppPmePencilXYZ proxy_t;
    typedef CProxyElement_DpcppPmePencilXYZ element_t;
    typedef CProxySection_DpcppPmePencilXYZ section_t;

    using array_index_t = CkArrayIndex1D;
    CProxy_DpcppPmePencilXYZ(void) {
    }
    CProxy_DpcppPmePencilXYZ(const ArrayElement *e) : CProxy_PmePencilXYZ(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_PmePencilXYZ::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_PmePencilXYZ::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_PmePencilXYZ::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxy_PmePencilXYZ::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_PmePencilXYZ::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_PmePencilXYZ::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_PmePencilXYZ::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_PmePencilXYZ::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_PmePencilXYZ::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_PmePencilXYZ::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_PmePencilXYZ::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxy_PmePencilXYZ::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxy_PmePencilXYZ::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_PmePencilXYZ::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_PmePencilXYZ::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_PmePencilXYZ::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_PmePencilXYZ::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilXYZ::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilXYZ::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_PmePencilXYZ::ckSetReductionClient(cb); }

    // Generalized array indexing:
    CProxyElement_DpcppPmePencilXYZ operator [] (const CkArrayIndex1D &idx) const
    { return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilXYZ operator() (const CkArrayIndex1D &idx) const
    { return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilXYZ operator [] (int idx) const 
        {return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), CkArrayIndex1D(idx), CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilXYZ operator () (int idx) const 
        {return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), CkArrayIndex1D(idx), CK_DELCTOR_CALL);}
    CProxy_DpcppPmePencilXYZ(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_PmePencilXYZ(aid,CK_DELCTOR_ARGS) {}
    CProxy_DpcppPmePencilXYZ(const CkArrayID &aid) 
        :CProxy_PmePencilXYZ(aid) {}
/* DECLS: DpcppPmePencilXYZ();
 */
    
    static CkArrayID ckNew(const CkArrayOptions &opts = CkArrayOptions(), const CkEntryOptions *impl_e_opts=NULL);
    static void      ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(const int s1, const CkEntryOptions *impl_e_opts=NULL);
    static void ckNew(const int s1, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initialize(DpcppPmeXYZInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYZInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: DpcppPmePencilXYZ(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxy_DpcppPmePencilXYZ)
/* ---------------- section proxy -------------- */
 class CProxySection_DpcppPmePencilXYZ : public CProxySection_PmePencilXYZ{
  public:
    typedef DpcppPmePencilXYZ local_t;
    typedef CkIndex_DpcppPmePencilXYZ index_t;
    typedef CProxy_DpcppPmePencilXYZ proxy_t;
    typedef CProxyElement_DpcppPmePencilXYZ element_t;
    typedef CProxySection_DpcppPmePencilXYZ section_t;

    using array_index_t = CkArrayIndex1D;
    CProxySection_DpcppPmePencilXYZ(void) {
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_PmePencilXYZ::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_PmePencilXYZ::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_PmePencilXYZ::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxySection_PmePencilXYZ::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_PmePencilXYZ::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_PmePencilXYZ::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_PmePencilXYZ::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_PmePencilXYZ::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_PmePencilXYZ::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_PmePencilXYZ::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_PmePencilXYZ::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxySection_PmePencilXYZ::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxySection_PmePencilXYZ::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_PmePencilXYZ::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_PmePencilXYZ::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_PmePencilXYZ::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_PmePencilXYZ::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilXYZ::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilXYZ::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_PmePencilXYZ::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_PmePencilXYZ::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_PmePencilXYZ::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_PmePencilXYZ::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_PmePencilXYZ::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_PmePencilXYZ::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_PmePencilXYZ::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_PmePencilXYZ::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_PmePencilXYZ::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_PmePencilXYZ::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_PmePencilXYZ::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_DpcppPmePencilXYZ operator [] (const CkArrayIndex1D &idx) const
        {return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilXYZ operator() (const CkArrayIndex1D &idx) const
        {return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilXYZ operator [] (int idx) const 
        {return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), *(CkArrayIndex1D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilXYZ operator () (int idx) const 
        {return CProxyElement_DpcppPmePencilXYZ(ckGetArrayID(), *(CkArrayIndex1D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex1D *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex1D> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l, int u, int s, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      std::vector<CkArrayIndex1D> al;
      for (int i=l; i<=u; i+=s) al.emplace_back(i);
      return CkSectionID(aid, al, factor);
    } 
    CProxySection_DpcppPmePencilXYZ(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXYZ(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXYZ(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXYZ(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXYZ(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilXYZ(aid,elems,nElems, factor) {}
    CProxySection_DpcppPmePencilXYZ(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilXYZ(aid,elems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXYZ(const CkSectionID &sid)  
        :CProxySection_PmePencilXYZ(sid) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXYZ(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXYZ(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXYZ(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXYZ(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXYZ(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_PmePencilXYZ(n,aid,elems,nElems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXYZ(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems) 
        :CProxySection_PmePencilXYZ(aid,elems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXYZ(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, int factor) 
        :CProxySection_PmePencilXYZ(n,aid,elems,nElems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXYZ(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, int factor) 
        :CProxySection_PmePencilXYZ(aid,elems, factor) { ckAutoDelegate(); }
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems) {
       return CkSectionID(aid, elems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor) {
      return CkSectionID(aid, elems, factor);
    } 
    void ckAutoDelegate(int opts=1) {
      if(ckIsDelegated()) return;
      CProxySection_PmePencilXYZ::ckAutoDelegate(opts);
    } 
    void setReductionClient(CkCallback *cb) {
      CProxySection_PmePencilXYZ::setReductionClient(cb);
    } 
    void resetSection() {
      CProxySection_PmePencilXYZ::resetSection();
    } 
    static void contribute(CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
/* DECLS: DpcppPmePencilXYZ();
 */
    

/* DECLS: void initialize(DpcppPmeXYZInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYZInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: DpcppPmePencilXYZ(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxySection_DpcppPmePencilXYZ)
#define DpcppPmePencilXYZ_SDAG_CODE 
typedef CBaseT1<PmePencilXYZ, CProxy_DpcppPmePencilXYZ>CBase_DpcppPmePencilXYZ;

class CProxy_DpcppPmePencilZ;

/* DECLS: array DpcppPmePencilXY: PmePencilXY{
DpcppPmePencilXY();
void initialize(DpcppPmeXYInitMsg* impl_msg);
void initializeDevice(InitDeviceMsg* impl_msg);
void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
void recvDeviceBuffer(DeviceDataMsg* impl_msg);
void recvDeviceBuffers(const CkCallback &cb);
DpcppPmePencilXY(CkMigrateMessage* impl_msg);
};
 */
 class DpcppPmePencilXY;
 class CkIndex_DpcppPmePencilXY;
 class CProxy_DpcppPmePencilXY;
 class CProxyElement_DpcppPmePencilXY;
 class CProxySection_DpcppPmePencilXY;
/* --------------- index object ------------------ */
class CkIndex_DpcppPmePencilXY:public CkIndex_PmePencilXY{
  public:
    typedef DpcppPmePencilXY local_t;
    typedef CkIndex_DpcppPmePencilXY index_t;
    typedef CProxy_DpcppPmePencilXY proxy_t;
    typedef CProxyElement_DpcppPmePencilXY element_t;
    typedef CProxySection_DpcppPmePencilXY section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppPmePencilXY();
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilXY_void();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilXY_void() {
      static int epidx = reg_DpcppPmePencilXY_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppPmePencilXY_void(); }
    
    static void _call_DpcppPmePencilXY_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilXY_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_DpcppPmeXYInitMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_DpcppPmeXYInitMsg() {
      static int epidx = reg_initialize_DpcppPmeXYInitMsg();
      return epidx;
    }

    
    inline static int idx_initialize(void (DpcppPmePencilXY::*)(DpcppPmeXYInitMsg* impl_msg) ) {
      return idx_initialize_DpcppPmeXYInitMsg();
    }


    
    static int initialize(DpcppPmeXYInitMsg* impl_msg) { return idx_initialize_DpcppPmeXYInitMsg(); }
    
    static void _call_initialize_DpcppPmeXYInitMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_DpcppPmeXYInitMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initializeDevice_InitDeviceMsg();
    // Entry point index lookup
    
    inline static int idx_initializeDevice_InitDeviceMsg() {
      static int epidx = reg_initializeDevice_InitDeviceMsg();
      return epidx;
    }

    
    inline static int idx_initializeDevice(void (DpcppPmePencilXY::*)(InitDeviceMsg* impl_msg) ) {
      return idx_initializeDevice_InitDeviceMsg();
    }


    
    static int initializeDevice(InitDeviceMsg* impl_msg) { return idx_initializeDevice_InitDeviceMsg(); }
    
    static void _call_initializeDevice_InitDeviceMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initializeDevice_InitDeviceMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBufferZ_marshall4();
    // Entry point index lookup
    
    inline static int idx_getDeviceBufferZ_marshall4() {
      static int epidx = reg_getDeviceBufferZ_marshall4();
      return epidx;
    }

    
    inline static int idx_getDeviceBufferZ(void (DpcppPmePencilXY::*)(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) ) {
      return idx_getDeviceBufferZ_marshall4();
    }


    
    static int getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) { return idx_getDeviceBufferZ_marshall4(); }
    
    static void _call_getDeviceBufferZ_marshall4(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBufferZ_marshall4(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBufferZ_marshall4(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBufferZ_marshall4(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer_marshall5();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer_marshall5() {
      static int epidx = reg_getDeviceBuffer_marshall5();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer(void (DpcppPmePencilXY::*)(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) ) {
      return idx_getDeviceBuffer_marshall5();
    }


    
    static int getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) { return idx_getDeviceBuffer_marshall5(); }
    
    static void _call_getDeviceBuffer_marshall5(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer_marshall5(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer_marshall5(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer_marshall5(PUP::er &p,void *msg);
    /* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBuffer_DeviceDataMsg();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBuffer_DeviceDataMsg() {
      static int epidx = reg_recvDeviceBuffer_DeviceDataMsg();
      return epidx;
    }

    
    inline static int idx_recvDeviceBuffer(void (DpcppPmePencilXY::*)(DeviceDataMsg* impl_msg) ) {
      return idx_recvDeviceBuffer_DeviceDataMsg();
    }


    
    static int recvDeviceBuffer(DeviceDataMsg* impl_msg) { return idx_recvDeviceBuffer_DeviceDataMsg(); }
    
    static void _call_recvDeviceBuffer_DeviceDataMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBuffer_DeviceDataMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvDeviceBuffers(const CkCallback &cb);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBuffers_marshall7();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBuffers_marshall7() {
      static int epidx = reg_recvDeviceBuffers_marshall7();
      return epidx;
    }

    
    inline static int idx_recvDeviceBuffers(void (DpcppPmePencilXY::*)(const CkCallback &cb) ) {
      return idx_recvDeviceBuffers_marshall7();
    }


    
    static int recvDeviceBuffers(const CkCallback &cb) { return idx_recvDeviceBuffers_marshall7(); }
    
    static void _call_recvDeviceBuffers_marshall7(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBuffers_marshall7(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvDeviceBuffers_marshall7(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvDeviceBuffers_marshall7(PUP::er &p,void *msg);
    /* DECLS: DpcppPmePencilXY(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilXY_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilXY_CkMigrateMessage() {
      static int epidx = reg_DpcppPmePencilXY_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_DpcppPmePencilXY_CkMigrateMessage(); }
    
    static void _call_DpcppPmePencilXY_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilXY_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_DpcppPmePencilXY : public CProxyElement_PmePencilXY{
  public:
    typedef DpcppPmePencilXY local_t;
    typedef CkIndex_DpcppPmePencilXY index_t;
    typedef CProxy_DpcppPmePencilXY proxy_t;
    typedef CProxyElement_DpcppPmePencilXY element_t;
    typedef CProxySection_DpcppPmePencilXY section_t;

    using array_index_t = CkArrayIndex3D;

    /* TRAM aggregators */

    CProxyElement_DpcppPmePencilXY(void) {
    }
    CProxyElement_DpcppPmePencilXY(const ArrayElement *e) : CProxyElement_PmePencilXY(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_PmePencilXY::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_PmePencilXY::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_PmePencilXY::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxyElement_PmePencilXY::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_PmePencilXY::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_PmePencilXY::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_PmePencilXY::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_PmePencilXY::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_PmePencilXY::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_PmePencilXY::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_PmePencilXY::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxyElement_PmePencilXY::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxyElement_PmePencilXY::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_PmePencilXY::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_PmePencilXY::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_PmePencilXY::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_PmePencilXY::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilXY::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilXY::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_PmePencilXY::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_PmePencilXY::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_PmePencilXY::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_PmePencilXY::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_PmePencilXY::ckGetIndex(); }

    DpcppPmePencilXY *ckLocal(void) const
    { return (DpcppPmePencilXY *)CProxyElement_PmePencilXY::ckLocal(); }

    CProxyElement_DpcppPmePencilXY(const CkArrayID &aid,const CkArrayIndex3D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilXY(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilXY(const CkArrayID &aid,const CkArrayIndex3D &idx)
        :CProxyElement_PmePencilXY(aid,idx)
    {
}

    CProxyElement_DpcppPmePencilXY(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilXY(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilXY(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_PmePencilXY(aid,idx)
    {
}
/* DECLS: DpcppPmePencilXY();
 */
    
    void insert(int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilXY(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxyElement_DpcppPmePencilXY)
/* ---------------- collective proxy -------------- */
 class CProxy_DpcppPmePencilXY : public CProxy_PmePencilXY{
  public:
    typedef DpcppPmePencilXY local_t;
    typedef CkIndex_DpcppPmePencilXY index_t;
    typedef CProxy_DpcppPmePencilXY proxy_t;
    typedef CProxyElement_DpcppPmePencilXY element_t;
    typedef CProxySection_DpcppPmePencilXY section_t;

    using array_index_t = CkArrayIndex3D;
    CProxy_DpcppPmePencilXY(void) {
    }
    CProxy_DpcppPmePencilXY(const ArrayElement *e) : CProxy_PmePencilXY(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_PmePencilXY::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_PmePencilXY::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_PmePencilXY::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxy_PmePencilXY::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_PmePencilXY::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_PmePencilXY::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_PmePencilXY::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_PmePencilXY::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_PmePencilXY::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_PmePencilXY::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_PmePencilXY::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxy_PmePencilXY::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxy_PmePencilXY::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_PmePencilXY::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_PmePencilXY::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_PmePencilXY::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_PmePencilXY::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilXY::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilXY::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_PmePencilXY::ckSetReductionClient(cb); }

    // Generalized array indexing:
    CProxyElement_DpcppPmePencilXY operator [] (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilXY(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilXY operator() (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilXY(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilXY operator () (int i0,int i1,int i2) const 
        {return CProxyElement_DpcppPmePencilXY(ckGetArrayID(), CkArrayIndex3D(i0,i1,i2), CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilXY operator () (CkIndex3D idx) const 
        {return CProxyElement_DpcppPmePencilXY(ckGetArrayID(), CkArrayIndex3D(idx), CK_DELCTOR_CALL);}
    CProxy_DpcppPmePencilXY(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_PmePencilXY(aid,CK_DELCTOR_ARGS) {}
    CProxy_DpcppPmePencilXY(const CkArrayID &aid) 
        :CProxy_PmePencilXY(aid) {}
/* DECLS: DpcppPmePencilXY();
 */
    
    static CkArrayID ckNew(const CkArrayOptions &opts = CkArrayOptions(), const CkEntryOptions *impl_e_opts=NULL);
    static void      ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(const int s1, const int s2, const int s3, const CkEntryOptions *impl_e_opts=NULL);
    static void ckNew(const int s1, const int s2, const int s3, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilXY(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxy_DpcppPmePencilXY)
/* ---------------- section proxy -------------- */
 class CProxySection_DpcppPmePencilXY : public CProxySection_PmePencilXY{
  public:
    typedef DpcppPmePencilXY local_t;
    typedef CkIndex_DpcppPmePencilXY index_t;
    typedef CProxy_DpcppPmePencilXY proxy_t;
    typedef CProxyElement_DpcppPmePencilXY element_t;
    typedef CProxySection_DpcppPmePencilXY section_t;

    using array_index_t = CkArrayIndex3D;
    CProxySection_DpcppPmePencilXY(void) {
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_PmePencilXY::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_PmePencilXY::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_PmePencilXY::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxySection_PmePencilXY::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_PmePencilXY::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_PmePencilXY::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_PmePencilXY::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_PmePencilXY::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_PmePencilXY::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_PmePencilXY::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_PmePencilXY::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxySection_PmePencilXY::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxySection_PmePencilXY::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_PmePencilXY::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_PmePencilXY::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_PmePencilXY::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_PmePencilXY::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilXY::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilXY::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_PmePencilXY::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_PmePencilXY::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_PmePencilXY::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_PmePencilXY::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_PmePencilXY::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_PmePencilXY::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_PmePencilXY::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_PmePencilXY::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_PmePencilXY::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_PmePencilXY::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_PmePencilXY::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_DpcppPmePencilXY operator [] (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilXY(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilXY operator() (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilXY(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilXY operator () (int idx) const 
        {return CProxyElement_DpcppPmePencilXY(ckGetArrayID(), *(CkArrayIndex3D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex3D *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex3D> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l1, int u1, int s1, int l2, int u2, int s2, int l3, int u3, int s3, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      std::vector<CkArrayIndex3D> al;
      for (int i=l1; i<=u1; i+=s1) 
        for (int j=l2; j<=u2; j+=s2) 
          for (int k=l3; k<=u3; k+=s3) 
          al.emplace_back(i, j, k);
      return CkSectionID(aid, al, factor);
    } 
    CProxySection_DpcppPmePencilXY(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXY(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXY(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXY(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXY(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilXY(aid,elems,nElems, factor) {}
    CProxySection_DpcppPmePencilXY(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilXY(aid,elems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXY(const CkSectionID &sid)  
        :CProxySection_PmePencilXY(sid) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXY(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXY(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXY(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilXY(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilXY(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_PmePencilXY(n,aid,elems,nElems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXY(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems) 
        :CProxySection_PmePencilXY(aid,elems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXY(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, int factor) 
        :CProxySection_PmePencilXY(n,aid,elems,nElems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilXY(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, int factor) 
        :CProxySection_PmePencilXY(aid,elems, factor) { ckAutoDelegate(); }
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems) {
       return CkSectionID(aid, elems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor) {
      return CkSectionID(aid, elems, factor);
    } 
    void ckAutoDelegate(int opts=1) {
      if(ckIsDelegated()) return;
      CProxySection_PmePencilXY::ckAutoDelegate(opts);
    } 
    void setReductionClient(CkCallback *cb) {
      CProxySection_PmePencilXY::setReductionClient(cb);
    } 
    void resetSection() {
      CProxySection_PmePencilXY::resetSection();
    } 
    static void contribute(CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
/* DECLS: DpcppPmePencilXY();
 */
    

/* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBufferZ(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilXY(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxySection_DpcppPmePencilXY)
#define DpcppPmePencilXY_SDAG_CODE                                             \
public:                                                                        \
  void getDeviceBuffer(int x, bool sameDevice, CProxy_DpcppPmePencilZ proxy);  \
  void getDeviceBuffer(Closure_DpcppPmePencilXY::getDeviceBuffer_5_closure* gen0);\
private:                                                                       \
  void getDeviceBuffer_end(Closure_DpcppPmePencilXY::getDeviceBuffer_5_closure* gen0);\
  void _slist_0(Closure_DpcppPmePencilXY::getDeviceBuffer_5_closure* gen0);    \
  void _slist_0_end(Closure_DpcppPmePencilXY::getDeviceBuffer_5_closure* gen0);\
  void _serial_0(Closure_DpcppPmePencilXY::getDeviceBuffer_5_closure* gen0);   \
public:                                                                        \
  void recvDeviceBuffers(const CkCallback & cb);                               \
  void _sdag_fnc_recvDeviceBuffers(const CkCallback & cb);                     \
  void _sdag_fnc_recvDeviceBuffers(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0);\
private:                                                                       \
  void recvDeviceBuffers_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0);\
  void _slist_1(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0);  \
  void _slist_1_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0);\
  void _overlap_0(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0);\
  void _overlap_0_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0);\
  void _olist_0(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0);  \
  void _olist_0_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_2(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_2_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_0(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _when_0_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _serial_1(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _for_1(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _for_1_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_1(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _when_1_end(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilXY::getDeviceBufferZ_4_closure* gen2);\
  void _serial_2(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilXY::getDeviceBufferZ_4_closure* gen2);\
  void _serial_3(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0); \
  void _serial_4(Closure_DpcppPmePencilXY::recvDeviceBuffers_7_closure* gen0); \
public:                                                                        \
  void recvDeviceBuffer(DeviceDataMsg* msg_msg);                               \
  void getDeviceBufferZ(Closure_DpcppPmePencilXY::getDeviceBufferZ_4_closure* genClosure);\
  void getDeviceBufferZ(int x, bool sameDevice, CProxy_DpcppPmePencilZ proxy); \
public:                                                                        \
  SDAG::dep_ptr __dep;                                                         \
  void _sdag_init();                                                           \
  void __sdag_init();                                                          \
public:                                                                        \
  void _sdag_pup(PUP::er &p);                                                  \
  void __sdag_pup(PUP::er &p) { }                                              \
  static void __sdag_register();                                               \
  static int _sdag_idx_DpcppPmePencilXY_serial_0();                            \
  static int _sdag_reg_DpcppPmePencilXY_serial_0();                            \
  static int _sdag_idx_DpcppPmePencilXY_serial_1();                            \
  static int _sdag_reg_DpcppPmePencilXY_serial_1();                            \
  static int _sdag_idx_DpcppPmePencilXY_serial_2();                            \
  static int _sdag_reg_DpcppPmePencilXY_serial_2();                            \
  static int _sdag_idx_DpcppPmePencilXY_serial_3();                            \
  static int _sdag_reg_DpcppPmePencilXY_serial_3();                            \
  static int _sdag_idx_DpcppPmePencilXY_serial_4();                            \
  static int _sdag_reg_DpcppPmePencilXY_serial_4();                            \

typedef CBaseT1<PmePencilXY, CProxy_DpcppPmePencilXY>CBase_DpcppPmePencilXY;

class CProxy_DpcppPmePencilY;

/* DECLS: array DpcppPmePencilX: PmePencilX{
DpcppPmePencilX();
void initialize(DpcppPmeXInitMsg* impl_msg);
void initializeDevice(InitDeviceMsg* impl_msg);
void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
void recvDeviceBuffer(DeviceDataMsg* impl_msg);
void recvDeviceBuffers(const CkCallback &cb);
DpcppPmePencilX(CkMigrateMessage* impl_msg);
};
 */
 class DpcppPmePencilX;
 class CkIndex_DpcppPmePencilX;
 class CProxy_DpcppPmePencilX;
 class CProxyElement_DpcppPmePencilX;
 class CProxySection_DpcppPmePencilX;
/* --------------- index object ------------------ */
class CkIndex_DpcppPmePencilX:public CkIndex_PmePencilX{
  public:
    typedef DpcppPmePencilX local_t;
    typedef CkIndex_DpcppPmePencilX index_t;
    typedef CProxy_DpcppPmePencilX proxy_t;
    typedef CProxyElement_DpcppPmePencilX element_t;
    typedef CProxySection_DpcppPmePencilX section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppPmePencilX();
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilX_void();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilX_void() {
      static int epidx = reg_DpcppPmePencilX_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppPmePencilX_void(); }
    
    static void _call_DpcppPmePencilX_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilX_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_DpcppPmeXInitMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_DpcppPmeXInitMsg() {
      static int epidx = reg_initialize_DpcppPmeXInitMsg();
      return epidx;
    }

    
    inline static int idx_initialize(void (DpcppPmePencilX::*)(DpcppPmeXInitMsg* impl_msg) ) {
      return idx_initialize_DpcppPmeXInitMsg();
    }


    
    static int initialize(DpcppPmeXInitMsg* impl_msg) { return idx_initialize_DpcppPmeXInitMsg(); }
    
    static void _call_initialize_DpcppPmeXInitMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_DpcppPmeXInitMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initializeDevice_InitDeviceMsg();
    // Entry point index lookup
    
    inline static int idx_initializeDevice_InitDeviceMsg() {
      static int epidx = reg_initializeDevice_InitDeviceMsg();
      return epidx;
    }

    
    inline static int idx_initializeDevice(void (DpcppPmePencilX::*)(InitDeviceMsg* impl_msg) ) {
      return idx_initializeDevice_InitDeviceMsg();
    }


    
    static int initializeDevice(InitDeviceMsg* impl_msg) { return idx_initializeDevice_InitDeviceMsg(); }
    
    static void _call_initializeDevice_InitDeviceMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initializeDevice_InitDeviceMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer2_marshall4();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer2_marshall4() {
      static int epidx = reg_getDeviceBuffer2_marshall4();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer2(void (DpcppPmePencilX::*)(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) ) {
      return idx_getDeviceBuffer2_marshall4();
    }


    
    static int getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) { return idx_getDeviceBuffer2_marshall4(); }
    
    static void _call_getDeviceBuffer2_marshall4(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer2_marshall4(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer2_marshall4(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer2_marshall4(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer_marshall5();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer_marshall5() {
      static int epidx = reg_getDeviceBuffer_marshall5();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer(void (DpcppPmePencilX::*)(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) ) {
      return idx_getDeviceBuffer_marshall5();
    }


    
    static int getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) { return idx_getDeviceBuffer_marshall5(); }
    
    static void _call_getDeviceBuffer_marshall5(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer_marshall5(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer_marshall5(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer_marshall5(PUP::er &p,void *msg);
    /* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBuffer_DeviceDataMsg();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBuffer_DeviceDataMsg() {
      static int epidx = reg_recvDeviceBuffer_DeviceDataMsg();
      return epidx;
    }

    
    inline static int idx_recvDeviceBuffer(void (DpcppPmePencilX::*)(DeviceDataMsg* impl_msg) ) {
      return idx_recvDeviceBuffer_DeviceDataMsg();
    }


    
    static int recvDeviceBuffer(DeviceDataMsg* impl_msg) { return idx_recvDeviceBuffer_DeviceDataMsg(); }
    
    static void _call_recvDeviceBuffer_DeviceDataMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBuffer_DeviceDataMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvDeviceBuffers(const CkCallback &cb);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBuffers_marshall7();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBuffers_marshall7() {
      static int epidx = reg_recvDeviceBuffers_marshall7();
      return epidx;
    }

    
    inline static int idx_recvDeviceBuffers(void (DpcppPmePencilX::*)(const CkCallback &cb) ) {
      return idx_recvDeviceBuffers_marshall7();
    }


    
    static int recvDeviceBuffers(const CkCallback &cb) { return idx_recvDeviceBuffers_marshall7(); }
    
    static void _call_recvDeviceBuffers_marshall7(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBuffers_marshall7(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvDeviceBuffers_marshall7(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvDeviceBuffers_marshall7(PUP::er &p,void *msg);
    /* DECLS: DpcppPmePencilX(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilX_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilX_CkMigrateMessage() {
      static int epidx = reg_DpcppPmePencilX_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_DpcppPmePencilX_CkMigrateMessage(); }
    
    static void _call_DpcppPmePencilX_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilX_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_DpcppPmePencilX : public CProxyElement_PmePencilX{
  public:
    typedef DpcppPmePencilX local_t;
    typedef CkIndex_DpcppPmePencilX index_t;
    typedef CProxy_DpcppPmePencilX proxy_t;
    typedef CProxyElement_DpcppPmePencilX element_t;
    typedef CProxySection_DpcppPmePencilX section_t;

    using array_index_t = CkArrayIndex3D;

    /* TRAM aggregators */

    CProxyElement_DpcppPmePencilX(void) {
    }
    CProxyElement_DpcppPmePencilX(const ArrayElement *e) : CProxyElement_PmePencilX(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_PmePencilX::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_PmePencilX::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_PmePencilX::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxyElement_PmePencilX::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_PmePencilX::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_PmePencilX::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_PmePencilX::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_PmePencilX::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_PmePencilX::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_PmePencilX::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_PmePencilX::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxyElement_PmePencilX::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxyElement_PmePencilX::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_PmePencilX::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_PmePencilX::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_PmePencilX::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_PmePencilX::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilX::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilX::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_PmePencilX::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_PmePencilX::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_PmePencilX::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_PmePencilX::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_PmePencilX::ckGetIndex(); }

    DpcppPmePencilX *ckLocal(void) const
    { return (DpcppPmePencilX *)CProxyElement_PmePencilX::ckLocal(); }

    CProxyElement_DpcppPmePencilX(const CkArrayID &aid,const CkArrayIndex3D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilX(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilX(const CkArrayID &aid,const CkArrayIndex3D &idx)
        :CProxyElement_PmePencilX(aid,idx)
    {
}

    CProxyElement_DpcppPmePencilX(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilX(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilX(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_PmePencilX(aid,idx)
    {
}
/* DECLS: DpcppPmePencilX();
 */
    
    void insert(int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilX(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxyElement_DpcppPmePencilX)
/* ---------------- collective proxy -------------- */
 class CProxy_DpcppPmePencilX : public CProxy_PmePencilX{
  public:
    typedef DpcppPmePencilX local_t;
    typedef CkIndex_DpcppPmePencilX index_t;
    typedef CProxy_DpcppPmePencilX proxy_t;
    typedef CProxyElement_DpcppPmePencilX element_t;
    typedef CProxySection_DpcppPmePencilX section_t;

    using array_index_t = CkArrayIndex3D;
    CProxy_DpcppPmePencilX(void) {
    }
    CProxy_DpcppPmePencilX(const ArrayElement *e) : CProxy_PmePencilX(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_PmePencilX::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_PmePencilX::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_PmePencilX::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxy_PmePencilX::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_PmePencilX::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_PmePencilX::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_PmePencilX::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_PmePencilX::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_PmePencilX::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_PmePencilX::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_PmePencilX::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxy_PmePencilX::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxy_PmePencilX::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_PmePencilX::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_PmePencilX::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_PmePencilX::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_PmePencilX::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilX::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilX::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_PmePencilX::ckSetReductionClient(cb); }

    // Generalized array indexing:
    CProxyElement_DpcppPmePencilX operator [] (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilX(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilX operator() (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilX(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilX operator () (int i0,int i1,int i2) const 
        {return CProxyElement_DpcppPmePencilX(ckGetArrayID(), CkArrayIndex3D(i0,i1,i2), CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilX operator () (CkIndex3D idx) const 
        {return CProxyElement_DpcppPmePencilX(ckGetArrayID(), CkArrayIndex3D(idx), CK_DELCTOR_CALL);}
    CProxy_DpcppPmePencilX(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_PmePencilX(aid,CK_DELCTOR_ARGS) {}
    CProxy_DpcppPmePencilX(const CkArrayID &aid) 
        :CProxy_PmePencilX(aid) {}
/* DECLS: DpcppPmePencilX();
 */
    
    static CkArrayID ckNew(const CkArrayOptions &opts = CkArrayOptions(), const CkEntryOptions *impl_e_opts=NULL);
    static void      ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(const int s1, const int s2, const int s3, const CkEntryOptions *impl_e_opts=NULL);
    static void ckNew(const int s1, const int s2, const int s3, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilX(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxy_DpcppPmePencilX)
/* ---------------- section proxy -------------- */
 class CProxySection_DpcppPmePencilX : public CProxySection_PmePencilX{
  public:
    typedef DpcppPmePencilX local_t;
    typedef CkIndex_DpcppPmePencilX index_t;
    typedef CProxy_DpcppPmePencilX proxy_t;
    typedef CProxyElement_DpcppPmePencilX element_t;
    typedef CProxySection_DpcppPmePencilX section_t;

    using array_index_t = CkArrayIndex3D;
    CProxySection_DpcppPmePencilX(void) {
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_PmePencilX::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_PmePencilX::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_PmePencilX::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxySection_PmePencilX::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_PmePencilX::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_PmePencilX::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_PmePencilX::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_PmePencilX::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_PmePencilX::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_PmePencilX::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_PmePencilX::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxySection_PmePencilX::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxySection_PmePencilX::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_PmePencilX::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_PmePencilX::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_PmePencilX::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_PmePencilX::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilX::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilX::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_PmePencilX::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_PmePencilX::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_PmePencilX::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_PmePencilX::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_PmePencilX::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_PmePencilX::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_PmePencilX::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_PmePencilX::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_PmePencilX::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_PmePencilX::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_PmePencilX::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_DpcppPmePencilX operator [] (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilX(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilX operator() (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilX(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilX operator () (int idx) const 
        {return CProxyElement_DpcppPmePencilX(ckGetArrayID(), *(CkArrayIndex3D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex3D *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex3D> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l1, int u1, int s1, int l2, int u2, int s2, int l3, int u3, int s3, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      std::vector<CkArrayIndex3D> al;
      for (int i=l1; i<=u1; i+=s1) 
        for (int j=l2; j<=u2; j+=s2) 
          for (int k=l3; k<=u3; k+=s3) 
          al.emplace_back(i, j, k);
      return CkSectionID(aid, al, factor);
    } 
    CProxySection_DpcppPmePencilX(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilX(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilX(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilX(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilX(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilX(aid,elems,nElems, factor) {}
    CProxySection_DpcppPmePencilX(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilX(aid,elems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilX(const CkSectionID &sid)  
        :CProxySection_PmePencilX(sid) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilX(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilX(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilX(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilX(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilX(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_PmePencilX(n,aid,elems,nElems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilX(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems) 
        :CProxySection_PmePencilX(aid,elems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilX(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, int factor) 
        :CProxySection_PmePencilX(n,aid,elems,nElems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilX(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, int factor) 
        :CProxySection_PmePencilX(aid,elems, factor) { ckAutoDelegate(); }
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems) {
       return CkSectionID(aid, elems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor) {
      return CkSectionID(aid, elems, factor);
    } 
    void ckAutoDelegate(int opts=1) {
      if(ckIsDelegated()) return;
      CProxySection_PmePencilX::ckAutoDelegate(opts);
    } 
    void setReductionClient(CkCallback *cb) {
      CProxySection_PmePencilX::setReductionClient(cb);
    } 
    void resetSection() {
      CProxySection_PmePencilX::resetSection();
    } 
    static void contribute(CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
/* DECLS: DpcppPmePencilX();
 */
    

/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg* impl_msg) ;

/* DECLS: void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer2(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer(int x, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilX(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxySection_DpcppPmePencilX)
#define DpcppPmePencilX_SDAG_CODE                                              \
public:                                                                        \
  void getDeviceBuffer(int x, bool sameDevice, CProxy_DpcppPmePencilY proxy);  \
  void getDeviceBuffer(Closure_DpcppPmePencilX::getDeviceBuffer_5_closure* gen0);\
private:                                                                       \
  void getDeviceBuffer_end(Closure_DpcppPmePencilX::getDeviceBuffer_5_closure* gen0);\
  void _slist_0(Closure_DpcppPmePencilX::getDeviceBuffer_5_closure* gen0);     \
  void _slist_0_end(Closure_DpcppPmePencilX::getDeviceBuffer_5_closure* gen0); \
  void _serial_0(Closure_DpcppPmePencilX::getDeviceBuffer_5_closure* gen0);    \
public:                                                                        \
  void recvDeviceBuffers(const CkCallback & cb);                               \
  void _sdag_fnc_recvDeviceBuffers(const CkCallback & cb);                     \
  void _sdag_fnc_recvDeviceBuffers(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);\
private:                                                                       \
  void recvDeviceBuffers_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);\
  void _slist_1(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);   \
  void _slist_1_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);\
  void _overlap_0(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0); \
  void _overlap_0_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);\
  void _olist_0(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);   \
  void _olist_0_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_2(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_2_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_0(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _when_0_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _serial_1(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _for_1(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _for_1_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_1(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0);\
  void _when_1_end(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilX::getDeviceBuffer2_4_closure* gen2);\
  void _serial_2(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilX::getDeviceBuffer2_4_closure* gen2);\
  void _serial_3(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);  \
  void _serial_4(Closure_DpcppPmePencilX::recvDeviceBuffers_7_closure* gen0);  \
public:                                                                        \
  void recvDeviceBuffer(DeviceDataMsg* msg_msg);                               \
  void getDeviceBuffer2(Closure_DpcppPmePencilX::getDeviceBuffer2_4_closure* genClosure);\
  void getDeviceBuffer2(int x, bool sameDevice, CProxy_DpcppPmePencilY proxy); \
public:                                                                        \
  SDAG::dep_ptr __dep;                                                         \
  void _sdag_init();                                                           \
  void __sdag_init();                                                          \
public:                                                                        \
  void _sdag_pup(PUP::er &p);                                                  \
  void __sdag_pup(PUP::er &p) { }                                              \
  static void __sdag_register();                                               \
  static int _sdag_idx_DpcppPmePencilX_serial_0();                             \
  static int _sdag_reg_DpcppPmePencilX_serial_0();                             \
  static int _sdag_idx_DpcppPmePencilX_serial_1();                             \
  static int _sdag_reg_DpcppPmePencilX_serial_1();                             \
  static int _sdag_idx_DpcppPmePencilX_serial_2();                             \
  static int _sdag_reg_DpcppPmePencilX_serial_2();                             \
  static int _sdag_idx_DpcppPmePencilX_serial_3();                             \
  static int _sdag_reg_DpcppPmePencilX_serial_3();                             \
  static int _sdag_idx_DpcppPmePencilX_serial_4();                             \
  static int _sdag_reg_DpcppPmePencilX_serial_4();                             \

typedef CBaseT1<PmePencilX, CProxy_DpcppPmePencilX>CBase_DpcppPmePencilX;

/* DECLS: array DpcppPmePencilY: PmePencilY{
DpcppPmePencilY();
void initialize(DpcppPmeXInitMsg* impl_msg);
void initializeDevice(InitDeviceMsg2* impl_msg);
void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
void recvDeviceBufferZ(DeviceDataMsg* impl_msg);
void recvDeviceBufferX(DeviceDataMsg* impl_msg);
void recvDeviceBuffers(const CkCallback &cb);
DpcppPmePencilY(CkMigrateMessage* impl_msg);
};
 */
 class DpcppPmePencilY;
 class CkIndex_DpcppPmePencilY;
 class CProxy_DpcppPmePencilY;
 class CProxyElement_DpcppPmePencilY;
 class CProxySection_DpcppPmePencilY;
/* --------------- index object ------------------ */
class CkIndex_DpcppPmePencilY:public CkIndex_PmePencilY{
  public:
    typedef DpcppPmePencilY local_t;
    typedef CkIndex_DpcppPmePencilY index_t;
    typedef CProxy_DpcppPmePencilY proxy_t;
    typedef CProxyElement_DpcppPmePencilY element_t;
    typedef CProxySection_DpcppPmePencilY section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppPmePencilY();
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilY_void();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilY_void() {
      static int epidx = reg_DpcppPmePencilY_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppPmePencilY_void(); }
    
    static void _call_DpcppPmePencilY_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilY_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_DpcppPmeXInitMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_DpcppPmeXInitMsg() {
      static int epidx = reg_initialize_DpcppPmeXInitMsg();
      return epidx;
    }

    
    inline static int idx_initialize(void (DpcppPmePencilY::*)(DpcppPmeXInitMsg* impl_msg) ) {
      return idx_initialize_DpcppPmeXInitMsg();
    }


    
    static int initialize(DpcppPmeXInitMsg* impl_msg) { return idx_initialize_DpcppPmeXInitMsg(); }
    
    static void _call_initialize_DpcppPmeXInitMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_DpcppPmeXInitMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initializeDevice_InitDeviceMsg2();
    // Entry point index lookup
    
    inline static int idx_initializeDevice_InitDeviceMsg2() {
      static int epidx = reg_initializeDevice_InitDeviceMsg2();
      return epidx;
    }

    
    inline static int idx_initializeDevice(void (DpcppPmePencilY::*)(InitDeviceMsg2* impl_msg) ) {
      return idx_initializeDevice_InitDeviceMsg2();
    }


    
    static int initializeDevice(InitDeviceMsg2* impl_msg) { return idx_initializeDevice_InitDeviceMsg2(); }
    
    static void _call_initializeDevice_InitDeviceMsg2(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initializeDevice_InitDeviceMsg2(void* impl_msg, void* impl_obj);
    /* DECLS: void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer2_marshall4();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer2_marshall4() {
      static int epidx = reg_getDeviceBuffer2_marshall4();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer2(void (DpcppPmePencilY::*)(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy) ) {
      return idx_getDeviceBuffer2_marshall4();
    }


    
    static int getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy) { return idx_getDeviceBuffer2_marshall4(); }
    
    static void _call_getDeviceBuffer2_marshall4(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer2_marshall4(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer2_marshall4(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer2_marshall4(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer_marshall5();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer_marshall5() {
      static int epidx = reg_getDeviceBuffer_marshall5();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer(void (DpcppPmePencilY::*)(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy) ) {
      return idx_getDeviceBuffer_marshall5();
    }


    
    static int getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy) { return idx_getDeviceBuffer_marshall5(); }
    
    static void _call_getDeviceBuffer_marshall5(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer_marshall5(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer_marshall5(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer_marshall5(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer22_marshall6();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer22_marshall6() {
      static int epidx = reg_getDeviceBuffer22_marshall6();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer22(void (DpcppPmePencilY::*)(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) ) {
      return idx_getDeviceBuffer22_marshall6();
    }


    
    static int getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) { return idx_getDeviceBuffer22_marshall6(); }
    
    static void _call_getDeviceBuffer22_marshall6(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer22_marshall6(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer22_marshall6(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer22_marshall6(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer_marshall7();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer_marshall7() {
      static int epidx = reg_getDeviceBuffer_marshall7();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer(void (DpcppPmePencilY::*)(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) ) {
      return idx_getDeviceBuffer_marshall7();
    }


    
    static int getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy) { return idx_getDeviceBuffer_marshall7(); }
    
    static void _call_getDeviceBuffer_marshall7(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer_marshall7(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer_marshall7(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer_marshall7(PUP::er &p,void *msg);
    /* DECLS: void recvDeviceBufferZ(DeviceDataMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBufferZ_DeviceDataMsg();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBufferZ_DeviceDataMsg() {
      static int epidx = reg_recvDeviceBufferZ_DeviceDataMsg();
      return epidx;
    }

    
    inline static int idx_recvDeviceBufferZ(void (DpcppPmePencilY::*)(DeviceDataMsg* impl_msg) ) {
      return idx_recvDeviceBufferZ_DeviceDataMsg();
    }


    
    static int recvDeviceBufferZ(DeviceDataMsg* impl_msg) { return idx_recvDeviceBufferZ_DeviceDataMsg(); }
    
    static void _call_recvDeviceBufferZ_DeviceDataMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBufferZ_DeviceDataMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvDeviceBufferX(DeviceDataMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBufferX_DeviceDataMsg();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBufferX_DeviceDataMsg() {
      static int epidx = reg_recvDeviceBufferX_DeviceDataMsg();
      return epidx;
    }

    
    inline static int idx_recvDeviceBufferX(void (DpcppPmePencilY::*)(DeviceDataMsg* impl_msg) ) {
      return idx_recvDeviceBufferX_DeviceDataMsg();
    }


    
    static int recvDeviceBufferX(DeviceDataMsg* impl_msg) { return idx_recvDeviceBufferX_DeviceDataMsg(); }
    
    static void _call_recvDeviceBufferX_DeviceDataMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBufferX_DeviceDataMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvDeviceBuffers(const CkCallback &cb);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBuffers_marshall10();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBuffers_marshall10() {
      static int epidx = reg_recvDeviceBuffers_marshall10();
      return epidx;
    }

    
    inline static int idx_recvDeviceBuffers(void (DpcppPmePencilY::*)(const CkCallback &cb) ) {
      return idx_recvDeviceBuffers_marshall10();
    }


    
    static int recvDeviceBuffers(const CkCallback &cb) { return idx_recvDeviceBuffers_marshall10(); }
    
    static void _call_recvDeviceBuffers_marshall10(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBuffers_marshall10(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvDeviceBuffers_marshall10(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvDeviceBuffers_marshall10(PUP::er &p,void *msg);
    /* DECLS: DpcppPmePencilY(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilY_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilY_CkMigrateMessage() {
      static int epidx = reg_DpcppPmePencilY_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_DpcppPmePencilY_CkMigrateMessage(); }
    
    static void _call_DpcppPmePencilY_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilY_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_DpcppPmePencilY : public CProxyElement_PmePencilY{
  public:
    typedef DpcppPmePencilY local_t;
    typedef CkIndex_DpcppPmePencilY index_t;
    typedef CProxy_DpcppPmePencilY proxy_t;
    typedef CProxyElement_DpcppPmePencilY element_t;
    typedef CProxySection_DpcppPmePencilY section_t;

    using array_index_t = CkArrayIndex3D;

    /* TRAM aggregators */

    CProxyElement_DpcppPmePencilY(void) {
    }
    CProxyElement_DpcppPmePencilY(const ArrayElement *e) : CProxyElement_PmePencilY(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_PmePencilY::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_PmePencilY::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_PmePencilY::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxyElement_PmePencilY::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_PmePencilY::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_PmePencilY::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_PmePencilY::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_PmePencilY::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_PmePencilY::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_PmePencilY::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_PmePencilY::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxyElement_PmePencilY::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxyElement_PmePencilY::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_PmePencilY::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_PmePencilY::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_PmePencilY::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_PmePencilY::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilY::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilY::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_PmePencilY::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_PmePencilY::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_PmePencilY::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_PmePencilY::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_PmePencilY::ckGetIndex(); }

    DpcppPmePencilY *ckLocal(void) const
    { return (DpcppPmePencilY *)CProxyElement_PmePencilY::ckLocal(); }

    CProxyElement_DpcppPmePencilY(const CkArrayID &aid,const CkArrayIndex3D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilY(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilY(const CkArrayID &aid,const CkArrayIndex3D &idx)
        :CProxyElement_PmePencilY(aid,idx)
    {
}

    CProxyElement_DpcppPmePencilY(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilY(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilY(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_PmePencilY(aid,idx)
    {
}
/* DECLS: DpcppPmePencilY();
 */
    
    void insert(int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg2* impl_msg) ;

/* DECLS: void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
 */
    
    void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
 */
    
    void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBufferZ(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBufferZ(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBufferX(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBufferX(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilY(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxyElement_DpcppPmePencilY)
/* ---------------- collective proxy -------------- */
 class CProxy_DpcppPmePencilY : public CProxy_PmePencilY{
  public:
    typedef DpcppPmePencilY local_t;
    typedef CkIndex_DpcppPmePencilY index_t;
    typedef CProxy_DpcppPmePencilY proxy_t;
    typedef CProxyElement_DpcppPmePencilY element_t;
    typedef CProxySection_DpcppPmePencilY section_t;

    using array_index_t = CkArrayIndex3D;
    CProxy_DpcppPmePencilY(void) {
    }
    CProxy_DpcppPmePencilY(const ArrayElement *e) : CProxy_PmePencilY(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_PmePencilY::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_PmePencilY::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_PmePencilY::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxy_PmePencilY::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_PmePencilY::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_PmePencilY::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_PmePencilY::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_PmePencilY::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_PmePencilY::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_PmePencilY::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_PmePencilY::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxy_PmePencilY::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxy_PmePencilY::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_PmePencilY::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_PmePencilY::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_PmePencilY::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_PmePencilY::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilY::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilY::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_PmePencilY::ckSetReductionClient(cb); }

    // Generalized array indexing:
    CProxyElement_DpcppPmePencilY operator [] (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilY(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilY operator() (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilY(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilY operator () (int i0,int i1,int i2) const 
        {return CProxyElement_DpcppPmePencilY(ckGetArrayID(), CkArrayIndex3D(i0,i1,i2), CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilY operator () (CkIndex3D idx) const 
        {return CProxyElement_DpcppPmePencilY(ckGetArrayID(), CkArrayIndex3D(idx), CK_DELCTOR_CALL);}
    CProxy_DpcppPmePencilY(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_PmePencilY(aid,CK_DELCTOR_ARGS) {}
    CProxy_DpcppPmePencilY(const CkArrayID &aid) 
        :CProxy_PmePencilY(aid) {}
/* DECLS: DpcppPmePencilY();
 */
    
    static CkArrayID ckNew(const CkArrayOptions &opts = CkArrayOptions(), const CkEntryOptions *impl_e_opts=NULL);
    static void      ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(const int s1, const int s2, const int s3, const CkEntryOptions *impl_e_opts=NULL);
    static void ckNew(const int s1, const int s2, const int s3, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg2* impl_msg) ;

/* DECLS: void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
 */
    
    void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
 */
    
    void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBufferZ(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBufferZ(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBufferX(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBufferX(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilY(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxy_DpcppPmePencilY)
/* ---------------- section proxy -------------- */
 class CProxySection_DpcppPmePencilY : public CProxySection_PmePencilY{
  public:
    typedef DpcppPmePencilY local_t;
    typedef CkIndex_DpcppPmePencilY index_t;
    typedef CProxy_DpcppPmePencilY proxy_t;
    typedef CProxyElement_DpcppPmePencilY element_t;
    typedef CProxySection_DpcppPmePencilY section_t;

    using array_index_t = CkArrayIndex3D;
    CProxySection_DpcppPmePencilY(void) {
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_PmePencilY::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_PmePencilY::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_PmePencilY::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxySection_PmePencilY::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_PmePencilY::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_PmePencilY::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_PmePencilY::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_PmePencilY::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_PmePencilY::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_PmePencilY::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_PmePencilY::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxySection_PmePencilY::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxySection_PmePencilY::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_PmePencilY::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_PmePencilY::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_PmePencilY::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_PmePencilY::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilY::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilY::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_PmePencilY::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_PmePencilY::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_PmePencilY::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_PmePencilY::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_PmePencilY::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_PmePencilY::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_PmePencilY::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_PmePencilY::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_PmePencilY::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_PmePencilY::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_PmePencilY::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_DpcppPmePencilY operator [] (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilY(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilY operator() (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilY(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilY operator () (int idx) const 
        {return CProxyElement_DpcppPmePencilY(ckGetArrayID(), *(CkArrayIndex3D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex3D *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex3D> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l1, int u1, int s1, int l2, int u2, int s2, int l3, int u3, int s3, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      std::vector<CkArrayIndex3D> al;
      for (int i=l1; i<=u1; i+=s1) 
        for (int j=l2; j<=u2; j+=s2) 
          for (int k=l3; k<=u3; k+=s3) 
          al.emplace_back(i, j, k);
      return CkSectionID(aid, al, factor);
    } 
    CProxySection_DpcppPmePencilY(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilY(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilY(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilY(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilY(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilY(aid,elems,nElems, factor) {}
    CProxySection_DpcppPmePencilY(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilY(aid,elems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilY(const CkSectionID &sid)  
        :CProxySection_PmePencilY(sid) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilY(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilY(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilY(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilY(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilY(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_PmePencilY(n,aid,elems,nElems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilY(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems) 
        :CProxySection_PmePencilY(aid,elems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilY(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, int factor) 
        :CProxySection_PmePencilY(n,aid,elems,nElems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilY(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, int factor) 
        :CProxySection_PmePencilY(aid,elems, factor) { ckAutoDelegate(); }
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems) {
       return CkSectionID(aid, elems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor) {
      return CkSectionID(aid, elems, factor);
    } 
    void ckAutoDelegate(int opts=1) {
      if(ckIsDelegated()) return;
      CProxySection_PmePencilY::ckAutoDelegate(opts);
    } 
    void setReductionClient(CkCallback *cb) {
      CProxySection_PmePencilY::setReductionClient(cb);
    } 
    void resetSection() {
      CProxySection_PmePencilY::resetSection();
    } 
    static void contribute(CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
/* DECLS: DpcppPmePencilY();
 */
    

/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg2* impl_msg) ;

/* DECLS: void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
 */
    
    void getDeviceBuffer2(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy);
 */
    
    void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilX &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer22(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy);
 */
    
    void getDeviceBuffer(int y, const bool &sameDevice, const CProxy_DpcppPmePencilZ &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBufferZ(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBufferZ(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBufferX(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBufferX(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilY(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxySection_DpcppPmePencilY)
#define DpcppPmePencilY_SDAG_CODE                                              \
public:                                                                        \
  void getDeviceBuffer(int y, bool sameDevice, CProxy_DpcppPmePencilX proxy);  \
  void getDeviceBuffer(Closure_DpcppPmePencilY::getDeviceBuffer_5_closure* gen0);\
private:                                                                       \
  void getDeviceBuffer_end(Closure_DpcppPmePencilY::getDeviceBuffer_5_closure* gen0);\
  void _slist_0(Closure_DpcppPmePencilY::getDeviceBuffer_5_closure* gen0);     \
  void _slist_0_end(Closure_DpcppPmePencilY::getDeviceBuffer_5_closure* gen0); \
  void _serial_0(Closure_DpcppPmePencilY::getDeviceBuffer_5_closure* gen0);    \
public:                                                                        \
  void getDeviceBuffer(int y, bool sameDevice, CProxy_DpcppPmePencilZ proxy);  \
  void getDeviceBuffer(Closure_DpcppPmePencilY::getDeviceBuffer_7_closure* gen0);\
private:                                                                       \
  void getDeviceBuffer_end(Closure_DpcppPmePencilY::getDeviceBuffer_7_closure* gen0);\
  void _slist_1(Closure_DpcppPmePencilY::getDeviceBuffer_7_closure* gen0);     \
  void _slist_1_end(Closure_DpcppPmePencilY::getDeviceBuffer_7_closure* gen0); \
  void _serial_1(Closure_DpcppPmePencilY::getDeviceBuffer_7_closure* gen0);    \
public:                                                                        \
  void recvDeviceBuffers(const CkCallback & cb);                               \
  void _sdag_fnc_recvDeviceBuffers(const CkCallback & cb);                     \
  void _sdag_fnc_recvDeviceBuffers(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0);\
private:                                                                       \
  void recvDeviceBuffers_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0);\
  void _slist_2(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0);  \
  void _slist_2_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0);\
  void _overlap_0(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0);\
  void _overlap_0_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0);\
  void _olist_0(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0);  \
  void _olist_0_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_0(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _when_0_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _serial_2(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _for_1(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_1_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_4(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_4_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_1(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _when_1_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _serial_3(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _for_2(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_2_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_5(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_5_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_2(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _when_2_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilY::getDeviceBuffer2_4_closure* gen2);\
  void _serial_4(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilY::getDeviceBuffer2_4_closure* gen2);\
  void _for_3(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_3_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_6(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_6_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_3(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _when_3_end(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilY::getDeviceBuffer22_6_closure* gen2);\
  void _serial_5(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilY::getDeviceBuffer22_6_closure* gen2);\
  void _serial_6(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0); \
  void _serial_7(Closure_DpcppPmePencilY::recvDeviceBuffers_10_closure* gen0); \
public:                                                                        \
  void recvDeviceBufferZ(DeviceDataMsg* msg_msg);                              \
  void recvDeviceBufferX(DeviceDataMsg* msg_msg);                              \
  void getDeviceBuffer2(Closure_DpcppPmePencilY::getDeviceBuffer2_4_closure* genClosure);\
  void getDeviceBuffer2(int y, bool sameDevice, CProxy_DpcppPmePencilX proxy); \
  void getDeviceBuffer22(Closure_DpcppPmePencilY::getDeviceBuffer22_6_closure* genClosure);\
  void getDeviceBuffer22(int y, bool sameDevice, CProxy_DpcppPmePencilZ proxy);\
public:                                                                        \
  SDAG::dep_ptr __dep;                                                         \
  void _sdag_init();                                                           \
  void __sdag_init();                                                          \
public:                                                                        \
  void _sdag_pup(PUP::er &p);                                                  \
  void __sdag_pup(PUP::er &p) { }                                              \
  static void __sdag_register();                                               \
  static int _sdag_idx_DpcppPmePencilY_serial_0();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_0();                             \
  static int _sdag_idx_DpcppPmePencilY_serial_1();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_1();                             \
  static int _sdag_idx_DpcppPmePencilY_serial_2();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_2();                             \
  static int _sdag_idx_DpcppPmePencilY_serial_3();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_3();                             \
  static int _sdag_idx_DpcppPmePencilY_serial_4();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_4();                             \
  static int _sdag_idx_DpcppPmePencilY_serial_5();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_5();                             \
  static int _sdag_idx_DpcppPmePencilY_serial_6();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_6();                             \
  static int _sdag_idx_DpcppPmePencilY_serial_7();                             \
  static int _sdag_reg_DpcppPmePencilY_serial_7();                             \

typedef CBaseT1<PmePencilY, CProxy_DpcppPmePencilY>CBase_DpcppPmePencilY;

/* DECLS: array DpcppPmePencilZ: PmePencilZ{
DpcppPmePencilZ();
void initialize(DpcppPmeXInitMsg* impl_msg);
void initialize(DpcppPmeXYInitMsg* impl_msg);
void initializeDevice(InitDeviceMsg2* impl_msg);
void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
void recvDeviceBuffer(DeviceDataMsg* impl_msg);
void recvDeviceBuffers(const CkCallback &cb);
DpcppPmePencilZ(CkMigrateMessage* impl_msg);
};
 */
 class DpcppPmePencilZ;
 class CkIndex_DpcppPmePencilZ;
 class CProxy_DpcppPmePencilZ;
 class CProxyElement_DpcppPmePencilZ;
 class CProxySection_DpcppPmePencilZ;
/* --------------- index object ------------------ */
class CkIndex_DpcppPmePencilZ:public CkIndex_PmePencilZ{
  public:
    typedef DpcppPmePencilZ local_t;
    typedef CkIndex_DpcppPmePencilZ index_t;
    typedef CProxy_DpcppPmePencilZ proxy_t;
    typedef CProxyElement_DpcppPmePencilZ element_t;
    typedef CProxySection_DpcppPmePencilZ section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: DpcppPmePencilZ();
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilZ_void();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilZ_void() {
      static int epidx = reg_DpcppPmePencilZ_void();
      return epidx;
    }

    
    static int ckNew() { return idx_DpcppPmePencilZ_void(); }
    
    static void _call_DpcppPmePencilZ_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilZ_void(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_DpcppPmeXInitMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_DpcppPmeXInitMsg() {
      static int epidx = reg_initialize_DpcppPmeXInitMsg();
      return epidx;
    }

    
    inline static int idx_initialize(void (DpcppPmePencilZ::*)(DpcppPmeXInitMsg* impl_msg) ) {
      return idx_initialize_DpcppPmeXInitMsg();
    }


    
    static int initialize(DpcppPmeXInitMsg* impl_msg) { return idx_initialize_DpcppPmeXInitMsg(); }
    
    static void _call_initialize_DpcppPmeXInitMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_DpcppPmeXInitMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initialize_DpcppPmeXYInitMsg();
    // Entry point index lookup
    
    inline static int idx_initialize_DpcppPmeXYInitMsg() {
      static int epidx = reg_initialize_DpcppPmeXYInitMsg();
      return epidx;
    }

    
    inline static int idx_initialize(void (DpcppPmePencilZ::*)(DpcppPmeXYInitMsg* impl_msg) ) {
      return idx_initialize_DpcppPmeXYInitMsg();
    }


    
    static int initialize(DpcppPmeXYInitMsg* impl_msg) { return idx_initialize_DpcppPmeXYInitMsg(); }
    
    static void _call_initialize_DpcppPmeXYInitMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initialize_DpcppPmeXYInitMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_initializeDevice_InitDeviceMsg2();
    // Entry point index lookup
    
    inline static int idx_initializeDevice_InitDeviceMsg2() {
      static int epidx = reg_initializeDevice_InitDeviceMsg2();
      return epidx;
    }

    
    inline static int idx_initializeDevice(void (DpcppPmePencilZ::*)(InitDeviceMsg2* impl_msg) ) {
      return idx_initializeDevice_InitDeviceMsg2();
    }


    
    static int initializeDevice(InitDeviceMsg2* impl_msg) { return idx_initializeDevice_InitDeviceMsg2(); }
    
    static void _call_initializeDevice_InitDeviceMsg2(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_initializeDevice_InitDeviceMsg2(void* impl_msg, void* impl_obj);
    /* DECLS: void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBufferXY_marshall5();
    // Entry point index lookup
    
    inline static int idx_getDeviceBufferXY_marshall5() {
      static int epidx = reg_getDeviceBufferXY_marshall5();
      return epidx;
    }

    
    inline static int idx_getDeviceBufferXY(void (DpcppPmePencilZ::*)(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy) ) {
      return idx_getDeviceBufferXY_marshall5();
    }


    
    static int getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy) { return idx_getDeviceBufferXY_marshall5(); }
    
    static void _call_getDeviceBufferXY_marshall5(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBufferXY_marshall5(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBufferXY_marshall5(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBufferXY_marshall5(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer_marshall6();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer_marshall6() {
      static int epidx = reg_getDeviceBuffer_marshall6();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer(void (DpcppPmePencilZ::*)(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy) ) {
      return idx_getDeviceBuffer_marshall6();
    }


    
    static int getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy) { return idx_getDeviceBuffer_marshall6(); }
    
    static void _call_getDeviceBuffer_marshall6(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer_marshall6(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer_marshall6(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer_marshall6(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBufferY_marshall7();
    // Entry point index lookup
    
    inline static int idx_getDeviceBufferY_marshall7() {
      static int epidx = reg_getDeviceBufferY_marshall7();
      return epidx;
    }

    
    inline static int idx_getDeviceBufferY(void (DpcppPmePencilZ::*)(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) ) {
      return idx_getDeviceBufferY_marshall7();
    }


    
    static int getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) { return idx_getDeviceBufferY_marshall7(); }
    
    static void _call_getDeviceBufferY_marshall7(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBufferY_marshall7(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBufferY_marshall7(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBufferY_marshall7(PUP::er &p,void *msg);
    /* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
     */
    // Entry point registration at startup
    
    static int reg_getDeviceBuffer_marshall8();
    // Entry point index lookup
    
    inline static int idx_getDeviceBuffer_marshall8() {
      static int epidx = reg_getDeviceBuffer_marshall8();
      return epidx;
    }

    
    inline static int idx_getDeviceBuffer(void (DpcppPmePencilZ::*)(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) ) {
      return idx_getDeviceBuffer_marshall8();
    }


    
    static int getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy) { return idx_getDeviceBuffer_marshall8(); }
    
    static void _call_getDeviceBuffer_marshall8(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_getDeviceBuffer_marshall8(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_getDeviceBuffer_marshall8(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_getDeviceBuffer_marshall8(PUP::er &p,void *msg);
    /* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBuffer_DeviceDataMsg();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBuffer_DeviceDataMsg() {
      static int epidx = reg_recvDeviceBuffer_DeviceDataMsg();
      return epidx;
    }

    
    inline static int idx_recvDeviceBuffer(void (DpcppPmePencilZ::*)(DeviceDataMsg* impl_msg) ) {
      return idx_recvDeviceBuffer_DeviceDataMsg();
    }


    
    static int recvDeviceBuffer(DeviceDataMsg* impl_msg) { return idx_recvDeviceBuffer_DeviceDataMsg(); }
    
    static void _call_recvDeviceBuffer_DeviceDataMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBuffer_DeviceDataMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvDeviceBuffers(const CkCallback &cb);
     */
    // Entry point registration at startup
    
    static int reg_recvDeviceBuffers_marshall10();
    // Entry point index lookup
    
    inline static int idx_recvDeviceBuffers_marshall10() {
      static int epidx = reg_recvDeviceBuffers_marshall10();
      return epidx;
    }

    
    inline static int idx_recvDeviceBuffers(void (DpcppPmePencilZ::*)(const CkCallback &cb) ) {
      return idx_recvDeviceBuffers_marshall10();
    }


    
    static int recvDeviceBuffers(const CkCallback &cb) { return idx_recvDeviceBuffers_marshall10(); }
    
    static void _call_recvDeviceBuffers_marshall10(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvDeviceBuffers_marshall10(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvDeviceBuffers_marshall10(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvDeviceBuffers_marshall10(PUP::er &p,void *msg);
    /* DECLS: DpcppPmePencilZ(CkMigrateMessage* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_DpcppPmePencilZ_CkMigrateMessage();
    // Entry point index lookup
    
    inline static int idx_DpcppPmePencilZ_CkMigrateMessage() {
      static int epidx = reg_DpcppPmePencilZ_CkMigrateMessage();
      return epidx;
    }

    
    static int ckNew(CkMigrateMessage* impl_msg) { return idx_DpcppPmePencilZ_CkMigrateMessage(); }
    
    static void _call_DpcppPmePencilZ_CkMigrateMessage(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_DpcppPmePencilZ_CkMigrateMessage(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
 class CProxyElement_DpcppPmePencilZ : public CProxyElement_PmePencilZ{
  public:
    typedef DpcppPmePencilZ local_t;
    typedef CkIndex_DpcppPmePencilZ index_t;
    typedef CProxy_DpcppPmePencilZ proxy_t;
    typedef CProxyElement_DpcppPmePencilZ element_t;
    typedef CProxySection_DpcppPmePencilZ section_t;

    using array_index_t = CkArrayIndex3D;

    /* TRAM aggregators */

    CProxyElement_DpcppPmePencilZ(void) {
    }
    CProxyElement_DpcppPmePencilZ(const ArrayElement *e) : CProxyElement_PmePencilZ(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_PmePencilZ::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_PmePencilZ::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_PmePencilZ::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxyElement_PmePencilZ::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_PmePencilZ::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_PmePencilZ::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_PmePencilZ::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxyElement_PmePencilZ::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxyElement_PmePencilZ::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxyElement_PmePencilZ::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxyElement_PmePencilZ::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxyElement_PmePencilZ::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxyElement_PmePencilZ::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxyElement_PmePencilZ::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxyElement_PmePencilZ::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxyElement_PmePencilZ::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxyElement_PmePencilZ::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilZ::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_PmePencilZ::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_PmePencilZ::ckSetReductionClient(cb); }

    inline void ckInsert(CkArrayMessage *m,int ctor,int onPe)
    { CProxyElement_PmePencilZ::ckInsert(m,ctor,onPe); }
    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0) const
    { CProxyElement_PmePencilZ::ckSend(m,ep,opts); }
    inline void *ckSendSync(CkArrayMessage *m, int ep) const
    { return CProxyElement_PmePencilZ::ckSendSync(m,ep); }
    inline const CkArrayIndex &ckGetIndex() const
    { return CProxyElement_PmePencilZ::ckGetIndex(); }

    DpcppPmePencilZ *ckLocal(void) const
    { return (DpcppPmePencilZ *)CProxyElement_PmePencilZ::ckLocal(); }

    CProxyElement_DpcppPmePencilZ(const CkArrayID &aid,const CkArrayIndex3D &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilZ(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilZ(const CkArrayID &aid,const CkArrayIndex3D &idx)
        :CProxyElement_PmePencilZ(aid,idx)
    {
}

    CProxyElement_DpcppPmePencilZ(const CkArrayID &aid,const CkArrayIndex &idx,CK_DELCTOR_PARAM)
        :CProxyElement_PmePencilZ(aid,idx,CK_DELCTOR_ARGS)
    {
}
    CProxyElement_DpcppPmePencilZ(const CkArrayID &aid,const CkArrayIndex &idx)
        :CProxyElement_PmePencilZ(aid,idx)
    {
}
/* DECLS: DpcppPmePencilZ();
 */
    
    void insert(int onPE=-1, const CkEntryOptions *impl_e_opts=NULL);
/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg2* impl_msg) ;

/* DECLS: void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
 */
    
    void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
 */
    
    void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilZ(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxyElement_DpcppPmePencilZ)
/* ---------------- collective proxy -------------- */
 class CProxy_DpcppPmePencilZ : public CProxy_PmePencilZ{
  public:
    typedef DpcppPmePencilZ local_t;
    typedef CkIndex_DpcppPmePencilZ index_t;
    typedef CProxy_DpcppPmePencilZ proxy_t;
    typedef CProxyElement_DpcppPmePencilZ element_t;
    typedef CProxySection_DpcppPmePencilZ section_t;

    using array_index_t = CkArrayIndex3D;
    CProxy_DpcppPmePencilZ(void) {
    }
    CProxy_DpcppPmePencilZ(const ArrayElement *e) : CProxy_PmePencilZ(e){
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_PmePencilZ::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_PmePencilZ::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_PmePencilZ::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxy_PmePencilZ::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_PmePencilZ::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_PmePencilZ::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_PmePencilZ::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_PmePencilZ::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxy_PmePencilZ::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxy_PmePencilZ::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxy_PmePencilZ::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxy_PmePencilZ::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxy_PmePencilZ::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxy_PmePencilZ::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxy_PmePencilZ::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxy_PmePencilZ::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxy_PmePencilZ::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilZ::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_PmePencilZ::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_PmePencilZ::ckSetReductionClient(cb); }

    // Generalized array indexing:
    CProxyElement_DpcppPmePencilZ operator [] (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilZ(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilZ operator() (const CkArrayIndex3D &idx) const
    { return CProxyElement_DpcppPmePencilZ(ckGetArrayID(), idx, CK_DELCTOR_CALL); }
    CProxyElement_DpcppPmePencilZ operator () (int i0,int i1,int i2) const 
        {return CProxyElement_DpcppPmePencilZ(ckGetArrayID(), CkArrayIndex3D(i0,i1,i2), CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilZ operator () (CkIndex3D idx) const 
        {return CProxyElement_DpcppPmePencilZ(ckGetArrayID(), CkArrayIndex3D(idx), CK_DELCTOR_CALL);}
    CProxy_DpcppPmePencilZ(const CkArrayID &aid,CK_DELCTOR_PARAM) 
        :CProxy_PmePencilZ(aid,CK_DELCTOR_ARGS) {}
    CProxy_DpcppPmePencilZ(const CkArrayID &aid) 
        :CProxy_PmePencilZ(aid) {}
/* DECLS: DpcppPmePencilZ();
 */
    
    static CkArrayID ckNew(const CkArrayOptions &opts = CkArrayOptions(), const CkEntryOptions *impl_e_opts=NULL);
    static void      ckNew(const CkArrayOptions &opts, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);
    static CkArrayID ckNew(const int s1, const int s2, const int s3, const CkEntryOptions *impl_e_opts=NULL);
    static void ckNew(const int s1, const int s2, const int s3, CkCallback _ck_array_creation_cb, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg2* impl_msg) ;

/* DECLS: void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
 */
    
    void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
 */
    
    void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilZ(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxy_DpcppPmePencilZ)
/* ---------------- section proxy -------------- */
 class CProxySection_DpcppPmePencilZ : public CProxySection_PmePencilZ{
  public:
    typedef DpcppPmePencilZ local_t;
    typedef CkIndex_DpcppPmePencilZ index_t;
    typedef CProxy_DpcppPmePencilZ proxy_t;
    typedef CProxyElement_DpcppPmePencilZ element_t;
    typedef CProxySection_DpcppPmePencilZ section_t;

    using array_index_t = CkArrayIndex3D;
    CProxySection_DpcppPmePencilZ(void) {
    }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_PmePencilZ::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_PmePencilZ::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_PmePencilZ::pup(p);
    }

    int ckIsDelegated(void) const
    { return CProxySection_PmePencilZ::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_PmePencilZ::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_PmePencilZ::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_PmePencilZ::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxySection_PmePencilZ::ckCheck(); }
    inline operator CkArrayID () const
    { return ckGetArrayID(); }
    inline CkArrayID ckGetArrayID(void) const
    { return CProxySection_PmePencilZ::ckGetArrayID(); }
    inline CkArray *ckLocalBranch(void) const
    { return CProxySection_PmePencilZ::ckLocalBranch(); }
    inline CkLocMgr *ckLocMgr(void) const
    { return CProxySection_PmePencilZ::ckLocMgr(); }

    inline static CkArrayID ckCreateEmptyArray(CkArrayOptions opts = CkArrayOptions())
    { return CProxySection_PmePencilZ::ckCreateEmptyArray(opts); }
    inline static void ckCreateEmptyArrayAsync(CkCallback cb, CkArrayOptions opts = CkArrayOptions())
    { CProxySection_PmePencilZ::ckCreateEmptyArrayAsync(cb, opts); }
    inline static CkArrayID ckCreateArray(CkArrayMessage *m,int ctor,const CkArrayOptions &opts)
    { return CProxySection_PmePencilZ::ckCreateArray(m,ctor,opts); }
    inline void ckInsertIdx(CkArrayMessage *m,int ctor,int onPe,const CkArrayIndex &idx)
    { CProxySection_PmePencilZ::ckInsertIdx(m,ctor,onPe,idx); }
    inline void doneInserting(void)
    { CProxySection_PmePencilZ::doneInserting(); }

    inline void ckBroadcast(CkArrayMessage *m, int ep, int opts=0) const
    { CProxySection_PmePencilZ::ckBroadcast(m,ep,opts); }
    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilZ::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_PmePencilZ::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_PmePencilZ::ckSetReductionClient(cb); }

    inline void ckSend(CkArrayMessage *m, int ep, int opts = 0)
    { CProxySection_PmePencilZ::ckSend(m,ep,opts); }
    inline CkSectionInfo &ckGetSectionInfo()
    { return CProxySection_PmePencilZ::ckGetSectionInfo(); }
    inline CkSectionID *ckGetSectionIDs()
    { return CProxySection_PmePencilZ::ckGetSectionIDs(); }
    inline CkSectionID &ckGetSectionID()
    { return CProxySection_PmePencilZ::ckGetSectionID(); }
    inline CkSectionID &ckGetSectionID(int i)
    { return CProxySection_PmePencilZ::ckGetSectionID(i); }
    inline CkArrayID ckGetArrayIDn(int i) const
    { return CProxySection_PmePencilZ::ckGetArrayIDn(i); } 
    inline CkArrayIndex *ckGetArrayElements() const
    { return CProxySection_PmePencilZ::ckGetArrayElements(); }
    inline CkArrayIndex *ckGetArrayElements(int i) const
    { return CProxySection_PmePencilZ::ckGetArrayElements(i); }
    inline int ckGetNumElements() const
    { return CProxySection_PmePencilZ::ckGetNumElements(); } 
    inline int ckGetNumElements(int i) const
    { return CProxySection_PmePencilZ::ckGetNumElements(i); }    // Generalized array indexing:
    CProxyElement_DpcppPmePencilZ operator [] (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilZ(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilZ operator() (const CkArrayIndex3D &idx) const
        {return CProxyElement_DpcppPmePencilZ(ckGetArrayID(), idx, CK_DELCTOR_CALL);}
    CProxyElement_DpcppPmePencilZ operator () (int idx) const 
        {return CProxyElement_DpcppPmePencilZ(ckGetArrayID(), *(CkArrayIndex3D*)&ckGetArrayElements()[idx], CK_DELCTOR_CALL);}
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex3D *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex3D> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      return CkSectionID(aid, elems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, int l1, int u1, int s1, int l2, int u2, int s2, int l3, int u3, int s3, int factor=USE_DEFAULT_BRANCH_FACTOR) {
      std::vector<CkArrayIndex3D> al;
      for (int i=l1; i<=u1; i+=s1) 
        for (int j=l2; j<=u2; j+=s2) 
          for (int k=l3; k<=u3; k+=s3) 
          al.emplace_back(i, j, k);
      return CkSectionID(aid, al, factor);
    } 
    CProxySection_DpcppPmePencilZ(const CkArrayID &aid, CkArrayIndex *elems, int nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilZ(aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilZ(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilZ(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilZ(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilZ(aid,elems,nElems, factor) {}
    CProxySection_DpcppPmePencilZ(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor=USE_DEFAULT_BRANCH_FACTOR) 
        :CProxySection_PmePencilZ(aid,elems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilZ(const CkSectionID &sid)  
        :CProxySection_PmePencilZ(sid) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilZ(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilZ(n,aid,elems,nElems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilZ(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, CK_DELCTOR_PARAM) 
        :CProxySection_PmePencilZ(aid,elems,CK_DELCTOR_ARGS) {}
    CProxySection_DpcppPmePencilZ(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems) 
        :CProxySection_PmePencilZ(n,aid,elems,nElems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilZ(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems) 
        :CProxySection_PmePencilZ(aid,elems) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilZ(int n, const CkArrayID *aid, CkArrayIndex const * const *elems, const int *nElems, int factor) 
        :CProxySection_PmePencilZ(n,aid,elems,nElems, factor) { ckAutoDelegate(); }
    CProxySection_DpcppPmePencilZ(const std::vector<CkArrayID> &aid, const std::vector<std::vector<CkArrayIndex> > &elems, int factor) 
        :CProxySection_PmePencilZ(aid,elems, factor) { ckAutoDelegate(); }
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems) {
      return CkSectionID(aid, elems, nElems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems) {
       return CkSectionID(aid, elems);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, CkArrayIndex *elems, int nElems, int factor) {
      return CkSectionID(aid, elems, nElems, factor);
    } 
    static CkSectionID ckNew(const CkArrayID &aid, const std::vector<CkArrayIndex> &elems, int factor) {
      return CkSectionID(aid, elems, factor);
    } 
    void ckAutoDelegate(int opts=1) {
      if(ckIsDelegated()) return;
      CProxySection_PmePencilZ::ckAutoDelegate(opts);
    } 
    void setReductionClient(CkCallback *cb) {
      CProxySection_PmePencilZ::setReductionClient(cb);
    } 
    void resetSection() {
      CProxySection_PmePencilZ::resetSection();
    } 
    static void contribute(CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, int userData=-1, int fragSize=-1);
    static void contribute(CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    static void contribute(int dataSize,void *data,CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
    template <typename T>
    static void contribute(std::vector<T> &data, CkReduction::reducerType type, CkSectionInfo &sid, const CkCallback &cb, int userData=-1, int fragSize=-1);
/* DECLS: DpcppPmePencilZ();
 */
    

/* DECLS: void initialize(DpcppPmeXInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXInitMsg* impl_msg) ;

/* DECLS: void initialize(DpcppPmeXYInitMsg* impl_msg);
 */
    
    void initialize(DpcppPmeXYInitMsg* impl_msg) ;

/* DECLS: void initializeDevice(InitDeviceMsg2* impl_msg);
 */
    
    void initializeDevice(InitDeviceMsg2* impl_msg) ;

/* DECLS: void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
 */
    
    void getDeviceBufferXY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy);
 */
    
    void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilXY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBufferY(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy);
 */
    
    void getDeviceBuffer(int z, const bool &sameDevice, const CProxy_DpcppPmePencilY &proxy, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: void recvDeviceBuffer(DeviceDataMsg* impl_msg);
 */
    
    void recvDeviceBuffer(DeviceDataMsg* impl_msg) ;

/* DECLS: void recvDeviceBuffers(const CkCallback &cb);
 */
    
    void recvDeviceBuffers(const CkCallback &cb, const CkEntryOptions *impl_e_opts=NULL) ;

/* DECLS: DpcppPmePencilZ(CkMigrateMessage* impl_msg);
 */

};
PUPmarshall(CProxySection_DpcppPmePencilZ)
#define DpcppPmePencilZ_SDAG_CODE                                              \
public:                                                                        \
  void getDeviceBuffer(int z, bool sameDevice, CProxy_DpcppPmePencilXY proxy); \
  void getDeviceBuffer(Closure_DpcppPmePencilZ::getDeviceBuffer_6_closure* gen0);\
private:                                                                       \
  void getDeviceBuffer_end(Closure_DpcppPmePencilZ::getDeviceBuffer_6_closure* gen0);\
  void _slist_0(Closure_DpcppPmePencilZ::getDeviceBuffer_6_closure* gen0);     \
  void _slist_0_end(Closure_DpcppPmePencilZ::getDeviceBuffer_6_closure* gen0); \
  void _serial_0(Closure_DpcppPmePencilZ::getDeviceBuffer_6_closure* gen0);    \
public:                                                                        \
  void getDeviceBuffer(int z, bool sameDevice, CProxy_DpcppPmePencilY proxy);  \
  void getDeviceBuffer(Closure_DpcppPmePencilZ::getDeviceBuffer_8_closure* gen0);\
private:                                                                       \
  void getDeviceBuffer_end(Closure_DpcppPmePencilZ::getDeviceBuffer_8_closure* gen0);\
  void _slist_1(Closure_DpcppPmePencilZ::getDeviceBuffer_8_closure* gen0);     \
  void _slist_1_end(Closure_DpcppPmePencilZ::getDeviceBuffer_8_closure* gen0); \
  void _serial_1(Closure_DpcppPmePencilZ::getDeviceBuffer_8_closure* gen0);    \
public:                                                                        \
  void recvDeviceBuffers(const CkCallback & cb);                               \
  void _sdag_fnc_recvDeviceBuffers(const CkCallback & cb);                     \
  void _sdag_fnc_recvDeviceBuffers(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0);\
private:                                                                       \
  void recvDeviceBuffers_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0);\
  void _slist_2(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0);  \
  void _slist_2_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0);\
  void _overlap_0(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0);\
  void _overlap_0_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0);\
  void _olist_0(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0);  \
  void _olist_0_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_0_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_3_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_0(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _when_0_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _serial_2(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, DeviceDataMsg* gen2);\
  void _for_1(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_1_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_4(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_4_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_1(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _when_1_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilZ::getDeviceBufferY_7_closure* gen2);\
  void _serial_3(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilZ::getDeviceBufferY_7_closure* gen2);\
  void _for_2(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _for_2_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_5(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _slist_5_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  SDAG::Continuation* _when_2(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0);\
  void _when_2_end(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilZ::getDeviceBufferXY_5_closure* gen2);\
  void _serial_4(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0, SDAG::CCounter* _co0, Closure_DpcppPmePencilZ::getDeviceBufferXY_5_closure* gen2);\
  void _serial_5(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0); \
  void _serial_6(Closure_DpcppPmePencilZ::recvDeviceBuffers_10_closure* gen0); \
public:                                                                        \
  void recvDeviceBuffer(DeviceDataMsg* msg_msg);                               \
  void getDeviceBufferY(Closure_DpcppPmePencilZ::getDeviceBufferY_7_closure* genClosure);\
  void getDeviceBufferY(int z, bool sameDevice, CProxy_DpcppPmePencilY proxy); \
  void getDeviceBufferXY(Closure_DpcppPmePencilZ::getDeviceBufferXY_5_closure* genClosure);\
  void getDeviceBufferXY(int z, bool sameDevice, CProxy_DpcppPmePencilXY proxy);\
public:                                                                        \
  SDAG::dep_ptr __dep;                                                         \
  void _sdag_init();                                                           \
  void __sdag_init();                                                          \
public:                                                                        \
  void _sdag_pup(PUP::er &p);                                                  \
  void __sdag_pup(PUP::er &p) { }                                              \
  static void __sdag_register();                                               \
  static int _sdag_idx_DpcppPmePencilZ_serial_0();                             \
  static int _sdag_reg_DpcppPmePencilZ_serial_0();                             \
  static int _sdag_idx_DpcppPmePencilZ_serial_1();                             \
  static int _sdag_reg_DpcppPmePencilZ_serial_1();                             \
  static int _sdag_idx_DpcppPmePencilZ_serial_2();                             \
  static int _sdag_reg_DpcppPmePencilZ_serial_2();                             \
  static int _sdag_idx_DpcppPmePencilZ_serial_3();                             \
  static int _sdag_reg_DpcppPmePencilZ_serial_3();                             \
  static int _sdag_idx_DpcppPmePencilZ_serial_4();                             \
  static int _sdag_reg_DpcppPmePencilZ_serial_4();                             \
  static int _sdag_idx_DpcppPmePencilZ_serial_5();                             \
  static int _sdag_reg_DpcppPmePencilZ_serial_5();                             \
  static int _sdag_idx_DpcppPmePencilZ_serial_6();                             \
  static int _sdag_reg_DpcppPmePencilZ_serial_6();                             \

typedef CBaseT1<PmePencilZ, CProxy_DpcppPmePencilZ>CBase_DpcppPmePencilZ;








/* ---------------- method closures -------------- */
class Closure_DpcppPmePencilXYZ {
  public:




};


/* ---------------- method closures -------------- */
class Closure_DpcppPmePencilXY {
  public:




    struct getDeviceBufferZ_4_closure;


    struct getDeviceBuffer_5_closure;



    struct recvDeviceBuffers_7_closure;


};


/* ---------------- method closures -------------- */
class Closure_DpcppPmePencilX {
  public:




    struct getDeviceBuffer2_4_closure;


    struct getDeviceBuffer_5_closure;



    struct recvDeviceBuffers_7_closure;


};

/* ---------------- method closures -------------- */
class Closure_DpcppPmePencilY {
  public:




    struct getDeviceBuffer2_4_closure;


    struct getDeviceBuffer_5_closure;


    struct getDeviceBuffer22_6_closure;


    struct getDeviceBuffer_7_closure;




    struct recvDeviceBuffers_10_closure;


};

/* ---------------- method closures -------------- */
class Closure_DpcppPmePencilZ {
  public:





    struct getDeviceBufferXY_5_closure;


    struct getDeviceBuffer_6_closure;


    struct getDeviceBufferY_7_closure;


    struct getDeviceBuffer_8_closure;



    struct recvDeviceBuffers_10_closure;


};

extern void _registerDpcppPmeSolver(void);
#endif
