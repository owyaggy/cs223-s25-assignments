// Authors: Owen and Lina
// Date: 2/18/25
// Description: Stores a given string in a 2D array
// where the string is written across the top and
// bottom rows, as well as the main diagonal connecting
// the top-left and bottom-right corners

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
  char str[32];
  printf("Enter a string:");
  scanf("%s",str);
  int len = strlen(str);
  char* array = malloc(sizeof(char)*len*len);
  for (int i = 0; i<len; i++){
    if (i == 0 || i == len-1){
      for (int j = 0; j < len; j++){
        array[i*len +j] = str[j];
        printf("%c ", str[j]);
      }
      printf("\n");
    }
    else{
      for (int j = 0; j < len; j++){
        if (i ==j){
          array[i*len+j]= str[j];
          printf("%c ", str[j]);
        }
        else{
          printf("  ");
        }
      }
      printf("\n");
    }
  }
  free(array);
  return 0;
}