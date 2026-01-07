#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 256

void preprocess_bad_char(const char* pattern, int* bad_char, int m);
void boyer_moore_horspool(const char* source, const char* pattern);

int main(void) {
    const char* source = "HELLO";
    const char* pattern = "HELLO";

    boyer_moore_horspool(source, pattern);

    return 0;
}

void preprocess_bad_char(const char* pattern, int* bad_char, int m) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bad_char[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        bad_char[(unsigned char)pattern[i]] = m - 1 - i;
    }
}

void boyer_moore_horspool(const char* source, const char* pattern) {
    int n = strlen(source);
    int m = strlen(pattern);

    int* bad_char = (int*)malloc(ALPHABET_SIZE*sizeof(int));

    if (bad_char == NULL) {
        free(bad_char);
        return;
    }

    preprocess_bad_char(pattern, bad_char, m);

    int i = 0;
    while (i <= n-m) {
        int j = m-1;
        while (j >= 0 && pattern[j]==source[i+j]) {
            j--;
        }
        if (j < 0) {
            printf("совпадение на %d\n", i);
            i += 1;
            continue;
        }
        if (j == m-1) {
            i += bad_char[(unsigned char)source[i+j]];
        } else {
            i += bad_char[(unsigned char)pattern[j]];
        }
    }
    free(bad_char);
}