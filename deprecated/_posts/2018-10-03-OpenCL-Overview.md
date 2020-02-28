---
layout: post
title: "Using OpenCL on iMX8"
author: "Diego Dorta"
categories: gpu
tags: [ openCL, imx, GPU, CPU, high-performance, heterogeneous, data-parallel, c99, c++11 ]
---

A short statement can define OpenCL as a `low-level` language for `high-performance`
heterogeneous data-parallel computation. `Low-level` means that as lower it gets the
effort increases, and the user/developer is forced to handle the entire code by itself.
For insuring a `high-performance` the code must be matched to the hardware, with that
we can really get a strong performance leveraging the hardware into its maximum power
processing.

`Heterogeneous` is an often concept to describe a system that supports (run across) multiples
types of devices, currently we can compile identical codes using `OpenCL` to run on GPUs,
and although it was developed for GPUs, it has found an use in CPUs, and even FPGAs.
`Data-parallel` is a model of parallelism, and as GPUs are set for it, `OpenCL` has it at
its best feature distributing data across different nodes, which operate on the data in
parallel.

This framework specifies programming languages based on `C99`, `C++11`, it means the code
can be written in programming languages as C, C++ which are similar to this standards. It's
possible to write them and compile it at run-time, or get compiled binaries already to shorten
the preparations. This typical way of coding has its issues, it is not very user friendly,
and also it is not portable across devices. 

That's the reason `OpenCL` offers a unified parallel programming model across heterogeneous
devices while abstracting away many implementation details.

`OpenCL` and `CUDA` are basically the same, however `CUDA` is great as long you use its GPUs,
it does not work at all on other ones. `CUDA` for sure has better tools, language and
features, in turn `OpenCL` supports more devices. One good thing about these frameworks, it's
that the same algorithm runs well on both of them.

An `OpenCL` program mainly consists of several parts:

### Setup

- Get the devices and platforms:

For CPU:

```c
clGetDevicesIDs(NULL, CL_DEVICE_TYPE_CPU, 1, &devices, NULL);
```
For GPU:

```c
clGetDevicesIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &devices, NULL);
```
- Create a context for sharing between devices:

```c
context = clCreateContext(NULL, 1, &devices, NULL, NULL, NULL);
```
- Create command queues for submitting work:

```c
queue = clCreateCommandQueue(context, device,
	         (cl_command_queue_properties)0, NULL);
```

### Compilation

- Creating a source to be part of the program:

```c
char *source = {
	"kernel void calculateSin(global float *data) {\n"
        "  int id = get_global_id(0); \n"
        "  data[id] = sin(data[id]);\n"
        "}\n"
}
```
- Creating the program:

```c
program = clCreateProgramWithSource(context, 1,
		(const char**)&source, NULL, NULL);
```

- Building the program:

```c
clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
```

- Create Kernels:

```c
clCreateKernel(program, "calculateSin", NULL);
```

### Create Memory Objects

```c
buffer = clCreateBuffer(context, CL_MEM_READ_WRITE,
			 DATA_SIZE, NULL, NULL);
```

### Enqueue writes to copy data to the GPU

```c
clEnqueueWriterBuffer(queue, buffer, CF_FALSE, 0,
			DATA_SIZE, data, 0, NULL, NULL);
```

### Set the Kernel arguments

```c
clSetKernelArg(kernel, 0, sizeof(buffer), &buffer);
```

### Enquere Kernel Executions

```c
size_t global_dimensions[] = {LENGTH, 0, 0};
clEnqueueNDRangeKernel(queue, kernel, 1, NULL,
			global_dimensions, NULL, 0, NULL, NULL);
```

### Enqueue reads to copy data back from the GPU

```c
clEnqueueReadBuffer(queue, buffer, CL_FALSE, 0,
			sizeof(cl_float)*LENGTH, data, 0, NULL, NULL);
```

### Wait for your commands to finish

```c
clFinish(queue);
```
## Running a Hello World program on iMX8 QXP MEK

This section starts learning `OpenCL` programming basics by building and running actual
code for running on `iMX8QXP` board. To get the whole idea concentrate on the general
_flow_ of `OpenCL` programming.

Follow a familiar and simple `Hello World` code written in `OpenCL`:

```c
__kernel void hello(__global char* string)
{
  string[0] =  'H';
  string[1] =  'e';
  string[2] =  'l';
  string[3] =  'l';
  string[4] =  'o';
  string[5] =  ',';
  string[6] =  ' ';
  string[7] =  'W';
  string[8] =  'o';
  string[9] =  'r';
  string[10] = 'l';
  string[11] = 'd';
  string[12] = '!';
  string[13] = '\0';
}
```

Since standard `in/out` can not be used within the kernel, we use the kernel only
to set the _char array_. In this program, the `string` set on the kernel copies
over to the host side, which can then be _outputted_. 

```c
#include <CL/cl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

int main(void)
{
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem memobj = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;

    char string[MEM_SIZE];

    FILE *fp;
    const char file_name[] = "hello.cl";
    char *source_str;
    size_t source_size;

    fp = fopen(file_name, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel %s.\n", strerror(errno));
        return EXIT_FAILURE;
     }
    source_str = (char *) malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
		&device_id, &ret_num_devices);

    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    
    memobj = clCreateBuffer(context, CL_MEM_READ_WRITE,
    				MEM_SIZE * sizeof(char), NULL, &ret);
	
    program = clCreateProgramWithSource(context, 1,
    		(const char **)&source_str,
    		(const size_t *)&source_size, &ret);

    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	
    kernel = clCreateKernel(program, "hello", &ret);
	
    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
	
    clEnqueueTask(command_queue, kernel, 0, NULL,NULL);

    clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
    		MEM_SIZE * sizeof(char),string, 0, NULL, NULL);

    puts(string);

    clFlush(command_queue);
    clFinish(command_queue);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(memobj);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);

    free(source_str);
    return EXIT_SUCCESS;
}
```
### Compiling

This code requires a `toolchain` to be compiled for `arm64`. Follow the
next instructions to download and install it:

* [`Setting Up Yocto`](https://diegodorta.com.br/yocto/Setting-Up-Yocto.html)

After the installation, export the `toolchain` using `source`:

```bash
$ source /opt/<DISTRO>/<BSP_RELEASE>/environment-setup-aarch64-poky-linux
```
For this case was used:

```bash
$ source /opt/fsl-imx-internal-xwayland/4.9.51-mx8-beta/ \
		environment-setup-aarch64-poky-linux
```
To check if the export worked, just:

```bash
$ echo $CC
aarch64-poky-linux-gcc --sysroot=/opt/fsl-imx-internal-xwayland/ \
		4.9.51-mx8-beta/sysroots/aarch64-poky-linux
```

Then, compile the code by running:

```bash
$ $CC hello.cpp -o hello -Wl,--library-path=<PATH_TO_LIB>,\
		-rpath-link=<PATH_TO_LIB> -lm -lOpenCL
```
For this case was used:

```bash
$ $CC hello.cpp -o hello -Wl,--library-path=/opt/ \
	fsl-imx-internal-xwayland/4.9.51-mx8-beta/ \
	sysroots/aarch64-poky-linux/usr/lib, \
	-rpath-link=/opt/fsl-imx-internal-xwayland/ \
	4.9.51-mx8-beta/sysroots/aarch64-poky-linux/usr/lib \
	-lm -lOpenCL
```
The compilation results in a binary like this:

```bash
$ file hello
hello: ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV),
dynamically linked, interpreter /lib/ld-linux-aarch64.so.1, for GNU/Linux 3.14.0, BuildID[sha1]=a41d49b113b751af77800727f2f1ee9328317a0f, not stripped
```

### Running

Copy the binary to the board and run it, you will get the following result:

<center><img src="{{site.url}}{{site.baseurl}}/assets/opencl.gif"/></center>

