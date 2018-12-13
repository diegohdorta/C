#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <CL/cl.h>

#define VEC_VALUES_SIZE 100
#define SIZE 600000
#define BUFFER_SIZE 1024
#define MAX_SOURCE_SIZE (0x100000)

int main(void)
{	
	int a[VEC_VALUES_SIZE];
	int b[VEC_VALUES_SIZE];

	int vec_1[SIZE];
	int vec_2[SIZE];
	int vec_3[SIZE];

	cl_ulong start = 0;
	cl_ulong end = 0;
	double gpu_time = 0.0;
	int i = 0;
	
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj_1 = NULL;
	cl_mem memobj_2 = NULL;
	cl_mem memobj_3 = NULL;
	cl_kernel kernel = NULL;
	cl_program program = NULL;
	cl_event event = NULL;

	char buf[BUFFER_SIZE];
	
	FILE *fp;
	const char file_name[] = "kernel.cl";
	char *source_str;
	size_t source_size;
	
	fp = fopen(file_name, "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
	source_str = (char *) malloc(MAX_SOURCE_SIZE);
	if (source_str == NULL) {
		fprintf(stderr, "Failed malloc() %s.\n", strerror(errno));
		return EXIT_FAILURE;	
	}	
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);
	
	for(i = 0; i < VEC_VALUES_SIZE; i++) {
		a[i] = i * i;
		b[i] = i * i;
	}

	for(i = 0; i < SIZE; i++) {
		vec_1[i] = a[i % 20];
		vec_2[i] = a[i % 20];
		vec_3[i] = 0;
	}
	 
	clGetPlatformIDs(1, &platform_id, NULL);
	clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1,
			&device_id, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_NAME, sizeof(buf),
			&buf, NULL);
	clGetDeviceInfo(device_id, CL_DRIVER_VERSION, sizeof(buf),
			&buf, NULL);

	printf("CL_DEVICE_NAME: %s\n", buf);

	context = clCreateContextFromType(0, CL_DEVICE_TYPE_GPU,
			NULL, NULL, NULL);     
	command_queue = clCreateCommandQueue(context, device_id,
			CL_QUEUE_PROFILING_ENABLE, NULL);

	memobj_1 = clCreateBuffer(context, CL_MEM_READ_ONLY |
			CL_MEM_COPY_HOST_PTR, sizeof(int) * SIZE, vec_1, NULL);

	memobj_2 = clCreateBuffer(context, CL_MEM_READ_ONLY |
			CL_MEM_COPY_HOST_PTR, sizeof(int) * SIZE, vec_2, NULL);

	memobj_3 = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
			sizeof(int) * SIZE, NULL, NULL);

	program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
			(const size_t *)&source_size, NULL);

	clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

	kernel = clCreateKernel(program, "sum", NULL);

	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&memobj_3);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&memobj_1);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&memobj_2);
	 
	event = clCreateUserEvent(context, NULL);
	 
	size_t work_size[1] = {SIZE};
	clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
			work_size, NULL, 0, NULL, &event);

	clEnqueueReadBuffer(command_queue, memobj_3, CL_TRUE, 0,
			SIZE * sizeof(int), vec_3, 0, NULL, NULL);

	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);
	clReleaseMemObject(memobj_1);
	clReleaseMemObject(memobj_2);
	clReleaseMemObject(memobj_3);    

	clWaitForEvents(1, &event);

	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(cl_ulong), &start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
			sizeof(cl_ulong), &end, NULL);
	 
	gpu_time = end - start;
	gpu_time = gpu_time * 1.0e-9;
	printf("Execution Time >> %0.3f seconds\n", gpu_time);  

	return EXIT_SUCCESS;
}
