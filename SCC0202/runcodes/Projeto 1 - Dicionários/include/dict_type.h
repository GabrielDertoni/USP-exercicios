#ifndef __TYPES_H__
#define __TYPES_H__

typedef struct {
    char *word;
    char *definition;
} dict_entry_t;

dict_entry_t *dict_entry_create(char *word, char *definition);
dict_entry_t dict_entry_search(char *word);
void dict_entry_delete(dict_entry_t *entry);
int compare_entry_words(dict_entry_t *a, dict_entry_t *b);
int compare_entry_word_ini(dict_entry_t *a, dict_entry_t *b);


#endif
