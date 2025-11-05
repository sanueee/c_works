#include <stdio.h>
#define MAXLINE 1000
#define LIMIT 8

int getLine(char line[], int maxlen)
{
    int c, i;
    for (i = 0; i < maxlen - 1 && ((c = getchar()) != EOF) && c != '\n' && c != ' '; i++)
        line[i] = c;
    if (c == ' ')
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

int main()
{
    char lines[MAXLINE];
    int len;

    while ((len = getLine(lines, MAXLINE)) > 0) {

        if (len > LIMIT) {
            printf("%s\n", lines);

        }
    }
    return 0;
}