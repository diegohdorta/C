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
		create_thread(&app_listener, QUEUE_APP, communication_app, queue_list, &args);
		create_thread(&devices_listener, QUEUE_DEVICES, communication_devices, queue_list, &args);
		create_thread(&web_listener, QUEUE_WEB, communication_web, queue_list, &args);

		destroy_thread(app_listener);
		destroy_thread(devices_listener);
		destroy_thread(web_listener);

	} while (true);

	return EXIT_SUCCESS;
}

/* END */
