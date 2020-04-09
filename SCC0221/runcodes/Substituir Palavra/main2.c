#include <stdio.h>
#include <stdlib.h>

#define BOOL short int
#define TRUE 1
#define FALSE 0

typedef struct LinkedString {
	char chr;
	struct LinkedString *next;
} lstring_t;

BOOL endWord(int c);
BOOL endLine(int c);
lstring_t *createLink(char c);
lstring_t *appendLink(lstring_t *str, char c);
lstring_t *linkAt(int index, lstring_t *str);
lstring_t *insertLink(int index, lstring_t *str, char c);
lstring_t *readWord();
int linkedLength(lstring_t *str);
BOOL lstringEqual(lstring_t *str1, lstring_t *str2);
void freeLinked(lstring_t *str);
void printLstring(lstring_t *str);
int clearBuff();

int main(int argc, char *argv[]) {
	lstring_t *search = readWord();
	lstring_t *replace = readWord();

	int search_length = linkedLength(search);

	lstring_t *buffer = NULL;
	int i = 0;
	for (int c = clearBuff(); !endLine(c) && c != EOF; c = getchar()) {
		buffer = appendLink(buffer, c);
		if (c == linkAt(i, search)->chr) {
			i++;
			if (i == search_length) {
				printLstring(replace);
				buffer = NULL;
				i = 0;
			}
		} else {
			printLstring(buffer);
			buffer = NULL;
			i = 0;
		}
	}

	return 0;
}

lstring_t *readWord() {
	lstring_t *str = NULL;
	for (int c = clearBuff(); !endWord(c); c = getchar())
		if (c == EOF) return NULL;
		else str = appendLink(str, c);

	return str;
}

BOOL lstringEqual(lstring_t *str1, lstring_t *str2) {
	lstring_t *pointer1 = str1;
	lstring_t *pointer2 = str2;
	while (pointer1->next != NULL && pointer2->next != NULL && pointer1->chr == pointer2->chr) {
		pointer1 = pointer1->next;
		pointer2 = pointer2->next;
	}
	return pointer1->chr == pointer2->chr;
}

int linkedLength(lstring_t *str) {
	int counter = 0;
	lstring_t *pointer;
	for (pointer = str; pointer != NULL; pointer = pointer->next) counter++;

	return counter;
}

// Cria um novo elemento de lista encadeada.
lstring_t *createLink(char c) {
	lstring_t *str = (lstring_t *)malloc(sizeof(lstring_t));
	str->chr = c;
	str->next = NULL;
	return str;
}

// Adiciona um novo elemento ao final da lista encadeada.
lstring_t *appendLink(lstring_t *str, char c) {
	lstring_t *newstr = createLink(c);
	if (str == NULL) return newstr;

	lstring_t *pointer;
	for (pointer = str; pointer->next != NULL; pointer = pointer->next);
	pointer->next = newstr;
	return str;
}

// Retorna o elemento num determinado índice da lista encadeada.
lstring_t *linkAt(int index, lstring_t *str) {
	lstring_t *pointer = str;
	for (int i = 0; i < index && pointer->next != NULL; i++) pointer = pointer->next;
	return pointer;
}

// Insere um novo elemento numa lista encadeada.
lstring_t *insertLink(int index, lstring_t *str, char c) {
	lstring_t *newstr = createLink(c);
	// Se o índice for 0, coloque o novo elemento no começo da cadeia.
	if (index == 0 || str == NULL) {
		newstr->next = str;
		return newstr;
	}
	lstring_t *pointer = linkAt(index - 1, str);
	// Insere o novo elemento na lista encadeada.
	newstr->next = pointer->next;
	pointer->next = newstr;
	
	return str;
}

void printLstring(lstring_t *str) {
	if (str != NULL) {
		putchar(str->chr);
		printLstring(str->next);
	}
}

void freeLinked(lstring_t *str) {
	if (str->next != NULL)
		freeLinked(str->next);

	free(str);
}

BOOL endLine(int c) {
	return c == '\n' || c == '\r';
}

BOOL endWord(int c) {
	return c == ' ' || c == ',' || c == '?' || endLine(c);
}

int clearBuff() {
	int c;
	// Limpa o buffer de \n, \r " "indesejados.
	do c = getchar();
	while (endWord(c));
	return c;
}
