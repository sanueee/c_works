#include <stdio.h>
#include <string.h>

int main(void) {
    int m;
    scanf("%d", &m);

    char pattern[m];
    int i = 0; int c;
    while ((c = getchar()) != EOF || c != '\n') {
        pattern[i++] = c;
    }
    pattern[i] = '\0';

    int n;
    scanf("%d", &n);

    char source[n];
    int i = 0; int c;
    while ((c = getchar()) != EOF || c != '\n') {
        source[i++] = c;
    }
    source[i] = '\0';

    char *needIndex = strstr(source, pattern);
    printf("%d", *needIndex);
    
    return 0;
}