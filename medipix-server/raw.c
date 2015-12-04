#include <stdbool.h>

#include "common.h"

bool save_images(char *buffer, const struct medipix_header *header,
               const struct acquisition_info *info)
{
	FILE *output;
	bool rc;
	int file_size;

	output = fopen(info->filename, "w");

	if (output == NULL)
		return false;

	rc = false;

	if (fwrite(info, sizeof(struct acquisition_info), 1, output) < 1)
		goto cleanup;

	file_size = SIZE_IMAGE_DATA*NUMBER_OF_PACKETS[info->number_bits]*
		info->number_frames*NUMBER_OF_READINGS[info->read_counter];

	if (fwrite(buffer, file_size, 1, output) < 1)
		goto cleanup;

	rc = true;

cleanup:
	fclose(output);
	return rc;
}
