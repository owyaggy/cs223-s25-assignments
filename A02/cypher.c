/***************************************************
 * Author: Owen Yaggy
 * Implements a basic shift cipher
 */
#include <stdio.h>
#include <string.h>

int main() {
  char plaintext[64]; // variable for user word input
  int shift; // variable for user shift input

  // prompt user
  printf("Enter a word: ");
  scanf("%s", plaintext);
  printf("Enter a shift: ");
  scanf("%d", &shift);

  // shift each character
  for (int i=0; i < strlen(plaintext); i++) {
    // shift to [0, 26) range, apply shift, find remainder with 26
    plaintext[i] = (plaintext[i] - 97  + shift) % 26;
    // if remainder negative, add 26, in both cases shift back to [97, 123) range
    plaintext[i] = (plaintext[i] < 0) ? plaintext[i] + 26 + 97 : plaintext[i] + 97;
  }

  // show user result
  printf("Your cypher is %s\n", plaintext);

  return 0;
}
