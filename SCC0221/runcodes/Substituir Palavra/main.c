#include <stdio.h>
#include <stdlib.h>

#define BOOL short int
#define TRUE 1
#define FALSE 0

// Define o tipo lstring_t (Linked List String Type). Cada struct armazena um único caractere e uma
// referência para o próximo struct.
typedef struct LinkedString {
	char chr;
	struct LinkedString *next;
} lstring_t;

// Lê uma palavra da entrada padrão e a armazena em write. Retorna o caractere imediatamente após
// o término da palavra mas que não a pertence. clear define se o buffer de entrada deve ser limpo
// antes da leitura.
int readWord(lstring_t **write, BOOL clear);
BOOL endLine(int c); // Retorna TRUE se c for um caractere de término de linha, FALSE caso contrário.
BOOL endWord(int c); // Returna TRUE se c for um caractere de término de palavra, FALSE caso contrário.
BOOL linkedEqual(lstring_t *str1, lstring_t *str2); // Returna str1 == str2 para lstring_t.
int clearBuff(); // Limpa o buffer de entrada de caracteres de término de palavra e retorna o próxima caractere.
void printLinked(lstring_t *str); // Imprime uma string lstring_t.
void freeLinked(lstring_t *str); // Libera toda a memória alocada numa lstring_t.

int main(int argc, char *argv[]) {
	lstring_t *search = NULL;
	lstring_t *replace = NULL;

	readWord(&search, TRUE); // Lê as outras caracteres da palavra.
	readWord(&replace, TRUE);

	lstring_t *buffer = NULL; // Inicializa um buffer que armazenará a palavra atualmente sendo processada.
	int c = readWord(&buffer, TRUE); // Limpa o buffer antes da primeira letra da frase. Frase não pode começar com ' '.
	do {
		if (buffer == NULL) c = readWord(&buffer, FALSE);
		if (linkedEqual(buffer, search)) // Se a palavra for a que estamos procurando, substitua ela.
			printLinked(replace);
		else // Se não, apenas imprima a palavra original.
			printLinked(buffer);

		if (buffer != NULL) freeLinked(buffer); // Libera memória armazenada no buffer.
		buffer = NULL;

		if (!endLine(c) && c != EOF) putchar(c); // Imprime a caractere imediatamente após a palavra mas que não a pertence.
	} while(!endLine(c) && c != EOF); // Repete até que a linha termine ou o arquivo.

	return 0;
}
BOOL linkedEqual(lstring_t *str1, lstring_t *str2) {
	if (str1 != NULL && str2 != NULL)
		if (str1->chr == str2->chr) return linkedEqual(str1->next, str2->next);
		else return FALSE;
	else return str1 == str2;
}
void printLinked(lstring_t *str) {
	if (str != NULL) {
		putchar(str->chr);
		printLinked(str->next);
	}
}
int readWord(lstring_t **write, BOOL clear) {
	int c;
	if (clear) c = clearBuff();
	else c = getchar();

	if (!endWord(c) && c != EOF) {
		lstring_t *pointer = (lstring_t *)malloc(sizeof(lstring_t));
		pointer->chr = c;
		*write = pointer;
		return readWord(&pointer->next, FALSE);
	} else *write = NULL;
	return c;
}
BOOL endLine(int c) {
	return c == '\n' || c == '\r';
}
BOOL endWord(int c) {
	return c == ' ' || c == '.' || c == ',' || c == '?' || endLine(c);
}
int clearBuff() {
	int c;
	do c = getchar();
	while (endLine(c) || c == ' ');
	return c;
}
void freeLinked(lstring_t *str) {
	if (str->next != NULL)
		freeLinked(str->next);

	free(str);
}
