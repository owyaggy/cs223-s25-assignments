#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 32

int main()
{
    int boolean;
    int number;
    char **adjectives;
    printf("Boolean: ");
    scanf("%d", &boolean);
    printf("Number: ");
    scanf("%d", &number);
    adjectives = malloc(sizeof(char*) * number);
    for (int i = 0; i < number; i++) {
        printf("Adjective: ");
        adjectives[i] = malloc(sizeof(char) * MAXSIZE);
        scanf("%s", adjectives[i]);
    }
    char* bool_string;
    if (boolean == 1) {
        bool_string = "true";
    } else {
        bool_string = "false";
    }
    if (number > 1) {
        printf("You are the most ");
        for (int i = number - 1; i > 0; i--) {
            printf("%s, ", adjectives[i]);
        }
        printf("and %s person that I know and you know that its %s!\n", adjectives[0], bool_string);     
    } else {
        printf("You are the most %s person that I know and you know that its %s!\n", adjectives[0], bool_string);
    }
    for (int i = 0; i < number; i++) {
        free(adjectives[i]);
    }
    free(adjectives);
    return 0;
}
