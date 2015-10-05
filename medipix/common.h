/* Common Headers */
/* Medipix Server - Developed by Diego Dorta */
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
#define ID_ACQUIRE 		'D'
#define DEBUG_MESSAGE		"This log is only for debbuging in case something stop working.\n\n"
#define SENTINEL		-1
#define MINIMUM_IMAGE_COUNT	1
#define MAXIMUM_IMAGE_COUNT	100
#define MINIMUM_BIT_COUNT	0
#define MAXIMUM_BIT_COUNT	3
#define NUMBER_OF_BROTHERS	2
#define WIDTH			256
#define HEIGHT			256
#define MAXIMUM_NUMBER_OF_BYTES 3
#define IMAGE_BUFFER_SIZE	(WIDTH*HEIGHT*MAXIMUM_NUMBER_OF_BYTES)

extern FILE *log_error;

/* Struct destinada a comunicação entre os processos filhos (Um filho se comunica com o IOC e outro filho com o medipix). */
struct acquisition_info {
	int number_bits;
	int number_frames;
	char filename[FILENAME_SIZE];
};

struct process_arguments {
	int brother_socket;
	int remote_socket;
};

struct medipix_header {
	char sync_1;
	char sync_2;
	char sync_3;
	char sync_4;
};

typedef void (*start_routine_t)(struct process_arguments *);

void binding_udp_socket(int s_udp, uint16_t port);
int create_tcp_socket(void);
int accept_new_connection(int s);
int create_udp_socket(void);
void receive_variables(struct process_arguments *args);
void receive_bytes_from_medipix(int s_udp, struct acquisition_info  *fl);
void communication_medipix(struct process_arguments *args) __attribute__ ((noreturn));
pid_t create_process(start_routine_t start_routine, struct process_arguments *args);
void create_socketpair(int *sv);
void send_or_panic(int socket, const void *text, size_t length);

#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
void debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
void debug(FILE *output, const char *format, ...);
#endif

#endif /* _COMMON_H_DEFINED_ */
