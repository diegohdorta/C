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

#define PATH			"database.txt"
#define BUFFER_SIZE 		500
#define LOG_ERROR 		"log.txt"
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

#define MESSAGE_PAYLOAD_SIZE (sizeof(message_t)-sizeof(message_type))

extern FILE *log_error;

struct process_arguments {
	int arg;
};

typedef enum message_type message_type;

enum message_type {
	/* Force message_type to be a long integer to be compatible with System V message queue API. */
	MESSAGE_PAYMENT = LONG_MAX,
	MESSAGE_DEVICE = 1,
	MESSAGE_FORWARD_PAYMENT
};

typedef struct payment_t payment_t;

struct payment_t {
	char cpf[SIZE_CPF];
	uint64_t value_cents;
};

typedef struct forward_payment_t forward_payment_t;

struct forward_payment_t {
	uint64_t value_cents;
};

typedef struct connected_client_t connected_client_t;

struct connected_client_t {
	char cpf[SIZE_CPF];
	int device_queue;
};

typedef struct message_t message_t;

struct message_t {
	message_type type;
	union {
		payment_t payment;
		connected_client_t connected_client;
		forward_payment_t forward_payment;
	};
};

typedef enum queue_type queue_type;

enum queue_type {
	QUEUE_APP = 0,
	QUEUE_DEVICES,
	QUEUE_WEB,
	QUEUE_CHILDREN_THREADS
};

typedef struct thread_t thread_t;

struct thread_t {
	void (*thread_fn)(int, int *, void *);
	int *queue_list;
	int my_queue;
	void *data;
};

/* network.c */
int create_tcp_socket(uint16_t port);
int accept_new_connection_from_web(int s);
int accept_new_device_connection(int s);

/* utils.c */
void start_log_file(void);
void send_or_panic(int socket, const void *text, size_t length);
int get_size(const char *file_name);

/* web.c */
void communication_web(int my_queue, int *queue_list, void *data);
bool receive_data_from_web(int web_socket, int *queue_list);
void put_payment_on_message_queue(char *cpf, uint64_t value_cents, int *queue_list);

/* app.c */
void communication_app(int my_queue, int *queue_list, void *data);
void look_for_mobile_to_send_payment(const message_t *info, const char *cpf_list[], int socket_list[]);

/* thread.c */
void create_thread(pthread_t *thread, void (*function)(int, int *, void *), int queue_index, int *queue_list, void *data);
void check_creation_thread(int id);
void destroy_thread(pthread_t id);

/* database.c */
int verify_cpf_on_database(char *token_cpf, char *name, char *cpf, char *phone);

/* devices.c */
void communication_devices(int my_queue, int *queue_list, void *data);
void receive_data_and_put_on_queue(int my_queue, int *queue_list, void *data);
bool receive_data_from_device(int socket, char *cpf);

/* queue.c */
int create_message_queue(void);
void destroy_queue(int queue_id);
void send_queue_message(int queue_id, const message_t *message);
void receive_queue_message(int queue_id, message_t *info);

#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
void debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
void debug(FILE *output, const char *format, ...);
#endif

#endif /* _LIBRARY_H_DEFINED_ */
