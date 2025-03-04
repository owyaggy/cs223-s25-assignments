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
  
  // converting integer to binary
  printf("0b ");
  unsigned int mask;
  mask = 0x80000000;
  for (int i = 0; i < 32; i++) {
    int result;
    result = (n & mask) >> (31 - i);
    printf("%d", result);
    if (i % 4 == 3) printf(" ");
    mask = mask >> 1;
  }
  return 0;
}