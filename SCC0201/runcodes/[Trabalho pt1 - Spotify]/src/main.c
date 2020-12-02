#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sorting.h>
#include <csv.h>

#define POPULARITY_COLUMN_IDX 8
#define AUTHOR_NAME_COLUMN_IDX 4
#define AUTHOR_ID_COLUMN_IDX 5

typedef struct {
    char *name;
    char *id;
    int nsongs;
    double popularity;
} author_t;

typedef struct {
    author_t **values;
    size_t cap;
    uint size;
} author_list_t;

int compare_popularities(void *a, void *b) {
    double pop_a = ((author_t *)a)->popularity;
    double pop_b = ((author_t *)b)->popularity;
    if (pop_a > pop_b) return -1;
    else if (pop_b > pop_a) return 1;
    return 0;
}

int compare_author_ids(void *a, void *b) {
    char *id_a = ((value_t *)a)[AUTHOR_ID_COLUMN_IDX].as_string;
    char *id_b = ((value_t *)b)[AUTHOR_ID_COLUMN_IDX].as_string;
    return strcmp(id_a, id_b);
}

author_list_t extract_authors(csv_t *csv) {
    value_t **values = csv_get_values(csv);
    quick_sort_with((void **)values, (void **)(values + csv_get_rows(csv)), compare_author_ids);
    size_t alloc = 0;
    author_t **authors = NULL;

    int author_idx = -1;
    for (int i = 0; i < csv_get_rows(csv); i++) {
        if ((author_idx + 1) * sizeof(author_t *) >= alloc) {
            if ((alloc *= 2) == 0) alloc = 8 * sizeof(author_t *);
            authors = (author_t **)realloc(authors, alloc);
        }
        if (author_idx < 0 || strcmp(authors[author_idx]->id, values[i][AUTHOR_ID_COLUMN_IDX].as_string)) {
            author_t *author = (author_t *)malloc(sizeof(author_t));
            author->name = values[i][AUTHOR_NAME_COLUMN_IDX].as_string;
            author->popularity = values[i][POPULARITY_COLUMN_IDX].as_int;
            author->nsongs = 1;
            author->id = values[i][AUTHOR_ID_COLUMN_IDX].as_string;

            authors[++author_idx] = author;
        } else {
            authors[author_idx]->nsongs++;
            authors[author_idx]->popularity += values[i][POPULARITY_COLUMN_IDX].as_int;
        }
    }

    for (int i = 0; i < author_idx + 1; i++)
        authors[i]->popularity /= authors[i]->nsongs;

    author_list_t list = {
        .values = authors,
        .cap    = alloc,
        .size   = author_idx + 1,
    };
    return list;
}


char *readline(FILE *fp) {
    char *str = NULL;
    int i, c;
    size_t alloc;
    // Consome os primeiros \r\n
    while (strchr("\r\n", c = getc(fp)) && !feof(fp));
    // Consome até o próximo \r\n
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

int main(int argc, char *argv[]) {
    csv_t *csv = csv_create();

    // Adiciona todas as colunas e deixa o nome da coluna a ser inferido pelo programa.
    csv_add_column(csv, "track_name"      , STRING);
    csv_add_column(csv, "track_id"        , STRING);
    csv_add_column(csv, "album_name"      , STRING);
    csv_add_column(csv, "album_id"        , STRING);
    csv_add_column(csv, "artist_name"     , STRING);
    csv_add_column(csv, "artist_id"       , STRING);
    csv_add_column(csv, "release_date"    , STRING);
    csv_add_column(csv, "length"          , INTEGER);
    csv_add_column(csv, "popularity"      , INTEGER);
    csv_add_column(csv, "acousticness"    , DOUBLE);
    csv_add_column(csv, "danceability"    , DOUBLE);
    csv_add_column(csv, "energy"          , DOUBLE);
    csv_add_column(csv, "instrumentalness", DOUBLE);
    csv_add_column(csv, "liveness"        , DOUBLE);
    csv_add_column(csv, "loudness"        , DOUBLE);
    csv_add_column(csv, "speechiness"     , DOUBLE);
    csv_add_column(csv, "tempo"           , DOUBLE);
    csv_add_column(csv, "time_signature"  , INTEGER);

    char *fname = readline(stdin);

    csv_load(csv, fname);

    free(fname);
    author_list_t author_list = extract_authors(csv);
    author_t **authors = author_list.values;

    quick_sort_with((void **)authors,
                    (void **)(authors + author_list.size),
                    compare_popularities);

    printf("O Dataset contem %d Artistas e %d Musicas\n", (int)author_list.size, csv_get_rows(csv));
    printf("Os artistas mais populares sao:\n");
    for (int i = 0; i < author_list.size; i++)
        printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2lf, Link: https://open.spotify.com/artist/%s\n",
               i + 1, authors[i]->name, authors[i]->nsongs, authors[i]->popularity, authors[i]->id);

    for (int i = 0; i < author_list.size; i++)
        free(authors[i]);
    free(authors);

    csv_destroy(csv);

    return EXIT_SUCCESS;
}

