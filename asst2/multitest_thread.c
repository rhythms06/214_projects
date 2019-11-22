#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "multitest.h"


void dummy_search(int target, int* arr, int len, int bites, int* ifound)
{
	printf("dummy search process\n");
	pthread_exit(EXIT_SUCCESS);
}
