#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_

#define CHARACTERS		"ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 1234567890"

int free_id;
int busy_id;
int producer_lock;
int consumer_lock;
int stderr_lock;
int g_shm_id;

buffer_t *g_buffer_t;

int *tmp_addr;

char g_letters_and_numbers[] = CHARACTERS;

#endif /* _CHARACTERS_H_DEFINED_ */
