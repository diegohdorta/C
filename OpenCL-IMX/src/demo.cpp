#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <chrono>
#include <CL/cl.h>
#include "demo.h"

// http://svn.clifford.at/tools/trunk/examples/cldemo.c
 // scp diego@10.29.244.160:/home/diego/codes/nxp/employee/ML/iMX8QXPMEK_Demos/OpenCL-IMX/bin/demo .

static cl_int 
init(cl_platform_id *p, cl_device_id *d, cl_context *c, cl_command_queue *q)
{
	cl_uint platform, dev;
	cl_int error;
	
	error = clGetPlatformIDs(1, p, &platform);
	if (error != CL_SUCCESS) 
		return CL_ERROR;
	
	error = clGetDeviceIDs((*p), CL_DEVICE_TYPE_GPU, 1, d, &dev);
	if (error != CL_SUCCESS) 
		return CL_ERROR;
	
	cl_context_properties properties[] =
		{CL_CONTEXT_PLATFORM, (cl_context_properties)(*p), 0};
	
	(*c) = clCreateContext(properties, 1, d, NULL, NULL, &error);
	
	if (error != CL_SUCCESS) 
		return CL_ERROR;
	
	(*q) = clCreateCommandQueue ((*c), (*d), CL_QUEUE_PROFILING_ENABLE, &error);
	if (error != CL_SUCCESS) 
		return CL_ERROR;

	return CL_SUCCESS;
}

static cl_int
build_cl_program(cl_program *p, cl_device_id *d, cl_context c, kernel_src_t *ks)
{
	cl_int err = CL_SUCCESS;
	
	(*p) = clCreateProgramWithSource(c, 1, (const char **)&ks->source, &ks->source_size, &err);
	if (err != CL_SUCCESS)
		return CL_ERROR;
	
	err = clBuildProgram((*p), 1, d, "", NULL, NULL);
	if (err < 0) {
		clGetProgramBuildInfo((*p), (*d), CL_PROGRAM_BUILD_LOG, ks->source_size, ks->source, NULL);
		printf("\n%s", ks->source);
	}	
	return err;
}

static void 
init_opencl(cl_platform_id *p, cl_device_id *d, cl_context *c, cl_command_queue *q)
{
	if (init(p, d, c, q) != CL_SUCCESS) {
		fprintf(stderr, "init_opencl() failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void
get_imx_platform_info(cl_platform_id *p)
{
    const char *platform_names[PLATFORM_SIZE] = 
    			{"Name", "Vendor", "Version", "Profile"};
    
    const cl_platform_info attribute_types[PLATFORM_SIZE] = { CL_PLATFORM_NAME,
    			CL_PLATFORM_VENDOR,	CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE };
    	
	char info[PLATFORM_BUFFER];
    size_t info_size = PLATFORM_BUFFER;
    int i;

	printf("\n\t\t# PLATFORM INFO #\n\n");
	for(i = 0; i < PLATFORM_SIZE; i++) {		
		if(clGetPlatformInfo(*p, attribute_types[i], info_size, info, NULL)) {
			fprintf(stderr, "get_imx_platform_info() failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("%s\t>>\t%s\n", platform_names[i], info);	
	}
}

static dev_info_t
get_imx_device_info(cl_device_id *d)
{
    const char* device_names[DEVICE_SIZE] = 
    			{"Name", "Vendor", "Version", "Profile"};
    			
    const cl_platform_info attribute_types[DEVICE_SIZE] = { CL_DEVICE_NAME,
    			CL_DEVICE_VENDOR, CL_DEVICE_VERSION, CL_DEVICE_PROFILE };
    			
    			
    const char* extra_device_names[EXTRA_DEVICE_SIZE] = 
    			{"G.Size", "M.Alloc", "M.Size", "C.Freq"};
    			
    const cl_platform_info extra_attribute_types[EXTRA_DEVICE_SIZE] = 
    			{ CL_DEVICE_MAX_WORK_GROUP_SIZE,
    			  CL_DEVICE_MAX_MEM_ALLOC_SIZE,
    			  CL_DEVICE_GLOBAL_MEM_SIZE,
    			  CL_DEVICE_MAX_CLOCK_FREQUENCY };
    			
	char info[DEVICE_BUFFER];
    size_t info_size = DEVICE_BUFFER;
    int i;
    cl_ulong e;
    dev_info_t dev_imx_info;
	
	printf("\n\t\t# DEVICE INFO #\n\n");
	for(i = 0; i < DEVICE_SIZE; i++) {		
		if(clGetDeviceInfo(*d, attribute_types[i], info_size, info, NULL)) {
			fprintf(stderr, "get_imx_device_info() failed: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("%s\t>>\t%s\n", device_names[i], info);	
	}

	for(i = 0; i < EXTRA_DEVICE_SIZE; i++) {		
		if(clGetDeviceInfo(*d, extra_attribute_types[i], sizeof(cl_ulong), &e, NULL)) {
			fprintf(stderr, "get_imx_device_info() failed: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("%s\t>>\t%lu\n", extra_device_names[i], e);	
	}
	
	if(dev_imx_info.deviceType & CL_DEVICE_TYPE_CPU) 
    {
        printf ("\nDevice Type: CPU\n");
        dev_imx_info.gloalBWIters = 20;
        dev_imx_info.computeWgsPerCU = 512;
        dev_imx_info.computeIters = 10;
    } 
    else 
    {            // GPU
        printf ("\nDevice Type: GPU\n");
        dev_imx_info.gloalBWIters = 50;
        dev_imx_info.computeWgsPerCU = 2048;
        dev_imx_info.computeIters = 30;
    }
    
    dev_imx_info.transferBWIters = 20;
    dev_imx_info.kernelLatencyIters = 20000;
	
	return dev_imx_info;
}

static void
load_kernel_source(char *f, kernel_src_t *ks)
{
	FILE *fp = fopen(f, "rb");
	if(fp == NULL) {
		fprintf(stderr, "load_kernel_source() failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_END);
	ks->source_size = ftell(fp);
	rewind(fp);

	ks->source = (char *)malloc(sizeof(char) * ks->source_size);
	if(ks->source == NULL) {
		fprintf(stderr, "malloc Load_kernel_source() failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	fread(ks->source, 1, ks->source_size, fp);
	ks->source[ks->source_size] = '\0';
	fclose(fp);
	printf("Kernel source loaded!\n");
}

int main(void)
{	
	cl_platform_id 	 platform_id = 0;
	cl_device_id 	 device_id = 0;
	cl_context 	 context = 0;
	cl_command_queue command_queue = 0;
	cl_program 	 program;
	cl_kernel 	 kernel;
	cl_mem 		 compute_sp_v4_mem_input = NULL;
	cl_int 		 ret = 0;
	cl_float 	 A = 1.3f;
	cl_uint 	 workPerWI = 4096;
	
	kernel_src_t kernel_str;
	dev_info_t dev_info;

    int dimension = 1;
    double gflops = 0.0;
    size_t global = 0; 
    size_t local  = 0;
 
	init_opencl(&platform_id, &device_id, &context, &command_queue);
	get_imx_platform_info(&platform_id);
	dev_info = get_imx_device_info(&device_id);
		
	printf("\n# Loading CL Kernel: %s\n", KERNEL_FILE);
	load_kernel_source(KERNEL_SOURCE, &kernel_str);

	printf("\n# Building '%s' program...\n", KERNEL_FILE);
	build_cl_program(&program, &device_id, context, &kernel_str);
	
	printf("\n# Creating CL Kernel...\n");	
	kernel = clCreateKernel(program, "compute_sp_v4", &ret);
 
//   ############    

    dev_info = PrintInfo (platform_id, device_id);
        
	//printf ("\nLoading CL Kernel: compute_sp_v4.cl");
	
//	ret = LoadKernelSource ((char *)"compute_sp.cl", &kernel_str);
	

	
	//printf ("Building compute_sp_v4 program ");
	
	/*ret = BuildProgram (&program, &device_id, context, &kernel_str);
	if (ret != CL_SUCCESS) 
	{
		 
         printf (".....Failed\n");
		 exit (0);
	}
	else
		printf (".....Ok\n");
		
	printf ("Creating CL kernel");
	
	kernel = clCreateKernel (program, "compute_sp_v4", &ret);
	
	if (ret != CL_SUCCESS) 
	{
		 printf (".....Failed\n");
		 exit (0);
	}
	else
		printf (".....Ok\n");*/
    
	printf ("Allocating buffers");

    uint globalWIs = (dev_info.numCUs) * (dev_info.computeWgsPerCU) * (dev_info.maxWGSize);
    uint t = MIN((globalWIs * sizeof(cl_float)), dev_info.maxAllocSize);
    t = roundToPowOf2(t, 0);
    globalWIs = t / sizeof(cl_float);

	compute_sp_v4_mem_input = clCreateBuffer (context, CL_MEM_WRITE_ONLY, globalWIs * sizeof(cl_float), NULL, &ret);	
	
	/*if (ret != CL_SUCCESS) 
	{
		 printf (".....Failed\n");
		 exit (0);
	}
	printf ("......Ok\n");*/
    
	// run the CL kernel    
    printf ("Running Kernel...\n");
    global = globalWIs;
    local = dev_info.maxWGSize;
    int iters = dev_info.computeIters;
    
    clSetKernelArg (kernel, 0, sizeof(cl_mem), &compute_sp_v4_mem_input);
    clSetKernelArg (kernel, 1, sizeof(float), &A);
    
    // for computing GFLOPs
    timespec timer_start;
    timespec timer_end;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer_start);
    
    // needed to use C++ for high_resolution_clock
    std::chrono::high_resolution_clock::time_point tick, tock;
    tick = chrono::high_resolution_clock::now();
    for(int i = 0; i < iters; i++)
    {
        clEnqueueNDRangeKernel (command_queue, kernel, dimension, NULL, &global, &local, 0, NULL, NULL);
    }
    clFinish (command_queue);
    tock = chrono::high_resolution_clock::now();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timer_end);

    float res_timer = (float)(chrono::duration_cast<chrono::microseconds>(tock - tick).count()) / iters;
    gflops = ((float)globalWIs * workPerWI) / res_timer / 1e3f; ;
    printf ("\nUsing C++ chrono::high_resolution_clock::now\n");
    printf ("\nCompute Single Precision (Float4): %.3f GFLOPS\n\n", gflops);
    
  
    res_timer = (diffTimer (timer_start,timer_end).tv_nsec)  / (float) iters;
    gflops = ((float)globalWIs * workPerWI) / res_timer / 1e3f; ;    
    printf ("\nUsing C clock_gettime\n");
    printf ("\nCompute Single Precision (Float4): %.3f GFLOPS\n", gflops);
	
	printf ("\nFinishing OpenCL");
   	clFlush( command_queue);
	clReleaseContext(context);
	clReleaseProgram(program);
	clReleaseCommandQueue(command_queue);
	clReleaseKernel (kernel);
	clReleaseMemObject (compute_sp_v4_mem_input);
	printf (".....OK\n\n");

	return 0;
}



dev_info_t PrintInfo (cl_platform_id platform_id, cl_device_id device_id)
{

	char buffer[10240];
    cl_ulong i;
    cl_device_type devType;
    
    dev_info_t dev_info;
    
	printf ("\n-=-=-=- Platform Information -=-=-=-\n\n");
  
   	clGetPlatformInfo (platform_id, CL_PLATFORM_NAME, 10240, buffer, NULL);
	printf ("Platform Name: %s\n", buffer);

	clGetPlatformInfo (platform_id, CL_PLATFORM_PROFILE, 10240, buffer, NULL);
	printf ("Platform Profile: %s\n", buffer);
	
	clGetPlatformInfo (platform_id, CL_PLATFORM_VERSION, 10240, buffer, NULL);
	printf ("Platform Version: %s\n", buffer);
	
	clGetPlatformInfo (platform_id, CL_PLATFORM_VENDOR, 10240, buffer, NULL);
	printf ("Platform Vendor: %s\n", buffer);
	
	printf ("\n-=-=-=- Device Information -=-=-=-\n\n");
	clGetDeviceInfo( device_id, CL_DEVICE_NAME, 10240, dev_info.deviceName, NULL);
	printf ("Device Name: %s\n", dev_info.deviceName);

	clGetDeviceInfo( device_id, CL_DRIVER_VERSION, 10240, dev_info.driverVersion, NULL);
	printf ("Driver Version: %s\n", dev_info.driverVersion);
    
	clGetDeviceInfo (device_id, CL_DEVICE_PROFILE, 10240, buffer, NULL);
	printf ("Device Profile: %s\n", buffer);

    clGetDeviceInfo (device_id, CL_DEVICE_VERSION, 10240, buffer, NULL);
	printf ("Device Version: %s\n", buffer);

	clGetDeviceInfo (device_id, CL_DEVICE_VENDOR, 10240, buffer, NULL);
	printf ("Device Vendor: %s\n", buffer);
    
	clGetDeviceInfo (device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof (cl_uint), &i, NULL);
	printf ("Device Max Work Item Dimensions: %lu\n", i);

	clGetDeviceInfo (device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof (cl_uint), &i, NULL);
    printf ("Device Max Work Compute Units: %lu\n", i);
    dev_info.numCUs = i;

    size_t v[3];
	clGetDeviceInfo (device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof (size_t) * 3, v, NULL);
    printf ("Device Max Work Item Size: %lu\n", v[0]);
    dev_info.maxWGSize = v[0];
    #define MAX_WG_SIZE 256
    dev_info.maxWGSize = MIN(dev_info.maxWGSize, MAX_WG_SIZE);
    
	clGetDeviceInfo (device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof (size_t), &i, NULL);
	printf ("Device Max Work Group Size: %lu\n", i);
    
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof (cl_ulong), &i, NULL);
    printf ("Device Max Memory Allocation: %lu\n", i);
    dev_info.maxAllocSize = i;

	clGetDeviceInfo(device_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof (cl_ulong), &i, NULL);
    printf ("Device Global Memory Size: %lu\n", i);
    dev_info.maxGlobalSize = i;
   
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof (cl_uint), &i, NULL);
    printf ("Device Max Clock Frequency: %lu\n", i);
    dev_info.maxClockFreq = i;
    
    clGetDeviceInfo (device_id, CL_DEVICE_TYPE, sizeof (cl_device_type), &devType, NULL);
    dev_info.deviceType = devType;
        
    if(dev_info.deviceType & CL_DEVICE_TYPE_CPU) 
    {
        printf ("\nDevice Type: CPU\n");
        dev_info.gloalBWIters = 20;
        dev_info.computeWgsPerCU = 512;
        dev_info.computeIters = 10;
    } 
    else 
    {            // GPU
        printf ("\nDevice Type: GPU\n");
        dev_info.gloalBWIters = 50;
        dev_info.computeWgsPerCU = 2048;
        dev_info.computeIters = 30;
    }
    
    dev_info.transferBWIters = 20;
    dev_info.kernelLatencyIters = 20000;
    
	printf ("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

	return dev_info;
}


cl_int BuildProgram (cl_program *program, cl_device_id *device_id, cl_context context, kernel_src_t *ks)
{
	cl_int error = CL_SUCCESS;
	
	(* program) = clCreateProgramWithSource (context, 1, (const char **)&ks->source, &ks->source_size, &error);
	if (error != CL_SUCCESS)
	{
		return CL_ERROR;
	}
	
	error = clBuildProgram ((* program), 1, device_id, "", NULL, NULL);
	if (error < 0)
	{
		clGetProgramBuildInfo((* program), (* device_id), CL_PROGRAM_BUILD_LOG, ks->source_size, ks->source, NULL);
		printf ("\n%s", ks->source);
	}
	
	return error;
}

uint roundToPowOf2(uint number, int maxPower)
{
  int i;

  if ((maxPower > 0) && (number > ((uint)1 << maxPower)))
    return (1 << maxPower);

  for (i=1 ; i < (int)(8*sizeof(int)) ; i++)
    if (((uint)1 << i) > number)
      break;

  return (1 << (i-1));
}

timespec diffTimer(timespec start, timespec end)
{
    timespec temp;
    
    if ((end.tv_nsec-start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec-start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}
