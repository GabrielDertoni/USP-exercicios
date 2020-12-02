#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <skip_list.h>
#include <dict_type.h>
#include <utils.h>

bool insert_operation(skip_list_t *list, char *word, char *definition);
bool update_operation(skip_list_t *list, char *word, char *replace_def);
bool remove_operation(skip_list_t *list, char *word);
bool search_operation(skip_list_t *list, char *word);
bool print_operation(skip_list_t *list, char c);

int main(int argc, char *argv[]) {
    char *line;
    skip_list_t *list = skip_list_create(compare_entry_words, NULL, 10);

    while ((line = readline(stdin))) {
        bool success;
        char *trim = trimstr(line);
        char *command = strsep(&trim, " ");
        char *word = strsep(&trim, " ");

        if (!strcmp("insercao", command))
            success = insert_operation(list, word, trim);

        else if (!strcmp("alteracao", command))
            success = update_operation(list, word, trim);
            
        else if (!strcmp("remocao", command))
            success = remove_operation(list, word);

        else if (!strcmp("busca", command))
            success = search_operation(list, word);

        else if (!strcmp("impressao", command))
            success = print_operation(list, word[0]);

        else
            success = false;

        if (!success) {
            if (!strcmp("impressao", command))
                printf("NAO HA PALAVRAS INICIADAS POR %c\n", word[0]);
            else
                printf("OPERACAO INVALIDA\n");
        }
        
        free(line);
    }

    skip_list_destroy(list, dict_entry_delete);
    return EXIT_SUCCESS;
}

bool insert_operation(skip_list_t *list, char *word, char *definition) {
    dict_entry_t *entry = dict_entry_create(strdup(word), strdup(definition));
    bool res = skip_list_insert(list, entry);
    if (!res) dict_entry_delete(entry);
    return res;
}

bool update_operation(skip_list_t *list, char *word, char *replace_def) {
    // Alocado na stack e temporário, apenas necessário para a busca.
    dict_entry_t search = dict_entry_search(word);
    skip_node_t *node = skip_list_find(list, &search);
    if (!node) return false;

    dict_entry_t *old = skip_node_value(node);
    free(old->definition);

    old->definition = strdup(replace_def);

    return true;
}

bool remove_operation(skip_list_t *list, char *word) {
    dict_entry_t search = dict_entry_search(word);
    return skip_list_remove_free(list, &search, dict_entry_delete);
}

bool search_operation(skip_list_t *list, char *word) {
    dict_entry_t search = dict_entry_search(word);
    skip_node_t *node = skip_list_find(list, &search);

    if (!node)
        return false;

    dict_entry_t *entry = skip_node_value(node);
    printf("%s %s\n", entry->word, entry->definition);

    return true;
}

bool print_operation(skip_list_t *list, char c) {
    dict_entry_t search = dict_entry_search(&c);
    skip_node_t *node = skip_list_find_with(list, &search, compare_entry_word_ini);

    if (!node) return false;

    for (dict_entry_t *content = skip_node_value(node);
         node && content->word[0] == c;
         node = skip_node_next(node), content = skip_node_value(node))
        printf("%s %s\n", content->word, content->definition);

    return true;
}
