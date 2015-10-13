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

void receive_bytes_from_medipix(int s_udp, struct acquisition_info *info)
{
	int i;
	int j;
	int aux;
	const int number_of_packets[] = {8, 96, 48, 96}; 
	const int number_of_readings[] = {1, 1, 2};
	static char image[IMAGE_BUFFER_SIZE*MAXIMUM_IMAGE_COUNT];
	
	FILE *output;	
	struct medipix_header header;
	
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
	
	aux = info->number_frames*number_of_readings[info->read_counter];
	
	for(j = 0; j < aux; j++) {
	
		for(i = 0; i < number_of_packets[info->number_bits]; i++ ) {	
	
			if(recvmsg(s_udp, &msg, 0) < 0) {
			
				if(errno == EAGAIN) {
					debug(log_error, "Timeout waiting for medipix!\n");
					debug(stderr, "Timeout waiting for medipix!\n");
					return;
				}				
			
				debug(log_error, "Recvmsg: %s\n", strerror(errno));
			        exit(EXIT_FAILURE);
			}
			iovec[1].iov_base = iovec[1].iov_base + SIZE_IMAGE_DATA;
			printf("aaaaaaaaaaaa\n");
		}
	}
	
	debug(stderr, "Saving file...\n");
	output = fopen(info->filename, "w");
        
        if (output == NULL) {    
        	debug(log_error, "Fopen(): %s\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
	
	fwrite(info, sizeof(struct acquisition_info), 1, output);
	fwrite(image, SIZE_IMAGE_DATA, number_of_packets[info->number_bits]*aux, output);
	fclose(output);
	printf("DONE!!!!!!!!!!!!!!\n");
}
