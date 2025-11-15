#include <stdio.h>

void high_low_bit(int n, int* low_index, int* high_index);
void print_output(int low_index, int high_index);

int main(void) {
    int n;
    scanf("%d", &n);
    int low_index = -1, high_index = -1;
    high_low_bit(n, &low_index, &high_index);
    print_output(low_index, high_index);
    return 0;
}

void high_low_bit(int n, int* low_index, int* high_index) {
    int counter = 0, first = -1, last = -1;
    while (n != 0) {
        if (n & 1) {
            if (first == -1) {
                *low_index = counter;
                first = 1;
            }
            *high_index = counter;
            last = 1;
        }
        counter++;
        n = n >> 1;
    }
}

void print_output(int low_index, int high_index) {
    if (low_index == -1 && high_index == -1) {
        printf("NO");
    }
    else {
        printf("%d %d", high_index, low_index);
    }
}