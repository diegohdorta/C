#!/bin/sh

# GCC Compiler:
#
# For compiling with Threads:
#	1 - Normal compiling:	make
#	2 - Debug mode: 	make DEBUG=-DDEBUG
#
# For compiling with OpenMP:
# 	** Additional libraries (OpenMP): sudo apt install gcc-multilib libomp-dev
#	1 - Normal compiling:	make PARALLEL="-fopenmp" PARALLEL=-DPARALLEL
#	2 - Debug mode:		make PARALLEL="-fopenmp" PARALLEL=-DPARALLEL DEBUG=-DDEBUG
#
# For cleaning and removing files:
#	1 - make clean

make PARALLEL="-fopenmp" PARALLEL=-DPARALLEL
