#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "multitest.h"

void search(int target, int* arr, int len) {
	int i = 0;
	while( i < len )
	{
		printf("*(arr + %d): %d\n", i, *(arr + i));
		i++;
	}
	exit(1);
}

void dummy_search(int target, int* arr, int len, int chunksize, int* ifound)
{
	printf("dummy search process\n");
	exit(EXIT_SUCCESS);
}
