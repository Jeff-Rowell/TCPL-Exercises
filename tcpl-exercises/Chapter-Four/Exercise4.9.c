#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>   /* for fmod(a, b) */
#include <string.h> /* for tolower(a) */

#define MAXOP 100       /* max size of operand or operator */
#define MAXVAL 100      /* maximum depth of val stack */
#define NUMBER '0'      /* signal that a number was found */
#define NEG_NUMBER '1'  /* signal that a negative number was found */
#define VARIABLE '2'    /* signal that a variable name was found */

#define BUFSIZE 100
#define MAX_VARS 26

/* Exercise 4-9
 *
 * Our getch and ungetch do not handle a pushed-back EOF correctly. Decide
 * what their properties ought to be if an EOF is pushed back, then implement your design.
 *
 * => If an EOF (-1) is received we need to make sure that we do not attempt to put it in buf, because buf
 *    is an array of type char and chars are defined as 0 or positive. Since buf is only accessed by
 *    ungetch, we need to make sure that we ignore EOF when received and don't add it to buf.
 */

int getch(void);
void ungetch(int);
void ungets(char*);

char buf[BUFSIZE];              /* buffer for ungetch */
int bufp = 0;                   /* next free position in buf */

int main(int argc, char* argv[])
{
    char c;
    printf("Calling getch();\nPlease enter EOF (^D): ");
    c = getch();
    printf("\n(c == EOF) = %d", (c == EOF));
    printf("\nbufp = %d\nCalling ungetch(%c);\n", bufp, c);
    ungetch(c);
    printf("bufp = %d\n", bufp, EOF);

    return 0;
}

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else if (c != EOF)
        buf[bufp++] = c;
}
