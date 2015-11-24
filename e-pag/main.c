/* Este problema é provavelmente fortemente acoplado, logo deveria utilizar threads.
   Ou seja, a troca de dados entre as tarefas são muito grandes.
   Criar o número de threads correspondente ao número de cores. Caso seja necessário, 
   e será, aumentar a concorrência utilizando co-rotinas.
   https://developer.gnome.org/
*/
#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE

#include "library.h"

int main(void)
{
	struct process_arguments *args = { 0 };
	//int ret_app_listener;
	int ret_web_listener;
	//int ret_opr_listener;

	//pthread_t app_listener;
	pthread_t web_listener;
	//pthread_t opr_listener;

	start_log_file();
	
	do {		
		//ret_app_listener = pthread_create(&app_listener, NULL, start_communication_app, (void *)args);
		//check_creation_thread(ret_app_listener);
		
		ret_web_listener = pthread_create(&web_listener, NULL, start_communication_web, (void *)args);
		check_creation_thread(ret_web_listener);
		
		//ret_opr_listener = pthread_create(&opr_listener, NULL, start_communication_opr, (void *)args);
		//check_creation_thread(ret_opr_listener);
		
		//destroy_thread(app_listener);
		destroy_thread(web_listener);
		//destroy_thread(opr_listener);
				

	} while (true);

	return EXIT_SUCCESS;
}

/* END */
