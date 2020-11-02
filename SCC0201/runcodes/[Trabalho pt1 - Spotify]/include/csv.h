#ifndef __CSV_H__
#define __CSV_H__

#include <stdlib.h>
#include <stdbool.h>
#include <parsing.h>

typedef struct _csv csv_t;

typedef enum {
    INTEGER,
    DOUBLE,
    STRING,
    GENERIC,
    NOTHING
} primitive_type_t;

typedef union {
    int32_t   as_int;
    double    as_double;
    char *    as_string;
    void *    as_generic;
} value_t;

csv_t *csv_create();
void csv_destroy(csv_t *csv);
void csv_add_column(csv_t *csv, const char *column_name, const primitive_type_t type);
void csv_load(csv_t *csv, const char *fname);

// Acesso a informações contidas em csv_t.
value_t **csv_get_values(csv_t *csv);
uint csv_get_rows(csv_t *csv);
int csv_get_field_index(csv_t *csv, char *field_name);

// Outros
char *type_to_string(primitive_type_t type);
void csv_print_header(csv_t *csv);

#endif
