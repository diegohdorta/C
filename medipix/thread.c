#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "common.h"

void communication_medipix(struct data *fl)
{
	uint16_t port = PORT_TO_RECEIVE_BYTES;
	int socket_udp;
	int image_counter;
	struct sockaddr_in med;

	image_counter = 0;
	socket_udp = create_udp_socket();
	med = binding_udp_socket(socket_udp, port);

	do {	/* Entender melhor onde colocar a criação do socket e o bind */
		/* Criar um switch com as opções
		 *
		 *  switch:
		 *	case 1 "quantidade de bits && nº de frames":
		 *		chama função para executar algoritmo de 1 bit
		 *		receive_bytes_and_build_images_one_bit(socket_udp, med, fl, image_counter);
		 *		break;
		 *	case 2: 
		 *		chama função para executar algoritmo de 6 bit
		 *		receive_bytes_and_build_images_six_bit(NUMERO_IMAGENS,socket_udp, med, fl, image_counter);
		 *		break;
		 *	case 3: 
		 *		chama função para executar algoritmo de 12 bit
		 *		receive_bytes_and_build_images_twelve_bit(socket_udp, med, fl, image_counter);
		 *		break;
		 *	case 4: 
		 *		chama função para executar algoritmo de 24 bit
		 *		receive_bytes_and_build_images_twenty-four_bit(socket_udp, med, fl, image_counter);
		 *		break;
		 *
		 */
	
		receive_bytes_from_medipix(socket_udp, med, fl, image_counter);
		image_counter++;
		
	} while(true);
}
