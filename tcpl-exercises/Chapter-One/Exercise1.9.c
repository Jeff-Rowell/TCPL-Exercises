#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char string[BUFSIZ];
    int c;

    while ((c = read(0, string, BUFSIZ)) > 0)
    {
         write(1, string, c);
    }

    return 0;
}