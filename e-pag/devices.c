#define _XOPEN_SOURCE 700

#include "library.h"

#define MAXIMUM_DEVICES 	100
#define INITIAL_VALUE		0
#define SERVER_BUSY		"Servidor está cheio!\n"
#define MESSAGE_LENGHT		4096

int list_length = 0;
int *sock_devices_list;
int sock_device;
int new_socket;

char message[MESSAGE_LENGHT + 1];

void *start_communication_devices(void *args)
{
	debug(stderr, "Função que se comunica com os dispositivos inicializada!\n");
	communication_devices();
	return NULL;
}

void communication_devices(void)
{
	/* Essa função será responsável por aceitar infinitas conexões dos celulares
	   e salvar todos os IP e também o CPF do usuário, para que possa ser feita
	   a comparação e então enviar a solicitação de pagamento correta para o usuário. 
	   
	   Quero dar um jeito dessa thread abrir em outro terminal e ficar atualizando
	   todos os celulares que estiverem online... exec(gnome-terminal) ?!
	   Mostrando: 
	   1 IP:PORTA + CPF
	   2 IP:PORTA + CPF
	   3 IP:PORTA + CPF
	   N IP:PORTA + CPF
	   */
	
	int x;

	struct timeval select_time;
	
	fd_set select_set;

	sock_device = create_tcp_socket(APP_TCP_PORT);

	sock_devices_list = (int *) malloc(MAXIMUM_DEVICES * sizeof(int));

	if (sock_devices_list == NULL) {
		debug(stderr, "Error trying to allocated memory: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for (x = 0; x < MAXIMUM_DEVICES; x++ )
		sock_devices_list[x] = INITIAL_VALUE;

	while (true) {

		FD_ZERO(&select_set);
		
		FD_SET(sock_device, &select_set) ;
		
		for (x = 0; list_length > 0 && x < MAXIMUM_DEVICES; x++) {
			if (sock_devices_list[x] != 0)
				FD_SET(sock_devices_list[x], &select_set);
		}

		debug(stderr, "[+] Listening devices on %d [%d/%d] ...\n", APP_TCP_PORT, list_length, MAXIMUM_DEVICES) ;

		select_time.tv_sec = 1;
		select_time.tv_usec = 0;

		if ((x = select(FD_SETSIZE, &select_set, NULL, NULL, &select_time)) < 0 ) {
			debug(stderr, "Error trying to select: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (x > 0) {

			if (FD_ISSET(sock_device, &select_set)) {

				if ((new_socket = accept(sock_device, NULL, NULL)) < 0 )
					debug(stderr, "Error trying to accept new connetion: %s\n", strerror(errno));
				
				else if (insert_socket_into_list(new_socket) == 1) {
					debug(stderr, "Servidor está cheio!\n");
					send_or_panic(new_socket, SERVER_BUSY, sizeof(SERVER_BUSY)-1);
					close(new_socket);
				}
				continue;
			} 
			else {
				for (x = 0; x < MAXIMUM_DEVICES; x++) {
					if (FD_ISSET(sock_devices_list[x], &select_set)) {
						if (get_message_from_socket(sock_devices_list[x]) == 0)
							send_message_to_all(sock_devices_list[x]);
					}
				}
			}
		}
	} /* while */
}

int insert_socket_into_list(int socket) 
{
	int i ;

	if (list_length == MAXIMUM_DEVICES)
	return 1 ;

	for (i = 0; i < MAXIMUM_DEVICES; i++) {
		if (sock_devices_list[i] == 0) {
			sock_devices_list[i] = socket;
			list_length++;
			break ;
		}
	}
	return 0;
}

int get_message_from_socket(int _sock) 
{
	int t;

	memset(message, 0x0, MESSAGE_LENGHT + 1) ;
	t = recv(_sock, message, MESSAGE_LENGHT, 0) ;

	if (t == 0) {
		remove_socket_from_list(_sock);
		return 1;
	}
	return 0 ;
}

void remove_socket_from_list(int _sock) 
{
	int i ;

	for (i = 0; i < MAXIMUM_DEVICES; i++) {
		if (sock_devices_list[i] == _sock) {
			close(sock_devices_list[i]);
			sock_devices_list[i] = 0;
			list_length--;
			break ;
		}
	}
}

void send_message_to_all(int _sock) 
{
	int i;

	for (i = 0; i < MAXIMUM_DEVICES; i++) {
		if ( (sock_devices_list[i] != 0) && (sock_devices_list[i] != _sock) && (sock_devices_list[i] != sock_device))
			send_or_panic(sock_devices_list[i], message, MESSAGE_LENGHT-1);
	}
}



