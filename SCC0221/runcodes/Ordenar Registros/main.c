#include <stdio.h>
#include <stdlib.h>

#define BOOL int
#define FALSE 0
#define TRUE 1
#define CHUNK 128
#define ITEM_CHUNK 10

typedef struct Item {
	char *title;
	int date;
} item_t;

// Lê stdin até que endInput(getchar()) == TRUE
// Retorna a caracter que determinou o final da leitura.
char readLine(char **result, FILE *fp);
int length(char *str);
int readInt(FILE *fp);
char readItem(item_t **result, FILE *fp);
int readItems(item_t ***result, FILE *fp);
void sortWith(void **list, int start, int end, int (*)(void *a, void *b));
int compare_dates(void *a, void *b);
int compare_titles(void *a, void *b);
int strcompare(char *a, char *b);
char toLower(char c);
BOOL isSpace(int);
BOOL isDigit(int c);
BOOL isPartOfNumber(int c);
BOOL isLine(int c);

int main(int argc, char *argv[]) {
	int order = readInt(stdin);
	item_t **items;
	int item_count = readItems(&items, stdin);

	if (order == 1)
		sortWith((void **)items, 0, item_count - 1, compare_titles);
	else
		sortWith((void **)items, 0, item_count - 1, compare_dates);

	for (int i = 0; i < item_count; i++)
		printf("%d\t%s\n", items[i]->date, items[i]->title);

	return 0;
}

int readItems(item_t ***result, FILE *fp) {
	int allocated = ITEM_CHUNK;
	int item_count;
	item_t **items = (item_t **)malloc(sizeof(item_t *) * allocated);
	item_t *item;
	for(item_count = 0; !feof(fp); item_count++) {
		readItem(&item, fp);
		if (item != NULL) {
			if (item_count >= allocated) {
				allocated += ITEM_CHUNK;
				items = (item_t **)realloc(items, sizeof(item_t *) * allocated);
			}
			items[item_count] = item;
		}
	}
	if (item_count == 0) {
		free(items);
		return 0;
	}
	// Realoca para que apenas o necessário continue alocado.
	items = (item_t **)realloc(items, sizeof(item_t *) * item_count);
	*result = items;
	return item_count;
}

char toLower(char c) { return (c >= 65 && c <= 90) ? c + 32 : c; }
int strcompare(char *a, char *b) {
	if (*a == '\0' || *b == '\0') return *a == '\0' ? (*b == '\0' ? 0 : -1) : 1;
	else if (toLower(*a) > toLower(*b)) return 1;
	else if (toLower(*a) < toLower(*b)) return -1;
	else return strcompare(a + 1, b + 1);
}
// Compara os títulos de dois itens a partir de pointeiros void (feito para ser usado com sortWith).
int compare_titles(void *a, void *b) {
	item_t *x = (item_t *)a;
	item_t *y = (item_t *)b;
	return strcompare(x->title, y->title);
}
// Compara as datas de de dois itens a partir de pointeiros void (usado com sortWith).
int compare_dates(void *a, void *b) {
	item_t *x = (item_t *)a;
	item_t *y = (item_t *)b;
	return x->date > y->date ? 1 : (x->date < y->date ? -1 : 0);
}

// Implementação de Quick Sort geral para quaquer lista de ponteiros e qualquer função de
// comparação. Essa função de comparação deve receber os dois elementos a serem comparados como void *
// e retornar 1 caso a > b, -1 caso 1 a < b e 0 caso a = b. Start representa o índice de início para
// a ordenação da lista, e end o final.
void sortWith(void **list, int start, int end, int (*compare)(void *a, void *b)) {
	// Range (start]
	// compare -> 1: a > b, -1: a < b, 0: a = b
	if (abs(start - end) <= 1) return;

	void *pivot = list[start];
	int p1 = start + 1;
	int p2 = end;
	while(p1 != p2) {
		// If the pointer from the left side is bigger than the pivot and the pointer from
		// the right is smaller or equal to the pivot, swap them.
		if (compare(list[p1], pivot) == 1 && compare(list[p2], pivot) != 1) {
			void *temp = list[p1];
			list[p1] = list[p2];
			list[p2] = temp;
		}
		// Usa else if para garantir que ambos os índices não avancem ao mesmo tempo, o que
		// pularia a verificação de p1 == p2 em alguns casos.
		if (compare(list[p1], pivot) == -1) p1++;
		else if (compare(list[p2], pivot) == 1) p2--;
	}
	if (compare(list[p1], pivot) == 1) {
		void *temp = list[p1 - 1];
		list[p1 - 1] = pivot;
		list[start] = temp;
		sortWith(list, start, p1 - 1, compare);
		sortWith(list, p1, end, compare);
	} else {
		void *temp = list[p1];
		list[p1] = pivot;
		list[start] = temp;
		sortWith(list, start, p1, compare);
		sortWith(list, p1 + 1, end, compare);
	}
}

char readItem(item_t **result, FILE *fp) {
	char *line;
	char last = readLine(&line, fp);
	if (line == NULL) {
		*result = NULL;
		return EOF;
	}
	int lineLenght = length(line);

	int digitsStart; // Encontra o índice onde o número começa.
	for (digitsStart = lineLenght - 1;
		 digitsStart >= 0 && (isPartOfNumber(line[digitsStart]) || isSpace(line[digitsStart]));
		 digitsStart--);
	digitsStart += 1; // Ajusta para que digitsStart seja um indice inclusivo.
	item_t *item = (item_t *)malloc(sizeof(item_t));
	// Star Wars ep 5: O Império Contra Ataca 1980 \0
	item->date = atoi(line + digitsStart);
	// Realoca a memória da string para que apenas o nome continue contido nela.
	item->title = (char *)realloc(line, sizeof(char) * (digitsStart + 1));
	item->title[digitsStart] = '\0';

	*result = item;
	return last;
}

int readInt(FILE *fp) {
	char *word;
	readLine(&word, fp);
	return atoi(word);
}

BOOL isDigit(int c) { return c >= 48 && c <= 57; }
BOOL isSpace(int c) { return c == ' '; }
BOOL isLine(int c) { return !(c == '\n' || c == '\r'); }
BOOL isPartOfNumber(int c) { return isDigit(c) || c == '.' || c == '-'; }

int length(char *str) {
	int i;
	for (i = 0; str[i] != '\0'; i++);
	return i;
}

char readLine(char **result, FILE *fp) {
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL; // Aloca chunk de memória.
	char c = getc(fp);
	if (feof(fp)) {
		*result = NULL;
		return EOF;
	}
	// Limpa o buffer de \n ou \r
	while(!isLine(c) && !feof(fp)) c = getc(fp);
	int i;
	for (i = 0; isLine(c) && !feof(fp); i++) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			// Garante que haverá espaço para o \0
			if (allocated == 0) {
				allocated = CHUNK + 1;
				string = (char *)malloc(allocated);
			} else {
				allocated += CHUNK;
				string = (char *)realloc(string, allocated);
			}
		}
		string[i] = c; // Escreve a entrada na memória.
		c = getc(fp);
	}
	string[i] = '\0'; // Adiciona '\0' ao final.
	*result = string;
	return c;
}
