#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parsing.h"
#include "database.h"

#define INDEX_CHUNK 16

int sizeofType(type dtype) {
	if (dtype == Void) return sizeof(void *);
	if (dtype == Char) return sizeof(char);
	if (dtype == Int) return sizeof(int);
	if (dtype == Float) return sizeof(float);
	if (dtype == Double) return sizeof(double);
	return 0;
}

long long sizeofRow(metadata meta) {
	int n_bytes = 0;
	for (int i = 0; i < meta.n_fields + 1; i++) {
		field meta_field;
		if (i == 0) meta_field = *meta.key;
		else meta_field = *meta.fields[i - 1];

		n_bytes += meta_field.size * sizeofType(meta_field.dtype);
	}
	return n_bytes;
}

void setField(void *ptr, char *data, type dtype, int size) {
	if (dtype == Char) {
		for (int i = 0; i < size && data[i] != '\0'; i++)
			((char *)ptr)[i] = data[i];

	} else if (dtype == Int) {
		*((int *)ptr) = atoi(data);
	} else if (dtype == Float) {
		*((float *)ptr) = (float)atof(data);
	} else if (dtype == Double) {
		*((double *)ptr) = atof(data);
	}
}

void *strtoa(char *data, type dtype, int size) {
	void *ptr = malloc(sizeofType(dtype) * size);
	if (dtype == Char) {
		memset(ptr, '\0', sizeofType(dtype) * size);
		for (int i = 0; i < size && data[i] != '\0'; i++)
			((char *)ptr)[i] = data[i];

	} else if (dtype == Int) {
		*((int *)ptr) = atoi(data);
	} else if (dtype == Float) {
		*((float *)ptr) = (float)atof(data);
	} else if (dtype == Double) {
		*((double *)ptr) = atof(data);
	}
	return ptr;
}

void writeField(char *data, type dtype, int size, FILE *fp) {
	void *ptr = strtoa(data, dtype, size);
	fwrite(ptr, sizeofType(dtype), size, fp);
	free(ptr);
}

void *readRow(long foffset, database_t db) {
	void *result = malloc(sizeofRow(db.meta));
	fseek(db.fp, foffset, SEEK_SET);
	int offset = 0;
	for (int i = 0; i < db.meta.n_fields + 1; i++) {
		field meta_field;
		if (i == 0) meta_field = *db.meta.key;
		else meta_field = *db.meta.fields[i - 1];
		fread(result + offset, sizeofType(meta_field.dtype) * meta_field.size, 1, db.fp);
		offset = sizeofType(meta_field.dtype) * meta_field.size;
	}
	return result;
}

void insert(database_t *db, char **data) {
	//int needed = sizeofRow(db->meta);
	entry_t *entry = (entry_t *)malloc(sizeof(entry_t));
	//printf("Needed %d bytes of memory, allocated %d bytes.\n", needed, (int)db->allocated);
	for (int i = 0; i < db->meta.n_fields + 1; i++) {
		field meta_field;
		if (i == 0) {
			meta_field = *db->meta.key;
			entry->key = malloc(sizeofType(meta_field.dtype) * meta_field.size);
			setField(entry->key, data[i], meta_field.dtype, meta_field.size);
			entry->offset = ftell(db->fp);
		} else {
			meta_field = *db->meta.fields[i - 1];
		}
		//printf("Writing field %s with type %d and size %d\n", meta_field->name, meta_field->dtype, meta_field->size);
		writeField(data[i], meta_field.dtype, meta_field.size, db->fp);
	}
	while (db->allocated - db->size <= 0) {
		db->allocated *= 2;
		if (db->allocated == 0) db->allocated++;
	}
	db->index = (entry_t **)realloc(db->index, db->allocated * sizeof(entry_t *));
	db->index[db->size++] = entry;
}

char *index_name(metadata meta) {
	char *filename = strdup(meta.filename);
	filename = strsep(&filename, ".");
	strcat(filename, ".idx");
	return filename;
}

void create_index(database_t db) {
	sortWith((void **)db.index, 0, db.size - 1, compareIntKeys);
	field meta_key = *db.meta.key;

	char *filename = index_name(db.meta);
	FILE *fp = fopen(filename, "w");
	for (int i = 0; i < db.size; i++) {
		fwrite(db.index[i]->key, sizeofType(meta_key.dtype), meta_key.size, fp);
		fwrite(&db.index[i]->offset, sizeof(long long), 1, fp);
	}
	fclose(fp);
}

long long load_index(entry_t ***ptr, metadata meta) {
	entry_t **result = NULL;
	FILE *fp = fopen(index_name(meta), "r");
	long long allocated = 0;
	long long i = 0;
	do {
		void *key = malloc(sizeofType(meta.key->dtype) * meta.key->size);
		int n_read = fread(key, sizeofType(meta.key->dtype) * meta.key->size, 1, fp);
		if (n_read == 0) break;

		long long offset;
		n_read = fread(&offset, sizeof(long long), 1, fp);
		if (n_read == 0) break;

		if (i >= allocated - 1) {
			allocated *= 2;
			if (allocated == 0) allocated++;
			result = (entry_t **)realloc(result, allocated * sizeof(entry_t *));
		}

		result[i] = (entry_t *)malloc(sizeof(entry_t));
		result[i]->key = key;
		result[i]->offset = offset;
		i++;
	} while(!feof(fp));
	if (i > 0) result = (entry_t **)realloc(result, i * sizeof(entry_t *));

	fclose(fp);
	*ptr = result;
	return i;
}

entry_t **reg2index(metadata meta) {
	FILE *fp = fopen(meta.filename, "r");
	entry_t **result = NULL;
	long long allocated = 0;
	long long i = 0;
	do {
		void *key = malloc(sizeofType(meta.key->dtype) * meta.key->size);
		int n_read = fread(key, sizeofType(meta.key->dtype) * meta.key->size, 1, fp);
		if (n_read == 0) break;

		long long offset = ftell(fp);
		if (i >= allocated - 1) {
			allocated *= 2;
			if (allocated == 0) allocated++;
			result = (entry_t **)realloc(result, allocated * sizeof(entry_t *));
		}

		result[i] = (entry_t *)malloc(sizeof(entry_t));
		result[i]->key = key;
		result[i]->offset = offset;
		i++;
	} while(!feof(fp));
	if (i > 0) result = (entry_t **)realloc(result, i * sizeof(entry_t *));
	fclose(fp);
	return result;
}

database_t open_databse(metadata meta) {
	FILE *fp = fopen(meta.filename, "r");
	if (fp == NULL) {
		//printf("Register file \"%s\" not found... Maybe database wasn't created.\n", meta.filename);
		fp = fopen(meta.filename, "a+");
		database_t db = {
			.meta = meta,
			.fp = fp,
			.size = 0,
			.allocated = 0,
			.index = NULL
		};
		return db;
	}
	fseek(fp, 0L, SEEK_END);
	long flength = ftell(fp);
	//printf("File length is %ld\n", flength);
	long long size = flength / sizeofRow(meta);
	//printf("Size is %lld\n", size);
	fclose(fp);

	entry_t **idx;
	long long n_reads = load_index(&idx, meta);
	//printf("Read from index %lld objects\n", n_reads);

	database_t db = {
		.meta = meta,
		.fp = fp,
		.size = size,
	};
	// Se o índice estiver desatualizado com os registros, reescreve o índice a partir dos registros
	// e substitui o índice desatualizado.
	if (n_reads != size) {
		//printf("Index file had different size then register file.\n");
		if (idx != NULL) {
			for (int i = 0; i < n_reads; i++)
				free(idx[i]);
			free(idx);
		}

		idx = reg2index(meta);
		// Já que o índice foi construído a partir do arquivo de registro, eles possuirão o mesmo tamanho.
		n_reads = size;
	}
	db.index = idx;
	db.allocated = n_reads;
	fp = fopen(meta.filename, "a+");

	return db;
}

void close_database(database_t *db) {
	for (int i = 0; i < db->size; i++) {
		free(db->index[i]);
	}
	free(db->index);
	db->allocated = 0;
	fclose(db->fp);
}

int compareTypes(void *a, void *b, type dtype, int size) {
	if (dtype == Char) {
		for (int i = 0; i < size && *(char *)a != '\0' && *(char *)b != '\0'; i++)
			if (*(char *)a > *(char *)b) return 1;
			else if (*(char *)a < *(char *)b) return -1;
			else continue;

		if (*(char *)a == '\0' && *(char *)b == '\0') return 0;
		else if (*(char *)a == '\0') return -1;
		else return 1;
	} else if (dtype == Int) {
		if (*(int *)a > *(int *)b) return 1;
		else if (*(int *)a < *(int *)b) return -1;
		else return 0;
	} else if (dtype == Float) {
		if (*(float *)a > *(float *)b) return 1;
		else if (*(float *)a < *(float *)b) return -1;
		else return 0;
	} else if (dtype == Double) {
		if (*(double *)a > *(double *)b) return 1;
		else if (*(double *)a < *(double *)b) return -1;
		else return 0;
	}
	return -2;
}

int compareIntKeys(void *a, void *b) {
	entry_t *enta = (entry_t *)a;
	entry_t *entb = (entry_t *)b;
	return compareTypes(enta->key, entb->key, Int, 1);
}

