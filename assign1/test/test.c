#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

int main()
{
/*
	// CASE 0;
	free(NULL);

	// CASE 1: Trying to free something that isn't a pointer.
	// note: find way to avoid warning upon compile and handle this gracefully.
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

	// Case 5b: Allocating too much memory.
	char* d = (char*)malloc(4096-sizeof(metadata));
	char* e = (char*)malloc(1);
	free(d);
	free(e);
*/

	/* general-use variables */
	short int i = 0;
	short int workload_iterator = 0;
	
	/* runtime-testing variables.
	 * using a struct for readability/organization.
	 * will accumulate all 100 iterations of each workload into respective vars.
	 */
	typedef struct {
		double A, B, C, D, E, F;
	} _runtime;
	_runtime runtime = {0, 0, 0, 0, 0, 0};
	struct timeval start, stop;

	while(workload_iterator < 100)
	{
		//printf("\\\\--------------- workload number: %d -------------\\\\\n", workload_iterator);
		// TEST A: malloc() 1 byte and immediately free it - do this 150 times
		gettimeofday(&start, NULL);
		char* f;
		int x;
		for(x = 0; x < 150; x++)
		{
			f = (char*)malloc(1);
			free(f);
		};
		gettimeofday(&stop, NULL);
		runtime.A += (stop.tv_usec - start.tv_usec);


		// TEST B: malloc() 1 byte, store the pointer in an array - do this 150 times.
		// Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
		gettimeofday(&start, NULL);
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
		gettimeofday(&stop, NULL);
		runtime.B += (stop.tv_usec - start.tv_usec);
		
		// TEST C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer > do this until you have allocated 50 times
		// - Keep track of each operation so that you eventually malloc() 50 bytes, in total
		// > if you have already allocated 50 times, disregard the random and just free() on each
		// iteration
		// - Keep track of each operation so that you eventually free() all pointers
		// > don't allow a free() if you have no pointers to free()
		//printf("\t##------- workload C -------##\n");
		gettimeofday(&start, NULL);
		char* j[50] = {NULL};
		int mallocs = 0;
		srand(time(NULL));
		//srand(times(NULL));
		// int frees = 0;
		while(mallocs < 50)
		{
			x = (random() % 2);
			if(x == 0)
			{
				// malloc 1 byte
				int k = 0;
				while(j[k] != NULL && k < 50)
				{
					++k;
				};
				j[k] = (char*)malloc(1);
				++mallocs;
				//printf("malloc #%d at j[%d]\n", mallocs, k);
			}
			else if(x == 1)
			{
				// free a 1 byte pointer
				int l = 0;

				while(j[l] == NULL && l < 50)
				{
					++l;
				};
				if(l < 50)
				{
					//printf("freeing 1 byte at j[%d]\n", l);
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

		//printf("we've malloc'd 50 times\n");
		for(x = 0; x < 50; x++)
		{
			if(j[x] != NULL)
			{
				//printf("freeing 1 byte at j[%d]\n", x);
				free(j[x]);
				j[x] = NULL;
			}
		}
		gettimeofday(&stop, NULL);
		runtime.C += (stop.tv_usec - start.tv_usec);

		// 	D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
		// - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
		// - Keep track of each operation so that you eventually free() all pointers
		// - Choose a random allocation size between 1 and 64 bytes
		gettimeofday(&start, NULL);
		mallocs = 0;
		//int malloc_size = 0;
		//srand(time(NULL));
		while(mallocs < 50)
		{
			x = rand() % 2;
			if(x == 0)
			{
				// malloc b/w 1 and 64 bytes
				// m is the number of bytes we need to malloc
				int m = (rand() % 64) + 1;
				int k = 0;
				while(j[k] != NULL && k < 50)
				{
					k++;
				}
				//printf("malloc %d: %d bytes at j[%d]\n", mallocs, m, k);
				j[k] = (char*)malloc(sizeof(char) * m);
				mallocs++;
			}
			else if(x == 1)
			{
				int l = 0;
				while(j[l] == NULL && l < 50)
				{
					l++;
				}
				if(l < 50)
				{
					//printf("free memory at j[%d]\n", l);
					free(j[l]);
					j[l] = NULL;
				}
			}

	///////////////// user should not be checking available memory before trying to malloc.
				/*
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
			mallocs++;
			*/
		}

		// malloc'd 50 times. free remaining memory.
		//printf("we've malloc'd 50 times\n");
		x = 0;
		while(x < 50)
		{
			if(j[x] != NULL)
			{
				//printf("freeing memory at j[%d]\n", x);
				free(j[x]);
				j[x] = NULL;	
			}
			x++;

		}
		gettimeofday(&stop, NULL);
		runtime.D += (stop.tv_usec - start.tv_usec);


		/* Test E
		 */
		gettimeofday(&start, NULL);

		// do some stuff... 

		gettimeofday(&stop, NULL);
		runtime.E += (stop.tv_usec - start.tv_usec);
		
		
		/* Test F
		 */
		gettimeofday(&start, NULL);

		// do some stuff... 

		gettimeofday(&stop, NULL);
		runtime.F += (stop.tv_usec - start.tv_usec);
		


		workload_iterator++;
	}

	/* Time-Crunch -- get the mean runtimes for each Workload, A-F, and print */
	fprintf(stdout, "Mean Runtimes:\n\tworkload A ---- %f\n", runtime.A/100);
	fprintf(stdout, "\tworkload B ---- %f\n", runtime.B/100);
	fprintf(stdout, "\tworkload C ---- %f\n", runtime.C/100);
	fprintf(stdout, "\tworkload D ---- %f\n", runtime.D/100);
	fprintf(stdout, "\tworkload E ---- %f\n", runtime.E/100);
	fprintf(stdout, "\tworkload F ---- %f\n", runtime.F/100);
	return 0;
}
