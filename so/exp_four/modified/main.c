#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	tittle();
	create_philosophers();
	
	sleep(100);
	
	exit(EXIT_SUCCESS);
}

