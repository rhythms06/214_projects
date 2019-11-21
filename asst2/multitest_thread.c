#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include "multitest.h"

void search(int list_size, int query) {
  printf("Mode: Multithreading.\n");
  printf("List size: %d.\n", list_size);
  printf("Query: %d.\n", query);
}

void dummy_search(int target, int** arr, int len, int chunksize, int* ifound)
{
	printf("dummy search process\n");
	pthread_exit(EXIT_SUCCESS);
}
