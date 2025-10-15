#include <stdio.h>
#define MAXLINE 1000

int rstrip(char lines[], int maxlen);
int getLine(char lines[], int maxlen);

int main() {
    char lines[MAXLINE];
    int len;
    while ((len = getLine(lines, MAXLINE)) > 0) {
        rstrip(lines, MAXLINE);
        printf("%s\n", lines);
    }
   
    return 0;
}

int rstrip(char *lines, int maxlen) {
    int c, i;
    for (i = 0; i < maxlen && lines[i] != '\0'; i++)
        ;
    for (;i > 0 && (lines[i-1] == ' ' || lines[i-1] == '\t' || lines[i-1] == '\n');) {
        i--;
    }
    lines[i] = '\0';
    return i;    
}

int getLine(char lines[], int maxlen)
{
    int c, i;
    for (i = 0; i < maxlen - 1 && ((c = getchar()) != EOF) && c != '\n' && c != ' '; i++)
        lines[i] = c;
    if (c == ' ') {
        lines[i] = c;
        i++;
    }
    lines[i] = '\0';
    return i;
}