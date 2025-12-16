#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    if (numsSize == 1) return 1;
    int k = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[k-1]) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}

int main(void) {
    int nums[] = {0,0,0,0,1,1,1,2,2,3,3,4};
    int res = removeDuplicates(nums, 12);
    for (int i = 0; i < res; i++) {
        printf("%d ", nums[i]);
    }
}