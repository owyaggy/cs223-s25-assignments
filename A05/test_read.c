/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/16/25
 * Description: Calls a function to read the
 * contents of a ppm file.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main() {
  int w, h;
  w = h = 4;
  char filename[64];
  strncpy(filename, "feep-raw.ppm", 64);
  struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

  // todo: print out the grid of pixels
  printf("Testing file %s: %d %d\n", filename, w, h);
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      printf("(%3d,%3d,%3d) ", pixels[i*w + j].red, pixels[i*w + j].green, pixels[i*w + j].blue);
    }
    printf("\n");
  }

  free(pixels);
  return 0;
}

