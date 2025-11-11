#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct sieve_t {
  unsigned long long n;
  char *s;
};

void fill_sieve(struct sieve_t *sv);
int nth_prime(struct sieve_t *sv, int N);
unsigned long long sieve_bound(int N);

int main(void) {
    int N;
    scanf("%d", &N);

    struct sieve_t sv;
    sv.n = sieve_bound(N);
    sv.s = calloc(sv.n, sizeof(char));

    fill_sieve(&sv);
    printf("%d", nth_prime(&sv, N));
    return 0;
}

void fill_sieve(struct sieve_t *sv) {
    unsigned long long len = sv->n;
    sv->s[0] = sv->s[1] = 1;
    for (unsigned long long i = 2; i < (((unsigned long long)sqrt(len)) + 1); i++) {
        if (!sv->s[i]) {
            for (unsigned long long j = i * i; j < len; j += i) {
                sv->s[j] = 1;
            }
        }
    }
}

int nth_prime(struct sieve_t *sv, int N) {
    int counter = 0;
    unsigned long long i = 2;
    while (counter < N) {
        if (sv->s[i] == 0) {
            counter++;
        }
        i++;
    }
    return --i;
}

unsigned long long sieve_bound(int N) {
    if (N > 20) {
        double dnum = N;
        double res = dnum * (log(dnum) + log(log(dnum)));
        return (unsigned long long)round(res);
    }
    return 20;
}