#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{
	// CASE 1: Trying to free something that isn't a pointer.
	int x = 0;
	free((int*)x);

	// CASE 2a: Trying to free something that was never saved to memory.
	char* y = (char*)malloc(200);
	free(y+10);
	free(y);

	// Case 2b: Trying to free something that was never saved to memory.
	int* z = NULL;
	free(z);

	// Case 3:  Trying to free something twice.
	char* a = (char*)malloc(100);
	free(a);
	free(a);

	// Case 4: Allocating something, freeing it, allocating it again, freeing it again.
	char* b = (char*)malloc(100);
	free(b);
	b = (char*)malloc(100);
	free(b);

	// Case 5a: Allocating too much memory.
	char* c = (char*)malloc(4097);
	free(c);

	// Case 5b: Allocating too much memory.
	char* d = (char*)malloc(4096-sizeof(metadata));
	char* e = (char*)malloc(1);
	free(d);
	free(e);

	// TEST A: malloc() 1 byte and immediately free it - do this 150 times
	char* f;
	for(x = 0; x < 150; x++)
	{
		f = (char*)malloc(1);
		free(f);
	};

	// TEST B: malloc() 1 byte, store the pointer in an array - do this 150 times.
	// Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.

	char* h[150];
	for(x = 0; x < 3; x++)
	{
		int i;
		for(i = (x*50); i < ((x*50)+50); i++)
		{
			h[i] = (char*)malloc(1);
		}
		for(i = (x*50); i < ((x*50)+50); i++)
		{
			free(h[i]);
		}
	}

	// TEST C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer > do this until you have allocated 50 times
	// - Keep track of each operation so that you eventually malloc() 50 bytes, in total
	// > if you have already allocated 50 times, disregard the random and just free() on each
	// iteration
	// - Keep track of each operation so that you eventually free() all pointers
	// > don't allow a free() if you have no pointers to free()

	char* j[50] = {NULL};
	int mallocs = 0;
	// int frees = 0;
	while(mallocs < 50)
	{
		x = (rand() % 2);
		if(x == 0)
		{
			// malloc 1 byte
			int k = 0;
			while(j[k] != NULL && k < 50)
			{
				++k;
			};
			if(k < 50)
			{
				j[k] = (char*)malloc(1);
				++mallocs;
				printf("malloc #%d at j[%d]\n", mallocs, k);
			}
			else
			{
				// we have 50 bytes allocated in memory...
				printf("all 50 bytes of j[] are in memory\n");
				x = 2;
				mallocs = 50;
			}
		}
		if(x == 1)
		{
			// free a 1 byte pointer
			int l = 0;

			while(j[l] == NULL && l < 50)
			{
				++l;
			};
			if(l < 50)
			{
				printf("freeing 1 byte at j[%d]\n", l);
				free(j[l]);
				j[l] = NULL;
				// ++frees;
			}
			else
			{
				// all pointers are free...
			}
		}
	}

	// by now hopefully we've malloc'd 50 times
	// now free any pointers that are still in j[].

	printf("we've malloc'd 50 times\n");
	for(x = 0; x < 50; x++)
	{
		if(j[x] != NULL)
		{
			printf("freeing 1 byte at j[%d]\n", x);
			free(j[x]);
		}
	}

	// 	D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
	// - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
	// - Keep track of each operation so that you eventually free() all pointers
	// - Choose a random allocation size between 1 and 64 bytes

	mallocs = 0;
	int malloc_size = 0;
	while(mallocs < 50)
	{
		x = rand() % 2;
		if(x == 0)
		{
			// malloc b/w 1 and 64 bytes
			int m = (rand() % 64) + 1;
			// m is the number of bytes we need to malloc
			if(malloc_size+m < 4096-sizeof(metadata))
			{
				//...allocate m bytes...
				malloc_size += m;
			}
		}
		if(x == 1)
		{
			// free a pointer
		}
	}

	printf("we've malloc'd 50 times\n");
	//...free everything...


	// E,F: Two more workloads of your choosing
	// - Describe both workloads in your testplan.txt

	// ...write test code here...

	return 0;
}
