/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/16/25
 * Description: Implements a program that reads
 * PPM files and creates a flat 2D array of
 * pixel structs.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile;
  infile = fopen(filename, "r"); // relative path name of file, read mode (textbook)
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    return NULL; // specification requires returning NULL if file can't be loaded
  }

  struct ppm_pixel *pixels;
  pixels = malloc(sizeof(struct ppm_pixel) * (*w) * (*h));
  if (!pixels) {
    printf("Error: malloc failed\n");
    return NULL; // specification requires returning NULL if memory can't be allocated
  }

  // read header lines (inflexible, but one comment is valid assumption under specs)
  char header[256];
  fgets(header, 255, infile); // gets magic number
  printf("%s", header);
  fgets(header, 255, infile); // gets comment
  printf("%s", header);
  fgets(header, 255, infile); // gets dimensions
  printf("%s", header);
  fgets(header, 255, infile); // gets maxval
  printf("%s", header);

  for (int ch = fgetc(infile), i = 0; ch != EOF; ch = fgetc(infile), i++) {
    printf("i: %d\tch: %d\n", i, ch);
    // TODO: assignment is not working, fix!
    if (i % 3 == 0) pixels[i / 3].red = ch;
    else if (i % 3 == 1) pixels[i / 3].green = ch;
    else if (i % 3 == 2) pixels[i / 3].blue = ch;
  }
  return pixels;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
