# Project for High Performance Computing course.

This program was created and tested on:

* Ubuntu 16.04 LTS 64-bit
* Processor Intel® Xeon(R) CPU E5-1620 v3 @ 3.50GHz × 4
* Memory 15,6 Gib

The following project has two ways for multiplying matrizes.

## Compiling

### For generating an executable binary using POSIX threads, type:

*	1 - Normal compiling:	$ make
*	2 - Debug mode: 	$ make DEBUG=-DDEBUG

#### Usage:

* $ ./program [number of threads] [first row matrix] [first column matrix] [second row matrix] [second column matrix]

#### Example:

* $ ./program 4 1000 1000 1000 1000

### For using OpenMP library, type:

* 	* Additional libraries (OpenMP): $ sudo apt install gcc-multilib libomp-dev 	
*	1 - Normal compiling:	$ make PARALLEL="-fopenmp" PARALLEL=-DPARALLEL	
*	2 - Debug mode:		$ make PARALLEL="-fopenmp" PARALLEL=-DPARALLEL DEBUG=-DDEBUG
*	3 - Script:		$ ./build.sh

#### Usage:

* $ ./program 1 [first row matrix] [first column matrix] [second row matrix] [second column matrix]
* In this case, always use 1 for OpenMP parallelism.

#### Example:

* $ ./program 1 1000 1000 1000 1000

### For cleaning and removing:

* $ make clean

## Graphics

* For creating graphics execute 4 times the program increasing the number of threads, and then type:

* $ cd script/
* $ python _generate.py
* $ firefox https://plot.ly/~diegohdorta/0/multithreading-for-matrix-multiplication-on-unixlinux/

## The speedup results:

* Matrix size:	1000x1000
* Mimimum thread:	1 took 1.275796 seconds.
* Maximum thread:	10 took 0.380133 seconds.

* SpeedUp = 1.275796 / 0.380133 = 3,356183231



