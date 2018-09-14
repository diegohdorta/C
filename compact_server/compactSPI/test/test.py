#!/usr/bin/env python

from network import *
import sys

if __name__ == '__main__':

	if(len(sys.argv) < 7):
		sys.exit("ERROR - Missing: IP, Address Board, Command, Length, Data 1, Data 2\n")

	sock = create_tcp_socket()

	server_address = (sys.argv[1], 7000)
	
	print >>sys.stderr, ("Connecting to %s port %s") % server_address
	
	sock.connect(server_address)

	try:
	    addressA = int(sys.argv[2])
	    command  = int(sys.argv[3])
	    length   = int(sys.argv[4])
	    data1    = int(sys.argv[5])
	    data2    = int(sys.argv[6])
	    
	    message = [0x53,addressA,command,length,data1]
	    
	    hexdata = ''.join([chr(item) for item in message])
	    
	    print >>sys.stderr, ("Sending: %s") % message
	    sock.sendall(hexdata)
	    

	    data = sock.recv(32)
	    print >>sys.stderr, 'received "%s"' % data
	    length = len(data)
	    idata = []
	    for i in range(length):
		idata.append(ord(data[i]))                                          # ASCII for Integer converter        
	    #hexdata = ''.join([chr(item) for item in data])
	    #print hexdata
	    #print 'received iData %d' % iData

	except:
	    sock.close()
	    print 'Close Socket Client'



