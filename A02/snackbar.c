/***************************************************
 * Author: Owen Yaggy
 * Implements a snackbar simulator built with a struct
 */
#include <stdio.h>
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int quantity;
};

int main() {
  float money; // variable to hold user input of money

  // setup snack bar
  struct snack *snackbar[4];
  snackbar[0] = malloc(sizeof(struct snack));
  strcpy(snackbar[0]->name, "Twix");//, size_t=32);
  snackbar[0]->cost = 2.50;
  snackbar[1]->quantity = 6;
  strcpy(snackbar[1]->name, "Gum");
  snackbar[1]->cost = 1.50;
  snackbar[1]->quantity = 2;
  strcpy(snackbar[2]->name, "Skittles");
  snackbar[2]->cost = 3.0;
  snackbar[2]->quantity = 0;
  strcpy(snackbar[3]->name, "Ice Cream");
  snackbar[3]->cost = 7.50;
  snackbar[3]->quantity = 3;
  
  // prompt user
  printf("Welcome to Steven Struct's Snack Bar.\n\n");
  printf("How much money do you have? ");
  scanf("%f", &money);
  printf("\n\n");

  // show user options
  for (int i=0; i < sizeof(snackbar); i++) {
    printf("%d) %-21scost: $%-9.2fquantity: %d", snackbar[i].name, snackbar[i].cost, snackbar[i].quantity);
  }
  return 0;
}
