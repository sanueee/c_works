#include <stdio.h>

int main(void) {
    char string[1024];
    int c;
    int sum = 0;
    int i = 0;

    while ((c = getchar()) != EOF && i < 1023) {
        string[i++] = (char)c;
    }
    string[i] = '\0';

    for (i = 0; string[i] != '\0'; i++) {
        sum += (char)string[i];
    }

    printf("%d\n", sum);
    return 0;
}