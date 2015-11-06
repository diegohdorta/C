#include <stdlib.h>
#include <tiffio.h>
#include <math.h>
#include <string.h>

void try(tsize_t v)
{
    if (v == -1) {
        fprintf(stderr, "Error.\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    TIFF *t;
    unsigned char image[256*256];
    unsigned i;
    double x, y, z;
    unsigned j, k;

    t = TIFFOpen("hello.tiff", "w");
    
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    
    memset(image, 0, sizeof(image));
    
    for (i = 0; i < 36000; i++) {
        z = i;
        z /= 1000.0;
        x = 30*(2*cos(z)-cos(2*z)) + 128.0;
        y = 30*(2*sin(z)-sin(2*z)) + 128.0;
        j = x;
        k = y;
        image[j+256*k] = 255;
    }

    try(TIFFSetField(t, TIFFTAG_IMAGEWIDTH, 256));
    try(TIFFSetField(t, TIFFTAG_IMAGELENGTH, 256));
    try(TIFFSetField(t, TIFFTAG_SAMPLESPERPIXEL, 1));
    try(TIFFSetField(t, TIFFTAG_BITSPERSAMPLE, 8));
    try(TIFFSetField(t, TIFFTAG_ORIENTATION, ORIENTATION_RIGHTBOT));
    try(TIFFSetField(t, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG));
    try(TIFFSetField(t, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK));
    try(TIFFSetField(t, TIFFTAG_ROWSPERSTRIP, 256));
    
    for (i = 0; i < 256; i++) {
        try(TIFFWriteRawStrip(t, 0, image+256*i, 256));
    }
    
    TIFFClose(t);
    
    return 0;
}
