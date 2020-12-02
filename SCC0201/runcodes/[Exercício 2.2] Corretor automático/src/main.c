#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <utils.h>
#include <parsing_utils.h>
#include <file.h>
#include <hashset.h>
#include <generic.h>
#include <json_model.h>

// Converte uma string para caixa baixa.
// NOTE: Essa operação modifica a string original.
char *to_lower(char *str) {
    for (char *ptr = str; *ptr; ptr++)
        if (*ptr >= 'A' && *ptr <= 'Z')
            *ptr += 32;

    return str;
}

// Estrai todas as palavras de um corpo de texto e as coloca em um hashset.
// NOTE: Operação que modifica a string passada como parâmetro e dá free ao final.
hashset_t *extract_words(char *contents) {
    hashset_t *hashset = hashset_create();
    char *ptr = contents;
    char *word;
    while (*ptr) {
        parse_until(LETTERS, &ptr);
        word = parse_some(LETTERS, &ptr);
        if (*ptr) *(ptr++) = '\0';

        to_lower(word);
        if (*word && !hashset_contains(hashset, word))
            hashset_insert(hashset, strdup(word));
    }
    free(contents);
    return hashset;
}

#pragma pack(1)
struct tweet {
    char *text;
};

#pragma pack(1)
struct statuses {
    struct tweet *vec;
    int size;
};

#pragma pack(1)
struct tweets {
    struct statuses *statuses;
};

int main(int argc, char *argv[]) {
    generic_t *tweets_gen = GEN_STRUCT(1,
        GEN_SFIELD("statuses", GEN_POINTER(GEN_STRUCT(2,
            GEN_SFIELD("vec", GEN_POINTER(GEN_STRUCT(1,
                GEN_SFIELD("text", GEN_STRING)
            ))),
            GEN_SFIELD("size", GEN_INT)
        )))
    );

    char *fbook_name = readline(stdin);
    char *ftweet_name = readline(stdin);

    char *book_contents = fread_contents(fbook_name);
    hashset_t *words_set = extract_words(book_contents);

    struct tweets tweets;
    if (json_parse_model_file(ftweet_name, &tweets, tweets_gen, PARSE_SOME) != PARSER_SUCCESS) {
        fprintf(stderr, "Error while reading json file...\n");
        free(ftweet_name);
        exit(1);
    }

    if (tweets.statuses) {
        for (int i = 0; i < tweets.statuses->size; i++) {
            char *tweet_text = strdup(tweets.statuses->vec[i].text);

            char *ptr = tweet_text, *word;
            while (*ptr) {
                parse_until(LETTERS, &ptr);
                word = parse_some(LETTERS, &ptr);
                if (*ptr) *(ptr++) = '\0';

                // Armazena a palavra num vetor temporário na stack (como é uma
                // única palavra, não deve ocupar muito espaço). Utilizado para
                // preservar caixa alta e baixa.
                size_t len = strlen(word);
                char tmp_word[len];
                memcpy(tmp_word, word, (len + 1) * sizeof(char));

                if (!hashset_contains(words_set, to_lower(word)))
                    printf("%s ", tmp_word);
            }
            printf("\n");

            free(tweet_text);
        }

        for (int i = 0; i < tweets.statuses->size; i++)
            free(tweets.statuses->vec[i].text);

        free(tweets.statuses->vec);
        free(tweets.statuses);
    } else {
        printf("No tweets to check\n");
    }

    generic_free(tweets_gen);
    hashset_delete(words_set);
    free(ftweet_name);
    free(fbook_name);

    return EXIT_SUCCESS;
}

