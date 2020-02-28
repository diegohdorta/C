/* Copyright (C) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 */
#ifndef _IMAGE_RECOGNIZER_DEMO_H_
#define _IMAGE_RECOGNIZER_DEMO_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE    1024
#define SCRIPT_FILE "./parser.sh"
#define CSV_FILE    "labels.csv"

struct dict {
    int index;
    char label[MAX_SIZE];
};

typedef struct dict dict_t;

void get_csv_file_size(unsigned int *csv_size);
void load_csv_file(dict_t *dict, unsigned int *csv_size);

void search(dict_t *dict, int key, int low, int high);
void get_index_from_parser(int *index);

#endif /* _IMAGE-RECOGNIZER-DEMO_H_DEFINED_*/
