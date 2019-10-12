#include <stdio.h>
#include <malloc.h>
#include "mymalloc.h"

int main()
{
	printf("here we goo.\n\n");

	malloc(10, __FILE__, __LINE__);

	free(NULL, __FILE__, __LINE__);
	
	return 0;
}
