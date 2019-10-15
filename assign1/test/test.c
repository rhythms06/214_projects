#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{
	// CASE 1: Trying to free something that isn't a pointer.
	// int x = 0;
	// free((int*)x);

	// CASE 2a: Trying to free something that was never saved to memory.
	// char* y = (char*)malloc(200);
	// free(y+10);
	// free(y);

	// Case 2b: Trying to free something that was never saved to memory.
	// int* z = NULL;
	// free(z);

	// Case 3:  Trying to free something twice.
	// char* a = (char*)malloc(100);
	// free(a);
	// free(a);

	// Case 4: Allocating something, freeing it, allocating it again, freeing it again.
	// char* b = (char*)malloc(100);
	// free(b);
	// b = (char*)malloc(100);
	// free(b);

	// Case 5a: Allocating too much memory.
	// char* c = (char*)malloc(4097);

	// Case 5b: Allocating too much memory.
	// char* d = (char*)malloc(4096-sizeof(metadata));
	// char* e = (char*)malloc(1);

	// TEST A
	// char* f;
	// for(int i = 0; i < 150; i++)
	// {
	// 	f = (char*)malloc(1);
	// 	free(f);
	// };

	// TEST B

	// if(p != NULL)
	// {
	// 	printf("%c\n", *p);
	// };

	// char* q = (char*)malloc(1);
	// if(q != NULL)
	// {
	// 	printf("%c\n", *q);
	// };



	// free(p);
	// free(q);

	// printf("Testing complete.\n");

	return 0;
}
