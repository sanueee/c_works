#include <stdio.h>

int main()
{
    char c;
    char prev = 0;

    while ((c = getchar()) != EOF)
    {
        if (c != ' ')
        {
            printf("%c", c);
            continue;
        }
        if (prev != ' ')
        {
            printf("%c", c);
        }
        prev = c;
    }
    return 0;
}