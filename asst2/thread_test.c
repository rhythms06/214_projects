#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "multitest.h"

typedef struct
{ // used as argument to search_t()
	pthread_t thread_id;
	int thread_num;
	int target;
	int* arr;
	int len;
	int bites;
} thread_info;

static void* search_t(void* args)
{
	thread_info *thread = args;
	int i, start, end;	
	i = start = thread->bites * thread->thread_num;
	end = start + thread->bites;
	if(end >= thread->len)
	{
		end = thread->len;
	}
	printf("thread: %d\tstart: %d\tend: %d\n", thread->thread_num, start, end);
	int titties = 420;
	pthread_exit((void*)&titties);
}

void dummy_search(int target, int* arr, int len, int bites, int* ifound)
{
	printf("target: %d\tlen: %d\tbites: %d\n", target, len, bites);
	int workers = ceil((double)len/bites);
	thread_info *threads = calloc(workers, sizeof(thread_info));
	if(threads == NULL)
	{ // mem allocation error
		fprintf(stderr, "error: unable to allocate memory for threads\n");
		exit(EXIT_FAILURE);
	}
	int tnum = 0;
	int s;
	while(tnum < workers)
	{
		threads[tnum].thread_num = tnum;
		threads[tnum].target = target;
		threads[tnum].arr = arr;
		threads[tnum].len = len;
		threads[tnum].bites = bites;
		s = pthread_create(&threads[tnum].thread_id, NULL, &search_t, &threads[tnum]);
		if(s != 0)
		{ // error creating thread
			fprintf(stderr, "error: thread %d was not created", tnum);
			exit(EXIT_FAILURE);
		}
		tnum++;
	}
	tnum = 0;
	//void* res = NULL;
	void* res = malloc(sizeof(void*));
	if(res == NULL)
	{ // obligatory error check
		fprintf(stderr, "error: unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	while(tnum < workers)
	{
		s = pthread_join(threads[tnum].thread_id, &res);
		if(s != 0)
		{
			fprintf(stderr, "error: thread %d not joined\n", tnum);
			exit(EXIT_FAILURE);
		}
		printf("Joined with thread %d. res: %d\n", threads[tnum].thread_num, (int*)res);
		tnum++;
	}
	free(res); 
	free(threads);
	exit(EXIT_SUCCESS);
}
