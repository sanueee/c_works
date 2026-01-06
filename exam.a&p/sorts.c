#include <stdio.h>
#include <stdlib.h>

void printArray(int* arr, int n);
void bubbleSort(int* arr, int len);
void insertionSort(int* arr, int len);
void selectionSort(int* arr, int len);
void shakerSort(int* arr, int len);
void shellSort(int* arr, int len);
void merge(int* arr, int left, int mid, int right);
void mergeSort(int* arr, int left, int right);
void quickSortL(int* arr, int left, int right);
void quickSortH(int* arr, int left, int right);

int main(void) {
    int arr[] = {1, 9, 3, 0, 7, 5, 3,0,1020, 2103021, 2, 21, 2, 2, 5, 233, 11, 929139};
    int len = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, len);
    //bubbleSort(arr, len);
    //insertionSort(arr, len);
    //selectionSort(arr, len);
    //shakerSort(arr,len);
    //shellSort(arr, len);
    //mergeSort(arr, 0, len-1);
    //quickSortL(arr, 0, len-1);
    //quickSortH(arr, 0, len-1);
    printArray(arr, len);
}

void quickSortH(int* arr, int left, int right) {
	if (!arr || left >= right) return;
	int i = left, j = right;
	int pivot = arr[left + (right-left)/2];
	do {
		if (arr[i] < pivot) {
			i++;
			continue;
		}
		if (arr[j] > pivot) {
			j--;
			continue;
		}
		if (i<=j) {
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
			i++; j--;
		}			
	} while (i<=j);
	if (j > left) quickSortH(arr, left, j);
	if (i < right) quickSortH(arr, i, right);
}

void quickSortL(int* arr, int left, int right) {
	if (!arr || left >= right) return;
	
	int i = left-1; // отслеживание границы между <pivot и >pivot
	int pivot = arr[right];
	for (int j = left; j < right; j++) {
		if (arr[j] < pivot) {
			i++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	int temp = arr[i+1];
	arr[i+1] = arr[right];
	arr[right] = temp;
		
	quickSortL(arr, left, i);
	quickSortL(arr, i+2, right);		
}

void merge(int* arr, int left, int mid, int right) {
	int len1 = mid - left + 1;
	int len2 = right - mid;
	if (len1 < 0 || len2 < 0) {
        return;
    }

	int* L = malloc(len1*sizeof(int));
	int* R = malloc(len2*sizeof(int));
    if (L == NULL || R == NULL) {
        if (!L) free(L);
        if (!R) free(R);
        return;
    }

	for (int i = 0; i<len1; i++) L[i] = arr[left+i];
	for (int i = 0; i<len2; i++) R[i] = arr[mid+1+i];
	
	int i=0, j=0, k = left;
	while (i < len1 && j < len2) { // добавляем с учетом порядка
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		} else {
			arr[k++] = R[j++];
		}
	}
	
	while (i < len1) arr[k++] = L[i++]; // остались элементы в L
	while (j < len2) arr[k++] = R[j++]; // остались элементы в R
	
	free(L);
	free(R);	
}

void mergeSort(int* arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left)/2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}
}

void shellSort(int* arr, int len) {
	int gap;
	int i, j, temp;
	for (gap = len/2; gap>0; gap/=2) {
		for (i = gap; i < len; i++) {
			temp = arr[i];
			j = i;
			while (j >= gap && arr[j-gap]>temp) {
				arr[j] = arr[j-gap];
				j -= gap;
			}
			arr[j] = temp;
		}
        printArray(arr, len);
	}
}

void shakerSort(int* arr, int len) {
	int left = 1, right = len - 1;
	int k = len - 1;
	do {
		for (int j = right; j >= left; j--) { // cправа налево
			if (arr[j] < arr[j-1]) {
				int temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
				k = j;
			}
		}
		left = k+1;
		for (int i = left; i <= right; i++) {
			if (arr[i] < arr[i-1]) {
				int temp = arr[i-1];
				arr[i-1] = arr[i];
				arr[i] = temp;
				k = i;
			}
		}
		right = k-1;
	} while (left < right);
}

void selectionSort(int* arr, int len) {
	for (int i = 0; i < len-1; i++) {
		int min_index = i;
        int j;
		for (j = i+1; j < len; j++) {
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}
		}
		if (min_index != i) {
			int temp = arr[min_index];
			arr[min_index] = arr[i];
			arr[i] = temp;
		}
        printArray(arr, len);
	}
}

void insertionSort(int* arr, int len) {
	for (int i = 2; i < len; i++) {
		int key = arr[i];
		int left = 0;
		int right = i;
		while (left < right) {
			int mid = left + (right - left)/2;
			if (arr[mid] <= key) {
				left = mid+1;
			}
			else {
				right = mid;
			}
		}
		int j;
		for (j = i; j > right; arr[j] = arr[j-1], j--);
		arr[right] = key;
        printArray(arr, len);
	}
}

void bubbleSort(int* arr, int len) {
	int flag = 1;
	for (int i = 0; flag; i++) {
		flag = 0;
		for (int j = len-1; j > i; j--) {
			if (arr[j-1] > arr[j]) {
				int temp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temp;
				flag = 1;
			}
		}
        printArray(arr, len);
	}
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}