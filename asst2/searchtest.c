#include <stdio.h>
#include <stdlib.h>
// #include "multitest.h"

void generateArray(int* array, int length) {
  int i;
  for(i = 0; i < length; i++)
  {
    array[i] = i;
  }
  int minScrambles = ((length *  3) + (4 - 1)) / 4;
  printf("Let's scramble %d out of %d integers.\n", minScrambles, length);
  for(i = 0; i < minScrambles; i++)
  {
    int swapIndex = (rand() % length);
    array[swapIndex] = i;
    array[i] = swapIndex;
  }
}

int main(int argc, char** argv) {
  int* array0 = (int*) malloc(250 * sizeof(int));
  if(array0 == NULL)
  {
    printf("Memory allocation failed :()\n");
    return -1;
  }
  generateArray(array0, 250);
  // printf("array0: %d %d %d %d ...\n", array0[0], array0[1], array0[2], array0[3]);
  free(array0);


  // int array1[300] = {0};
  // int array2[500] = {0};
  // int array3[1000] = {0};
  // int array4[2000] = {0};
  // int array5[4000] = {0};
  // int array6[8000] = {0};
  // int array7[16000] = {0};
  // int array8[32000] = {0};




}
