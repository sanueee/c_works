#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void randomSample(int* arr, int n, int* res, int m);
void printArray(int* arr, int n);

int main(void) {
    srand(time(NULL));

    int n = 10;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int m = 5;

    int res[m];
    randomSample(arr, n, res, m);

    printArray(res, m);

    return 0;
}

void randomSample(int* arr, int N, int* res, int n) {
    int m = 0;
    for (int t = 0; t<N && m<n; t++) {
        int remain = n - m; // диапазон оставшихся к выбору
        int not_seen = N - t; // диапазон оставшихся к просмотру

        int r = rand() % not_seen; // дает диапазон от 0 до N-t-1, каждое значение имеет вероятность 1/N-t

        if (r < remain) { // эквивалентно n-m/N-t так как значений r < n-m ровно n-m (от 0 до n-m-1) получается n-m * 1/N-t
            res[m] = arr[t];
            m++;
        }
    }
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}