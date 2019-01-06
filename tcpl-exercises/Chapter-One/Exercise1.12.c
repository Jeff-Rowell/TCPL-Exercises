#include <stdio.h>

int main(int argc, char* argv[])
{
    int c, wc;

    wc = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n' || c == '\t' || c == ' ')
        {
            printf("\n");
            ++wc;
        }
        else
        {
            putchar(c);
        }
    }
    printf("==========================\nTotal Count of Words: %d\n==========================\n", wc);

    return 0;
}



