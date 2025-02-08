/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/7/2025
 * Description: Implements a snackbar emulator
 * that allows the user to add snacks
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

// define a snack struct
struct snack {
  char name[32];
  float cost;
  int quantity;
};

int main() {
  int count;
  struct snack *snackbar;
  printf("Enter a number of snacks: ");
  scanf("%d", &count);
  snackbar = malloc(sizeof(struct snack) * count);

  // check malloc
  if (snackbar == NULL) {
    printf("Error: malloc failed\n");
    exit(1);
  }

  // prompt for attributes
  for (int i = 0; i < count; i++) {
    printf("Enter a name: ");
    scanf("%s", snackbar[i].name);
    printf("Enter a cost: ");
    scanf("%f", &snackbar[i].cost);
    printf("Enter a quantity: ");
    scanf("%d", &snackbar[i].quantity);
  }
  
  printf("\nWelcome to Dynamic Donna's Snack Bar.\n\n");

  // show user options
  for (int i=0; i < count; i++) {
    printf("%d) %-12scost: $%-9.2fquantity: %d\n", i, snackbar[i].name, snackbar[i].cost, snackbar[i].quantity);
  }

  free(snackbar);

  return 0;
}
