#!/usr/bin/env python
# coding: utf-8
# mcsrv.py 20080524 AF
 
import sys, struct, socket
 
def mcastServer():
    addr = '225.0.0.1'
    port = 10000

    print("running server on {}:{}".format(addr, port))

    fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    fd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
 
    # bind udp port
    fd.bind(('', port))
 
    # set mcast group
    mreq = struct.pack('4sl', socket.inet_aton(addr), socket.INADDR_ANY)
    fd.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
 
    buff = "You are watching me!"
 
    try:
        while True:
            data, addr = fd.recvfrom(1024)

            print("{} bytes from {}: {}".format(len(data), addr, data))
            
            fd.sendto(buff, addr)
            
    except KeyboardInterrupt:
        print 'done'
        sys.exit(0)
 
if __name__ == '__main__':


    mcastServer()
