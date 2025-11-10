#include <stdio.h>

void mirror(int (*matrix)[3], int cols, int rows) { // int* matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == j) {
                printf("%d ", *(*(matrix+i)+j));
            }
            else {
                printf("%d ", *(*(matrix+j)+i));
            }
        }
        printf("\n");
    }
}
int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = 3, cols = 3;
    mirror(matrix, cols, rows);
    return 0;
}