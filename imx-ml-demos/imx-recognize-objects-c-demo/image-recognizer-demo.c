/* Copyright (C) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 */
#include "image-recognizer-demo.h"

int main(int argc, char *argv[])
{
    int i = 0;
    int ret = 0;
    int index = 0;
    unsigned int csv_size = 0;
    dict_t *dict;

    get_csv_file_size(&csv_size);

    dict = malloc(sizeof(dict_t) * csv_size);
    if (!dict) {
        fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    load_csv_file(dict, &csv_size);
    get_index_from_parser(&index);     

    (index <= csv_size && index >= 0)
        ? search(dict, index, 0, csv_size)
        : fprintf(stderr, "out of range\n");

    free(dict);
    return EXIT_SUCCESS;
}
