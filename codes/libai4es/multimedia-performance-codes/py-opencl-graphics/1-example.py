#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (C) 2019 Diego Dorta
Diego Dorta <diegohdorta@gmail.com>
"""
import pyopencl as cl

def getPlatformDevices():
    print("=" * 60 + "\n\t    OpenCL Platforms and Devices")
    for platform in cl.get_platforms():
        print("=" * 60)
        print("PLATFORM")
        print("=" * 60)
        print("Name\t\t\t ->\t" + platform.name)
        print("Vendor\t\t\t ->\t" + platform.vendor)
        print("Version\t\t\t ->\t" + platform.version)
        print("Profile\t\t\t ->\t" + platform.profile)
        for device in platform.get_devices():
            print("=" * 60)
            print("DEVICE")
            print("=" * 60)
            print("Name\t\t\t ->\t" + device.name)
            print("Type\t\t\t ->\t" + cl.device_type.to_string(device.type))
            print("Max Clock Speed\t\t ->\t{0} Mhz"
                 .format(device.max_clock_frequency))
            print("Compute Units\t\t ->\t{0}"
                 .format(device.max_compute_units))
            print("Local Memory\t\t ->\t{0:.0f} KB"
                 .format(device.local_mem_size/1024.0))
            print("Constant Memory\t\t ->\t{0:.0f} KB"
                 .format(device.max_constant_buffer_size/1024.0))
            print("Global Memory\t\t ->\t{0:.0f} GB"
                 .format(device.global_mem_size/1073741824.0))
            print("Max Buffer/Image Size\t ->\t{0:.0f} MB"
                 .format(device.max_mem_alloc_size/1048576.0))
            print("Max Work Group Size\t ->\t{0:.0f}"
                 .format(device.max_work_group_size))
    print("=" * 60)

if __name__ == "__main__":
    getPlatformDevices()
