// Owen & Gabby
// J03
// 3/4/25

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc == 1) {
    printf("Usage: ./int2hex\n");
    exit(1);
  }
  int n;
  n = atoi(argv[1]);
  
  // converting integer to hexadecimal
  printf("0x ");
  unsigned int mask;
  mask = 0xF0000000; // is this right?
  for (int i = 0; i < 8; i++) {
    int result;
    result = (n & mask) >> ((7 - i) * 4); // or is right?(!)
    char str[16] = "0123456789ABCDEF";
    printf("%c", str[result]);
    if (i % 2 == 1) printf(" ");
    mask = mask >> 4;
  }
  printf("\n");

  // converting integer to binary
  printf("0b ");
  mask = 0x80000000;
  for (int i = 0; i < 32; i++) {
    int result;
    result = (n & mask) >> (31 - i);
    printf("%d", result);
    if (i % 4 == 3) printf(" ");
    mask = mask >> 1;
  }
  printf("\n");
  return 0;
}