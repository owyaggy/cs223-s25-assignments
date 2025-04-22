#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    char c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", (c >> 1) & 0b01111111);
        c = fgetc(fp);
    }
    fclose(fp);
    return 0;
}
