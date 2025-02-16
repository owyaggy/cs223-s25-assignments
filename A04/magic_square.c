/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/14/25
 * Description: Implements a magic square detector
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int check_magic(const int *square, const int n) {
  // Find sum of first row
  int sum;
  sum = 0;
  for (int j = 0; j < n; j++) {
    sum += square[j];
  }

  // Compare with remaining rows
  for (int i = 1; i < n; i++) {
    int row_sum;
    row_sum = 0;
    for (int j = 0; j < n; j++) {
      row_sum += square[i*n + j];
    }
    if (row_sum != sum) {
      return 0;
    }
  }

  // compare with columns
  for (int j = 0; j < n; j++) {
    int col_sum;
    col_sum = 0;
    for (int i = 0; i < n; i++) {
      col_sum += square[i*n + j];
    }
    if (col_sum != sum) {
      return 0;
    }
  }

  // compare with main diagonals
  int diagonal_down_sum;
  int diagonal_up_sum;
  diagonal_down_sum = 0;
  diagonal_up_sum = 0;
  for (int i = 0; i < n; i++) {
    diagonal_down_sum += square[i*n + i];
    diagonal_up_sum += square[(n-1-i)*n + (n-1-i)];
  }
  if (diagonal_down_sum != sum || diagonal_up_sum != sum) {
    return 0;
  }

  // nothing left! return magic constant
  return sum;
}

int main() {
  // read in square size
  int n;
  scanf("%d", &n);
  scanf("%d", &n);

  // set up square data structure
  int *square;
  square = malloc(sizeof(int) * n * n);
  if (!square) {
    printf("Error: malloc failed!\n");
    exit(1);
  }
  
  // read in square
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf(" %d", &square[i*n + j]);
      printf("%-3d", square[i*n + j]);
    }
    printf("\n");
  }

  /* Check for magic */
  int result;
  result = check_magic(square, n);

  // show result
  if (result) {
    printf("M is a magic square (magic constant = %d)\n", result);
  } else {
    printf("M is NOT a magic square!\n");
  }

  // free
  free(square);
  return 0;
}
