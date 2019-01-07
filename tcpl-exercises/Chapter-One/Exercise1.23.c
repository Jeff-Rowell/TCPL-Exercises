#include <stdio.h>
#define MAXLINELENGTH 120

/* Exercise 1-23.
 *
 * Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments don't nest.
 */

int main(int argc, char* argv[])
{
    FILE *infp = fopen("program-in.txt","r");
    FILE *outfp = fopen("program-out.txt","w");

    int c, i, j, inside_quotes = 0, is_first_quote = 1;
    char ins[MAXLINELENGTH], out[MAXLINELENGTH], temp[MAXLINELENGTH];

    for (i = 0; i < MAXLINELENGTH; i++)
    {
        ins[i] = '\0';
        out[i] = '\0';
    }

    i = 0;
    while (fgets(ins, MAXLINELENGTH, infp))
    {
        while (i < MAXLINELENGTH && (c = ins[i]) != '\n')
        {
            if (c == '"' && is_first_quote)
            {
                inside_quotes = 1;
                is_first_quote = 0;
            }
            else if (c == '"' && !is_first_quote)
            {
                inside_quotes = 0;
                is_first_quote = 1;
            }
            if (c == '/' && ins[i + 1] == '/' && !inside_quotes)
            {
                out[i] = '\n';
                break;
            }
            if ((c == '/' || c == ' ') && !inside_quotes)
            {
                if (ins[i + 1] == '*') //then we are entering a block comment starting with "/*"
                {
                    while (i < MAXLINELENGTH && (c = ins[i]) != '\n')
                    {
                        if ((c == '/' || c == '*') && ins[i + 1] == '*')
                        {
                            while (i < MAXLINELENGTH && (c = ins[i]) != '\n')
                            {
                                if ((c = ins[i]) != '*' && ins[i + 1] != '/')
                                {
                                    ++i;
                                }
                                else
                                {
                                    while (fgets(ins, MAXLINELENGTH, infp) &&  ins[0] == ' ' && ins[1] == '*')
                                        ; // skip comment body

                                    for (j = 0; j < i; j++)
                                    {
                                        out[j] = ins[j];
                                    }
                                    i = i - 2;
                                    break;
                                }
                            }
                            break;
                        }
                        else
                        {
                            out[i] = c;
                        }
                        ++i;
                    }
                }
                if (ins[i + 1] == '/')
                {
                    out[i] = '\n';
                    break;
                }
            }
            out[i] = c;
            ++i;
        }
        if (c == '\n')
        {
            out[i] = '\n';
        }
        fprintf(outfp, "%s", out);
        for (i = 0; i < MAXLINELENGTH; i++)
        {
            out[i] = '\0';
        }
        i = 0;
    }
    fclose(infp);
    fclose(outfp);

    return 0;
}
