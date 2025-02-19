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

// read the header lines of a PPM file
// infile: an opened file stream
// returns an array of integer dimensions (width then height)
// NOTE: Caller is responsible for freeing the returned array
int* read_header(FILE *infile) {
  int *dimensions;
  dimensions = malloc(sizeof(int) * 2);
  if (!dimensions) {
    printf("Error: malloc failed!\n");
    exit(1);
  }
  // read header lines (inflexible, but one comment is valid assumption under specs)
  char header[256];
  fgets(header, 255, infile); // gets magic number
  fgets(header, 255, infile); // gets comment
  fgets(header, 255, infile); // gets dimensions
  // split dimensions into width and height
  char *dimension_chars[2];
  dimension_chars[0] = strtok(header, " ");
  dimension_chars[1] = strtok(NULL, " ");
  dimensions[0] = atoi(dimension_chars[0]);
  dimensions[1] = atoi(dimension_chars[1]);
  fgets(header, 255, infile); // gets maxval
  return dimensions;
}

// Choose *one* to implement (do not remove the other one!)

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
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
