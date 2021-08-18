      AC_TAG("calcTileListPosKernel");
      auto &cudaComputes = dpcppComputes;
      AC_DEVICE_STRUCT(myQ, "pre_tilelistposkernel_patchInd", cudaComputes, numComputes, int, 2, AC_ADD(patchInd[0]);AC_ADD(patchInd[1]););
      AC_DEVICE_STRUCT(myQ, "pre_tilelistposkernel_offsetXYZ", cudaComputes, numComputes, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
     auto &cudaPatches = dpcppPatches;
      AC_DEVICE_STRUCT(myQ, "pre_tilelistposkernel", cudaPatches, numPatches, int, 3, AC_ADD(numAtoms);AC_ADD(numFreeAtoms);AC_ADD(atomStart););
 
