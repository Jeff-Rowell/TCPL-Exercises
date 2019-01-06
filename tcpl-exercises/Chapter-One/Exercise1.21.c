#include <stdio.h>
#define TABSTOP 8

void printBlanks(int num_blanks);

int main(int argc, char* argv[])
{
    int c, i, blanks = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            ++blanks; // blanks is 1
            while ((c = getchar()) == ' ')
            {
                ++blanks;
                if (blanks == TABSTOP)
                {
                    putchar('\t');
                    blanks = 0;
                }
            }
            printBlanks(blanks);
            if (c != ' ')
            {
                putchar(c);
            }
        }
        else
        {
            putchar(c);
        }
    }

    return 0;
}

void printBlanks(int num_blanks)
{
    int i;

    for (i = 0; i < num_blanks; ++i)
    {
        putchar(' ');
    }
}







