/* Copyright (C) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 */
#include "image-recognizer-demo.h"

const char *csv_file = CSV_FILE;

void get_csv_file_size(unsigned int *csv_size)
{
    char ch;
    FILE *fp = fopen(csv_file, "r");

    if (!fp) {
        fprintf(stderr, "fopen() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    do {
        ch = fgetc(fp);
        if (ch == '\n') (*csv_size)++;
    } while (ch != EOF);
    if (ferror(fp)) {
        fprintf(stderr, "fgetc() failed: %s\n", strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

void load_csv_file(dict_t *dict, unsigned int *csv_size)
{
    int ret = 0, i = 0;
    FILE *fp = fopen(csv_file, "r");

    if (!fp) {
        fprintf(stderr, "fopen()function failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < *csv_size; i++) {
        ret = fscanf(fp, "%d:", &dict[i].index);
        if (ferror(fp) || ret < 1) {
            fprintf(stderr, "fscanf() failed: invalid file format\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        if (!(fgets(dict[i].label, sizeof(dict[i].label), fp))) {
            fprintf(stderr, "fgets() failed: %s\n", strerror(errno));
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        dict[i].label[strlen(dict[i].label) - 1] = '\0';
    }
    fclose(fp);
}
