#include <stdio.h>
#include <stdlib.h>

void quickSort(int* nums, int left, int right) {
    if (!nums || left >= right) {
        return;
    }

    int i = left - 1;
    int pivot = nums[right];
    for (int j = left; j < right; j++) {
        if (nums[j] < pivot) {
            i++;
            int temp = nums[j];
            nums[j] = nums[i];
            nums[i] = temp;
        }
    }

    int temp = nums[i+1];
    nums[i+1] = nums[right];
    nums[right] = temp;

    quickSort(nums, left, i);
    quickSort(nums, i+2, right);
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int rows = 0, cols = 3;
    int capacity = numsSize;
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    quickSort(nums, 0, numsSize - 1);

    int** result = malloc(capacity * sizeof(int*));
    for (int i = 0; i < numsSize - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        if (nums[i] > 0) break; 
        int j = i + 1, k = numsSize - 1;
        while (j < k) {
            int sum = nums[i] + nums[j] + nums[k];
            if (sum == 0) {

                if (rows >= capacity) {
                    capacity *= 2;
                    result = (int**)realloc(result, capacity * sizeof(int*));
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                }
                result[rows] = (int*)malloc(cols * sizeof(int));

                result[rows][0] = nums[i];
                result[rows][1] = nums[j];
                result[rows][2] = nums[k];

                *returnColumnSizes = (int*)realloc(*returnColumnSizes, (rows+1) * sizeof(int));
                (*returnColumnSizes)[rows] = cols;
                rows++;

                while (j < k && nums[j] == nums[j + 1]) j++;
                while (j < k && nums[k] == nums[k - 1]) k--;
                j++;
                k--;
            }
            else if (sum > 0) {
                k--;
            } else {
                j++;
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
    int nums[] = {-1,0,1,2,-1,-4};
    int numsSize = sizeof(nums) / sizeof(int);

    int returnSize = 0;
    

    threeSum(nums, numsSize, &returnSize, returnColumnSizes);

    return 0;
}