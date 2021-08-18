    AC_DEVICE_STRUCT(myQ, "post_buildtilelistsbbkernel_offsetXYZ", tileLists1, tileLists1Size, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
// Comparing the following two cases is limited due to the random order from the atomic add
//    AC_DEVICE_STRUCT(myQ, "post_buildtilelistsbbkernel_ints", tileLists1, tileLists1Size, int, 8, 
//      AC_ADD(iatomStart);AC_ADD(jtileStart);
//      AC_ADD(jtileEnd);AC_ADD(patchInd[0]);
//      AC_ADD(patchInd[1]);AC_ADD(patchNumList[0]);
//      AC_ADD(patchNumList[1]);AC_ADD(icompute););
//    AC_DEVICE(myQ, "post_buildtilelistsbbkernel", tileJatomStart1, tileJatomStart1Size);
    AC_DEVICE(myQ, "post_buildtilelistsbbkernel", tileListDepth1, tileListDepth1Size);
    AC_DEVICE(myQ, "post_buildtilelistsbbkernel", tileListOrder1, tileListOrder1Size);
    AC_DEVICE_STRUCT(myQ, "post_buildtilelistsbbkernel", patchPairs1, patchPairs1Size, int, 4, 
      AC_ADD(iatomSize);AC_ADD(iatomFreeSize);
      AC_ADD(jatomSize);AC_ADD(jatomFreeSize););
    AC_DEVICE_STRUCT(myQ, "post_buildtilelistsbbkernel", d_tileListStat, 1, int, 6, 
      AC_ADD(numTileLists); AC_ADD(numTileListsGBIS); AC_ADD(numJtiles);
      AC_ADD(numExcluded); AC_ADD(patchReadyQueueCount); AC_ADD(outputOrderIndex););


