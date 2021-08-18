#ifndef DPCPPPMESOLVERUTIL_H
#define DPCPPPMESOLVERUTIL_H
#include <stdio.h>
#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>
#include "fftw3.h"
#include "fftw3_mkl.h"
#endif // NAMD_DPCPP
#include "PmeSolverUtil.h"
#include "DpcppUtils.h"
#include "DpcppPmeSolverUtilKernel.h"

#ifdef NAMD_DPCPP
void writeComplexToDisk(const sycl::float2 *d_data, const int size,
                        const char *filename, sycl::queue *stream);
void writeHostComplexToDisk(const sycl::float2 *h_data, const int size,
                            const char *filename);
void writeRealToDisk(const float *d_data, const int size, const char *filename,
                     sycl::queue *stream);

//
// DPC++ implementation of FFTCompute
//
class DpcppFFTCompute : public FFTCompute {
private:
  fftwf_plan forwardPlan, backwardPlan;
  int deviceID;
  sycl::queue *stream;

private:
	float* allocateData(const int dataSizeRequired);
	void plan3D(int *n, int flags);
	void plan2D(int *n, int howmany, int flags);
	void plan1DX(int *n, int howmany, int flags);
	void plan1DY(int *n, int howmany, int flags);
	void plan1DZ(int *n, int howmany, int flags);

public:
	DpcppFFTCompute(int deviceID, sycl::queue *stream)
    : deviceID(deviceID), stream(stream) { fftw3_mkl.verbose = 1; }
	~DpcppFFTCompute();
	void forward();
	void backward();
};

//
// DPC++ implementation of PmeKSpaceCompute class
//
class DpcppPmePencilXYZ;
class DpcppPmePencilZ;

class DpcppPmeKSpaceCompute : public PmeKSpaceCompute {
private:
	int deviceID;
	sycl::queue *stream;
	// Device memory versions of (bm1, bm2, bm3)
	float *d_bm1, *d_bm2, *d_bm3;
	//float *prefac_x, *prefac_y, *prefac_z;
	struct EnergyVirial {
		double energy;
		double virial[9];
	};
	EnergyVirial* d_energyVirial;
	EnergyVirial* h_energyVirial;
	sycl::event copyEnergyVirialEvent;
	bool ortho;
  // Check counter for event polling in energyAndVirialCheck()
  int checkCount;
	static void energyAndVirialCheck(void *arg, double walltime);
	DpcppPmePencilXYZ* pencilXYZPtr;
	DpcppPmePencilZ* pencilZPtr;
public:
	DpcppPmeKSpaceCompute(
		PmeGrid pmeGrid, const int permutation, const int jblock,
		const int kblock, double kappa,
		int deviceID, sycl::queue *stream);
	~DpcppPmeKSpaceCompute();
	void solve(Lattice &lattice, const bool doEnergy, const bool doVirial, float* data);
	// void waitEnergyAndVirial();
	double getEnergy();
	void getVirial(double *virial);
	void energyAndVirialSetCallback(DpcppPmePencilXYZ* pencilPtr);
	void energyAndVirialSetCallback(DpcppPmePencilZ* pencilPtr);
};

//
// DPC++ implementation of PmeRealSpaceCompute class
//

class DpcppComputePmeDevice;

class DpcppPmeRealSpaceCompute : public PmeRealSpaceCompute {
private:
  bool gridTexObjActive;
  dpct::image_wrapper_base_p gridTexObj;
  int tex_data_len;
	float* tex_data;
	int deviceID;
	sycl::queue *stream;
	void setupGridTexture(float* data, int data_len);
	// Device memory for atoms
	int d_atomsCapacity;
	DpcppAtom* d_atoms;
	// Device memory for patches
	// int d_patchesCapacity;
	// PatchInfo* d_patches;
	// Device memory for forces
	int d_forceCapacity;
	DpcppForce* d_force;
	// // Device memory for self energy
	// double* d_selfEnergy;
  // Events
  sycl::event gatherForceEvent;
  // Check counter for event polling
  int checkCount;
  // Store device pointer for event polling
  DpcppComputePmeDevice* devicePtr;
  static void dpcpp_gatherforce_check(void *arg, double walltime);
public:
	DpcppPmeRealSpaceCompute(
		PmeGrid pmeGrid, const int jblock, const int kblock,
		int deviceID, sycl::queue *stream);
	~DpcppPmeRealSpaceCompute();
	void copyAtoms(const int numAtoms, const DpcppAtom* atoms);
	void spreadCharge(Lattice &lattice);
	void gatherForce(Lattice &lattice, DpcppForce* force);
	void gatherForceSetCallback(DpcppComputePmeDevice* devicePtr_in);
	void waitGatherForceDone();
};

//
// DPC++ implementation of PmeTranspose class
//
class DpcppPmeTranspose : public PmeTranspose {
private:
	int deviceID;
	sycl::queue *stream;
	sycl::float2 *d_data;
#ifndef P2P_ENABLE_3D
	sycl::float2 *d_buffer;
#endif
	// List of device data pointers for transpose destinations on:
	// (a) this device on a different pencil (e.g. in XYZ->YZX transpose, on Y -pencil)
	// (b) different device on a different pencil
	// If NULL, use the local d_data -buffer
	std::vector<sycl::float2 *> dataPtrsYZX;
	std::vector<sycl::float2 *> dataPtrsZXY;

	// Batch data
	int max_nx_YZX[3];
	TransposeBatch<sycl::float2> *batchesYZX;
	int max_nx_ZXY[3];
	TransposeBatch<sycl::float2> *batchesZXY;

	void copyDataToPeerDevice(const int iblock, const int iblock_out,
		const int jblock_out, const int kblock_out,
		int deviceID_out, int permutation_out,
		sycl::float2 *data_out);

public:
	DpcppPmeTranspose(PmeGrid pmeGrid, const int permutation,
		const int jblock, const int kblock, int deviceID,
		sycl::queue *stream);
	~DpcppPmeTranspose();
	void setDataPtrsYZX(std::vector<sycl::float2 *> &dataPtrsNew,
		sycl::float2 *data);
	void setDataPtrsZXY(std::vector<sycl::float2 *> &dataPtrsNew,
		sycl::float2 *data);
	void transposeXYZtoYZX(const sycl::float2 *data);
	void transposeXYZtoZXY(const sycl::float2 *data);
	// void waitTransposeDone();
	void waitStreamSynchronize();
	void copyDataDeviceToHost(const int iblock, sycl::float2 *h_data,
		const int h_dataSize);
	void copyDataHostToDevice(const int iblock, sycl::float2 *data_in,
		sycl::float2 *data_out);
#ifndef P2P_ENABLE_3D
	void copyDataDeviceToDevice(const int iblock, sycl::float2 *data_out);
	sycl::float2 *getBuffer(const int iblock);
#endif
	void copyDataToPeerDeviceYZX(const int iblock, int deviceID_out,
		int permutation_out, sycl::float2 *data_out);
	void copyDataToPeerDeviceZXY(const int iblock, int deviceID_out,
		int permutation_out, sycl::float2 *data_out);
};
#endif // NAMD_DPCPP
#endif // DPCPPPMESOLVERUTIL_H
