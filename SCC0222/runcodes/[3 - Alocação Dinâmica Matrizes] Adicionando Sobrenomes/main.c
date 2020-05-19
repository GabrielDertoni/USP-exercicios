#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 32

char *readUntil(char *stop, FILE *fp);

int main(int argc, char *argv[]) {
	int i = 0;
	char *prev_last_name = "";
	char *name = readUntil("\r\n", stdin);
	do {
		if (i++ % 2 == 0) {
			printf("%s\n", name);
			int last_name_idx;
			for (last_name_idx = strlen(name) - 1; last_name_idx >= 0 && name[last_name_idx] != ' '; last_name_idx--);
			prev_last_name = (char *)malloc(strlen(&name[last_name_idx + 1]) * sizeof(char));
			prev_last_name = strcpy(prev_last_name, &name[last_name_idx + 1]);
		} else {
			printf("%s %s\n", name, prev_last_name);
			free(prev_last_name);
		}
		// Ignora qualquer \r ou \n na sequência.
		char c;
		do c = getchar();
		while(c == '\r' || c == '\n');
		ungetc(c, stdin);

		free(name);
		name = readUntil("\r\n$", stdin);
	} while(strlen(name) != 0);

	if (i % 2 == 1) free(prev_last_name);
	
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
