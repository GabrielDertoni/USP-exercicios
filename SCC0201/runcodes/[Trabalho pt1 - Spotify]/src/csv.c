#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <file.h>
#include <parsing.h>
#include <csv.h>

struct _csv {
    char **field_names;
    primitive_type_t *column_types;
    value_t **values;
    uint n_columns;
    uint n_rows;
    size_t alloc;
};

csv_t *csv_create() {
    csv_t *csv = (csv_t *)malloc(sizeof(csv_t));
    csv->field_names = NULL;
    csv->column_types = NULL;
    csv->alloc = 0;
    csv->n_columns = 0;
    csv->n_rows = 0;

    return csv;
}

void free_type(primitive_type_t type, value_t val) {
    switch (type) {
        case STRING:
        case GENERIC:
            free(val.as_generic);
            return;

        case INTEGER:
        case DOUBLE:
        case NOTHING:
        default:
            return;
    }
}

void csv_destroy(csv_t *csv) {
    for (int i = 0; i < csv->n_columns; i++)
        free(csv->field_names[i]);

    free(csv->field_names);
    for (int i = 0; i < csv->n_rows; i++) {
        for (int j = 0; j < csv->n_columns; j++)
            free_type(csv->column_types[j], csv->values[i][j]);

        free(csv->values[i]);
    }
    free(csv->values);
    free(csv->column_types);
    free(csv);
}

// NOTE: Not very efficient, but hopefully no one will use a csv with lots of columns.
void csv_add_column(csv_t *csv, const char *column_name, const primitive_type_t type) {
    csv->n_columns++;
    csv->field_names = (char **)realloc(csv->field_names, csv->n_columns * sizeof(char *));
    csv->column_types = (primitive_type_t *)realloc(csv->column_types, csv->n_columns * sizeof(primitive_type_t));
    // Duplicates the string so that column_name can be freed from the caling function.
    if (column_name == NULL)
        csv->field_names[csv->n_columns - 1] = NULL;
    else
        csv->field_names[csv->n_columns - 1] = strdup(column_name);

    csv->column_types[csv->n_columns - 1] = type;
}

value_t csv_parse_value(primitive_type_t type, const parse_result_t input) {
    value_t val;
    switch (type) {
        case INTEGER:
            val.as_int = parse_to_int(input);
            break;

        case DOUBLE:
            val.as_double = parse_to_float(input);
            break;

        case STRING:
            val.as_string = parse_to_string(input);
            break;

        case GENERIC:
            val.as_generic = (void *)parse_to_string(input);
            break;

        case NOTHING:
            val.as_generic = NULL;
            break;
    }
    return val;
}

void csv_parse_row(csv_t *csv, const parse_result_t input) {
    // Dynamically allocate memory for the rows.
    if (csv->n_rows >= csv->alloc) {
        if ((csv->alloc *= 2) == 0) csv->alloc = 32;
        csv->values = (value_t **)realloc(csv->values, csv->alloc * sizeof(value_t *));
    }
    csv->values[csv->n_rows] = (value_t *)malloc(csv->n_columns * sizeof(value_t));
    int i = 0;
    parse_result_t pfield = parse_some(" ", input);
    do {
        pfield = parse_split(";\r\n", pfield);
        csv->values[csv->n_rows][i] = csv_parse_value(csv->column_types[i], pfield);
        // Consume empty spaces.
        pfield = parse_some(" ", pfield);
        i++;
    } while (unparsed_get_size(pfield));
    csv->n_rows++;
}


void csv_load(csv_t *csv, const char *fname) {
    file_t *file;
    parse_result_t line, header_line, header_column;

    file = file_read(fname);

    line = slice_to_parse(file_slice(file));
    header_line = line = parse_line(line);

    header_column = parse_inside(header_line);
    // Consume empty spaces.
    header_column = parse_some(" ", header_column);

    assert(csv->n_columns > 0);
    int i = 0;
    do {
        header_column = parse_split(";\r\n", header_column);
        char *column_name = parse_to_string(header_column);

        // Infer the name of the column if needed.
        if (!csv->field_names[i]) {
            csv->field_names[i] = column_name;
        } else {
            if (strcmp(column_name, csv->field_names[i]))
                printf("warning: column %d expected name '%s' but found name '%s'\n",
                       i, csv->field_names[i], column_name);

            free(column_name);
        }

        // Consume empty spaces.
        header_column = parse_some(" ", header_column);
    } while (unparsed_get_size(header_column) && ++i < csv->n_columns);

    csv->n_rows = 0;
    while (parse_get_size(line = parse_line(line)))
        csv_parse_row(csv, parse_inside(line));

    file_close(file);
}

char *type_to_string(primitive_type_t type) {
    switch (type) {
        case INTEGER:
            return "int";

        case DOUBLE:
            return "float";

        case STRING:
            return "str";

        case GENERIC:
            return "?";

        case NOTHING:
        default:
            return "_";
    }
}

void csv_print_header(csv_t *csv) {
    if (csv->n_columns == 0) {
        printf("No headers...\n");
        return;
    }

    printf("%s (%s)",
           csv->field_names[0] ? csv->field_names[0] : "[undefined]",
           type_to_string(csv->column_types[0]));

    for (int i = 0; i < csv->n_columns; i++)
        printf(" | %s (%s)",
               csv->field_names[i] ? csv->field_names[i] : "[undefined]",
               type_to_string(csv->column_types[i]));

    printf("\n");
}

value_t **csv_get_values(csv_t *csv) {
    return csv->values;
}

int csv_get_field_index(csv_t *csv, char *field_name) {
    int i;
    for (i = 0; i < csv->n_rows && strcmp(field_name, csv->field_names[i]); i++);
    if (i == csv->n_rows) return -1;
    return i;
}

uint csv_get_rows(csv_t *csv) { return csv->n_rows; }
