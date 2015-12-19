#define _XOPEN_SOURCE 700

#include "../include/epnl.h"

#define ENABLE 1
#define BACKLOG 100

ready_socket_t create_tcp_socket(uint16_t port)
{
	int s;
	int enable = ENABLE;

	struct sockaddr_in local;

	local.sin_family = AF_INET;
	local.sin_port   = htons(port);
	local.sin_addr.s_addr = INADDR_ANY;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		debug(stderr, "Error creating socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		debug(stderr, "Error trying to reuse address socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (bind(s, (struct sockaddr *)&local, sizeof(local)) < 0) {
		debug(stderr, "Error binding on port: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (listen(s, BACKLOG) != 0) {
		debug(stderr, "Error trying to listen: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s;
}
