#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverse(const char *s) {
	size_t len = strlen(s);
	char *reversed_s = malloc(len + 1);
	if (!reversed_s) return NULL;
	
	for (size_t i = 0; i < len; ++i) {
		reversed_s[i] = s[len - 1 - i];
	}
	reversed_s[len] = '\0';
	return reversed_s;
}

int main() {
	const char *s = "Hello!";
	char *reversed_s = reverse(s);

	if (reversed_s) {
		printf("original: %s\n", s);
		printf("reversed: %s\n", reversed_s);
		free(reversed_s);
	}
	return 0;
}
