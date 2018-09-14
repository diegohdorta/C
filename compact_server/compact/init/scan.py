#!/usr/bin/env python

import bus
import time
import sys
import geniePi

PORT = '/dev/ttyAMA0'
BAUD_RATE = 115200

def handler():

	while True:

		while True:
		
			event = geniePi.genieReadObj(geniePi.GENIE_OBJ_WINBUTTON, 1)
			if event == 1:
				break
		
		scan_boards()


def scan_boards():

	geniePi.genieWriteStr(2, 'Searching boards...')
	devices = bus.scan()

	print devices

	for i in range(1,5):
		time.sleep(0.1)
		geniePi.genieWriteStr(i+2, str(devices[i-1]))    

	geniePi.genieWriteStr(2, 'Found boards!')

	print >>sys.stderr, ("Scan realizado com sucesso!\n") 


if __name__ == '__main__':

	print("Iniciated program to scan boards!\n")
	geniePi.genieSetup(PORT, BAUD_RATE)
	handler()
