#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 256

int is_prefix(const char *pattern, int start, int m);
int suffix_length(const char *pattern, int end, int m);
void preprocess_good_suffix(const char *pattern, int m, int *good_suffix);
void preprocess_bad_char(const char *pattern, int m, int *bad_char);
void boyer_moore_search(const char *text, const char *pattern);

int main(void) {
    const char *text = "ABABCABABABABC";
    const char *pattern = "ABABC";
    
    printf("Текст:   %s\n", text);
    printf("Длина: %d\n", (int)strlen(text));
    printf("Паттерн: %s\n", pattern);
    printf("Длина: %d\n\n", (int)strlen(pattern));
    
    boyer_moore_search(text, pattern);
    
    return 0;
}

int is_prefix(const char *pattern, int start, int m) { // суффикс является ли префиксом
    int suffix_len = m - start;
    for (int i = 0; i < suffix_len; i++) {
        if (pattern[i] != pattern[start + i])
            return 0;
    }
    return 1;
}

int suffix_length(const char *pattern, int end, int m) { // максимальная длина подстроки 0<-end совпадающей с 0<-m-1
    int len = 0, i = end, j = m - 1;
    while (i >= 0 && pattern[i] == pattern[j]) {
        len++;
        i--; j--;
    }
    return len;
}

void preprocess_good_suffix(const char *pattern, int m, int *good_suffix) { // правило хорошего суффикса
    int last_prefix = m;
    for (int i = 0; i < m; i++) {
        good_suffix[i] = m;
    }
    // ПРАВИЛО 1: Суффикс, который также является префиксом
    for (int i = m - 1; i >= 0; i--) {
        if (is_prefix(pattern, i+1, m)) {
            last_prefix = i + 1;  // запоминаем начало этого суффикса-префикса
        }
        int mismatch_pos = m - 1 - i;  // позиция несовпадения (от конца)
        int shift = last_prefix - i + m - 1; // сдвиг
        good_suffix[mismatch_pos] = shift; // сдвиг для этой позиции несовпадения
    }
    // ПРАВИЛО 2: Суффикс, который встречается где-то в паттерне
    // может перезаписать значения из Правила 1, если найдёт более близкое вхождение
    for (int i = 0; i < m - 1; i++) {
        int len = suffix_length(pattern, i, m); // длина суффикса, который совпадает с pattern[...i]
        if (len > 0) {
            // Вычисляем сдвиг:
            // (m - 1) - i: расстояние между вхождением суффикса и найденного в suffix_length вхождения
            // + len: корректировка для правильного выравнивания
            int shift = (m - 1 - i) + len;
            good_suffix[len] = shift;
        }
    }
}

void preprocess_bad_char(const char *pattern, int m, int *bad_char) { // правило плохого символа
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bad_char[i] = -1;
    }
    for (int j = 0; j < m; j++) {
        bad_char[(unsigned char)pattern[j]] = j;
    }
}

void boyer_moore_search(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    if (m > n) {
        printf("Паттерн длиннее текста, совпадений нет\n");
        return;
    }
    
    int *bad_char = (int*)malloc(ALPHABET_SIZE * sizeof(int));
    int *good_suffix = (int*)malloc(m * sizeof(int));
    
    if (bad_char == NULL || good_suffix == NULL) {
        free(bad_char);
        free(good_suffix);
        return;
    }
    
    preprocess_bad_char(pattern, m, bad_char);
    preprocess_good_suffix(pattern, m, good_suffix);
    
    printf("Bad Character Table:\n");
    for (int i = 0; i < m; i++) {
        printf("  '%c' -> %d\n", pattern[i], bad_char[(unsigned char)pattern[i]]);
    }
    
    printf("\nGood Suffix Table:\n");
    for (int i = 0; i < m; i++) {
        printf("  good_suffix[%d] = %d\n", i, good_suffix[i]);
    }
    printf("\n");
    
    int i = 0;
    int matches_found = 0;
    
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }        
        if (j < 0) { // полное совпадение
            printf("Совпадение найдено на позиции %d\n", i);
            i += good_suffix[0];
        } else { // несовпадение: вычисляем сдвиг
            int shift_bc = j - bad_char[(unsigned char)text[i + j]];
            int shift_gs = good_suffix[j];
            if (shift_bc < 1) {
                shift_bc = 1;
            }
            int shift = (shift_bc > shift_gs) ? shift_bc : shift_gs;
            
            printf("  Позиция i=%d: несовпадение на j=%d ('%c' != '%c'), "
                   "shift_bc=%d, shift_gs=%d, сдвиг=%d\n",
                   i, j, pattern[j], text[i + j], shift_bc, shift_gs, shift);
            
            i += shift;
        }
    }

    free(bad_char);
    free(good_suffix);
}