    AC_TAG("buildtilelistsbbkernel_range"+std::to_string(rangeSize)+"_workgroup"+std::to_string(workGroupSize));

    AC_DEVICE_STRUCT(myQ, "pre_buildtilelistsbbkernel_offsetXYZ", tileLists1, tileLists1Size, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
    AC_DEVICE_STRUCT(myQ, "pre_buildtilelistsbbkernel_ints", tileLists1, tileLists1Size, int, 8, 
      AC_ADD(iatomStart);AC_ADD(jtileStart);
      AC_ADD(jtileEnd);AC_ADD(patchInd[0]);
      AC_ADD(patchInd[1]);AC_ADD(patchNumList[0]);
      AC_ADD(patchNumList[1]);AC_ADD(icompute););
    auto &cudaPatches = dpcppPatches;
    AC_DEVICE_STRUCT(myQ, "pre_buildtilelistsbbkernel", cudaPatches, numPatches, int, 3, AC_ADD(numAtoms);AC_ADD(numFreeAtoms);AC_ADD(atomStart););
    AC_DEVICE(myQ, "pre_buildtilelistsbbkernel", tilePos, tilePosSize);
    AC_DEVICE_STRUCT(myQ, "pre_buildtilelistsbbkernel", boundingBoxes, boundingBoxesSize, float, 6,
      AC_ADD(xyz.x());AC_ADD(xyz.y());
      AC_ADD(xyz.z());AC_ADD(wxyz.x());
      AC_ADD(wxyz.y());AC_ADD(wxyz.z()););
    AC_DEVICE(myQ, "pre_buildtilelistsbbkernel", tileJatomStart1, tileJatomStart1Size);
    AC_DEVICE(myQ, "pre_buildtilelistsbbkernel", tileListDepth1, tileListDepth1Size);
    AC_DEVICE(myQ, "pre_buildtilelistsbbkernel", tileListOrder1, tileListOrder1Size);
    AC_DEVICE_STRUCT(myQ, "pre_buildtilelistsbbkernel", patchPairs1, patchPairs1Size, int, 4, 
      AC_ADD(iatomSize);AC_ADD(iatomFreeSize);
      AC_ADD(jatomSize);AC_ADD(jatomFreeSize););
    AC_DEVICE_STRUCT(myQ, "pre_buildtilelistsbbkernel", d_tileListStat, 1, int, 6, 
      AC_ADD(numTileLists); AC_ADD(numTileListsGBIS); AC_ADD(numJtiles);
      AC_ADD(numExcluded); AC_ADD(patchReadyQueueCount); AC_ADD(outputOrderIndex););


