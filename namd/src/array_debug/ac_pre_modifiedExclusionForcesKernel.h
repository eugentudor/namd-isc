  AC_TAG("modifiedExclusionForcesKernel");
  AC_DEVICE_STRUCT(myQ, "pre_modifiedexclusionforceskernel_ints", modifiedExclusions, numModifiedExclusions, int, 4, AC_ADD(i); AC_ADD(j); AC_ADD(vdwtypei); AC_ADD(vdwtypej););
  AC_DEVICE_STRUCT(myQ, "pre_modifiedexclusionforceskernel_floats", modifiedExclusions, numModifiedExclusions, float, 3, AC_ADD(ioffsetXYZ.x()); AC_ADD(ioffsetXYZ.y()); AC_ADD(ioffsetXYZ.z()););
  auto vdwCoefTable = dpcppNonbondedTables.getExclusionVdwCoefTable();
    AC_DEVICE_FLOAT2(myQ, "pre_modifiedexclusionforceskernel", vdwCoefTable, dpcppNonbondedTables.getVdwCoefTableWidth());

  auto modifiedExclusionForceTable = dpcppNonbondedTables.getModifiedExclusionForceTable();
  auto modifiedExclusionEnergyTable = dpcppNonbondedTables.getModifiedExclusionEnergyTable();
    int feTableSize = dpcppNonbondedTables.getModifiedExclusionTableSize();
    AC_DEVICE_FLOAT4(myQ, "pre_modifiedexclusionforceskernel", modifiedExclusionForceTable, feTableSize);
    AC_DEVICE_FLOAT4(myQ, "pre_modifiedexclusionforceskernel", modifiedExclusionEnergyTable, feTableSize);
    AC_DEVICE_FLOAT4(myQ, "pre_modifiedexclusionforceskernel", xyzq, atomStorageSize);
    AC_DEVICE(myQ, "pre_modifiedexclusionforceskernel", forces, forceSize);
    AC_DEVICE(myQ, "pre_modifiedexclusionforceskernel", energies_virials, energies_virials_SIZE);
