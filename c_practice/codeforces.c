#include <stdio.h>
#include <stdbool.h>

int sum_arr(int* arr, int len);
void input_data(int* arr, int n);
void calculate_sums_counts(int* arr, int n, int* count_negative_x, int* count_positive_x, int* negative_sum, int* positive_sum);
void fill_arr(int* arr, int n, int count_x, int filler);
void print_arr(int* arr, int n);

int main(void) {
    int t;
    scanf("%d", &t);

    for (int number = 0; number < t; number++) {
        int n;
        scanf("%d", &n);

        int arr[n];
        input_data(arr, n);

        int count_negative_x = 0, count_positive_x = 0, negative_sum = 0, positive_sum = 0;
        calculate_sums_counts(arr, n, &count_negative_x, &count_positive_x, &negative_sum, &positive_sum);

        int count_x = count_positive_x - count_negative_x;
        int res_count_x = count_positive_x + count_negative_x;
        int sum = positive_sum - negative_sum;
        int filler = sum / count_x; // чем заполнять пустоты;

        fill_arr(arr, n, count_x, filler);
        printf("%d\n", sum_arr(arr, n));
        print_arr(arr, n);
    }
}

void input_data(int* arr, int n) {
    for (int i = 0; i < n; i++)
        scanf("%d", (arr + i));
}

int sum_arr(int* arr, int len) {
    int sum = 0;
    for(int i = 1; i < len; i++) {
        sum += (*(arr + i - 1) - *(arr + i));
    }
    if (sum < 0)
        return -sum;
    return sum;
}

void calculate_sums_counts(int* arr, int n, int* count_negative_x, int* count_positive_x, int* negative_sum, int* positive_sum) {
    for (int i = 1; i < n - 1; i++) {
        if (*(arr+i) == -1) {
            if (*(arr+i-1) == -1) {
                *(count_negative_x)++;
            } else {
                *(negative_sum) += *(arr+i-1);
            }
        *(count_positive_x)++;
        } else {
            if (*(arr+i-1) == -1) {
                *(count_negative_x)++;
            } else {
                *(negative_sum) += *(arr+i-1);
            }
            *(positive_sum)++;
        }
    }
}

void fill_arr(int* arr, int n, int count_x, int filler) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (*(arr + i) == -1) {
            if (counter < count_x) {
                *(arr + i) = 0;
                counter++;
            } else {
                *(arr + i) = filler;
            }
        }
    }
}

void print_arr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr+i));
    }
    printf("\n");
}