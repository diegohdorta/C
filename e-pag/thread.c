#define _XOPEN_SOURCE 700

#include <sys/prctl.h>

#include "library.h"

void check_thread_creation(int id)
{
	if (id) {
		debug(log_error, "Error trying to create thread: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void destroy_thread(pthread_t id)
{
	pthread_join(id, NULL);
}

static void *entry(void *entry_data)
{
	thread_t *thread_data = entry_data;
	
	if (prctl(PR_SET_NAME, (unsigned long)thread_data->name, 0, 0, 0) < 0) {
		debug(log_error, "Error trying to alloc memory: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	thread_data->thread_fn(thread_data->my_queue, thread_data->queue_list, thread_data->data);
	destroy_queue(thread_data->my_queue);
	free(thread_data);
	return NULL;
}

void create_thread(pthread_t *thread, const char *name, void (*function)(int, int *, void *), int queue_index, int *queue_list, void *data)
{
	int ret;
	thread_t *thread_data;
	
	thread_data = malloc(sizeof(thread_t));
	
	if (thread_data == NULL) {
		debug(log_error, "Error trying to alloc memory: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	thread_data->queue_list = queue_list;
	thread_data->queue_list[queue_index] = create_message_queue();
	thread_data->my_queue = queue_list[queue_index];
	thread_data->data = data;
	thread_data->thread_fn = function;
	thread_data->name = name;

	ret = pthread_create(thread, NULL, entry, thread_data);	
	check_thread_creation(ret);
	
}

