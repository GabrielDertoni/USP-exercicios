#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bigint.h>

char *readline(FILE *fp);

int main(int argc, char *argv[]) {
    int n;
    scanf(" %d", &n);

    for (int i = 0; i < n; i++) {
        char *input = readline(stdin);
        char *parse_ptr = input;
        char *command = strsep(&parse_ptr, " ");
        big_int_t *a = big_int_from_str(strsep(&parse_ptr, " "));
        big_int_t *b = big_int_from_str(strsep(&parse_ptr, " "));

        printf("Resultado %d: ", i + 1);

        if (!strcmp("sum", command)) {
            big_int_t *result = big_int_sum(a, b);
            big_int_println(result);
            big_int_delete(result);
        }
        else if (!strcmp("big", command))
            if (big_int_compare(a, b) > 0) printf("1\n");
            else printf("0\n");

        else if (!strcmp("sml", command))
            if (big_int_compare(a, b) < 0) printf("1\n");
            else printf("0\n");

        else if (!strcmp("eql", command))
            if (big_int_compare(a, b) == 0) printf("1\n");
            else printf("0\n");

        else fprintf(stderr, "Erro: Comando não reconhecido\n");

        big_int_delete(a);
        big_int_delete(b);
        free(input);
    }

    return EXIT_SUCCESS;
}

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

