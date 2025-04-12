#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  // todo: your code here
  // compute image
  struct ppm_pixel *pixels;
  int w, h;
  int threshold = 200;
  int blur_box = 50;
  int blur_side = sqrt(blur_box);
  int brightness;
  pixels = read_ppm("earth-small.ppm", &w, &h);
  printf("w: %d, h: %d\n", w, h);
  struct ppm_pixel *filter_area;
  filter_area = malloc(sizeof(struct ppm_pixel) * w * h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      brightness = (pixels[i*w + j].red + pixels[i*w + j].green + pixels[i*w + j].blue) / 3;
      if (brightness >= threshold) {
        //printf("(%d, %d) brightness : %d\n", i, j, brightness);
        filter_area[i*w + j].red = pixels[i*w + j].red;
        filter_area[i*w + j].green = pixels[i*w + j].green;
        filter_area[i*w + j].blue = pixels[i*w + j].blue;
      } else {
        filter_area[i*w + j].red = 0;
        filter_area[i*w + j].green = 0;
        filter_area[i*w + j].blue = 0;
      }
    }
  }
  write_ppm("filter_area.ppm", filter_area, w, h);
  struct ppm_pixel *blur;
  blur = malloc(sizeof(struct ppm_pixel) * w * h);
  int top; // y coordinate of top pixel used in blur box
  int bottom; // y coordinate of bottom pixel used in blur box
  int left; // x coordinate of leftmost pixel used in blur box
  int right; // x coordinate of rightmost pixel used in blur box
  int total_red;
  int total_green;
  int total_blue;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      // set parameters of blur box
      top = i - (blur_side/2);
      if (top < 0) {
        top = 0;
      }
      bottom = i + (blur_side/2);
      if (top >= h) {
        top = h - 1;
      }
      left = j - (blur_side/2);
      if (left < 0) {
        left = 0;
      }
      right = j + (blur_side/2);
      if (right >= w) {
        right = w - 1;
      }
      total_red = 0;
      total_green = 0;
      total_blue = 0;
      for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
          total_red += filter_area[y*w + x].red;
          total_green += filter_area[y*w + x].green;
          total_blue += filter_area[y*w + x].blue;
        }
      }
      blur[i*w + j].red = total_red / blur_box;
      blur[i*w + j].green = total_green / blur_box;
      blur[i*w + j].blue = total_blue / blur_box;
      if (blur[i*w + j].red > 255 || blur[i*w + j].green > 255 || blur[i*w + j].blue > 255) {
        printf("blur too big\n");
        printf("total red: %d ", total_red);
        printf("q: %d ", blur[i*w + j].red);
        printf("total green: %d ", total_green);
        printf("q: %d ", blur[i*w + j].green);
        printf("total blue: %d ", total_blue);
        printf("q: %d\n", blur[i*w + j].blue);
      }
      // add blurred pixel to original pixel
      pixels[i*w + j].red += blur[i*w + j].red;
      pixels[i*w + j].green += blur[i*w + j].green;
      pixels[i*w + j].blue += blur[i*w + j].blue;
      if (pixels[i*w + j].red > 255) {
        printf("red over");
        pixels[i*w + j].red = 255;
      }
      if (pixels[i*w + j].green > 255) {
        printf("green over");
        pixels[i*w + j].green = 255;
      }
      if (pixels[i*w + j].blue > 255) {
        printf("blue over");
        pixels[i*w + j].blue = 255;
      }
    }
  }
  write_ppm("blur.ppm", blur, w, h);
  write_ppm("glow.ppm", pixels, w, h);
  free(filter_area);
  free(pixels);
  free(blur);
}