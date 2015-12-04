#define _BSD_SOURCE

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
	
	thread_data->thread_fn(thread_data->my_queue, thread_data->queue_list, thread_data->data);
	destroy_queue(thread_data->my_queue);
	free(thread_data);
	return NULL;
}
	//create_thread(&app_listener, QUEUE_APP, communication_app, queue_list, &args);
	
	//void communication_devices(int my_queue, int *queue_list, void *data)

void create_thread(pthread_t *thread, void (*function)(int, int *, void *), int queue_index, int *queue_list, void *data)
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

	ret = pthread_create(thread, NULL, entry, thread_data);	
	check_thread_creation(ret);
}

