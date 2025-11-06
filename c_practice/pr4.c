#include <stdio.h>

void reverse(char* s) {
    while (*s != '\0') {
        s++;
    }
    s--;
    while (*s > '0') {
        printf("%c", *s);
        s--;
    }
}

int main() {
    char s[100];
    char c;
    int i = 0;
    
    while ((c = getchar()) != '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';

    reverse(s);

    return 0;
}