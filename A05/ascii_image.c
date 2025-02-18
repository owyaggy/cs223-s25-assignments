/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/18/25
 * Description: Takes a PPM image as a command
 * line argument and displays it as ASCII art.
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char *argv[]) {
  // get dimensions
  FILE *infile;
  infile = fopen(argv[1], "rb");
  if (!infile) {
    printf("Error - file not found\n");
    exit(1);
  }
  int w, h;
  int *dimensions;
  dimensions = read_header(infile);
  fclose(infile);
  w = dimensions[0];
  h = dimensions[1];
  free(dimensions);

  // get raster
  struct ppm_pixel *pixels;
  pixels = read_ppm(argv[1], w, h);
  printf("Reading %s with width %d and height %d", argv[1], w, h);
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      // assign intensity for each pixel
    }
  }
  free(pixels);
  return 0;
}
