#include <stdio.h>
#include <stdlib.h>

void recursive_fill(char* sequence, int N, int c_opened, int c_closed, int cur_pos);
void print_array(char* arr, int len);
void generate(int N);

int main(void) {
    int N = 3;

    generate(N);

    return 0;
}

void generate(int N) {
    char* sequence = (char*)malloc(2*N*sizeof(char)+1);
    recursive_fill(sequence, N, 0, 0, 0);
    free(sequence);
}

void recursive_fill(char* sequence, int N, int c_opened, int c_closed, int cur_pos) {
    if (cur_pos == 2*N) {
        print_array(sequence, 2*N);
        return;
    }
    if (c_opened < N) {
        sequence[cur_pos] = '(';
        recursive_fill(sequence, N, c_opened+1, c_closed, cur_pos+1);
    }
    if (c_closed < c_opened) {
        sequence[cur_pos] = ')';
        recursive_fill(sequence, N, c_opened, c_closed+1, cur_pos+1);
    }   
}

void print_array(char* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}