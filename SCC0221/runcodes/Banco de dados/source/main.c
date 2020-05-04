#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/utils.h"
#include "../includes/parsing.h"
#include "../includes/database.h"

#define COMMA ","
#define SQUO "'"
#define DQUO "\""

/**
 * TODO: metadata.key doesn't need to be a pointer, change so it isn't.
 */

void *binarySearch(void **list, int start, int end, void *key, int (*compare)(void *a, void *b)) {
	if (start == end) return NULL;
	// range [start, end)
	int middle = (start + end) / 2;
	if (compare(list[middle], key) == 0)
		return list[middle];
	else if (compare(list[middle], key) == 1)
		return binarySearch(list, start, middle, key, compare);
	else
		return binarySearch(list, middle + 1, end, key, compare);
}

int compareKeyWithInt(void *a, void *b) {
	int key = *(int *)((entry_t *)a)->key;
	int comp = *(int *)b;
	if (key > comp) return 1;
	if (key < comp) return -1;
	return 0;
}

void *search(database_t db, void *key) {
	void *el = binarySearch((void **)db.index, 0, db.size, key, compareKeyWithInt);
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
		if (i == 0) meta_field = *meta.key;
		else meta_field = *meta.fields[i - 1];

		printf("%s: ", meta_field.name);
		print_field(row + offset, meta_field.dtype, meta_field.size);
		printf("\n");
		offset += sizeofType(meta_field.dtype) * meta_field.size;
	}
}

int main(int argc, char *argv[]) {
	char *filename = readLine(stdin);
	FILE *fp = fopen(filename, "r");
	metadata meta = *parseMetadata(fp);
	fclose(fp);

	database_t db = open_databse(meta);

	BOOL exit = FALSE;
	while(!exit) {
		char *command = readWord(stdin);
		if (strcmp(command, "insert") == 0) {
			char **fields = malloc((meta.n_fields + 1) * sizeof (char *));
			for (int i = 0; i < meta.n_fields + 1; i++) {
				field meta_field;
				if (i == 0) meta_field = *meta.key;
				else meta_field = *meta.fields[i - 1];

				char *value;
				if (meta_field.dtype == Char && meta_field.size == 1)
					value = readBetween(SPACE SQUO COMMA, SQUO COMMA LN, stdin);
				else if (meta_field.dtype == Char)
					value = readBetween(SPACE DQUO COMMA, SQUO COMMA LN, stdin);
				else
					value = readBetween(SPACE COMMA, COMMA LN, stdin);

				printf("Just read field %s with value: %s\n", meta_field.name, value);

				fields[i] = value;
			}
			insert(&db, fields);
		} else if (strcmp(command, "search") == 0) {
			char *key = readBetween(SPACE, LN, stdin);
			printf("Searching with key %s\n", key);
			void *result = search(db, strtoa(key, meta.key->dtype, meta.key->size));
			//int k = 3;
			//void *result = search(db, (void *)&k);
			if (result != NULL)
				print_row(meta, result);
			else
				printf("Not found...\n");

		} else if (strcmp(command, "index") == 0) {
			create_index(db);
		} else if (strcmp(command, "exit") == 0) {
			create_index(db);
			break;
		} else {
			printf("Command not found...\n");
		}
	}

	close_database(&db);

	return EXIT_SUCCESS;
}
