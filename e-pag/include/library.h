#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <limits.h>
#include <sys/times.h>
#include <sys/select.h>

#define PATH			"data/database.txt"
#define BUFFER_SIZE 		500
#define BUFFER	 		100
#define LOG_ERROR 		"log/log.txt"
#define DEBUG_MESSAGE		"E-Pag - This log is only for debbuging in case something stops working.\n\n"
#define WEB_TCP_PORT		4000
#define APP_TCP_PORT		6000
#define DEVICES_TCP_PORT	5000
#define OPR_TCP_PORT		3000
#define NUMBER_WEB_CONNECTIONS	10
#define SUCCESS 		"e-Pag message: Recebido com sucesso!\n"
#define FAILURE 		"e-Pag message: Não foi recebido!\n"
#define FAILURE_MESSAGE		"e-Pag message: Mensagem muito grande!\n"
#define USER_EXISTS		2
#define MESSAGE_USER_EXISTS	"e-Pag message: Usuário encontrado no banco de dados!\n"
#define USER_NO_EXISTS		3
#define MESSAGE_USER_NO_EXISTS	"e-Pag message: Usuário NÃO encontrado no banco de dados!\n"
#define INVALID_COMMAND		4
#define MESSAGE_INVALID_COMMAND	"e-Pag message: Mensagem inválida!\n"
#define MESSAGE_DEVICE_CPF	"e-Pag message: Envie seu CPF para associar com seu IP!\n"
#define TOKEN_SIZE		32
#define MAXIMUM_MESSAGE_SIZE	100
#define ID_USER_EXISTS		2		
#define ID_USER_NO_EXISTS	3
#define ID_INVALID_COMMAND	4
#define SIZE_NAME		40
#define SIZE_CPF		15
#define SIZE_PHONE		15
#define SIZE_IP			16
#define SIZE_PORT		6
/* These duplicate constants work around STRINGIFY limitations */
#define SIZE_NAME_MINUS_ONE	39
#define SIZE_CPF_MINUS_ONE	14
#define SIZE_PHONE_MINUS_ONE	14
#define SIZE_IP_MINUS_ONE	15
#define SIZE_PORT_MINUS_ONE	5
#define SIZE_MESSAGE		150
#define STRINGIFY(s) 		STRINGIFY1(s)
#define STRINGIFY1(s) 		#s
/* Constants for queue messages */
#define MESSAGE_QUEUE_ID	3000
#define MESSAGE_MTYPE		1
#define QUEUE_PERMISSION	0666
#define SIZE_VALUE		10
#define MAXIMUM_THREADS		10000
#define NUMBER_OF_BROTHERS	2
#define SENTINEL		-1
#define COMM_APP		"COMMAPP"
#define COMM_THREAD		"COMMTHREAD"
#define ID_DEVICE               0
#define ID_WEB                  1

#define MESSAGE_PAYLOAD_SIZE (sizeof(message_t)-sizeof(message_type))

extern FILE *log_error;

struct process_arguments {
	int args;
};

typedef enum message_type message_type;

enum message_type {
	/* Force message_type to be a long integer to be compatible with System V message queue API. */
	MESSAGE_PAYMENT = LONG_MAX,
	MESSAGE_DEVICE = 1,
	MESSAGE_FORWARD_PAYMENT,
	MESSAGE_SOCKET_RECEIVE,
};

typedef struct payment_t payment_t;

struct payment_t {
	char cpf[SIZE_CPF];   /*!< Variável para armazenar CPF */
	uint64_t value_cents; /*!< Variável para armazenar valor a ser cobrado */
};

typedef struct forward_payment_t forward_payment_t;

struct forward_payment_t {
	uint64_t value_cents; /*!< Variável para armazenar valor a ser cobrado */
};

typedef struct connected_client_t connected_client_t;

struct connected_client_t {
	char cpf[SIZE_CPF]; /*!< Variável para armazenar CPF do cliente conectado */
	int device_queue;   /*!< Variável para armazenar fila do cliente conectado */
};

typedef struct received_data_t received_data_t;

struct received_data_t {
	ssize_t size;
	char buffer[BUFFER_SIZE];
	int error;
};

typedef struct message_t message_t;

struct message_t {
	message_type type; /*!< Variável para definir o tipo de mensagem que será transmitida na fila. */
	union {
		payment_t payment;
		connected_client_t connected_client;
		forward_payment_t forward_payment;
		received_data_t received_data;
	};
};

typedef enum queue_type queue_type;

enum queue_type {
	QUEUE_APP = 0,
	QUEUE_COMMUNICATION_THREAD,
	QUEUE_OTHER_THREADS,
};

typedef struct thread_t thread_t;

struct thread_t {
	void (*thread_fn)(int, int *, void *);  /*!< Usado para definir quais parâmetros serão aceitos na função */
	int *queue_list;			/*!< Variável para armazenar os IDs das filas */
	int my_queue;				/*!< Variável para armazenar fila do processo */
	void *data;				/*!< Variável para armazenar qualquer dado extra */
	const char *name;
};
/* helper.c */
void communication_thread(int my_queue, int *queue_list, void *data);
 
/* network.c */
int create_tcp_socket(uint16_t port);
int accept_new_connection_from_web(int s);
int accept_new_device_connection(int s);

/* utils.c */
void start_log_file(void);
void send_or_panic(int socket, const void *text, size_t length);
int get_size(const char *file_name);
void create_socketpair(int *sv);

/* web.c */
void receive_data_and_send(int my_queue, int *queue_list, void *data);
void put_payment_on_message_queue(char *cpf, uint64_t value_cents, int *queue_list);

/* app.c */
void communication_app(int my_queue, int *queue_list, void *data);

/* thread.c */
void create_thread(pthread_t *thread, const char *name, void (*function)(int, int *, void *), int queue_index, int *queue_list, void *data);
void check_creation_thread(int id);
void destroy_thread(pthread_t id);

/* database.c */
int verify_cpf_on_database(char *token_cpf, char *name, char *cpf, char *phone);

/* devices.c */
void receive_data_and_put_on_queue(int my_queue, int *queue_list, void *data);

/* queue.c */
int create_message_queue(void);
void destroy_queue(int queue_id);
void send_queue_message(int queue_id, const message_t *message);
void receive_queue_message(int queue_id, message_t *info);

/* helper.c */
void helper_devices(int my_queue, int *queue_list, void *data);

#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
void debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
void debug(FILE *output, const char *format, ...);
#endif

#endif /* _LIBRARY_H_DEFINED_ */
