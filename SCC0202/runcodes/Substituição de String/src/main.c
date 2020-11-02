#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <helpers.h>

#define LIMIT 100

bool is_prefix_of(const char *prefix, const char *str) {
    if (!*prefix) return true;
    if (!*str) return false;
    if (*prefix == *str) return is_prefix_of(prefix + 1, str + 1);
    return false;
}

char *search_and_replace(const char *str, const char *find, const char *repl) {
    int str_len = strlen(str);
    int find_len = strlen(find);
    int repl_len = strlen(repl);
    int res_len = str_len;
    char *result = (char *)malloc(str_len * sizeof(char));

    if (find_len > str_len)
        return strcpy(result, str);

    int i = 0, j = 0;
    while (i < str_len && i < LIMIT) {
        if (!is_prefix_of(find, str + i))
            result[j++] = str[i++];
        else {
            if (find_len != repl_len) {
                res_len += find_len - repl_len;
                result = realloc(result, res_len * sizeof(char));
            }
            strncpy(result + j, repl, repl_len * sizeof(char));
            j += repl_len;
            i += find_len;
        }
    }
    if (i == LIMIT)
        strncpy(result + j, str + i, (str_len - i + 1) * sizeof(char));

    return result;
}

int main(int argc, char *argv[]) {
    char *line = NULL, *error = NULL, *replace = NULL, *fixed = NULL;
    while ((line = readLine(stdin)) &&
           (error = readLine(stdin)) &&
           (replace = readLine(stdin))) {

        fixed = search_and_replace(line, error, replace);
        printf("%s\n", fixed);

        free(fixed);   fixed   = NULL;
        free(line);    line    = NULL;
        free(error);   error   = NULL;
        free(replace); replace = NULL;
    }

    // Libera qualquer memória que tenha ficado alocada.
    if (fixed) free(fixed);
    if (line) free(line);
    if (error) free(error);
    if (replace) free(replace);

    return EXIT_SUCCESS;
}
