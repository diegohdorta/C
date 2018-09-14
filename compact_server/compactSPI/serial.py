#!/usr/bin/env python

import time
#import geniePi
import sys

PORT = '/dev/ttyAMA0'
BAUD_RATE = 115200

def opening_serial_communication(f):

	#lista = ["diego", "william", "gustavo"]
	
	#for i in range(len(lista)):
	#	f.write(lista[i])
	
	#f.close()

	print "fechei arquivo\n"

	#geniePi.genieSetup(PORT, BAUD_RATE)
	#No lugar de conexao local, incluir o INADDR_ANY.
	#geniePi.genieWriteStr(0, 'Conexao Local')
	#geniePi.genieWriteObj(0x0E, 0x00, 0x01)
	#time.sleep(1)
	#geniePi.genieWriteStr(1, 'Pronto para operar!')
	
	#while True:
	#	event = geniePi.genieReadObj(geniePi.GENIE_OBJ_WINBUTTON, 1)
#		if event == 1:
#			break
			
#	time.sleep(0.2)
#	geniePi.genieWriteStr(2, 'Procurando Placas...')
	
#	for i in range(1,5):
#		devices = bus.scan(i)
#		geniePi.genieWriteStr(i+2, str(devices))    

#	geniePi.genieWriteStr(2, 'Placas encontradas!')

#	for i in range(1,5):
#        	devices = bus.scan(i)
#	        geniePi.genieWriteStr(i+2, str(devices))    

#	geniePi.genieWriteStr(2, 'Placas encontradas!')	

#	for i in range(1,5):
#		f.write(devices[i])
#		f.write('\n')

	print >>sys.stderr, ("Scan realizado com sucesso!\n")
	
	# Terminou o scan, colocar um LED
	# salvar o devices em um arquivo


def turn_on_scan_status():

	print("Ligando LED!")
	#colocar codigo para habilitar botao verde.
	#geniePi.genieWriteObj(0x0E, 0x00, 0x01)

def turn_off_scan_status():
	
	print("Desligando LED!")
	#colocar cpdigo para desabilitar botao vermelho.
	#geniePi.genieWriteObj(0x0E, 0x00, 0x01)
