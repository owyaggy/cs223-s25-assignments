#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
    FILE *infile;
    infile = fopen(filename, "rb"); // relative path name of file, read binary mode
    if (infile == NULL) {
      printf("Error: unable to open file %s\n", filename);
      return NULL; // specification requires returning NULL if file can't be loaded
    }

    // read header (function returns pointer to dimensions array)
    int *dimensions;
    dimensions = read_header(infile);
    *w = dimensions[0];
    *h = dimensions[1];
    free(dimensions);

    struct ppm_pixel *pixels;
    pixels = malloc(sizeof(struct ppm_pixel) * (*w) * (*h));
    if (!pixels) {
      printf("Error: malloc failed\n");
      return NULL; // specification requires returning NULL if memory can't be allocated
    }

    // get raster
    fread(pixels, sizeof(struct ppm_pixel), (*w)*(*h), infile);

    fclose(infile);
    return pixels;
    return NULL;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {

  return NULL;
}
