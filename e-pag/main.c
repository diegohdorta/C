/* Este problema é provavelmente fortemente acoplado, logo deveria utilizar threads.
   Ou seja, a troca de dados entre as tarefas são muito grandes.
   Criar o número de threads correspondente ao número de cores. Caso seja necessário, 
   e será, aumentar a concorrência utilizando co-rotinas.
   https://developer.gnome.org/
*/
#define _XOPEN_SOURCE 700

#include "library.h"


int main(void)
{
	struct process_arguments args = { 0 };
	
	int queue_list[MAXIMUM_THREADS];
	
	pthread_t app_listener;
	pthread_t devices_listener;
	pthread_t web_listener;

	start_log_file();
	
	do {		
		create_thread(&app_listener, communication_app, QUEUE_APP, queue_list, &args);
		create_thread(&devices_listener, communication_devices, QUEUE_DEVICES, queue_list, &args);
		create_thread(&web_listener, communication_web, QUEUE_WEB, queue_list, &args);

		destroy_thread(app_listener);
		destroy_thread(devices_listener);
		destroy_thread(web_listener);

	} while (true);

	return EXIT_SUCCESS;
}

/* END */
