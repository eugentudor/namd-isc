#ifndef _DECL_ComputeMgr_H_
#define _DECL_ComputeMgr_H_
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
/* DECLS: message ComputeGlobalDataMsg;
 */
class ComputeGlobalDataMsg;
class CMessage_ComputeGlobalDataMsg:public CkMessage{
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
    CMessage_ComputeGlobalDataMsg();
    static void *pack(ComputeGlobalDataMsg *p);
    static ComputeGlobalDataMsg* unpack(void* p);
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
/* DECLS: message ComputeGlobalResultsMsg;
 */
class ComputeGlobalResultsMsg;
class CMessage_ComputeGlobalResultsMsg:public CkMessage{
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
    CMessage_ComputeGlobalResultsMsg();
    static void *pack(ComputeGlobalResultsMsg *p);
    static ComputeGlobalResultsMsg* unpack(void* p);
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
/* DECLS: message ComputeDPMEDataMsg;
 */
class ComputeDPMEDataMsg;
class CMessage_ComputeDPMEDataMsg:public CkMessage{
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
    CMessage_ComputeDPMEDataMsg();
    static void *pack(ComputeDPMEDataMsg *p);
    static ComputeDPMEDataMsg* unpack(void* p);
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
/* DECLS: message ComputeDPMEResultsMsg;
 */
class ComputeDPMEResultsMsg;
class CMessage_ComputeDPMEResultsMsg:public CkMessage{
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
    CMessage_ComputeDPMEResultsMsg();
    static void *pack(ComputeDPMEResultsMsg *p);
    static ComputeDPMEResultsMsg* unpack(void* p);
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
/* DECLS: message ComputeConsForceMsg;
 */
class ComputeConsForceMsg;
class CMessage_ComputeConsForceMsg:public CkMessage{
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
    CMessage_ComputeConsForceMsg();
    static void *pack(ComputeConsForceMsg *p);
    static ComputeConsForceMsg* unpack(void* p);
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
/* DECLS: message ComputeEwaldMsg{
float eik[];
}
;
 */
class ComputeEwaldMsg;
class CMessage_ComputeEwaldMsg:public CkMessage{
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
    CMessage_ComputeEwaldMsg();
    static void *pack(ComputeEwaldMsg *p);
    static ComputeEwaldMsg* unpack(void* p);
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
/* DECLS: message NonbondedCUDASlaveMsg;
 */
class NonbondedCUDASlaveMsg;
class CMessage_NonbondedCUDASlaveMsg:public CkMessage{
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
    CMessage_NonbondedCUDASlaveMsg();
    static void *pack(NonbondedCUDASlaveMsg *p);
    static NonbondedCUDASlaveMsg* unpack(void* p);
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
/* DECLS: message NonbondedCUDASkipMsg;
 */
class NonbondedCUDASkipMsg;
class CMessage_NonbondedCUDASkipMsg:public CkMessage{
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
    CMessage_NonbondedCUDASkipMsg();
    static void *pack(NonbondedCUDASkipMsg *p);
    static NonbondedCUDASkipMsg* unpack(void* p);
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
/* DECLS: message NonbondedMICSlaveMsg;
 */
class NonbondedMICSlaveMsg;
class CMessage_NonbondedMICSlaveMsg:public CkMessage{
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
    CMessage_NonbondedMICSlaveMsg();
    static void *pack(NonbondedMICSlaveMsg *p);
    static NonbondedMICSlaveMsg* unpack(void* p);
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
/* DECLS: message NonbondedMICSkipMsg;
 */
class NonbondedMICSkipMsg;
class CMessage_NonbondedMICSkipMsg:public CkMessage{
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
    CMessage_NonbondedMICSkipMsg();
    static void *pack(NonbondedMICSkipMsg *p);
    static NonbondedMICSkipMsg* unpack(void* p);
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
/* DECLS: message DpcppComputeNonbondedMsg;
 */
class DpcppComputeNonbondedMsg;
class CMessage_DpcppComputeNonbondedMsg:public CkMessage{
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
    CMessage_DpcppComputeNonbondedMsg();
    static void *pack(DpcppComputeNonbondedMsg *p);
    static DpcppComputeNonbondedMsg* unpack(void* p);
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
/* DECLS: message DpcppComputeBondedMsg;
 */
class DpcppComputeBondedMsg;
class CMessage_DpcppComputeBondedMsg:public CkMessage{
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
    CMessage_DpcppComputeBondedMsg();
    static void *pack(DpcppComputeBondedMsg *p);
    static DpcppComputeBondedMsg* unpack(void* p);
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

/* DECLS: group ComputeMgr: IrrGroup{
ComputeMgr();
void updateComputes2(CkQdMsg* impl_msg);
void updateComputes3();
void splitComputes();
void splitComputes2(CkQdMsg* impl_msg);
void updateLocalComputes();
void updateLocalComputes2(CkQdMsg* impl_msg);
void updateLocalComputes3();
void updateLocalComputes4(CkQdMsg* impl_msg);
void updateLocalComputes5();
void doneUpdateLocalComputes();
void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);
void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);
void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);
void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);
void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);
void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);
void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);
void recvYieldDevice(int pe);
void recvBuildCudaExclusions();
void recvBuildCudaForceTable();
void recvBuildMICForceTable();
void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);
void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2);
void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);
void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);
void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);
void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);
void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);
sync void recvUnregisterBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);
void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);
void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);
void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);
sync void recvUnregisterBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);
void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5);
void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);
void recvMICPEData(int impl_noname_6, int impl_noname_7);
};
 */
 class ComputeMgr;
 class CkIndex_ComputeMgr;
 class CProxy_ComputeMgr;
 class CProxyElement_ComputeMgr;
 class CProxySection_ComputeMgr;
/* --------------- index object ------------------ */
class CkIndex_ComputeMgr:public CkIndex_IrrGroup{
  public:
    typedef ComputeMgr local_t;
    typedef CkIndex_ComputeMgr index_t;
    typedef CProxy_ComputeMgr proxy_t;
    typedef CProxyElement_ComputeMgr element_t;
    typedef CProxySection_ComputeMgr section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: ComputeMgr();
     */
    // Entry point registration at startup
    
    static int reg_ComputeMgr_void();
    // Entry point index lookup
    
    inline static int idx_ComputeMgr_void() {
      static int epidx = reg_ComputeMgr_void();
      return epidx;
    }

    
    static int ckNew() { return idx_ComputeMgr_void(); }
    
    static void _call_ComputeMgr_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_ComputeMgr_void(void* impl_msg, void* impl_obj);
    /* DECLS: void updateComputes2(CkQdMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_updateComputes2_CkQdMsg();
    // Entry point index lookup
    
    inline static int idx_updateComputes2_CkQdMsg() {
      static int epidx = reg_updateComputes2_CkQdMsg();
      return epidx;
    }

    
    inline static int idx_updateComputes2(void (ComputeMgr::*)(CkQdMsg* impl_msg) ) {
      return idx_updateComputes2_CkQdMsg();
    }


    
    static int updateComputes2(CkQdMsg* impl_msg) { return idx_updateComputes2_CkQdMsg(); }
    
    static void _call_updateComputes2_CkQdMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateComputes2_CkQdMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void updateComputes3();
     */
    // Entry point registration at startup
    
    static int reg_updateComputes3_void();
    // Entry point index lookup
    
    inline static int idx_updateComputes3_void() {
      static int epidx = reg_updateComputes3_void();
      return epidx;
    }

    
    inline static int idx_updateComputes3(void (ComputeMgr::*)() ) {
      return idx_updateComputes3_void();
    }


    
    static int updateComputes3() { return idx_updateComputes3_void(); }
    
    static void _call_updateComputes3_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateComputes3_void(void* impl_msg, void* impl_obj);
    /* DECLS: void splitComputes();
     */
    // Entry point registration at startup
    
    static int reg_splitComputes_void();
    // Entry point index lookup
    
    inline static int idx_splitComputes_void() {
      static int epidx = reg_splitComputes_void();
      return epidx;
    }

    
    inline static int idx_splitComputes(void (ComputeMgr::*)() ) {
      return idx_splitComputes_void();
    }


    
    static int splitComputes() { return idx_splitComputes_void(); }
    
    static void _call_splitComputes_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_splitComputes_void(void* impl_msg, void* impl_obj);
    /* DECLS: void splitComputes2(CkQdMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_splitComputes2_CkQdMsg();
    // Entry point index lookup
    
    inline static int idx_splitComputes2_CkQdMsg() {
      static int epidx = reg_splitComputes2_CkQdMsg();
      return epidx;
    }

    
    inline static int idx_splitComputes2(void (ComputeMgr::*)(CkQdMsg* impl_msg) ) {
      return idx_splitComputes2_CkQdMsg();
    }


    
    static int splitComputes2(CkQdMsg* impl_msg) { return idx_splitComputes2_CkQdMsg(); }
    
    static void _call_splitComputes2_CkQdMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_splitComputes2_CkQdMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void updateLocalComputes();
     */
    // Entry point registration at startup
    
    static int reg_updateLocalComputes_void();
    // Entry point index lookup
    
    inline static int idx_updateLocalComputes_void() {
      static int epidx = reg_updateLocalComputes_void();
      return epidx;
    }

    
    inline static int idx_updateLocalComputes(void (ComputeMgr::*)() ) {
      return idx_updateLocalComputes_void();
    }


    
    static int updateLocalComputes() { return idx_updateLocalComputes_void(); }
    
    static void _call_updateLocalComputes_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateLocalComputes_void(void* impl_msg, void* impl_obj);
    /* DECLS: void updateLocalComputes2(CkQdMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_updateLocalComputes2_CkQdMsg();
    // Entry point index lookup
    
    inline static int idx_updateLocalComputes2_CkQdMsg() {
      static int epidx = reg_updateLocalComputes2_CkQdMsg();
      return epidx;
    }

    
    inline static int idx_updateLocalComputes2(void (ComputeMgr::*)(CkQdMsg* impl_msg) ) {
      return idx_updateLocalComputes2_CkQdMsg();
    }


    
    static int updateLocalComputes2(CkQdMsg* impl_msg) { return idx_updateLocalComputes2_CkQdMsg(); }
    
    static void _call_updateLocalComputes2_CkQdMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateLocalComputes2_CkQdMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void updateLocalComputes3();
     */
    // Entry point registration at startup
    
    static int reg_updateLocalComputes3_void();
    // Entry point index lookup
    
    inline static int idx_updateLocalComputes3_void() {
      static int epidx = reg_updateLocalComputes3_void();
      return epidx;
    }

    
    inline static int idx_updateLocalComputes3(void (ComputeMgr::*)() ) {
      return idx_updateLocalComputes3_void();
    }


    
    static int updateLocalComputes3() { return idx_updateLocalComputes3_void(); }
    
    static void _call_updateLocalComputes3_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateLocalComputes3_void(void* impl_msg, void* impl_obj);
    /* DECLS: void updateLocalComputes4(CkQdMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_updateLocalComputes4_CkQdMsg();
    // Entry point index lookup
    
    inline static int idx_updateLocalComputes4_CkQdMsg() {
      static int epidx = reg_updateLocalComputes4_CkQdMsg();
      return epidx;
    }

    
    inline static int idx_updateLocalComputes4(void (ComputeMgr::*)(CkQdMsg* impl_msg) ) {
      return idx_updateLocalComputes4_CkQdMsg();
    }


    
    static int updateLocalComputes4(CkQdMsg* impl_msg) { return idx_updateLocalComputes4_CkQdMsg(); }
    
    static void _call_updateLocalComputes4_CkQdMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateLocalComputes4_CkQdMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void updateLocalComputes5();
     */
    // Entry point registration at startup
    
    static int reg_updateLocalComputes5_void();
    // Entry point index lookup
    
    inline static int idx_updateLocalComputes5_void() {
      static int epidx = reg_updateLocalComputes5_void();
      return epidx;
    }

    
    inline static int idx_updateLocalComputes5(void (ComputeMgr::*)() ) {
      return idx_updateLocalComputes5_void();
    }


    
    static int updateLocalComputes5() { return idx_updateLocalComputes5_void(); }
    
    static void _call_updateLocalComputes5_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_updateLocalComputes5_void(void* impl_msg, void* impl_obj);
    /* DECLS: void doneUpdateLocalComputes();
     */
    // Entry point registration at startup
    
    static int reg_doneUpdateLocalComputes_void();
    // Entry point index lookup
    
    inline static int idx_doneUpdateLocalComputes_void() {
      static int epidx = reg_doneUpdateLocalComputes_void();
      return epidx;
    }

    
    inline static int idx_doneUpdateLocalComputes(void (ComputeMgr::*)() ) {
      return idx_doneUpdateLocalComputes_void();
    }


    
    static int doneUpdateLocalComputes() { return idx_doneUpdateLocalComputes_void(); }
    
    static void _call_doneUpdateLocalComputes_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_doneUpdateLocalComputes_void(void* impl_msg, void* impl_obj);
    /* DECLS: void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvComputeGlobalData_ComputeGlobalDataMsg();
    // Entry point index lookup
    
    inline static int idx_recvComputeGlobalData_ComputeGlobalDataMsg() {
      static int epidx = reg_recvComputeGlobalData_ComputeGlobalDataMsg();
      return epidx;
    }

    
    inline static int idx_recvComputeGlobalData(void (ComputeMgr::*)(ComputeGlobalDataMsg* impl_msg) ) {
      return idx_recvComputeGlobalData_ComputeGlobalDataMsg();
    }


    
    static int recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg) { return idx_recvComputeGlobalData_ComputeGlobalDataMsg(); }
    
    static void _call_recvComputeGlobalData_ComputeGlobalDataMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvComputeGlobalData_ComputeGlobalDataMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvComputeGlobalResults_ComputeGlobalResultsMsg();
    // Entry point index lookup
    
    inline static int idx_recvComputeGlobalResults_ComputeGlobalResultsMsg() {
      static int epidx = reg_recvComputeGlobalResults_ComputeGlobalResultsMsg();
      return epidx;
    }

    
    inline static int idx_recvComputeGlobalResults(void (ComputeMgr::*)(ComputeGlobalResultsMsg* impl_msg) ) {
      return idx_recvComputeGlobalResults_ComputeGlobalResultsMsg();
    }


    
    static int recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg) { return idx_recvComputeGlobalResults_ComputeGlobalResultsMsg(); }
    
    static void _call_recvComputeGlobalResults_ComputeGlobalResultsMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvComputeGlobalResults_ComputeGlobalResultsMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvComputeDPMEData_ComputeDPMEDataMsg();
    // Entry point index lookup
    
    inline static int idx_recvComputeDPMEData_ComputeDPMEDataMsg() {
      static int epidx = reg_recvComputeDPMEData_ComputeDPMEDataMsg();
      return epidx;
    }

    
    inline static int idx_recvComputeDPMEData(void (ComputeMgr::*)(ComputeDPMEDataMsg* impl_msg) ) {
      return idx_recvComputeDPMEData_ComputeDPMEDataMsg();
    }


    
    static int recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg) { return idx_recvComputeDPMEData_ComputeDPMEDataMsg(); }
    
    static void _call_recvComputeDPMEData_ComputeDPMEDataMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvComputeDPMEData_ComputeDPMEDataMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvComputeDPMEResults_ComputeDPMEResultsMsg();
    // Entry point index lookup
    
    inline static int idx_recvComputeDPMEResults_ComputeDPMEResultsMsg() {
      static int epidx = reg_recvComputeDPMEResults_ComputeDPMEResultsMsg();
      return epidx;
    }

    
    inline static int idx_recvComputeDPMEResults(void (ComputeMgr::*)(ComputeDPMEResultsMsg* impl_msg) ) {
      return idx_recvComputeDPMEResults_ComputeDPMEResultsMsg();
    }


    
    static int recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg) { return idx_recvComputeDPMEResults_ComputeDPMEResultsMsg(); }
    
    static void _call_recvComputeDPMEResults_ComputeDPMEResultsMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvComputeDPMEResults_ComputeDPMEResultsMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvComputeConsForceMsg_ComputeConsForceMsg();
    // Entry point index lookup
    
    inline static int idx_recvComputeConsForceMsg_ComputeConsForceMsg() {
      static int epidx = reg_recvComputeConsForceMsg_ComputeConsForceMsg();
      return epidx;
    }

    
    inline static int idx_recvComputeConsForceMsg(void (ComputeMgr::*)(ComputeConsForceMsg* impl_msg) ) {
      return idx_recvComputeConsForceMsg_ComputeConsForceMsg();
    }


    
    static int recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg) { return idx_recvComputeConsForceMsg_ComputeConsForceMsg(); }
    
    static void _call_recvComputeConsForceMsg_ComputeConsForceMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvComputeConsForceMsg_ComputeConsForceMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvComputeEwaldData_ComputeEwaldMsg();
    // Entry point index lookup
    
    inline static int idx_recvComputeEwaldData_ComputeEwaldMsg() {
      static int epidx = reg_recvComputeEwaldData_ComputeEwaldMsg();
      return epidx;
    }

    
    inline static int idx_recvComputeEwaldData(void (ComputeMgr::*)(ComputeEwaldMsg* impl_msg) ) {
      return idx_recvComputeEwaldData_ComputeEwaldMsg();
    }


    
    static int recvComputeEwaldData(ComputeEwaldMsg* impl_msg) { return idx_recvComputeEwaldData_ComputeEwaldMsg(); }
    
    static void _call_recvComputeEwaldData_ComputeEwaldMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvComputeEwaldData_ComputeEwaldMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvComputeEwaldResults_ComputeEwaldMsg();
    // Entry point index lookup
    
    inline static int idx_recvComputeEwaldResults_ComputeEwaldMsg() {
      static int epidx = reg_recvComputeEwaldResults_ComputeEwaldMsg();
      return epidx;
    }

    
    inline static int idx_recvComputeEwaldResults(void (ComputeMgr::*)(ComputeEwaldMsg* impl_msg) ) {
      return idx_recvComputeEwaldResults_ComputeEwaldMsg();
    }


    
    static int recvComputeEwaldResults(ComputeEwaldMsg* impl_msg) { return idx_recvComputeEwaldResults_ComputeEwaldMsg(); }
    
    static void _call_recvComputeEwaldResults_ComputeEwaldMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvComputeEwaldResults_ComputeEwaldMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvYieldDevice(int pe);
     */
    // Entry point registration at startup
    
    static int reg_recvYieldDevice_marshall19();
    // Entry point index lookup
    
    inline static int idx_recvYieldDevice_marshall19() {
      static int epidx = reg_recvYieldDevice_marshall19();
      return epidx;
    }

    
    inline static int idx_recvYieldDevice(void (ComputeMgr::*)(int pe) ) {
      return idx_recvYieldDevice_marshall19();
    }


    
    static int recvYieldDevice(int pe) { return idx_recvYieldDevice_marshall19(); }
    
    static void _call_recvYieldDevice_marshall19(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvYieldDevice_marshall19(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvYieldDevice_marshall19(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvYieldDevice_marshall19(PUP::er &p,void *msg);
    /* DECLS: void recvBuildCudaExclusions();
     */
    // Entry point registration at startup
    
    static int reg_recvBuildCudaExclusions_void();
    // Entry point index lookup
    
    inline static int idx_recvBuildCudaExclusions_void() {
      static int epidx = reg_recvBuildCudaExclusions_void();
      return epidx;
    }

    
    inline static int idx_recvBuildCudaExclusions(void (ComputeMgr::*)() ) {
      return idx_recvBuildCudaExclusions_void();
    }


    
    static int recvBuildCudaExclusions() { return idx_recvBuildCudaExclusions_void(); }
    
    static void _call_recvBuildCudaExclusions_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvBuildCudaExclusions_void(void* impl_msg, void* impl_obj);
    /* DECLS: void recvBuildCudaForceTable();
     */
    // Entry point registration at startup
    
    static int reg_recvBuildCudaForceTable_void();
    // Entry point index lookup
    
    inline static int idx_recvBuildCudaForceTable_void() {
      static int epidx = reg_recvBuildCudaForceTable_void();
      return epidx;
    }

    
    inline static int idx_recvBuildCudaForceTable(void (ComputeMgr::*)() ) {
      return idx_recvBuildCudaForceTable_void();
    }


    
    static int recvBuildCudaForceTable() { return idx_recvBuildCudaForceTable_void(); }
    
    static void _call_recvBuildCudaForceTable_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvBuildCudaForceTable_void(void* impl_msg, void* impl_obj);
    /* DECLS: void recvBuildMICForceTable();
     */
    // Entry point registration at startup
    
    static int reg_recvBuildMICForceTable_void();
    // Entry point index lookup
    
    inline static int idx_recvBuildMICForceTable_void() {
      static int epidx = reg_recvBuildMICForceTable_void();
      return epidx;
    }

    
    inline static int idx_recvBuildMICForceTable(void (ComputeMgr::*)() ) {
      return idx_recvBuildMICForceTable_void();
    }


    
    static int recvBuildMICForceTable() { return idx_recvBuildMICForceTable_void(); }
    
    static void _call_recvBuildMICForceTable_void(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvBuildMICForceTable_void(void* impl_msg, void* impl_obj);
    /* DECLS: void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvCreateNonbondedCUDASlave_NonbondedCUDASlaveMsg();
    // Entry point index lookup
    
    inline static int idx_recvCreateNonbondedCUDASlave_NonbondedCUDASlaveMsg() {
      static int epidx = reg_recvCreateNonbondedCUDASlave_NonbondedCUDASlaveMsg();
      return epidx;
    }

    
    inline static int idx_recvCreateNonbondedCUDASlave(void (ComputeMgr::*)(NonbondedCUDASlaveMsg* impl_msg) ) {
      return idx_recvCreateNonbondedCUDASlave_NonbondedCUDASlaveMsg();
    }


    
    static int recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg) { return idx_recvCreateNonbondedCUDASlave_NonbondedCUDASlaveMsg(); }
    
    static void _call_recvCreateNonbondedCUDASlave_NonbondedCUDASlaveMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvCreateNonbondedCUDASlave_NonbondedCUDASlaveMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2);
     */
    // Entry point registration at startup
    
    static int reg_recvNonbondedCUDASlaveReady_marshall24();
    // Entry point index lookup
    
    inline static int idx_recvNonbondedCUDASlaveReady_marshall24() {
      static int epidx = reg_recvNonbondedCUDASlaveReady_marshall24();
      return epidx;
    }

    
    inline static int idx_recvNonbondedCUDASlaveReady(void (ComputeMgr::*)(int impl_noname_0, int impl_noname_1, int impl_noname_2) ) {
      return idx_recvNonbondedCUDASlaveReady_marshall24();
    }


    
    static int recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2) { return idx_recvNonbondedCUDASlaveReady_marshall24(); }
    
    static void _call_recvNonbondedCUDASlaveReady_marshall24(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvNonbondedCUDASlaveReady_marshall24(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvNonbondedCUDASlaveReady_marshall24(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvNonbondedCUDASlaveReady_marshall24(PUP::er &p,void *msg);
    /* DECLS: void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvNonbondedCUDASlaveSkip_NonbondedCUDASkipMsg();
    // Entry point index lookup
    
    inline static int idx_recvNonbondedCUDASlaveSkip_NonbondedCUDASkipMsg() {
      static int epidx = reg_recvNonbondedCUDASlaveSkip_NonbondedCUDASkipMsg();
      return epidx;
    }

    
    inline static int idx_recvNonbondedCUDASlaveSkip(void (ComputeMgr::*)(NonbondedCUDASkipMsg* impl_msg) ) {
      return idx_recvNonbondedCUDASlaveSkip_NonbondedCUDASkipMsg();
    }


    
    static int recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg) { return idx_recvNonbondedCUDASlaveSkip_NonbondedCUDASkipMsg(); }
    
    static void _call_recvNonbondedCUDASlaveSkip_NonbondedCUDASkipMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvNonbondedCUDASlaveSkip_NonbondedCUDASkipMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvAssignPatchesOnPe_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvAssignPatchesOnPe_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvAssignPatchesOnPe_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvAssignPatchesOnPe(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvAssignPatchesOnPe_DpcppComputeNonbondedMsg();
    }


    
    static int recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvAssignPatchesOnPe_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvAssignPatchesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvAssignPatchesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvSkipPatchesOnPe_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvSkipPatchesOnPe_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvSkipPatchesOnPe_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvSkipPatchesOnPe(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvSkipPatchesOnPe_DpcppComputeNonbondedMsg();
    }


    
    static int recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvSkipPatchesOnPe_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvSkipPatchesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvSkipPatchesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvFinishPatchesOnPe_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvFinishPatchesOnPe_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvFinishPatchesOnPe_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvFinishPatchesOnPe(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvFinishPatchesOnPe_DpcppComputeNonbondedMsg();
    }


    
    static int recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvFinishPatchesOnPe_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvFinishPatchesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvFinishPatchesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvFinishPatchOnPe_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvFinishPatchOnPe_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvFinishPatchOnPe_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvFinishPatchOnPe(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvFinishPatchOnPe_DpcppComputeNonbondedMsg();
    }


    
    static int recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvFinishPatchOnPe_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvFinishPatchOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvFinishPatchOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvOpenBoxesOnPe_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvOpenBoxesOnPe_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvOpenBoxesOnPe_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvOpenBoxesOnPe(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvOpenBoxesOnPe_DpcppComputeNonbondedMsg();
    }


    
    static int recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvOpenBoxesOnPe_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvOpenBoxesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvOpenBoxesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvFinishReductions_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvFinishReductions_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvFinishReductions_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvFinishReductions(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvFinishReductions_DpcppComputeNonbondedMsg();
    }


    
    static int recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvFinishReductions_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvFinishReductions_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvFinishReductions_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvMessageEnqueueWork_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvMessageEnqueueWork_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvMessageEnqueueWork_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvMessageEnqueueWork(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvMessageEnqueueWork_DpcppComputeNonbondedMsg();
    }


    
    static int recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvMessageEnqueueWork_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvMessageEnqueueWork_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvMessageEnqueueWork_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvLaunchWork_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvLaunchWork_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvLaunchWork_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvLaunchWork(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvLaunchWork_DpcppComputeNonbondedMsg();
    }


    
    static int recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvLaunchWork_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvLaunchWork_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvLaunchWork_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvUnregisterBoxesOnPe_DpcppComputeNonbondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvUnregisterBoxesOnPe_DpcppComputeNonbondedMsg() {
      static int epidx = reg_recvUnregisterBoxesOnPe_DpcppComputeNonbondedMsg();
      return epidx;
    }

    
    inline static int idx_recvUnregisterBoxesOnPe(void (ComputeMgr::*)(DpcppComputeNonbondedMsg* impl_msg) ) {
      return idx_recvUnregisterBoxesOnPe_DpcppComputeNonbondedMsg();
    }


    
    static int recvUnregisterBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg) { return idx_recvUnregisterBoxesOnPe_DpcppComputeNonbondedMsg(); }
    
    static void _call_recvUnregisterBoxesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvUnregisterBoxesOnPe_DpcppComputeNonbondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvAssignPatchesOnPe_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvAssignPatchesOnPe_DpcppComputeBondedMsg() {
      static int epidx = reg_recvAssignPatchesOnPe_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvAssignPatchesOnPe(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvAssignPatchesOnPe_DpcppComputeBondedMsg();
    }


    
    static int recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg) { return idx_recvAssignPatchesOnPe_DpcppComputeBondedMsg(); }
    
    static void _call_recvAssignPatchesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvAssignPatchesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvMessageEnqueueWork_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvMessageEnqueueWork_DpcppComputeBondedMsg() {
      static int epidx = reg_recvMessageEnqueueWork_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvMessageEnqueueWork(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvMessageEnqueueWork_DpcppComputeBondedMsg();
    }


    
    static int recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg) { return idx_recvMessageEnqueueWork_DpcppComputeBondedMsg(); }
    
    static void _call_recvMessageEnqueueWork_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvMessageEnqueueWork_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvOpenBoxesOnPe_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvOpenBoxesOnPe_DpcppComputeBondedMsg() {
      static int epidx = reg_recvOpenBoxesOnPe_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvOpenBoxesOnPe(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvOpenBoxesOnPe_DpcppComputeBondedMsg();
    }


    
    static int recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg) { return idx_recvOpenBoxesOnPe_DpcppComputeBondedMsg(); }
    
    static void _call_recvOpenBoxesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvOpenBoxesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvLoadTuplesOnPe_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvLoadTuplesOnPe_DpcppComputeBondedMsg() {
      static int epidx = reg_recvLoadTuplesOnPe_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvLoadTuplesOnPe(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvLoadTuplesOnPe_DpcppComputeBondedMsg();
    }


    
    static int recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg) { return idx_recvLoadTuplesOnPe_DpcppComputeBondedMsg(); }
    
    static void _call_recvLoadTuplesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvLoadTuplesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvLaunchWork_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvLaunchWork_DpcppComputeBondedMsg() {
      static int epidx = reg_recvLaunchWork_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvLaunchWork(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvLaunchWork_DpcppComputeBondedMsg();
    }


    
    static int recvLaunchWork(DpcppComputeBondedMsg* impl_msg) { return idx_recvLaunchWork_DpcppComputeBondedMsg(); }
    
    static void _call_recvLaunchWork_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvLaunchWork_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvFinishPatchesOnPe_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvFinishPatchesOnPe_DpcppComputeBondedMsg() {
      static int epidx = reg_recvFinishPatchesOnPe_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvFinishPatchesOnPe(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvFinishPatchesOnPe_DpcppComputeBondedMsg();
    }


    
    static int recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg) { return idx_recvFinishPatchesOnPe_DpcppComputeBondedMsg(); }
    
    static void _call_recvFinishPatchesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvFinishPatchesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvFinishReductions_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvFinishReductions_DpcppComputeBondedMsg() {
      static int epidx = reg_recvFinishReductions_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvFinishReductions(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvFinishReductions_DpcppComputeBondedMsg();
    }


    
    static int recvFinishReductions(DpcppComputeBondedMsg* impl_msg) { return idx_recvFinishReductions_DpcppComputeBondedMsg(); }
    
    static void _call_recvFinishReductions_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvFinishReductions_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvUnregisterBoxesOnPe_DpcppComputeBondedMsg();
    // Entry point index lookup
    
    inline static int idx_recvUnregisterBoxesOnPe_DpcppComputeBondedMsg() {
      static int epidx = reg_recvUnregisterBoxesOnPe_DpcppComputeBondedMsg();
      return epidx;
    }

    
    inline static int idx_recvUnregisterBoxesOnPe(void (ComputeMgr::*)(DpcppComputeBondedMsg* impl_msg) ) {
      return idx_recvUnregisterBoxesOnPe_DpcppComputeBondedMsg();
    }


    
    static int recvUnregisterBoxesOnPe(DpcppComputeBondedMsg* impl_msg) { return idx_recvUnregisterBoxesOnPe_DpcppComputeBondedMsg(); }
    
    static void _call_recvUnregisterBoxesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvUnregisterBoxesOnPe_DpcppComputeBondedMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvCreateNonbondedMICSlave_NonbondedMICSlaveMsg();
    // Entry point index lookup
    
    inline static int idx_recvCreateNonbondedMICSlave_NonbondedMICSlaveMsg() {
      static int epidx = reg_recvCreateNonbondedMICSlave_NonbondedMICSlaveMsg();
      return epidx;
    }

    
    inline static int idx_recvCreateNonbondedMICSlave(void (ComputeMgr::*)(NonbondedMICSlaveMsg* impl_msg) ) {
      return idx_recvCreateNonbondedMICSlave_NonbondedMICSlaveMsg();
    }


    
    static int recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg) { return idx_recvCreateNonbondedMICSlave_NonbondedMICSlaveMsg(); }
    
    static void _call_recvCreateNonbondedMICSlave_NonbondedMICSlaveMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvCreateNonbondedMICSlave_NonbondedMICSlaveMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5);
     */
    // Entry point registration at startup
    
    static int reg_recvNonbondedMICSlaveReady_marshall44();
    // Entry point index lookup
    
    inline static int idx_recvNonbondedMICSlaveReady_marshall44() {
      static int epidx = reg_recvNonbondedMICSlaveReady_marshall44();
      return epidx;
    }

    
    inline static int idx_recvNonbondedMICSlaveReady(void (ComputeMgr::*)(int impl_noname_3, int impl_noname_4, int impl_noname_5) ) {
      return idx_recvNonbondedMICSlaveReady_marshall44();
    }


    
    static int recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5) { return idx_recvNonbondedMICSlaveReady_marshall44(); }
    
    static void _call_recvNonbondedMICSlaveReady_marshall44(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvNonbondedMICSlaveReady_marshall44(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvNonbondedMICSlaveReady_marshall44(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvNonbondedMICSlaveReady_marshall44(PUP::er &p,void *msg);
    /* DECLS: void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_recvNonbondedMICSlaveSkip_NonbondedMICSkipMsg();
    // Entry point index lookup
    
    inline static int idx_recvNonbondedMICSlaveSkip_NonbondedMICSkipMsg() {
      static int epidx = reg_recvNonbondedMICSlaveSkip_NonbondedMICSkipMsg();
      return epidx;
    }

    
    inline static int idx_recvNonbondedMICSlaveSkip(void (ComputeMgr::*)(NonbondedMICSkipMsg* impl_msg) ) {
      return idx_recvNonbondedMICSlaveSkip_NonbondedMICSkipMsg();
    }


    
    static int recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg) { return idx_recvNonbondedMICSlaveSkip_NonbondedMICSkipMsg(); }
    
    static void _call_recvNonbondedMICSlaveSkip_NonbondedMICSkipMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvNonbondedMICSlaveSkip_NonbondedMICSkipMsg(void* impl_msg, void* impl_obj);
    /* DECLS: void recvMICPEData(int impl_noname_6, int impl_noname_7);
     */
    // Entry point registration at startup
    
    static int reg_recvMICPEData_marshall46();
    // Entry point index lookup
    
    inline static int idx_recvMICPEData_marshall46() {
      static int epidx = reg_recvMICPEData_marshall46();
      return epidx;
    }

    
    inline static int idx_recvMICPEData(void (ComputeMgr::*)(int impl_noname_6, int impl_noname_7) ) {
      return idx_recvMICPEData_marshall46();
    }


    
    static int recvMICPEData(int impl_noname_6, int impl_noname_7) { return idx_recvMICPEData_marshall46(); }
    
    static void _call_recvMICPEData_marshall46(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_recvMICPEData_marshall46(void* impl_msg, void* impl_obj);
    
    static int _callmarshall_recvMICPEData_marshall46(char* impl_buf, void* impl_obj_void);
    
    static void _marshallmessagepup_recvMICPEData_marshall46(PUP::er &p,void *msg);
};
/* --------------- element proxy ------------------ */
class CProxyElement_ComputeMgr: public CProxyElement_IrrGroup{
  public:
    typedef ComputeMgr local_t;
    typedef CkIndex_ComputeMgr index_t;
    typedef CProxy_ComputeMgr proxy_t;
    typedef CProxyElement_ComputeMgr element_t;
    typedef CProxySection_ComputeMgr section_t;


    /* TRAM aggregators */

    CProxyElement_ComputeMgr(void) {
    }
    CProxyElement_ComputeMgr(const IrrGroup *g) : CProxyElement_IrrGroup(g){
    }
    CProxyElement_ComputeMgr(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_IrrGroup(_gid,_onPE,CK_DELCTOR_ARGS){
    }
    CProxyElement_ComputeMgr(CkGroupID _gid,int _onPE) : CProxyElement_IrrGroup(_gid,_onPE){
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
    ComputeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static ComputeMgr* ckLocalBranch(CkGroupID gID) {
      return (ComputeMgr*)CkLocalBranch(gID);
    }
/* DECLS: ComputeMgr();
 */
    

/* DECLS: void updateComputes2(CkQdMsg* impl_msg);
 */
    
    void updateComputes2(CkQdMsg* impl_msg);

/* DECLS: void updateComputes3();
 */
    
    void updateComputes3(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void splitComputes();
 */
    
    void splitComputes(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void splitComputes2(CkQdMsg* impl_msg);
 */
    
    void splitComputes2(CkQdMsg* impl_msg);

/* DECLS: void updateLocalComputes();
 */
    
    void updateLocalComputes(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateLocalComputes2(CkQdMsg* impl_msg);
 */
    
    void updateLocalComputes2(CkQdMsg* impl_msg);

/* DECLS: void updateLocalComputes3();
 */
    
    void updateLocalComputes3(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateLocalComputes4(CkQdMsg* impl_msg);
 */
    
    void updateLocalComputes4(CkQdMsg* impl_msg);

/* DECLS: void updateLocalComputes5();
 */
    
    void updateLocalComputes5(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void doneUpdateLocalComputes();
 */
    
    void doneUpdateLocalComputes(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);
 */
    
    void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);

/* DECLS: void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);
 */
    
    void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);

/* DECLS: void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);
 */
    
    void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);

/* DECLS: void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);
 */
    
    void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);

/* DECLS: void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);
 */
    
    void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);

/* DECLS: void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);
 */
    
    void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);

/* DECLS: void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);
 */
    
    void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);

/* DECLS: void recvYieldDevice(int pe);
 */
    
    void recvYieldDevice(int pe, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildCudaExclusions();
 */
    
    void recvBuildCudaExclusions(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildCudaForceTable();
 */
    
    void recvBuildCudaForceTable(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildMICForceTable();
 */
    
    void recvBuildMICForceTable(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);
 */
    
    void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);

/* DECLS: void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2);
 */
    
    void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);
 */
    
    void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);

/* DECLS: void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvUnregisterBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);

/* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvUnregisterBoxesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);
 */
    
    void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);

/* DECLS: void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5);
 */
    
    void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);
 */
    
    void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);

/* DECLS: void recvMICPEData(int impl_noname_6, int impl_noname_7);
 */
    
    void recvMICPEData(int impl_noname_6, int impl_noname_7, const CkEntryOptions *impl_e_opts=NULL);

};
PUPmarshall(CProxyElement_ComputeMgr)
/* ---------------- collective proxy -------------- */
class CProxy_ComputeMgr: public CProxy_IrrGroup{
  public:
    typedef ComputeMgr local_t;
    typedef CkIndex_ComputeMgr index_t;
    typedef CProxy_ComputeMgr proxy_t;
    typedef CProxyElement_ComputeMgr element_t;
    typedef CProxySection_ComputeMgr section_t;

    CProxy_ComputeMgr(void) {
    }
    CProxy_ComputeMgr(const IrrGroup *g) : CProxy_IrrGroup(g){
    }
    CProxy_ComputeMgr(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_IrrGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_ComputeMgr(CkGroupID _gid) : CProxy_IrrGroup(_gid){  }
    CProxyElement_ComputeMgr operator[](int onPE) const
      {return CProxyElement_ComputeMgr(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

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
    ComputeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static ComputeMgr* ckLocalBranch(CkGroupID gID) {
      return (ComputeMgr*)CkLocalBranch(gID);
    }
/* DECLS: ComputeMgr();
 */
    
    static CkGroupID ckNew(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateComputes2(CkQdMsg* impl_msg);
 */
    
    void updateComputes2(CkQdMsg* impl_msg);
    
    void updateComputes2(CkQdMsg* impl_msg, int npes, int *pes);
    
    void updateComputes2(CkQdMsg* impl_msg, CmiGroup &grp);

/* DECLS: void updateComputes3();
 */
    
    void updateComputes3(const CkEntryOptions *impl_e_opts=NULL);
    
    void updateComputes3(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void updateComputes3(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void splitComputes();
 */
    
    void splitComputes(const CkEntryOptions *impl_e_opts=NULL);
    
    void splitComputes(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void splitComputes(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void splitComputes2(CkQdMsg* impl_msg);
 */
    
    void splitComputes2(CkQdMsg* impl_msg);
    
    void splitComputes2(CkQdMsg* impl_msg, int npes, int *pes);
    
    void splitComputes2(CkQdMsg* impl_msg, CmiGroup &grp);

/* DECLS: void updateLocalComputes();
 */
    
    void updateLocalComputes(const CkEntryOptions *impl_e_opts=NULL);
    
    void updateLocalComputes(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void updateLocalComputes(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateLocalComputes2(CkQdMsg* impl_msg);
 */
    
    void updateLocalComputes2(CkQdMsg* impl_msg);
    
    void updateLocalComputes2(CkQdMsg* impl_msg, int npes, int *pes);
    
    void updateLocalComputes2(CkQdMsg* impl_msg, CmiGroup &grp);

/* DECLS: void updateLocalComputes3();
 */
    
    void updateLocalComputes3(const CkEntryOptions *impl_e_opts=NULL);
    
    void updateLocalComputes3(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void updateLocalComputes3(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateLocalComputes4(CkQdMsg* impl_msg);
 */
    
    void updateLocalComputes4(CkQdMsg* impl_msg);
    
    void updateLocalComputes4(CkQdMsg* impl_msg, int npes, int *pes);
    
    void updateLocalComputes4(CkQdMsg* impl_msg, CmiGroup &grp);

/* DECLS: void updateLocalComputes5();
 */
    
    void updateLocalComputes5(const CkEntryOptions *impl_e_opts=NULL);
    
    void updateLocalComputes5(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void updateLocalComputes5(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void doneUpdateLocalComputes();
 */
    
    void doneUpdateLocalComputes(const CkEntryOptions *impl_e_opts=NULL);
    
    void doneUpdateLocalComputes(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void doneUpdateLocalComputes(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);
 */
    
    void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);
    
    void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg, int npes, int *pes);
    
    void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);
 */
    
    void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);
    
    void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg, int npes, int *pes);
    
    void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);
 */
    
    void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);
    
    void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg, int npes, int *pes);
    
    void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);
 */
    
    void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);
    
    void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg, int npes, int *pes);
    
    void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);
 */
    
    void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);
    
    void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg, int npes, int *pes);
    
    void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);
 */
    
    void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);
    
    void recvComputeEwaldData(ComputeEwaldMsg* impl_msg, int npes, int *pes);
    
    void recvComputeEwaldData(ComputeEwaldMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);
 */
    
    void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);
    
    void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg, int npes, int *pes);
    
    void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvYieldDevice(int pe);
 */
    
    void recvYieldDevice(int pe, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvYieldDevice(int pe, int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvYieldDevice(int pe, CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildCudaExclusions();
 */
    
    void recvBuildCudaExclusions(const CkEntryOptions *impl_e_opts=NULL);
    
    void recvBuildCudaExclusions(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvBuildCudaExclusions(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildCudaForceTable();
 */
    
    void recvBuildCudaForceTable(const CkEntryOptions *impl_e_opts=NULL);
    
    void recvBuildCudaForceTable(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvBuildCudaForceTable(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildMICForceTable();
 */
    
    void recvBuildMICForceTable(const CkEntryOptions *impl_e_opts=NULL);
    
    void recvBuildMICForceTable(int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvBuildMICForceTable(CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);
 */
    
    void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);
    
    void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg, int npes, int *pes);
    
    void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2);
 */
    
    void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2, int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2, CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);
 */
    
    void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);
    
    void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg, int npes, int *pes);
    
    void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);
    
    void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg, int npes, int *pes);
    
    void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */

/* DECLS: void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
    
    void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg, int npes, int *pes);
    
    void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);
    
    void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg, int npes, int *pes);
    
    void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
    
    void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg, int npes, int *pes);
    
    void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);
    
    void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg, int npes, int *pes);
    
    void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);
    
    void recvLaunchWork(DpcppComputeBondedMsg* impl_msg, int npes, int *pes);
    
    void recvLaunchWork(DpcppComputeBondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
    
    void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg, int npes, int *pes);
    
    void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);
    
    void recvFinishReductions(DpcppComputeBondedMsg* impl_msg, int npes, int *pes);
    
    void recvFinishReductions(DpcppComputeBondedMsg* impl_msg, CmiGroup &grp);

/* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
 */

/* DECLS: void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);
 */
    
    void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);
    
    void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg, int npes, int *pes);
    
    void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5);
 */
    
    void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5, int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5, CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);
 */
    
    void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);
    
    void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg, int npes, int *pes);
    
    void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg, CmiGroup &grp);

/* DECLS: void recvMICPEData(int impl_noname_6, int impl_noname_7);
 */
    
    void recvMICPEData(int impl_noname_6, int impl_noname_7, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvMICPEData(int impl_noname_6, int impl_noname_7, int npes, int *pes, const CkEntryOptions *impl_e_opts=NULL);
    
    void recvMICPEData(int impl_noname_6, int impl_noname_7, CmiGroup &grp, const CkEntryOptions *impl_e_opts=NULL);

};
PUPmarshall(CProxy_ComputeMgr)
/* ---------------- section proxy -------------- */
class CProxySection_ComputeMgr: public CProxySection_IrrGroup{
  public:
    typedef ComputeMgr local_t;
    typedef CkIndex_ComputeMgr index_t;
    typedef CProxy_ComputeMgr proxy_t;
    typedef CProxyElement_ComputeMgr element_t;
    typedef CProxySection_ComputeMgr section_t;

    CProxySection_ComputeMgr(void) {
    }
    CProxySection_ComputeMgr(const IrrGroup *g) : CProxySection_IrrGroup(g){
    }
    CProxySection_ComputeMgr(const CkGroupID &_gid,const int *_pelist,int _npes, CK_DELCTOR_PARAM) : CProxySection_IrrGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_ComputeMgr(const CkGroupID &_gid,const int *_pelist,int _npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_IrrGroup(_gid,_pelist,_npes,factor){  }
    CProxySection_ComputeMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, int factor = USE_DEFAULT_BRANCH_FACTOR) : CProxySection_IrrGroup(n,_gid,_pelist,_npes,factor){  }
    CProxySection_ComputeMgr(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes, CK_DELCTOR_PARAM) : CProxySection_IrrGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

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
    ComputeMgr* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static ComputeMgr* ckLocalBranch(CkGroupID gID) {
      return (ComputeMgr*)CkLocalBranch(gID);
    }
/* DECLS: ComputeMgr();
 */
    

/* DECLS: void updateComputes2(CkQdMsg* impl_msg);
 */
    
    void updateComputes2(CkQdMsg* impl_msg);

/* DECLS: void updateComputes3();
 */
    
    void updateComputes3(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void splitComputes();
 */
    
    void splitComputes(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void splitComputes2(CkQdMsg* impl_msg);
 */
    
    void splitComputes2(CkQdMsg* impl_msg);

/* DECLS: void updateLocalComputes();
 */
    
    void updateLocalComputes(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateLocalComputes2(CkQdMsg* impl_msg);
 */
    
    void updateLocalComputes2(CkQdMsg* impl_msg);

/* DECLS: void updateLocalComputes3();
 */
    
    void updateLocalComputes3(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void updateLocalComputes4(CkQdMsg* impl_msg);
 */
    
    void updateLocalComputes4(CkQdMsg* impl_msg);

/* DECLS: void updateLocalComputes5();
 */
    
    void updateLocalComputes5(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void doneUpdateLocalComputes();
 */
    
    void doneUpdateLocalComputes(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);
 */
    
    void recvComputeGlobalData(ComputeGlobalDataMsg* impl_msg);

/* DECLS: void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);
 */
    
    void recvComputeGlobalResults(ComputeGlobalResultsMsg* impl_msg);

/* DECLS: void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);
 */
    
    void recvComputeDPMEData(ComputeDPMEDataMsg* impl_msg);

/* DECLS: void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);
 */
    
    void recvComputeDPMEResults(ComputeDPMEResultsMsg* impl_msg);

/* DECLS: void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);
 */
    
    void recvComputeConsForceMsg(ComputeConsForceMsg* impl_msg);

/* DECLS: void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);
 */
    
    void recvComputeEwaldData(ComputeEwaldMsg* impl_msg);

/* DECLS: void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);
 */
    
    void recvComputeEwaldResults(ComputeEwaldMsg* impl_msg);

/* DECLS: void recvYieldDevice(int pe);
 */
    
    void recvYieldDevice(int pe, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildCudaExclusions();
 */
    
    void recvBuildCudaExclusions(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildCudaForceTable();
 */
    
    void recvBuildCudaForceTable(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvBuildMICForceTable();
 */
    
    void recvBuildMICForceTable(const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);
 */
    
    void recvCreateNonbondedCUDASlave(NonbondedCUDASlaveMsg* impl_msg);

/* DECLS: void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2);
 */
    
    void recvNonbondedCUDASlaveReady(int impl_noname_0, int impl_noname_1, int impl_noname_2, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);
 */
    
    void recvNonbondedCUDASlaveSkip(NonbondedCUDASkipMsg* impl_msg);

/* DECLS: void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvAssignPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvSkipPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishPatchesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishPatchOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvOpenBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvFinishReductions(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvMessageEnqueueWork(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);
 */
    
    void recvLaunchWork(DpcppComputeNonbondedMsg* impl_msg);

/* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeNonbondedMsg* impl_msg);
 */

/* DECLS: void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvAssignPatchesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvMessageEnqueueWork(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvOpenBoxesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvLoadTuplesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvLaunchWork(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvFinishPatchesOnPe(DpcppComputeBondedMsg* impl_msg);

/* DECLS: void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);
 */
    
    void recvFinishReductions(DpcppComputeBondedMsg* impl_msg);

/* DECLS: sync void recvUnregisterBoxesOnPe(DpcppComputeBondedMsg* impl_msg);
 */

/* DECLS: void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);
 */
    
    void recvCreateNonbondedMICSlave(NonbondedMICSlaveMsg* impl_msg);

/* DECLS: void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5);
 */
    
    void recvNonbondedMICSlaveReady(int impl_noname_3, int impl_noname_4, int impl_noname_5, const CkEntryOptions *impl_e_opts=NULL);

/* DECLS: void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);
 */
    
    void recvNonbondedMICSlaveSkip(NonbondedMICSkipMsg* impl_msg);

/* DECLS: void recvMICPEData(int impl_noname_6, int impl_noname_7);
 */
    
    void recvMICPEData(int impl_noname_6, int impl_noname_7, const CkEntryOptions *impl_e_opts=NULL);

};
PUPmarshall(CProxySection_ComputeMgr)
#define ComputeMgr_SDAG_CODE 
typedef CBaseT1<Group, CProxy_ComputeMgr>CBase_ComputeMgr;













/* ---------------- method closures -------------- */
class Closure_ComputeMgr {
  public:



    struct updateComputes3_3_closure;


    struct splitComputes_4_closure;



    struct updateLocalComputes_6_closure;



    struct updateLocalComputes3_8_closure;



    struct updateLocalComputes5_10_closure;


    struct doneUpdateLocalComputes_11_closure;









    struct recvYieldDevice_19_closure;


    struct recvBuildCudaExclusions_20_closure;


    struct recvBuildCudaForceTable_21_closure;


    struct recvBuildMICForceTable_22_closure;



    struct recvNonbondedCUDASlaveReady_24_closure;





















    struct recvNonbondedMICSlaveReady_44_closure;



    struct recvMICPEData_46_closure;

};

extern void _registerComputeMgr(void);
#endif
