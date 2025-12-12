#include <stdio.h>

void inverse_str(char *str, int index);

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        inverse_str(&argv[i][0], 0);
        printf("\n");
    }

    return 0;
}

void inverse_str(char *str, int index) {
    if (str[index] == '\0' ) {
        return;
    }
    inverse_str(str, index+1);
    printf("%c", str[index]);
}

