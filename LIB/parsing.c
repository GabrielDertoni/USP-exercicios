#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros para parsing
#define LN "\r\n"
#define SPACE " "
#define COMMA ","
#define DOT "."
#define SQUO "'"
#define DQUO "\""
#define LLETTER "abcdefghijklmnopqrstuvwxyz"
#define ULETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTER LLETTER ULETTER
#define DIGIT "0123456789"
#define SIGN "-+"

// Macros para quantidade de alocação.
#define CHUNK 32

int ignoreUntill(char *stop, FILE *fp) {
	if (feof(fp)) return 0;
	char c = getc(fp);
	int i;
	for (i = 0; strchr(stop, c) == NULL && !feof(fp); i++, c = getc(fp));
	ungetc(c, fp);
	return i;
}

int ignoreSome(char *chars, FILE *fp) {
	if (feof(fp)) return 0;
	char c = getc(fp);
	int i;
	for (i = 0; strchr(chars, c) != NULL && !feof(fp), i++, c = getc(fp));
	ungetc(c, fp)
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
			// Garante que haverá espaço para o \0
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

char *readSome(char *chars, FILE *fp) {
	if (feof(fp)) return "";
	char c = getc(fp);
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL;
	int i = 0;
	for (i = 0; strchr(chars, c) != NULL && !feof(fp); i++, c = getc(fp)) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			// Garante que haverá espaço para o \0
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

void ignore(char *str) {
	if (str != NULL && strlen(str) > 0)
		free(str);
}
