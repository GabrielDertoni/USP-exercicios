#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *dp_strstr(char *str, char *sub, int *vec) {
	if (!vec) vec = (int *)malloc(strlen(str) * sizeof(int));
	if (!*sub) return vec;
	int fst = 0;
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == *sub)
			vec[i] = 1 + (i > 0 ? vec[i - 1] : 0);

	return dp_strstr(str, sub + 1, vec);
}

int main(int argc, char *argv[]) {
	char str[20];
	char sub[20];
	scanf(" %s", str);
	scanf(" %s", sub);

	int *vec = dp_strstr(str, sub, NULL);
	for (int i = 0; i < strlen(str); i++) {
		printf("%d ", vec[i]);
	}
	printf("\n");
	
	return EXIT_SUCCESS;
}
