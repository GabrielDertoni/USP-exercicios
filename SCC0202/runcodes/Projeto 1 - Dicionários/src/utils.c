#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

// Retorna uma string sem espaços em branco no começo e no fim.
// NOTE: modifica a string original.
char *trimstr(char *str) {
    while(str && *str == ' ') str++;
    int i;
    for (i = strlen(str) - 1; i >= 0 && str[i] == ' '; i--);
    str[i + 1] = '\0';
    return str;
}

char *readline(FILE *fp) {
    char *str = NULL;
    int i, c;
    size_t alloc;
    // Ignora \r e \n no começo da leitura.
    while (strchr("\r\n", c = getc(fp)) && !feof(fp));

    // Lê até encontrar um \r ou \n.
    for (i = 0, alloc = 0; !strchr("\r\n", c) && !feof(fp); i++, c = getc(fp)) {
        // Dobra a quantidade alocada se necessário. Resulta em log(n) reallocs.
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

