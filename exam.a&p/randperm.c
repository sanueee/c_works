#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void randomPermutation(int* arr, int n);
void printArray(int* arr, int n);

int main(void) {
    srand(time(NULL));

    int n;
    n = 10;

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    randomPermutation(arr, n);

    printArray(arr, n);

    return 0;
}

void randomPermutation(int* arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int j = i + rand() % (n-i);

        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}