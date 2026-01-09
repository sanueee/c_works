#include <stdio.h>
#include <stdlib.h>
/*
long ftell (FILE *stream); // текущее положение
int fseek (FILE *stream, long offset, int origin); // ищет текущее положение(offset) от origin
SEEK_SET - начало
SEEK_CUR - текущее положение
SEEK_END - конец 
*/

int findInFile(const char *name, int needle) {
    FILE *f;
    int count = 0;
    f = fopen(name, "r");
    if (!f) {
        perror("Error opening file");
        abort();
    }

    for (;;) {
        int res, n;
        res = fscanf(f, "%d", &n);
        if (res == EOF)
            break;
        if (res != 1) {
            fprintf(stderr, "File %s have broken format\n", name);
            abort();
        }
        if (needle == n) {
            count++;
        }
    }

    fclose(f);
    return count;
}

int main(int argc, char **argv) {
    int n; char *endptr; int count = 0;

    if (argc < 3) {
        fprintf(stderr, "Call: %s <n> <files...>\n", argv[0]);
        return 1;
    } // что n < 3

    n = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1]) { // если не продвинулись (не считали)
        fprintf(stderr, "<%s> cannot be converted to int\n", argv[1]);
        return 1;
    } // уверены что в n лежит число

    for (int i = 2; i < argc; i++)
        count += findInFile(argv[i], n);
    return 0;
}