#include <stdio.h>

long long sum_digits(long long n);
int countEvenDigits(long long n);
int maxDigit(long long n);
int digitalRoot(long long n);
int isPalindrome(long long n);

int main(void) {
    long long n = 115511;

    int sum = sum_digits(n);
    int digital_root = digitalRoot(n);
    int count_even_digits = countEvenDigits(n);
    int max_digit = maxDigit(n);
    int is_palindrome = isPalindrome(n);

    printf("sum=%d\n", sum);
    printf("digital_root=%d\n", digital_root);
    printf("count_even_digits=%d\n", count_even_digits);
    printf("max_digit=%d\n", max_digit);
    printf("is_palindrome=%d\n", is_palindrome);

    return 0;
}

long long sum_digits(long long n) {
    int sum = 0;
    while (n > 0) {
        sum += (int)(n % 10);
        n /= 10;
    }
    return sum;
}

int countEvenDigits(long long n) {
    int count = 0;
    while (n > 0) {
        if (!( (n % 10) & 1 )) {
            count++;
        }
        n /= 10;
    }
    return count;
}

int maxDigit(long long n) {
    int mx = 0;
    while (n > 0) {
        int tmp = (int)(n % 10);
        if (tmp > mx) {
            mx = tmp;
        }
        n /= 10;
    }
    return (int)mx;
}

int digitalRoot(long long n) {
    if (n == 0) return 0;
    return 1 + (n - 1) % 9;
}

int isPalindrome(long long n) {
   if (n < 0 || (n % 10 == 0 && n != 0)) return 0;

   long long reversed = 0;
   while (n > reversed) {
        reversed = reversed * 10 + n % 10; // сохраняем вторую половину числа
        n /= 10; // оставляем первую половину числа
   }
   return (int)(n == reversed || n == reversed / 10);
}