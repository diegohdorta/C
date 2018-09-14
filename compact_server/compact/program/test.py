#!/usr/bin/env python

from network import *
import sys


# Warning: passe o endereco IP como argumento antes de rodar o programa.

if __name__ == '__main__':

	if(len(sys.argv) < 2):
		sys.exit("ERROR - Missing IP!")		
	sock = create_tcp_socket()
	server_address = (sys.argv[1], 7000)
	print >>sys.stderr, ("Connecting to %s on port %s") % server_address

	sock.connect(server_address)
		
	while True:

		print ("# Choose types: 1 - Scan | 2 - LoopBack | 3 - DAC | 4 - Motor | 5 - Temperature | 6 - Current  | 0 - Exit#\n")

		t = raw_input()
		
		# Package for scan:
		# [0x53, 1]

		# Package for loopback:
		# [0x53, ?]

		# Package for motor:
		# [0x53, command, address, dados]
		# dados = [direction, velocity, position]

		if (t == str(1)):
			print ("Pegando informacoes para SCAN\n")			
			message = [0x53,1]
			print message

		elif (t == str(2)):
			#address = raw_input(" ")			
			print ("Pegando informacoes para LoopBack!\n")
			#for address in range(2,5):
			message = [0x53,2,2]

		elif (t == str(3)):
			print ("Pegando informacoes para DAC!\n")

		elif (t == str(4)):
			print ("Pegando informacoes para MOTOR!\n")
			message = [0x53,4,4,0,20,200]
		elif (t == str(5)):
			print ("Pegando informacoes para TEMPERATURA!\n")

		elif (t == str(6)):
			print ("Pegando informacoes para CORRENTE!\n")
			
		elif (t == str(0)):
			sock.close()
			sys.exit("Socket closed. Exiting...")	

		else:
			print ("Invalid Option!\n")


		try:
			hexdata = ''.join([chr(item) for item in message])

			print >>sys.stderr, ("Sending: %s") % message
			sock.sendall(hexdata)

			data = sock.recv(32)
			print >>sys.stderr, 'received "%s"' % data

			length = len(data)
			idata = []

			for i in range(length):
				idata.append(ord(data[i]))

		except:			
			print >>sys.stderr, ("Impossible to send message!\n")



