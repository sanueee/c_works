#include <stdio.h>

void bubble_sort(int *arr, int length) {

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            int temp = arr[i];
            if (temp > arr[j]) {
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

}

int main() {
    int letters[5];

    int c;

    for (int i = 0; i < 5; i++) {
        c = getchar();
        letters[i] = c;
    }

    bubble_sort(letters, 5);

    for (int i = 4; i >= 0; i--) {
        printf("%c", letters[i]);
    }
    putchar('\n');

    return 0;
}