#ifndef DPCPPPMESOLVER_H
#define DPCPPPMESOLVER_H
#include "PmeSolver.h"
#include "DpcppPmeSolver.decl.h"

#ifdef NAMD_DPCPP
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>

class DpcppPmeXYZInitMsg : public CMessage_DpcppPmeXYZInitMsg {
public:
	DpcppPmeXYZInitMsg(PmeGrid& pmeGrid) : pmeGrid(pmeGrid) {}
	PmeGrid pmeGrid;
};

class DpcppPmeXYInitMsg : public CMessage_DpcppPmeXYInitMsg {
public:
	DpcppPmeXYInitMsg(PmeGrid& pmeGrid, CProxy_DpcppPmePencilXY& pmePencilXY, CProxy_DpcppPmePencilZ& pmePencilZ,
		CProxy_PmePencilXYMap& xyMap, CProxy_PmePencilXMap& zMap) : 
		pmeGrid(pmeGrid), pmePencilXY(pmePencilXY), pmePencilZ(pmePencilZ), xyMap(xyMap), zMap(zMap) {}
	PmeGrid pmeGrid;
  CProxy_DpcppPmePencilXY pmePencilXY;
  CProxy_DpcppPmePencilZ pmePencilZ;
  CProxy_PmePencilXMap zMap;
  CProxy_PmePencilXYMap xyMap;
};

class DpcppPmeXInitMsg : public CMessage_DpcppPmeXInitMsg {
public:
	DpcppPmeXInitMsg(PmeGrid& pmeGrid,
		CProxy_DpcppPmePencilX& pmePencilX, CProxy_DpcppPmePencilY& pmePencilY, CProxy_DpcppPmePencilZ& pmePencilZ,
		CProxy_PmePencilXMap& xMap, CProxy_PmePencilXMap& yMap, CProxy_PmePencilXMap& zMap) : 
		pmeGrid(pmeGrid), pmePencilX(pmePencilX), pmePencilY(pmePencilY), pmePencilZ(pmePencilZ),
		xMap(xMap), yMap(yMap), zMap(zMap) {}
	PmeGrid pmeGrid;
  CProxy_DpcppPmePencilX pmePencilX;
  CProxy_DpcppPmePencilY pmePencilY;
  CProxy_DpcppPmePencilZ pmePencilZ;
  CProxy_PmePencilXMap xMap;
  CProxy_PmePencilXMap yMap;
  CProxy_PmePencilXMap zMap;
};

class InitDeviceMsg : public CMessage_InitDeviceMsg {
public:
	InitDeviceMsg(CProxy_DpcppComputePmeDevice deviceProxy) : deviceProxy(deviceProxy) {}
	CProxy_DpcppComputePmeDevice deviceProxy;
};

class InitDeviceMsg2 : public CMessage_InitDeviceMsg2 {
public:
	InitDeviceMsg2(int deviceID, sycl::queue *stream,
		CProxy_DpcppComputePmeMgr mgrProxy)
		: deviceID(deviceID), stream(stream), mgrProxy(mgrProxy) {}
	int deviceID;
	sycl::queue *stream;
	CProxy_DpcppComputePmeMgr mgrProxy;
};

class DpcppPmePencilXYZ : public CBase_DpcppPmePencilXYZ {
public:
	DpcppPmePencilXYZ() {}
	DpcppPmePencilXYZ(CkMigrateMessage *m) {}
	void initialize(DpcppPmeXYZInitMsg *msg);
	void initializeDevice(InitDeviceMsg *msg);
	void energyAndVirialDone();
private:
	void backwardDone();
  CProxy_DpcppComputePmeDevice deviceProxy;
};

struct DeviceBuffer {
	DeviceBuffer(int deviceID, bool isPeerDevice, sycl::float2 *data)
		: deviceID(deviceID), isPeerDevice(isPeerDevice), data(data) {}
	bool isPeerDevice;
	int deviceID;
	sycl::event event;
	sycl::float2 *data;
};

class DeviceDataMsg : public CMessage_DeviceDataMsg {
public:
	DeviceDataMsg(int i, sycl::event event, sycl::float2 *data)
		: i(i), event(event), data(data) {}
	int i;
	sycl::event event;
	sycl::float2 *data;
};

class DpcppPmePencilXY : public CBase_DpcppPmePencilXY {
public:
	DpcppPmePencilXY_SDAG_CODE
	DpcppPmePencilXY() : numGetDeviceBuffer(0), eventCreated(false) {}
	DpcppPmePencilXY(CkMigrateMessage *m) : numGetDeviceBuffer(0), eventCreated(false) {}
	~DpcppPmePencilXY();
	void initialize(DpcppPmeXYInitMsg *msg);
	void initializeDevice(InitDeviceMsg *msg);
private:
	void forwardDone();
	void backwardDone();
	void recvDataFromZ(PmeBlockMsg *msg);
	void start(const CkCallback &);
	void setDeviceBuffers();
	sycl::float2 *getData(const int i, const bool sameDevice);
	int deviceID;
	sycl::queue *stream;
	sycl::event event;
	bool eventCreated;
	int imsgZ;
	int numDeviceBuffers;
	int numGetDeviceBuffer;
	std::vector<DeviceBuffer> deviceBuffers;
  CProxy_DpcppComputePmeDevice deviceProxy;
  CProxy_DpcppPmePencilZ pmePencilZ;
  CProxy_PmePencilXMap zMap;
};

class DpcppPmePencilX : public CBase_DpcppPmePencilX {
public:
	DpcppPmePencilX_SDAG_CODE
	DpcppPmePencilX() : numGetDeviceBuffer(0), eventCreated(false) {}
	DpcppPmePencilX(CkMigrateMessage *m) : numGetDeviceBuffer(0), eventCreated(false) {}
	~DpcppPmePencilX();
	void initialize(DpcppPmeXInitMsg *msg);
	void initializeDevice(InitDeviceMsg *msg);
private:
	void forwardDone();
	void backwardDone();
	void recvDataFromY(PmeBlockMsg *msg);
	void start(const CkCallback &);
	void setDeviceBuffers();
	sycl::float2 *getData(const int i, const bool sameDevice);
	int deviceID;
	sycl::queue *stream;
	sycl::event event;
	bool eventCreated;
	int imsgY;
	int numDeviceBuffers;
	int numGetDeviceBuffer;
	std::vector<DeviceBuffer> deviceBuffers;
  CProxy_DpcppComputePmeDevice deviceProxy;
  CProxy_DpcppPmePencilY pmePencilY;
  CProxy_PmePencilXMap yMap;
};

class DpcppPmePencilY : public CBase_DpcppPmePencilY {
public:
	DpcppPmePencilY_SDAG_CODE
	DpcppPmePencilY() : numGetDeviceBufferZ(0), numGetDeviceBufferX(0), eventCreated(false) {}
	DpcppPmePencilY(CkMigrateMessage *m) : numGetDeviceBufferZ(0), numGetDeviceBufferX(0), eventCreated(false) {}
	~DpcppPmePencilY();
	void initialize(DpcppPmeXInitMsg *msg);
	void initializeDevice(InitDeviceMsg2 *msg);
private:
	void forwardDone();
	void backwardDone();
	void recvDataFromX(PmeBlockMsg *msg);
	void recvDataFromZ(PmeBlockMsg *msg);
	void start(const CkCallback &);
	void setDeviceBuffers();
	sycl::float2 *getDataForX(const int i, const bool sameDevice);
	sycl::float2 *getDataForZ(const int i, const bool sameDevice);
	int deviceID;
	sycl::queue *stream;
	sycl::event event;
	bool eventCreated;
	int imsgZ, imsgX;
	int imsgZZ, imsgXX;
	int numGetDeviceBufferZ;
	int numGetDeviceBufferX;
	int numDeviceBuffersZ;
	int numDeviceBuffersX;
	std::vector<DeviceBuffer> deviceBuffersZ;
	std::vector<DeviceBuffer> deviceBuffersX;
  CProxy_DpcppPmePencilX pmePencilX;
  CProxy_DpcppPmePencilZ pmePencilZ;
  CProxy_PmePencilXMap xMap;
  CProxy_PmePencilXMap zMap;
};

class DpcppPmePencilZ : public CBase_DpcppPmePencilZ {
public:
	DpcppPmePencilZ_SDAG_CODE
	DpcppPmePencilZ() : numGetDeviceBufferY(0), numGetDeviceBufferXY(0), eventCreated(false) {}
	DpcppPmePencilZ(CkMigrateMessage *m) : numGetDeviceBufferY(0), numGetDeviceBufferXY(0), eventCreated(false) {}
	~DpcppPmePencilZ();
	void initialize(DpcppPmeXInitMsg *msg);
	void initialize(DpcppPmeXYInitMsg *msg);
	void initializeDevice(InitDeviceMsg2 *msg);
	void energyAndVirialDone();
private:
	void backwardDone();
	void recvDataFromY(PmeBlockMsg *msg);
	void start(const CkCallback &);
	void setDeviceBuffers();
	sycl::float2 *getData(const int i, const bool sameDevice);
	int deviceID;
	sycl::queue *stream;
	sycl::event event;
	bool eventCreated;
	int imsgY;
	int numDeviceBuffers;
	int numGetDeviceBufferY;
	std::vector<DeviceBuffer> deviceBuffers;
  CProxy_DpcppPmePencilY pmePencilY;
  CProxy_PmePencilXMap yMap;

	bool useXYslab;
	int numGetDeviceBufferXY;
  CProxy_DpcppPmePencilXY pmePencilXY;
  CProxy_PmePencilXYMap xyMap;
};

#endif // NAMD_DPCPP
#endif //DPCPPPMESOLVER_H
