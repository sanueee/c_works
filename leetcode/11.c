#include <stdio.h>

int calc_area(int l, int r, int k) {
    if (l >= r) {
        return r * k;
    }
    return l * k;
}

int maxArea(int* height, int heightSize) {
    int l = 0, r = heightSize - 1;
    int res = calc_area(height[l], height[r], r - l);
    int loc_area = 0;
    while (l < r) {
        if (height[l] < height[r]) {
            l++;
            loc_area = calc_area(height[l], height[r], r - l);
        }
        else {
            r--;
            loc_area = calc_area(height[l], height[r], r - l);
        }
        if (loc_area > res) {
            res = loc_area;
        }
    }
    return res;
}

int main(void) {
    int height[4] = {8,7,2,1};
    int res = maxArea(height, 4, 0);
    printf("%d", res);

    return 0;
}