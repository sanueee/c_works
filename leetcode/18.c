
#include <stdio.h>
#include <stdlib.h>

int comp_int_asc(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(nums, numsSize, sizeof(nums[0]), comp_int_asc);

    *returnSize = 0; // размер выходного массива (rows)
    *returnColumnSizes = malloc(numsSize * sizeof(int*)); // массив rows штук 4 
    int** result = malloc(numsSize * sizeof(int*)); // матрица [rows * 4]
    int rows = 0;
    int capacity = numsSize;

    // nums[i], nums[j], nums[k], nums[h]
    for (int i = 0; i < numsSize - 3; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        for (int j = i + 1; j < numsSize - 2; j++) {
            if (j > i+1 && nums[j] == nums[j-1]) continue;
            int k = j + 1, h = numsSize - 1;
            while (k < h) {
                long long sum = (long long)nums[i]+(long long)nums[j]+(long long)nums[k]+(long long)nums[h];
                if (sum == target) {
                    if (rows >= capacity) {
                        capacity*=2;
                        result = realloc(result, capacity * sizeof(int*));
                        *returnColumnSizes = realloc(*returnColumnSizes, capacity * sizeof(int));
                    }
                    result[rows] = malloc(sizeof(int) * 4);
                    result[rows][0] = nums[i];
                    result[rows][1] = nums[j];
                    result[rows][2] = nums[k];
                    result[rows][3] = nums[h];

                    (*returnColumnSizes)[rows] = 4;
                    rows++;
                    
                    while (k < h && nums[k] == nums[k + 1]) k++;
                    while (k < h && nums[h] == nums[h - 1]) h--;
                    k++;
                    h--;
                }
                else if (sum < target) {
                    k++;
                } else {
                    h--;
                }
            }
        }
    }
    if (rows == 0) {
        free(result);
        free(*returnColumnSizes);
        *returnColumnSizes = NULL;
        return NULL;
    }
    result = (int**)realloc(result, rows * sizeof(int*));
    *returnColumnSizes = (int*)realloc(*returnColumnSizes, rows * sizeof(int));
    *returnSize = rows;

    return result;
}

int main(void) {
    int nums[] = {1,0,-1,0,-2,2};
    int target = 0;
    int numsSize = sizeof(nums) / sizeof(int);

    int returnSize;
    int** arr = malloc(sizeof(int*));
    arr[0]=malloc(sizeof(int));
    fourSum(nums, numsSize, target, &returnSize, arr);

    return 0;
}