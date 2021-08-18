    AC_TAG("repackTileListsKernel range:"+std::to_string(rangeSize)+" workgroup:"+std::to_string(workGroupSize));
    AC_DEVICE(myQ, "pre_repacktilelistskernel", tileListPos, tileListPosSize);
//    AC_DEVICE(myQ, "pre_repacktilelistskernel", tileListOrderDst.ptr,numTileListsDst);
    if(useJtiles) AC_DEVICE(myQ, "pre_repacktilelistskernel", jtiles, jtilesSize);

//    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel_offsetXYZ",tileListsSrc.ptr, tileListsSrc.size, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
//    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel_ints", tileListsSrc.ptr, tileListsSrc.size, int, 8, 
//      AC_ADD(iatomStart);AC_ADD(jtileStart);
//      AC_ADD(jtileEnd);AC_ADD(patchInd[0]);
//      AC_ADD(patchInd[1]);AC_ADD(patchNumList[0]);
//      AC_ADD(patchNumList[1]);AC_ADD(icompute););

// This is an output, no need to compare before
//    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel_offsetXYZ", tileListsDst.ptr, tileListsDst.size, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
//    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel_ints", tileListsDst.ptr, tileListsDst.size, int, 8, 
//      AC_ADD(iatomStart);AC_ADD(jtileStart);
//      AC_ADD(jtileEnd);AC_ADD(patchInd[0]);
//      AC_ADD(patchInd[1]);AC_ADD(patchNumList[0]);
//      AC_ADD(patchNumList[1]);AC_ADD(icompute););

    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel", patchPairsSrc.ptr, patchPairsSrc.size, int, 4, 
      AC_ADD(iatomSize);AC_ADD(iatomFreeSize);
      AC_ADD(jatomSize);AC_ADD(jatomFreeSize););
//    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel", patchPairsDst.ptr, patchPairsDst.size, int, 4, 
//      AC_ADD(iatomSize);AC_ADD(iatomFreeSize);
//      AC_ADD(jatomSize);AC_ADD(jatomFreeSize););
//    AC_DEVICE(myQ, "pre_repacktilelistskernel", tileJatomStartSrc.ptr, tileJatomStartSrc.size);
//    AC_DEVICE(myQ, "pre_repacktilelistskernel", tileJatomStartDst.ptr, tileJatomStartDst.size);
    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel", tileExclsSrc.ptr, tileExclsSrc.size,
                         unsigned int, AVXSIZE, for(int j=0;j<AVXSIZE;j++){AC_ADD(excl[j]);}); 
//    AC_DEVICE_STRUCT(myQ, "pre_repacktilelistskernel", tileExclsDst.ptr, tileExclsDst.size,
//                         unsigned int, AVXSIZE, for(int j=0;j<AVXSIZE;j++){AC_ADD(excl[j]);}); 


