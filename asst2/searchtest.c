#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "multitest.h"

void generateArray(int* array, int length) {
  int i;
  for(i = 0; i < length; i++)
  {
    array[i] = i;
  }
  int minScrambles = ((length *  3) + (4 - 1)) / 4;
  int swap1, swap2, tmp; swap1 = swap2 = tmp = -1;
  srand(time(NULL));
  //printf("Let's scramble %d out of %d integers.\n", minScrambles, length);
  for(i = 0; i < minScrambles; i++)
  {
  	swap1 = (rand() % length);
  	swap2 = (rand() % length);
  	tmp = array[swap1];
  	array[swap1] = array[swap2];
  	array[swap2] = tmp;
  }
}

int main(int argc, char** argv) {
  // int found = 0;
  // struct timeval start, stop;

  int testsizes[9] = {250, 300, 500, 1000, 2000, 4000, 8000, 16000, 32000};

  int i;

  for(i = 0; i < 9; i++)
  {
    int size = testsizes[i];
    int* array = (int*) malloc(size * sizeof(int));
    if(array == NULL)
    {
      printf("Memory allocation failed :()\n");
      return -1;
    }
    generateArray(array, size);

    // Uncomment the following to print out
    // the first few random numbers we just generated.
    //
    // int j = 0;
  	// while( j < 5 )
  	// {
  	// 	printf("%d ", *(array + j));
  	// 	j++;
  	// }
    // printf("\n");

    // Try an iterative search first.
    //
    // gettimeofday(&start, NULL);
    // CALL search() HERE with the inputs:
      // List: array
      // Size: testsizes[i]
      // Workers: 1
      // Query: query
      // Result: found
    // gettimeofday(&stop, NULL);
    // long seconds = (stop.tv_sec - start.tv_sec);
    // long micros = ((seconds * 1000000) + stop.tv_usec) - (start.tv_usec);
    // printf("Time elapsed: %ld.%ld seconds.\n", seconds, micros);

    // Now try searhing with an increasing number of workers,
    // making sure that no worker is searching more than 250 integers.
    //
    int min_workers = (size +  (250 - 1)) / 250;
    // The '5' in the line below is arbitrary.
    int max_workers = min_workers + 5;
    int workers;
    for(workers = min_workers; workers < max_workers; workers++)
    {
      // gettimeofday(&start, NULL);
      // CALL search() HERE with the inputs:
        // List: array
        // Size: testsizes[i]
        // Workers: workers
        // Query: query
        // Result: found
      // gettimeofday(&stop, NULL);
      // long seconds = (stop.tv_sec - start.tv_sec);
      // long micros = ((seconds * 1000000) + stop.tv_usec) - (start.tv_usec);
      // printf("Time elapsed: %ld.%ld seconds.\n", seconds, micros);
    }

    free(array);
  }
}
