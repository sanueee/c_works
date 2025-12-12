#include <stdio.h>

long long countLines(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return -1;
    }
    
    long long lines = 0;
    int ch;
    int prevChar = '\n';
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
        prevChar = ch;
    }

    if (prevChar != '\n' && lines > 0) {
        lines++;
    }
    
    fclose(file);
    return lines;
}

int main(int argc, char** argv) {
    char* filepath = argv[1];
    printf("%lld", countLines(filepath));
}
 