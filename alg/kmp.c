#include <stdio.h>
#include <string.h>

void fill_pi(char *pattern, int m, int *pi);
void input_string(char *str, int length);
int kmp_search(char *src, char* pattern, int* pi, int n, int m);
void print_res(int start_position);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char src[n];
    char pattern[m];
    int pi[m];

    memset(src, 0, n * sizeof(char));
    memset(pattern, 0, m * sizeof(char));
    memset(pi, 0, m * sizeof(int));
    
    input_string(src, n);
    input_string(pattern, m);

    fill_pi(pattern, m, pi);

    int start_pattern = kmp_search(src, pattern, pi, n, m);

    print_res(start_pattern);

    return 0;
}

void fill_pi(char *pattern, int m, int *pi) {
    int left = 0, right = 1;
    while (right < m) {
        if (*(pattern + left) == *(pattern + right)) {
            *(pi + right) = left + 1;
            left++;
            right++;
        }
        else {
            if (left == 0) {
                *(pi + right) = 0;
                right++;
            }
            else {
                left = *(pi + left - 1);
            }
        }
    }
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

int kmp_search(char *src, char* pattern, int* pi, int n, int m) {
    int i = 0, j = 0;
    while (i < n) {
        if (*(src + i) == *(pattern + j)) {
            i++;
            j++;
            if (j==m) return i;
        }
        else {
            if (j > 0) {
                j = *(pi + j - 1);
            }
            else {
                i++;
                if (i == n) return -1;
            }
        }
    }
    return -1;
}

void print_res(int start_position) {
    if (start_position == -1) {
        printf("Подстрока не найдена");
    } else {
        printf("Подстрока найдена на позиции %d.", start_position);
    }
}