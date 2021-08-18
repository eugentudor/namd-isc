#ifdef WIN32
#define _USE_MATH_DEFINES
#define __thread __declspec(thread)
#endif
#include <math.h>
#include "DpcppComputeBondedKernel.h"
#include "NamdTypes.h"

#include "DpcppDevice.h"
#include <algorithm>

#ifdef NAMD_DPCPP

using namespace sycl;
using namespace sycl::ONEAPI;

#ifdef WIN32
#define __thread __declspec(thread)
#endif
extern __thread DpcppDevice *dpcppDevice;

//NAMD_INLINE float4 linear_interp_cudata_float4(const sycl::float4 *__restrict__ mytable, const float rinv, const int tsize)
//{
//    const float table_rinv = rinv > 1.f ? 1.f : rinv;
//    const float table_f = tsize * table_rinv;
//    const int table_i = (int) table_f;
//    const float table_diff = table_f - table_i;
//    sycl::float4 xi;
//    xi.x() = table_diff * mytable[table_i + 1].x() +
//             (1.f - table_diff) * mytable[table_i].x();
//    xi.y() = table_diff * mytable[table_i + 1].y() +
//             (1.f - table_diff) * mytable[table_i].y();
//    xi.z() = table_diff * mytable[table_i + 1].z() +
//             (1.f - table_diff) * mytable[table_i].z();
//    xi.w() = table_diff * mytable[table_i + 1].w() +
//             (1.f - table_diff) * mytable[table_i].w();
//   return xi;
//}

template <typename T>
NAMD_INLINE void convertForces(const float x, const float y, const float z,
                                   T &Tx, T &Ty, T &Tz) {

  Tx = (T)(x);
  Ty = (T)(y);
  Tz = (T)(z);
}

template <typename T>
NAMD_INLINE void calcComponentForces(float fij, const float dx,
                                         const float dy, const float dz,
                                         T &fxij, T &fyij, T &fzij) {

  fxij = (T)(fij*dx);
  fyij = (T)(fij*dy);
  fzij = (T)(fij*dz);

}

template <typename T>
NAMD_INLINE void calcComponentForces(float fij1, const float dx1,
                                         const float dy1, const float dz1,
                                         float fij2, const float dx2,
                                         const float dy2, const float dz2,
                                         T &fxij, T &fyij, T &fzij) {

  fxij = (T)(fij1*dx1 + fij2*dx2);
  fyij = (T)(fij1*dy1 + fij2*dy2);
  fzij = (T)(fij1*dz1 + fij2*dz2);
}

template <typename T>
NAMD_INLINE void storeForces(const T fx, const T fy, const T fz,
                                 const int ind, const int stride, T *force) {
  ATOMIC_ADD(T, force[ind           ], fx);
  ATOMIC_ADD(T, force[ind + stride  ], fy);
  ATOMIC_ADD(T, force[ind + stride*2], fz);
}

//
// Calculates bonds
//
template <typename T, bool doEnergy, bool doVirial>
void bondForce(
    const int index, const DpcppBond *__restrict__ bondList,
    const DpcppBondValue *__restrict__ bondValues,
    const sycl::float4 *__restrict__ xyzq, const int stride,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    T *__restrict__ force, double &energy,
#ifdef WRITE_FULL_VIRIALS
    DpcppComputeBondedKernel::BondedVirial<double> &virial
#else
    DpcppComputeBondedKernel::BondedVirial *__restrict__ virial
#endif
) {

  DpcppBond bl = bondList[index];
  DpcppBondValue bondValue = bondValues[bl.itype];
  if (bondValue.x0 == 0.0f) return;

  float shx = bl.ioffsetXYZ.x() * lata.x() + bl.ioffsetXYZ.y() * latb.x() +
              bl.ioffsetXYZ.z() * latc.x();
  float shy = bl.ioffsetXYZ.x() * lata.y() + bl.ioffsetXYZ.y() * latb.y() +
              bl.ioffsetXYZ.z() * latc.y();
  float shz = bl.ioffsetXYZ.x() * lata.z() + bl.ioffsetXYZ.y() * latb.z() +
              bl.ioffsetXYZ.z() * latc.z();

  sycl::float4 xyzqi = xyzq[bl.i];
  sycl::float4 xyzqj = xyzq[bl.j];

  float xij = xyzqi.x() + shx - xyzqj.x();
  float yij = xyzqi.y() + shy - xyzqj.y();
  float zij = xyzqi.z() + shz - xyzqj.z();

  float r = sycl::sqrt(xij * xij + yij * yij + zij * zij);

  float db = r - bondValue.x0;
  if (bondValue.x1) {
    // in this case, the bond represents a harmonic wall potential
    // where x0 is the lower wall and x1 is the upper
    db = (r > bondValue.x1 ? r - bondValue.x1 : (r > bondValue.x0 ? 0 : db));
  }
  float fij = db * bondValue.k * bl.scale;
 
  if (doEnergy) {
    energy += (double)(fij*db);
  }
  fij *= -2.0f/r;
  
  T T_fxij, T_fyij, T_fzij;
  calcComponentForces<T>(fij, xij, yij, zij, T_fxij, T_fyij, T_fzij);
  
  // Store forces
  storeForces<T>(T_fxij, T_fyij, T_fzij, bl.i, stride, force);
  storeForces<T>(-T_fxij, -T_fyij, -T_fzij, bl.j, stride, force);

  // Store virial
  if (doVirial) {
#ifdef WRITE_FULL_VIRIALS
    float fxij = fij*xij;
    float fyij = fij*yij;
    float fzij = fij*zij;
    virial.xx = (fxij*xij);
    virial.xy = (fxij*yij);
    virial.xz = (fxij*zij);
    virial.yx = (fyij*xij);
    virial.yy = (fyij*yij);
    virial.yz = (fyij*zij);
    virial.zx = (fzij*xij);
    virial.zy = (fzij*yij);
    virial.zz = (fzij*zij);
#endif
  }
}

//
// Calculates modified exclusions
//
template <typename T, bool doEnergy, bool doVirial, bool doElect>
NAMD_INLINE void modifiedExclusionForce(
    const int index, const DpcppExclusion *__restrict__ exclusionList,
    const bool doSlow,
    const float one_scale14, // 1 - scale14
    const int vdwCoefTableWidth,
    const sycl::float2 *__restrict__ vdwCoefTable,
    const sycl::float4 *forceTable, const sycl::float4 *energyTable, int feTableSize,
    const sycl::float4 *__restrict__ xyzq, const int stride,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    const float cutoff2, double &energyVdw, T *__restrict__ forceNbond,
    double &energyNbond, T *__restrict__ forceSlow, double &energySlow,
#ifdef WRITE_FULL_VIRIALS
    DpcppComputeBondedKernel::BondedVirial<double> &virialNbond,
    DpcppComputeBondedKernel::BondedVirial<double> &virialSlow
#else
    DpcppComputeBondedKernel::BondedVirial *__restrict__ virialNbond,
    DpcppComputeBondedKernel::BondedVirial *__restrict__ virialSlow
#endif
) {

  DpcppExclusion bl = exclusionList[index];

  float shx = bl.ioffsetXYZ.x() * lata.x() + bl.ioffsetXYZ.y() * latb.x() +
              bl.ioffsetXYZ.z() * latc.x();
  float shy = bl.ioffsetXYZ.x() * lata.y() + bl.ioffsetXYZ.y() * latb.y() +
              bl.ioffsetXYZ.z() * latc.y();
  float shz = bl.ioffsetXYZ.x() * lata.z() + bl.ioffsetXYZ.y() * latb.z() +
              bl.ioffsetXYZ.z() * latc.z();

  sycl::float4 xyzqi = xyzq[bl.i];
  sycl::float4 xyzqj = xyzq[bl.j];

  float xij = xyzqi.x() + shx - xyzqj.x();
  float yij = xyzqi.y() + shy - xyzqj.y();
  float zij = xyzqi.z() + shz - xyzqj.z();

  float r2 = xij*xij + yij*yij + zij*zij;
  if (r2 < cutoff2) {

    float rinv = sycl::rsqrt(r2);

    float qq;
    if (doElect) qq = one_scale14 * xyzqi.w() * xyzqj.w();

    int vdwIndex = bl.vdwtypei + bl.vdwtypej*vdwCoefTableWidth;
    sycl::float2 ljab = vdwCoefTable[vdwIndex];

    sycl::float4 fi =
        linear_interp_cudata_float4(forceTable, rinv, feTableSize);
    sycl::float4 ei;
    if (doEnergy) {
      ei = linear_interp_cudata_float4(energyTable, rinv, feTableSize);
      energyVdw += (double)(ljab.x() * ei.z() + ljab.y() * ei.y());
      if (doElect) {
        energyNbond += qq * ei.x();
        if (doSlow) energySlow += qq * ei.w();
      }
    }

    float fNbond;
    if (doElect) {

      fNbond = -(ljab.x() * fi.z() + ljab.y() * fi.y() + qq * fi.x());
    } else {

      fNbond = -(ljab.x() * fi.z() + ljab.y() * fi.y());
    }
    T T_fxij, T_fyij, T_fzij;
    calcComponentForces<T>(fNbond, xij, yij, zij, T_fxij, T_fyij, T_fzij);
    storeForces<T>(T_fxij, T_fyij, T_fzij, bl.i, stride, forceNbond);
    storeForces<T>(-T_fxij, -T_fyij, -T_fzij, bl.j, stride, forceNbond);

    float fSlow;
    if (doSlow && doElect) {

      fSlow = -qq * fi.w();
      T T_fxij, T_fyij, T_fzij;
      calcComponentForces<T>(fSlow, xij, yij, zij, T_fxij, T_fyij, T_fzij);
      storeForces<T>(T_fxij, T_fyij, T_fzij, bl.i, stride, forceSlow);
      storeForces<T>(-T_fxij, -T_fyij, -T_fzij, bl.j, stride, forceSlow);
    }

    // Store virial
    if (doVirial) {
#ifdef WRITE_FULL_VIRIALS
      float fxij = fNbond*xij;
      float fyij = fNbond*yij;
      float fzij = fNbond*zij;
      virialNbond.xx = (fxij*xij);
      virialNbond.xy = (fxij*yij);
      virialNbond.xz = (fxij*zij);
      virialNbond.yx = (fyij*xij);
      virialNbond.yy = (fyij*yij);
      virialNbond.yz = (fyij*zij);
      virialNbond.zx = (fzij*xij);
      virialNbond.zy = (fzij*yij);
      virialNbond.zz = (fzij*zij);
#endif
    }

    // Store virial
    if (doVirial && doSlow && doElect) {
#ifdef WRITE_FULL_VIRIALS
      float fxij = fSlow*xij;
      float fyij = fSlow*yij;
      float fzij = fSlow*zij;
      virialSlow.xx = (fxij*xij);
      virialSlow.xy = (fxij*yij);
      virialSlow.xz = (fxij*zij);
      virialSlow.yx = (fyij*xij);
      virialSlow.yy = (fyij*yij);
      virialSlow.yz = (fyij*zij);
      virialSlow.zx = (fzij*xij);
      virialSlow.zy = (fzij*yij);
      virialSlow.zz = (fzij*zij);
#endif
    }

  }

}

//
// Calculates exclusions. Here doSlow = true
//
template <typename T, bool doEnergy, bool doVirial>
NAMD_INLINE void exclusionForce(
    const int index, const DpcppExclusion *__restrict__ exclusionList,
    const float r2_delta, const int r2_delta_expc,
    const float *__restrict__ r2_table,
    const sycl::float4 *__restrict__ exclusionTable,
    const sycl::float4 *__restrict__ xyzq, const int stride,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    const float cutoff2, T *__restrict__ forceSlow, double &energySlow,
#ifdef WRITE_FULL_VIRIALS
    DpcppComputeBondedKernel::BondedVirial<double> &virialSlow
#else
    DpcppComputeBondedKernel::BondedVirial *__restrict__ virialSlow
#endif
) {

  DpcppExclusion bl = exclusionList[index];

  float shx = bl.ioffsetXYZ.x() * lata.x() + bl.ioffsetXYZ.y() * latb.x() +
              bl.ioffsetXYZ.z() * latc.x();
  float shy = bl.ioffsetXYZ.x() * lata.y() + bl.ioffsetXYZ.y() * latb.y() +
              bl.ioffsetXYZ.z() * latc.y();
  float shz = bl.ioffsetXYZ.x() * lata.z() + bl.ioffsetXYZ.y() * latb.z() +
              bl.ioffsetXYZ.z() * latc.z();

  sycl::float4 xyzqi = xyzq[bl.i];
  sycl::float4 xyzqj = xyzq[bl.j];

  float xij = xyzqi.x() + shx - xyzqj.x();
  float yij = xyzqi.y() + shy - xyzqj.y();
  float zij = xyzqi.z() + shz - xyzqj.z();

  float r2 = xij*xij + yij*yij + zij*zij;
  if (r2 < cutoff2) {
    r2 += r2_delta;

    union { float f; int i; } r2i;
    r2i.f = r2;
    int table_i = (r2i.i >> 17) + r2_delta_expc;  // table_i >= 0

    float r2_table_val = r2_table[table_i];
    float diffa = r2 - r2_table_val;
    float qq = xyzqi.w() * xyzqj.w();

    sycl::float4 slow = exclusionTable[table_i];

    if (doEnergy) {
      energySlow +=
          (double)(qq *
                   (((diffa * (1.0f / 6.0f) * slow.x() + 0.25f * slow.y()) *
                         diffa +
                     0.5f * slow.z()) *
                        diffa +
                    slow.w()));
    }

    float fSlow = -qq * ((diffa * slow.x() + slow.y()) * diffa + slow.z());

    T T_fxij, T_fyij, T_fzij;
    calcComponentForces<T>(fSlow, xij, yij, zij, T_fxij, T_fyij, T_fzij);
    storeForces<T>(T_fxij, T_fyij, T_fzij, bl.i, stride, forceSlow);
    storeForces<T>(-T_fxij, -T_fyij, -T_fzij, bl.j, stride, forceSlow);

    // Store virial
    if (doVirial) {
#ifdef WRITE_FULL_VIRIALS
      float fxij = fSlow*xij;
      float fyij = fSlow*yij;
      float fzij = fSlow*zij;
      virialSlow.xx = (fxij*xij);
      virialSlow.xy = (fxij*yij);
      virialSlow.xz = (fxij*zij);
      virialSlow.yx = (fyij*xij);
      virialSlow.yy = (fyij*yij);
      virialSlow.yz = (fyij*zij);
      virialSlow.zx = (fzij*xij);
      virialSlow.zy = (fzij*yij);
      virialSlow.zz = (fzij*zij);
#endif
    }
  }
}

template <typename T, bool doEnergy, bool doVirial>
void angleForce(
    const int index, const DpcppAngle *__restrict__ angleList,
    const DpcppAngleValue *__restrict__ angleValues,
    const sycl::float4 *__restrict__ xyzq, const int stride,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    T *__restrict__ force, double &energy,
#ifdef WRITE_FULL_VIRIALS
    DpcppComputeBondedKernel::BondedVirial<double> &virial
#else
    DpcppComputeBondedKernel::BondedVirial *__restrict__ virial
#endif
) {

  DpcppAngle al = angleList[index];

  float ishx = al.ioffsetXYZ.x() * lata.x() + al.ioffsetXYZ.y() * latb.x() +
               al.ioffsetXYZ.z() * latc.x();
  float ishy = al.ioffsetXYZ.x() * lata.y() + al.ioffsetXYZ.y() * latb.y() +
               al.ioffsetXYZ.z() * latc.y();
  float ishz = al.ioffsetXYZ.x() * lata.z() + al.ioffsetXYZ.y() * latb.z() +
               al.ioffsetXYZ.z() * latc.z();

  float kshx = al.koffsetXYZ.x() * lata.x() + al.koffsetXYZ.y() * latb.x() +
               al.koffsetXYZ.z() * latc.x();
  float kshy = al.koffsetXYZ.x() * lata.y() + al.koffsetXYZ.y() * latb.y() +
               al.koffsetXYZ.z() * latc.y();
  float kshz = al.koffsetXYZ.x() * lata.z() + al.koffsetXYZ.y() * latb.z() +
               al.koffsetXYZ.z() * latc.z();

  float xij = xyzq[al.i].x() + ishx - xyzq[al.j].x();
  float yij = xyzq[al.i].y() + ishy - xyzq[al.j].y();
  float zij = xyzq[al.i].z() + ishz - xyzq[al.j].z();

  float xkj = xyzq[al.k].x() + kshx - xyzq[al.j].x();
  float ykj = xyzq[al.k].y() + kshy - xyzq[al.j].y();
  float zkj = xyzq[al.k].z() + kshz - xyzq[al.j].z();

  float rij_inv = sycl::rsqrt(xij * xij + yij * yij + zij * zij);
  float rkj_inv = sycl::rsqrt(xkj * xkj + ykj * ykj + zkj * zkj);

  float xijr = xij*rij_inv;
  float yijr = yij*rij_inv;
  float zijr = zij*rij_inv;
  float xkjr = xkj*rkj_inv;
  float ykjr = ykj*rkj_inv;
  float zkjr = zkj*rkj_inv;
  float cos_theta = xijr*xkjr + yijr*ykjr + zijr*zkjr;

  DpcppAngleValue angleValue = angleValues[al.itype];
  angleValue.k *= al.scale;

  float diff;
  if (angleValue.normal == 1) {
    // Restrict values of cos_theta to the interval [-0.999 ... 0.999]
    cos_theta = sycl::min(0.999f, sycl::max(-0.999f, cos_theta));
    float theta = sycl::acos(cos_theta);
    diff = theta - angleValue.theta0;
  } else {
    diff = cos_theta - angleValue.theta0;
  }

  if (doEnergy) {
    energy += (double)(angleValue.k * diff * diff);
  }
  if (angleValue.normal == 1) {
    float inv_sin_theta = sycl::rsqrt(1.0f - cos_theta * cos_theta);
    if (inv_sin_theta > 1.0e6) {
      diff = (diff < 0.0f) ? 1.0f : -1.0f;
    } else {
      diff *= -inv_sin_theta;
    }
  }
  diff *= -2.0f*angleValue.k;

  float dtxi = rij_inv*(xkjr - cos_theta*xijr);
  float dtxj = rkj_inv*(xijr - cos_theta*xkjr);
  float dtyi = rij_inv*(ykjr - cos_theta*yijr);
  float dtyj = rkj_inv*(yijr - cos_theta*ykjr);
  float dtzi = rij_inv*(zkjr - cos_theta*zijr);
  float dtzj = rkj_inv*(zijr - cos_theta*zkjr);

  T T_dtxi, T_dtyi, T_dtzi;
  T T_dtxj, T_dtyj, T_dtzj;
  calcComponentForces<T>(diff, dtxi, dtyi, dtzi, T_dtxi, T_dtyi, T_dtzi);
  calcComponentForces<T>(diff, dtxj, dtyj, dtzj, T_dtxj, T_dtyj, T_dtzj);
  T T_dtxk = -T_dtxi - T_dtxj;
  T T_dtyk = -T_dtyi - T_dtyj;
  T T_dtzk = -T_dtzi - T_dtzj;
  storeForces<T>(T_dtxk, T_dtyk, T_dtzk, al.j, stride, force);

  if (angleValue.k_ub) {
    float xik = xij - xkj;
    float yik = yij - ykj;
    float zik = zij - zkj;
    float rik_inv = sycl::rsqrt(xik * xik + yik * yik + zik * zik);
    float rik = 1.0f/rik_inv;
    float diff_ub = rik - angleValue.r_ub;
    if (doEnergy) {
      energy += (double)(angleValue.k_ub * diff_ub * diff_ub);
    }
    diff_ub *= -2.0f*angleValue.k_ub*rik_inv;
    T T_dxik, T_dyik, T_dzik;
    calcComponentForces<T>(diff_ub, xik, yik, zik, T_dxik, T_dyik, T_dzik);
    T_dtxi += T_dxik;
    T_dtyi += T_dyik;
    T_dtzi += T_dzik;
    T_dtxj -= T_dxik;
    T_dtyj -= T_dyik;
    T_dtzj -= T_dzik;
  }

  storeForces<T>(T_dtxi, T_dtyi, T_dtzi, al.i, stride, force);
  storeForces<T>(T_dtxj, T_dtyj, T_dtzj, al.k, stride, force);

  // Store virial
  if (doVirial) {
#ifdef WRITE_FULL_VIRIALS
    float fxi = ((float)T_dtxi)*force_to_float;
    float fyi = ((float)T_dtyi)*force_to_float;
    float fzi = ((float)T_dtzi)*force_to_float;
    float fxk = ((float)T_dtxj)*force_to_float;
    float fyk = ((float)T_dtyj)*force_to_float;
    float fzk = ((float)T_dtzj)*force_to_float;
    virial.xx = (fxi*xij) + (fxk*xkj);
    virial.xy = (fxi*yij) + (fxk*ykj);
    virial.xz = (fxi*zij) + (fxk*zkj);
    virial.yx = (fyi*xij) + (fyk*xkj);
    virial.yy = (fyi*yij) + (fyk*ykj);
    virial.yz = (fyi*zij) + (fyk*zkj);
    virial.zx = (fzi*xij) + (fzk*xkj);
    virial.zy = (fzi*yij) + (fzk*ykj);
    virial.zz = (fzi*zij) + (fzk*zkj);
#endif
  }
}

//
// Dihedral computation
//
// Out: df, e
//
template <bool doEnergy>
NAMD_INLINE void diheComp(const DpcppDihedralValue *dihedralValues, int ic,
                              const float sin_phi, const float cos_phi,
                              const float scale, float &df, double &e) {

  df = 0.0f;
  if (doEnergy) e = 0.0;


  float phi = sycl::atan2((float)sin_phi, (float)cos_phi);

  bool lrep = true;
  while (lrep) {
    DpcppDihedralValue dihedralValue = dihedralValues[ic];
    dihedralValue.k *= scale;

    // Last dihedral has n low bit set to 0
    lrep = (dihedralValue.n & 1);
    dihedralValue.n >>= 1;
    if (dihedralValue.n) {
      float nf = dihedralValue.n;
      float x = nf*phi - dihedralValue.delta;
      if (doEnergy) {
        float sin_x, cos_x;
/* DPCT_ORIG         sincosf(x, &sin_x, &cos_x);*/
        /*
        DPCT1017:112: The sycl::sincos call is used instead of the sincosf call.
        These two calls do not provide exactly the same functionality. Check the
        potential precision and/or performance issues for the generated code.
        */
        sin_x = sycl::sincos(x, &cos_x);
        e += (double)(dihedralValue.k*(1.0f + cos_x));
        df += (double)(nf*dihedralValue.k*sin_x);
      } else {
        float sin_x = sycl::sin(x);
        df += (double)(nf*dihedralValue.k*sin_x);
      }
    } else {
      float diff = phi - dihedralValue.delta;
      if (diff < -(float)(M_PI)) diff += (float)(2.0*M_PI);
      if (diff >  (float)(M_PI)) diff -= (float)(2.0*M_PI);
      if (doEnergy) {
        e += (double)(dihedralValue.k*diff*diff);
      }
      df -= 2.0f*dihedralValue.k*diff;
    }
    ic++;
  }

}

template <typename T, bool doEnergy, bool doVirial>
void diheForce(
    const int index, const DpcppDihedral *__restrict__ diheList,
    const DpcppDihedralValue *__restrict__ dihedralValues,
    const sycl::float4 *__restrict__ xyzq, const int stride,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    T *__restrict__ force, double &energy,
#ifdef WRITE_FULL_VIRIALS
    DpcppComputeBondedKernel::BondedVirial<double> &virial
#else
    DpcppComputeBondedKernel::BondedVirial *__restrict__ virial
#endif
) {

  DpcppDihedral dl = diheList[index];

  float ishx = dl.ioffsetXYZ.x() * lata.x() + dl.ioffsetXYZ.y() * latb.x() +
               dl.ioffsetXYZ.z() * latc.x();
  float ishy = dl.ioffsetXYZ.x() * lata.y() + dl.ioffsetXYZ.y() * latb.y() +
               dl.ioffsetXYZ.z() * latc.y();
  float ishz = dl.ioffsetXYZ.x() * lata.z() + dl.ioffsetXYZ.y() * latb.z() +
               dl.ioffsetXYZ.z() * latc.z();

  float jshx = dl.joffsetXYZ.x() * lata.x() + dl.joffsetXYZ.y() * latb.x() +
               dl.joffsetXYZ.z() * latc.x();
  float jshy = dl.joffsetXYZ.x() * lata.y() + dl.joffsetXYZ.y() * latb.y() +
               dl.joffsetXYZ.z() * latc.y();
  float jshz = dl.joffsetXYZ.x() * lata.z() + dl.joffsetXYZ.y() * latb.z() +
               dl.joffsetXYZ.z() * latc.z();

  float lshx = dl.loffsetXYZ.x() * lata.x() + dl.loffsetXYZ.y() * latb.x() +
               dl.loffsetXYZ.z() * latc.x();
  float lshy = dl.loffsetXYZ.x() * lata.y() + dl.loffsetXYZ.y() * latb.y() +
               dl.loffsetXYZ.z() * latc.y();
  float lshz = dl.loffsetXYZ.x() * lata.z() + dl.loffsetXYZ.y() * latb.z() +
               dl.loffsetXYZ.z() * latc.z();

  float xij = xyzq[dl.i].x() + ishx - xyzq[dl.j].x();
  float yij = xyzq[dl.i].y() + ishy - xyzq[dl.j].y();
  float zij = xyzq[dl.i].z() + ishz - xyzq[dl.j].z();

  float xjk = xyzq[dl.j].x() + jshx - xyzq[dl.k].x();
  float yjk = xyzq[dl.j].y() + jshy - xyzq[dl.k].y();
  float zjk = xyzq[dl.j].z() + jshz - xyzq[dl.k].z();

  float xlk = xyzq[dl.l].x() + lshx - xyzq[dl.k].x();
  float ylk = xyzq[dl.l].y() + lshy - xyzq[dl.k].y();
  float zlk = xyzq[dl.l].z() + lshz - xyzq[dl.k].z();

  // A=F^G, B=H^G.
  float ax = yij*zjk - zij*yjk;
  float ay = zij*xjk - xij*zjk;
  float az = xij*yjk - yij*xjk;
  float bx = ylk*zjk - zlk*yjk;
  float by = zlk*xjk - xlk*zjk;
  float bz = xlk*yjk - ylk*xjk;

  float ra2 = ax*ax + ay*ay + az*az;
  float rb2 = bx*bx + by*by + bz*bz;
  float rg = sycl::sqrt(xjk * xjk + yjk * yjk + zjk * zjk);

  //    if((ra2 <= rxmin2) .or. (rb2 <= rxmin2) .or. (rg <= rxmin)) then
  //          nlinear = nlinear + 1
  //       endif

  float rgr = 1.0f / rg;
  float ra2r = 1.0f / ra2;
  float rb2r = 1.0f / rb2;
  float rabr = sycl::sqrt(ra2r * rb2r);

  float cos_phi = (ax*bx + ay*by + az*bz)*rabr;
  //
  // Note that sin(phi).G/|G|=B^A/(|A|.|B|)
  // which can be simplify to sin(phi)=|G|H.A/(|A|.|B|)
  float sin_phi = rg*rabr*(ax*xlk + ay*ylk + az*zlk);
  //
  //     Energy and derivative contributions.

  float df;
  double e;
  diheComp<doEnergy>(dihedralValues, dl.itype, sin_phi, cos_phi, dl.scale, df, e);

  if (doEnergy) energy += e;

  //
  //     Compute derivatives wrt catesian coordinates.
  //
  // GAA=dE/dphi.|G|/A^2, GBB=dE/dphi.|G|/B^2, FG=F.G, HG=H.G
  //  FGA=dE/dphi*F.G/(|G|A^2), HGB=dE/dphi*H.G/(|G|B^2)

  float fg = xij*xjk + yij*yjk + zij*zjk;
  float hg = xlk*xjk + ylk*yjk + zlk*zjk;
  ra2r *= df;
  rb2r *= df;
  float fga = fg*ra2r*rgr;
  float hgb = hg*rb2r*rgr;
  float gaa = ra2r*rg;
  float gbb = rb2r*rg;
  // DFi=dE/dFi, DGi=dE/dGi, DHi=dE/dHi.

  // Store forces
  T T_fix, T_fiy, T_fiz;
  calcComponentForces<T>(-gaa, ax, ay, az, T_fix, T_fiy, T_fiz);
  storeForces<T>(T_fix, T_fiy, T_fiz, dl.i, stride, force);

  T dgx, dgy, dgz;
  calcComponentForces<T>(fga, ax, ay, az, -hgb, bx, by, bz, dgx, dgy, dgz);
  T T_fjx = dgx - T_fix;
  T T_fjy = dgy - T_fiy;
  T T_fjz = dgz - T_fiz;
  storeForces<T>(T_fjx, T_fjy, T_fjz, dl.j, stride, force);

  T dhx, dhy, dhz;
  calcComponentForces<T>(gbb, bx, by, bz, dhx, dhy, dhz);
  T T_fkx = -dhx - dgx;
  T T_fky = -dhy - dgy;
  T T_fkz = -dhz - dgz;
  storeForces<T>(T_fkx, T_fky, T_fkz, dl.k, stride, force);
  storeForces<T>(dhx, dhy, dhz, dl.l, stride, force);

  // Store virial
  if (doVirial) {
#ifdef WRITE_FULL_VIRIALS
    float fix = ((float)T_fix)*force_to_float;
    float fiy = ((float)T_fiy)*force_to_float;
    float fiz = ((float)T_fiz)*force_to_float;
    float fjx = ((float)dgx)*force_to_float;
    float fjy = ((float)dgy)*force_to_float;
    float fjz = ((float)dgz)*force_to_float;
    float flx = ((float)dhx)*force_to_float;
    float fly = ((float)dhy)*force_to_float;
    float flz = ((float)dhz)*force_to_float;
    virial.xx = (fix*xij) + (fjx*xjk) + (flx*xlk);
    virial.xy = (fix*yij) + (fjx*yjk) + (flx*ylk);
    virial.xz = (fix*zij) + (fjx*zjk) + (flx*zlk);
    virial.yx = (fiy*xij) + (fjy*xjk) + (fly*xlk);
    virial.yy = (fiy*yij) + (fjy*yjk) + (fly*ylk);
    virial.yz = (fiy*zij) + (fjy*zjk) + (fly*zlk);
    virial.zx = (fiz*xij) + (fjz*xjk) + (flz*xlk);
    virial.zy = (fiz*yij) + (fjz*yjk) + (flz*ylk);
    virial.zz = (fiz*zij) + (fjz*zjk) + (flz*zlk);
#endif
  }

}

NAMD_INLINE sycl::float3 cross(const sycl::float3 v1,
                                   const sycl::float3 v2) {
 return sycl::float3(
     v1.y() * v2.z() - v2.y() * v1.z(),
     v2.x() * v1.z() - v1.x() * v2.z(),
     v1.x() * v2.y() - v2.x() * v1.y());
}

NAMD_INLINE float dot(const sycl::float3 v1, const sycl::float3 v2) {
  return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
}

//
// Calculates crossterms
//
template <typename T, bool doEnergy, bool doVirial>
void crosstermForce(
    const int index, const DpcppCrossterm *__restrict__ crosstermList,
    const DpcppCrosstermValue *__restrict__ crosstermValues,
    const sycl::float4 *__restrict__ xyzq, const int stride,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    T *__restrict__ force, double &energy,
#ifdef WRITE_FULL_VIRIALS
    DpcppComputeBondedKernel::BondedVirial<double> &virial
#else
    DpcppComputeBondedKernel::BondedVirial *__restrict__ virial
#endif
) {

  DpcppCrossterm cl = crosstermList[index];

  // ----------------------------------------------------------------------------
  // Angle between 1 - 2 - 3 - 4
  //
  // 1 - 2
  sycl::float3 sh12 = sycl::float3(
      cl.offset12XYZ.x() * lata.x() + cl.offset12XYZ.y() * latb.x() +
          cl.offset12XYZ.z() * latc.x(),
      cl.offset12XYZ.x() * lata.y() + cl.offset12XYZ.y() * latb.y() +
          cl.offset12XYZ.z() * latc.y(),
      cl.offset12XYZ.x() * lata.z() + cl.offset12XYZ.y() * latb.z() +
          cl.offset12XYZ.z() * latc.z());

  sycl::float4 xyzq1 = xyzq[cl.i1];
  sycl::float4 xyzq2 = xyzq[cl.i2];

  sycl::float3 r12 = sycl::float3(
      xyzq1.x() + sh12.x() - xyzq2.x(),
      xyzq1.y() + sh12.y() - xyzq2.y(),
      xyzq1.z() + sh12.z() - xyzq2.z());

  // 2 - 3
  sycl::float3 sh23 = sycl::float3(
      cl.offset23XYZ.x() * lata.x() + cl.offset23XYZ.y() * latb.x() +
          cl.offset23XYZ.z() * latc.x(),
      cl.offset23XYZ.x() * lata.y() + cl.offset23XYZ.y() * latb.y() +
          cl.offset23XYZ.z() * latc.y(),
      cl.offset23XYZ.x() * lata.z() + cl.offset23XYZ.y() * latb.z() +
          cl.offset23XYZ.z() * latc.z());

  sycl::float4 xyzq3 = xyzq[cl.i3];

  sycl::float3 r23 = sycl::float3(
      xyzq2.x() + sh23.x() - xyzq3.x(),
      xyzq2.y() + sh23.y() - xyzq3.y(),
      xyzq2.z() + sh23.z() - xyzq3.z());

  // 3 - 4
  sycl::float3 sh34 = sycl::float3(
      cl.offset34XYZ.x() * lata.x() + cl.offset34XYZ.y() * latb.x() +
          cl.offset34XYZ.z() * latc.x(),
      cl.offset34XYZ.x() * lata.y() + cl.offset34XYZ.y() * latb.y() +
          cl.offset34XYZ.z() * latc.y(),
      cl.offset34XYZ.x() * lata.z() + cl.offset34XYZ.y() * latb.z() +
          cl.offset34XYZ.z() * latc.z());

  sycl::float4 xyzq4 = xyzq[cl.i4];

  sycl::float3 r34 = sycl::float3(
      xyzq3.x() + sh34.x() - xyzq4.x(),
      xyzq3.y() + sh34.y() - xyzq4.y(),
      xyzq3.z() + sh34.z() - xyzq4.z());

  // Calculate the cross products
  sycl::float3 A = cross(r12, r23);
  sycl::float3 B = cross(r23, r34);
  sycl::float3 C = cross(r23, A);

  // Calculate the inverse distances
  float inv_rA = sycl::rsqrt(dot(A, A));
  float inv_rB = sycl::rsqrt(dot(B, B));
  float inv_rC = sycl::rsqrt(dot(C, C));

  //  Calculate the sin and cos
  float cos_phi = dot(A, B)*(inv_rA*inv_rB);
  float sin_phi = dot(C, B)*(inv_rC*inv_rB);

  float phi = -sycl::atan2(sin_phi, cos_phi);

  // ----------------------------------------------------------------------------
  // Angle between 5 - 6 - 7 - 8
  //

  // 5 - 6
  sycl::float3 sh56 = sycl::float3(
      cl.offset56XYZ.x() * lata.x() + cl.offset56XYZ.y() * latb.x() +
          cl.offset56XYZ.z() * latc.x(),
      cl.offset56XYZ.x() * lata.y() + cl.offset56XYZ.y() * latb.y() +
          cl.offset56XYZ.z() * latc.y(),
      cl.offset56XYZ.x() * lata.z() + cl.offset56XYZ.y() * latb.z() +
          cl.offset56XYZ.z() * latc.z());

  sycl::float4 xyzq5 = xyzq[cl.i5];
  sycl::float4 xyzq6 = xyzq[cl.i6];

  sycl::float3 r56 = sycl::float3(
      xyzq5.x() + sh56.x() - xyzq6.x(),
      xyzq5.y() + sh56.y() - xyzq6.y(),
      xyzq5.z() + sh56.z() - xyzq6.z());

  // 6 - 7
  sycl::float3 sh67 = sycl::float3(
      cl.offset67XYZ.x() * lata.x() + cl.offset67XYZ.y() * latb.x() +
          cl.offset67XYZ.z() * latc.x(),
      cl.offset67XYZ.x() * lata.y() + cl.offset67XYZ.y() * latb.y() +
          cl.offset67XYZ.z() * latc.y(),
      cl.offset67XYZ.x() * lata.z() + cl.offset67XYZ.y() * latb.z() +
          cl.offset67XYZ.z() * latc.z());

  sycl::float4 xyzq7 = xyzq[cl.i7];

  sycl::float3 r67 = sycl::float3(
      xyzq6.x() + sh67.x() - xyzq7.x(),
      xyzq6.y() + sh67.y() - xyzq7.y(),
      xyzq6.z() + sh67.z() - xyzq7.z());

  // 7 - 8
  sycl::float3 sh78 = sycl::float3(
      cl.offset78XYZ.x() * lata.x() + cl.offset78XYZ.y() * latb.x() +
          cl.offset78XYZ.z() * latc.x(),
      cl.offset78XYZ.x() * lata.y() + cl.offset78XYZ.y() * latb.y() +
          cl.offset78XYZ.z() * latc.y(),
      cl.offset78XYZ.x() * lata.z() + cl.offset78XYZ.y() * latb.z() +
          cl.offset78XYZ.z() * latc.z());

  sycl::float4 xyzq8 = xyzq[cl.i8];

  sycl::float3 r78 = sycl::float3(
      xyzq7.x() + sh78.x() - xyzq8.x(),
      xyzq7.y() + sh78.y() - xyzq8.y(),
      xyzq7.z() + sh78.z() - xyzq8.z());

  // Calculate the cross products
  sycl::float3 D = cross(r56, r67);
  sycl::float3 E = cross(r67, r78);
  sycl::float3 F = cross(r67, D);

  // Calculate the inverse distances
  float inv_rD = sycl::rsqrt(dot(D, D));
  float inv_rE = sycl::rsqrt(dot(E, E));
  float inv_rF = sycl::rsqrt(dot(F, F));

  //  Calculate the sin and cos
  float cos_psi = dot(D, E)*(inv_rD*inv_rE);
  float sin_psi = dot(F, E)*(inv_rF*inv_rE);

  float psi = -sycl::atan2(sin_psi, cos_psi);

  // ----------------------------------------------------------------------------
  // Calculate the energy

  const float inv_h = (float)( (DpcppCrosstermValue::dim) / (2.0*M_PI) );

  // Shift angles
  phi = sycl::fmod(phi + (float)M_PI, 2.0f * (float)M_PI);
  psi = sycl::fmod(psi + (float)M_PI, 2.0f * (float)M_PI);

  // distance measured in grid points between angle and smallest value
  float phi_h = phi * inv_h;
  float psi_h = psi * inv_h;

  // find smallest numbered grid point in stencil
  int iphi = (int)sycl::floor(phi_h);
  int ipsi = (int)sycl::floor(psi_h);

  const DpcppCrosstermValue& cp = crosstermValues[cl.itype];

  // Load coefficients
  sycl::float4 c[4];
  c[0] = cp.c[iphi][ipsi][0];
  c[1] = cp.c[iphi][ipsi][1];
  c[2] = cp.c[iphi][ipsi][2];
  c[3] = cp.c[iphi][ipsi][3];

  float dphi = phi_h - (float)iphi;
  float dpsi = psi_h - (float)ipsi;

  if (doEnergy) {
    float energyf =
        c[3].x() + dphi * (c[3].y() + dphi * (c[3].z() + dphi * c[3].w()));
    energyf = energyf * dpsi + c[2].x() +
              dphi * (c[2].y() + dphi * (c[2].z() + dphi * c[2].w()));
    energyf = energyf * dpsi + c[1].x() +
              dphi * (c[1].y() + dphi * (c[1].z() + dphi * c[1].w()));
    energyf = energyf * dpsi + c[0].x() +
              dphi * (c[0].y() + dphi * (c[0].z() + dphi * c[0].w()));
    energy += energyf*cl.scale;
  }

  float dEdphi =
      3.0f *
      (c[0].w() + dpsi * (c[1].w() + dpsi * (c[2].w() + dpsi * c[3].w())));
  dEdphi = dEdphi * dphi +
           2.0f * (c[0].z() +
                   dpsi * (c[1].z() + dpsi * (c[2].z() + dpsi * c[3].z())));
  dEdphi = dEdphi * dphi +
           (c[0].y() +
            dpsi * (c[1].y() + dpsi * (c[2].y() + dpsi * c[3].y()))); // 13 muls
  dEdphi *= cl.scale*inv_h;

  float dEdpsi =
      3.0f *
      (c[3].x() + dphi * (c[3].y() + dphi * (c[3].z() + dphi * c[3].w())));
  dEdpsi = dEdpsi * dpsi +
           2.0f * (c[2].x() +
                   dphi * (c[2].y() + dphi * (c[2].z() + dphi * c[2].w())));
  dEdpsi = dEdpsi * dpsi +
           (c[1].x() +
            dphi * (c[1].y() + dphi * (c[1].z() + dphi * c[1].w()))); // 13 muls
  dEdpsi *= cl.scale*inv_h;

  // float normCross1 = dot(A, A);
  float square_r23 = dot(r23, r23);
  float norm_r23 = sycl::sqrt(square_r23);
  float inv_square_r23 = 1.0f/square_r23;
  float ff1 = dEdphi*norm_r23*inv_rA*inv_rA;
  float ff2 = -dot(r12, r23)*inv_square_r23;
  float ff3 = -dot(r34, r23)*inv_square_r23;
  float ff4 = -dEdphi*norm_r23*inv_rB*inv_rB;

  sycl::float3 f1 = sycl::float3(ff1 * A.x(), ff1 * A.y(), ff1 * A.z());
  sycl::float3 f4 = sycl::float3(ff4 * B.x(), ff4 * B.y(), ff4 * B.z());
  sycl::float3 t1 =
      sycl::float3(ff2 * f1.x() - ff3 * f4.x(), ff2 * f1.y() - ff3 * f4.y(),
                   ff2 * f1.z() - ff3 * f4.z());
  sycl::float3 f2 =
      sycl::float3(t1.x() - f1.x(), t1.y() - f1.y(), t1.z() - f1.z());
  sycl::float3 f3 =
      sycl::float3(-t1.x() - f4.x(), -t1.y() - f4.y(), -t1.z() - f4.z());

  T T_f1x, T_f1y, T_f1z;
  T T_f2x, T_f2y, T_f2z;
  T T_f3x, T_f3y, T_f3z;
  T T_f4x, T_f4y, T_f4z;
  convertForces<T>(f1.x(), f1.y(), f1.z(), T_f1x, T_f1y, T_f1z);
  convertForces<T>(f2.x(), f2.y(), f2.z(), T_f2x, T_f2y, T_f2z);
  convertForces<T>(f3.x(), f3.y(), f3.z(), T_f3x, T_f3y, T_f3z);
  convertForces<T>(f4.x(), f4.y(), f4.z(), T_f4x, T_f4y, T_f4z);
  storeForces<T>(T_f1x, T_f1y, T_f1z, cl.i1, stride, force);
  storeForces<T>(T_f2x, T_f2y, T_f2z, cl.i2, stride, force);
  storeForces<T>(T_f3x, T_f3y, T_f3z, cl.i3, stride, force);
  storeForces<T>(T_f4x, T_f4y, T_f4z, cl.i4, stride, force);

  float square_r67 = dot(r67, r67);
  float norm_r67 = sycl::sqrt(square_r67);
  float inv_square_r67 = 1.0f/(square_r67);
  ff1 = dEdpsi*norm_r67*inv_rD*inv_rD;
  ff2 = -dot(r56, r67)*inv_square_r67;
  ff3 = -dot(r78, r67)*inv_square_r67;
  ff4 = -dEdpsi*norm_r67*inv_rE*inv_rE;

  sycl::float3 f5 = sycl::float3(ff1 * D.x(), ff1 * D.y(), ff1 * D.z());
  sycl::float3 f8 = sycl::float3(ff4 * E.x(), ff4 * E.y(), ff4 * E.z());
  sycl::float3 t2 =
      sycl::float3(ff2 * f5.x() - ff3 * f8.x(), ff2 * f5.y() - ff3 * f8.y(),
                   ff2 * f5.z() - ff3 * f8.z());
  sycl::float3 f6 =
      sycl::float3(t2.x() - f5.x(), t2.y() - f5.y(), t2.z() - f5.z());
  sycl::float3 f7 =
      sycl::float3(-t2.x() - f8.x(), -t2.y() - f8.y(), -t2.z() - f8.z());

  T T_f5x, T_f5y, T_f5z;
  T T_f6x, T_f6y, T_f6z;
  T T_f7x, T_f7y, T_f7z;
  T T_f8x, T_f8y, T_f8z;
  convertForces<T>(f5.x(), f5.y(), f5.z(), T_f5x, T_f5y, T_f5z);
  convertForces<T>(f6.x(), f6.y(), f6.z(), T_f6x, T_f6y, T_f6z);
  convertForces<T>(f7.x(), f7.y(), f7.z(), T_f7x, T_f7y, T_f7z);
  convertForces<T>(f8.x(), f8.y(), f8.z(), T_f8x, T_f8y, T_f8z);
  storeForces<T>(T_f5x, T_f5y, T_f5z, cl.i5, stride, force);
  storeForces<T>(T_f6x, T_f6y, T_f6z, cl.i6, stride, force);
  storeForces<T>(T_f7x, T_f7y, T_f7z, cl.i7, stride, force);
  storeForces<T>(T_f8x, T_f8y, T_f8z, cl.i8, stride, force);

  // Store virial
  if (doVirial) {
#ifdef WRITE_FULL_VIRIALS
    sycl::float3 s12 =
        sycl::float3(f1.x() + f2.x(), f1.y() + f2.y(), f1.z() + f2.z());
    sycl::float3 s56 =
        sycl::float3(f5.x() + f6.x(), f5.y() + f6.y(), f5.z() + f6.z());
    virial.xx = f1.x()*r12.x() + s12.x()*r23.x() - f4.x()*r34.x() + f5.x()*r56.x() + s56.x()*r67.x() - f8.x()*r78.x();
    virial.xy = f1.x()*r12.y() + s12.x()*r23.y() - f4.x()*r34.y() + f5.x()*r56.y() + s56.x()*r67.y() - f8.x()*r78.y();
    virial.xz = f1.x()*r12.z() + s12.x()*r23.z() - f4.x()*r34.z() + f5.x()*r56.z() + s56.x()*r67.z() - f8.x()*r78.z();
    virial.yx = f1.y()*r12.x() + s12.y()*r23.x() - f4.y()*r34.x() + f5.y()*r56.x() + s56.y()*r67.x() - f8.y()*r78.x();
    virial.yy = f1.y()*r12.y() + s12.y()*r23.y() - f4.y()*r34.y() + f5.y()*r56.y() + s56.y()*r67.y() - f8.y()*r78.y();
    virial.yz = f1.y()*r12.z() + s12.y()*r23.z() - f4.y()*r34.z() + f5.y()*r56.z() + s56.y()*r67.z() - f8.y()*r78.z();
    virial.zx = f1.z()*r12.x() + s12.z()*r23.x() - f4.z()*r34.x() + f5.z()*r56.x() + s56.z()*r67.x() - f8.z()*r78.x();
    virial.zy = f1.z()*r12.y() + s12.z()*r23.y() - f4.z()*r34.y() + f5.z()*r56.y() + s56.z()*r67.y() - f8.z()*r78.y();
    virial.zz = f1.z()*r12.z() + s12.z()*r23.z() - f4.z()*r34.z() + f5.z()*r56.z() + s56.z()*r67.z() - f8.z()*r78.z();
  }
#endif

}

#define BONDEDFORCESKERNEL_NUM_WARP 4
//
// Calculates all forces in a single kernel call
//
template <typename T, bool doEnergy, bool doVirial>
void bondedForcesKernel(
    const int start,

    const int numBonds, const DpcppBond *__restrict__ bonds,
    const DpcppBondValue *__restrict__ bondValues,

    const int numAngles, const DpcppAngle *__restrict__ angles,
    const DpcppAngleValue *__restrict__ angleValues,

    const int numDihedrals, const DpcppDihedral *__restrict__ dihedrals,
    const DpcppDihedralValue *__restrict__ dihedralValues,

    const int numImpropers, const DpcppDihedral *__restrict__ impropers,
    const DpcppDihedralValue *__restrict__ improperValues,

    const int numExclusions, const DpcppExclusion *__restrict__ exclusions,

    const int numCrossterms, const DpcppCrossterm *__restrict__ crossterms,
    const DpcppCrosstermValue *__restrict__ crosstermValues,

    const float cutoff2, const float r2_delta, const int r2_delta_expc,

    const float *__restrict__ r2_table,

    const sycl::float4 *__restrict__ exclusionTable,
    const sycl::float4 *__restrict__ xyzq, const int stride,

    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    T *__restrict__ force, T *__restrict__ forceSlow,
    double *__restrict__ energies_virials,
    queue &myQ,  int rangeSize, int workGroupSize) {

  myQ.submit([&](handler &cgh) {
    sycl::accessor<double, 1, sycl::access::mode::read_write, sycl::access::target::local>
        shEnergy_acc_ct1(sycl::range<1>(BONDEDFORCESKERNEL_NUM_WARP), cgh);
    sycl::accessor<DpcppComputeBondedKernel::BondedVirial<double>, 1,
        sycl::access::mode::read_write, sycl::access::target::local>
        shVirial_acc_ct1(sycl::range<1>(BONDEDFORCESKERNEL_NUM_WARP), cgh);
 
    cgh.parallel_for<class bondedForceKernel_offload>(
        nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
        [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {

  double *shEnergy = shEnergy_acc_ct1.get_pointer(); 
  DpcppComputeBondedKernel::BondedVirial<double> *shVirial = shVirial_acc_ct1.get_pointer();

  // Thread-block index

  int indexTB = start + item_ct1.get_group(2);
  auto sg = item_ct1.get_sub_group();


  const int numBondsTB = (numBonds + item_ct1.get_local_range().get(2) - 1) /
                         item_ct1.get_local_range().get(2);
  const int numAnglesTB = (numAngles + item_ct1.get_local_range().get(2) - 1) /
                          item_ct1.get_local_range().get(2);
  const int numDihedralsTB =
      (numDihedrals + item_ct1.get_local_range().get(2) - 1) /
      item_ct1.get_local_range().get(2);
  const int numImpropersTB =
      (numImpropers + item_ct1.get_local_range().get(2) - 1) /
      item_ct1.get_local_range().get(2);
  const int numExclusionsTB =
      (numExclusions + item_ct1.get_local_range().get(2) - 1) /
      item_ct1.get_local_range().get(2);
  const int numCrosstermsTB =
      (numCrossterms + item_ct1.get_local_range().get(2) - 1) /
      item_ct1.get_local_range().get(2);

  // Each thread computes single bonded interaction.
  // Each thread block computes single bonded type
  double energy;
  int energyIndex;

  if (doEnergy) {
    energy = 0.0;
    energyIndex = -1;
  }

#ifdef WRITE_FULL_VIRIALS
  DpcppComputeBondedKernel::BondedVirial<double> virial;
  int virialIndex;
  if (doVirial) {
    virial.xx = 0.0;
    virial.xy = 0.0;
    virial.xz = 0.0;
    virial.yx = 0.0;
    virial.yy = 0.0;
    virial.yz = 0.0;
    virial.zx = 0.0;
    virial.zy = 0.0;
    virial.zz = 0.0;
    virialIndex = DpcppComputeBondedKernel::normalVirialIndex_XX;
  }
#endif

  if (indexTB < numBondsTB) {
    int i =
        item_ct1.get_local_id(2) + indexTB * item_ct1.get_local_range().get(2);
    if (doEnergy) {
      energyIndex = DpcppComputeBondedKernel::energyIndex_BOND;
    }
    if (i < numBonds) {
      bondForce<T, doEnergy, doVirial>
      (i, bonds, bondValues, xyzq,
        stride, lata, latb, latc,
        force, energy, virial);
    }
    goto reduce;
  }
  indexTB -= numBondsTB;

  if (indexTB < numAnglesTB) {
    int i =
        item_ct1.get_local_id(2) + indexTB * item_ct1.get_local_range().get(2);
    if (doEnergy) {
      energyIndex = DpcppComputeBondedKernel::energyIndex_ANGLE;
    }
    if (i < numAngles) {
      angleForce<T, doEnergy, doVirial>
      (i, angles, angleValues, xyzq, stride,
        lata, latb, latc,
        force, energy, virial);
    }
    goto reduce;
  }
  indexTB -= numAnglesTB;

  if (indexTB < numDihedralsTB) {
    int i =
        item_ct1.get_local_id(2) + indexTB * item_ct1.get_local_range().get(2);
    if (doEnergy) {
      energyIndex = DpcppComputeBondedKernel::energyIndex_DIHEDRAL;
    }
    if (doVirial) {
      virialIndex = DpcppComputeBondedKernel::amdDiheVirialIndex_XX;
    }
    if (i < numDihedrals) {
      diheForce<T, doEnergy, doVirial>
      (i, dihedrals, dihedralValues, xyzq, stride,
        lata, latb, latc,
        force, energy, virial);
    }
    goto reduce;
  }
  indexTB -= numDihedralsTB;

  if (indexTB < numImpropersTB) {
    int i =
        item_ct1.get_local_id(2) + indexTB * item_ct1.get_local_range().get(2);
    if (doEnergy) {
      energyIndex = DpcppComputeBondedKernel::energyIndex_IMPROPER;
    }
    if (i < numImpropers) {
      diheForce<T, doEnergy, doVirial>
      (i, impropers, improperValues, xyzq, stride,
        lata, latb, latc,
        force, energy, virial);
    }
    goto reduce;
  }
  indexTB -= numImpropersTB;

  if (indexTB < numExclusionsTB) {
    int i =
        item_ct1.get_local_id(2) + indexTB * item_ct1.get_local_range().get(2);
    if (doEnergy) {
      energyIndex = DpcppComputeBondedKernel::energyIndex_ELECT_SLOW;
    }
    if (doVirial) {
      virialIndex = DpcppComputeBondedKernel::slowVirialIndex_XX;
    }
    if (i < numExclusions) {
      exclusionForce<T, doEnergy, doVirial>
      (i, exclusions, r2_delta, r2_delta_expc,
        r2_table, exclusionTable,
        xyzq, stride, lata, latb, latc, cutoff2,
        forceSlow, energy, virial);
    }
    goto reduce;
  }
  indexTB -= numExclusionsTB;

  if (indexTB < numCrosstermsTB) {
    int i =
        item_ct1.get_local_id(2) + indexTB * item_ct1.get_local_range().get(2);
    if (doEnergy) {
      energyIndex = DpcppComputeBondedKernel::energyIndex_CROSSTERM;
    }
    if (doVirial) {
      virialIndex = DpcppComputeBondedKernel::amdDiheVirialIndex_XX;
    }
    if (i < numCrossterms) {
      crosstermForce<T, doEnergy, doVirial>
      (i, crossterms, crosstermValues,
        xyzq, stride, lata, latb, latc,
        force, energy, virial);
    }
    goto reduce;
  }
  // indexTB -= numCrosstermsTB;

  reduce:

  // Write energies to global memory
  if (doEnergy) {
    // energyIndex is constant within thread-block
//#pragma unroll
    for (int i=(AVXSIZE/2);i >= 1;i/=2) {
      energy += sg.shuffle_xor(energy, i);
    }
    int laneID = (item_ct1.get_local_id(2) & (AVXSIZE - 1));
    int warpID = item_ct1.get_local_id(2) / AVXSIZE;
    if (laneID == 0) {
      shEnergy[warpID] = energy;
    }
    item_ct1.barrier();
    if (warpID == 0) {
      energy = (laneID < BONDEDFORCESKERNEL_NUM_WARP) ? shEnergy[laneID] : 0.0;
//#pragma unroll
      for (int i=(AVXSIZE/2);i >= 1;i/=2) {
        energy += sg.shuffle_xor(energy, i);
      }
      if (laneID == 0) {
        ATOMIC_FETCH_ADD(double, energies_virials[energyIndex], energy);
      }
    }
  }

  // Write virials to global memory
#ifdef WRITE_FULL_VIRIALS
  if (doVirial) {
//#pragma unroll
    for (int i=(AVXSIZE/2);i >= 1;i/=2) {
      virial.xx += sg.shuffle_xor(virial.xx, i);
      virial.xy += sg.shuffle_xor(virial.xy, i);
      virial.xz += sg.shuffle_xor(virial.xz, i);
      virial.yx += sg.shuffle_xor(virial.yx, i);
      virial.yy += sg.shuffle_xor(virial.yy, i);
      virial.yz += sg.shuffle_xor(virial.yz, i);
      virial.zx += sg.shuffle_xor(virial.zx, i);
      virial.zy += sg.shuffle_xor(virial.zy, i);
      virial.zz += sg.shuffle_xor(virial.zz, i);
    }
    int laneID = (item_ct1.get_local_id(2) & (AVXSIZE - 1));
    int warpID = item_ct1.get_local_id(2) / AVXSIZE;
    if (laneID == 0) {
      shVirial[warpID] = virial;
    }
    item_ct1.barrier();

    if (warpID == 0) {
      virial.xx = 0.0;
      virial.xy = 0.0;
      virial.xz = 0.0;
      virial.yx = 0.0;
      virial.yy = 0.0;
      virial.yz = 0.0;
      virial.zx = 0.0;
      virial.zy = 0.0;
      virial.zz = 0.0;
      if (laneID < BONDEDFORCESKERNEL_NUM_WARP) virial = shVirial[laneID];
//#pragma unroll
      for (int i=(AVXSIZE/2);i >= 1;i/=2) {
        virial.xx += sg.shuffle_xor(virial.xx, i);
        virial.xy += sg.shuffle_xor(virial.xy, i);
        virial.xz += sg.shuffle_xor(virial.xz, i);
        virial.yx += sg.shuffle_xor(virial.yx, i);
        virial.yy += sg.shuffle_xor(virial.yy, i);
        virial.yz += sg.shuffle_xor(virial.yz, i);
        virial.zx += sg.shuffle_xor(virial.zx, i);
        virial.zy += sg.shuffle_xor(virial.zy, i);
        virial.zz += sg.shuffle_xor(virial.zz, i);
      }   

      if (laneID == 0) {
        ATOMIC_ADD(double, energies_virials[virialIndex + 0], virial.xx);
        ATOMIC_ADD(double, energies_virials[virialIndex + 1], virial.xy);
        ATOMIC_ADD(double, energies_virials[virialIndex + 2], virial.xz);
        ATOMIC_ADD(double, energies_virials[virialIndex + 3], virial.yx);
        ATOMIC_ADD(double, energies_virials[virialIndex + 4], virial.yy);
        ATOMIC_ADD(double, energies_virials[virialIndex + 5], virial.yz);
        ATOMIC_ADD(double, energies_virials[virialIndex + 6], virial.zx);
        ATOMIC_ADD(double, energies_virials[virialIndex + 7], virial.zy);
        ATOMIC_ADD(double, energies_virials[virialIndex + 8], virial.zz);
      }
    }
  }
#endif

  }); // cgs.parallel_for
  }); // q.submit
//  myQ.wait();
}

template <typename T, bool doEnergy, bool doVirial, bool doElect>
void modifiedExclusionForcesKernel(
    const int start,

    const int numModifiedExclusions,
    const DpcppExclusion *__restrict__ modifiedExclusions,

    const bool doSlow,
    const float one_scale14, // 1 - scale14
    const float cutoff2, const int vdwCoefTableWidth,
    const sycl::float2 *__restrict__ vdwCoefTable,
    const sycl::float4 *__restrict__ modifiedExclusionForceTable,
    const sycl::float4 *__restrict__ modifiedExclusionEnergyTable, const int feTableSize,
    const sycl::float4 *__restrict__ xyzq, const int stride,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    T *__restrict__ forceNbond, T *__restrict__ forceSlow,
    double *__restrict__ energies_virials,
    queue &myQ,  int rangeSize, int workGroupSize) {

  myQ.submit([&](handler &cgh) {
                                                           \
//    auto float_to_force_ptr_ct1 = float_to_force.get_ptr();                    \
//    auto double_to_virial_ptr_ct1 = double_to_virial.get_ptr();                \

    constexpr int localAllocSize = (doElect) ? BONDEDFORCESKERNEL_NUM_WARP : 1;
    sycl::accessor<double, 1, sycl::access::mode::read_write, sycl::access::target::local>
        shEnergyVdw_acc_ct1(sycl::range<1>(BONDEDFORCESKERNEL_NUM_WARP), cgh);
    sycl::accessor<double, 1, sycl::access::mode::read_write, sycl::access::target::local>
        shEnergyNbond_acc_ct1(sycl::range<1>(localAllocSize), cgh);
    sycl::accessor<double, 1, sycl::access::mode::read_write, sycl::access::target::local>
        shEnergySlow_acc_ct1(sycl::range<1>(localAllocSize), cgh);
    sycl::accessor<DpcppComputeBondedKernel::BondedVirial<double>, 1,
        sycl::access::mode::read_write, sycl::access::target::local>
        shVirialNbond_acc_ct1(sycl::range<1>(BONDEDFORCESKERNEL_NUM_WARP), cgh);
    sycl::accessor<DpcppComputeBondedKernel::BondedVirial<double>, 1,
        sycl::access::mode::read_write,sycl::access::target::local>
        shVirialSlow_acc_ct1(sycl::range<1>(localAllocSize), cgh);

    cgh.parallel_for<class bondedForceKernel_offload>(
        nd_range<3>(range<3>(1, 1, rangeSize), range<3>(1, 1, workGroupSize)),
        [=](nd_item<3> item_ct1) [[intel::reqd_sub_group_size(AVXSIZE)]] {

  // Shared local memory
  double *shEnergyVdw = shEnergyVdw_acc_ct1.get_pointer();
  double *shEnergyNbond = shEnergyNbond_acc_ct1.get_pointer();
  double *shEnergySlow = shEnergySlow_acc_ct1.get_pointer();
  DpcppComputeBondedKernel::BondedVirial<double> *shVirialNbond = shVirialNbond_acc_ct1.get_pointer();
  DpcppComputeBondedKernel::BondedVirial<double> *shVirialSlow = shVirialSlow_acc_ct1.get_pointer();

  // index
  auto sg = item_ct1.get_sub_group();
  int i = item_ct1.get_local_id(2) +
          (start + item_ct1.get_group(2)) * item_ct1.get_local_range().get(2);

  double energyVdw, energyNbond, energySlow;
  if (doEnergy) {
    energyVdw = 0.0;
    if (doElect) {
      energyNbond = 0.0;
      energySlow = 0.0;
    }
  }

#ifdef WRITE_FULL_VIRIALS
  DpcppComputeBondedKernel::BondedVirial<double> virialNbond;
  DpcppComputeBondedKernel::BondedVirial<double> virialSlow;
  if (doVirial) {
    virialNbond.xx = 0.0;
    virialNbond.xy = 0.0;
    virialNbond.xz = 0.0;
    virialNbond.yx = 0.0;
    virialNbond.yy = 0.0;
    virialNbond.yz = 0.0;
    virialNbond.zx = 0.0;
    virialNbond.zy = 0.0;
    virialNbond.zz = 0.0;
    if (doElect) {
      virialSlow.xx = 0.0;
      virialSlow.xy = 0.0;
      virialSlow.xz = 0.0;
      virialSlow.yx = 0.0;
      virialSlow.yy = 0.0;
      virialSlow.yz = 0.0;
      virialSlow.zx = 0.0;
      virialSlow.zy = 0.0;
      virialSlow.zz = 0.0;
    }
  }
#endif

  if (i < numModifiedExclusions)
  {
    modifiedExclusionForce<T, doEnergy, doVirial, doElect>
    (i, modifiedExclusions, doSlow, one_scale14, vdwCoefTableWidth,
      vdwCoefTable,
      modifiedExclusionForceTable, modifiedExclusionEnergyTable, feTableSize,
      xyzq, stride, lata, latb, latc, cutoff2,
      energyVdw, forceNbond, energyNbond,
      forceSlow, energySlow, virialNbond, virialSlow);
  }

  // Write energies to global memory
  if (doEnergy) {
//#pragma unroll
    for (int i=(AVXSIZE/2);i >= 1;i/=2) {
      energyVdw += sg.shuffle_xor(energyVdw, i);
      if (doElect) {
        energyNbond += sg.shuffle_xor(energyNbond, i);
        energySlow += sg.shuffle_xor(energySlow, i);
      }
    }
    int laneID = (item_ct1.get_local_id(2) & (AVXSIZE - 1));
    int warpID = item_ct1.get_local_id(2) / AVXSIZE;
    if (laneID == 0) {
      shEnergyVdw[warpID]   = energyVdw;
      if (doElect) {
        shEnergyNbond[warpID] = energyNbond;
        shEnergySlow[warpID]  = energySlow;
      }
    }
    item_ct1.barrier();
    if (warpID == 0) {
      energyVdw   = (laneID < BONDEDFORCESKERNEL_NUM_WARP) ? shEnergyVdw[laneID] : 0.0;
      if (doElect) {
        energyNbond = (laneID < BONDEDFORCESKERNEL_NUM_WARP) ? shEnergyNbond[laneID] : 0.0;
        energySlow  = (laneID < BONDEDFORCESKERNEL_NUM_WARP) ? shEnergySlow[laneID] : 0.0;
      }
//#pragma unroll
      for (int i=(AVXSIZE/2);i >= 1;i/=2) {
        energyVdw += sg.shuffle_xor(energyVdw, i);
        if (doElect) {
          energyNbond += sg.shuffle_xor(energyNbond, i);
          energySlow += sg.shuffle_xor(energySlow, i);
        }
      }
      if (laneID == 0) {
        ATOMIC_FETCH_ADD(double,
          energies_virials[DpcppComputeBondedKernel::energyIndex_LJ], energyVdw);
        if (doElect) {
          ATOMIC_FETCH_ADD(double,
            energies_virials[DpcppComputeBondedKernel::energyIndex_ELECT], energyNbond);
          ATOMIC_FETCH_ADD(double,
            energies_virials[DpcppComputeBondedKernel::energyIndex_ELECT_SLOW], energySlow);
        }
      }
    }
  }

  // Write virials to global memory
#ifdef WRITE_FULL_VIRIALS
  if (doVirial) {
//#pragma unroll
    for (int i=(AVXSIZE/2);i >= 1;i/=2) {
      virialNbond.xx += sg.shuffle_xor(virialNbond.xx, i);
      virialNbond.xy += sg.shuffle_xor(virialNbond.xy, i);
      virialNbond.xz += sg.shuffle_xor(virialNbond.xz, i);
      virialNbond.yx += sg.shuffle_xor(virialNbond.yx, i);
      virialNbond.yy += sg.shuffle_xor(virialNbond.yy, i);
      virialNbond.yz += sg.shuffle_xor(virialNbond.yz, i);
      virialNbond.zx += sg.shuffle_xor(virialNbond.zx, i);
      virialNbond.zy += sg.shuffle_xor(virialNbond.zy, i);
      virialNbond.zz += sg.shuffle_xor(virialNbond.zz, i);
      if (doElect && doSlow) {
        virialSlow.xx += sg.shuffle_xor(virialSlow.xx, i);
        virialSlow.xy += sg.shuffle_xor(virialSlow.xy, i);
        virialSlow.xz += sg.shuffle_xor(virialSlow.xz, i);
        virialSlow.yx += sg.shuffle_xor(virialSlow.yx, i);
        virialSlow.yy += sg.shuffle_xor(virialSlow.yy, i);
        virialSlow.yz += sg.shuffle_xor(virialSlow.yz, i);
        virialSlow.zx += sg.shuffle_xor(virialSlow.zx, i);
        virialSlow.zy += sg.shuffle_xor(virialSlow.zy, i);
        virialSlow.zz += sg.shuffle_xor(virialSlow.zz, i);
      }
    }
    int laneID = (item_ct1.get_local_id(2) & (AVXSIZE - 1));
    int warpID = item_ct1.get_local_id(2) / AVXSIZE;
    if (laneID == 0) {
      shVirialNbond[warpID] = virialNbond;
      shVirialSlow[warpID] = virialSlow;
    }
    item_ct1.barrier();

    virialNbond.xx = 0.0;
    virialNbond.xy = 0.0;
    virialNbond.xz = 0.0;
    virialNbond.yx = 0.0;
    virialNbond.yy = 0.0;
    virialNbond.yz = 0.0;
    virialNbond.zx = 0.0;
    virialNbond.zy = 0.0;
    virialNbond.zz = 0.0;
    if (doElect && doSlow) {
      virialSlow.xx = 0.0;
      virialSlow.xy = 0.0;
      virialSlow.xz = 0.0;
      virialSlow.yx = 0.0;
      virialSlow.yy = 0.0;
      virialSlow.yz = 0.0;
      virialSlow.zx = 0.0;
      virialSlow.zy = 0.0;
      virialSlow.zz = 0.0;
    }

    if (warpID == 0) {
      if (laneID < BONDEDFORCESKERNEL_NUM_WARP) {
        virialNbond = shVirialNbond[laneID];
        virialSlow = shVirialSlow[laneID];
      }
//#pragma unroll
      for (int i=(AVXSIZE/2);i >= 1;i/=2) {
        virialNbond.xx += sg.shuffle_xor(virialNbond.xx, i);
        virialNbond.xy += sg.shuffle_xor(virialNbond.xy, i);
        virialNbond.xz += sg.shuffle_xor(virialNbond.xz, i);
        virialNbond.yx += sg.shuffle_xor(virialNbond.yx, i);
        virialNbond.yy += sg.shuffle_xor(virialNbond.yy, i);
        virialNbond.yz += sg.shuffle_xor(virialNbond.yz, i);
        virialNbond.zx += sg.shuffle_xor(virialNbond.zx, i);
        virialNbond.zy += sg.shuffle_xor(virialNbond.zy, i);
        virialNbond.zz += sg.shuffle_xor(virialNbond.zz, i);
        if (doElect && doSlow) {
          virialSlow.xx += sg.shuffle_xor(virialSlow.xx, i);
          virialSlow.xy += sg.shuffle_xor(virialSlow.xy, i);
          virialSlow.xz += sg.shuffle_xor(virialSlow.xz, i);
          virialSlow.yx += sg.shuffle_xor(virialSlow.yx, i);
          virialSlow.yy += sg.shuffle_xor(virialSlow.yy, i);
          virialSlow.yz += sg.shuffle_xor(virialSlow.yz, i);
          virialSlow.zx += sg.shuffle_xor(virialSlow.zx, i);
          virialSlow.zy += sg.shuffle_xor(virialSlow.zy, i);
          virialSlow.zz += sg.shuffle_xor(virialSlow.zz, i);
        }
      }

      if (laneID == 0)
      {
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_XX], virialNbond.xx);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_XY], virialNbond.xy);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_XZ], virialNbond.xz);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_YX], virialNbond.yx);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_YY], virialNbond.yy);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_YZ], virialNbond.yz);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_ZX], virialNbond.zx);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_ZY], virialNbond.zy);
        ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::nbondVirialIndex_ZZ], virialNbond.zz);
        if (doElect && doSlow) {
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_XX], virialSlow.xx);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_XY], virialSlow.xy);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_XZ], virialSlow.xz);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_YX], virialSlow.yx);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_YY], virialSlow.yy);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_YZ], virialSlow.yz);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_ZX], virialSlow.zx);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_ZY], virialSlow.zy);
          ATOMIC_ADD(double, energies_virials[DpcppComputeBondedKernel::slowVirialIndex_ZZ], virialSlow.zz);
        }
      }
    }
  }
#endif

  }); // cgs.parallel_for
  }); // q.submit
//  myQ.wait();
}

// ##############################################################################################
// ##############################################################################################
// ##############################################################################################

//
// Class constructor
//
DpcppComputeBondedKernel::DpcppComputeBondedKernel(
    int deviceID, DpcppNonbondedTables &dpcppNonbondedTables) try
    : deviceID(deviceID), dpcppNonbondedTables(dpcppNonbondedTables) {

  dpcppDevice->setDeviceID(deviceID);

  tupleData = NULL;
  tupleDataSize = 0;

  numBonds = 0;
  numAngles = 0;
  numDihedrals = 0;
  numImpropers = 0;
  numModifiedExclusions = 0;
  numExclusions = 0;
  numCrossterms = 0;

  bondValues = NULL;
  angleValues = NULL;
  dihedralValues = NULL;
  improperValues = NULL;
  crosstermValues = NULL;

  xyzq = NULL;
  xyzqSize = 0;

  forces = NULL;
  forcesSize = 0;

  allocate_device<double>(&energies_virials, energies_virials_SIZE);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// Class destructor
//
DpcppComputeBondedKernel::~DpcppComputeBondedKernel() try {
  dpcppDevice->setDeviceID(deviceID);

  deallocate_device<double>(&energies_virials);
  // deallocate_device<BondedVirial>(&virial);

  if (tupleData != NULL) deallocate_device<char>(&tupleData);
  if (xyzq != NULL) deallocate_device(&xyzq);
  if (forces != NULL) deallocate_device<FORCE_TYPE>(&forces);

  if (bondValues != NULL) deallocate_device<DpcppBondValue>(&bondValues);
  if (angleValues != NULL) deallocate_device<DpcppAngleValue>(&angleValues);
  if (dihedralValues != NULL) deallocate_device<DpcppDihedralValue>(&dihedralValues);
  if (improperValues != NULL) deallocate_device<DpcppDihedralValue>(&improperValues);
  if (crosstermValues != NULL) deallocate_device<DpcppCrosstermValue>(&crosstermValues);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppComputeBondedKernel::setupBondValues(int numBondValues, DpcppBondValue* h_bondValues) {
  allocate_device<DpcppBondValue>(&bondValues, numBondValues);
  copy_HtoD_sync<DpcppBondValue>(h_bondValues, bondValues, numBondValues);
  bondValuesSize = numBondValues;
}

void DpcppComputeBondedKernel::setupAngleValues(int numAngleValues, DpcppAngleValue* h_angleValues) {
  allocate_device<DpcppAngleValue>(&angleValues, numAngleValues);
  copy_HtoD_sync<DpcppAngleValue>(h_angleValues, angleValues, numAngleValues);
  angleValuesSize = numAngleValues;
}

void DpcppComputeBondedKernel::setupDihedralValues(int numDihedralValues, DpcppDihedralValue* h_dihedralValues) {
  allocate_device<DpcppDihedralValue>(&dihedralValues, numDihedralValues);
  copy_HtoD_sync<DpcppDihedralValue>(h_dihedralValues, dihedralValues, numDihedralValues);
  dihedralValuesSize = numDihedralValues;
}

void DpcppComputeBondedKernel::setupImproperValues(int numImproperValues, DpcppDihedralValue* h_improperValues) {
  allocate_device<DpcppDihedralValue>(&improperValues, numImproperValues);
  copy_HtoD_sync<DpcppDihedralValue>(h_improperValues, improperValues, numImproperValues);
  improperValuesSize = numImproperValues;
}

void DpcppComputeBondedKernel::setupCrosstermValues(int numCrosstermValues, DpcppCrosstermValue* h_crosstermValues) {
  allocate_device<DpcppCrosstermValue>(&crosstermValues, numCrosstermValues);
  copy_HtoD_sync<DpcppCrosstermValue>(h_crosstermValues, crosstermValues, numCrosstermValues);
  crosstermValuesSize = numCrosstermValues;
}

//
// Update bonded lists
//
void DpcppComputeBondedKernel::update(
    const int numBondsIn, const int numAnglesIn, const int numDihedralsIn,
    const int numImpropersIn, const int numModifiedExclusionsIn,
    const int numExclusionsIn, const int numCrosstermsIn,
    const char *h_tupleData,
     queue myQ) {

  numBonds              = numBondsIn;
  numAngles             = numAnglesIn;
  numDihedrals          = numDihedralsIn;
  numImpropers          = numImpropersIn;
  numModifiedExclusions = numModifiedExclusionsIn;
  numExclusions         = numExclusionsIn;
  numCrossterms         = numCrosstermsIn;

  int numBondsWA     = warpAlign(numBonds);
  int numAnglesWA    = warpAlign(numAngles);
  int numDihedralsWA = warpAlign(numDihedrals);
  int numImpropersWA = warpAlign(numImpropers);
  int numModifiedExclusionsWA = warpAlign(numModifiedExclusions);
  int numExclusionsWA         = warpAlign(numExclusions);
  int numCrosstermsWA         = warpAlign(numCrossterms);

  int sizeTot = numBondsWA*sizeof(DpcppBond) + numAnglesWA*sizeof(DpcppAngle) + 
  numDihedralsWA*sizeof(DpcppDihedral) + numImpropersWA*sizeof(DpcppDihedral) +
  numModifiedExclusionsWA*sizeof(DpcppExclusion) + numExclusionsWA*sizeof(DpcppExclusion) + 
  numCrosstermsWA*sizeof(DpcppCrossterm);

  myQ.wait();
  reallocate_device<char>(&tupleData, &tupleDataSize, sizeTot, 1.4f);
  copy_HtoD<char>(h_tupleData, tupleData, sizeTot, myQ);

  // Setup pointers
  int pos = 0;
  bonds = (DpcppBond *)&tupleData[pos];
  pos += numBondsWA*sizeof(DpcppBond);

  angles = (DpcppAngle* )&tupleData[pos];
  pos += numAnglesWA*sizeof(DpcppAngle);

  dihedrals = (DpcppDihedral* )&tupleData[pos];
  pos += numDihedralsWA*sizeof(DpcppDihedral);

  impropers = (DpcppDihedral* )&tupleData[pos];
  pos += numImpropersWA*sizeof(DpcppDihedral);

  modifiedExclusions = (DpcppExclusion* )&tupleData[pos];
  pos += numModifiedExclusionsWA*sizeof(DpcppExclusion);

  exclusions = (DpcppExclusion* )&tupleData[pos];
  pos += numExclusionsWA*sizeof(DpcppExclusion);

  crossterms = (DpcppCrossterm* )&tupleData[pos];
  pos += numCrosstermsWA*sizeof(DpcppCrossterm);
}

//
// Return stride for force array
//
int DpcppComputeBondedKernel::getForceStride(const int atomStorageSize) {
#ifdef USE_STRIDED_FORCE
  // Align stride to 256 bytes
  return ((atomStorageSize*sizeof(FORCE_TYPE) - 1)/256 + 1)*256/sizeof(FORCE_TYPE);
#else
  return 1;
#endif
}

//
// Return size of single force array
//
int DpcppComputeBondedKernel::getForceSize(const int atomStorageSize) {
#ifdef USE_STRIDED_FORCE
  return (3*getForceStride(atomStorageSize));
#else
  return (3*atomStorageSize);
#endif
}

//
// Return size of the all force arrays
//
int DpcppComputeBondedKernel::getAllForceSize(const int atomStorageSize, const bool doSlow) {

  int forceSize = getForceSize(atomStorageSize);

  if (numModifiedExclusions > 0 || numExclusions > 0) {
    if (doSlow) {
      // All three force arrays [normal, nbond, slow]
      forceSize *= 3;
    } else {
      // Two force arrays [normal, nbond]
      forceSize *= 2;
    }
  }

  return forceSize;
}

//
// Compute bonded forces
//
void DpcppComputeBondedKernel::bondedForce(
    const double scale14, const int atomStorageSize, const bool doEnergy,
    const bool doVirial, const bool doSlow,
    const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
    const float cutoff2, const float r2_delta, const int r2_delta_expc,

    const sycl::float4 *h_xyzq, FORCE_TYPE *h_forces,
    double *h_energies_virials,
     queue myQ) {

  int forceStorageSize = getAllForceSize(atomStorageSize, true);
  int forceCopySize = getAllForceSize(atomStorageSize, doSlow);
  int forceStride = getForceStride(atomStorageSize);

  int forceSize = getForceSize(atomStorageSize);
  int startNbond = forceSize;
  int startSlow = 2*forceSize;

  // Re-allocate coordinate and force arrays if neccessary
  myQ.wait();
  reallocate_device<float4>(&xyzq, &xyzqSize, atomStorageSize, 1.4f);
  reallocate_device<FORCE_TYPE>(&forces, &forcesSize, forceStorageSize, 1.4f);

  // Copy coordinates to device
  copy_HtoD<float4>(h_xyzq, xyzq, atomStorageSize, myQ);

  // Clear force array
  clear_device_array<FORCE_TYPE>(forces, forceCopySize, myQ);
  if (doEnergy || doVirial) {
    clear_device_array<double>(energies_virials, energies_virials_SIZE, myQ);
  }

  float one_scale14 = (float)(1.0 - scale14);

  // If doSlow = false, these exclusions are not calculated
  int numExclusionsDoSlow = doSlow ? numExclusions : 0;

  int workGroupSize = std::min(dpcppDevice->getMaxWorkGroupSize(), AVXSIZE*BONDEDFORCESKERNEL_NUM_WARP);

  // TODO: Use more elegant code to round each term to multiples of workGroupSize
  int numBondsTB     = (numBonds + workGroupSize - 1)/workGroupSize;
  int numAnglesTB    = (numAngles + workGroupSize - 1)/workGroupSize;
  int numDihedralsTB = (numDihedrals + workGroupSize - 1)/workGroupSize;
  int numImpropersTB = (numImpropers + workGroupSize - 1)/workGroupSize;
  int numExclusionsTB= (numExclusionsDoSlow + workGroupSize - 1)/workGroupSize;
  int numCrosstermsTB= (numCrossterms + workGroupSize - 1)/workGroupSize;

  int totalRangeSize = workGroupSize*(numBondsTB + numAnglesTB + numDihedralsTB + numImpropersTB + 
  numExclusionsTB + numCrosstermsTB);
  int shmem_size = 0;

  // printf("%d %d %d %d %d %d totalRangeSize %d\n",
  //  numBonds, numAngles, numDihedrals, numImpropers, numModifiedExclusions, numExclusions, totalRangeSize);

  int start = 0;
  while (start < totalRangeSize)
  {
    int nleft = totalRangeSize - start;
    // TODO: add max range size limit here if needed
    int rangeSize = nleft;

#define CALL(DOENERGY, DOVIRIAL) \
  bondedForcesKernel<FORCE_TYPE, DOENERGY, DOVIRIAL> \
  (start, numBonds, bonds, bondValues, \
    numAngles, angles, angleValues, \
    numDihedrals, dihedrals, dihedralValues, \
    numImpropers, impropers, improperValues, \
    numExclusionsDoSlow, exclusions, \
    numCrossterms, crossterms, crosstermValues, \
    cutoff2, \
    r2_delta, r2_delta_expc, \
    dpcppNonbondedTables.get_r2_table(), dpcppNonbondedTables.getExclusionTable(), \
    xyzq, forceStride, \
    lata, latb, latc, \
    forces, &forces[startSlow], energies_virials, myQ, rangeSize, workGroupSize);

#include "array_debug/ac_pre_bondedForcesKernel.h"

    if (!doEnergy && !doVirial) {
      CALL(0, 0);
    }
    if (!doEnergy && doVirial) {
      CALL(0, 1);
    }
    if (doEnergy && !doVirial) {
      CALL(1, 0);
    }
    if (doEnergy && doVirial) {
      CALL(1, 1);
    }
 
#include "array_debug/ac_post_bondedForcesKernel.h"

#undef CALL
    start += rangeSize;
  }

  workGroupSize = BONDEDFORCESKERNEL_NUM_WARP * AVXSIZE;
  // round up to nearest workGroupSize
  totalRangeSize = ( (numModifiedExclusions-1)/workGroupSize + 1)*workGroupSize;
  
  bool doElect = (one_scale14 == 0.0f) ? false : true;

  start = 0;
  while (start < totalRangeSize)
  {
    int nleft = totalRangeSize - start;
    // TODO: add range size limit here, if needed
    int rangeSize = nleft;

#define CALL(DOENERGY, DOVIRIAL, DOELECT) \
  modifiedExclusionForcesKernel<FORCE_TYPE, DOENERGY, DOVIRIAL, DOELECT> \
  (start, numModifiedExclusions, modifiedExclusions, \
    doSlow, one_scale14, cutoff2, \
    dpcppNonbondedTables.getVdwCoefTableWidth(), dpcppNonbondedTables.getExclusionVdwCoefTable(), \
    dpcppNonbondedTables.getModifiedExclusionForceTable(), dpcppNonbondedTables.getModifiedExclusionEnergyTable(), \
    dpcppNonbondedTables.getModifiedExclusionTableSize(), \
    xyzq, forceStride, lata, latb, latc, \
    &forces[startNbond], &forces[startSlow], energies_virials, myQ, rangeSize, workGroupSize);

#include "array_debug/ac_pre_modifiedExclusionForcesKernel.h"
    if (!doEnergy && !doVirial && !doElect) {
      CALL(0, 0, 0);
    }
    if (!doEnergy && doVirial && !doElect) {
      CALL(0, 1, 0);
    }
    if (doEnergy && !doVirial && !doElect) {
      CALL(1, 0, 0);
    }
    if (doEnergy && doVirial && !doElect) {
      CALL(1, 1, 0);
    }
    if (!doEnergy && !doVirial && doElect) {
      CALL(0, 0, 1);
    }
    if (!doEnergy && doVirial && doElect) {
      CALL(0, 1, 1);
    }
    if (doEnergy && !doVirial && doElect) {
      CALL(1, 0, 1);
    }
    if (doEnergy && doVirial && doElect) {
      CALL(1, 1, 1);
    }    
#include "array_debug/ac_post_modifiedExclusionForcesKernel.h"

#undef CALL
    start += rangeSize;
  }

  copy_DtoH<FORCE_TYPE>(forces, h_forces, forceCopySize, myQ);
  if (doEnergy || doVirial) {
    copy_DtoH<double>(energies_virials, h_energies_virials, energies_virials_SIZE, myQ);
  }
myQ.wait();

//  myQ.wait();
}

#endif // NAMD_DPCPP
