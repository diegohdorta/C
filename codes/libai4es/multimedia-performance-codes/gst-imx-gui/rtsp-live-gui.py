#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (C) 2019 Diego Dorta
Diego Dorta <diego.dorta@nxp.com>
"""
import socket
import struct
import sys
 
def runMultiCastServer(addr, port):
    fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    fd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    fd.bind(('', port))
 
    # set mcast group
    mreq = struct.pack('4sl', socket.inet_aton(addr), socket.INADDR_ANY)
    fd.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
 
    try:
        while True:
            data, addr = fd.recvfrom(1024)
            print("{} bytes from {}: {}".format(len(data), addr, data))
    except KeyboardInterrupt:
        print("done")
        sys.exit(0)
 
if __name__ == '__main__':
    try:
        addr = sys.argv[1]
        port = int(sys.argv[2])
    except IndexError:
        addr = '225.0.0.1'
        port = 10000
    finally:
        print("running server on {}:{}".format(addr, port))
        runMultiCastServer(addr, port)
