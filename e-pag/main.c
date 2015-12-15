#define _XOPEN_SOURCE 700

#include "library.h"

/* comments: doc.txt -> main.c -> 1# */

int main(void)
{
	int queue_list[MAXIMUM_THREADS]; 
	
	pthread_t app_listener;
	pthread_t communication_pthread;

	start_log_file();
	
	create_thread(&app_listener, "COMMAPP", communication_app, QUEUE_APP, queue_list, NULL);			

	create_thread(&communication_pthread, "COMMTHREAD", communication_thread, QUEUE_COMMUNICATION_THREAD, queue_list, NULL);

	destroy_thread(app_listener);
	destroy_thread(communication_pthread);

	return EXIT_SUCCESS;
}

/* END */
