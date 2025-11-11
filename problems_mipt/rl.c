#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

long long gcd_r(long long x, long long y);
long long gcd_c(long long x, long long y);

int main(void) {
	long long x = 0, y = 0;
	scanf("%lld %lld", &x, &y);

	long long g = gcd_c(x, y);
	printf("%lld\n", g);

	return 0;
}

long long gcd_r(long long x, long long y) {
    if (y > x) {
        return gcd_r(y, x); // x > y
    }
    x = llabs(x);
    y = llabs(y);
    int q = x % y;
    if (q == 0) {
        return y; // если делятся без остатка возвращаем меньшее
    }
    return gcd_r(y, q); // gcd(a, b) == gcd(b, q)
}

long long gcd_c(long long x, long long y) {
    if (y > x) {
        return gcd_c(y, x); // x > y
    }
    x = llabs(x);
    y = llabs(y);
    while (y != 0) {
        long long temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}