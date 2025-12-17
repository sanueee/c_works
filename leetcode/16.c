#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void quicksort(int* nums, int left, int right) { // ломуто
    if (left >= right) return;

    int pivot = nums[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (nums[j] < pivot) {
            i++;
            int temp = nums[j];
            nums[j] = nums[i];
            nums[i] = temp;
        }
    }
    int temp = nums[right];
    nums[right] = nums[i+1];
    nums[i+1] = temp;

    quicksort(nums, left, i);
    quicksort(nums, i+2, right);
}

int threeSumClosest(int* nums, int numsSize, int target) {
    quicksort(nums, 0, numsSize - 1);
    int result_sum = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < numsSize; i++) {
        int l = i + 1, r = numsSize - 1;
        while (l < r) {
            int sum = nums[l] + nums[r] + nums[i];
            if (sum == target) {
                return sum;
            }
            if (abs(target - sum) < abs(target - result_sum)) {
                result_sum = sum;
            }
            if (sum < target) {
                l++;
            } else {
                r--;
            }
        }
    }
    return result_sum;
}

int main(void) {
    int nums[4] = {-4, -1, 1, 2};
    int res;
    res = threeSumClosest(nums, 4, 1);
    printf("%d", res);
    return 0;
}