#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <stdio.h>
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

#define PATH			"database.txt"
#define CLEAR			"\e[H\e[2J"
#define RED			"\e[31m"
#define BLUE			"\e[34m"
#define GREEN			"\e[32m"
#define NORMAL			"\e[0m"
#define OPEN_UNDERSCORE		"\e[4m"
#define OPEN_BLINK		"\e[5m"
#define OPEN_REVERSE		"\e[7m"
#define BUFFER_SIZE 		500
#define LOG_ERROR 		"log.txt"
#define DEBUG_MESSAGE		"E-Pag - This log is only for debbuging in case something stops working.\n\n"
#define WEB_TCP_PORT		4000
#define APP_TCP_PORT		5000
#define OPR_TCP_PORT		3000
#define NUMBER_WEB_CONNECTIONS	1
#define SUCCESS 		"e-Pag message: recebido com sucesso!\n"
#define FAILURE 		"e-Pag message: não foi recebido!\n"
#define USER_EXISTS		"Usuário encontrado no banco de dados!\n"
#define USER_NO_EXISTS		"Usuário não encontrado no banco de dados!\n"
#define TOKEN_SIZE		32
#define ID_USER_EXISTS		1		
#define ID_USER_NO_EXISTS	2
#define SIZE_NAME		40
#define SIZE_CPF		14
#define STRINGIFY(s) 		STRINGIFY1(s)
#define STRINGIFY1(s) 		#s


extern FILE *log_error;

struct process_arguments {
	int arg;
};

/* network.c */
int create_tcp_socket(uint16_t port);
int accept_new_connection_from_web(int s);

/* utils.c */
void start_log_file(void);
void send_or_panic(int socket, const void *text, size_t length);
int get_size(const char *file_name);

/* financial.c */
void *start_communication_opr(void *args);

/* web.c */
void *start_communication_web(void *args);
void communication_web(void);
bool receive_data_from_web(int web_socket);

/* app.c */
void *start_communication_app(void *args);

/* thread.c */
void check_creation_thread(int id);
void destroy_thread(pthread_t id);

/* database.c */
int verify_cpf_on_database(char *token);

#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
void debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
void debug(FILE *output, const char *format, ...);
#endif

#endif /* _LIBRARY_H_DEFINED_ */
