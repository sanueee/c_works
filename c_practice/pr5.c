#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void search_max_min(int* arr, int len, int* mx, int* mn);
void generate_array(int* arr, int len);
void print_array(int* arr, int len);

int main(void) {
    srand(time(NULL));

    int arr1[10], arr2[10], arr3[10];

    generate_array(arr1, 10);
    generate_array(arr2, 10);
    generate_array(arr3, 10);
    
    int inx_mx1 = 0, inx_mx2 = 0, inx_mx3 = 0;
    int inx_mn1 = 0, inx_mn2 = 0, inx_mn3 = 0;
    
    search_max_min(arr1, 10, &inx_mx1, &inx_mn1);
    search_max_min(arr2, 10, &inx_mx2, &inx_mn2);
    search_max_min(arr3, 10, &inx_mx3, &inx_mn3);

    print_array(arr1, 10);
    print_array(arr2, 10);
    print_array(arr3, 10);

    printf("\n");

    printf("mx1 = %d , index_mx1 = %d\n", *(arr1 + inx_mx1), inx_mx1);
    printf("mx2 = %d , index_mx2 = %d\n", *(arr2 + inx_mx2), inx_mx2);
    printf("mx3 = %d , index_mx3 = %d\n\n", *(arr3 + inx_mx3), inx_mx3);

    printf("mn1 = %d , index_mn1 = %d\n", *(arr1 + inx_mn1), inx_mn1);
    printf("mn2 = %d , index_mn2 = %d\n", *(arr2 + inx_mn2), inx_mn2);
    printf("mn3 = %d , index_mn3 = %d\n", *(arr3 + inx_mn3), inx_mn3);

    return 0;
}

void generate_array(int* arr, int len) {
    for(int i = 0; i < len; i++)
        *(arr + i) = rand() % 100;
}

void search_max_min(int* arr, int len, int* mx, int* mn) {
    int l = 0, r = len - 1;
    while(l <= r) {
        if(*(arr + l) <= *(arr + r)) {
            if (*(arr + r) > *(arr + *mx))
                *mx = r;
            if (*(arr + l) < *(arr + *mn))
                *mn = l;
        } else {
            if (*(arr + l) > *(arr + *mx))
                *mx = l;
            if (*(arr + r) < *(arr + *mn))
                *mn = r;
        }
        l++;
        r--;
    }
}

void print_array(int* arr, int len) {
    for(int i = 0; i < len; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}
