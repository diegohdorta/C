#!/usr/bin/env python

# Software control of bus SPI

# staff of development

# William Roberto de Araujo
# Afonso Alonso 

# Version 1.0 - 06/05/2015

import bus               						# Library Bus SPI Control.
import time
import sys

def Motor(address,direction, velocity, position, loop):

	data = [direction,velocity,position,loop]				# [Direction, Velocity, Step].				
	lenght = 1						        # get length of Data.
	typeBoard = 52							# Type of Board.
	bus.put(address,data)
	resp = bus.get(address,lenght)
	print resp
	bus.deinit()
	
if __name__ == '__main__':
	dir = int(sys.argv[1])
	loop = int(sys.argv[2])
	for i in range(1):
		try:
			for i in range(loop):
				Motor(4,dir,10,250)
				time.sleep(0.5)
			#Motor(4,1,10,200)
			#time.sleep(0.5)
		except KeyboardInterrupt:
			print 'Exit program'
			exit()
