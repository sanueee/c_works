#include <stdio.h>

void hanoi(int n, int from, int to);

int main(void) {

    hanoi(5, 1, 2);

    return 0;
}

void hanoi(int n, int from, int to) {
    if (n == 1) {
        printf("переложили диск %d с %d на %d\n", n, from, to);
    } else {
    int temp = 6 - from - to;
    hanoi(n - 1, from, temp);
    printf("переложили диск %d с %d на %d\n", n, from, to);
    hanoi(n - 1, temp, to);
    }
}