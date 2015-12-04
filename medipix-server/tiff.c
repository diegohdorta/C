#include <stdbool.h>

#include <tiffio.h>

#include "common.h"

static void *image_open(const char *file_name)
{
	return TIFFOpen(file_name, "w");
}

static void image_close(void *image)
{
	TIFFClose(image);
}

static bool image_fill_metadata(void *image, unsigned bits_per_pixel)
{
	if (TIFFSetField(image, TIFFTAG_IMAGEWIDTH, WIDTH) < 0 ||
		TIFFSetField(image, TIFFTAG_IMAGELENGTH, HEIGHT) < 0 ||
		TIFFSetField(image, TIFFTAG_SAMPLESPERPIXEL, 1) < 0 ||
		TIFFSetField(image, TIFFTAG_BITSPERSAMPLE, bits_per_pixel) < 0 ||
		TIFFSetField(image, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT) < 0 ||
		TIFFSetField(image, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG) < 0 ||
		TIFFSetField(image, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK) < 0 ||
		TIFFSetField(image, TIFFTAG_MAKE, MEDIPIX) < 0 ||
		TIFFSetField(image, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT) < 0 ||
		TIFFSetField(image, TIFFTAG_ROWSPERSTRIP, HEIGHT) < 0) {

		return false;
	}

	return true;
}

static bool image_write(void *image, char *data, size_t size)
{
	return (TIFFWriteRawStrip(image, 0, data, size) != -1);
}

bool save_images(char *buffer, const struct medipix_header *header,
	const struct acquisition_info *info)
{
	void *img;
	bool rc;
	char packed[WIDTH*MAX_IMAGE_BYTES_PER_PIXEL];
	size_t nl, fl;
	const size_t network_bits_per_pixel[] = { 8, 96, 48, 96 };
	const size_t file_bits_per_pixel[] = { 1, 16, 8, 16 };
	unsigned i;

	rc = false;
	img = image_open(info->filename);

	if (img == NULL)
		return false;

	if (!image_fill_metadata(img, file_bits_per_pixel[info->number_bits]))
		goto cleanup;

	nl = network_bits_per_pixel[info->number_bits]*WIDTH/8;
	fl = file_bits_per_pixel[info->number_bits]*WIDTH/8;

	for (i = 0; i < HEIGHT; i++) {
		convert_line(packed, buffer, info->number_bits);

		if (!image_write(img, packed, fl))
			goto cleanup;

		buffer += nl;
	}

	rc = true;

cleanup:
	if (!rc) {

		debug(log_error, "Error writing TIFF file.\n");
		debug(stderr, "Error writing TIFF file.\n");
	}

	image_close(img);

	return rc;
}
