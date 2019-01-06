#include <stdio.h>

// This will generate a warning because '\c' is an unkown escape sequence
int main(int argc, char* argv[])
{
    printf("hello, world\n");
    printf("testing....");
    printf("\n");
    printf("\c");
    printf("\n");

    return 0;
}
