#include <stdio.h>
#include "mymalloc.h"

void* mymalloc(size_t s)
{
	printf("mymalloc called\n");
	return NULL;
}

int myfree(void* ptr)
{
	printf("myfree called\n");
	return 0;
}
