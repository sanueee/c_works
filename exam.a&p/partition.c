#include <stdio.h>
#include <stdlib.h>

void backtrack(int sum_left, int count_left, int start_val, int* sum, int start_pos);
void partition(int N, int K);
void print_array(int* arr, int len);

int main(void) {
    int N = 20;
    int K = 3;

    partition(N, K);

    return 0;
}

void backtrack(int sum_left, int count_left, int start_val, int* sum, int start_pos) {
    if (count_left == 0) {
        if (sum_left == 0) {
            print_array(sum, start_pos);
        }
        return;
    }
    for (int i = start_val; i <= sum_left; i++) {
        sum[start_pos] = i;
        backtrack(sum_left - i, count_left - 1, i, sum, start_pos+1);
    }
}

void partition(int N, int K) {
    int sum[K];
    backtrack(N, K, 1, sum, 0); // sum_left, count_left, start_val, sum, start_pos
}

void print_array(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}