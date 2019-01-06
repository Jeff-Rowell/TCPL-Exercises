#include <stdio.h>

/* prints a horizontal histogram of the lengths of the words input */
int main(int argc, char* argv[])
{
    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n' || c == ' ' || c == '\t')
        {
            printf("\n");
        }
        else
            printf("*");
    }

    return 0;
}