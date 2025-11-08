#include <stdio.h> 
#include <assert.h>
void n_prime(int n);
int is_prime(int x);

int main() {
    int n;
    scanf("%d", &n);
    assert(n > 0);
    n_prime(n);
    return 0;    
}
void n_prime(int n) {
    int x, k = 1;
    for (x = 2; ; x++) {
        if (is_prime(x)) {
            if (k == n) {
                printf("%d", x);
                break;
            }
            k++;
        }
    }
}

int is_prime(int x) {
    if (x < 2) {
        return 0;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}