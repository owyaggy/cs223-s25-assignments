/***************************************************
 * mathgame.c
 * Author: Owen Yaggy
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int rounds, correct; // variables for # of rounds and # correct
  correct = 0;
  printf("Welcome to Math Game!\nHow many rounds do you want to play? ");
  scanf("%d", &rounds); // store user input in rounds variable
  for (int i=0; i<rounds; i++) { // ask math question for each round
    int num1, num2, response; // operands and user response
    srand(time(NULL)); // use current time as seed for random generator (cpprefernce.com)
    num1 = rand() % 9 + 1; // random number in range [1, 10)
    num2 = rand() % 9 + 1;
    printf("\n\n%d + %d = ? ", num1, num2);
    scanf("%d", &response); // store user input in response variable
    if (num1 + num2 == response) { // validate response
      printf("Correct!");
      correct++;
    } else {
      printf("Incorrect :(");
    }
  }
  printf("\nYou answered %d/%d correctly.\n", correct, rounds);
  return 0;
}
