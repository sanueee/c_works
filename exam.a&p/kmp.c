#include <stdio.h>
#include <string.h>

// Функция для вычисления префикс-функции
void compute_prefix(const char *pattern, int *pi) {
    int m = strlen(pattern);
    pi[0] = 0;
    int k = 0;
    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[q]!=pattern[k]) {
            k = pi[k-1];
        }
        if (pattern[q]==pattern[k]) {
            k++;
        }
        pi[q]=k;
    }
}
// Основная функция поиска
void kmp_search(const char *text, const char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    int pi[m];

    compute_prefix(pattern, pi);

    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q]!=text[i]) {
            q = pi[q-1];
        }
        if (pattern[q]==text[i]) {
            q++;
        }
        if (q==m) {
            printf("match found at %d\n", i);
            q = pi[q-1];
        }
    }
}
int main() {
    const char *text = "ABABCABABABABCABCABCAB";
    const char *pattern = "ABCABCAB";
    
    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    
    kmp_search(text, pattern);
    
    return 0;
}