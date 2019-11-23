#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
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
  int* found = (int*)malloc(sizeof(int));
  if(found == NULL)
  {
    printf("Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }

  struct timeval start, stop;

  int testlengths[9] = {250, 300, 500, 1000, 2000, 4000, 8000, 16000, 32000};
  // int testlengths[1] = {250};

  int i;

  for(i = 0; i < 9; i++)
  {
    int length = testlengths[i];
    int* array = (int*) malloc(length * sizeof(int));
    if(array == NULL)
    {
      printf("Memory allocation failed!\n");
      exit(EXIT_FAILURE);
    }
    generateArray(array, length);

    // Print the first few random numbers we just generated.
    //
    // int j = 0;
  	// while( j < 5 )
  	// {
  	// 	printf("%d ", *(array + j));
  	// 	j++;
  	// }
    // printf("\n");

    int query = 63;
    printf("Query: %d.\n", query);

    int chunkSize = 0;
    // int minChunkSize = (length + (15-1))/15;
    // int maxChunkSize = 250;
    int numWorkers = 0;
    int minWorkers = (length + (250-1))/250;
    int iter;
    // Change maxIter if you want more or less iterations per testcase.
    int maxIter = 5;
    long timeArray[maxIter];
    long currTime;
    gettimeofday(&start, NULL);
    long minTime = start.tv_usec;
    long maxTime = 0;
    long sumOfTimes = 0;
    long avgTime;
    long stDev;

    for(numWorkers = minWorkers; numWorkers <= (minWorkers + 9); numWorkers++)
    {
      chunkSize = ceil((double)length/numWorkers);
      // if(numWorkers != ceil((double)length/chunkSize))
      // if(chunkSize != ceil((double)length/numWorkers))
      // {
      //   chunkSize = ceil((double)length/numWorkers);
        // numWorkers = ceil((double)length/chunkSize);
        gettimeofday(&start, NULL);
        minTime = start.tv_usec;
        maxTime = 0;
        sumOfTimes = 0;
        for(iter = 1; iter <= maxIter; iter++)
        {
          printf("Iteration #%d out of %d.\n", iter, maxIter);
          // Set a timer, call search(), and stop the timer.
          //
          gettimeofday(&start, NULL);
          search(62, array, length, chunkSize, found);
          gettimeofday(&stop, NULL);
          // printf("found at %d\n", *found);
          currTime = (stop.tv_usec - start.tv_usec);
          timeArray[iter - 1] = currTime;
          sumOfTimes += currTime;
          if(currTime < minTime){minTime = currTime;}
          if(currTime > maxTime){maxTime = currTime;}
          printf("Time elapsed: %ld microseconds.\n", currTime);
          int randomIndex = (rand() % length);
          int intAtRandomIndex = array[randomIndex];
          // printf("BEFORE - array[%d]: %d, array[%d]: %d\n", *found, array[*found], randomIndex, array[randomIndex]);
          array[*found] = intAtRandomIndex;
          array[randomIndex] = *found;
          // printf("AFTER - array[%d]: %d, array[%d]: %d\n", *found, array[*found], randomIndex, array[randomIndex]);
        }
        avgTime = sumOfTimes/3;
        for(iter = 1; iter <= maxIter; iter++)
        {
          stDev += pow((timeArray[iter - 1] - avgTime),2);
          stDev = stDev/(maxIter - 1);
          stDev = sqrt(stDev);
        }
        printf("Min: %ld us. - Max: %ld us. - Average: %ld us. - Standard Deviation: %ld us.\n", minTime, maxTime, avgTime, stDev);
      // }
    }

    // Do everything once more with just one Process.
    printf("Mode: Just one process. - List Size: %d.\n", length);
    gettimeofday(&start, NULL);
    minTime = start.tv_usec;
    maxTime = 0;
    sumOfTimes = 0;
    for(iter = 1; iter <= maxIter; iter++)
    {
      printf("Iteration #%d out of %d.\n", iter, maxIter);
      // Set a timer, search, and stop the timer.
      //
      gettimeofday(&start, NULL);
      int index;
      for(index = 0; index < length; index++)
      {
        if(array[index] == query)
        {
          *found = index;
          index = length;
        }
      }
      gettimeofday(&stop, NULL);
      // printf("found at %d\n", *found);
      currTime = (stop.tv_usec - start.tv_usec);
      timeArray[iter - 1] = currTime;
      sumOfTimes += currTime;
      if(currTime < minTime){minTime = currTime;}
      if(currTime > maxTime){maxTime = currTime;}
      printf("Time elapsed: %ld microseconds.\n", currTime);
      int randomIndex = (rand() % length);
      int intAtRandomIndex = array[randomIndex];
      array[*found] = intAtRandomIndex;
      array[randomIndex] = *found;
    };
    avgTime = sumOfTimes/maxIter;
    for(iter = 1; iter <= maxIter; iter++)
    {
      stDev += pow((timeArray[iter - 1] - avgTime),2);
      stDev = stDev/(maxIter - 1);
      stDev = sqrt(stDev);
    }
    printf("Min: %ld us. - Max: %ld us. - Average: %ld us. - Standard Deviation: %ld ms.\n", minTime, maxTime, avgTime, stDev);


    free(array);
  }
}
