#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include "multitest.h"


int main()
{
	int i;
	int len = 700;

	int* arr = (int*)malloc(len * sizeof(int));
	int* found = (int*)malloc(sizeof(int));;
	if(arr == NULL || found == NULL) { printf("error.\n"); exit(EXIT_FAILURE); }

	i = 0;
	while(i < len)
	{
		*(arr+i) = i;
		i++;
	}

	int minScrambles = ((len *  3) + (4 - 1)) / 4;
	int swap1, swap2, tmp; swap1 = swap2 = tmp = -1;
  	srand(time(NULL));
  	//printf("Let's scramble %d out of %d integers.\n", minScrambles, length);

  	for(i = 0; i < minScrambles; i++)
  	{
		swap1 = (rand() % len);
		swap2 = (rand() % len);
		tmp = arr[swap1];
		arr[swap1] = arr[swap2];
		arr[swap2] = tmp;
	}

	i = 0;
	while(i < 700)
	{
		if(*(arr + i) == 301)
		{
			printf("found %d at arr[%d]\n", 301, i);
			break;
		}
		i++;
	}
	search(301, arr, len, 50, found);
	printf("found: %d\n", *found);

	free(arr);
	free(found);
	exit(EXIT_SUCCESS);
}
