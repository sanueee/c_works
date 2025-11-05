#include <stdio.h>
void print_matrix(int *matrix, int rows, int cols) {
    int *ptr = (int *)matrix;
    int *end = ptr + rows * cols;
    while (ptr < end) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");
}

void xor_swap(int *a, int *b) {
    if (a != b) {
        *a ^= *b;  // a = a ^ b
        *b ^= *a;  // b = b ^ (a ^ b) = a
        *a ^= *b;  // a = (a ^ b) ^ a = b
    }
}

void bubble_sort(int *arr, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (*(arr+j) > *(arr+j+1)) {
                xor_swap(arr + j, arr + j + 1);
            }
        }
    }
}

int is_prime_recursive(int n, int divisor) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    if (divisor * divisor > n) return 1;
    if (n % divisor == 0) return 0;
    return is_prime_recursive(n, divisor + 2);
}

int is_prime(int n) {
    return is_prime_recursive(n, 3);
}

void transpose_matrix(int *matrix, int *res, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(res + j * rows + i) = *(matrix + i * cols + j);
        }
    }
}

int main() {
    int matrix[3][3]= {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int res[3][3];
    int rows = 3, cols = 3;
    int arr[5] = {5, 4, 1, 3, 2};
    int length = 5;
    int num = 11;
    transpose_matrix((int *)matrix, (int *)res, rows, cols);
    print_matrix((int *)res, rows, cols);
    bubble_sort(arr, length);
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%d", is_prime(num));
    return 0;
}