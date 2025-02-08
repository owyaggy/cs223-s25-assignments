/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/7/2025
 * Description: Implements a program that
 * randomly places a Wampus within a NxM grid.
 * Then, fills the remaining cells with their
 * Manhattan distance from the Wampus.
 * 
 * NOTE: In the assignment, two different
 * specifications are listed. First, it says to
 * prompt the user for grid width and height.
 * Second, it says to use a command line arg.
 * I interpreted these as contradictory, and
 * chose to go with the first specification.
 ---------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
  // initialize variables
  int rows;
  int cols;
  int wampus_i;
  int wampus_j;
  printf("Number of rows: ");
  scanf("%d", &rows);
  printf("Number of columns: ");
  scanf("%d", &cols);

  srand(time(NULL)); // use current time as seed for random generator (cpprefernce.com)

  // set random wampus location
  wampus_i = rand() % rows;
  wampus_j = rand() % cols;

  char *grid; // intialize array of pointers to chars

  // allocate one char per grid space
  grid = malloc(sizeof(char) * (rows * cols));

  // check malloc
  if (grid == NULL) {
    printf("Error: malloc failed\n");
    exit(1);
  }

  // calculate manhattan distances
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // +48 because ascii value for 0 is 48!
      grid[i*cols + j] = abs(i - wampus_i) + abs(j - wampus_j) + 48;
    }
  }

  // indicate wampus location
  grid[wampus_i*cols + wampus_j] = 'W';

  // print each grid space
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%c ", grid[i*cols + j]);
    }
    printf("\n");
  }

  free(grid); // if you malloc, set it free
  
  return 0;
}
