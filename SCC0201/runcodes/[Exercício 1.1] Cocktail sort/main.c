#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 32

typedef struct {
    char *name;
    char *city;
} person_t;
typedef int (*comp_t)(person_t *, person_t *); // Função de comparação

char lower(char c); // Retorna o caractere em caia baixa.
int noCaseStrCompare(char *a, char *b); // Comapara strings sem considerar caixa alta.
int nameCompare(person_t *a, person_t *b); // Compara o nome de duas pessoas.
// Performa cocktail sort com uma determinada função de comparação.
void cocktailSortWith(person_t **begin, person_t **end, comp_t comp);
void swap(person_t **a, person_t **b);

// Realoca ptr se used >= allocated e muda o valor de allocated para a nova
// quantidade alocada.
void *maybeReallocate(void *ptr, const size_t used, size_t *allocated);

// Consome caracteres até que algum caractere contido em stop seja encontrado.
// Retorna uma string com os caracteres lidos.
char *readUntil(char *stop, FILE *fp);

// Consome caracteres de fp contidas em chars até um caractere que não esteja
// contido em chars seja lido retorna o número de caracteres consumidos.
int skipSome(char *chars, FILE *fp);

// Lê informações de uma struct person_t no formato <nome>. <cidade>.
person_t *readPerson();

// Performa buscabinária de acordo com o nome de uma pessoa.
person_t **binSearchPersonWithName(char *key, person_t **start, person_t **end);

int main(void) {
    int n, k;
    person_t **people;
    scanf(" %d", &n);

    people = (person_t **)malloc(n * sizeof(person_t *));
    for (int i = 0; i < n; i++)
        people[i] = readPerson();

    skipSome(". \r\n", stdin); // Consome excedentes da leitura anterior.

    cocktailSortWith(people, people + n, nameCompare);
    for (int i = 0; i < n; i++)
        printf("%s.\n", people[i]->name);

    scanf(" %d", &k);
    for (int i = 0; i < k; i++) {
        skipSome(". \r\n", stdin); // Consome excedentes da leitura anterior.
        char *search = readUntil(".\r\n", stdin);
        person_t **result = binSearchPersonWithName(search, people, people + n);

        if (!result) // Nunca deveria acontecer.
            printf("No person with such name was found...\n");
        else
            printf("%d\n", !strcmp((*result)->city, "Sao Carlos") ? 1 : 0);

        free(search);
    }

    while(n--) {
        free(people[n]->name);
        free(people[n]->city);
        free(people[n]);
    }

    free(people);

    return EXIT_SUCCESS;
}

char lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

int noCaseStrCompare(char *a, char *b) {
    for (; *a && *b && lower(*a) == lower(*b); a++, b++);
    if (lower(*a) > lower(*b)) return 1;
    if (lower(*a) < lower(*b)) return -1;
    return 0;
}

int nameCompare(person_t *a, person_t *b) {
    return noCaseStrCompare(a->name, b->name);
}

void cocktailSortWith(person_t **begin, person_t **end, comp_t comp) {
    while (begin < end) {
        for (person_t **up = begin + 1; up < end; up++)
            if (comp(*(up - 1), *up) > 0)
                swap(up - 1, up);

        end--;
        for (person_t **down = end - 2; down >= begin; down--)
            if (comp(*down, *(down + 1)) > 0)
                swap(down, down + 1);

        begin++;
    }
}

person_t **binSearchPersonWithName(char *key, person_t **start, person_t **end) {
    if (start >= end) return NULL;

    person_t **pivot = start + (end - start) / 2;
    if (noCaseStrCompare(key, (*pivot)->name) > 0)
        return binSearchPersonWithName(key, pivot + 1, end);

    if (noCaseStrCompare(key, (*pivot)->name) < 0)
        return binSearchPersonWithName(key, start, pivot);

    return pivot;
}

person_t *readPerson() {
    person_t *person = (person_t *)malloc(sizeof(person_t));
    skipSome(". \r\n", stdin);
    person->name = readUntil(".", stdin);
    skipSome(". ", stdin);
    person->city = readUntil(".", stdin);
    return person;
}

void swap(person_t **a, person_t **b) {
    person_t *tmp = *a;
    *a = *b;
    *b = tmp;
}

void *maybeReallocate(void *ptr, const size_t used, size_t *allocated) {
    if (used >= *allocated) {
        if (*allocated == 0) *allocated = CHUNK;
        else *allocated *= 2;

        return realloc(ptr, *allocated);
    }
    return ptr;
}

char *readUntil(char *stop, FILE *fp) {
    size_t allocated = 0;
    char *string = NULL;
    int c, i;
    for (i = 0; !strchr(stop, c = getc(fp)) && !feof(fp); i++) {
        string = (char *)maybeReallocate((void *)string, i * sizeof(char), &allocated);
        string[i] = (char)c;
    }
    if (c != EOF) ungetc(c, stdin);
    if (allocated == 0) return NULL;
    string[i] = '\0';
    return realloc(string, (i + 1) * sizeof(char));
}

int skipSome(char *chars, FILE *fp) {
    int c, i;
    for (i = 0; strchr(chars, c = getc(fp)) && !feof(fp); i++);
    if (c != EOF) ungetc(c, stdin);
    return i;
}
