#include <stdio.h>
#include "mymalloc.h"

void* mymalloc(size_t s, char* file, int line)
{
	printf("mymalloc called on line %d in file %s\n", line, file);
	return NULL;
}

int myfree(void* ptr, char* file, int line)
{
	printf("myfree called on line %d in file %s\n", line, file);
	return 0;
}
