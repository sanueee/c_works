#include <stdio.h>

int removeElement(int* nums, int numsSize, int val) {
    int left = 0, right = numsSize - 1;

    while (left <= right) {
        while (left <= right && nums[left] != val) {
            left++;
        }
        while (left <= right && nums[right] == val) {
            right--;
        }

        if (left < right) {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            left++;
            right--;
        }
    }
    return left;
}

int main(void) {
    int nums[] = {3,3,2,2};
    int val = 3;
    int numsSize = sizeof(nums) / sizeof(int);
    int res = 0;
    res = removeElement(nums, numsSize, val);

    for (int i = 0; i < res; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}