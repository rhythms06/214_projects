#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{

	char* p = (char*)malloc(30);
	// if(p != NULL)
	// {
	// 	printf("%c\n", *p);
	// };

	char* q = (char*)malloc(30);
	// if(q != NULL)
	// {
	// 	printf("%c\n", *q);
	// };

	free(NULL);

	// printf("Testing complete.\n");

	return 0;
}
