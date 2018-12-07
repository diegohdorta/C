#ifndef _DEMO_H_
#define _DEMO_H_

#define MIN(X, Y)       \
  (X < Y)? X: Y;

#define KERNEL_SOURCE 		(char *)"compute_sp.cl"
#define KERNEL_FILE		"compute_sp.cl"
#define CL_ERROR !CL_SUCCESS

#define PLATFORM_SIZE		4
#define PLATFORM_BUFFER		1024

#define DEVICE_SIZE		4
#define DEVICE_BUFFER		1024

#define EXTRA_DEVICE_SIZE	4
#define EXTRA_DEVICE_BUFFER	1024

#define BUFFER_SIZE		1024


using namespace std;

typedef struct kernel_src_str {
	char *source;
	size_t source_size;
} kernel_src_t;

typedef struct {
  char deviceName[BUFFER_SIZE];
  char driverVersion[BUFFER_SIZE];

  uint numCUs;
  uint maxWGSize;
  ulong maxAllocSize;
  ulong maxGlobalSize;
  uint maxClockFreq;

  bool halfSupported;
  bool doubleSupported;
  cl_device_type  deviceType;

  // Test specific options
  int gloalBWIters;
  int computeWgsPerCU;
  int computeIters;
  int transferBWIters;
  int kernelLatencyIters;

} dev_info_t;



cl_int LoadKernelSource (char *filename, kernel_src_str *kernel);
cl_int BuildProgram (cl_program *program, cl_device_id *device_id, cl_context context, kernel_src_str *kernel);
dev_info_t PrintInfo(cl_platform_id platform_id, cl_device_id device_id);
cl_int Init (cl_platform_id *platform_id, cl_device_id *device_id, cl_context *context, cl_command_queue *cq);
cl_int LoadKernelSource (char *filename, kernel_src_str *kernel_src);
uint roundToPowOf2(uint number, int maxPower);
timespec diffTimer (timespec start, timespec end);

#endif /* _DEMO_H_DEFINED_*/
