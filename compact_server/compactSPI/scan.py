# Software control of bus SPI

# staff of development

# 
# 
# 

# Version 1.0 - 05/11/2014

import time              # Library time
import RPi.GPIO as GPIO  # Library GPIO
import bus               # Library Bus SPI Control
#import server            # Library Ethernet Communication
#import display           # Library Display Control
 
print '\nTeste SCAN\n'

#address   = int(raw_input('What is address ? '))
address = 3


a = [82, address]

typeBoard = 3

if typeBoard == 1:   
	a.append(50) 
elif typeBoard == 2: 
	a.append(52)
elif typeBoard == 3: 
	a.append(53)
elif typeBoard == 4: 
	a.append(51)	
else: print 'Error: Incorrect Board'

print a

for i in range(1):
	b = bus.scan(address)
