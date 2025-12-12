#include <stdio.h>
#include <stdlib.h>
#define N ((size_t)1000)

void fill_frequency(FILE* fp, int* help_arr);
int find_frequent(int* help_arr);

int main(void) {
    char* file_name = "task_1.txt";
    FILE* fp = fopen(file_name, "r");
    int* help_arr = calloc(N, sizeof(int));

    fill_frequency(fp, help_arr);
    fclose(fp);
    int fr_el = 0;
    fr_el = find_frequent(help_arr);

    printf("%c", fr_el);

    free(help_arr);

    return 0;
}

void fill_frequency(FILE* fp, int* help_arr) {
    char c;
    if (fp) {
        while ((c = getc(fp)) != EOF) {
            (*(help_arr + c))++;
        }
    }
}

int find_frequent(int* help_arr) {
    int max_freq = 0;
    int most_frequent_char = 0;
    
    for (int i = 0; i < N; i++) {
        if (help_arr[i] > max_freq) {
            max_freq = help_arr[i];
            most_frequent_char = i;
        }
    }
    
    return most_frequent_char;
}
