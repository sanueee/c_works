#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calc_lens(char** strs, int strsSize, int* lens) {
    for (int i = 0; i < strsSize; i++) {
        lens[i] = (int)strlen(strs[i]);
    }
}

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) {
        char* res = malloc(1);
        res[0] = '\0';
        return res;
    }

    int* lens = malloc(strsSize * sizeof(int));
    calc_lens(strs, strsSize, lens);

    int min_prefix_len = 200;
    for (int i = 0; i < strsSize; i++) {
        if (lens[i] < min_prefix_len) {
            min_prefix_len = lens[i];
        }
    }

    char* res = malloc(sizeof(char) * (min_prefix_len + 1));

    if (min_prefix_len == 0) {
        res[0] = '\0';
        free(lens);
        return res;
    }

    int i = 0;
    for (i = 0; i < min_prefix_len; i++) { // бежим по префиксу
        char curr_c = strs[0][i];
        for (int j = 1; j < strsSize; j++) { // бежим по строкам
            if (strs[j][i] != curr_c) {
                res[i] = '\0';
                free(lens);
                return res;
            }
        }
        res[i] = strs[0][i];
    }
    res[i] = '\0';
    free(lens);
    return res;
}

int main(void) {
    char* strs[] = {"flower", "flow", "flight"};

    char* res = longestCommonPrefix(strs, 3);

    printf("Longest prefix = %s", res);

    return 0;
}