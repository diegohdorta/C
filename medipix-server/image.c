/* Images functions */
/* Medipix Server - Developed by Diego Dorta */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#include "common.h"

static void swap (void *a, void *b, size_t s)
{
	char buff[s];

	memmove(buff, a, s);
	memmove(a, b, s);
	memmove(b, buff, s);
}

void receive_bytes_from_medipix(int s_udp, struct acquisition_info *info)
{
	int i;
	int j;
	int aux;
	static char image[IMAGE_BUFFER_SIZE * MAXIMUM_IMAGE_COUNT];

	static struct medipix_header header[MAXIMUM_PACKET_COUNT];

	struct iovec iovec[NUMBER_OF_IO_ELEMENTS] = {
		{ .iov_base = &header,	.iov_len = sizeof(struct medipix_header) },
		{ .iov_base = &image,	.iov_len = SIZE_IMAGE_DATA }
	};

	struct msghdr msg = {
		.msg_name = NULL,
		.msg_namelen = 0,
		.msg_iov = iovec,
		.msg_iovlen = NUMBER_OF_IO_ELEMENTS,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = 0,
	};

	debug(stderr, "Waiting for medipix sending the image bytes...\n");

	aux = info->number_frames * NUMBER_OF_READINGS[info->read_counter];

	set_socket_timeout(s_udp, info->gap_us + MEDIPIX_TIMEOUT * MICRO_PER_SECOND);

	for(j = 0; j < aux; j++) {

		for(i = 0; i < NUMBER_OF_PACKETS[info->number_bits]; i++ ) {

			if(recvmsg(s_udp, &msg, 0) < 0) {
				debug(stderr, "Received %d packets.\n", i);

				if(errno == EAGAIN) {
					debug(log_error, "Timeout waiting for medipix!\n");
					debug(stderr, "Timeout waiting for medipix!\n");
					return;
				}

				debug(log_error, "Recvmsg: %s\n", strerror(errno));
			        exit(EXIT_FAILURE);
			}

			iovec[0].iov_base += sizeof(struct medipix_header);
			iovec[1].iov_base += SIZE_IMAGE_DATA;
		}

		debug(stderr, "Received %d packets.\n", i);
	} /* for j */

	/* Ordering packets - Insertion sort is used because most of the time the array
	   is already ordered, so the running time is Ω(n) */
	header[0].packet_number = ntohs(header[0].packet_number);
	for (i = 1; i < aux*NUMBER_OF_PACKETS[info->number_bits]; i++) {
		j = i;
		header[i].packet_number = ntohs(header[i].packet_number);
		while (j > 0 && header[j-1].packet_number > header[j].packet_number) {
			swap(&image[j*SIZE_IMAGE_DATA], &image[(j-1)*SIZE_IMAGE_DATA],
				SIZE_IMAGE_DATA);
			swap(&header[j], &header[j-1], sizeof(struct medipix_header));
			j--;
		}
	}

	debug(stderr, "Saving file...\n");

	if (save_images(image, header, info))
		debug(stderr, "Image done!\n");
	else {
		debug(log_error, "Unable to write output file!\n");
		debug(stderr, "Unable to write output file!\n");
		exit(EXIT_FAILURE);
	}
}
