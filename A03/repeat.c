/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/7/25
 * Description: Asks a user for a string `s` and
 an integer `n` and then creates a new string
 that repeats `s` `n` times.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char s[32]; // user input string
  int count; // user input count (n)
  printf("Enter a word: ");
  scanf("%s", s);
  printf("Enter a count: ");
  scanf("%d", &count);

  char *output;
  output = NULL;
  output = malloc((sizeof(char) * strlen(s)) * count + 1);

  // check for successful malloc
  if (output == NULL) {
    printf("Error: malloc failed\n");
    exit(1);
  }

  // give one instance of s to output
  strcpy(output, s);

  // concatenate n - 1 times
  for (int i = 1; i < count; i++) {
    strcat(output, s);
  }

  printf("Your word is %s\n", output);

  free(output);

  return 0;
}