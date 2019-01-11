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

/* Exercise 4-6
 *
 * Add commands for handling variables. (It's easy to provide twenty-six variables
 * with single-letter names.) Add a variable for the most recently printed value.
 */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int size(void);
double peek(void);
void duplicate(void);
void swap(void);
void clear(void);
int is_variable(int);
double resolve_variable(char);

char buf[BUFSIZE];              /* buffer for ungetch */
int bufp = 0;                   /* next free position in buf */
int sp = 0;                     /* next free stack position */
double val[MAXVAL];             /* value stack */
double* valp = val;
int var_count = 0;              /* next free variable name */
double variable_vals[MAX_VARS]; /* values of variable names */
const char* vars = "abcdefghijklmnopqrstuvwxyz";

/* reverse Polish calculator */
int main(int argc, char* argv[])
{
    int type;
    double op2, temp;
    char s[MAXOP], c;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case NEG_NUMBER:
                if (is_variable(s[0]))
                    push(-resolve_variable(s[0]));
                else
                    push(-atof(s));
                break;
            case VARIABLE:
                push(resolve_variable(s[0]));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case '\n':
                temp = pop();
                variable_vals[var_count++] = temp;
                printf("\t%.8g\tstored in variable %c\n", temp, vars[var_count - 1]);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
    {
        sp++;
        *(valp++) = f;
    }
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
    {
        sp--;
        return *(--valp);
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* peek: get the top element of the stack without removing it. */
double peek(void)
{
    return *(valp - 1);
}

/* duplicate: duplicates the top element on the stack. */
void duplicate(void)
{
    push(peek());
}

/* swap: swaps the top two elements on the stack. */
void swap(void)
{
    double item1 = pop(), item2 = pop();
    push(item1);
    push(item2);
}

/* clear: removes all elements from the stack. */
void clear(void)
{
    valp = val;
    sp = 0;
}

/* size: get the size of the stack */
int size(void)
{
    return valp - val;
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c, temp;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (is_variable(c))
    {
        return VARIABLE;
    }
    if (!isdigit(c) && c != '.')
    {
        if (c == '\n')
            return c;
        if (isdigit(temp = getch()) || is_variable(temp))
        {
            s[0] = temp;
            i = 0;/* collect integer part */
            while (isdigit(s[++i] = c = getch()))
                ;
            if (c == '.') /* collect fraction part */
                while (isdigit(s[++i] = c = getch()))
                    ;
            s[i] = '\0';
            return NEG_NUMBER;
        }
        else
        {
            ungetch(temp);
            return c; /* not a number */
        }
    }
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
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
    else
        buf[bufp++] = c;
}

/* is_variable: checks if a given item is a variable name. */
int is_variable(int item)
{
    return ((item >= 'a' && item <= 'z') || (item >= 'A' && item <= 'Z')) ? 1 : 0;
}

/* resolve_variable: given a variable name, returns its corresponding value. */
double resolve_variable(char c)
{
    double result = 0.0;
    for (int i = 0; i < MAX_VARS; i++)
    {
        if (vars[i] == tolower(c))
        {
            result = variable_vals[i];
        }
    }
    return result;
}
