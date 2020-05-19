#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros para parsing
#define LN "\r\n"
#define SPACE " "
#define LLETTER "abcdefghijklmnopqrstuvwxyz"
#define ULETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTER LLETTER ULETTER
#define DIGIT "0123456789"

// Macros para quantidade de alocação.
#define CHUNK 32
#define NAME_CHUNK = 10;

char *readName(FILE *fp);
void sortNames(char **begin, char **end);
int ignoreUntill(char *stop, FILE *fp);
char *readUntil(char *stop, FILE *fp);

int main(int argc, char *argv[]) {
	char **names = (char **)malloc(5 * sizeof(char *));
	for (int i = 0; i < 5; i++)
		names[i] = readName(stdin);

	sortNames(names, names + 5);
	for (int i = 0; i < 5; i++)
		printf("%s\n", names[i]);

	return EXIT_SUCCESS;
}

void sortNames(char **begin, char **end) {
	// Range [start, end)
	// compare -> 1: a > b, -1: a < b, 0: a = b
	if (end - begin <= 1) return;

	char **p1 = begin + 1;
	char **p2 = end - 1;
	while(p1 != p2) {
		if (strcmp(*p1, *begin) > 0 && strcmp(*p2, *begin) <= 0) {
			void *temp = *p1;
			*p1 = *p2;
			*p2 = temp;
		}
		if (strcmp(*p1, *begin) <= 0) p1++;
		else if (strcmp(*p2, *begin) > 0) p2--;
	}
	if (strcmp(*p1, *begin) > 0) p1--;
	void *temp = *p1;
	*p1 = *begin;
	*begin = temp;
	sortNames(begin, p1);
	sortNames(p1 + 1, end);
}

char *readName(FILE *fp) {
	ignoreUntill(LETTER DIGIT, fp);
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

