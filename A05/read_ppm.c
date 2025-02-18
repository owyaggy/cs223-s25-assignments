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
  infile = fopen(filename, "rb"); // relative path name of file, read binary mode
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
  fgets(header, 255, infile); // gets comment
  fgets(header, 255, infile); // gets dimensions
  fgets(header, 255, infile); // gets maxval

  // get raster
  fread(pixels, sizeof(struct ppm_pixel), (*w)*(*h), infile);

  fclose(infile);
  return pixels;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
