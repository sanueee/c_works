#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 1000
#define max(a, b) (a >= b ? a: b)

typedef struct {
    char digits[MAX];
    short len;
    bool sign;
} big_num;

void input_big_num(big_num *num);
void print_big_num(big_num *num_1);
void do_operation(char op, big_num *num_1, big_num *num_2, big_num *res);
short compare_abs(big_num *num_1, big_num *num_2);
short compare_with_sign(big_num *num_1, big_num *num_2);
void swap_big_num(big_num *num_1, big_num *num_2);
bool sign_big_num(big_num *num);
void next_big_num(big_num *num_1, big_num *next);
void copy_big_num(big_num *dest, const big_num *src);

void sum(big_num *num_1, big_num *num_2, big_num *res, bool range_flag);
void difference(big_num *num_1, big_num *num_2, big_num *res);
void multiply(big_num *num_1, big_num *num_2, big_num *res);
void power(big_num *num_1, big_num *num_2, big_num *res);
void factorial(big_num *num_1, big_num *res); 
void range_sum(big_num *num_1, big_num *num_2, big_num *res); 

int main(void) {
    char op;
    scanf("%c", &op);
    (void)getchar(); // пропуск \n
    big_num num_1;
    big_num num_2;
    big_num res;
    
    memset(&num_1, 0, sizeof(big_num));
    memset(&num_2, 0, sizeof(big_num));
    memset(&res, 0, sizeof(big_num));
    
    do_operation(op, &num_1, &num_2, &res);
    print_big_num(&res);
    return 0;
}

void input_big_num(big_num *num) { // ввод числа с консоли, старше разряд -> меньше индекс (конец числа \0) 
    char c;
    short i = 0;
    if ((c = getchar()) == '-')
        num->sign = true;
    else {
        num->digits[i] = c;
        num->sign = false;
        i++;
    }
    while ((c = getchar()) <= '9' && c >= '0') {
        num->digits[i++] = c;
    }
    num->digits[i] = '\0';
    num->len = i;
}

void do_operation(char op, big_num *num_1, big_num *num_2, big_num *res) {
    if (op == '!') {
        input_big_num(num_1);
    }
    else {
        input_big_num(num_1);
        input_big_num(num_2);
    }
    switch (op) {
    case '+':
        sum(num_1, num_2, res, false);
        break;
    case '-':
        difference(num_1, num_2, res);
        break;
    case '*':
        multiply(num_1, num_2, res);
        break;
    case '^':
        power(num_1, num_2, res);
        break;
    case '!':
        factorial(num_1, res);
        break;
    case 'S':
        range_sum(num_1, num_2, res);
        break;
    }
}

short compare_abs(big_num *num_1, big_num *num_2) { // вспомогательная функция для сравнения абсолютных значений
    if (num_1->len != num_2->len)
        return num_1->len - num_2->len; // >0 - num_1 длиннее (значит больше), <0 - num_2 длиннее (больше)
    for (short i = 0; i < num_1->len; i++) {
        if (num_1->digits[i] != num_2->digits[i])
            return num_1->digits[i] - num_2->digits[i];  // >0 - num_1 больше , <0 - num_2 больше
    }
    return 0;
}

short compare_with_sign(big_num *num_1, big_num *num_2) { // сравнение с учетом знака
    if (num_1->sign != num_2->sign) { // если знаки разные
        return num_1->sign ? -1 : 1;  // отрицательное меньше положительного
    }
    if (!num_1->sign) { // если оба положительные
        return compare_abs(num_1, num_2);
    }
    // если оба отрицательные
    return -compare_abs(num_1, num_2);  // для отрицательных больше по модулю = меньше
}

void swap_big_num(big_num *num_1, big_num *num_2) {
    big_num temp = *num_1;
    *num_1 = *num_2;
    *num_2 = temp;
}

bool sign_big_num(big_num *num) {
    bool is_zero = true;
    for (short i = 0; i < num->len; i++) {
        if (num->digits[i] != '0') {
            is_zero = false;
            break;
        }
    }
    if (is_zero) {
        return false;  // число равно нулю
    }
    return num->sign ? true : false;
}

void next_big_num(big_num *num_1, big_num *next) {
    big_num one = {{'1', '\0'}, 1, false};
    sum(num_1, &one, next, true);
}

void print_big_num(big_num *num) {
    num->digits[num->len] = '\0';
    
    if (num->sign) {
        printf("Result=-%s", num->digits);
    } else {
        printf("Result=%s", num->digits);
    }
}

void copy_big_num(big_num *dest, const big_num *src) {
    dest->len = src->len;
    dest->sign = src->sign;
    for (short i = 0; i < src->len; i++) {
        dest->digits[i] = src->digits[i];
    }
    dest->digits[src->len] = '\0';
}

void sum(big_num *num_1, big_num *num_2, big_num *res, bool range_flag) {
    if (num_1->sign == num_2->sign) { // если знаки одинаковые - складываем
        short carry = 0;
        short i = num_1->len - 1;
        short j = num_2->len - 1;
        short max_len = (num_1->len > num_2->len) ? num_1->len : num_2->len;
        short k = max_len; // позиция в результате
        char temp_res[MAX]; // временный массив для результата
        memset(temp_res, 0, MAX);
        while (i >= 0 || j >= 0 || carry) {
            short sum = carry;
            if (i >= 0) {
                sum += (num_1->digits[i] - '0');
                i--;
            }
            if (j >= 0) {
                sum += (num_2->digits[j] - '0');
                j--;
            }
            temp_res[k] = (sum % 10) + '0';
            carry = sum / 10;
            k--;
        }

        k++;  // k теперь указывает на первую записанную цифру
        if (k == 0 && carry) {
            temp_res[0] = carry + '0';
            k = 0;
        }
        
        short result_len = max_len + 1 - k;
        for (short m = 0; m < result_len; m++) {
            res->digits[m] = temp_res[k + m];
        }
        res->digits[result_len] = '\0';
        res->len = result_len;
        res->sign = num_1->sign;
    }
    else { // если знаки разные - вызываем вычитание
        difference(num_1, num_2, res);
    }
}

void difference(big_num *num_1, big_num *num_2, big_num *res) {
    if (num_1->sign != num_2->sign) {
        big_num temp;
        copy_big_num(&temp, num_2);
        temp.sign = num_1->sign;
        sum(num_1, &temp, res, false);
        return;
    }
    big_num *greater, *lesser;
    bool result_negative = false;
    
    if (compare_abs(num_1, num_2) >= 0) {
        greater = num_1;
        lesser = num_2;
        result_negative = num_1->sign;  // сохраняем знак большего
    } else {
        greater = num_2;
        lesser = num_1;
        result_negative = !num_1->sign;  // меняем знак
    }
    
    short borrow = 0;
    short i = greater->len - 1;
    short j = lesser->len - 1;
    short k = greater->len - 1;
    
    for (short m = 0; m <= greater->len; m++) {
        res->digits[m] = '0';
    }

    while (i >= 0) {
        short diff = (greater->digits[i] - '0') - borrow;
        if (j >= 0) {
            diff -= (lesser->digits[j] - '0');
        }
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        res->digits[k] = diff + '0';
        i--;
        j--;
        k--;
    }

    short start = 0;
    while (start < greater->len - 1 && res->digits[start] == '0') {
        start++;
    }
    
    if (start > 0) {
        for (short m = 0; m < greater->len - start; m++) {
            res->digits[m] = res->digits[m + start];
        }
        res->len = greater->len - start;
    } else {
        res->len = greater->len;
    }
    
    res->digits[res->len] = '\0';
    
    // проверка на ноль
    if (res->len == 1 && res->digits[0] == '0') {
        res->sign = false;
    } else {
        res->sign = result_negative;
    }
}

void multiply(big_num *num_1, big_num *num_2, big_num *res) {
    if (compare_abs(num_1, num_2) < 0)
        swap_big_num(num_1, num_2);

    res->len = 0;
    res->sign = num_1->sign ^ num_2->sign; // XOR 

    short temp = 0,
        carry = 0,
        product = 1,
        k = num_1->len + num_2->len,
        k_index = 0;

    for (short m = 0; m <= k; m++)
        res->digits[m] = '0';
    
    for (short i = num_1->len - 1; i >= 0; --i) {
        carry = 0;
        short i_j_base = i + num_2->len;
        for (short j = num_2->len - 1; j >= 0; --j) {
            k_index = i + j + 1;
            product = ((num_1->digits[i] - '0') * (num_2->digits[j] - '0'))
                + (res->digits[k_index] - '0') + carry;
            res->digits[k_index] = product % 10 + '0';
            carry = (short)(product / 10);
        }
        if (carry > 0) {
            res->digits[i] = (res->digits[i] - '0' + carry) % 10 + '0';
        }
    }
    
    short start = 0;
    while (start < k - 1 && res->digits[start] == '0') {
        start++;
    }
    
    if (start > 0) {
        for (short i = 0; i < k - start; i++) {
            res->digits[i] = res->digits[i + start];
        }
        res->len = k - start;
    } else {
        res->len = k;
    }
    res->digits[res->len] = '\0';
}

void power(big_num *num_1, big_num *num_2, big_num *res) {
    if (num_2->sign) {
        res->digits[0] = '0';
        res->digits[1] = '\0';
        res->len = 1;
        res->sign = false;
        return;
    }
    if (num_2->len == 1 && num_2->digits[0] == '0') {
        res->digits[0] = '1';
        res->digits[1] = '\0';
        res->len = 1;
        res->sign = false;
        return;
    }

    copy_big_num(res, num_1);
    big_num limit;
    copy_big_num(&limit, num_2);
    
    big_num temp;
    memset(&temp, 0, sizeof(big_num));
    big_num current = {{'1', '\0'}, 1, false};    
    while (compare_with_sign(&current, &limit) < 0) { // умножаем result на num_1 (num_2 - 1) раз
        multiply(res, num_1, &temp);
        copy_big_num(res, &temp);
        next_big_num(&current, &temp); // увеличиваем current на 1
        copy_big_num(&current, &temp);
    }
}

void factorial(big_num *num_1, big_num *res) {
    if (num_1->sign) {
        return;
    }
    big_num current = {{'1', '\0'}, 1, false}; // множитель (от 1 до limit)
    big_num counter = {{'1', '\0'}, 1, false};
    big_num temp_current = {{'1', '\0'}, 1, false}; // то куда складывается current + 1
    big_num temp_product = {{'1', '\0'}, 1, false}; // сюда складываем результат умножения
    big_num limit;
    copy_big_num(&limit, num_1); // ограничитель (последний множитель)
    while (compare_abs(&limit, &counter) > 0) {
        next_big_num(&counter, &temp_current);
        multiply(&temp_product, &temp_current, &current);
        next_big_num(&counter, &counter);
        copy_big_num(&temp_product, &current);
    }
    copy_big_num(res, &current);
}

void range_sum(big_num *num_1, big_num *num_2, big_num *res) { // S = n * (a1 + an) / 2 где n = количество чисел от a1 до an включительно
    big_num first, last;
    if (compare_with_sign(num_1, num_2) <= 0) {
        copy_big_num(&first, num_1);
        copy_big_num(&last, num_2);
    } else {
        copy_big_num(&first, num_2);
        copy_big_num(&last, num_1);
    }
    
    // n = last - first + 1
    big_num n;
    difference(&last, &first, &n);
    big_num one = {{'1', '\0'}, 1, false};
    sum(&n, &one, &n, false);
    
    // (first + last)
    big_num sum_ends;
    sum(&first, &last, &sum_ends, false);
    
    // n * (first + last)
    big_num product;
    multiply(&n, &sum_ends, &product);
    
    short carry = 0;
    res->len = 0;
    
    for (short i = 0; i < product.len; i++) {
        short digit = (product.digits[i] - '0') + carry * 10;
        res->digits[i] = (digit / 2) + '0';
        carry = digit % 2;
    }

    res->len = product.len;
    res->sign = product.sign;
    
    while (res->len > 1 && res->digits[0] == '0') {
        for (short i = 0; i < res->len - 1; i++) {
            res->digits[i] = res->digits[i + 1];
        }
        res->len--;
    }
    
    res->digits[res->len] = '\0';
}