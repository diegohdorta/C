#define _XOPEN_SOURCE 700

#include "library.h"

void communication_devices(int my_queue, int *queue_list, void *data)
{
	/* Essa função será responsável por aceitar infinitas conexões dos celulares.
	   Para cada nova conexão serão criadas novas threads, e cada thread envia o
	   IP e o CPF para a fila de mensagens do app.c como tipo DEVICE. 
	   Enquanto a quantidade de threads for da ordem de milhares um PC normal aguenta,
	   quando passar a ter milhões de threads será necessário usar co-routinas. */
	int i = QUEUE_CHILDREN_THREADS;
	int j;
	int sock_device;
	int new_device_socket[MAXIMUM_THREADS];
	

	pthread_t devices[MAXIMUM_THREADS];
	
	sock_device = create_tcp_socket(DEVICES_TCP_PORT);
	
	do {
		new_device_socket[i] = accept_new_device_connection(sock_device);
		
		create_thread(&devices[i], i, receive_data_and_put_on_queue, queue_list, &new_device_socket[i]);
		i++;
		/* Tratar destruição das threads e organização dos IDs */
		
	} while (i < MAXIMUM_THREADS);	
	
	for (j = 0; j < i; j++)
		destroy_thread(devices[j]);
}


void receive_data_and_put_on_queue(int my_queue, int *queue_list, void *data)
{
	int *socket_ptr = data;
	int socket = *socket_ptr;
	bool ret;
	char cpf[SIZE_CPF];
	
	message_t client;
	
	do {
		
		ret = receive_data_from_device(socket, cpf);
		
		if(ret == true)
			break;

		client.type = MESSAGE_DEVICE;
		
		client.connected_client.socket = socket;
		strcpy(client.connected_client.cpf, cpf);


		send_queue_message(queue_list[QUEUE_APP], &client);

	
		/* Ler da minha fila agora e reagir de acordo com a mensagem que estiver na fila */
	
	
	} while(true);
	
	
	//return NULL;
}

bool receive_data_from_device(int socket, char *cpf)
{


	
	send_or_panic(socket, "Envia seu cpf\n", 20);

	return false;

}













