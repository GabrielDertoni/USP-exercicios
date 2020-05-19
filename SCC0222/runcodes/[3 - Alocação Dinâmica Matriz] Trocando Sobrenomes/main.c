#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 20

char *readUntil(char *stop, FILE *fp);

int main(int argc, char *argv[]) {
	int n = 0, allocated = 0;
	char **names = NULL;
	char *name = readUntil("\r\n", stdin);
	do {
		if (n >= allocated) {
			allocated *= 2;
			if (allocated == 0) allocated += 2;
			names = (char **)realloc(names, allocated * sizeof(char *));
		}
		// Ignora qualquer \r ou \n na sequência.
		char c;
		do c = getchar();
		while(!feof(stdin) && (c == '\r' || c == '\n'));
		ungetc(c, stdin);

		names[n++] = name;
		name = readUntil("\r\n$", stdin);
	} while(strlen(name) != 0);

	names = (char **)realloc(names, n * sizeof(char *));

	for (int i = 0; i < n; i++) {
		int j, c;
		for (j = strlen(names[i]) - 1; j >= 0 && names[i][j] != ' '; j--);
		for (c = strlen(names[n - i - 1]) - 1; c >= 0 && names[n - i - 1][c] != ' '; c--);
		printf("%.*s %s\n", j, names[i], &names[n - i - 1][++c]);
	}
	
	free(names);
	return 0;
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
