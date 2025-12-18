/*
В алгоритме КМП используется понятие наибольшего собственного префикса, совпадающего с суффиксом.
Алгоритм КМП:
1) Построение массива сдвигов:
    - на каждой позиции i pi[i] показывает длину наибольшего префикса, который также является суффиксом.
*/

#include <stdio.h>

size_t str_len(const char* str) {
    return (*str) ? str_len(++str) + 1: 0;
}

void prefix_func(const char *pattern, int *pi) {
    int m = str_len(pattern);
    pi[0] = 0;
    int k = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && pi[i] != pi[k]) {
            k = pi[k-1];
        }
        if (pi[i] == pi[k]) {
            k++;
        }
        pi[i] = k;
    }
}

void kmp_search(const char *source, const char *pattern) {
    int n = str_len(source);
    int m = str_len(pattern);

    int pi[m];
    prefix_func(pattern, pi);

    int q = 0; // индекс в шаблоне
    for(int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != source[i]) {
            q = pi[q - 1];
        }
        if (pattern[q] == source[i]) {
            q++;
        }
        if (q == m) {
            printf("Match found at position %d.\n", i - m + 1);
            q = pi[q - 1];
        }
    }
}

int main(void) {
    const char *source = "Helloworld!";
    const char *pattern = "world";

    kmp_search(source, pattern);
    
    return 0;
}