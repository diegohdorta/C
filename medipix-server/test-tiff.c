#include <stdio.h>
#include <string.h>

#include "common.h"

int main(void)
{
	FILE *f;
	char data[65536];
	struct acquisition_info info;

	f = fopen("teste", "r");
	fread(&info, sizeof(info), 1, f);
	fread(data, 65536, 1, f);
	fclose(f);

	strcpy(info.filename, "test-tiff.tiff");

	save_images(data, NULL, &info);
}
