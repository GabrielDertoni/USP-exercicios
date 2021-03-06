#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils.h>

char *readline(FILE *fp) {
    char *str = NULL;
    int i, c;
    size_t alloc;
    while (strchr("\r\n", c = getc(fp)) && !feof(fp));
    for (i = 0, alloc = 0; !strchr("\r\n", c) && !feof(fp); i++, c = getc(fp)) {
        if ((i + 1) * sizeof(char) >= alloc) {
            if ((alloc *= 2) == 0) alloc = 32 * sizeof(char);
            str = (char *)realloc((void *)str, alloc);
        }
        str[i] = c;
    }

    if (c != EOF) ungetc(c, fp);
    if (alloc == 0) return NULL;
    str[i] = '\0';
    return realloc(str, (i + 1) * sizeof(char));
}

