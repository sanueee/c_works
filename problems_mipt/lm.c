#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int max_power(int n, int p);
long long lcm_range(int n);
void sieve(int n, int *primes, int *count);

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%lld", lcm_range(n));
    return 0;
}

int max_power(int n, int p) { // максимальная степень вхождения простого числа (n - ограничение, исходное число; p - простой делитель)
    int power = 0;
    int p_k = p;
    while (p_k <= n) {
        power++;
        p_k*=p;
    }
    return power;
}

long long lcm_range(int n) {
    if (n < 2) {
        return 1;
    }

    int *primes = malloc((n + 1) * sizeof(int)); // массив простых
    int prime_count; // количество простых 
    sieve(n, primes, &prime_count);

    long long result = 1;

    for (int i = 0; i < prime_count; i++) {
        int p = primes[i];
        int max_exp = max_power(n, p);

        for (int j = 0; j < max_exp; j++) {
            result *= p;
        }
    }

    free(primes);
    return result;
}

void sieve(int n, int* primes, int* count) {
    char *is_prime = calloc(n + 1, sizeof(char)); // решето 0 и 1 (0 - простое, 1 - составное)
    *count = 0;
    is_prime[0] = is_prime[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) { // это выполнится только для простых чисел
            primes[(*count)++] = i; // заполняем массив простыми числами, count - их кол-во
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 1;
            }
        }
    }
    free(is_prime);
}

/*
Временная эффективность нерекурсивных алгоритмов
Общий план анализа
1) Выберите параметр n, указывающий размер входных данных
2) Определите основную операцию алгоритма
3) Определите наихудший, средний и наилучший варианты для входных данных размера n
4) Задайте сумму для количества раз, когда выполняется основная операция
5) Упростите сумму, используя стандартные формулы и правила

Посчитаем сложность:
1) n - число поступившее на вход.
2) вызов lcm_range: T(n) = (n - 1) + T(sieve) + T(prime_count) * (T(max_power) + T(max_exp));
   распишем каждое T из T(n): 
   T(sieve) = n + n * (loglog(n)) ; O(n*loglog(n))
   T(prime_count) = n / ln(n) (теорема о распределении простых чисел)
   T(max_power) = log(n)
   T(max_exp) = T(max_power) = log(n)
3) Наихудший, наилучший, средний - O(nloglog(n)) (при всех n >= 2)
*/