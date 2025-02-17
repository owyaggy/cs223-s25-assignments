/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/16/25
 * Description: Implements a function that reads
 * in a PPM file and writes it to a file `test.ppm`
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  FILE *outfile;
  outfile = fopen(filename, "w");
  if (outfile == NULL) {
    printf("Error: unable to open outfile\n");
    exit(1);
  }

  // create header
  fprintf(outfile, "P6\n");
  fprintf(outfile, "# Created by GIMP version 2.10.24 PNM plug-in\n");
  fprintf(outfile, "%d %d\n", w, h);
  fprintf(outfile, "255\n");

  // create raster
  for (int i = 0; i < w*h*3; i++) {
    if (i % 3 == 0) fputc(pixels[i / 3].red, outfile);
    else if (i % 3 == 1) fputc(pixels[i / 3].green, outfile);
    else if (i % 3 == 2) fputc(pixels[i / 3].blue, outfile);
  }
  fclose(outfile);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
