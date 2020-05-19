#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros para parsing.
#define LN "\r\n"
#define LLETTER "abcdefghijklmnopqrstuvwxyz"
#define ULETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTER LLETTER ULETTER
#define DIGIT "0123456789"

// Macros para quantidade de alocação.
#define CHUNK 32
#define WORD_CHUNK 16

// Compara duas strings e as torna lower case.
int lowerStrCompare(void *a, void *b);
// Quick sort com função de comparação parametrizada.
void sortWith(void **begin, void **end, int (*compare)(void *a, void *b));
// Lê palavras da entrada padrão até o fim da linha.
int readWords(char ***write);
// Lê uma única palavra da entrada padrão sem pular linha.
char *readWordInline();
// Lê caracteres até que um caractere dentro de char *stop seja encontrado.
char *readUntil(char *stop, FILE *fp);
// Lê caracteres até que um caractere fora de char *chars seja encontrado.
char *readSome(char *chars, FILE *fp);
// Libera a string que recebe (é essencialmente syntactic sugar para free())
void ignore(char *str);

int main(int argc, char *argv[]) {
	char **words;
	int n_words = readWords(&words);
	int op;
	scanf("%d", &op);

	if (op == 2)
		sortWith((void **)words, (void **)words + n_words, lowerStrCompare);

	for (int i = 0; i < n_words; i++)
		printf("%s\n", words[i]);

	for (int i = 0; i < n_words; i++)
		free(words[i]);

	free(words);
	
	return EXIT_SUCCESS;
}

int lowerStrCompare(void *a, void *b) {
	char *stra = (char *)a;
	char *strb = (char *)b;
	if (*stra == '\0' && *strb == '\0') return 0;
	if (*strb == '\0') return 1;
	if (*stra == '\0') return -1;
	if (*stra >= 65 && *stra <= 90) *stra += 32;
	if (*strb >= 65 && *strb <= 90) *strb += 32;
	if (*stra > *strb) return 1;
	if (*stra < *strb) return -1;
	return lowerStrCompare(a + 1, b + 1);
}

void sortWith(void **begin, void **end, int (*compare)(void *a, void *b)) {
	// Range [start, end)
	// compare -> 1: a > b, -1: a < b, 0: a = b
	if (end - begin <= 1) return;

	void **p1 = begin + 1;
	void **p2 = end - 1;
	while(p1 != p2) {
		if (compare(*p1, *begin) > 0 && compare(*p2, *begin) <= 0) {
			void *temp = *p1;
			*p1 = *p2;
			*p2 = temp;
		}
		if (compare(*p1, *begin) <= 0) p1++;
		else if (compare(*p2, *begin) > 0) p2--;
	}
	if (compare(*p1, *begin) > 0) p1--;
	void *temp = *p1;
	*p1 = *begin;
	*begin = temp;
	sortWith(begin, p1, compare);
	sortWith(p1 + 1, end, compare);
}

int readWords(char ***write) {
	int allocated = 0;
	char *word;
	char **words = NULL;
	int i;
	for (i = 0; strlen((word = readWordInline())) != 0; i++) {
		if (i >= allocated) {
			allocated *= 2;
			if (allocated == 0) allocated += WORD_CHUNK;
			words = (char **)realloc(words, allocated * sizeof(char *));
		}
		words[i] = word;
	}
	words = (char **)realloc(words, i * sizeof(char *));
	*write = words;
	return i;
}

char *readWordInline() {
	// Ignora espaços anteriores à palavra.
	ignore(readUntil(LETTER DIGIT LN, stdin));
	return readSome(LETTER DIGIT, stdin);
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
