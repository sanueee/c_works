#include <stdio.h>

int main() {
    int arr1[5] = {1, 2, 2, 5, 6};
    int arr2[4] = {1, 2, 3, 4};
    int n = 5, m = 4;

    int help[1000];
    for (int i = 0; i < 1000; i++) {help[i] = 0;};

    for (int i = 0; i < n; i++) {
        if (*(help+arr1[i]) == 0) { // было просто i
            printf("%d ", arr1[i]);
            *(help+arr1[i]) = 1;
        }
    }
    for (int i = 0; i < m; i++) {
        if (*(help+arr2[i]) == 0) {
            printf("%d ", arr2[i]);
            *(help+arr2[i]) = 1;
        }
    }
}