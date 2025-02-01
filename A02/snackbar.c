/***************************************************
 * Author: Owen Yaggy
 * Implements a snackbar simulator built with a struct
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define a snack struct
struct snack {
  char name[32];
  float cost;
  int quantity;
};

int main() {
  float money; // variable to hold user input of money
  int choice; // variable to hold user's choice of snack

  // setup snack bar
  struct snack *snackbar;
  snackbar = malloc(sizeof(struct snack) * 4);
  strncpy(snackbar[0].name, "Twix", 32);
  snackbar[0].cost = 2.50;
  snackbar[0].quantity = 6;
  strncpy(snackbar[1].name, "Gum", 32);
  snackbar[1].cost = 1.50;
  snackbar[1].quantity = 2;
  strncpy(snackbar[2].name, "Skittles", 32);
  snackbar[2].cost = 3.0;
  snackbar[2].quantity = 0;
  strncpy(snackbar[3].name, "Ice Cream", 32);
  snackbar[3].cost = 7.50;
  snackbar[3].quantity = 3;
  
  // prompt user
  printf("Welcome to Steven Struct's Snack Bar.\n\n");
  printf("How much money do you have? ");
  scanf("%f", &money);
  printf("\n");

  // show user options
  for (int i=0; i < sizeof(snackbar) / 2; i++) {
    printf("%d) %-12scost: $%-9.2fquantity: %d\n", i, snackbar[i].name, snackbar[i].cost, snackbar[i].quantity);
  }

  // ask for choice
  printf("\nWhat snack would you like to buy? [0, 1, 2, 3] ");
  scanf("%d", &choice);

  // logic and response
  if (snackbar[choice].quantity == 0) {
    printf("Sorry, we are out of %s\n\n", snackbar[choice].name);
  } else if (money < snackbar[choice].cost) {
    printf("You can't afford it!\n\n");
  } else {
    printf("You bought %s\nYou have $%.2f left\n\n", snackbar[choice].name, money - snackbar[choice].cost);
  }

  // free allocated memory
  free(snackbar);

  return 0;
}
