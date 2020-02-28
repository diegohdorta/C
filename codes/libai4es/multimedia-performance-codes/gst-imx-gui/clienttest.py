#!/usr/bin/env python
# coding: utf-8
# udpcli.py 20080524 AF
 
import sys, socket
 
if __name__ == '__main__':

    addr = '225.0.0.1'
    port = 10000
    buff = 'Hello'

    fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    fd.sendto(buff, (addr, port))
    data, addr = fd.recvfrom(1024)

    print("{} bytes from {}: {}".format(len(data), addr, data))
