/* Sigma code: undefined
 * Diego Dorta <diegohdorta@gmail.com>
 */
#include "../include/debug.h"
#include "../include/event.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

unsigned int uid = MINIMUM;
data_t *clients[MAXIMUM];

data_t create_server(data_t *master)
{
	unsigned int enable = true;

	if (!(master->sock = socket(AF_INET , SOCK_STREAM , 0)))
		sigma_err_quit("%s socket() failed!", trace);

	if (setsockopt(master->sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		sigma_err_quit("%s setsockopt() failed!", trace);
		
	master->address.sin_family = AF_INET;
	master->address.sin_addr.s_addr = INADDR_ANY;
	master->address.sin_port = htons(master->port);

	if (bind(master->sock, (struct sockaddr *)&master->address, sizeof(master->address)) < 0)
		sigma_err_quit("%s setsockopt() failed!", trace);

	if (listen(master->sock, 3) < 0)
		sigma_err_quit("%s listen() failed!", trace);

	return *master;
}

void queue_add(data_t *cl) // Need to fix function
{
	int i;
	for (i = 0; i < MAXIMUM; i++) {
		if (!clients[i]) {
			clients[i] = cl;
			break;
		}
	}
}

void queue_delete(int uid) // Need to fix function
{
	int i;
	for(i = 0; i < MAXIMUM; i++) {
		if (clients[i]) {
			if (clients[i]->id == (unsigned int)uid) {
				clients[i] = NULL;
				return;
			}
		}
	}
}

static data_t
connection(data_t *master)
{
	int ns;
	struct sockaddr_in caddr;
	socklen_t lenght = sizeof(caddr);

	if ((ns = accept(master->sock, (struct sockaddr *)&caddr, &lenght)) < 0)
		sigma_err_quit("%s accept() failed!", trace);

	data_t *c = (data_t *)malloc(sizeof(data_t));
	if (c == NULL)
		sigma_err_quit("%s malloc() error!", trace);

	c->sock = ns;
	c->address = caddr;
	c->id = uid++;
	sprintf(c->name, "%d", c->id);
	queue_add(c);

	return *c;
}

static void
send_or_exit(data_t *client, char *message)
{
	if (send(client->sock, message, strlen(message), 0) != (ssize_t)strlen(message))
		sigma_err_quit("%s send() failed!", trace);
}

static void online(data_t *local)
{
	int addrlen, i;
	data_t client;

	for (i = 0; i < MAXIMUM; i++) {
		client = *clients[i];
		if (clients[i] == 0) break;
		else {
			addrlen = sizeof(client.address);
			getpeername(client.sock, (struct sockaddr*)&client.address, (socklen_t*)&addrlen);
			send_or_exit(local, inet_ntoa(client.address.sin_addr));
			break;
		}
	}
}

void
loop_events(data_t *master)
{
	g_running = true;
	fd_set fdsockets;
	int ns[MAXIMUM];
	int maximum_fdsocket, fdsocket;
	int event, i;
	data_t client;
	data_t local;
	ssize_t size;
	unsigned int command = 0;

	char *buffer = malloc(sizeof(char) * ONEKBUFFER);
	if (buffer == NULL)
		sigma_err_quit("%s malloc() failed!", trace);

	status_t c = CONNECTED;
	status_t d = DISCONNECTED;
	status_t e = ENDING;
	
	signal(SIGINT, &sig_handler);
	memset(ns, 0, sizeof(ns));
	sigma_cpu_features();
	
	do {
		FD_ZERO(&fdsockets);
		FD_SET(master->sock, &fdsockets);
		maximum_fdsocket = master->sock;
		
		for (i = 0; i < MAXIMUM; i++) {
			fdsocket = ns[i];
			if (fdsocket > 0) FD_SET(fdsocket, &fdsockets);
			if (fdsocket > maximum_fdsocket) maximum_fdsocket = fdsocket;
		}

		event = select(maximum_fdsocket + 1, &fdsockets, NULL, NULL, NULL);		
		if ((event < 0) && (errno != EINTR)) 
			sigma_err_quit("%s select() failed!", trace);
				
		if (FD_ISSET(master->sock, &fdsockets)) {		
			client = connection(master);
			sigma_debug(&client, NULL, c);
			send_or_exit(&client, FORMAT_INIT);

			for (i = 0; i < MAXIMUM; i++)		
				if (!ns[i]) { ns[i] = client.sock; break; }
		}
		
		for (i = 0; i < MAXIMUM; i++) {
			fdsocket = ns[i];
			if (FD_ISSET(fdsocket, &fdsockets)) {
				start_time();
				local.sock = fdsocket;
				if (!(size = read(fdsocket, buffer, ONEKBUFFER))) {
					sigma_debug(&local, NULL, d);
					queue_delete(local.id);
					close(fdsocket);
					ns[i] = ZERO;
					uid--; clients[i] = NULL;
				}
				else {
					buffer[size] = '\0';
					command = atoi(buffer);

					switch (command) {
					case CMD_ONLINE:
						online(&local);
						final_time(buffer);
						send_or_exit(&local, buffer);
						break;
					case CMD_EXIT:
						sigma_debug(&local, NULL, d);
						close(fdsocket);
						ns[i] = ZERO;
						uid--; clients[i] = NULL;
					}
				}
			}
		}			
	} while (g_running);
	free(buffer);
	sigma_debug(NULL, NULL, e);
	exit(EXIT_SUCCESS);
}
