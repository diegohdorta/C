#define _BSD_SOURCE

#include "include/library.h"

int create_tcp_socket(uint16_t port)
{
	int s;
	int enable = 1;

	struct sockaddr_in local;

	local.sin_family = AF_INET;
	local.sin_port   = htons(port);
	local.sin_addr.s_addr = INADDR_ANY;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		debug(log_error, "Error creating socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		debug(log_error, "Error trying to reuse address socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (bind(s, (struct sockaddr *)&local, sizeof(local)) < 0) {
		debug(log_error, "Error binding on port: %s\n", strerror(errno));
		debug(stderr, "Error binding on port: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (listen(s, NUMBER_WEB_CONNECTIONS) != 0) {
		debug(log_error, "Error trying to listen: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s;
}

int accept_new_connection_from_web(int s)
{
	int ns;
	socklen_t length;

	struct sockaddr_in info;

	length = sizeof(info);
	debug(stderr, "Waiting for web site to connect...\n");

	if ((ns = accept(s, (struct sockaddr *)&info, &length)) == -1) {
		debug(log_error, "Error trying to accept new connection: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	debug(stderr, "The web site %s is now connected!\n", inet_ntoa(info.sin_addr));
	debug(log_error, "The web site %s is now connected!\n", inet_ntoa(info.sin_addr));
	return ns;
}

int accept_new_device_connection(int s)
{
	int ns;
	socklen_t length;

	struct sockaddr_in info;

	length = sizeof(info);
	debug(stderr, "Waiting for device to connect...\n");

	if ((ns = accept(s, (struct sockaddr *)&info, &length)) == -1) {
		debug(log_error, "Error trying to accept new connection: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	debug(stderr, "The device %s is now connected!\n", inet_ntoa(info.sin_addr));
	debug(log_error, "The device %s is now connected!\n", inet_ntoa(info.sin_addr));
	return ns;
}

/* END */

