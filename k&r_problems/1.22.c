#include <stdio.h>
#define MAX_COLUMN 10

int main(void) {
	int c;
	int col = 0; //столбец(позиция)
	int last_space = -1;		
	char line[1000];
	while ((c = getchar()) != EOF) {
		line[col] = c;

		if (c == ' ' || c == '\t') {
			last_space = col;
		}
		
		if (col < MAX_COLUMN && c == '\n') {    // 1 случай (перенос раньше MAX_COLUMN)
			for (int j = 0; j < col; j++) {
				printf("%c", line[j]);
			}
			putchar('\n');
			col = 0;
		}
		
		if (col >= MAX_COLUMN) { // 2 случай (переступили границу)
			if (c == ' ' || c == '\t' || c == '\n') { // 2.1 случай (переступили границу пробелом, \t \n) 
				for (int j = 0; j < col; j++) {
					printf("%c", line[j]);
				}
				putchar('\n');
				col = 0;
			}
			else { // 2.2 случай (переступили границу другим символом) 
				for (int j = 0; j < last_space; j++) {
					printf("%c", line[j]);
				}
				putchar('\n');
				for (int j = 0; j <  col - last_space + 1; j++) {
					line[j] = line[j+last_space+1];
				}
			}
		}	
		
		col++;
	}
	return 0;
}
