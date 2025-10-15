#include <stdio.h>

int binary_search(int numbers[], int len_numbers, int x)
{    
    int left = 0, right = len_numbers - 1; // границы

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // середина 
        if (x > numbers[mid])
        {
            left = mid + 1;
        }
        else if (x < numbers[mid])
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int main()
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len_numbers = sizeof(numbers) / sizeof(numbers[0]);
    int x;

    printf("Введите число которое необходимо найти: "); // искомое
    scanf("%d", &x);

    int res = binary_search(numbers, len_numbers, x);
    
    if (res == -1) 
    {
        printf("Числа нет в массиве!\n");
        return 1;
    }
    else
    {
        printf("Число найдено в массиве на индексе: %d.\n", res);
        return 0;
    }
}