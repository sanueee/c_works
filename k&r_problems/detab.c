#include <stdio.h>
#define TABSIZE 8

int main() {
	int c;
	int position = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (int i = 0; i < (TABSIZE - (position % TABSIZE)); i++) {
				putchar(' ');
			}
		position += 8;
		}
		else {
			putchar(c);
			if (c == '\n') {
				position = 0;
			}
			else {
				position++;
			}
		}
	}

	return 0;
}


