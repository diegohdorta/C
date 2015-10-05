/* Images functions */
/* Medipix Server - Developed by Diego Dorta */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "common.h"

void receive_bytes_from_medipix(int s_udp, struct acquisition_info *fl)
{

	char image[IMAGE_BUFFER_SIZE];
	
	struct medipix_header header;


// 	ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);



}


