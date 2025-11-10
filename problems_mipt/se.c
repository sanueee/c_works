#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

struct sieve_t {
        unsigned size;
        unsigned char *sieve;
    };

void init_sieve(int n, struct sieve_t* s);
int count_primes(int n, struct sieve_t* s);
void print_sieve(struct sieve_t *s, int n);
void free_sieve(struct sieve_t* s);

int main() {
    int n;
    scanf("%d", &n);
    struct sieve_t s;
    s.sieve = calloc((n - 1), sizeof(char));
    s.size = n;
    init_sieve(n, &s);
    printf("%d", count_primes(n, &s));
    free_sieve(&s);
    return 0;
}

void init_sieve(int n, struct sieve_t* s) {
    /*
    for (int i = 0; i < (n - 1); i++) {
        assert((s->sieve + i) != NULL);
        *(s->sieve + i) = i + 2;
    }
    print_sieve(s, n);
    printf("\n");
    */    
    s->sieve[0] = s->sieve[1] = 1;  // не простые
    int sqrt_n = (int)sqrt(n);
    for (int i = 2; i <= (sqrt_n + 1); i++) {
        if (!s->sieve[i]) {
            for (int j = i * i; j <= n + 1; j += i) {  // начинаем с i*i, т.к. меньшие кратные уже вычеркнуты
                s->sieve[j] = 1;
            }
        }
    }
}

int count_primes(int n, struct sieve_t* s) {
    int counter = 0;
    for (int i = 0; i < n + 1; i++) {
        if (s->sieve[i] == 0) {
            counter++;
        }
    }
    return counter;
}

void print_sieve(struct sieve_t* s, int n) {
    for (int i = 0; i < (n - 1); i++) {
        printf("%d ", s->sieve[i]);
    }
}

void free_sieve(struct sieve_t* s) {
    free(s->sieve);
    s->size = 0;
}