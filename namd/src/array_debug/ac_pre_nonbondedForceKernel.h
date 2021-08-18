  AC_TAG("nonbondedForceKernel_range");
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel_offsetXYZ", tlKernel.getTileLists(), numTileLists, float, 3, AC_ADD(offsetXYZ[0]);AC_ADD(offsetXYZ[1]);AC_ADD(offsetXYZ[2]););
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel_ints",tlKernel.getTileLists(), numTileLists, int, 8, 
    AC_ADD(iatomStart);AC_ADD(jtileStart);
    AC_ADD(jtileEnd);AC_ADD(patchInd[0]);
    AC_ADD(patchInd[1]);AC_ADD(patchNumList[0]);
    AC_ADD(patchNumList[1]);AC_ADD(icompute););

  AC_DEVICE_STRUCT     (myQ, "pre_nonbondedforcekernel", tlKernel.getTileExcls(), tlKernel.getTileExclsSize(),
                       unsigned int, AVXSIZE, for(int j=0;j<AVXSIZE;j++)AC_ADD(excl[j]);); 
// Currenlty not possible to compare

  auto *nonbondedTables_VdwCoefTable = dpcppNonbondedTables.getVdwCoefTable();
  AC_DEVICE_FLOAT2(myQ, "pre_nonbondedforcekernel", nonbondedTables_VdwCoefTable, dpcppNonbondedTables.getVdwCoefTableWidth()*dpcppNonbondedTables.getVdwCoefTableWidth());

  AC_DEVICE(myQ, "pre_nonbondedforcekernel", vdwTypes, atomStorageSize);
  

  AC_DEVICE_FLOAT4(myQ, "pre_nonbondedforcekernel", tlKernel.get_xyzq(), atomStorageSize);
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel", tlKernel.getPatchPairs(), tlKernel.getPatchPairsSize(), int, 4, 
    AC_ADD(iatomSize);AC_ADD(iatomFreeSize);AC_ADD(jatomSize);AC_ADD(jatomFreeSize););
  AC_DEVICE(myQ, "pre_nonbondedforcekernel", atomIndex, atomStorageSize);
  AC_DEVICE_INT2(myQ, "pre_nonbondedforcekernel", exclIndexMaxDiff, exclIndexMaxDiffSize);
  AC_DEVICE(myQ, "pre_nonbondedforcekernel", overflowExclusions, overflowExclusionsSize);
  AC_DEVICE(myQ, "pre_nonbondedforcekernel",tlKernel.getTileListDepth(), tlKernel.getNumTileLists());//tlKernel.getTileListDepthSize());
  AC_DEVICE(myQ, "pre_nonbondedforcekernel",tlKernel.getTileListOrder(), tlKernel.getNumTileLists());// tlKernel.getTileListOrderSize());
  AC_DEVICE(myQ, "pre_nonbondedforcekernel",tlKernel.getJtiles(), tlKernel.getJtilesSize());
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel", tlKernel.getTileListStatDevPtr(), 1, int, 6, 
    AC_ADD(numTileLists); AC_ADD(numTileListsGBIS); AC_ADD(numJtiles);
    AC_ADD(numExcluded); AC_ADD(patchReadyQueueCount); AC_ADD(outputOrderIndex););
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel",tlKernel.getBoundingBoxes(), tlKernel.getBoundingBoxesSize(), float, 6,
    AC_ADD(xyz.x());AC_ADD(xyz.y());AC_ADD(xyz.z());AC_ADD(wxyz.x());AC_ADD(wxyz.y());AC_ADD(wxyz.z()););
  AC_DEVICE_FLOAT4(myQ, "pre_nonbondedforcekernel", d_forces, atomStorageSize);
  AC_DEVICE_FLOAT4(myQ, "pre_nonbondedforcekernel", d_forcesSlow, atomStorageSize);
  AC_DEVICE(myQ, "pre_nonbondedforcekernel",patchNumCountPtr, numPatches);
  auto *tlKernel_getPatches =tlKernel.getDpcppPatches();
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel", tlKernel_getPatches, tlKernel.getDpcppPatchesSize(), int, 3, AC_ADD(numAtoms);AC_ADD(numFreeAtoms);AC_ADD(atomStart););
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel_floats", tlKernel.getTileListVirialEnergy(), tlKernel.getTileListVirialEnergySize(), float, 9, AC_ADD(sh.x());AC_ADD(sh.y());AC_ADD(sh.z());AC_ADD(force.x());AC_ADD(force.y());AC_ADD(force.z());AC_ADD(forceSlow.x());AC_ADD(forceSlow.y());AC_ADD(forceSlow.z()););
  AC_DEVICE_STRUCT(myQ, "pre_nonbondedforcekernel_doubles", tlKernel.getTileListVirialEnergy(), tlKernel.getTileListVirialEnergySize(), double, 4, AC_ADD(energyVdw);AC_ADD(energyElec);AC_ADD(energySlow);AC_ADD(energyGBIS););
 

