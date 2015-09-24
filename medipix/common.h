#ifndef _COMMON_H_
#define _COMMON_H_

#define SUCCESS 		"ok\n"
#define FAILURE 		"error\n"
#define VARIABLE_SIZE 		40
#define FILENAME_SIZE 		40
#define BUFFER_SIZE 		500
#define SIZE_PACKET 		1028
#define DEFAULT_FILE_NAME 	"sol"
#define LOG_ERROR 		"log.txt"
#define PORT_TO_RECEIVE_BYTES	4000
#define PORT_FOR_INFO  		5000
#define ID_FILENAME 		'A'
#define ID_FRAMES 		'B'
#define ID_BITS 		'C'
#define DEBUG_MESSAGE		"This log is only for debbuging in case something stop working.\n\n"

#include <stdbool.h>

extern FILE *log_error;

struct data {
	int n_socket;
	int number_bits;
	int number_frames;
	char filename[FILENAME_SIZE];
	bool ret;
};

struct sockaddr_in binding_udp_socket(int s_udp, uint16_t port);
int create_tcp_socket(void);
int accept_new_connection(int s);
int create_udp_socket(void);
void receive_variables(struct data *fl);
void receive_bytes_from_medipix(int s_udp, struct sockaddr_in medipix, struct data *fl, int counter);
void check_thread(int t);
void communication_medipix(struct data *fl) __attribute__ ((noreturn));

#ifdef __GNUC__
int debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
int debug(FILE *output, const char *format, ...);
#endif

#endif /* _COMMON_H_DEFINED_ */
