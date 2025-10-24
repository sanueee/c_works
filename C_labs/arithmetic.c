#include <stdio.h>
#include <stdbool.h>

#define MAX 1000
#define max(a, b) (a >= b ? a: b)

typedef struct {
    char digits[MAX];
    short len;
    bool sign;
} big_num;

short input_big_num(big_num *num_1);
void print_big_num(big_num *num_1);

void sum(big_num *num_1, big_num *num_2, short len_1, short len_2, big_num *res);

int main(void) {
    char op;
    scanf("%c", &op);
    (void)getchar(); // пропуск \n


    big_num num_1;
    big_num num_2;
    big_num res;

    print_big_num(&num_1);
    print_big_num(&num_2);
    return 0;
}

short input_big_num(big_num *num) { // ввод числа с консоли, старше разряд -> меньше индекс (конец числа \0) 
    char c;
    short i = 0;
    if ((c = getchar()) == '-') {
        num->sign = true;
    }
    else {
        num->digits[i] = c;
        i++;
    }
    while ((c = getchar()) != '\n') {
        num->digits[i++] = c;
    }
    num->digits[i] = '\0';
    return i;
}

void do_operation(char op) {
    switch (op) {
        case '+':
            input_big_num(&num_1);
            input_big_num(&num_2);
            sum()
            break;
        case '-':
            input_big_num(&num_1);
            input_big_num(&num_2);
            break;
        case '*':
            input_big_num(&num_1);
            input_big_num(&num_2);
            break;
        case '^':
            input_big_num(&num_1);
            input_big_num(&num_2);
            break;
        case '!':
            input_big_num(&num_1);
            break;
        case 'S':
            input_big_num(&num_1);
            input_big_num(&num_2);
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

void print_big_num(big_num *num) { // вывод числа как строки
    if (num->sign) {
        printf("-%s\n", num->digits);
        return;
    }
    printf("%s\n", num->digits);
}

void sum(big_num *num_1, big_num *num_2, big_num *res) {
    if (num_1->sign == num_2->sign) { // если знаки одинаковые - складываем и сохраняем знак (случаи: + и + || - и -)
        short temp = 0; // то что держим в "уме" когда считаем столбиком типа 8 + 2 = 10, 0 пишем 1 в уме
        short i = num_1->len - 1; // счетчик для первого числа
        short j = num_2->len - 1; // счетчик для второго
        short k = max(num_1->len, num_2->len) + 1; // счетчик для результата ("+ 1" для случаев типа 5 + 5 = 10)
        
        while (i >= 0 || j >= 0 || temp) { // сложение столбиком пока не дойдем до старшего разряда большего числа и пока есть что то в "уме"
            short sum = temp;
            if (i >= 0) sum += (short)(num_1->digits[i] - '0');
            if (j >= 0) sum += (short)(num_2->digits[j] - '0');
            res[k] = (short)(sum % 10 + '0');
            temp = (short)(sum / 10);
        }
        
        res->digits[++k] = '\0';
        res->sign = num1->sign;
    }
    else { // если знаки разные - вызываем вычитание (случаи: + и - || - и +)
        difference(num_1, num_2, res);
    }
}

void difference(big_num *num_1, big_num *num_2, big_num *res) {
    big_num *greater, *lesser; // объявляем указатели на большее и меньшее
    bool res_sign;
    if (compare_abs(num_1, num_2) >= 0) { // определяем большее по модулю (когда мы из большего по модулю вычитаем меньшее по модулю то результат имеет знак большего)
        greater = num_1;
        lesser = num_2;
        res_sign = num_1->sign;
    } else {
        greater = num_2;
        lesser = num_1;
        res_sign = !num_2->sign;
    }
    res->sign = res_sign;
    short borrow = 0;
    short i = greater->len - 1;
    short j = lesser->len - 1;
    short k = greater->len;

    for (short m = 0; m <= k; m++) { // заполним нулями чтоб потом подправить результат (непонятно скок знаков будет в res)
        res->digits[m] = '0';
    }

    while (i >= 0) { // вычитание столбиком
        short diff = (short)(greater->digits[i] - '0') - borrow;
        if (j >= 0) {
            diff -= (short)(lesser->digits[j] - '0');
        }
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        res->digits[k] = (char)(diff) + '0';
        i--;
        j--;
        k--;
    }
    
    k = 0;
    while (res->digits[k] == '0' && k < greater->len - 1) { // находим старший разряд
        k++;
    }
    if (k > 0) {
        for (short m = 0; m < greater->len - k + 1; m++) {
            res->digits[m] = res->digits[m + k];
        }
        res->len = greater->len - k;
    } else {
        res->len = greater->len;
    }
}