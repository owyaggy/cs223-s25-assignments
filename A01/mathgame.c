/***************************************************
 * mathgame.c
 * Author: Owen Yaggy
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int rounds, correct;
  correct = 0;
  printf("Welcome to Math Game!\nHow many rounds do you want to play? ");
  scanf("%d", &rounds);
  for (int i=0; i<rounds; i++) {
    int num1, num2, response;
    srand(time(NULL)); // use current time as seed for random generator (cpprefernce.com)
    num1 = rand() % 9 + 1;
    num2 = rand() % 9 + 1;
    printf("\n\n%d + %d = ? ", num1, num2);
    scanf("%d", &response);
    if (num1 + num2 == response) {
      printf("Correct!");
      correct++;
    } else {
      printf("Incorrect :(");
    }
  }
  printf("\nYou answered %d/%d correctly.", correct, rounds);
  return 0;
}
