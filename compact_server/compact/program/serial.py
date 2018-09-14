#!/usr/bin/env python

import time
import geniePi
import sys
import bus
import socket
from network import *

PORT = '/dev/ttyAMA0'
BAUD_RATE = 115200

def setup_port():

	geniePi.genieSetup(PORT, BAUD_RATE)

def opening_serial_communication(f):

	setup_port()

	printing_ip_on_display()	
	
	time.sleep(0.2)
	geniePi.genieWriteStr(2, 'Searching boards...')
	devices = bus.scan()
	
	for i in range(1,5):
		geniePi.genieWriteStr(i+2, str(devices[i-1]))    

	geniePi.genieWriteStr(2, 'Found boards!')
	print >>sys.stderr, ("Scan realizado com sucesso!\n")
	
def printing_ip_on_display():

	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.connect(("gmail.com",90))
	local_ip = s.getsockname()[0]
	geniePi.genieWriteStr(1, local_ip)
	s.close()

	return local_ip
