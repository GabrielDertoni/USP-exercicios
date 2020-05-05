#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/utils.h"
#include "../includes/parsing.h"
#include "../includes/database.h"

/**
 * TODO: Add a way to sort with different types of primary keys than Int.
 */

int compareKeyWithInt(void *a, void *b) {
	int key = *(int *)((entry_t *)a)->key;
	int comp = *(int *)b;
	if (key > comp) return 1;
	if (key < comp) return -1;
	return 0;
}

void *search(database_t db, void *key) {
	entry_t **idx;
	if (!index_exists(db.meta) || load_index(&idx, db.meta) != db.size)
		idx = create_index(db);

	void *el = binarySearch((void **)idx, 0, db.size, key, compareKeyWithInt);
	if (el == NULL) return NULL;

	return readRow(((entry_t *)el)->offset, db);
}

void print_field(void *data, type dtype, int size) {
	if (dtype == Char && size == 1)
		printf("%c", *(char *)data);
	else if (dtype == Char)
		printf("%s", (char *)data);
	else if (dtype == Int)
		printf("%d", *(int *)data);
	else if (dtype == Float)
		printf("%f", *(float *)data);
	else if (dtype == Double)
		printf("%lf", *(double *)data);
	else
		printf("Type not recognized...\n");
}

void print_row(metadata meta, void *row) {
	int offset = 0;
	for (int i = 0; i < meta.n_fields + 1; i++) {
		field meta_field;
		if (i == 0) meta_field = meta.key;
		else meta_field = meta.fields[i - 1];

		printf("%s: ", meta_field.name);
		print_field(row + offset, meta_field.dtype, meta_field.size);
		printf("\n");
		offset += sizeofType(meta_field.dtype) * meta_field.size;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	char *filename = readLine(stdin);
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Meta file does not exist.\n");
		exit(EXIT_FAILURE);
	}
	metadata meta = parseMetadata(fp);
	fclose(fp);

	database_t db = open_databse(meta);

	BOOL exit = FALSE;
	while(!exit) {
		char *command = readWord(stdin);

		if (strcmp(command, "insert") == 0) {
			char **fields = malloc((meta.n_fields + 1) * sizeof (char *));
			for (int i = 0; i < meta.n_fields + 1; i++) {
				field meta_field;
				if (i == 0) meta_field = meta.key;
				else meta_field = meta.fields[i - 1];

				fields[i] = parseField(meta_field, stdin);
			}
			insert(&db, fields);

		} else if (strcmp(command, "search") == 0) {
			char *key = parseField(meta.key, stdin);
			void *result = search(db, strtoa(key, meta.key.dtype, meta.key.size));
			if (result != NULL) print_row(meta, result);

		} else if (strcmp(command, "index") == 0)
			create_index(db);

		else if (strcmp(command, "exit") == 0)
			break;

		else 
			printf("Command not found...\n");
	}

	close_database(&db);

	return EXIT_SUCCESS;
}
