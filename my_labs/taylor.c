#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

double fact_plus(double fact, long long k) {
    if (k == 0) 
        return 1;
    else 
        return fact * (2 * k - 1) * 2 * k;
}

double minus_1K(long long k) {
    if (k % 2 == 0)
        return  1;
    else 
        return -1;
}

int main(void) {
    int n;
    double cosin;
    scanf("%d", &n); //точность
    scanf("%lf", &cosin); //значение косинуса
    
    double sum_n = 0;
    double sum_max = 0;
    double fact2K = 1;
    double cosin2K = 1;
    
    for (int k = 0; k <= n; k++) {
        double term = minus_1K(k) * cosin2K / fact2K;
        sum_n += term;
        fact2K = fact_plus(fact2K, k + 1);
        cosin2K *= cosin * cosin;
    }
    
    fact2K = 1;
    cosin2K = 1;

    
    for (int k = 0; ; k++) {
        double term = minus_1K(k) * cosin2K / fact2K;
        
        if (k > 0 && term == 0) {
            break;
        }
        
        sum_max += term;
        fact2K = fact_plus(fact2K, k + 1);
        cosin2K *= cosin * cosin;
        
    }
    
    printf("sum_n=%.15f\n", sum_n);
    printf("sum_max_precision=%.15f\n", sum_max);
    
    return 0;
}
