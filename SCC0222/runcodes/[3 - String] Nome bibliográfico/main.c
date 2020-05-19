#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros para parsing
#define LN "\r\n"
#define LLETTER "abcdefghijklmnopqrstuvwxyz"
#define ULETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTER LLETTER ULETTER

// Macros para quantidade de alocação.
#define CHUNK 32

char *toUpper(char *string);
char *readName(FILE *fp);
int ignoreUntill(char *stop, FILE *fp);
char *readUntil(char *stop, FILE *fp);

int main(int argc, char *argv[]) {
	char *name = readName(stdin);
	int len = strlen(name);

	int i;
	for (i = len - 1; name[i] != ' ' && i >= 0; i--);
	toUpper(&name[++i]);

	for (int j = 0; j < len; j++) {
		if (j < len - i) putchar(name[j + i]);
		else if (j == len - i) printf(", ");
		else putchar(name[j - len + i - 1]);
	}
	
	return EXIT_SUCCESS;
}

char *toUpper(char *string) {
	if (!*string) return string;
	if (*string >= 97 && *string <= 122) *string -= 32;
	toUpper(string + 1);
	return string;
}

char *readName(FILE *fp) {
	ignoreUntill(LETTER, fp);
	return readUntil(LN, fp);
}

int ignoreUntill(char *stop, FILE *fp) {
	if (feof(fp)) return 0;
	char c = getc(fp);
	int i;
	for (i = 0; strchr(stop, c) == NULL && !feof(fp); i++, c = getc(fp));
	ungetc(c, fp);
	return i;
}

char *readUntil(char *stop, FILE *fp) {
	if (feof(fp)) return "";
	char c = getc(fp);

	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL;
	int i = 0;
	for (i = 0; strchr(stop, c) == NULL && !feof(fp); i++, c = getc(fp)) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			allocated *= 2;
			if (allocated == 0) allocated += CHUNK;
			string = (char *)realloc(string, allocated);
		}
		string[i] = c; // Escreve a entrada na memória.
	}
	if (c != EOF) ungetc(c, fp);
	if (allocated == 0) return "";
	string[i] = '\0'; // Adiciona '\0' ao final.
	string = (char *)realloc(string, (i + 1) * sizeof(char));
	return string;
}
