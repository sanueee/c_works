#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256
#define MAX(a, b) ((a>=b) ? a: b)

void bm_search(const char* source, const char* pattern);
void preprocess_bad_char_table(int* bad_char, const char* pattern, int m);
void preprocess_good_suffix_table(int* good_suffix, const char* pattern, int m);
int is_prefix(const char* pattern, int start, int m);
int suffix_length(const char* pattern, int position, int m);

int main(void) {
    const char* source = "HELLO WORLD!";
    const char* pattern = "WORLD";

    bm_search(source, pattern);

    return 0;
}

void bm_search(const char* source, const char* pattern) {
    if (!source || !pattern) return;
    int n = strlen(source);
    int m = strlen(pattern);
    if (m == 0 || m > n) return;
    
    int* bad_char = (int*)malloc(ALPHABET_SIZE*sizeof(int));
    int* good_suffix = (int*)malloc(m*sizeof(int));


    if (bad_char == NULL || good_suffix == NULL) {
        free(bad_char); free(good_suffix);
        return;
    }

    preprocess_bad_char_table(bad_char, pattern, m);
    preprocess_good_suffix_table(good_suffix, pattern, m);

    int i = 0;
    while (i <= n-m) {
        int j = m-1;
        while (j >= 0 && pattern[j]==source[i+j]) {
            j--;
        }
        if (j < 0) {
            printf("совпадение на %d\n", i);
            i += good_suffix[0];
        } else {
            int shift_bc = MAX(1,j - bad_char[(unsigned char)source[i+j]]);
            int shift_gc = good_suffix[j];
            
            i += MAX(shift_bc, shift_gc);
        }
    }
    free(bad_char);
    free(good_suffix);
} 

void preprocess_bad_char_table(int* bad_char, const char* pattern, int m) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bad_char[i] = -1;
    }
    for (int j = 0; j < m; j++) {
        bad_char[(unsigned char)pattern[j]] = j;
    }
}

void preprocess_good_suffix_table(int* good_suffix, const char* pattern, int m) {
    for (int i = 0; i < m; i++) {
        good_suffix[i] = m;
    }

    int start_p_suffix = m;
    // правило 1 - является ли суффикс префиксом
    for (int i = m-1; i >= 0; i--) {
        if (is_prefix(pattern, i+1, m)) { // если подстрока pattern[i+1...m-1] является суффиксом то запомним ее начало
            start_p_suffix = i + 1;
        }
        good_suffix[m-1-i] = start_p_suffix + (m - 1 - i); // сдвиг = расстояние до конца + расстояние от начала до last_prefix
    }
    // правило 2 - есть ли суффикс где то в паттерне попозже чем префикс
    for (int i = 0; i < m-1; i++) {
        int suffix_len = suffix_length(pattern, i, m);
        good_suffix[suffix_len] = m - 1 - i + suffix_len;
    }
}

int is_prefix(const char* pattern, int start, int m) {
    int suffix_len = m - start;
    for (int i = 0; i < suffix_len; i++) {
        if (pattern[i] != pattern[start + i]) return 0;
    }
    return 1;
}

int suffix_length(const char* pattern, int position, int m) {
    int len = 0; int i = position; int j = m-1;
    while (i>=0 && pattern[i] == pattern[j]) {
        len++; i--; j--;
    }
    return len;
}