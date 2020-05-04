#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define BOOL int
#define FALSE 0
#define TRUE 1
#define CHUNK 128

char *readWhile(BOOL (*condition)(int)); // Lê stdin até que endInput(getchar()) == TRUE
char _readWhile(char **, int, ...);
BOOL isLetter(int);
BOOL isSpace(int);

int main(int argc, char *argv[]) {
	char *name = NULL;
	char last = _readWhile(&name, 2, isLetter, isSpace);
	return 0;
}

BOOL isLetter(int c) {
	return (c >= 97 && c <= 122) || (c >= 65 && c <= 90);
}

BOOL isSpace(int c) {
	return c == ' ';
}

BOOL isLine(int c) {
	return !(c == EOF || c == '\n' || c == '\r');
}

BOOL or(int input, int argc, va_list funcs) {
	BOOL result = FALSE;
	for (int i = 0; i < argc; i++) {
		BOOL (*func)(int) = (BOOL (*)(int))va_arg(funcs, BOOL (*)(int));
		result |= func(input);
	}

	return result;
}

char _readWhile(char **result, int argc, ...) {
	va_list args;
	va_start(args, argc);
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = CHUNK + 1;
	char *string = (char *)malloc(allocated); // Aloca chunk de memória.
	int c = getchar();
	int i;
	for (i = 0; or(c, argc, args); i++) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			allocated += CHUNK;
			char *temp = (char *)realloc(string, allocated);
			string = temp;
		}
		string[i] = (int)c; // Escreve a entrada na memória.
		c = getchar();
		va_start(args, argc);
		va_end(args);
	}
	string[i] = '\0'; // Adiciona '\0' ao final.

	*result = string;
	return c;
}

char *readWhile(BOOL (*condition)(int)) {
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = CHUNK + 1;
	char *string = (char *)malloc(allocated); // Aloca chunk de memória.
	char c = getchar();
	int i;
	for (i = 0; condition(c); i++) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			allocated += CHUNK;
			char *temp = (char *)realloc(string, allocated);
			string = temp;
		}
		string[i] = c; // Escreve a entrada na memória.
		c = getchar();
	}
	string[i] = '\0'; // Adiciona '\0' ao final.

	return string;
}
