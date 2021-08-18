    AC_DEVICE_STRUCT(myQ, "post_reducenonbondedvirialkernel_virial", d_virialEnergy, 1, double, 9,{for(int i=0; i<9;i++)AC_ADD(virial[i]);}); 
    AC_DEVICE_STRUCT(myQ, "post_reducenonbondedvirialkernel_virialslow", d_virialEnergy, 1, double, 9,{for(int i=0; i<9;i++)AC_ADD(virialSlow[i]);}); 
    AC_DEVICE_STRUCT(myQ, "post_reducenonbondedvirialkernel_doubles", d_virialEnergy, 1, double, 4, AC_ADD(energyVdw);AC_ADD(energyElec);AC_ADD(energySlow);AC_ADD(energyGBIS););


