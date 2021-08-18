    AC_DEVICE_STRUCT(myQ, "post_repacktilelistskernel_offsetXYZ", tileListsDst.ptr, tileListsDst.size, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
    AC_DEVICE_STRUCT(myQ, "post_repacktilelistskernel_ints", tileListsDst.ptr, tileListsDst.size, int, 8, 
      AC_ADD(iatomStart);AC_ADD(jtileStart);
      AC_ADD(jtileEnd);AC_ADD(patchInd[0]);
      AC_ADD(patchInd[1]);AC_ADD(patchNumList[0]);
      AC_ADD(patchNumList[1]);AC_ADD(icompute););
    AC_DEVICE_STRUCT(myQ, "post_repacktilelistskernel", patchPairsDst.ptr, patchPairsDst.size, int, 4, 
      AC_ADD(iatomSize);AC_ADD(iatomFreeSize);
      AC_ADD(jatomSize);AC_ADD(jatomFreeSize););
    if (tileJatomStartDst.size) AC_DEVICE(myQ, "post_repacktilelistskernel", tileJatomStartDst.ptr, tileJatomStartDst.size);
    AC_DEVICE_STRUCT(myQ, "post_repacktilelistskernel", tileExclsDst.ptr, tileExclsDst.size,
                         unsigned int, AVXSIZE, for(int j=0;j<AVXSIZE;j++){AC_ADD(excl[j]);}); 
