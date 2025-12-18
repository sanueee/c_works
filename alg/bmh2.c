/*
1. Таблица смещений строится на основе образа, начиная с конца образа. 
2. Для каждого символа в **алфавите** вычисляется смещение, которое указывает, на сколько позиций нужно сдвинуть образ при несовпадении символа. 
3. Смещение вычисляется как расстояние от конца образа до последнего вхождения символа в образ.
4. Если символ не встречается в образе, смещение равно длине образа.
Для того чтобы построить таблицу сдвигов правильно, стоит начинать построение таблицы сдвигов с предпоследней буквы.
Для повторяющихся символов в образе необходимо указывать минимальный сдвиг.
Если последний символ в образе встречался ранее, то необходимо указывать минимальный сдвиг.
abbab
12212
*/
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256

int bmh_search(const char* pattern, const char* source) {
    if (!pattern || !source) {
        return -1;
    }

    int m = strlen(pattern);
    int n = strlen(source);
    
    if (m > n || m == 0) {
        return -1;
    }

    int shift[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        shift[i] = m;
    }
    for (int i = 0; i < m - 1; i++) {
        unsigned char c = (unsigned char)(*(pattern + i));
        shift[c] = m - i - 1;
    }

    int i = 0; // позиция в исходной строке
    while (i <= n - m) {
        int j = m - 1; // позиция в образе 
        while (j >= 0 && pattern[j] == source[i + j]) { 
            j--;
        }

        if (j == -1) { // нашли
            return i;
        }

        i += shift[(unsigned char)source[i + m - 1]]; // правило плохого символа
    }
    return -1;
}

int main(void) {
    const char *pattern = "БУКВБ";
    const char *source = "РУССКИЕ БУКВБ";

    int res = bmh_search(pattern, source);
    if (res != -1) {
        printf("Match found at %d.\n", res); // возвращает байтовую позицию, символ может быть либо 1 либо 2 байта.
    } else {
        printf("Match not foud\n");
    }

    return 0;
}