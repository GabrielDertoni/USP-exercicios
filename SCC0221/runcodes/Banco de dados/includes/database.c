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
		if (i == 0) meta_field = meta.key;
		else meta_field = meta.fields[i - 1];

		n_bytes += meta_field.size * sizeofType(meta_field.dtype);
	}
	return n_bytes;
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
		if (i == 0) meta_field = db.meta.key;
		else meta_field = db.meta.fields[i - 1];

		fread(result + offset, sizeofType(meta_field.dtype) * meta_field.size, 1, db.fp);
		offset += sizeofType(meta_field.dtype) * meta_field.size;
	}
	return result;
}

void insert(database_t *db, char **data) {
	// Itera por todos os campos. Desde a chave promária até o último campo.
	for (int i = 0; i < db->meta.n_fields + 1; i++) {
		field meta_field; // Informações sobre o campo sendo considerado.
		if (i == 0) meta_field = db->meta.key;
		else meta_field = db->meta.fields[i - 1];
		// Escreve os dados inseridos no arquivo de registro.
		writeField(data[i], meta_field.dtype, meta_field.size, db->fp);
	}
	// Aumenta o tamanho do banco de dados de acordo com o número de bytes adicionados.
	db->size++;
}

// Recupera o nome do arquivo de índice a partir de metadados (troca a extenção).
// Ex.: registro.reg -> registro.idx
char *index_name(metadata meta) {
	char *filename = strdup(meta.filename);
	filename = strsep(&filename, ".");
	strcat(filename, ".idx");
	return filename;
}

int (*compareTypeKeys(field key_field))(void *, void *) {
	switch (key_field.dtype) {
		case Char:
			if (key_field.size == 1) return compareCharKeys;
			else return compareStringKeys;
		case Int:
			return compareIntKeys;
		case Float:
			return compareFloatKeys;
		case Double:
			return compareDoubleKeys;
		default:
			return compareIntKeys;
	}
}

// Gera um arquivo de índice.
entry_t **create_index(database_t db) {
	// Cria um índice fora de ordem a partir da leitura dos registros.
	entry_t **idx = reg2index(db);
	sortWith((void **)idx, 0, db.size - 1, compareTypeKeys(db.meta.key));

	char *filename = index_name(db.meta);
	FILE *fp = fopen(filename, "w");
	for (int i = 0; i < db.size; i++) {
		fwrite(idx[i]->key, sizeofType(db.meta.key.dtype), db.meta.key.size, fp);
		fwrite(&idx[i]->offset, sizeof(long long), 1, fp);
	}
	fclose(fp);
	return idx;
}

BOOL index_exists(metadata meta) {
	FILE *fp;
	if ((fp = fopen(index_name(meta), "r"))) {
		fclose(fp);
		return TRUE;
	}
	return FALSE;
}

long long load_index(entry_t ***ptr, metadata meta) {
	FILE *fp = fopen(index_name(meta), "r"); // Abre o arquivo de índice.
	if (fp == NULL) return FILE_NOT_FOUND;
	entry_t **result = NULL; // Inicializa a variável de resultado.
	long long allocated = 0; // Armazena memória alocada em entry_t **result.
	long long i = 0; // Conta o número de leituras feitas (linhas do banco de dados).
	do {
		// Lê a chave primária.
		void *key = malloc(sizeofType(meta.key.dtype) * meta.key.size);
		int n_read = fread(key, sizeofType(meta.key.dtype) * meta.key.size, 1, fp);
		// Se nada tiver sido lido, ou menos que o necessário, termine a leitura.
		if (n_read < sizeofType(meta.key.dtype)){
			free(key);
			break;
		}

		long long offset;
		n_read = fread(&offset, sizeof(long long), 1, fp);
		if (n_read < sizeofType(meta.key.dtype)) {
			break;
		}

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

entry_t **reg2index(database_t db) {
	// Move o cursor para o início do arquivo antes de começar a leitura.
	entry_t **result = malloc(db.size * sizeofRow(db.meta));
	for (int i = 0; i < db.size && !feof(db.fp); i++) {
		long long offset = (long long)i * sizeofRow(db.meta);
		fseek(db.fp, offset, SEEK_SET);
		void *key = malloc(sizeofType(db.meta.key.dtype) * db.meta.key.size);
		int n_read = fread(key, sizeofType(db.meta.key.dtype) * db.meta.key.size, 1, db.fp);
		if (n_read == 0) {
			free(key);
			break;
		}

		result[i] = (entry_t *)malloc(sizeof(entry_t));
		result[i]->key = key;
		result[i]->offset = offset;
	}
	return result;
}

database_t open_databse(metadata meta) {
	FILE *fp = fopen(meta.filename, "r");
	long long size;
	if (fp == NULL) {
		fp = fopen(meta.filename, "a+");
		size = 0;
	} else {
		fseek(fp, 0L, SEEK_END);
		long flength = ftell(fp);
		size = flength / sizeofRow(meta);
		fclose(fp);
	}
	fp = fopen(meta.filename, "a+");
	database_t db = {
		.meta = meta,
		.fp = fp,
		.size = size
	};

	return db;
}

void close_database(database_t *db) { fclose(db->fp); }

int compareTypes(void *a, void *b, type dtype, int size) {
	switch(dtype) {
		case Char:
			if (size > 1 || size < 0) {
				for (int i = 0; (i < size || size < 0) && *(char *)a != '\0' && *(char *)b != '\0'; i++)
					if (*(char *)a > *(char *)b) return 1;
					else if (*(char *)a < *(char *)b) return -1;
					else a++, b++;

				if (*(char *)a == '\0' && *(char *)b == '\0') return 0;
				else if (*(char *)a == '\0') return -1;
				else return 1;
			} else
				if (*(char *)a > *(char *)b) return 1;
				else if (*(char *)a < *(char *)b) return -1;
				else return 0;

		case Int:
			if (*(int *)a > *(int *)b) return 1;
			else if (*(int *)a < *(int *)b) return -1;
			else return 0;

		case Float:
			if (*(float *)a > *(float *)b) return 1;
			else if (*(float *)a < *(float *)b) return -1;
			else return 0;

		case Double:
			if (*(double *)a > *(double *)b) return 1;
			else if (*(double *)a < *(double *)b) return -1;
			else return 0;

		default:
			return -2;
	}
}

// TODO: Encontrar um jeito melhor de fazer essas funções.

int compareCharKeys(void *a, void *b) {
	entry_t *enta = (entry_t *)a;
	entry_t *entb = (entry_t *)b;
	return compareTypes(enta->key, entb->key, Char, 1);
}

int compareStringKeys(void *a, void *b) {
	entry_t *enta = (entry_t *)a;
	entry_t *entb = (entry_t *)b;
	return compareTypes(enta->key, entb->key, Char, -1);
}

int compareIntKeys(void *a, void *b) {
	entry_t *enta = (entry_t *)a;
	entry_t *entb = (entry_t *)b;
	return compareTypes(enta->key, entb->key, Int, 1);
}

int compareFloatKeys(void *a, void *b) {
	entry_t *enta = (entry_t *)a;
	entry_t *entb = (entry_t *)b;
	return compareTypes(enta->key, entb->key, Float, 1);
}

int compareDoubleKeys(void *a, void *b) {
	entry_t *enta = (entry_t *)a;
	entry_t *entb = (entry_t *)b;
	return compareTypes(enta->key, entb->key, Double, 1);
}
