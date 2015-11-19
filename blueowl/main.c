/* Este problema é provavelmente fortemente acoplado, logo deveria utilizar threads.
   Ou seja, a troca de dados entre as tarefas são muito grandes.
   Criar o número de threads correspondente ao número de cores. Caso seja necessário, 
   e será, aumentar a concorrência utilizando co-rotinas.
   https://developer.gnome.org/
*/
#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "library.h"

int main(void)
{
	struct process_arguments x = { 0 };
	pid_t app_listener;
	pid_t web_listener;
	pid_t bank_listener;

	start_log_file();
	
	do {
		
		app_listener = create_process(communication_app, &x);
				
		web_listener = create_process(communication_web, &x);
				
		bank_listener = create_process(communication_bank, &x);
		
		
		kill(app_listener, SIGTERM);
		waitpid(app_listener, NULL, 0);
		
		kill(web_listener, SIGTERM);
		waitpid(web_listener, NULL, 0);
		
		kill(bank_listener, SIGTERM);
		waitpid(bank_listener, NULL, 0);
	
	
	} while (true);

	return EXIT_SUCCESS;
}

/* END */
