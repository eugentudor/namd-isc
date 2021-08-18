//
// Tuple types that enable fast evaluation on GPU
//
#ifndef DPCPPTUPLETYPES_H
#define DPCPPTUPLETYPES_H

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>

struct DpcppBond {
  int i, j, itype;
  // int ivir;
  float scale;
  sycl::float3 ioffsetXYZ;
};

struct DpcppAngle {
  int i, j, k, itype;
  // int ivir, kvir;
  float scale;
  sycl::float3 ioffsetXYZ;
  sycl::float3 koffsetXYZ;
};

struct DpcppDihedral {
  int i, j, k, l, itype;
  // int ivir, jvir, lvir;
  float scale;
  sycl::float3 ioffsetXYZ;
  sycl::float3 joffsetXYZ;
  sycl::float3 loffsetXYZ;
};

struct DpcppExclusion {
  int i, j, vdwtypei, vdwtypej;
  // int ivir;
  sycl::float3 ioffsetXYZ;
};

struct DpcppCrossterm {
  int i1, i2, i3, i4, i5, i6, i7, i8, itype;
  float scale;
  sycl::float3 offset12XYZ;
  sycl::float3 offset23XYZ;
  sycl::float3 offset34XYZ;
  sycl::float3 offset56XYZ;
  sycl::float3 offset67XYZ;
  sycl::float3 offset78XYZ;
};

struct DpcppBondValue {
  float k;   //  Force constant for the bond
  float x0;  //  Rest distance for the bond
  float x1;  //  Upper wall for harmonic wall potential (with x0 lower wall)
};

struct DpcppAngleValue {
  float k;   //  Force constant for angle
  float theta0;  //  Rest angle for angle
  float k_ub;  //  Urey-Bradley force constant
  float r_ub;  //  Urey-Bradley distance
  int normal; // Whether we use harmonic (0) or cos-based (1) angle terms
};

struct DpcppDihedralValue {
  float k;     //  Force constant
  float delta; //  Phase shift
  int n;       //  Periodicity*2, if n low bit is set to 0, this is the last in multiplicity
};

// struct DpcppCrosstermData { float d00,d01,d10,d11; };

struct DpcppCrosstermValue {
  enum {dim=24};
  sycl::float4 c[dim][dim][4]; // bicubic interpolation coefficients
};

#endif

#endif // DPCPPTUPLETYPES_H
