#!/usr/bin/python

import socket
import sys
import time
import geniePi

PORT = '/dev/ttyAMA0'
BAUD_RATE = 115200
MESSAGE_ON = 'Operational System On'
MESSAGE_OFF = 'Operational System Off'

def recover_data(ip):
	
	while True:
		# Add all the return bottons here.
		event = geniePi.genieReadObj(geniePi.GENIE_OBJ_WINBUTTON, 7)
		
		if event == 1:
			print ("valor de event: %d") % event
		if (event == 1):
			print >>sys.stderr, ("Recovering info to display!")
			time.sleep(0.1)
			geniePi.genieWriteObj(19, 0, 1)
			time.sleep(0.1)
			geniePi.genieWriteStr(0, MESSAGE_ON)
			time.sleep(0.1)
			geniePi.genieWriteStr(1, ip)
			time.sleep(0.1)
			event = 0

def printing_ip_on_display():

	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	s.connect(("gmail.com",90))
	local_ip = s.getsockname()[0]
	time.sleep(0.1)
	geniePi.genieWriteStr(1, local_ip)
	time.sleep(0.1)
	geniePi.genieWriteObj(19, 0, 1)
	time.sleep(0.1)
	geniePi.genieWriteStr(0, MESSAGE_ON)
	s.close()
	
	return local_ip

def turn_on_off_led(status):

	geniePi.genieSetup(PORT, BAUD_RATE)
	
	if (status == 1):
		print("Turning on LED!")
		time.sleep(0.1)
		geniePi.genieWriteObj(19, 0, 1)
		time.sleep(0.1)
		geniePi.genieWriteStr(0, MESSAGE_ON)
	else:
		print("Turning off LED!")
		time.sleep(0.1)
		geniePi.genieWriteObj(19, 0, 0)
		time.sleep(0.1)
		geniePi.genieWriteStr(0, MESSAGE_OFF)

	geniePi.genieClose()

if __name__ == '__main__':

	print("Iniciated program to recover data!\n")
	turn_on_off_led(1)
	ip = printing_ip_on_display()
	recover_data(ip)

