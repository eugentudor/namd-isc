  AC_TAG("bondedForceKernel");
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", bonds, numBonds, int, 3, AC_ADD(i); AC_ADD(j); AC_ADD(itype););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", bonds, numBonds, float, 4, AC_ADD(scale); AC_ADDV3(ioffsetXYZ));
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel", bondValues, bondValuesSize, float, 3, AC_ADD(k); AC_ADD(x0); AC_ADD(x1););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", angles, numAngles, int, 4, AC_ADD(i); AC_ADD(j); AC_ADD(k); AC_ADD(itype););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", angles, numAngles, float, 7, AC_ADD(scale); AC_ADD(ioffsetXYZ.x()); AC_ADD(ioffsetXYZ.y()); AC_ADD(ioffsetXYZ.z()); AC_ADD(koffsetXYZ.x()); AC_ADD(koffsetXYZ.y()); AC_ADD(koffsetXYZ.z()););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", angleValues, angleValuesSize, int, 1, AC_ADD(normal););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", angleValues, angleValuesSize, float, 4, AC_ADD(k); AC_ADD(theta0); AC_ADD(k_ub); AC_ADD(r_ub););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", dihedrals, numDihedrals, int, 5, AC_ADD(i); AC_ADD(j); AC_ADD(k); AC_ADD(l); AC_ADD(itype););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", dihedrals, numDihedrals, float, 10, AC_ADD(scale); AC_ADD(ioffsetXYZ.x()); AC_ADD(ioffsetXYZ.y()); AC_ADD(ioffsetXYZ.z()); AC_ADD(joffsetXYZ.x()); AC_ADD(joffsetXYZ.y()); AC_ADD(joffsetXYZ.z()); AC_ADD(loffsetXYZ.x()); AC_ADD(loffsetXYZ.y()); AC_ADD(loffsetXYZ.z()););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", dihedralValues, dihedralValuesSize, int, 1, AC_ADD(n););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", dihedralValues, dihedralValuesSize, float, 2, AC_ADD(k); AC_ADD(delta););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", impropers, numImpropers, int, 5, AC_ADD(i); AC_ADD(j); AC_ADD(k); AC_ADD(l); AC_ADD(itype););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", impropers, numImpropers, float,10, AC_ADD(scale); AC_ADD(ioffsetXYZ.x()); AC_ADD(ioffsetXYZ.y()); AC_ADD(ioffsetXYZ.z()); AC_ADD(joffsetXYZ.x()); AC_ADD(joffsetXYZ.y()); AC_ADD(joffsetXYZ.z()); AC_ADD(loffsetXYZ.x()); AC_ADD(loffsetXYZ.y()); AC_ADD(loffsetXYZ.z()););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", improperValues, improperValuesSize, int, 1, AC_ADD(n););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", improperValues, improperValuesSize, float, 2, AC_ADD(k); AC_ADD(delta););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", exclusions, numExclusions, int, 4, AC_ADD(i); AC_ADD(j); AC_ADD(vdwtypei); AC_ADD(vdwtypej););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", exclusions, numExclusions, float, 3, AC_ADD(ioffsetXYZ.x()); AC_ADD(ioffsetXYZ.y()); AC_ADD(ioffsetXYZ.z()););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_ints", crossterms, numCrossterms, int, 9, AC_ADD(i1); AC_ADD(i2); AC_ADD(i3); AC_ADD(i4); AC_ADD(i5); AC_ADD(i6); AC_ADD(i7); AC_ADD(i8); AC_ADD(itype););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel_floats", crossterms, numCrossterms, float, 19, AC_ADD(scale); AC_ADDV3(offset12XYZ); AC_ADDV3(offset23XYZ); AC_ADDV3(offset34XYZ); AC_ADDV3(offset56XYZ); AC_ADDV3(offset67XYZ); AC_ADDV3(offset78XYZ););
  AC_DEVICE_STRUCT(myQ, "pre_bondedforcekernel", crosstermValues, crosstermValuesSize, float, 2304, 
    for(int i=0; i<24; i++)
      for(int j=0; j<24; j++)
        for(int k=0; k<4; k++)
          {AC_ADDV4(c[i][j][k]);});
  auto r2_table = dpcppNonbondedTables.get_r2_table();
  AC_DEVICE(myQ, "pre_bondedforcekernel", r2_table, dpcppNonbondedTables.getTableSize());
  auto exclusionTable = dpcppNonbondedTables.getExclusionTable();
    AC_DEVICE_FLOAT4(myQ, "pre_bondedforcekernel", exclusionTable, dpcppNonbondedTables.getTableSize());
    AC_DEVICE_FLOAT4(myQ, "pre_bondedforcekernel", xyzq, atomStorageSize);


