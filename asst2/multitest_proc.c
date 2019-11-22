#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "multitest.h"

/*
 * I'm pretty sure this is 100% correct. 
 * Ready for plug-and-play.
 * Let me know if you run into any problems during testing.
 */

void dummy_search(int target, int* arr, int len, int bites, int* ifound)
{
	pid_t cpid;
	int i, j, start, end; 
	i = 0;
	int workers = ceil((double)len/bites);
	while(i < workers)
	{
		cpid = fork();
		if(cpid == -1)
		{
			exit(-1);
		}
		if(cpid == 0) // child
		{
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
					j = j - start;
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
		{ // shouldn't run into an error.. but.. safety first ya know.
			fprintf(stderr, "%s\n", strerror(errno));
		} else if(stat == NOT_FOUND){ // proc didn't find target. no problem. carry on.
		} else
		{ // dynomite.
			stat = stat + (bites * i);
			*ifound = stat;
		}
		i++;
	}
	return;
}
