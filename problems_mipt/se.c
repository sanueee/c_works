#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct sieve_t {
        unsigned size;
        unsigned char *sieve;
    };

void init_sieve(int n, struct sieve_t* s);
void print_sieve(struct sieve_t *s, int n);
void free_sieve(struct sieve_t* s);

int main() {
    int n;
    scanf("%d", &n);
    
    struct sieve_t s;
    s.sieve = calloc((n - 1), sizeof(char));
    s.size = n;
    init_sieve(n, &s);
    print_sieve(&s, n);
    free_sieve(&s);
    return 0;
}

void init_sieve(int n, struct sieve_t* s) {
    int k = 0;
    for (int i = 0; i < (n - 1); i++) {
        assert((s->sieve + i) != NULL);
        *(s->sieve + i) = i + 2;
    }
    print_sieve(s, n);
    printf("\n");
    for (int i = 0; i < (n - 1); i++) {
        int k = 0, j = 0;
        if (s->sieve[i] == 0) { // если уже побывали на 4 во время того как i = 2 например
            continue;
        }
        k = s->sieve[i]; // шаг
        j = i; // шаг внутри шага 
        while (j < n) {
            if (s->sieve[j] == k) {
                s->sieve[j] = 1;
                j+=k;
                continue;
            }
            s->sieve[j] = 0;
            j+=k;
        }
    }
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