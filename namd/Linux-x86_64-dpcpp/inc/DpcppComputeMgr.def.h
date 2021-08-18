/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */


/* DEFS: nodegroup DpcppComputeMgr: NodeGroup{
DpcppComputeMgr();
void initialize(CkQdMsg* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_DpcppComputeMgr::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputeMgr();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initialize(CkQdMsg* impl_msg);
 */
void CProxyElement_DpcppComputeMgr::initialize(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupSend(ckDelegatedPtr(),CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else {
    CkSendMsgNodeBranch(CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputeMgr();
 */
CkGroupID CProxy_DpcppComputeMgr::ckNew(const CkEntryOptions *impl_e_opts)
{
  void *impl_msg = CkAllocSysMsg(impl_e_opts);
  UsrToEnv(impl_msg)->setMsgtype(NodeBocInitMsg);
  CkGroupID gId = CkCreateNodeGroup(CkIndex_DpcppComputeMgr::__idx, CkIndex_DpcppComputeMgr::idx_DpcppComputeMgr_void(), impl_msg);
  return gId;
}

// Entry point registration function
int CkIndex_DpcppComputeMgr::reg_DpcppComputeMgr_void() {
  int epidx = CkRegisterEp("DpcppComputeMgr()",
      _call_DpcppComputeMgr_void, 0, __idx, 0);
  return epidx;
}

void CkIndex_DpcppComputeMgr::_call_DpcppComputeMgr_void(void* impl_msg, void* impl_obj_void)
{
  DpcppComputeMgr* impl_obj = static_cast<DpcppComputeMgr*>(impl_obj_void);
  new (impl_obj_void) DpcppComputeMgr();
  if(UsrToEnv(impl_msg)->isVarSysMsg() == 0)
    CkFreeSysMsg(impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initialize(CkQdMsg* impl_msg);
 */
void CProxy_DpcppComputeMgr::initialize(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkNodeGroupMsgPrep(CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->NodeGroupBroadcast(ckDelegatedPtr(),CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgNodeBranch(CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg, ckGetGroupID(),0);
}

// Entry point registration function
int CkIndex_DpcppComputeMgr::reg_initialize_CkQdMsg() {
  int epidx = CkRegisterEp("initialize(CkQdMsg* impl_msg)",
      _call_initialize_CkQdMsg, CMessage_CkQdMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)CkQdMsg::ckDebugPup);
  return epidx;
}

void CkIndex_DpcppComputeMgr::_call_initialize_CkQdMsg(void* impl_msg, void* impl_obj_void)
{
  DpcppComputeMgr* impl_obj = static_cast<DpcppComputeMgr*>(impl_obj_void);
  impl_obj->initialize((CkQdMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: DpcppComputeMgr();
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void initialize(CkQdMsg* impl_msg);
 */
void CProxySection_DpcppComputeMgr::initialize(CkQdMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     ckDelegatedTo()->NodeGroupSectionSend(ckDelegatedPtr(),CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgNodeBranchMulti(CkIndex_DpcppComputeMgr::idx_initialize_CkQdMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_DpcppComputeMgr::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeGroup);
  CkRegisterBase(__idx, CkIndex_NodeGroup::__idx);
   CkRegisterGroupIrr(__idx,DpcppComputeMgr::isIrreducible());
  // REG: DpcppComputeMgr();
  idx_DpcppComputeMgr_void();
  CkRegisterDefaultCtor(__idx, idx_DpcppComputeMgr_void());

  // REG: void initialize(CkQdMsg* impl_msg);
  idx_initialize_CkQdMsg();

}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
void _registerDpcppComputeMgr(void)
{
  static int _done = 0; if(_done) return; _done = 1;
/* REG: nodegroup DpcppComputeMgr: NodeGroup{
DpcppComputeMgr();
void initialize(CkQdMsg* impl_msg);
};
*/
  CkIndex_DpcppComputeMgr::__register("DpcppComputeMgr", sizeof(DpcppComputeMgr));

}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_DpcppComputeMgr::virtual_pup(PUP::er &p) {
    recursive_pup<DpcppComputeMgr>(dynamic_cast<DpcppComputeMgr*>(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
