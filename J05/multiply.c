#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100

// your code here
struct data {
  int startIndex;
  int endIndex;
  int* matrix;
  int* vector;
  int* result;
};

void* row_section(void* data) {
  struct data* info = data;
  for (int i = info->startIndex; i < info->endIndex; i++) {
    for (int j = 0; j < SIZE; j++) {
      info->result[i] += info->matrix[i*SIZE + j] * info->vector[j];
    }
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int M[SIZE*SIZE];
  int u[SIZE];
  int result[SIZE];
  int result_threads[SIZE] = {0};
   
  for (int i = 0; i < SIZE; i++) {
    u[i] = rand() % 10 - 5;
    result[i] = 0;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int value = rand() % 10 - 5;
      M[i*SIZE + j] = value;
      result[i] += value * u[j];
    }
  }

  // TODO: Implement your thread solution here
  printf("Test with 4 threads\n");

  pthread_t threads[4];
  struct data info[4];
  int subsize = SIZE/4;
  for (int i = 0; i < 4; i++) {
    info[i].matrix = M;
    info[i].vector = u;
    info[i].startIndex = subsize * i;
    info[i].endIndex = info[i].startIndex + subsize;
    info[i].result = result_threads;
    pthread_create(&threads[i], NULL, row_section, (void*) &info[i]);
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }

  int error = 0;
  for (int i = 0; i < SIZE; i++) {
    error += abs(result[i] - result_threads[i]);
  }
  printf("Error between ground truth and multithreaded version: %d\n", error);

  return 0;
}
