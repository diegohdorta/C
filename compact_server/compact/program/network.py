#!/usr/bin/env python

import socket
import sys

PORT = 7000
NUMBER_OF_CONNECTIONS = 1
SIZE_DATA_PACKET = 100

def create_tcp_socket():
 
	print("Creating a TCP/IP socket...\n")
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	reuse_port_bind(s)	
	return s

def reuse_port_bind(s):

	s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)	
	return

def binding_tcp_socket(sock):

	server_address = ('', PORT)
	print("Starting up on %s:%s" % server_address)
	sock.bind(server_address)
	
def listening_tcp_socket(sock):	

	print("Listening %d TCP socket...\n" % NUMBER_OF_CONNECTIONS)
	sock.listen(NUMBER_OF_CONNECTIONS)
	
def accepting_new_connection(sock):

	print("Waiting for a connection...\n")
	connection, client_address = sock.accept()
	print("Connected client", client_address)	
	return connection

def receive_data_from_client(connection):

	print("Waiting to receive package from client")
	data = connection.recv(SIZE_DATA_PACKET)
	
	if (data == ''):
		return False
		
	send_message_to_client(connection, "Receive data with success!")
	print("Received data ", data)
	return data

def send_message_to_client(sock, message):

	print("Sending message to client: ", message)
	sock.send(message)

	

