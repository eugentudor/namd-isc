#ifndef DEVICEDPCPP_H
#define DEVICEDPCPP_H

#include <map>
#include <functional>

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>

#define DPCPP_PME_SPREADCHARGE_EVENT 90
#define DPCPP_PME_GATHERFORCE_EVENT 91

//
// Class that handles PE <=> DPC++ device mapping
//
class DpcppDevice {

private:
	// Command line argument settings
	char *usedplatform=nullptr;
	char *devicelist;
  int splittiles;
	int usedevicelist;
	int devicesperreplica;
	int ignoresharing;
	int mergegrids;
	int nomergegrids;
	int nostreaming;

  // SYCL platform
  sycl::platform sycl_platform;
  bool platform_initialized=false;

	// Number of devices on this physical node
	int deviceCount;

	// Number of devices on this physical node that are used for computation
	int ndevices;

	// List of device IDs on this physical node that are used for computation
	int *devices;

	// Number of devices that are used for computation by this node
	int nnodedevices;

	// List of device IDs that are used for computation by this node
	int *nodedevices;

	// True when GPU is shared between PEs
	bool sharedGpu;
	// Index of next GPU sharing this GPU
	int nextPeSharingGpu;
	// Index of the master PE for this GPU
	int masterPe;
	// Number of PEs that share this GPU
	int numPesSharingDevice;
	// List of PEs that share this GPU
	int *pesSharingDevice;
	// True when what???
	int gpuIsMine;

	// Device ID for this Pe
	int deviceID;

	// Device properties for all devices on this node
	void register_user_events();

  std::function<void(cl::sycl::exception_list)> exceptionHandler;

public:
	DpcppDevice();
	~DpcppDevice();
	
	void initialize();
  sycl::context get_context();

	int getDeviceCount() {return deviceCount;}
	int getNumDevice() {return nnodedevices;}

	bool device_shared_with_pe(int pe);
	bool one_device_per_node();

	int getNoStreaming() {return nostreaming;}
	int getNoMergeGrids() {return nomergegrids;}
	int getMergeGrids() {return mergegrids;}
	void setMergeGrids(const int val) {mergegrids = val;}

	bool getSharedGpu() {return sharedGpu;}
	int getNextPeSharingGpu() {return nextPeSharingGpu;}
	int getMasterPe() {return masterPe;}
	int getNumPesSharingDevice() {return numPesSharingDevice;}
	int getPesSharingDevice(const int i) {return pesSharingDevice[i];}

	int getGpuIsMine() {return gpuIsMine;}
	void setGpuIsMine(const int val) {gpuIsMine = val;}

	int getDeviceID() {return deviceID;}
	void setDeviceID(int newID) {deviceID = newID;}
	int getDeviceIDbyRank(int rank) {return nodedevices[rank];}
	int getDeviceIDforPe(int pe);
	int getMasterPeForDeviceID(int deviceID);

  int getMaxWorkGroupSize();

  std::function<void(cl::sycl::exception_list)>& getExceptionHandler() {
    return exceptionHandler;
  }
};

extern __thread DpcppDevice *dpcppDevice;
extern std::map<int, sycl::queue> devices_default_queue;
inline sycl::queue& getDefaultQ() {return devices_default_queue[dpcppDevice->getDeviceID()];}

#endif //NAMD_DPCPP

#endif // DEVICEDPCPP_H
