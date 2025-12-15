#include <stdio.h>
#include <stdlib.h>

typedef struct {
        int value;
        int index;
    } Pair;

void quicksort(Pair* pair, int left, int right) {
    if (left > right) return;

    int i = left - 1;
    int pivot = pair[right].value;
    for (int j = left; j < right; j++) {
        if (pair[j].value < pivot) {
            i++;
            int temp = pair[j].value;
            int temp_index = pair[j].index;

            pair[j].value = pair[i].value;
            pair[j].index = pair[i].index;

            pair[i].value = temp;
            pair[i].index = temp_index;
        }
    }
    int temp = pair[i + 1].value; // ставим pivot на место
    int temp_index = pair[i + 1].index;

    pair[i + 1].value = pair[right].value;
    pair[i + 1].index = pair[right].index;

    pair[right].value = temp;
    pair[right].index = temp_index;

    quicksort(pair, left, i);
    quicksort(pair, i + 2, right);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Pair* arr = malloc(numsSize * sizeof(Pair));
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < numsSize; i++) {
        arr[i].value = nums[i];
        arr[i].index = i;
    }

    quicksort(arr, 0, numsSize - 1);
    
    int* res = malloc(2 * sizeof(int));
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int sum = arr[left].value + arr[right].value;
        if (sum == target) {
            res[0] = arr[left].index;
            res[1] = arr[right].index;
            *returnSize = 2;
            free(arr);
            return res;
        }
        if (sum < target) left++;
        else right--; 
    }
    free(res);
    return NULL;
}

int main(void) {
    int nums[4] = {2, 7, 11, 15};
    int numsSize = sizeof(nums) / sizeof(int);
    int target = 9;
    int returnSize;
    int* result = twoSum(nums, numsSize, target, &returnSize);
    printf("%d %d", result[0], result[1]);
    free(result);
    return 0;
}