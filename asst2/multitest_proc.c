#include <stdlib.h>
#include <stdio.h>
#include "multitest.h"

void search(int target, int** arr, int len) {
	int i = 0;
	while( i < len )
	{
		if( i == (*arr + i) )
		{ // target found
			exit(i);
		}
		i++;
	}
	exit(EXIT_FAILURE);
}

void dummy_search(int target, int** arr, int len, int chunksize, int* ifound)
{
	printf("dummy search process\n");
	exit(EXIT_SUCCESS);
}
