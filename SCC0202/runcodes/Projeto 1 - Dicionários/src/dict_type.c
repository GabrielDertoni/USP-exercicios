#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dict_type.h>

int compare_entry_words(dict_entry_t *a, dict_entry_t *b) {
    if (!a) return -1;
    if (!b) return 1;
    return strcmp(a->word, b->word);
}

int compare_entry_word_ini(dict_entry_t *a, dict_entry_t *b) {
    if (!a) return -1;
    if (!b) return 1;
    return *(a->word) - *(b->word);
}

dict_entry_t *dict_entry_create(char *word, char *definition) {
    dict_entry_t *entry = (dict_entry_t *)malloc(sizeof(dict_entry_t));
    entry->word = word;
    entry->definition = definition;
    return entry;
}

dict_entry_t dict_entry_search(char *word) {
    dict_entry_t entry = {
        .word = word,
        .definition = NULL
    };
    return entry;
}

void dict_entry_delete(dict_entry_t *entry) {
    if (!entry) return;
    free(entry->word);
    free(entry->definition);
    free(entry);
}
