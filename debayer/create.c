/* Code for creating image */
/* Command line for convert raw image to png:

   $ ffmpeg -vcodec rawvideo -f rawvideo -pix_fmt rgb565be -s 640x480 -i final.raw -f image2 -vcodec png screen.png

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define height 480
#define width 640

#define BLUE	0x001F // 0000 0001 0000 0005
//			  0000 0000 1111 1111
//00000001000000001

//0A53
//0000 1010 0101 0011
//#define BLUE_b	1000000100000001

//FF
//1111 1111

int main(void)
{
	FILE* output = NULL;

	int colums, rows, i;
	clock_t t;
	double time;

	char *final =  "/home/diego/debayer/media/final.raw";

	if ((output = fopen(final, "wb")) < 0) {
		printf("Unable to open final.raw\n");
		fclose(output);
		return EXIT_FAILURE;
	}

	unsigned char buffer[width*height*2];
	memset(buffer, 0, width*height*2);

   	t = clock();


	for (i = 0; i < height*width*2; i = i + 2) {
		
		buffer[i] = BLUE >> 8;
		buffer[i+1] = BLUE & 0xFF;

		//printf(" %d: %d\n", i, (int)buffer[i]);	
		//printf(" %d: %d\n", i+1, (int)buffer[i+1]);	

	}

	fwrite(&buffer, height*width*2, 1, output);

	t = clock() - t;
    	time = ((double)t) / CLOCKS_PER_SEC;

	printf("\nConversion took %f seconds to execute!\n", time);

	fclose(output);

	return EXIT_SUCCESS;
}
