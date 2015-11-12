/* Network functions */
/* Medipix Server - Developed by Diego Dorta */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>

#include "common.h"

int create_tcp_socket(void)
{
	int s;
	const uint16_t port = PORT_FOR_INFO;
	int enable = 1;

	struct sockaddr_in local;

	local.sin_family = AF_INET;
	local.sin_port   = htons(port);
	local.sin_addr.s_addr = INADDR_ANY;

	debug(stderr, "Creating TCP socket...\n");
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		debug(log_error, "Socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		debug(log_error, "Setsockopt(SO_REUSEADDR) Failed %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	debug(stderr, "Binding...\n");
	if (bind(s, (struct sockaddr *)&local, sizeof(local)) < 0) {
		debug(log_error, "Bind: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	debug(stderr, "Listening...\n");
	if (listen(s, 1) != 0) {
		debug(log_error, "Listen: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s;
}

int accept_new_connection(int s)
{
	int ns;
	socklen_t length;

	struct sockaddr_in ioc;

	length = sizeof(ioc);
	debug(stderr, "Waiting for IOC to connect on server...\n");

	if ((ns = accept(s, (struct sockaddr *)&ioc, &length)) == -1) {
		debug(log_error, "Accept: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	debug(stderr, "The client IOC IP %s is now connected!\n", inet_ntoa(ioc.sin_addr));
	return ns;
}

void receive_variables(struct process_arguments *args)
{
	int x;
	int aux;
	const int bit_count_dict[] = {1, 12, 6, 24};
	ssize_t size = 0;
	bool done;
	size_t i = 0;
	size_t variable_size = VARIABLE_SIZE;
	char buffer[BUFFER_SIZE];
	char variable[VARIABLE_SIZE];

	struct acquisition_info info = {
		.filename = DEFAULT_FILE_NAME,
		.number_frames = MINIMUM_IMAGE_COUNT,
		.number_bits = 0,
		.read_counter = 0,
		.gap_us = MEDIPIX_TIMEOUT
	};

	debug(stderr, "The filename is by default: %s\n", info.filename);
	debug(stderr, "The number of bits is by default: %d\n", bit_count_dict[info.number_bits]);
	debug(stderr, "The number of frames is by default: %d\n", info.number_frames);
	debug(stderr, "The read counter is by default: %d\n", info.read_counter);
	debug(stderr, "The acquisition time is by default: %d\n", info.gap_us);

	do {
		debug(stderr, "Waiting for variables...\n");
		done = false;
		i = 0;
		do {
			size = recv(args->remote_socket, buffer, BUFFER_SIZE, 0);

			if (size == 0) {
				debug(stderr, "The IOC was turned off!\n");
				debug(log_error, "The IOC was turned off!\n");
				return;
			}

			for (x = 0; x < size; x++) {
				if (buffer[x] == '\n') {
					variable[i] = '\0';
					done = true;
					break;
				}
				variable[i] = buffer[x];

				i++;
				if (i == variable_size) {
					debug(log_error, "Buffer full...\n");
					/* Enviando mensagem para o IOC que o nome não foi recebido */
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);
					i = 0;
					break;
				}
			} /* for */
		} while (!done);

		debug(stderr, "Content of buffer received from IOC: %s\n", variable);

		aux = atoi(&(variable[1]));

		switch(variable[0]) {

			case ID_FILENAME:

				strcpy(info.filename,(&(variable[1])));
				debug(stderr, "Current file name: %s\n",info.filename);
				break;

			case ID_FRAMES:

				if(aux < MINIMUM_IMAGE_COUNT || aux > MAXIMUM_IMAGE_COUNT) {
					debug(log_error, "Invalid number of frames: %s\n", &variable[1]);
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);
					continue;
				}
				info.number_frames = aux;
				debug(stderr, "Current number of frames: %d\n",info.number_frames);
				break;

			case ID_BITS:

				if(aux < MINIMUM_BIT_COUNT || aux > MAXIMUM_BIT_COUNT) {
					debug(log_error, "Invalid number of bits: %s\n", &variable[1]);
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);
					continue;
				}
				info.number_bits = aux;
				debug(stderr, "Current number of bits: %d\n",info.number_bits);
				break;

			case ID_ACQUIRE:

				debug(stderr, "Sending acquisition request to brother\n");
				send_or_panic(args->brother_socket, &info, sizeof(info));
				break;

			case ID_READING_COUNT:

				if(aux < MINIMUM_READING_COUNT || aux > MAXIMUM_READING_COUNT) {
					debug(log_error, "Invalid reading count: %s\n", &variable[1]);
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);
					continue;
				}
				info.read_counter = aux;
				debug(stderr, "Current read counter: %d\n", info.read_counter);
				break;

			case ID_GAP_TIME_COUNT:

				if(aux < MINIMUM_GAP_TIME_COUNT || aux > MAXIMUM_GAP_TIME_COUNT) {
					debug(log_error, "Invalid gap time: %s\n", &variable[1]);
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);
					continue;
				}
				info.gap_us = aux;
				debug(stderr, "Current gap time: %d\n", info.gap_us);
				break;

			default:

				debug(log_error, "Invalid variables types\n");
				debug(stderr, "Sending error message to IOC\n");
				send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);
				continue;
		}

		debug(stderr, "Sending SUCCESS message to IOC...\n");
		send_or_panic(args->remote_socket, SUCCESS, sizeof(SUCCESS)-1);

	} while (true);
}

int create_udp_socket(void)
{
	int s_udp;

	debug(stderr, "Creating UDP socket...\n");
	if ((s_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		debug(log_error, "Socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s_udp;
}

void set_socket_timeout(int socket, unsigned timeout_us)
{
	struct timeval timeout;

	timeout.tv_sec = timeout_us / MICRO_PER_SECOND;
	timeout.tv_usec = timeout_us % MICRO_PER_SECOND;

	if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) < 0) {
		debug(log_error, "Set sock opt (SO_RCVTIMEO) Failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	debug(stderr,"The medipix has %ld seconds to send the bytes!\n", timeout.tv_sec + timeout.tv_usec);

}

void binding_udp_socket(int s_udp, uint16_t port)
{
	int enable = 1;
	socklen_t namelen;

	struct sockaddr_in medipix;

	medipix.sin_family      = AF_INET;
	medipix.sin_port        = htons(port);
	medipix.sin_addr.s_addr = INADDR_ANY;

	if (setsockopt(s_udp, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		debug(log_error, "Set sock opt (SO_REUSEADDR) Failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	debug(stderr, "Binding UDP...\n");
	if (bind(s_udp, (struct sockaddr *)&medipix, sizeof(medipix)) < 0) {
		debug(log_error, "Bind: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	namelen = sizeof(medipix);
	if (getsockname(s_udp, (struct sockaddr *)&medipix, &namelen) < 0) {
		debug(log_error, "Get sock name: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	debug(stderr, "The port to receive the image bytes is %d\n", ntohs(medipix.sin_port));
}
