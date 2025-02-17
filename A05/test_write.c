/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/16/25
 * Description: Implements a test that reads in
 * a PPM file, writes it to a new PPM file, reads
 * in the new file, and prints its contents.
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

void test_file(const char *filename, struct ppm_pixel* pixels, const int w, const int h) {
  printf("Testing file %s: %d %d\n", filename, w, h);
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      printf("(%3d,%3d,%3d) ", pixels[i*w + j].red, pixels[i*w + j].green, pixels[i*w + j].blue);
    }
    printf("\n");
  }
}

int main(int argc, char** argv) {
  int w, h;
  w = 4;
  h = 4;
  char in_filename[64];
  strcpy(in_filename, "feep-raw.ppm");
  struct ppm_pixel* pixels = read_ppm(in_filename, &w, &h);

  // test writing the file to test.ppm, reload it, and print the contents
  write_ppm("test.ppm", pixels, w, h);
  struct ppm_pixel* new_pixels = read_ppm("test.ppm", &w, &h);
  test_file("test.ppm", new_pixels, w, h);

  free(pixels);
  free(new_pixels);
  return 0;
}
