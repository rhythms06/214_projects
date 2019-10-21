#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

int main()
{
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

	/* struct Node for linked list Workload E */
	typedef struct _Node {
		int data;
		struct _Node* next;
	} Node;

	while(workload_iterator < 100)
	{
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

		gettimeofday(&start, NULL);
		char* j[50] = {NULL};
		int mallocs = 0;
		srand(time(NULL));

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
			}
			else if(x == 1)
			{
				// free a 1 byte pointer
				int l = 0;

				while(j[l] == NULL && l < 50)
				{
					++l;
				};
				if(j[l] != NULL && l < 50)
				{
					free(j[l]);
					j[l] = NULL;
				}
			}
		}

		// by now we've malloc'd 50 times
		// free any pointers that are still in j[].
		for(x = 0; x < 50; x++)
		{
			if(j[x] != NULL)
			{
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
		char* arrD[50] = {NULL};
		x = 0;
		while(mallocs < 50)
		{
			x = rand() % 2;
			if(x == 0)
			{
				// malloc b/w 1 and 64 bytes
				// m is the number of bytes we need to malloc
				int m = (rand() % 64) + 1;
				int k = 0;
				while(arrD[k] != NULL && k < 50)
				{
					k++;
				}
				if(arrD[k] == NULL && k < 50)
				{
					arrD[k] = (char*)malloc(m);
					mallocs++;
				}
			}
			else if(x == 1)
			{
				int l = 0;
				while(arrD[l] == NULL && l < 50)
				{
					l++;
				}
				if(arrD[l] != NULL && l < 50)
				{
					free(arrD[l]);
					arrD[l] = NULL;
				}
			}
		}

		// malloc'd 50 times. free remaining memory.
		x = 0;
		while(x < 50)
		{
			if(arrD[x] != NULL)
			{
				free(arrD[x]);
				arrD[x] = NULL;	
			}
			x++;

		}
		gettimeofday(&stop, NULL);
		runtime.D += (stop.tv_usec - start.tv_usec);


		/* Workload E
		 * create a linked list of 20 Nodes, with an integer field.
		 * populate each node with a random number, then free all nodes.
		 * the struct will be defined at the top of this file.
		 */
		gettimeofday(&start, NULL);
		i = 0;
		int n = 0;
		Node* ptr;
		/* build the linked list */
		Node* head = (Node*)malloc(sizeof(Node));
		if(head == NULL)
		{
			fprintf(stderr, ERR_STR, __FILE__, __LINE__, "whoops, that Node wasn't allocated bruh.\n");
			continue;
		}
		else { head->data = rand(); head->next = NULL; ptr = head;}
		while(i < 20)
		{
			Node* new = (Node*)malloc(sizeof(Node));
			if(head == NULL)
			{
				fprintf(stderr, ERR_STR, __FILE__, __LINE__, "whoops, that Node wasn't allocated bruh.\n");
				continue;
			}	
			new->data = rand(); new->next = NULL;
			ptr->next = new; ptr = new;
			i++;
		}
		/* free all nodes */
		ptr = head;
		while(ptr != NULL)
		{
			Node* curr = ptr;
			ptr = ptr->next;
			free(curr);
		}
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
