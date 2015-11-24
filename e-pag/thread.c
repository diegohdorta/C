#define _BSD_SOURCE

#include "library.h"

void check_creation_thread(int id)
{
	if (id) {
		debug(stderr, "ERRO: Impossível criar thread!\n");
		exit(EXIT_FAILURE);
	}
}

void destroy_thread(pthread_t id)
{
	pthread_join(id, NULL);
}

