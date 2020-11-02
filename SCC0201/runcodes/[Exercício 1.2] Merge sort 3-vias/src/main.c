#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro para alocação de memória
#define CHUNK 32

typedef struct {
    char *name;
    float price;
} Book;

typedef void *elem_t;
typedef int (*comp_t)(elem_t, elem_t);

Book *parseBook(char *string);
int comparePrices(elem_t el1, elem_t el2);
void debugMerge3SortWith(elem_t *start, elem_t *end, comp_t comp);
void merge3With(elem_t *start, elem_t *mid1, elem_t *mid2, elem_t *end, comp_t comp);
void *maybeRealloc(void *ptr, const size_t used, size_t *alloc);
char *readline(FILE *fp);

int main(void) {
    int n;
    scanf(" %d", &n);

    Book **collection = (Book **)malloc(n * sizeof(Book *));

    for (int i = 0; i < n; i++) {
        char *line = readline(stdin);
        Book *book = parseBook(line);
        collection[i] = book;
        free(line);
    }

    debugMerge3SortWith((elem_t *)collection, (elem_t *)(collection + n), comparePrices);
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("%s, R$%0.2f\n", collection[i]->name, collection[i]->price);
    
    for (int i = 0; i < n; i++) {
        free(collection[i]->name);
        free(collection[i]);
    }
    free(collection);

    return EXIT_SUCCESS;
}

void merge3With(elem_t *start, elem_t *mid1, elem_t *mid2, elem_t *end, comp_t comp) {
    elem_t *auxorig = (elem_t *)malloc((end - start) * sizeof(elem_t));
    elem_t *startPtr = start, *mid1Ptr = mid1, *mid2Ptr = mid2, *aux = auxorig;

    // Toma conta de juntar as partições, mesmo se startPtr == mid1
    while (mid1Ptr < mid2 && mid2Ptr < end)
        if (startPtr < mid1 && comp(*startPtr, *mid1Ptr) < 0)
            if (comp(*startPtr, *mid2Ptr) < 0)
                *(aux++) = *(startPtr++);
            else
                *(aux++) = *(mid2Ptr++);
        else
            if (comp(*mid1Ptr, *mid2Ptr) < 0)
                *(aux++) = *(mid1Ptr++);
            else
                *(aux++) = *(mid2Ptr++);
    
    // Junta as partições restantes caso mid2Ptr == end
    while (mid1Ptr < mid2 && startPtr < mid1)
        if (comp(*startPtr, *mid1Ptr) < 0)
            *(aux++) = *(startPtr++);
        else
            *(aux++) = *(mid1Ptr++);

    // Junta as partições restantes caso mid1Ptr == mid2
    while (mid2Ptr < end && startPtr < mid1)
        if (comp(*startPtr, *mid2Ptr) < 0)
            *(aux++) = *(startPtr++);
        else
            *(aux++) = *(mid2Ptr++);
    
    while (startPtr < mid1) *(aux++) = *(startPtr++);
    while (mid1Ptr  < mid2) *(aux++) = *(mid1Ptr++);
    while (mid2Ptr  < end ) *(aux++) = *(mid2Ptr++);

    memcpy(start, auxorig, (end - start) * sizeof(elem_t));
    free(auxorig);
}

void debugMerge3SortWith(elem_t *start, elem_t *end, comp_t comp) {
    if (start < end) {
        for (elem_t *ptr = start; ptr < end; ptr++)
            printf("%0.2f ", ((Book *)*ptr)->price);

        printf("\n");
    }
    
    if (start >= end - 1) return;

    // Add 2 at the end to garantee rounding up.
    elem_t *mid1 = start + (end - start + 2) / 3;
    elem_t *mid2 = start + (2 * (end - start) + 2) / 3;
    debugMerge3SortWith(start, mid1, comp);
    debugMerge3SortWith(mid1, mid2, comp);
    debugMerge3SortWith(mid2, end, comp);
    merge3With(start, mid1, mid2, end, comp);
}

int comparePrices(elem_t el1, elem_t el2) {
    Book *book1 = (Book *)el1, *book2 = (Book *)el2;
    if (book1->price > book2->price) return 1;
    if (book1->price < book2->price) return -1;
    return 0;
}

Book *parseBook(char *string) {
    // Copia para não modificar a string original
    char *copy = strdup(string);
    char *parsePtr = copy;
    Book *book = (Book *)malloc(sizeof(Book));
    book->name = strdup(strsep(&parsePtr, ","));
    book->price = (float)atof(strsep(&parsePtr, "\r\n"));
    free(copy);
    return book;
}

void *maybeRealloc(void *ptr, const size_t used, size_t *alloc) {
    if (*alloc == 0)
        return realloc(ptr, *alloc = CHUNK);

    if (used >= *alloc)
        return realloc(ptr, *alloc *= 2);

    if (used < *alloc / 2 && *alloc > CHUNK)
        return realloc(ptr, *alloc /= 2);
    
    return ptr;
}

char *readline(FILE *fp) {
    char *str = NULL;
    int i, c;
    size_t alloc;
    // Consome os primeiros \r\n
    while (strchr("\r\n", c = getc(fp)) && !feof(fp));
    // Consome até o próximo \r\n
    for (i = 0, alloc = 0; !strchr("\r\n", c) && !feof(fp); i++, c = getc(fp)) {
        str = (char *)maybeRealloc((void *)str, i * sizeof(char), &alloc);
        str[i] = c;
    }
    
    if (c != EOF) ungetc(c, fp);
    if (alloc == 0) return NULL;
    str[i] = '\0';
    return realloc(str, (i + 1) * sizeof(char));
}