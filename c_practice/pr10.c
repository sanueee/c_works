#include <stdio.h>
#include <stdlib.h>

int* read_input(int* count) {
    int capacity = 10;
    int size = 0;
    int* arr = malloc(capacity * sizeof(int));

    if (arr == NULL) return NULL;

    int temp;
    while (scanf("%d", &temp) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            int* new_arr = realloc(arr, capacity * sizeof(int));
            if (new_arr == NULL) {
                free(arr);
                return NULL;
            }
            arr = new_arr;
        }
        arr[size++] = temp;

        int c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        ungetc(c, stdin);
    }

    *count = size;
    return arr;

}

int main(void) {
    int count = 0;
    int* numbers = read_input(&count);

    if (numbers != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        free(numbers);
    }

    return 0;
}