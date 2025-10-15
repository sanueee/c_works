#include <stdio.h>

int main()
{
    int c, n = 0, t = 0, s = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') n++;
        if (c == '\t') t++;
        if (c == ' ') s++;
    }
    printf("%d %d %d", n, t, s);
}