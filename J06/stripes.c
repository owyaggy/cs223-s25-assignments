#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"

struct thread_data {
  int starti;
  int endi;
  int width;
  int height;
  struct ppm_pixel color;
  struct ppm_pixel* image;
};

void *start(void* userdata) {
  struct thread_data* data = (struct thread_data*) userdata;
  // todo: your code here
  srand((unsigned int) pthread_self()); // uses thread id as seed
  data->color.red = rand() % 255;
  data->color.green = rand() % 255;
  data->color.blue = rand() % 255;
  printf("Thread is coloring rows %d to %d with color: %d %d %d\n", data->starti, data->endi, data->color.red, data->color.green, data->color.blue);
  for (int i = data->starti; i < data->endi; i++) { // y indices
    for (int j = 0; j < data->width; j++) { // x indices
      //data->image[j * data->width + i] = (struct ppm_pixel) data->image[j * data->width + i];
      data->image[j * data->width + i].red = data->color.red;
      data->image[j * data->width + i].green = data->color.green;
      data->image[j * data->width + i].blue = data->color.blue;
    }
  }
  return 0;
}

int main(int argc, char** argv) {

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);

  int size = 1024;
  struct ppm_pixel* image = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel* colors = malloc(sizeof(struct ppm_pixel) * N);
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  struct thread_data* data = malloc(sizeof(struct thread_data) * N);

  for (int i = 0; i < N; i++) {
    data[i].starti = i * (size / N);
    data[i].endi = data[i].starti + (size / N);
    data[i].image = image;
    data[i].width = size;
    data[i].height = size;
    pthread_create(&threads[i], NULL, start, &data[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("stripes.ppm", image, size, size);
  free(image);
  free(colors);
  free(threads);
  free(data);
}
