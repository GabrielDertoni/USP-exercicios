#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 20

char *readInput();
void sortChars(char *begin, char *end);

int main(int argc, char *argv[]) {
	char *chars = readInput();
	int len = strlen(chars);
	sortChars(chars, chars + len);
	
	for (int i = 0; i < len; i += sizeof(int)) {
		int output = 0;
		for (int j = 0; j < sizeof(int) && i + j < len; j++)
			output |= (int)chars[i + j] << (j * 8 * sizeof(char));

		printf("%d\n", output);
	}

	free(chars);
	
	return 0;
}

char *readInput() {
	if (feof(stdin)) return "";

	char c;
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL;
	int i = 0;
	do {
		c = getc(stdin);
		if (c != '\n' && c != '\r') {
			// Caso a memória alocada tenha terminado, aloca outro chunk.
			if (i >= allocated - 1) {
				// Garante que haverá espaço para o \0
				allocated *= 2;
				if (allocated == 0) allocated += CHUNK;
				string = (char *)realloc(string, allocated);
			}
			string[i++] = c; // Escreve a entrada na memória.
		}
	} while(!feof(stdin) && c != 'x');
	if (allocated == 0) return "";
	string[i] = '\0'; // Adiciona '\0' ao final.
	string = (char *)realloc(string, (i + 1) * sizeof(char));
	return string;
}

void sortChars(char *begin, char *end) {
	// Range [start, end)
	if (end - begin <= 1) return;

	char *p1 = begin + 1;
	char *p2 = end - 1;
	while(p1 != p2) {
		if (*p1 > *begin && *p2 <= *begin) {
			char temp = *p1;
			*p1 = *p2;
			*p2 = temp;
		}
		if (*p1 <= *begin) p1++;
		else if (*p2 > *begin) p2--;
	}
	if (*p1 > *begin) p1--;
	char temp = *p1;
	*p1 = *begin;
	*begin = temp;
	sortChars(begin, p1);
	sortChars(p1 + 1, end);
}
