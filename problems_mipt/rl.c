#include <stdio.h>
#include <assert.h>

unsigned long long gcd(unsigned long long x, unsigned long long y);

int main() {
	unsigned long long x = 0, y = 0, g;
	int res;
	res = scanf("%llu %llu", &x, &y);
	//assert(res==2);
	g = gcd(x, y);
	printf("%llu\n", g);
	return 0;
}

unsigned long long gcd(unsigned long long x, unsigned long long y) {

    if (x > y) {
    unsigned long long temp = x;
    x = y;
    y = temp;
    }
    // x < y - гарантируем 
    unsigned long long r = y % x; // остаток
    unsigned long long q = x; // то че делим
    while (1) {
        if (r == 0) return q;
        r = q % r;
        q = r;   
    }
}
