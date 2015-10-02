/* Images functions */
/* Medipix Server - Developed by Diego Dorta */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "common.h"

void receive_bytes_from_medipix(int s_udp, struct sockaddr_in medipix, struct acquisition_info *fl)
{
	int counter_bytes;
	int i;
	int j;
	int increase = 0;
	int flip_image [256][256];
	int counter = 0;

	char image_one [65536];
	char image_two [65536];
	const char *extension = ".ppm";        
        char file_name_image[strlen(fl->filename) + strlen(extension) + 10];

	typedef int buffer[257];
	buffer buffer_one_bit[64];	
	FILE *fp;
	socklen_t namelen;
	
	debug(stderr, "Waiting for medipix sending the bytes image...\n");

	namelen = sizeof(medipix);

	// for(conta_img=1;conta_img<=nimagens;conta_img++)

	for (counter_bytes = 0; counter_bytes <= 63; counter_bytes++) {

		if (recvfrom(s_udp, &buffer_one_bit[counter_bytes], SIZE_PACKET, 0, 
						(struct sockaddr *)&medipix, &namelen) < 0) {
			perror("recvfrom()");
			exit(EXIT_FAILURE);
		}
	}
	//printf("Received data from medipix, closing socket...\n");
	//close(s_udp);

	debug(stderr, "Treatment of the received data...\n");

	memmove(image_two, buffer_one_bit, 257*64*sizeof(int));

	for (i = 0; i < 64; i++) {
		for (j = 0; j < 257; j++) {
			if (j > 0) {
				image_one[increase + 0] = (buffer_one_bit[i][j] & 0x000000FF) >> 0;
				if (image_one[increase] != 0)
					printf("image_one0 = %hhx, buffer_one_bit = %x\n", image_one[increase], buffer_one_bit[i][j]);
				image_one[increase + 1] = (buffer_one_bit[i][j] & 0x0000FF00) >> 8;
				if (image_one[increase+1] != 0)
					printf("image_one1 = %hhx, buffer_one_bit = %x\n", image_one[increase+1], buffer_one_bit[i][j]);
				image_one[increase + 2] = (buffer_one_bit[i][j] & 0x00FF0000) >> 16;
				if (image_one[increase+2] != 0)
					printf("image_one2 = %hhx, buffer_one_bit = %x\n", image_one[increase+2], buffer_one_bit[i][j]);
				image_one[increase + 3] = (buffer_one_bit[i][j] & 0xFF000000) >> 24;
				if (image_one[increase+3] != 0)
					printf("image_one3 = %hhx, buffer_one_bit = %x\n", image_one[increase+3], buffer_one_bit[i][j]);
				increase = increase + 4;
			}
		}
	}
	debug(stderr, "MEMCMP TESTE\n");
	printf("%d\n", memcmp(image_two, image_one, 65536));

	fprintf(stderr, "Flipping image...\n");
	increase = 65535;
	for (i = 0; i <= 255; i++) {
		for (j = 0; j <= 255; j++) {
			flip_image[i][j]=image_one[increase];
			increase--;
		}
	}

	debug(stderr, "Creating file...\n");
	
	snprintf(file_name_image, sizeof(file_name_image), "%s_%d%s", fl->filename, counter, extension);

	fprintf(stderr, "Nome: %s\nContador: %d\n", file_name_image, counter);
	fp = fopen(file_name_image, "w+");
	
    	if (fp == NULL) {    
    	   	 perror("fopen()");
		 exit(EXIT_FAILURE);
    	}

	fprintf(fp, "P1\n");
    	fprintf(fp, "256 256\n");

	for (i = 0; i <= 255; i++) {
		for (j = 0; j <= 255; j++) {
			fprintf(fp, "%x ", flip_image[i][j]);
			if (j == 255)
				fprintf(fp,"\n");
		}
    	}
    	debug(stderr, "File created with SUCCESS...\n");

	sleep(1);
}


