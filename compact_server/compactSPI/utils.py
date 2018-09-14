#!/usr/bin/env python

import bus
import time
import sys

MINIMUM_DATA_SIZE = 2
MAXIMUM_DATA_SIZE = 15
CHECK = 0x53

def print_message():

	print("\t# Project CompactSPI #\n")	
	
def handler_received_data(string_data):

	print("Treating receveid string data: " + str(string_data))

	if (string_data == '\n'):
		print >>sys.stderr, ("Receive from client invalid command!")
		return

	length = len(string_data)

	if (length < MINIMUM_DATA_SIZE):
		print >>sys.stderr, ("The package size is too small!")
		return

	if (length > MAXIMUM_DATA_SIZE):
		print >>sys.stderr, ("The package size is too large!")
		return

	integer_data = []
	
	print("Converting string data to integers...\n")
	
	for i in range(length):
		integer_data.append(ord(string_data[i]))

	check    = integer_data[0]
	command  = integer_data[1]

	print ("Check: ", str(check))
	print ("Command: ", str(command))

	if(check == CHECK):

		if(command == 1):
		
			print ("REALIZANDO SCAN!\n")
			devices = bus.scan()
			print devices
			return devices

		elif(command == 2):

			print ("REALIZANDO LOOPBACK!\n")
			address = integer_data[2]
			data = [1,2,3,4,5,6,7,8]
			read = bus.loopback(address,data)
			print "Dados enviados: ", data
			print "Dados recebidos: ", read
				
		elif(command == 3):

			print ("REALIZANDO DAC!\n")

		elif(command == 4):

			print ("REALIZANDO MOTOR!\n")
			board_address 		= integer_data[2]
			direction 		= integer_data[3]
			velocity 		= integer_data[4]
			position	 	= integer_data[5]			
			
			motor(board_address, direction, velocity, position)
			
		elif(command == 5):

			print ("REALIZANDO TEMPERATURA!\n")
		
		elif(command == 6):

			print ("REALIZANDO CORRENTE!\n")

		else:
			print >>sys.stderr, ("Error: Incorrect Command\n")
			return                
	else:
		print >>sys.stderr, ("Error: Incorrect Package\n") 		
		return

	print("Cheguei no fim da funcao handler\n")

def motor(address, direction, velocity, position):

	data = [direction,velocity,position]
	
	print ("DADOS PARA COMANDAR MOTOR: ", data)
	bus.put(address,data)	
	info = bus.get(address,1)	
	print("Motor: ", info)	
	bus.deinit()



