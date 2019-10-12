#include <stdio.h>
#include <malloc.h>
#include "mymalloc.h"

int main()
{
	printf("here we goo.\n\n");

	malloc(10);

	free(NULL);
	
	return 0;
}
