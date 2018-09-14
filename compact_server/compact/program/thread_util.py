#!/usr/bin/python

import os
import threading
import time
import geniePi
from serial import *

MESSAGE_ON = 'Operational System On'
MESSAGE_OFF = 'Operational System Off'
TRUE = 1
R_BUTTON_MEASUREMENT = 3
R_BUTTON_SCAN = 4
R_BUTTON_CONFIGURATION = 6
START_SCAN = 5
REBOOT = 7
ON = 1
OFF = 0

class handler(threading.Thread):

	def __init__(self, threadID, name):

		threading.Thread.__init__(self)

		self.threadID = threadID
		self.name = name

	def run(self):

		print "Starting Thread: " + self.name 
		recover_data(self.name)
		print "Exiting: " + self.name

class scan(threading.Thread):

	def __init__(self, threadID, name):

		threading.Thread.__init__(self)

		self.threadID = threadID
		self.name = name

	def run(self):

		print "Starting Thread: " + self.name
		scan_recover(self.name)
		print "Exiting: " + self.name		

class configuration(threading.Thread):

	def __init__(self, threadID, name):
		
		threading.Thread.__init__(self)
	
		self.threadID = threadID
		self.name = name

	def run(self):

		print "Starting Thread: " + self.name
		configuration_recover(self.name)
		print "Exiting: " + self.name

class reboot(threading.Thread):

	def __init__(self, threadID, name):

		threading.Thread.__init__(self)

		self.threadID = threadID
		self.name = name

	def run(self):
		
		print "Starting Thread: " + self.name
		reboot_system(self.name)
		print "Exiting: " + self.name


def recover_data(threadName):
	
	while True:

		r = read_display(R_BUTTON_MEASUREMENT) | read_display(R_BUTTON_SCAN) | read_display(R_BUTTON_CONFIGURATION)

		if (r == TRUE):

			print >>sys.stderr, ("%s: Recovering info to display!") % threadName
			printing_ip_on_display()
			turn_led(ON)

def scan_recover(threadName):

	turn_led(ON)

	while True:

		while True:

			if (read_display(START_SCAN) == TRUE):
				break

		time.sleep(0.2)			
		geniePi.genieWriteStr(2, 'Searching boards...')
		devices = bus.scan()
	
		for i in range(1,5):
			geniePi.genieWriteStr(i+2, str(devices[i-1]))    

		geniePi.genieWriteStr(2, 'Found boards!')
		print >>sys.stderr, ("%s: Scan realizado com sucesso!\n") % threadName 

def configuration_recover(threadName):

	print >>sys.stderr, ("%s: Recovering info to configuration! (NOT READY)") % threadName

def reboot_system(threadName):

	while True:
		
		while True:

			if (read_display(REBOOT) == TRUE):
				break

		print "Rebooting the system..."
		turn_led(OFF)
		os.system("sudo reboot")		
		
def read_display(button):

	return geniePi.genieReadObj(geniePi.GENIE_OBJ_WINBUTTON, button)

def turn_led(status):

	if (status == ON):
		print >>sys.stderr, ("Turning on LED!")
		geniePi.genieWriteObj(19, 0, 1)
		geniePi.genieWriteStr(0, MESSAGE_ON)
	else:
		print >>sys.stderr, ("Turning off LED!")
		geniePi.genieWriteObj(19, 0, 0)
		geniePi.genieWriteStr(0, MESSAGE_OFF)

def start_threads():
	
	t = handler(1, "recover_info")
	s = scan(1, "scan_info")
	#c = configuration(1, "configuration_info")
	r = reboot(1, "reboot_system")	

	t.start()
	s.start()
	#c.start()
	r.start()
	t.join()
	s.join()
	r.join()

