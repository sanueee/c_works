#include <stdio.h>

void input_matrix(int *matrix, int rows, int cols);
void print_matrix(int *matrix, int rows, int cols);

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    (void)getchar();

    int matrix[n][m];
    input_matrix((int*)matrix, n, m);
    print_matrix((int*)matrix, n, m);

    return 0;
}

void input_matrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", (matrix + i*cols + j));
        }
    }
}

void print_matrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(matrix + i*cols + j));
        }
        printf("\n");
    }
}
