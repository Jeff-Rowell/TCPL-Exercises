#include <stdio.h>
#define MAX_LEN 1000 /* the maximum length of the entire input line */
#define N 40 /* The folding threshold */

int getlinelength(char s[], int lim);

int main(int argc, char* argv[])
{
    int len; /* the current length of the line */
    char line[MAX_LEN]; /* the current line */

    int c, i, spacemarker = -1, column = 0;

    while ((len = getlinelength(line, MAX_LEN)) > 0) {
        if (len <= N)
            printf("%s\n", line);
        else {
            for (i = 0; (c = line[i]) != '0' && c != '\n'; ++i) {
                if (column > N) {
                    line[spacemarker] = '\n';
                    column = 1;
                }
                if (c == ' ' || c == '\t') {
                    spacemarker = i;
                    ++column;
                }
                else
                    ++column;
            }
            printf("%s\n", line);
        }
        column = 0;
    }

    return 0;
}

int getlinelength(char s[], int lim)
{
    int c,i;

    for (i = 0; i < lim && ( (c = getchar()) != EOF && c != '\n'); ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}
