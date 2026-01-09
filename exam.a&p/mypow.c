#include <stdio.h>

int mypow(int a, int n) {
    if (n == 1) {
        return a;
    }
    if (!(n & 1)) {
        int half = mypow(a, (int)n/2);
        return half * half;
    } else {
        return a * mypow(a, n-1);
    }
}

int main(void) {
    int res = mypow(2, 8);
    
    return 0;
}