#ifndef DPCPPNONBONDEDTABLES_H
#define DPCPPNONBONDEDTABLES_H

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>

class DpcppNonbondedTables {
private:
  const int deviceID;

  cl::sycl::float2 *vdwCoefTable;
  int vdwCoefTableWidth;
  //jhr table sizes 
  int intel_vdwCoefTableSize, intel_feTableSize;
  cl::sycl::float4* d_forceTable;
  cl::sycl::float4* d_energyTable;
  int intel_modifiedExclusionTableSize;
  sycl::float4* d_modifiedExclusionForceTable;
  sycl::float4* d_modifiedExclusionEnergyTable;

  // Exclusions
  cl::sycl::float2 *exclusionVdwCoefTable;

  cl::sycl::float4* exclusionTable;
  float* r2_table;
  int tableSize;

  void buildVdwCoefTable(bool update=false);
  void buildForceAndEnergyTables(int tableSize);

public:
  DpcppNonbondedTables(const int deviceID);
  ~DpcppNonbondedTables();

  cl::sycl::float2* getVdwCoefTable() {return vdwCoefTable;}
  int getVdwCoefTableWidth() {return vdwCoefTableWidth;}

  // jhr  create getters for additional data
  cl::sycl::float4* getForceTable() { return d_forceTable; }
  cl::sycl::float4*  getEnergyTable() { return d_energyTable; }
  int getfeTableSize() { return intel_feTableSize; }
  int getvdwTableSize() { return intel_vdwCoefTableSize; }
  sycl::float4* getModifiedExclusionForceTable() { return d_modifiedExclusionForceTable; }
  sycl::float4*  getModifiedExclusionEnergyTable() { return d_modifiedExclusionEnergyTable; }
  int getModifiedExclusionTableSize() { return intel_modifiedExclusionTableSize; }
  void updateTables();

  cl::sycl::float2* getExclusionVdwCoefTable() {return exclusionVdwCoefTable;}
  sycl::float4 *getExclusionTable() { return exclusionTable; }
  float* get_r2_table() {return r2_table;}
  int getTableSize() {return tableSize;}

};

#endif // NAMD_DPCPP
#endif // DPCPPNONBONDEDTABLES_H
