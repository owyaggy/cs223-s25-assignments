/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/18/25
 * Description: Takes a PPM image as a command
 * line argument and displays it as ASCII art.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char *argv[]) {
  // get raster
  struct ppm_pixel *pixels;
  int w, h;
  pixels = read_ppm(argv[1], &w, &h);
  printf("Reading %s with width %d and height %d\n", argv[1], w, h);
  
  // create symbol table
  char symbols[11];
  strcpy(symbols, "@#\%*o;:,. ");

  // print ascii art
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      float intensity;
      intensity = (float) (1.0/3) * ((pixels[i*w+j].red) + (pixels[i*w+j].green) + (pixels[i*w+j].blue));
      int intensity_idx = intensity / 26; // what happens here
      printf("%c", symbols[intensity_idx]);
    }
    printf("\n");
  }
  free(pixels);
  return 0;
}
