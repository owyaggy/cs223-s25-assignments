/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/18/25
 * Description: Reads in a PPM file and "glitches"
 * it, saving the odified PPM in a new file with
 * the suffix "-glitch".
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

void simple_shift(struct ppm_pixel *pixels, int w, int h);
void color_bleed(struct ppm_pixel *pixels, int w, int h, char color);
void grid_filters(struct ppm_pixel *pixels, int w, int h);

int main(int argc, char *argv[]) {
  // get raster
  struct ppm_pixel *pixels;
  int w, h;
  pixels = read_ppm(argv[1], &w, &h);
  printf("Reading %s with width %d and height %d\n", argv[1], w, h);

  // modify image
  //simple_shift(pixels, w, h);
  //color_bleed(pixels, w, h, 'r');
  //color_bleed(pixels, w, h, 'g');
  //color_bleed(pixels, w, h, 'b');
  grid_filters(pixels, w, h);
  
  // write file
  char *old_filename = strtok(argv[1], ".");
  if (strlen(old_filename) > 52) {
    printf("Filename is too long! Exiting.\n");
    exit(1);
  }
  char new_filename[64];
  sprintf(new_filename, "%s-glitch.ppm", old_filename);
  printf("Writing file %s\n", new_filename);
  write_ppm(new_filename, pixels, w, h);
  free(pixels);
  return 0;
}

void simple_shift(struct ppm_pixel *pixels, int w, int h) {
  srand(time(NULL));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      pixels[i*w+j].red = pixels[i*w+j].red << (rand() % 2);
      pixels[i*w+j].green = pixels[i*w+j].green << (rand() % 2);
      pixels[i*w+j].blue = pixels[i*w+j].blue << (rand() % 2);
    }
  }
}

void color_bleed(struct ppm_pixel *pixels, int w, int h, char color) {
  for (int i = 1; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (color == 'r' && pixels[(i-1)*w+j].red > pixels[i*w+j].red) {
        pixels[i*w+j].red = 0.92 * (pixels[(i-1)*w+j].red);
      } else if (color == 'g' && pixels[(i-1)*w+j].green > pixels[i*w+j].green) {
        pixels[i*w+j].green = 0.92 * (pixels[(i-1)*w+j].green);
      } else {
        pixels[i*w+j].blue = 0.92 * (pixels[(i-1)*w+j].blue);
      }
    }
  }
}

void grid_filters(struct ppm_pixel *pixels, int w, int h) {
  int rgbs[21] = {255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0, 255, 0, 255, 0, 255, 0, 0, 0, 0};
  srand(time(NULL));
  int rows = rand() % 40 + 10;
  if (rows >= h*0.35) rows = h / 5;
  int *filters;
  int row_sections;
  filters = NULL;
  int filter_idx;
  int filter;
  // iterate thru pixels
  for (int i = 0; i < h; i++) { // each row
    if (i % (h / rows) == 0) { // if time to change filters
      free(filters); // get rid of old filters
      row_sections = rand() % 30 + 10; // decide how many filters per row
      if (row_sections >= w*0.35) row_sections = w / 5;
      filters = malloc(sizeof(int) * row_sections); // allocate filter space
      if (!filters) {
        printf("Error: malloc failed!\n");
        exit(1);
      }
      for (int k = 0; k < row_sections; k++) { // set each filter
        filters[k] = rand() % 7;
      }
    }
    filter_idx = 0;
    for (int j = 0; j < w; j++) { // each col
      if (j % (w / row_sections) == 0 && j != 0) filter_idx++;
      filter = filters[filter_idx % row_sections];
      if (filter == 6) {
        pixels[i*w+j].red *= 0.35;
        pixels[i*w+j].green *= 0.35;
        pixels[i*w+j].blue *= 0.35;
      } else {
        pixels[i*w+j].red = pixels[i*w+j].red + (0.2 * (rgbs[3*filter] - pixels[i*w+j].red));
        pixels[i*w+j].green = pixels[i*w+j].green + (0.2 * (rgbs[3*filter+1] - pixels[i*w+j].green));
        pixels[i*w+j].blue = pixels[i*w+j].blue + (0.2 * (rgbs[3*filter+2] - pixels[i*w+j].blue));
      }
    }
  }
  free(filters);
}