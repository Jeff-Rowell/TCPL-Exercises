#include <stdio.h>

int main(int argc, char* argv[])
{
    int c, nl, nt, nb;
    nl = 0;
    nt = 0;
    nb = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            nl++;
        if (c == '\t')
            nt++;
        if (c == ' ')
            nb++;
    }
    printf("Blanks: %d\nTabs: %d\nLines: %d\n", nb, nt, nl);

    return 0;
}
