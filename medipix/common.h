/* Common Headers */
/* Medipix Server - Developed by Diego Dorta */
#ifndef _COMMON_H_
#define _COMMON_H_

#define SUCCESS 		"ok\n"
#define FAILURE 		"error\n"
#define VARIABLE_SIZE 		40
#define FILENAME_SIZE 		40
#define BUFFER_SIZE 		500
#define SIZE_HEADER		4
#define SIZE_IMAGE_DATA		1024
#define SIZE_PACKET 		(SIZE_IMAGE_DATA+SIZE_HEADER)
#define DEFAULT_FILE_NAME 	"sol"
#define LOG_ERROR 		"log.txt"
#define PORT_TO_RECEIVE_BYTES	3000
#define PORT_FOR_INFO  		4000
#define ID_FILENAME 		'A'
#define ID_FRAMES 		'B'
#define ID_BITS 		'C'
#define ID_ACQUIRE 		'D'
#define ID_READING_COUNT	'E'
#define ID_GAP_TIME_COUNT	'F'
#define DEBUG_MESSAGE		"This log is only for debbuging in case something stops working.\n\n"
#define SENTINEL		-1
#define MINIMUM_IMAGE_COUNT	1
#define MAXIMUM_IMAGE_COUNT	100
#define MINIMUM_BIT_COUNT	0
#define MAXIMUM_BIT_COUNT	3
#define MINIMUM_READING_COUNT	0
#define MAXIMUM_READING_COUNT	2
#define MINIMUM_GAP_TIME_COUNT	1*MICRO_PER_SECOND
#define MAXIMUM_GAP_TIME_COUNT	10*MICRO_PER_SECOND
#define NUMBER_OF_BROTHERS	2
#define WIDTH			256
#define HEIGHT			256
#define MAXIMUM_NUMBER_OF_BYTES 3
#define IMAGE_BUFFER_SIZE	(WIDTH*HEIGHT*MAXIMUM_NUMBER_OF_BYTES)
#define MAXIMUM_PACKET_COUNT	(IMAGE_BUFFER_SIZE*MAXIMUM_IMAGE_COUNT/SIZE_IMAGE_DATA)
#define NUMBER_OF_IO_ELEMENTS	2
#define MEDIPIX_TIMEOUT		5
#define MICRO_PER_SECOND	1000000

extern FILE *log_error;

struct acquisition_info {
	int number_bits;
	int number_frames;
	int read_counter;
	int gap_us;
	char filename[FILENAME_SIZE];
};

/* Struct destinada a comunicação entre os processos filhos 
 (Um filho se comunica com o IOC e outro filho com o medipix). */
struct process_arguments {
	int brother_socket;
	int remote_socket;
};

struct medipix_header {
	char sync_1;
	char sync_2;
	char sync_3;
	char packet_number;
};

typedef void (*start_routine_t)(struct process_arguments *);

void binding_udp_socket(int s_udp, uint16_t port);
int create_tcp_socket(void);
int accept_new_connection(int s);
int create_udp_socket(void);
void receive_variables(struct process_arguments *args);
void receive_bytes_from_medipix(int s_udp, struct acquisition_info  *info);
void communication_medipix(struct process_arguments *args) __attribute__ ((noreturn));
pid_t create_process(start_routine_t start_routine, struct process_arguments *args);
void create_socketpair(int *sv);
void send_or_panic(int socket, const void *text, size_t length);
void set_socket_timeout(int socket, unsigned timeout_us);

#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
void debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
void debug(FILE *output, const char *format, ...);
#endif

#endif /* _COMMON_H_DEFINED_ */
