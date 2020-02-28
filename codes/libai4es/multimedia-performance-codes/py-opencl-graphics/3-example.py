#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (C) 2019 Diego Dorta - Baerlon Group
Diego Dorta <diegohdorta@gmail.com>
"""
import numpy
#import matplotlib.pyplot as plt
import pyopencl as cl
from time import time

def cpuArraySum(a, b):
    c_cpu = numpy.empty_like(a)
    cpu_start_time = time()
    for i in range(1000):
            for j in range(1000):
                c_cpu[i] = a[i] + b[i]
    print("\tCPU Total Time:\t\t\t{}".format((time() - cpu_start_time)))
    return  (time() - cpu_start_time)

def gpuArraySum(a, b):
    # Comment: Select the first platform [0]
    platform = cl.get_platforms()[0]

    # Comment: Select the first device on this platform [0]
    device = platform.get_devices()[0]

    # Comment: Create a context with your device
    context = cl.Context([device])
    
    queue = cl.CommandQueue(context, properties=cl.command_queue_properties.PROFILING_ENABLE)
    a_buffer = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=a)
    b_buffer = cl.Buffer(context, cl.mem_flags.READ_ONLY | cl.mem_flags.COPY_HOST_PTR, hostbuf=b)
    c_buffer = cl.Buffer(context, cl.mem_flags.WRITE_ONLY, b.nbytes)
    
    program = cl.Program(context, """
    __kernel void sum(__global const float *a, __global const float *b, __global float *c)
    {
        int i = get_global_id(0);
        int j;
        for(j = 0; j < 1000; j++)
        {
            c[i] = a[i] + b[i];
        }
    }""").build()
    gpu_start_time = time()
    print(a.shape)
    print(a.data)
    event = program.sum(queue, a.shape, None, a_buffer, b_buffer, c_buffer)
    event.wait()
    elapsed = 1e-9*(event.profile.end - event.profile.start)
    gpuTotal = time() - gpu_start_time
    
    print("\tGPU Kernel Time:\t\t{0} s".format(elapsed))    
    print("\tGPU Total Time:\t\t\t{0} s".format(gpuTotal))
    
    return elapsed, gpuTotal
    


if __name__ == "__main__":

    c = []
    g = []

    x = 0
    n = 1000000
        
    print("=" * 60)
    while (x < 4):

        print("{} ->".format(x + 1))
        
        a = numpy.random.rand(n).astype(numpy.float32)
        b = numpy.random.rand(n).astype(numpy.float32)

        cpuTotalTime = cpuArraySum(a, b)
        gpuElapsedTime, gpuTotalTime = gpuArraySum(a, b)
        
        c.append(cpuTotalTime)
        g.append(gpuTotalTime)
        
        n = n + 1000000
        x = x + 1
    print("=" * 60)
    
    print(c)
    print(g)
 
 
 
    
    # data to plot
    #nGroups = 4
    #cpuBlue = (c[0], c[1], c[2], c[3])
    #gpuGreen = (g[0], g[1], g[2], g[3])
     
    # create plot
    #fig, ax = plt.subplots()
    #index = numpy.arange(nGroups)
    #bar_width = 0.35
    #opacity = 0.8
     
    #rects1 = plt.bar(index, cpuBlue, bar_width, alpha=opacity, color='b', label='CPU')
     
    #rects2 = plt.bar(index + bar_width, gpuGreen, bar_width, alpha=opacity, color='g', label='GPU')
     
    #plt.xlabel('Array Sum')
    #plt.ylabel('Scores')
    #plt.title('Scores by person')
    #plt.xticks(index + bar_width, ('1000', '2000', '3000', '4000'))
    #plt.legend()
     
    #plt.tight_layout()
    #plt.show()
    

