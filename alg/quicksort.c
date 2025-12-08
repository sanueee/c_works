#include <stdio.h>

void quicksort(int* arr, int left, int right);

int main() {
    int arr[10] = {8, 7, 6, 5, 4, 3, 2, 1};
    quicksort(arr, 0, 10 - 1);
    return 0;
}

void quicksort(int* arr, int left, int right) {
    if (left > right) return;
    int i = left - 1;
    int pivot = *(arr + right);
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    quicksort(arr, left, i);
    quicksort(arr, i + 2, right);
}