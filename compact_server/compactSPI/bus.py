#!/usr/bin/env python
# Write and Read SPI Module
import time
import spidev
import RPi.GPIO as GPIO

# Pins for address of bus
A2 = 27                    
A1 = 17                   
A0 = 4        

# GPIO Configuration
GPIO.setmode(GPIO.BCM)     		# Pins reference of processor.
GPIO.setwarnings(False)    		# desable warning ...GPIO.setmode(GPIO.BCM)                     
GPIO.setup(A2,GPIO.OUT)    		# output digital
GPIO.setup(A1,GPIO.OUT)    		# output digital
GPIO.setup(A0,GPIO.OUT)    		# output digital
GPIO.output(A2,0)          		# A2 = 0V
GPIO.output(A1,0)          		# A1 = 0V
GPIO.output(A0,0)          		# A0 = 0V  

# Open port for SPI comumnication
spi = spidev.SpiDev()      		# Create object for SPI port 
spi.open(0,0)              		# Open port SPI  
spi.mode = 0               		# SPI in mode = 0
spi.bits_per_word = 8      		# Transfer 8 bits     
spi.max_speed_hz = 2000000		# clock = 1 MHz

#-----------------------------------------------
def deinit():
	GPIO.output(A2,0)          	# A2 = 0V
	GPIO.output(A1,0)          	# A1 = 0V
	GPIO.output(A0,0)          	# A0 = 0V

#-----------------------------------------------
def put(address,data):
	#addr = int(address)
	choose(address)
	time.sleep(0.001)		# wait 1 ms
	print 'Sending Data for Board with address: %d ' % address
	"""
		Message to send:
		Byte[0] = 'S'  = 0x53 --> send message initialization
		Byte[1] = address     --> {A2,A1,A0}
		Byte[2] = 0x02 =      --> command
		Byte[3] = lenght data
		Byte[4] = data
	"""
	#print ''.join(["%20X " % ord(x) for x in address]).strip()
	lenght = len(data)
	vector = [0x53,address,0x02,lenght] + data
	try:
		spi.xfer2(vector)
	except:
		print 'Error: spi.xfer2'
	return True
	
#-----------------------------------------------
def get(address, lenght):
	choose(address)
	time.sleep(0.001)		# wait 1 ms second
	"""
		Message to send:
		Byte[0] = 'S'  = 0x52  --> receive the message of initialization
		Byte[1] = address B
		Byte[2] = Type Board
		Byte[3] = lenght data
		Byte[4] = data
	"""
	#lenght = len(data)		
	lenght = lenght + 4		# Leght Data + Header (Byte[0] at Byte[3])
	print 'lenght = ' + str(lenght)
	read = spi.readbytes(lenght)  	# reading message
	cont = 0
	flag = 1
	while(read[0] != 0x52):
		cont = cont + 1
		if cont > 1000:
			print 'Error: Time Out > %d' %cont
			flag = 0
			break
		else:
			read = spi.readbytes(lenght)
		time.sleep(0.01)		
	return read

#-----------------------------------------------
def choose(i):
	a2 = i & 0x04
	a2 = a2 >> 2
	a1 = i & 0x02
	a1 = a1 >> 1
	a0 = i & 0x01
	GPIO.output(A0,a0)
	GPIO.output(A1,a1)
	GPIO.output(A2,a2)

#-----------------------------------------------
def scan():
	devices = []
	print 'Reading Board with address: 1'
	print 'Address: 1 , Board: CPU \n'
	devices.append('CPU')
	for address in range(2,5):
		choose(address)
		#time.sleep(0.1)                 # wait one second
		print 'Reading Board with address: %d ' % address
		"""
			Message to send:
			Byte[0] = 'S'  = 0x53 --> send message initialization
			Byte[1] =  i          --> address: {A2,A1,A0}
			Byte[2] = 0x01 =      --> command
			Byte[3] = 0x01 =      --> lenght data
			Byte[4] = 0x01 =      --> any data
		"""
		vector = [0x53,address,0x01,0x01,0x01]    
		spi.xfer2(vector)
		#time.sleep(0.1) 
		"""
			Message to receive:
	    		Byte[0] = 'R'  = 0x52 --> receive message initialization
	    		Byte[1] =  Address B  --> address of bus
	    		Byte[2] =             --> Type of board
	  	"""
	  	nameType = ''
	  	counter = 0
	  	read = spi.readbytes(3)  # reading message       
	  	if(0x52 == read[0] and address == read[1]):
	    		#print 'Receive message with Correct Address, Addr_B'
	    		nameType = boardType(read[2])
	    		print 'Address: %d , Board: %s \n' % (address,nameType)
	    		devices.append(nameType)
	  	elif(0x52 != read[0] or address != read[1]):
		        devices.append('No Board')
	    		print 'No Board \n'
	  	else:  print 'Verify protocol of data'
  	return devices

#-----------------------------------------------
def boardType(type):
	# Find type of board conect in the bus
  	dict = {'Output Analog 0-10V':50, 'Ammeter':51, 'Step Motor':52, 'Thermocoupler':53}
  	board = ''
  	for e in dict.keys():
    		if type == dict[e]: board = e
    		else: pass
  	return board

#-----------------------------------------------
def loopback(address,data):
	choose(address)
	time.sleep(0.01)	                                # wait 10 ms
	print 'Testing Board with address: %d ' % address
	"""
		Message to send:
		Byte[0] = 'S'  = 0x53 --> send message initialization
		Byte[1] = address     --> {A2,A1,A0}
		Byte[2] = 0x03 =      --> command
		Byte[3] = lenght data
		Byte[4] = any data
	"""
	lenght = len(data)
	vector = [0x53,address,0x03,lenght] + data
	spi.xfer2(vector)
	"""
		Message to receive:
		Byte[0] = 'R'  = 0x52 --> receive message initialization
		Byte[1] =  Address B  --> address of bus
		Byte[2] =             --> Type of board
	"""
	lenght = lenght + 4
	read = spi.readbytes(lenght)                            # reading message
	return read


