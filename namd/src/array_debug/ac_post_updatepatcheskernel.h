    AC_DEVICE_STRUCT(myQ, "post_updatepatcheskernel_patchInd", cudaComputes, numComputes, int, 2, AC_ADD(patchInd[0]);AC_ADD(patchInd[1]););
    AC_DEVICE_STRUCT(myQ, "post_updatepatcheskernel_offsetXYZ", cudaComputes, numComputes, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
    AC_DEVICE_STRUCT(myQ, "post_updatepatcheskernel", cudaPatches, numPatches, int, 3, AC_ADD(numAtoms);AC_ADD(numFreeAtoms);AC_ADD(atomStart););
    AC_DEVICE(myQ, "post_updatepatcheskernel", tilePos, tilePosSize);
    AC_DEVICE_STRUCT(myQ, "post_updatepatcheskernel_offsetXYZ", tileLists1, tileLists1Size, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
    AC_DEVICE_STRUCT(myQ, "post_updatepatcheskernel_ints", tileLists1, tileLists1Size, int, 8, 
      AC_ADD(iatomStart);AC_ADD(jtileStart);
      AC_ADD(jtileEnd);AC_ADD(patchInd[0]);
      AC_ADD(patchInd[1]);AC_ADD(patchNumList[0]);
      AC_ADD(patchNumList[1]);AC_ADD(icompute););


