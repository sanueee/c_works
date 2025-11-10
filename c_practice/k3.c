#include <stdio.h> 
#include <math.h>
int prime(int x);
int prime_d(int n);

int main() {
    int x = 18;
    prime_d(x);
    return 0;
}

int prime_d(int n) {
    if (prime(n)){
        printf("%d ", n); // на листике нет 
        return 0;
    }
    else {
        for (int i = 2; i < (int)pow(n, 0.5)+1; i++) {
            if (n % i == 0) {
                if (prime(i)) {
                    printf("%d ", i);
                    prime_d(n / i);
                    return 0;
                }
            }
        }
    }
}
int prime(int x) {
    if (x < 1) {
        return 0;
    }
    for (int i = 2; i < (int)pow(x, 0.5)+1; i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}