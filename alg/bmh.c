#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256
/*
1. Если символ встречается более одного раза, то применяем
значение, соответствующее символу, наиболее близкому к
концу образа.
2. Неоднократное вхождение символов в образ никак не влияет
на вычисление удаленности других символов от конца образа.
3а. Если символ в конце образа встречается только один раз, то
соответствующее ему значение таблицы d равно длине образа.
3б. Если символ в конце образа встречается более одного раза,
то применяем значение, соответствующее символу, наиболее
близкому к концу образа.
4. Для символов, не присутствующих в образе, будем применять
значение, равное длине образа.
*/

void input_string(char *str, int length);
void print_res(int start_position);
void build_bad_char_table(const char *pattern, int m, int *badChar);
int horspool_search(const char *src, const char *pattern, int n, int m);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char src[n];
    char pattern[m];

    memset(src, 0, n * sizeof(char));
    memset(pattern, 0, m * sizeof(char));
    
    input_string(src, n);
    input_string(pattern, m);

    int found = horspool_search(src, pattern, n, m);    

    print_res(found);

    return 0;
}

void input_string(char *str, int length) {
    (void)getchar();
    for (int i = 0; i < length; i++) {
        char c = (char)getchar();
        if (c != '\n') {
            *(str+i) = (char)c;
        }
    }
}

void print_res(int start_position) {
    if (start_position == -1) {
        printf("Подстрока не найдена");
    } else {
        printf("Подстрока найдена на позиции %d.", start_position);
    }
}

void build_bad_char_table(const char *pattern, int m, int *bad_char) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bad_char[i] = m;
    }
    
    for (int i = 0; i < m - 1; i++) {
        bad_char[(unsigned char)*(pattern + i)] = m - 1 - i;
    }
}

int horspool_search(const char *src, const char *pattern, int n, int m) {
    if (m == 0 || m > n) {
        return -1;
    }

    int bad_char[ALPHABET_SIZE];
    build_bad_char_table(pattern, m, bad_char);

    int i = 0;
    
    while (i <= n - m) {
        int j = m - 1;

        if (j >= 0 && pattern[j] == src[i + j]) {
            j--;
        }

        if (j < 0) {
            return i;
        }

        i += bad_char[(unsigned char)src[i + m - 1]];
    }
    return -1;
}