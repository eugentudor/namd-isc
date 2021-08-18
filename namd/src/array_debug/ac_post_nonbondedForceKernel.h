//    AC_TAG("POST nonbondedForceKernel");
    AC_DEVICE_STRUCT(myQ, "post_nonbondedforcekernel", tlKernel.getTileExcls(), tlKernel.getTileExclsSize(),
                         unsigned int, AVXSIZE, for(int j=0;j<AVXSIZE;j++)AC_ADD(excl[j]);); 
    AC_DEVICE(myQ, "post_nonbondedforcekernel",tlKernel.getTileListDepth(), tlKernel.getNumTileLists());//tlKernel.getTileListDepthSize());
    AC_DEVICE(myQ, "post_nonbondedforcekernel",tlKernel.getTileListOrder(), tlKernel.getNumTileLists());//tlKernel.getTileListOrderSize());
    AC_DEVICE(myQ, "post_nonbondedforcekernel",tlKernel.getJtiles(), tlKernel.getJtilesSize());
    AC_DEVICE_STRUCT(myQ, "post_nonbondedforcekernel", tlKernel.getTileListStatDevPtr(), 1, int, 6, 
      AC_ADD(numTileLists); AC_ADD(numTileListsGBIS); AC_ADD(numJtiles);
      AC_ADD(numExcluded); AC_ADD(patchReadyQueueCount); AC_ADD(outputOrderIndex););
    AC_DEVICE_FLOAT4(myQ, "post_nonbondedforcekernel", d_forces, atomStorageSize);
    AC_DEVICE_FLOAT4(myQ, "post_nonbondedforcekernel", d_forcesSlow, atomStorageSize);
    AC_DEVICE(myQ, "post_nonbondedforcekernel",patchNumCountPtr, numPatches);
    AC_DEVICE_STRUCT(myQ, "post_nonbondedforcekernel_floats", tlKernel.getTileListVirialEnergy(), tlKernel.getTileListVirialEnergySize(), float, 9, AC_ADD(sh.x());AC_ADD(sh.y());AC_ADD(sh.z());AC_ADD(force.x());AC_ADD(force.y());AC_ADD(force.z());AC_ADD(forceSlow.x());AC_ADD(forceSlow.y());AC_ADD(forceSlow.z()););
    AC_DEVICE_STRUCT(myQ, "post_nonbondedforcekernel_doubles", tlKernel.getTileListVirialEnergy(), tlKernel.getTileListVirialEnergySize(), double, 4, AC_ADD(energyVdw);AC_ADD(energyElec);AC_ADD(energySlow);AC_ADD(energyGBIS););


