#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void calculator(size_t msg_size)
{
	printf("calculator function: %zd\n", msg_size);
}
