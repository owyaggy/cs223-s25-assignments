// Owen & Gabby
// J03
// 3/4/25

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  if (argc == 1) {
    printf("Usage: ./hex2int\n");
    exit(1);
  }
  char *input = argv[1];
  if (strlen(input) <= 2) {
    printf("Please input a number beginning with 0x or 0b\n");
    exit(1);
  }

  char *token;
  int n;
  if (input[1] == 'x') {
    // converting from hexadecimal to decimal
    /* token = strtok(input, "0x");
    for (int i = 0; i < strlen(token); i++) {
      // if (strstr('a', tolower(token[i]))) {

      } else if (strstr('b', tolower(token[i]))) {

      } else if (strstr('c', tolower(token[i]))) {

      } || strstr('d', tolower(token[i])) || strstr('e', tolower(token[i])) || strstr('f', tolower(token[i]))) {

      } 
    } */
    token = input + 2;
    int result = 0;
    for (int i = 0; i < strlen(token); i++) {
      char c = tolower(token[i]); 
      int value;

      if (c >= '0' && c <= '9') {
        value = c - '0';
      } else if (c >= 'a' && c <= 'f') {
        value = c - 'a' + 10;
      } else {
        printf("Invalid hexadecimal character: %c\n", c);
        exit(1);
      }

      // Shift left by 4 bits 
      result = (result << 4) | value;
    }
    printf("%d\n", result);
  } else if (input[1] == 'b') {
    // converting from binary to decimal
    token = input + 2;
    int result = 0;
    for (int i = 0; i < strlen(token); i++) {
      char c = tolower(token[i]); 
      int value;

      if (c == '0') {
        value = 0;
      } else if (c == '1') {
        value = 1;
      } else {
        printf("Invalid hexadecimal character: %c\n", c);
        exit(1);
      }

      // Shift left by 1 bits 
      result = (result << 1) | value;
    }
    printf("%d\n", result);

  } else {
    printf("Not a valid input\n");
    exit(1);
  }
  return 0;
}
