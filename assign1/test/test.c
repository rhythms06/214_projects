#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{

<<<<<<< HEAD
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

=======
	malloc(10, __FILE__, __LINE__);

	free(NULL, __FILE__, __LINE__);
	
>>>>>>> 97ceddd4fc967859485689d2094619db0d099f6a
	return 0;
}
