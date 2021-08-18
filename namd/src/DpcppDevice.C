
#include "InfoStream.h"
#include "common.h"
#include "charm++.h"
#include "DpcppDevice.h"
#include "WorkDistrib.h"

#ifdef NAMD_DPCPP

using namespace sycl;

#ifdef WIN32
#define __thread __declspec(thread)
#endif

// Global storage for DPC++ devices
__thread DpcppDevice *dpcppDevice = nullptr;
// Global storage of devices default queues
std::map<int, queue> devices_default_queue;

void dpcpp_initialize() {
	dpcppDevice = new DpcppDevice();
	dpcppDevice->initialize();
}

// kill all service threads
void dpcpp_finalize() {
  // TODO: reset devices if needed
}

// -------------------------------------------------------------------------------------------------
// Called from BackEnd.C by all processes to read command line arguments
// These argument settings are used by DpcppDevice -class
// -------------------------------------------------------------------------------------------------
struct dpcpp_args_t {
	char *devicelist;
	char *usedplatform;
  int splittiles;
	int usedevicelist;
  int devicesperreplica;
	int ignoresharing;
	int mergegrids;
	int nomergegrids;
	int nostreaming;
};

static __thread dpcpp_args_t dpcpp_args;

void dpcpp_getargs(char **argv) {
  CmiGetArgStringDesc(argv, "+platform", &dpcpp_args.usedplatform,
		"SYCL Platform name");
  dpcpp_args.splittiles = CmiGetArgFlag(argv, "+splittiles");
  dpcpp_args.devicelist = 0;
  dpcpp_args.usedevicelist = CmiGetArgStringDesc(argv, "+devices", &dpcpp_args.devicelist,
		"comma-delimited list of DPC++ device numbers such as 0,2,1,2");
  dpcpp_args.devicesperreplica = 0;
  CmiGetArgInt(argv, "+devicesperreplica", &dpcpp_args.devicesperreplica);
  if ( dpcpp_args.devicesperreplica < 0 ) NAMD_die("Devices per replica must be positive\n");
  dpcpp_args.ignoresharing = CmiGetArgFlag(argv, "+ignoresharing");
  dpcpp_args.mergegrids = CmiGetArgFlag(argv, "+mergegrids");
  dpcpp_args.nomergegrids = CmiGetArgFlag(argv, "+nomergegrids");
  if ( dpcpp_args.mergegrids && dpcpp_args.nomergegrids ) NAMD_die("Do not specify both +mergegrids and +nomergegrids");
  dpcpp_args.nostreaming = CmiGetArgFlag(argv, "+nostreaming");
}
// -------------------------------------------------------------------------------------------------

// Node-wide list of device IDs for every rank
#define MAX_NUM_RANKS 2048
int deviceIDList[MAX_NUM_RANKS];
// Node-wide of master PEs for every device ID
#define MAX_NUM_DEVICES 256
int masterPeList[MAX_NUM_DEVICES];

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------

//
// Class creator
//
/// DPC++ default exception handler
auto exception_handler = [](exception_list exceptions) {
  for (std::exception_ptr const &e : exceptions) {
    try {
      std::rethrow_exception(e);
    } catch (exception const &e) {
      std::cerr << "Caught asynchronous SYCL exception:\n"
                << e.what() << std::endl;
    }
  }
};

DpcppDevice::DpcppDevice() : devices(NULL) {
}

//
// Initalize device
//
void DpcppDevice::initialize() {
	// Copy command-line arguments into class
	this->usedplatform = dpcpp_args.usedplatform;
	this->devicelist = dpcpp_args.devicelist;
	this->usedevicelist = dpcpp_args.usedevicelist;
  this->devicesperreplica = dpcpp_args.devicesperreplica;
	this->ignoresharing = dpcpp_args.ignoresharing;
	this->splittiles= dpcpp_args.splittiles;
	this->mergegrids = dpcpp_args.mergegrids;
	this->nomergegrids = dpcpp_args.nomergegrids;
	this->nostreaming = dpcpp_args.nostreaming;

  if (CkMyPe() == 0) register_user_events();

  char host[128];
  gethostname(host, 128);  host[127] = 0;

  int myPhysicalNodeID = CmiPhysicalNodeID(CkMyPe());
  int myRankInPhysicalNode;
  int numPesOnPhysicalNode;
  int *pesOnPhysicalNode;
  CmiGetPesOnPhysicalNode(myPhysicalNodeID,
                           &pesOnPhysicalNode,&numPesOnPhysicalNode);

  {
    int i;
    for ( i=0; i < numPesOnPhysicalNode; ++i ) {
      if ( i && (pesOnPhysicalNode[i] <= pesOnPhysicalNode[i-1]) ) {
        i = numPesOnPhysicalNode;
        break;
      }
      if ( pesOnPhysicalNode[i] == CkMyPe() ) break;
    }
    if ( i == numPesOnPhysicalNode || i != CmiPhysicalRank(CkMyPe()) ) {
      CkPrintf("Bad result from CmiGetPesOnPhysicalNode!\n");
      for ( i=0; i < numPesOnPhysicalNode; ++i ) {
        CkPrintf("pe %d physnode rank %d of %d is %d\n", CkMyPe(),
          i, numPesOnPhysicalNode, pesOnPhysicalNode[i]);
      }
      myRankInPhysicalNode = 0;
      numPesOnPhysicalNode = 1;
      pesOnPhysicalNode = new int[1];
      pesOnPhysicalNode[0] = CkMyPe();
    } else {
      myRankInPhysicalNode = i;
    }
  }
  // CkPrintf("Pe %d ranks %d in physical node\n",CkMyPe(),myRankInPhysicalNode);

  // Select Sycl platform
  int platform_id = 0; // Default is first one
  if (usedplatform!=nullptr) {
    platform_id = -1;
    std::vector<platform> pforms = platform::get_platforms();
    for( size_t pid=0; pid< pforms.size(); pid++){
      platform p = pforms[pid];
      if(p.get_info<info::platform::name>().compare(usedplatform) ==0) platform_id = pid;
    }
    if(platform_id == -1) {
      if (CkMyPe() == 0) {
        iout << iINFO << "Selected platform name not found\n" << endi;
        int platform_id = 0;
        int device_id = 0;
        std::vector<platform> pforms;
        std::vector<device> devs;
        iout << iINFO << "All available SYCL platforms and devices:" << "\n" << endi;
        pforms = platform::get_platforms();
        for( auto p : pforms ){
          iout << iINFO << "Platform Name = " <<
            p.get_info<info::platform::name>().c_str() << "\n" << endi;
          devs = p.get_devices();
          for( auto d : devs ){
            iout << iINFO << "    Device Name = " <<
              d.get_info<info::device::name>().c_str() << "\n" << endi;
            iout << iINFO << "    Device Max Compute Units = "
                 << d.get_info<info::device::max_compute_units>()
                 << "\n" << endi;
          }
        }
        NAMD_die("Selected platform name not found");
      }
    }
  }
  sycl_platform = platform::get_platforms()[platform_id];
  platform_initialized=true;
  if (CkMyPe() == 0)
    iout << iINFO << "Selected SYCL platform: " << sycl_platform.get_info<info::platform::name>().c_str()<< "\n" << endi;

  auto sycl_devices = sycl_platform.get_devices();
  if ( sycl_devices.size() <= 0 ) {
    NAMD_die("No DPC++ devices found.");
  }
  // Print device props
  if (CkMyPe() == 0) {
    for( auto d : sycl_devices){
      std::vector<device> tiles;
      try{
        tiles = d.create_sub_devices<info::partition_property::partition_by_affinity_domain>(info::partition_affinity_domain::next_partitionable);
      } catch(...){
        tiles.push_back(d); 
      }
      iout << iINFO << "    Device Name = " <<
        d.get_info<info::device::name>().c_str() << "\n" << endi;
      iout << iINFO << "    Device Max Compute Units = "
         << d.get_info<info::device::max_compute_units>() << "\n" << endi;
      iout << iINFO << "    Num Device Tiles = "
         << tiles.size() << "\n" << endi;
      if(tiles.size() > 1) {
        iout << iINFO << "        Tiles Info:\n" << endi;
        int tileId=0;
        for( auto t : tiles){
          iout << iINFO << "       [" << tileId++ <<"] Tile Max Compute Units = "
          << t.get_info<info::device::max_compute_units>() << "\n" << endi;
        }
      }
    }
  }

  // Create devices list
  std::vector<device> sycl_tiles;
  deviceCount=0; 
  for( auto d : sycl_devices){
    if(splittiles) {
      std::vector<device> tiles = d.create_sub_devices<info::partition_property::partition_by_affinity_domain>(info::partition_affinity_domain::next_partitionable);
      deviceCount += tiles.size();
      for(auto t: tiles) sycl_tiles.push_back(t);
    } else {
      deviceCount++;
      sycl_tiles.push_back(d);
    }
  }

  if (CkMyPe() == 0) {
    iout << iINFO << "Used device configurations:\n" <<  endi;
    int devIdx=0;
    for( auto d : sycl_tiles){
      iout << iINFO << "   Device Idx = " << devIdx++ << ". Name = " <<
        d.get_info<info::device::name>().c_str()
        << ". Max Compute Units = "
        << d.get_info<info::device::max_compute_units>() << "\n" << endi;
    }
  }

  ndevices = 0;
  int nexclusive = 0;
  if ( usedevicelist ) {
    devices = new int[strlen(devicelist)];
    int i = 0;
    while ( devicelist[i] ) {
      ndevices += sscanf(devicelist+i,"%d",devices+ndevices);
      while ( devicelist[i] && isdigit(devicelist[i]) ) ++i;
      while ( devicelist[i] && ! isdigit(devicelist[i]) ) ++i;
    }
  } else {
    if ( ! CkMyPe() ) {
      CkPrintf("Did not find +devices i,j,k,... argument, using all\n");
    }
    devices = new int[deviceCount];
    for ( int i=0; i<deviceCount; ++i ) {
      int dev = i % deviceCount;
      devices[ndevices++] = dev;
    }
  }

  if ( ! ndevices ) {
    NAMD_die("Did not find a usable GPU device");
  }

  if ( devicesperreplica > 0 ) {
    if ( devicesperreplica > ndevices ) {
      NAMD_die("More devices per partition requested than devices are available");
    }
    int *olddevices = devices;
    devices = new int[devicesperreplica];
    for ( int i=0; i<devicesperreplica; ++i ) {
      int mypart = CmiMyPartition();
      devices[i] = olddevices[(i+devicesperreplica*mypart)%ndevices];
    }
    ndevices = devicesperreplica;
    delete [] olddevices;
  }

  int myRankForDevice = ignoresharing ? CkMyRank() : myRankInPhysicalNode;
  int numPesForDevice = ignoresharing ? CkMyNodeSize() : numPesOnPhysicalNode;

  // catch multiple processes per device
  if ( ndevices % ( numPesForDevice / CkMyNodeSize() ) ) {
    char msg[1024];
    sprintf(msg,"Number of devices (%d) is not a multiple of number of processes (%d).  "
            "Sharing devices between processes is inefficient.  "
            "Specify +ignoresharing (each process uses all visible devices) if "
            "not all devices are visible to each process, otherwise "
            "adjust number of processes to evenly divide number of devices, "
            "specify subset of devices with +devices argument (e.g., +devices 0,2), "
            "or multiply list shared devices (e.g., +devices 0,1,2,0).",
            ndevices, numPesForDevice / CkMyNodeSize() );
    NAMD_die(msg);
  }

  {
    // build list of devices actually used by this node
    nodedevices = new int[ndevices];
    nnodedevices = 0;
    int pe = CkNodeFirst(CkMyNode());
    int dr = -1;
    for ( int i=0; i<CkMyNodeSize(); ++i, ++pe ) {
      int rank = ignoresharing ? i : CmiPhysicalRank(pe);
      int peDeviceRank = rank * ndevices / numPesForDevice;
      if ( peDeviceRank != dr ) {
        dr = peDeviceRank;
        nodedevices[nnodedevices++] = devices[dr];
      }
    }
  }

  {
    // check for devices used twice by this node
    for ( int i=0; i<nnodedevices; ++i ) {
      for ( int j=i+1; j<nnodedevices; ++j ) {
        if ( nodedevices[i] == nodedevices[j] ) { 
          char msg[1024];
          sprintf(msg,"Device %d bound twice by same process.", nodedevices[i]);
          NAMD_die(msg);
        }
      }
    }
  }

  sharedGpu = 0;
  gpuIsMine = 1;
  int firstPeSharingGpu = CkMyPe();
  nextPeSharingGpu = CkMyPe();

 {
    int dev;
    if ( numPesForDevice > 1 ) {
      int myDeviceRank = myRankForDevice * ndevices / numPesForDevice;
      dev = devices[myDeviceRank];
      masterPe = CkMyPe();
      {
        pesSharingDevice = new int[numPesForDevice];
        masterPe = -1;
        numPesSharingDevice = 0;
        for ( int i = 0; i < numPesForDevice; ++i ) {
          if ( i * ndevices / numPesForDevice == myDeviceRank ) {
            int thisPe = ignoresharing ? (CkNodeFirst(CkMyNode())+i) : pesOnPhysicalNode[i];
            pesSharingDevice[numPesSharingDevice++] = thisPe;
            if ( masterPe < 1 ) masterPe = thisPe;
            if ( WorkDistrib::pe_sortop_diffuse()(thisPe,masterPe) ) masterPe = thisPe;
          }
        }
        for ( int j = 0; j < ndevices; ++j ) {
          if ( devices[j] == dev && j != myDeviceRank ) sharedGpu = 1;
        }
      }
      if ( sharedGpu && masterPe == CkMyPe() ) {
        if ( CmiPhysicalNodeID(masterPe) < 2 )
        CkPrintf("Pe %d sharing DPC++ device %d\n", CkMyPe(), dev);
      }
    } else {  // in case phys node code is lying
      dev = devices[CkMyPe() % ndevices];
      masterPe = CkMyPe();
      pesSharingDevice = new int[1];
      pesSharingDevice[0] = CkMyPe();
      numPesSharingDevice = 1;
    }

    deviceID = dev;

    // Store device IDs to node-wide list
    if (CkMyRank() >= MAX_NUM_RANKS)
      NAMD_die("Maximum number of ranks (2048) per node exceeded");
    deviceIDList[CkMyRank()] = deviceID;

    if ( masterPe != CkMyPe() ) {
      if ( CmiPhysicalNodeID(masterPe) < 2 )
      CkPrintf("Pe %d physical rank %d will use DPC++ device of pe %d\n",
               CkMyPe(), myRankInPhysicalNode, masterPe);
      // for PME only
      dpcppDevice->setDeviceID(dev);
      return;
    }

    // Store master PEs for every device ID to node-wide list
    if (deviceID >= MAX_NUM_DEVICES)
      NAMD_die("Maximum number of DPC++ devices (256) per node exceeded");
    masterPeList[deviceID] = masterPe + 1;  // array is pre-initialized to zeros

    // disable token-passing but don't submit local until remote finished
    // if shared_gpu is true, otherwise submit all work immediately
    firstPeSharingGpu = CkMyPe();
    nextPeSharingGpu = CkMyPe();

    gpuIsMine = ( firstPeSharingGpu == CkMyPe() ); 

    if ( dev >= deviceCount ) {
      char buf[256];
      sprintf(buf,"Pe %d unable to bind to DPC++ device %d on %s because only %d devices are present",
  		CkMyPe(), dev, host, deviceCount);
      NAMD_die(buf);
    }

    if ( CmiPhysicalNodeID(masterPe) < 2 )
      // TODO: print all relevant SYCL device information here
    	CkPrintf("Pe %d physical rank %d binding to DPC++ device %d on %s:\n", CkMyPe(), myRankInPhysicalNode, dev, host);
      // Construct a default queue per offload device in the process
      devices_default_queue.insert(std::pair<int, queue>(dev, queue(sycl_tiles[dev], exception_handler, sycl::property::queue::in_order())));

      dpcppDevice->setDeviceID(dev);

  }  // just let pick a device for us
}

//
// Class destructor
//
DpcppDevice::~DpcppDevice() {
//  if (deviceProps != NULL) delete [] deviceProps;
  if (devices != NULL) delete [] devices;
	delete [] pesSharingDevice;
}

//
// Return device ID for pe. Assumes all nodes are the same
//
int DpcppDevice::getDeviceIDforPe(int pe) {
  return deviceIDList[CkRankOf(pe) % CkMyNodeSize()];
}

//
// Returns master PE for the device ID, or -1 if device not found
//
int DpcppDevice::getMasterPeForDeviceID(int deviceID) {
  return masterPeList[deviceID % deviceCount] - 1;
}

//
// Returns true if process "pe" shares this device
//
bool DpcppDevice::device_shared_with_pe(int pe) {
  for ( int i=0; i<numPesSharingDevice; ++i ) {
    if ( pesSharingDevice[i] == pe ) return true;
  }
  return false;
}

//
// Returns true if there is single device per node
//
bool DpcppDevice::one_device_per_node() {
  if ( numPesSharingDevice != CkMyNodeSize() ) return false;
  int numPesOnNodeSharingDevice = 0;
  for ( int i=0; i<numPesSharingDevice; ++i ) {
    if ( CkNodeOf(pesSharingDevice[i]) == CkMyNode() ) {
      ++numPesOnNodeSharingDevice;
    }
  }
  return ( numPesOnNodeSharingDevice == CkMyNodeSize() );
}

int DpcppDevice::getMaxWorkGroupSize() {
  return getDefaultQ().get_device().get_info<info::device::max_work_group_size>();
}

void DpcppDevice::register_user_events() {
//
//  traceRegisterUserEvent("CUDA PME spreadCharge", CUDA_PME_SPREADCHARGE_EVENT);
//  traceRegisterUserEvent("CUDA PME gatherForce", CUDA_PME_GATHERFORCE_EVENT);
//
//  traceRegisterUserEvent("CUDA bonded", CUDA_BONDED_KERNEL_EVENT);
//  traceRegisterUserEvent("CUDA debug", CUDA_DEBUG_EVENT);
//  traceRegisterUserEvent("CUDA nonbonded", CUDA_NONBONDED_KERNEL_EVENT);
//  traceRegisterUserEvent("CUDA GBIS Phase 1 kernel", CUDA_GBIS1_KERNEL_EVENT);
//  traceRegisterUserEvent("CUDA GBIS Phase 2 kernel", CUDA_GBIS2_KERNEL_EVENT);
//  traceRegisterUserEvent("CUDA GBIS Phase 3 kernel", CUDA_GBIS3_KERNEL_EVENT);
//
//  traceRegisterUserEvent("CUDA poll remote", CUDA_EVENT_ID_POLL_REMOTE);
//  traceRegisterUserEvent("CUDA poll local", CUDA_EVENT_ID_POLL_LOCAL);
//
//#define REGISTER_DEVICE_EVENTS(DEV) \
//  traceRegisterUserEvent("CUDA device " #DEV " remote", CUDA_EVENT_ID_BASE + 2 * DEV); \
//  traceRegisterUserEvent("CUDA device " #DEV " local", CUDA_EVENT_ID_BASE + 2 * DEV + 1);
//
//  REGISTER_DEVICE_EVENTS(0)
//  REGISTER_DEVICE_EVENTS(1)
//  REGISTER_DEVICE_EVENTS(2)
//  REGISTER_DEVICE_EVENTS(3)
//  REGISTER_DEVICE_EVENTS(4)
//  REGISTER_DEVICE_EVENTS(5)
//  REGISTER_DEVICE_EVENTS(6)
//  REGISTER_DEVICE_EVENTS(7)
//  REGISTER_DEVICE_EVENTS(8)
//  REGISTER_DEVICE_EVENTS(9)
//  REGISTER_DEVICE_EVENTS(10)
//  REGISTER_DEVICE_EVENTS(11)
//  REGISTER_DEVICE_EVENTS(12)
//  REGISTER_DEVICE_EVENTS(13)
//  REGISTER_DEVICE_EVENTS(14)
//  REGISTER_DEVICE_EVENTS(15)
//
}

#endif  // NAMD_DPCPP

