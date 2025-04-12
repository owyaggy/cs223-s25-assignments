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
   outfile = fopen(filename, "wb");
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
   fwrite(pixels, sizeof(struct ppm_pixel), w*h, outfile);
   fclose(outfile);
 }
 
 void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
 
 }
 