#include <stdio.h>
#include <algorithm>
#include "ComputeNonbondedUtil.h"
#include "DpcppComputePmeMgr.h"
#include "DpcppPmeSolver.h"
#include "DpcppPmeSolverUtil.h"
#include <chrono>

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>

extern "C" void CcdCallBacksReset(void *ignored, double curWallTime);  // fix Charm++

void writeComplexToDisk(const sycl::float2 *d_data, const int size,
                        const char *filename, sycl::queue *stream) try {
  fprintf(stderr, "writeComplexToDisk %d %s\n", size, filename);
  sycl::float2 *h_data = new sycl::float2[size];
  copy_DtoH<sycl::float2>(d_data, h_data, size, *stream);
  stream->wait();
  FILE *handle = fopen(filename, "w");
  for (int i=0;i < size;i++)
    fprintf(handle, "%f %f\n", h_data[i].x(), h_data[i].y());
  fclose(handle);
  delete [] h_data;
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void writeHostComplexToDisk(const sycl::float2 *h_data, const int size,
                            const char *filename) {
  FILE *handle = fopen(filename, "w");
  for (int i=0;i < size;i++)
    fprintf(handle, "%f %f\n", h_data[i].x(), h_data[i].y());
  fclose(handle);
}

void writeRealToDisk(const float *d_data, const int size, const char *filename,
                     sycl::queue *stream) try {
  fprintf(stderr, "writeRealToDisk %d %s\n", size, filename);
  float* h_data = new float[size];
  copy_DtoH<float>(d_data, h_data, size, *stream);
  stream->wait();
  FILE *handle = fopen(filename, "w");
  for (int i=0;i < size;i++)
    fprintf(handle, "%f\n", h_data[i]);
  fclose(handle);
  delete [] h_data;
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppFFTCompute::plan3D(int *n, int flags) try {
  dpcppDevice->setDeviceID(deviceID);
  forwardPlan = fftwf_plan_dft_r2c_3d(n[2], n[1], n[0], dataSrc, (fftwf_complex*)dataDst, FFTW_ESTIMATE);
  if (!forwardPlan) {
    NAMD_bug("Failed to create forward plan in DpcppFFTCompute::plan3D");
  }
  backwardPlan = fftwf_plan_dft_c2r_3d(n[2], n[1], n[0], (fftwf_complex*)dataDst, dataSrc, FFTW_ESTIMATE);
  if (!backwardPlan) {
    NAMD_bug("Failed to create backward plan in DpcppFFTCompute::plan3D");
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppFFTCompute::plan2D(int *n, int howmany, int flags) try {
  dpcppDevice->setDeviceID(deviceID);
  int nt[2] = {n[1], n[0]};
  forwardPlan = fftwf_plan_many_dft_r2c(2, nt, howmany, dataSrc, NULL, 1, 0,
      (fftwf_complex*)dataDst, NULL, 1, 0, FFTW_ESTIMATE);
  if (!forwardPlan) {
    NAMD_bug("Failed to create forward plan in DpcppFFTCompute::plan2D");
  }
  backwardPlan = fftwf_plan_many_dft_c2r(2, nt, howmany, (fftwf_complex*)dataDst, NULL, 1, 0,
      dataSrc, NULL, 1, 0, FFTW_ESTIMATE);
  if (!backwardPlan) {
    NAMD_bug("Failed to create backward plan in DpcppFFTCompute::plan2D");
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppFFTCompute::plan1DX(int *n, int howmany, int flags) try {
  dpcppDevice->setDeviceID(deviceID);
  forwardPlan = fftwf_plan_many_dft_r2c(1, n, howmany, dataSrc, NULL, 0, 0,
      (fftwf_complex*)dataDst, NULL, 0, 0, FFTW_ESTIMATE);
  if (!forwardPlan) {
    NAMD_bug("Failed to create forward plan in DpcppFFTCompute::plan1DX");
  }
  backwardPlan = fftwf_plan_many_dft_c2r(1, n, howmany, (fftwf_complex*)dataDst, NULL, 0, 0,
      dataSrc, NULL, 0, 0, FFTW_ESTIMATE);
  if (!backwardPlan) {
    NAMD_bug("Failed to create backward plan in DpcppFFTCompute::plan1DX");
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppFFTCompute::plan1DY(int *n, int howmany, int flags) try {
  dpcppDevice->setDeviceID(deviceID);
  forwardPlan = fftwf_plan_many_dft(1, n, howmany, (fftwf_complex*)dataSrc, NULL, 0, 0,
      (fftwf_complex*)dataDst, NULL, 0, 0, FFTW_FORWARD, FFTW_ESTIMATE);
  if (!forwardPlan) {
    NAMD_bug("Failed to create forward plan in DpcppFFTCompute::plan1DY");
  }
  backwardPlan = fftwf_plan_many_dft(1, n, howmany, (fftwf_complex*)dataDst, NULL, 0, 0,
      (fftwf_complex*)dataSrc, NULL, 0, 0, FFTW_BACKWARD, FFTW_ESTIMATE);
  if (!backwardPlan) {
    NAMD_bug("Failed to create backward plan in DpcppFFTCompute::plan1DY");
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppFFTCompute::plan1DZ(int *n, int howmany, int flags) try {
  dpcppDevice->setDeviceID(deviceID);
  forwardPlan = fftwf_plan_many_dft(1, n, howmany, (fftwf_complex*)dataSrc, NULL, 0, 0,
      (fftwf_complex*)dataDst, NULL, 0, 0, FFTW_FORWARD, FFTW_ESTIMATE);
  if (!forwardPlan) {
    NAMD_bug("Failed to create forward plan in DpcppFFTCompute::plan1DZ");
  }
  backwardPlan = fftwf_plan_many_dft(1, n, howmany, (fftwf_complex*)dataDst, NULL, 0, 0,
      (fftwf_complex*)dataSrc, NULL, 0, 0, FFTW_BACKWARD, FFTW_ESTIMATE);
  if (!backwardPlan) {
    NAMD_bug("Failed to create backward plan in DpcppFFTCompute::plan1DZ");
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

DpcppFFTCompute::~DpcppFFTCompute() try {
  dpcppDevice->setDeviceID(deviceID);
  fftwf_destroy_plan(forwardPlan);
  fftwf_destroy_plan(backwardPlan);
  if (dataSrcAllocated) deallocate_device<float>(&dataSrc);
  if (dataDstAllocated) deallocate_device<float>(&dataDst);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

float *DpcppFFTCompute::allocateData(const int dataSizeRequired) try {
  dpcppDevice->setDeviceID(deviceID);
  float* tmp = NULL;
  allocate_device<float>(&tmp, dataSizeRequired);
  return tmp;
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppFFTCompute::forward() try {
  dpcppDevice->setDeviceID(deviceID);
  fftwf_execute(forwardPlan);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppFFTCompute::backward() try {
  dpcppDevice->setDeviceID(deviceID);
  fftwf_execute(backwardPlan);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//###########################################################################
//###########################################################################
//###########################################################################

DpcppPmeKSpaceCompute::DpcppPmeKSpaceCompute(
    PmeGrid pmeGrid, const int permutation,
    const int jblock, const int kblock, double kappa, int deviceID,
    sycl::queue *stream) try
    : PmeKSpaceCompute(pmeGrid, permutation, jblock, kblock, kappa),
      deviceID(deviceID), stream(stream) {

  dpcppDevice->setDeviceID(deviceID);

  // Copy bm1 -> prefac_x on GPU memory
  float *bm1f = new float[pmeGrid.K1];
  float *bm2f = new float[pmeGrid.K2];
  float *bm3f = new float[pmeGrid.K3];
  for (int i=0;i < pmeGrid.K1;i++) bm1f[i] = (float)bm1[i];
  for (int i=0;i < pmeGrid.K2;i++) bm2f[i] = (float)bm2[i];
  for (int i=0;i < pmeGrid.K3;i++) bm3f[i] = (float)bm3[i];
  allocate_device<float>(&d_bm1, pmeGrid.K1);
  allocate_device<float>(&d_bm2, pmeGrid.K2);
  allocate_device<float>(&d_bm3, pmeGrid.K3);
  copy_HtoD_sync<float>(bm1f, d_bm1, pmeGrid.K1);
  copy_HtoD_sync<float>(bm2f, d_bm2, pmeGrid.K2);
  copy_HtoD_sync<float>(bm3f, d_bm3, pmeGrid.K3);
  delete [] bm1f;
  delete [] bm2f;
  delete [] bm3f;
  allocate_device<EnergyVirial>(&d_energyVirial, 1);
  allocate_host<EnergyVirial>(&h_energyVirial, 1);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

DpcppPmeKSpaceCompute::~DpcppPmeKSpaceCompute() try {
  dpcppDevice->setDeviceID(deviceID);
  deallocate_device<float>(&d_bm1);
  deallocate_device<float>(&d_bm2);
  deallocate_device<float>(&d_bm3);
  deallocate_device<EnergyVirial>(&d_energyVirial);
  deallocate_host<EnergyVirial>(&h_energyVirial);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeKSpaceCompute::solve(Lattice &lattice, const bool doEnergy,
                                 const bool doVirial, float *data) try {
#if 0
  // Check lattice to make sure it is updating for constant pressure
  fprintf(stderr, "K-SPACE LATTICE  %g %g %g  %g %g %g  %g %g %g\n",
      lattice.a().x, lattice.a().y, lattice.a().z,
      lattice.b().x, lattice.b().y, lattice.b().z,
      lattice.c().x, lattice.c().y, lattice.c().z);
#endif
  dpcppDevice->setDeviceID(deviceID);

  const bool doEnergyVirial = (doEnergy || doVirial);

  int nfft1, nfft2, nfft3;
  float *prefac1, *prefac2, *prefac3;

  BigReal volume = lattice.volume();
  Vector a_r = lattice.a_r();
  Vector b_r = lattice.b_r();
  Vector c_r = lattice.c_r();
  float recip1x, recip1y, recip1z;
  float recip2x, recip2y, recip2z;
  float recip3x, recip3y, recip3z;

  if (permutation == Perm_Z_cX_Y) {
    // Z, X, Y
    nfft1 = pmeGrid.K3;
    nfft2 = pmeGrid.K1;
    nfft3 = pmeGrid.K2;
    prefac1 = d_bm3;
    prefac2 = d_bm1;
    prefac3 = d_bm2;
    recip1x = c_r.z;
    recip1y = c_r.x;
    recip1z = c_r.y;
    recip2x = a_r.z;
    recip2y = a_r.x;
    recip2z = a_r.y;
    recip3x = b_r.z;
    recip3y = b_r.x;
    recip3z = b_r.y;
  } else if (permutation == Perm_cX_Y_Z) {
    // X, Y, Z
    nfft1 = pmeGrid.K1;
    nfft2 = pmeGrid.K2;
    nfft3 = pmeGrid.K3;
    prefac1 = d_bm1;
    prefac2 = d_bm2;
    prefac3 = d_bm3;
    recip1x = a_r.x;
    recip1y = a_r.y;
    recip1z = a_r.z;
    recip2x = b_r.x;
    recip2y = b_r.y;
    recip2z = b_r.z;
    recip3x = c_r.x;
    recip3y = c_r.y;
    recip3z = c_r.z;
  } else {
    NAMD_bug("DpcppPmeKSpaceCompute::solve, invalid permutation");
  }

  // ncall++;
  // if (ncall == 1) {
  //   char filename[256];
  //   sprintf(filename,"dataf_%d_%d.txt",jblock,kblock);
  //   writeComplexToDisk((sycl::float2*)data, size1*size2*size3, filename, stream);
  // }

  // if (ncall == 1) {
  //   sycl::float2* h_data = new sycl::float2[size1*size2*size3];
  //   sycl::float2* d_data = (sycl::float2*)data;
  //   copy_DtoH<sycl::float2>(d_data, h_data, size1*size2*size3, stream);
  //   cudaCheck(cudaStreamSynchronize(stream));
  //   FILE *handle = fopen("dataf.txt", "w");
  //   for (int z=0;z < pmeGrid.K3;z++) {
  //     for (int y=0;y < pmeGrid.K2;y++) {
  //       for (int x=0;x < pmeGrid.K1/2+1;x++) {
  //         int i;
  //         if (permutation == Perm_cX_Y_Z) {
  //           i = x + y*size1 + z*size1*size2;
  //         } else {
  //           i = z + x*size1 + y*size1*size2;
  //         }
  //         fprintf(handle, "%f %f\n", h_data[i].x, h_data[i].y);
  //       }
  //     }
  //   }
  //   fclose(handle);
  //   delete [] h_data;
  // }

  // Clear energy and virial array if needed
  if (doEnergyVirial) clear_device_array<EnergyVirial>(d_energyVirial, 1, *stream);

  scalar_sum(permutation == Perm_cX_Y_Z, nfft1, nfft2, nfft3, size1, size2,
             size3, kappa, recip1x, recip1y, recip1z, recip2x, recip2y, recip2z,
             recip3x, recip3y, recip3z, volume, prefac1, prefac2, prefac3, j0,
             k0, doEnergyVirial,
             &d_energyVirial->energy, d_energyVirial->virial,
             (sycl::float2 *)data, stream);

  // Copy energy and virial to host if needed
  if (doEnergyVirial) {
    copy_DtoH<EnergyVirial>(d_energyVirial, h_energyVirial, 1, *stream);
    copyEnergyVirialEvent = stream->single_task<class energyVirial_empty_task>([=](){});
  }
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeKSpaceCompute::energyAndVirialCheck(void *arg,
                                                double walltime) try {
  DpcppPmeKSpaceCompute* c = (DpcppPmeKSpaceCompute *)arg;

  auto status = c->copyEnergyVirialEvent
    .get_info<sycl::info::event::command_execution_status>();
  if (status == sycl::info::event_command_status::complete) {
    // Event has occurred
    c->checkCount = 0;
    if (c->pencilXYZPtr != NULL)
      c->pencilXYZPtr->energyAndVirialDone();
    else if (c->pencilZPtr != NULL)
      c->pencilZPtr->energyAndVirialDone();
    else
      NAMD_bug("DpcppPmeKSpaceCompute::energyAndVirialCheck, pencilXYZPtr and pencilZPtr not set");
    return;
  } else {
    // Event has not occurred
    c->checkCount++;
    if (c->checkCount >= 1000000) {
      char errmsg[256];
      sprintf(errmsg,"DpcppPmeKSpaceCompute::energyAndVirialCheck polled %d times",
              c->checkCount);
      dpcppDie(errmsg);
    }
  }

  // Call again
  CcdCallBacksReset(0, walltime);
  CcdCallFnAfter(energyAndVirialCheck, arg, 0.1);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeKSpaceCompute::energyAndVirialSetCallback(
    DpcppPmePencilXYZ *pencilPtr) try {
  dpcppDevice->setDeviceID(deviceID);
  pencilXYZPtr = pencilPtr;
  pencilZPtr = NULL;
  checkCount = 0;
  CcdCallBacksReset(0, CmiWallTimer());
  // Set the call back at 0.1ms
  CcdCallFnAfter(energyAndVirialCheck, this, 0.1);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeKSpaceCompute::energyAndVirialSetCallback(
    DpcppPmePencilZ *pencilPtr) try {
  dpcppDevice->setDeviceID(deviceID);
  pencilXYZPtr = NULL;
  pencilZPtr = pencilPtr;
  checkCount = 0;
  CcdCallBacksReset(0, CmiWallTimer());
  // Set the call back at 0.1ms
  CcdCallFnAfter(energyAndVirialCheck, this, 0.1);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

double DpcppPmeKSpaceCompute::getEnergy() {
  return h_energyVirial->energy;
}

void DpcppPmeKSpaceCompute::getVirial(double *virial) {
  if (permutation == Perm_Z_cX_Y) {
    // h_energyVirial->virial is storing ZZ, ZX, ZY, XX, XY, YY
    virial[0] = h_energyVirial->virial[3];
    virial[1] = h_energyVirial->virial[4];
    virial[2] = h_energyVirial->virial[1];

    virial[3] = h_energyVirial->virial[4];
    virial[4] = h_energyVirial->virial[5];
    virial[5] = h_energyVirial->virial[2];

    virial[6] = h_energyVirial->virial[1];
    virial[7] = h_energyVirial->virial[7];
    virial[8] = h_energyVirial->virial[0];
  } else if (permutation == Perm_cX_Y_Z) {
    // h_energyVirial->virial is storing XX, XY, XZ, YY, YZ, ZZ
    virial[0] = h_energyVirial->virial[0];
    virial[1] = h_energyVirial->virial[1];
    virial[2] = h_energyVirial->virial[2];

    virial[3] = h_energyVirial->virial[1];
    virial[4] = h_energyVirial->virial[3];
    virial[5] = h_energyVirial->virial[4];

    virial[6] = h_energyVirial->virial[2];
    virial[7] = h_energyVirial->virial[4];
    virial[8] = h_energyVirial->virial[5];
  }
}


//###########################################################################
//###########################################################################
//###########################################################################

//
// Class constructor
//
DpcppPmeRealSpaceCompute::DpcppPmeRealSpaceCompute(
    PmeGrid pmeGrid,
    const int jblock, const int kblock, int deviceID, sycl::queue *stream) try
    : PmeRealSpaceCompute(pmeGrid, jblock, kblock), deviceID(deviceID),
      stream(stream) {
  if (dataSize < xsize*ysize*zsize)
    NAMD_bug("DpcppPmeRealSpaceCompute::DpcppPmeRealSpaceCompute, insufficient dataSize");
  dpcppDevice->setDeviceID(deviceID);
  d_atomsCapacity = 0;
  d_atoms = NULL;
  d_forceCapacity = 0;
  d_force = NULL;
  tex_data = NULL;
  tex_data_len = 0;
  allocate_device<float>(&data, dataSize);
  setupGridTexture(data, xsize*ysize*zsize);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// Class desctructor
//
DpcppPmeRealSpaceCompute::~DpcppPmeRealSpaceCompute() try {
  dpcppDevice->setDeviceID(deviceID);
  if (d_atoms != NULL) deallocate_device<DpcppAtom>(&d_atoms);
  if (d_force != NULL) deallocate_device<DpcppForce>(&d_force);
  // if (d_patches != NULL) deallocate_device<PatchInfo>(&d_patches);
  // deallocate_device<double>(&d_selfEnergy);
  deallocate_device<float>(&data);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

// //
// // Copy patches and atoms to device memory
// //
// void DpcppPmeRealSpaceCompute::setPatchesAtoms(const int numPatches, const PatchInfo* patches,
//   const int numAtoms, const DpcppAtom* atoms) {

//   this->numPatches = numPatches;
//   this->numAtoms = numAtoms;

//   // Reallocate device arrays as neccessary
//   reallocate_device<DpcppAtom>(&d_atoms, &d_atomsCapacity, numAtoms, 1.5f);
//   reallocate_device<PatchInfo>(&d_patches, &d_patchesCapacity, numPatches, 1.5f);

//   // Copy atom and patch data to device
//   copy_HtoD<DpcppAtom>(atoms, d_atoms, numAtoms, stream);
//   copy_HtoD<PatchInfo>(patches, d_patches, numPatches, stream);
// }

//
// Copy atoms to device memory
//
void DpcppPmeRealSpaceCompute::copyAtoms(const int numAtoms,
                                        const DpcppAtom *atoms) try {
  dpcppDevice->setDeviceID(deviceID);
  this->numAtoms = numAtoms;

  // Reallocate device arrays as neccessary
  reallocate_device<DpcppAtom>(&d_atoms, &d_atomsCapacity, numAtoms, 1.5f);

  // Copy atom data to device
  copy_HtoD<DpcppAtom>(atoms, d_atoms, numAtoms, *stream);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// Spread charges on grid
//
void DpcppPmeRealSpaceCompute::spreadCharge(Lattice &lattice) try {
  dpcppDevice->setDeviceID(deviceID);

  // Clear grid
  clear_device_array<float>(data, xsize*ysize*zsize, *stream);

  spread_charge((const sycl::float4 *)d_atoms, numAtoms, pmeGrid.K1, pmeGrid.K2,
                pmeGrid.K3, xsize, ysize, zsize, xsize, y0, z0,
                (pmeGrid.yBlocks == 1), (pmeGrid.zBlocks == 1), data,
                pmeGrid.order, stream);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeRealSpaceCompute::dpcpp_gatherforce_check(void *arg,
                                                     double walltime) try {
  DpcppPmeRealSpaceCompute* c = (DpcppPmeRealSpaceCompute *)arg;
  dpct::dev_mgr::instance().select_device(c->deviceID);

  auto status = c->gatherForceEvent
    .get_info<sycl::info::event::command_execution_status>();
  if (status == sycl::info::event_command_status::complete) {
    // Event has occurred
    c->checkCount = 0;
//    c->deviceProxy[CkMyNode()].gatherForceDone();
    c->devicePtr->gatherForceDone();
    return;
  } else {
    // Anything else is an error
    char errmsg[256];
    sprintf(errmsg,"in DpcppPmeRealSpaceCompute::dpcpp_gatherforce_check after polling %d times",
            c->checkCount);
    dpcppDie(errmsg);
  }

  // Call again
  CcdCallBacksReset(0, walltime);
  CcdCallFnAfter(dpcpp_gatherforce_check, arg, 0.1);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeRealSpaceCompute::gatherForceSetCallback(
    DpcppComputePmeDevice *devicePtr_in) try {
  dpcppDevice->setDeviceID(deviceID);
  devicePtr = devicePtr_in;
  checkCount = 0;
  CcdCallBacksReset(0, CmiWallTimer());
  // Set the call back at 0.1ms
  CcdCallFnAfter(dpcpp_gatherforce_check, this, 0.1);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeRealSpaceCompute::waitGatherForceDone() try {
  dpcppDevice->setDeviceID(deviceID);
  gatherForceEvent.wait_and_throw();
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeRealSpaceCompute::setupGridTexture(float *data, int data_len) try {
  if (tex_data == data && tex_data_len == data_len) return;
  tex_data = data;
  tex_data_len = data_len;
  // TODO: Use texture objects
  dpct::image_data resDesc;
  //memset(&resDesc, 0, sizeof(resDesc));
  resDesc.set_data_type(dpct::image_data_type::linear);
  resDesc.set_data_ptr(data);
  resDesc.set_channel_data_type(dpct::image_channel_data_type::fp);
  resDesc.set_channel_size(1, sizeof(float) * 8);
  resDesc.set_x(data_len * sizeof(float));
  dpct::sampling_info texDesc;
  //memset(&texDesc, 0, sizeof(texDesc));
  //texDesc.readMode = cudaReadModeElementType;
  gridTexObj = dpct::create_image_wrapper(resDesc, texDesc);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeRealSpaceCompute::gatherForce(Lattice &lattice,
                                          DpcppForce *force) try {
  dpcppDevice->setDeviceID(deviceID);

  // Re-allocate force array if needed
  reallocate_device<DpcppForce>(&d_force, &d_forceCapacity, numAtoms, 1.5f);
  stream->memset(d_force, 0, sizeof(sycl::float3) * numAtoms);

  gather_force((const sycl::float4 *)d_atoms, numAtoms, pmeGrid.K1, pmeGrid.K2,
               pmeGrid.K3, xsize, ysize, zsize, xsize, y0, z0,
               (pmeGrid.yBlocks == 1), (pmeGrid.zBlocks == 1),
               data, pmeGrid.order, (sycl::float3 *)d_force, gridTexObj,
               stream);

  copy_DtoH<DpcppForce>(d_force, force, numAtoms, *stream);

  gatherForceEvent = stream->single_task<class gatherForce_empty_task>([=](){});
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

/*
double DpcppPmeRealSpaceCompute::calcSelfEnergy() {
  double h_selfEnergy;
  clear_device_array<double>(d_selfEnergy, 1);
  calc_sum_charge_squared((const float4*)d_atoms, numAtoms, d_selfEnergy, stream);
  copy_DtoH<double>(d_selfEnergy, &h_selfEnergy, 1, stream);
  cudaCheck(cudaStreamSynchronize(stream));
  // 1.7724538509055160273 = sqrt(pi)
  h_selfEnergy *= -ComputeNonbondedUtil::ewaldcof/1.7724538509055160273;
  return h_selfEnergy;
}
*/

//###########################################################################
//###########################################################################
//###########################################################################

DpcppPmeTranspose::DpcppPmeTranspose(
    PmeGrid pmeGrid, const int permutation,
    const int jblock, const int kblock, int deviceID, sycl::queue *stream) try
    : PmeTranspose(pmeGrid, permutation, jblock, kblock), deviceID(deviceID),
      stream(stream) {
  dpcppDevice->setDeviceID(deviceID);

  allocate_device<sycl::float2>(&d_data, dataSize);
#ifndef P2P_ENABLE_3D
  allocate_device<sycl::float2>(&d_buffer, dataSize);
#endif

  // Setup data pointers to NULL, these can be overridden later on by using setDataPtrs()
  dataPtrsYZX.resize(nblock, NULL);
  dataPtrsZXY.resize(nblock, NULL);

  allocate_device< TransposeBatch<sycl::float2> >(&batchesYZX, 3*nblock);
  allocate_device< TransposeBatch<sycl::float2> >(&batchesZXY, 3*nblock);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

DpcppPmeTranspose::~DpcppPmeTranspose() try {
  dpcppDevice->setDeviceID(deviceID);
  deallocate_device<sycl::float2>(&d_data);
#ifndef P2P_ENABLE_3D
  deallocate_device<sycl::float2>(&d_buffer);
#endif
  deallocate_device< TransposeBatch<sycl::float2> >(&batchesZXY);
  deallocate_device< TransposeBatch<sycl::float2> >(&batchesYZX);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// Set dataPtrsYZX
//
void DpcppPmeTranspose::setDataPtrsYZX(std::vector<sycl::float2 *> &dataPtrsNew,
                                      sycl::float2 *data) try {
  if (dataPtrsYZX.size() != dataPtrsNew.size())
    NAMD_bug("DpcppPmeTranspose::setDataPtrsYZX, invalid dataPtrsNew size");
  for (int iblock=0;iblock < nblock;iblock++) {
    dataPtrsYZX[iblock] = dataPtrsNew[iblock];
  }
  // Build batched data structures
  TransposeBatch<sycl::float2> *h_batchesYZX =
      new TransposeBatch<sycl::float2>[3 * nblock];

  for (int iperm=0;iperm < 3;iperm++) {
    int isize_out;
    if (iperm == 0) {
      // Perm_Z_cX_Y:
      // ZXY -> XYZ
      isize_out = pmeGrid.K1/2+1;
    } else if (iperm == 1) {
      // Perm_cX_Y_Z:
      // XYZ -> YZX
      isize_out = pmeGrid.K2;
    } else {
      // Perm_Y_Z_cX:
      // YZX -> ZXY
      isize_out = pmeGrid.K3;
    }

    int max_nx = 0;
    for (int iblock=0;iblock < nblock;iblock++) {

      int x0 = pos[iblock];
      int nx = pos[iblock+1] - x0;
      max_nx = std::max(max_nx, nx);

      int width_out;
      sycl::float2 *data_out;
      if (dataPtrsYZX[iblock] == NULL) {
        // Local transpose, use internal buffer
        data_out = d_data + jsize*ksize*x0;
        width_out = jsize;
      } else {
        // Non-local tranpose, use buffer in dataPtr[] and the size of that buffer
        data_out = dataPtrsYZX[iblock];
        width_out = isize_out;
      }

      TransposeBatch<sycl::float2> batch;
      batch.nx        = nx;
      batch.ysize_out = width_out;
      batch.zsize_out = ksize;
      batch.data_in   = data+x0;
      batch.data_out  = data_out;

      h_batchesYZX[iperm*nblock + iblock] = batch;

    // transpose_xyz_yzx(
    //   nx, jsize, ksize,
    //   isize, jsize,
    //   width_out, ksize,
    //   data+x0, data_out, stream);
    }

    max_nx_YZX[iperm] = max_nx;
  }

  copy_HtoD< TransposeBatch<sycl::float2> >(h_batchesYZX, batchesYZX, 3*nblock, *stream);
  stream->wait();
  delete [] h_batchesYZX;
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// Set dataPtrsZXY
//
void DpcppPmeTranspose::setDataPtrsZXY(std::vector<sycl::float2 *> &dataPtrsNew,
                                      sycl::float2 *data) try {
  if (dataPtrsZXY.size() != dataPtrsNew.size())
    NAMD_bug("DpcppPmeTranspose::setDataPtrsZXY, invalid dataPtrsNew size");
  for (int iblock=0;iblock < nblock;iblock++) {
    dataPtrsZXY[iblock] = dataPtrsNew[iblock];
  }

  // Build batched data structures
  TransposeBatch<sycl::float2> *h_batchesZXY =
      new TransposeBatch<sycl::float2>[3 * nblock];

  for (int iperm=0;iperm < 3;iperm++) {
    int isize_out;
    if (iperm == 0) {
      // Perm_cX_Y_Z:
      // XYZ -> ZXY
      isize_out = pmeGrid.K3;
    } else if (iperm == 1) {
      // Perm_Z_cX_Y:
      // ZXY -> YZX
      isize_out = pmeGrid.K2;
    } else {
      // Perm_Y_Z_cX:
      // YZX -> XYZ
      isize_out = pmeGrid.K1/2+1;
    }

    int max_nx = 0;
    for (int iblock=0;iblock < nblock;iblock++) {

      int x0 = pos[iblock];
      int nx = pos[iblock+1] - x0;
      max_nx = std::max(max_nx, nx);

      int width_out;
      sycl::float2 *data_out;
      if (dataPtrsZXY[iblock] == NULL) {
        // Local transpose, use internal buffer
        data_out = d_data + jsize*ksize*x0;
        width_out = ksize;
      } else {
        // Non-local tranpose, use buffer in dataPtr[] and the size of that buffer
        data_out = dataPtrsZXY[iblock];
        width_out = isize_out;
      }

      TransposeBatch<sycl::float2> batch;
      batch.nx        = nx;
      batch.zsize_out = width_out;
      batch.xsize_out = nx;
      batch.data_in   = data+x0;
      batch.data_out  = data_out;

      h_batchesZXY[iperm*nblock + iblock] = batch;
    }

    max_nx_ZXY[iperm] = max_nx;
  }

  copy_HtoD< TransposeBatch<sycl::float2> >(h_batchesZXY, batchesZXY, 3*nblock, *stream);
  stream->wait();
  delete [] h_batchesZXY;
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeTranspose::transposeXYZtoYZX(const sycl::float2 *data) try {
  dpcppDevice->setDeviceID(deviceID);

  int iperm;
  switch(permutation) {
    case Perm_Z_cX_Y:
    // ZXY -> XYZ
    iperm = 0;
    break;
    case Perm_cX_Y_Z:
    // XYZ -> YZX
    iperm = 1;
    break;
    case Perm_Y_Z_cX:
    // YZX -> ZXY
    iperm = 2;
    break;
    default:
    NAMD_bug("PmeTranspose::transposeXYZtoYZX, invalid permutation");
    break;
  }

  batchTranspose_xyz_yzx(
    nblock, batchesYZX + iperm*nblock,
    max_nx_YZX[iperm], jsize, ksize,
    isize, jsize, stream);


/*
  int isize_out;
  switch(permutation) {
    case Perm_Z_cX_Y:
    // ZXY -> XYZ
    isize_out = pmeGrid.K1/2+1;
    break;
    case Perm_cX_Y_Z:
    // XYZ -> YZX
    isize_out = pmeGrid.K2;
    break;
    case Perm_Y_Z_cX:
    // YZX -> ZXY
    isize_out = pmeGrid.K3;
    break;
    default:
    NAMD_bug("PmeTranspose::transposeXYZtoYZX, invalid permutation");
    break;
  }

  for (int iblock=0;iblock < nblock;iblock++) {

    int x0 = pos[iblock];
    int nx = pos[iblock+1] - x0;

    int width_out;
    sycl::float2* data_out;
    if (dataPtrsYZX[iblock] == NULL) {
      // Local transpose, use internal buffer
      data_out = d_data + jsize*ksize*x0;
      width_out = jsize;
    } else {
      // Non-local tranpose, use buffer in dataPtr[] and the size of that buffer
      data_out = dataPtrsYZX[iblock];
      width_out = isize_out;
    }

    transpose_xyz_yzx(
      nx, jsize, ksize,
      isize, jsize,
      width_out, ksize,
      data+x0, data_out, stream);
  }
*/
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeTranspose::transposeXYZtoZXY(const sycl::float2 *data) try {
  dpcppDevice->setDeviceID(deviceID);

  int iperm;
  switch(permutation) {
    case Perm_cX_Y_Z:
    // XYZ -> ZXY
    iperm = 0;
    break;
    case Perm_Z_cX_Y:
    // ZXY -> YZX
    iperm = 1;
    break;
    case Perm_Y_Z_cX:
    // YZX -> XYZ
    iperm = 2;
    break;
    default:
    NAMD_bug("PmeTranspose::transposeXYZtoZXY, invalid permutation");
    break;
  }

  batchTranspose_xyz_zxy(
    nblock, batchesZXY + iperm*nblock,
    max_nx_ZXY[iperm], jsize, ksize,
    isize, jsize, stream);

/*
  int isize_out;
  switch(permutation) {
    case Perm_cX_Y_Z:
    // XYZ -> ZXY
    isize_out = pmeGrid.K3;
    break;
    case Perm_Z_cX_Y:
    // ZXY -> YZX
    isize_out = pmeGrid.K2;
    break;
    case Perm_Y_Z_cX:
    // YZX -> XYZ
    isize_out = pmeGrid.K1/2+1;
    break;
    default:
    NAMD_bug("PmeTranspose::transposeXYZtoZXY, invalid permutation");
    break;
  }

  for (int iblock=0;iblock < nblock;iblock++) {

    int x0 = pos[iblock];
    int nx = pos[iblock+1] - x0;

    int width_out;
    sycl::float2* data_out;
    if (dataPtrsZXY[iblock] == NULL) {
      // Local transpose, use internal buffer
      data_out = d_data + jsize*ksize*x0;
      width_out = ksize;
    } else {
      // Non-local tranpose, use buffer in dataPtr[] and the size of that buffer
      data_out = dataPtrsZXY[iblock];
      width_out = isize_out;
    }

    transpose_xyz_zxy(
      nx, jsize, ksize,
      isize, jsize,
      width_out, nx,
      data+x0, data_out, stream);
  }
*/
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeTranspose::waitStreamSynchronize() try {
  dpcppDevice->setDeviceID(deviceID);
  stream->wait();
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeTranspose::copyDataDeviceToHost(const int iblock,
                                            sycl::float2 *h_data,
                                            const int h_dataSize) try {
  dpcppDevice->setDeviceID(deviceID);

  if (iblock >= nblock)
    NAMD_bug("DpcppPmeTranspose::copyDataDeviceToHost, block index exceeds number of blocks");

  int x0 = pos[iblock];
  int nx = pos[iblock+1] - x0;

  int copySize  = jsize*ksize*nx;
  int copyStart = jsize*ksize*x0;

  if (copyStart + copySize > dataSize)
    NAMD_bug("DpcppPmeTranspose::copyDataDeviceToHost, dataSize exceeded");

  if (copySize > h_dataSize) 
    NAMD_bug("DpcppPmeTranspose::copyDataDeviceToHost, h_dataSize exceeded");

  copy_DtoH<sycl::float2>(d_data+copyStart, h_data, copySize, *stream);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

void DpcppPmeTranspose::copyDataHostToDevice(const int iblock,
                                            sycl::float2 *data_in,
                                            sycl::float2 *data_out) try {
  dpcppDevice->setDeviceID(deviceID);

  if (iblock >= nblock)
    NAMD_bug("DpcppPmeTranspose::copyDataHostToDevice, block index exceeds number of blocks");

  // Determine block size = how much we're copying
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, permutation, iblock, jblock, kblock, i0, i1, j0, j1, k0, k1);
  int ni = i1-i0+1;
  int nj = j1-j0+1;
  int nk = k1-k0+1;

//  copy3D_HtoD<sycl::float2>(data_in, data_out,
//    0, 0, 0,
//    ni, nj,
//    i0, 0, 0,
//    isize, jsize,
//    ni, nj, nk, *stream);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

#ifndef P2P_ENABLE_3D
//
// Copy from temporary buffer to final buffer
//
void DpcppPmeTranspose::copyDataDeviceToDevice(const int iblock,
                                              sycl::float2 *data_out) try {
  dpcppDevice->setDeviceID(deviceID);

  if (iblock >= nblock)
    NAMD_bug("DpcppPmeTranspose::copyDataDeviceToDevice, block index exceeds number of blocks");

  // Determine block size = how much we're copying
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, permutation, iblock, jblock, kblock, i0, i1, j0, j1, k0, k1);
  int ni = i1-i0+1;
  int nj = j1-j0+1;
  int nk = k1-k0+1;

  sycl::float2 *data_in = d_buffer + i0 * nj * nk;

//  copy3D_DtoD<sycl::float2>(data_in, data_out,
//    0, 0, 0,
//    ni, nj,
//    i0, 0, 0,
//    isize, jsize,
//    ni, nj, nk, *stream);
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

//
// Return temporary buffer for block "iblock"
//
sycl::float2 *DpcppPmeTranspose::getBuffer(const int iblock) {
  if (iblock >= nblock)
    NAMD_bug("DpcppPmeTranspose::getBuffer, block index exceeds number of blocks");

  // Determine block size = how much we're copying
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, permutation, iblock, jblock, kblock, i0, i1, j0, j1, k0, k1);
  int ni = i1-i0+1;
  int nj = j1-j0+1;
  int nk = k1-k0+1;

  return d_buffer + i0*nj*nk;
}
#endif

void DpcppPmeTranspose::copyDataToPeerDeviceYZX(
    const int iblock, int deviceID_out, int permutation_out,
    sycl::float2 *data_out) {

  int iblock_out = jblock;
  int jblock_out = kblock;
  int kblock_out = iblock;

  copyDataToPeerDevice(iblock, iblock_out, jblock_out, kblock_out, deviceID_out, permutation_out, data_out);
}

void DpcppPmeTranspose::copyDataToPeerDeviceZXY(
    const int iblock, int deviceID_out, int permutation_out,
    sycl::float2 *data_out) {

  int iblock_out = kblock;
  int jblock_out = iblock;
  int kblock_out = jblock;

  copyDataToPeerDevice(iblock, iblock_out, jblock_out, kblock_out, deviceID_out, permutation_out, data_out);
}

void DpcppPmeTranspose::copyDataToPeerDevice(
    const int iblock, const int iblock_out, const int jblock_out,
    const int kblock_out,
    int deviceID_out, int permutation_out, sycl::float2 *data_out) try {

  dpcppDevice->setDeviceID(deviceID);

  // Determine block size = how much we're copying
  int i0, i1, j0, j1, k0, k1;
  getBlockDim(pmeGrid, permutation_out, iblock_out, jblock_out, kblock_out, i0, i1, j0, j1, k0, k1);
  int ni = i1-i0+1;
  int nj = j1-j0+1;
  int nk = k1-k0+1;

  getPencilDim(pmeGrid, permutation_out, jblock_out, kblock_out, i0, i1, j0, j1, k0, k1);
  int isize_out = i1-i0+1;
  int jsize_out = j1-j0+1;

  int x0 = pos[iblock];
  sycl::float2 *data_in = d_data + jsize * ksize * x0;

#ifndef P2P_ENABLE_3D
  // Copy into temporary peer device buffer
//  copy_PeerDtoD<sycl::float2>(deviceID, deviceID_out, data_in, data_out, ni*nj*nk, *stream);
#else
//  copy3D_PeerDtoD<sycl::float2>(deviceID, deviceID_out, data_in, data_out,
//    0, 0, 0,
//    ni, nj,
//    0, 0, 0,
//    isize_out, jsize_out,
//    ni, nj, nk, *stream);
#endif
}
catch (sycl::exception const &exc) {
  std::cerr << exc.what() << "Exception caught at file:" << __FILE__
            << ", line:" << __LINE__ << std::endl;
  std::exit(1);
}

#endif // NAMD_DPCPP
