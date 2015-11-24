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

void kill_process(pid_t listener)
{
	kill(listener, SIGTERM);
	waitpid(listener, NULL, 0);
}

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

	} while (true);
	
	kill_process(app_listener);
	kill_process(web_listener);
	kill_process(bank_listener);	


	return EXIT_SUCCESS;
}

/* END */
