#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{

	char* p = (char*)malloc(1);
	// if(p != NULL)
	// {
	// 	printf("%c\n", *p);
	// };

	char* q = (char*)malloc(1);
	// if(q != NULL)
	// {
	// 	printf("%c\n", *q);
	// };

	free(p);
	free(q);

	// printf("Testing complete.\n");

	return 0;
}
