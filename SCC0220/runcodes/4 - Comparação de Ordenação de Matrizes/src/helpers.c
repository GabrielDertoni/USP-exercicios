#include <stdio.h>
#include <stdlib.h>
#include <helpers.h>
#include <string.h>

int strcompare(char *stra, char *strb) {
    for (; *stra && lower(*stra) == lower(*strb); stra++, strb++);
    if (lower(*stra) > lower(*strb)) return  1;
    if (lower(*stra) < lower(*strb)) return -1;
    return 0;
}

int reverseStrCompare(elem_t a, elem_t b) {
    return -strcompare(a, b);
}

/*
void swap(elem_t *a, elem_t *b) {
    elem_t tmp = *a;
    *a = *b;
    *b = tmp;
}
*/

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
        str = (char *)maybeRealloc((void *)str, (i + 1) * sizeof(char), &alloc);
        str[i] = c;
    }
    if (c != EOF) ungetc(c, fp);
    if (alloc == 0) return NULL;
    str[i] = '\0';

    return (char *)realloc(str, (i + 1) * sizeof(char));
}
