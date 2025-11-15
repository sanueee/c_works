#include <stdio.h>

#define GET_BIT(n, i) (1 & (n >> i)) // i-ый бит
#define SET_BIT(n, i) (n | (1 << i)) // i-ый бит в 1
#define CLEAR_BIT(n, i) (n & ~(1 << i)) // i-ый бит в 0
#define INVERSE_BIT(n, i) (n ^ (1 << i)) // инвертирует i-ый бит
#define CHECK_BIT(n, i) (n & (1 << i)) // возвращает либо 0 либо 2^i
#define ASSIGN_BIT(n, i, x) ((n & ~(1 << i)) | (x << i)) // устанавливает i-ый бит значением x (0 || 1)

void input_arr(unsigned char* arr, int);
void inverse_bit(unsigned char* arr, int bit);
void print_arr(unsigned char* arr, int);

int main(void) {
    int len;
    scanf("%d", &len);

    unsigned char arr[len];
    input_arr(arr, len);

    int bit;
    scanf("%d", &bit);

    inverse_bit(arr, bit);

    print_arr(arr, len);

    return 0;
}

void input_arr(unsigned char* arr, int len) {
    for (int i = 0; i < len; i++){ 
        int temp;
        scanf("%d", &temp);
        arr[i] = (unsigned char)temp;
    }
}

void inverse_bit(unsigned char* arr, int bit) {
    int number = (int)(bit / 8);
    int number_bit = (int)(bit % 8);
    *(arr + number) = INVERSE_BIT(*(arr + number), number_bit);
}

void print_arr(unsigned char* arr, int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", (int)arr[i]);
    printf("\n");
}
