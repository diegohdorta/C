/* Copyright (C) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 */
#include "image-recognizer-demo.h"

void search(dict_t *dict, int key, int low, int high)
{
	int middle = 0;
	middle = (low + high) / 2;

	if (dict[middle].index == key) {
	    fprintf(stdout, "%s\n", dict[middle].label);
	}
	else (dict[middle].index > key)
	        ? search(dict, key, low, middle - 1)
	        : search(dict, key, middle + 1, high);
}

void get_index_from_parser(int *index)
{
    char line[MAX_SIZE];
    FILE *pipe = popen(SCRIPT_FILE, "r");

    if (!pipe) {
        fprintf(stderr, "popen() function failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (!(fgets(line, MAX_SIZE, pipe))) {
        fprintf(stderr, "fgets() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    (*index) = atoi(line);
    pclose(pipe);
}
