#!/usr/bin/env python

from network import *
from utils import *
from serial import *
from thread_util import *

import sys
import time
import os

PATH = '/home/pi/devices.txt'

if __name__ == '__main__':

	os.system("clear")
	
	print_message()	

	f = open(PATH, 'w')

	opening_serial_communication(f)	

	sock = create_tcp_socket()	
	binding_tcp_socket(sock)
	listening_tcp_socket(sock)

	start_threads()

	while True:
	
		connection = accepting_new_connection(sock)
		
		while True:
		
			ret = receive_data_from_client(connection)
			if (ret == False):
				connection.close()
				break
			
			print(ret)	
			handler_received_data(ret)
	
			

