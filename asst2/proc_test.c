#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "multitest.h"



void dummy_search(int target, int* arr, int len, int bites, int* ifound)
{
	printf("len: %d\n", len);
	printf("bites: %d\n", bites);
	int workers = ceil((double)len/bites);
	printf("workers: %d\n", workers);
	pid_t cpid;

	int i, j, start, end; 
	i = 0;
	while(i < workers)
	{
		cpid = fork();
		if(cpid == -1)
		{
			exit(-1);
		}
		if(cpid == 0) // child
		{
			printf("child %d -- PID: %d\n", i, getpid());
			j = start = (bites * i);
			end = j + bites;
			if(end >= len)
			{
				end = len;
			}
			while(j < end)
			{ 
				if(target == *(arr + j))
				{ // target found. let's get outta here!
					printf("*(arr + %d): %d\n", j, *(arr + j));
					printf("i = %d; j = %d; start = %d; end = %d\n", i, j, start, end);
					j = j - start;
					printf("i = %d; j = %d; start = %d; end = %d\n", i, j, start, end);
					exit(j);
				}
				j++;
			} // end of segment. target not found.
			exit(NOT_FOUND);
		}
		else { // parent. do nothing.
		}
		i++;
	}
	i = 0;
	int status;
	int stat = NOT_FOUND;
	while(i < workers)
	{
		wait(&status);
		stat = WEXITSTATUS(status);
		if(stat == -1)
		{
			fprintf(stderr, "%s\n", strerror(errno));
		} else if(stat == NOT_FOUND)
		{
		} else
		{
			printf("target found\n");
			printf("stat: %d\n", stat);
			printf("i: %d\n", i);
			stat = stat + (bites * i);
			*ifound = stat;
			//printf("ifound: %d\n", *ifound);
		}
		i++;
	}
	return;
}
