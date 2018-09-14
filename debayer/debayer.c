/* Code for debaying a image */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define height 480
#define width 640
#define PATH_IMAGE "/home/diego/debayer/media/image.raw"
#define PATH_FINAL "/home/diego/debayer/media/final.raw"

#define CHECK_EVEN(N) (N % 2 == 0)
#define CHECK_ODD(N) (N % 2 == 1)

static char generate_pixel_RGB565(char r, char g, char b)
{
	char rgb;
	
	printf("%c %c %c", r, g, b);
	
	rgb = r;// << g;
	
	return rgb;
}


static char *convert_bayer_to_rgb565(char *buffer, unsigned long size)
{
	unsigned long  i;

	char buf[size];
	char R, G, B;
	char pixel_rgb565;


	for (i = 0; i < size; i++) {
		
		if(CHECK_EVEN(x) && CHECK_EVEN(y)) { /* Red */
		
			R = (x, y)
			G = (x - Xunit, y)
			B = (x - Xunit, y - Yunit)
		
			pixel = generate_pixel_RGB565(R, G, B);
		}

		if(CHECK_ODD(x) && CHECK_EVEN(y)) { /* Green */
		
			R = (x - Xunit, y)
			G = (x, y)
			B = (x, y - Yunit)
		
			pixel = generate_pixel_RGB565(R, G, B);
		}
	
		if(CHECK_EVEN(x) && CHECK_ODD(y)) { /* Green */
		
			R = (x, y - Yunit)
			G = (x, y)
			B = (x - Xunit, y)
		
			pixel = generate_pixel_RGB565(R, G, B);
		}
	
		if(CHECK_ODD(x) && CHECK_ODD(y)) { /* Blue */
		
			R = (x - Xunit, y - Yunit)
			G = (x - Xunit, y)
			B = (x, y)
		
			pixel = generate_pixel_RGB565(R, G, B);
		}
		
		
		buffer[i] = pixel_rgb565;

		printf("%ld:\t%x\n", i, (char)buffer[i] & 0xFF);
		printf("%ld:\t%x\n", i, (char)buf[i]);
		
	}



	printf("Size of buffer: %ld", size);
	
	return buffer;
}


int main(void)
{
	FILE* input  = NULL;
	FILE* output = NULL;

	clock_t t;
	unsigned long rsize, result;	
	double time;

  	char *buffer;
  	char *outbuf;
	char *image = PATH_IMAGE;
	char *final =  PATH_FINAL;

	if ((input = fopen(image, "rb")) < 0) {
		fprintf(stderr, "The fopen() function has failed: %s!\n", strerror(errno));
		fclose(input);
		return EXIT_FAILURE;
	}

	if ((output = fopen(final, "wb")) < 0) {
		fprintf(stderr, "The fopen() function has failed: %s!\n", strerror(errno));
		fclose(input);
		fclose(output);
		return EXIT_FAILURE;
	}

	fseek(input, 0, SEEK_END);
	rsize = ftell(input);
	rewind (input);

	buffer = (char *) malloc(sizeof(char)*rsize);
	memset(buffer, 0, rsize);
  
	if(buffer == NULL) {
		fprintf(stderr, "Reading buffer has failed: %s!\n", strerror(errno));
		return EXIT_FAILURE;
	}

	result = fread(buffer, 1, rsize, input);

	if(result != rsize)	
		fprintf(stderr, "The fread() function has failed: %s!\n", strerror(errno));

    	t = clock();
	
	outbuf = convert_bayer_to_rgb565(buffer, rsize);

	fwrite(outbuf, 1, rsize, output);

 	t = clock() - t;
    	time = ((double)t) / CLOCKS_PER_SEC;

	printf("\nConversion took %f seconds to execute!\nDone!\n", time);

	fclose(input);
	fclose(output);

	return EXIT_SUCCESS;
}
