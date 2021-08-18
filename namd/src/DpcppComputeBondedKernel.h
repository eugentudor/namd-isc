#ifndef DPCPPCOMPUTEBONDEDKERNEL_H
#define DPCPPCOMPUTEBONDEDKERNEL_H
#include "DpcppUtils.h"
#include "DpcppTupleTypes.h"
#include "DpcppNonbondedTables.h"

#ifdef NAMD_DPCPP

#include <CL/sycl.hpp>

#define FORCE_TYPE double
#define USE_STRIDED_FORCE

#ifndef USE_STRIDED_FORCE
#error "Non-USE_STRIDED_FORCE not implemented"
#endif

#define VIRIAL_TYPE double

#define WRITE_FULL_VIRIALS

static const float float_to_force = 1.0f;
static const float force_to_float = 1.0f;
static const double force_to_double = 1.0;

class DpcppComputeBondedKernel {
public:

  // Enumeration for energies_virials[]
  enum {energyIndex_BOND=0, energyIndex_ANGLE, energyIndex_DIHEDRAL, energyIndex_IMPROPER,
    energyIndex_ELECT, energyIndex_LJ, energyIndex_ELECT_SLOW, energyIndex_CROSSTERM,
    normalVirialIndex_XX, normalVirialIndex_XY, normalVirialIndex_XZ,
    normalVirialIndex_YX, normalVirialIndex_YY, normalVirialIndex_YZ,
    normalVirialIndex_ZX, normalVirialIndex_ZY, normalVirialIndex_ZZ,
    nbondVirialIndex_XX, nbondVirialIndex_XY, nbondVirialIndex_XZ,
    nbondVirialIndex_YX, nbondVirialIndex_YY, nbondVirialIndex_YZ,
    nbondVirialIndex_ZX, nbondVirialIndex_ZY, nbondVirialIndex_ZZ,
    slowVirialIndex_XX, slowVirialIndex_XY, slowVirialIndex_XZ,
    slowVirialIndex_YX, slowVirialIndex_YY, slowVirialIndex_YZ,
    slowVirialIndex_ZX, slowVirialIndex_ZY, slowVirialIndex_ZZ,
    amdDiheVirialIndex_XX, amdDiheVirialIndex_XY, amdDiheVirialIndex_XZ,
    amdDiheVirialIndex_YX, amdDiheVirialIndex_YY, amdDiheVirialIndex_YZ,
    amdDiheVirialIndex_ZX, amdDiheVirialIndex_ZY, amdDiheVirialIndex_ZZ,
    energies_virials_SIZE};

  template <typename T>
  struct BondedVirial {
#ifdef WRITE_FULL_VIRIALS
    T xx;
    T xy;
    T xz;
    T yx;
    T yy;
    T yz;
    T zx;
    T zy;
    T zz;
#else
#error "non-WRITE_FULL_VIRIALS not implemented yet"
    union {
      double sforce_dp[27][3];
      long long int sforce_fp[27][3];
    };
#endif
  };

private:
  const int deviceID;
  DpcppNonbondedTables& dpcppNonbondedTables;

  // This stores all bonds, angles, dihedrals, and impropers in a single 
  // contigious memory array.
  char* tupleData;
  int tupleDataSize;

  // ---------------------------------------------------------------------------------
  // NOTE: bonds, angles, dihedrals, impropers, etc. - pointers below are 
  // computed pointers pointing to tupleData -array
  // DO NOT DEALLOCATE THESE!
  int numBonds;
  DpcppBond* bonds;

  int numAngles;
  DpcppAngle* angles;

  int numDihedrals;
  DpcppDihedral* dihedrals;

  int numImpropers;
  DpcppDihedral* impropers;

  int numModifiedExclusions;
  DpcppExclusion* modifiedExclusions;

  int numExclusions;
  DpcppExclusion* exclusions;

  int numCrossterms;
  DpcppCrossterm* crossterms;
  // ---------------------------------------------------------------------------------
  
  // Device memory for coordinates
  sycl::float4 *xyzq;
  int xyzqSize;

  // Device memory for forces:
  // [normal, nbond, slow]
  FORCE_TYPE* forces;
  int forcesSize;

  DpcppBondValue* bondValues;
  DpcppAngleValue* angleValues;
  DpcppDihedralValue* dihedralValues;
  DpcppDihedralValue* improperValues;
  DpcppCrosstermValue* crosstermValues;

  int bondValuesSize;
  int angleValuesSize;
  int dihedralValuesSize;
  int improperValuesSize;
  int crosstermValuesSize;

  // Accumulated energy values for every bonded type
  double* energies_virials;

public:

  DpcppComputeBondedKernel(int deviceID, DpcppNonbondedTables& dpcppNonbondedTables);
  ~DpcppComputeBondedKernel();

  static int warpAlign(const int n) {return ((n + AVXSIZE - 1)/AVXSIZE)*AVXSIZE;}

  void update(const int numBondsIn, const int numAnglesIn,
              const int numDihedralsIn, const int numImpropersIn,
              const int numModifiedExclusionsIn, const int numExclusionsIn,
              const int numCrosstermsIn, const char *h_tupleData,
              sycl::queue myQ);

  void setupBondValues(int numBondValues, DpcppBondValue* h_bondValues);
  void setupAngleValues(int numAngleValues, DpcppAngleValue* h_angleValues);
  void setupDihedralValues(int numDihedralValues, DpcppDihedralValue* h_dihedralValues);
  void setupImproperValues(int numImproperValues, DpcppDihedralValue* h_improperValues);
  void setupCrosstermValues(int numCrosstermValues, DpcppCrosstermValue* h_crosstermValues);

  int getForceStride(const int atomStorageSize);
  int getForceSize(const int atomStorageSize);
  int getAllForceSize(const int atomStorageSize, const bool doSlow);

  void bondedForce(
      const double scale14, const int atomStorageSize, const bool doEnergy,
      const bool doVirial, const bool doSlow,
      const sycl::float3 lata, const sycl::float3 latb, const sycl::float3 latc,
      const float cutoff2, const float r2_delta, const int r2_delta_expc,
      const sycl::float4 *h_xyzq, FORCE_TYPE *h_forces, double *h_energies,
      sycl::queue myQ);
};

#endif

#endif // DPCPPCOMPUTEBONDEDKERNEL_H
