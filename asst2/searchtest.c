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
    int* array = (int*) malloc(testsizes[i] * sizeof(int));
    if(array == NULL)
    {
      printf("Memory allocation failed :()\n");
      return -1;
    }
    generateArray(array, testsizes[i]);

    // int j = 0;
  	// while( j < 5 )
  	// {
  	// 	printf("%d ", *(array + j));
  	// 	j++;
  	// }
    // printf("\n");

    int chunks;
    for(chunks = 0; chunks < 5; chunks++)
    {
      // gettimeofday(&start, NULL);
      // CALL search() HERE with the inputs:
        // List: array
        // Size: testsizes[i]
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
