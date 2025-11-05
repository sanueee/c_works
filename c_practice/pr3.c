#include <stdio.h>
#define MAX 1000

int mystrlen(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

void mystrcpy(char *s, char *res) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        res[i] = s[i];
    }
    res[i] = '\0'; 
}

void mystrncpy(char *s, char *res, int n) {
    int i;
    for (i = 0; i < n; i++) {
        res[i] = s[i];
    }
    res[i] = '\0'; 
}

void clearstr(char *s) {
    s[0] = '\0';
}

int main() {
    char s[MAX] = "123456789";
    char res[MAX];
    mystrcpy(s, res);
    printf("res = %s\n", res);
    clearstr(res);
    printf("res = %s\n", res);
    return 0;
}