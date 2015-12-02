#define _XOPEN_SOURCE 700

#include "library.h"

#define MAXIMUM_DEVICES_THREADS 	100

void *start_communication_devices(void *args)
{
	debug(stderr, "Função que se comunica com os dispositivos inicializada!\n");
	communication_devices();
	return NULL;
}

void communication_devices(void)
{
	/* Essa função será responsável por aceitar infinitas conexões dos celulares.
	   Para cada nova conexão serão criadas novas threads, e cada thread envia o
	   IP e o CPF para a fila de mensagens do app.c como tipo DEVICE. 
	   Enquanto a quantidade de threads for da ordem de milhares um PC normal aguenta,
	   quando passar a ter milhões de threads será necessário usar co-routinas. */
	int i = 0;
	int j;
	int sock_device;
	int new_device_socket;
	int device_list[MAXIMUM_DEVICES_THREADS];
	
	pthread_t devices[MAXIMUM_DEVICES_THREADS];
	
	sock_device = create_tcp_socket(DEVICES_TCP_PORT);
	
	
	do {
		new_device_socket = accept_new_device_connection(sock_device);
		

		/* Construir uma estrutura para armazenar os dados do socket?! */
		
		device_list[i] = create_thread(device_list[i], FUNÇÃO, ARGUMENTOS, new_device_socket);
		i++;
		

		
	} while (true);	
	
	for (j = 0; j < i; j++)
		destroy_thread(devices[j]);

}

int create_thread(int thread_id, FUNÇÃO, ARGUMENTOS)
{
	int ret;

	ret = pthread_create(&thread_id, NULL, FUNÇÃO, ARGUMENTOS);	
	check_creation_thread(ret);
	
	return ret;
}


void FUNÇÃO()
{
	int ret;
	int queue_id_app;	
	char cpf[SIZE_CPF];	
		
	message_t phone;
	
	do {
		
		ret = receive_data_from_device(new_socket_from_web, cpf);
		
		if(ret == true)
			break;
	
		queue_id_app = create_message_queue();
		
		phone.type = MESSAGE_DEVICE;
		
		phone.device.address = mobile.sin_addr.s_addr;
		strcpy(phone.device.cpf, cpf);


		send_queue_message(queue_id_app, &phone);

	
	} while(true);
	
	


}















