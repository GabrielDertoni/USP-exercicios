#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parsing.h"
#include "database.h"

metadata parseMetadata(FILE *fp) {
	metadata meta;
	char *label;

	// Lê o nome do arquivo.
	label = readWord(fp);
	assert_str(label, "filename", "filename not found.");
	meta.filename = readBetween(": ", LN, fp);

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "key-name", "key-name not found.");
	meta.key.name = readBetween(": ", LN, fp);

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "key-type", "key-type not found.");
	meta.key.dtype = str2type(readWord(fp));

	char *size = readSomeBetween("[", DIGIT, "]" LN, fp);
	if (strlen(size) > 0) meta.key.size = atoi(size);
	else meta.key.size = 1;

	meta.fields = NULL;
	int allocated = 0;
	for (meta.n_fields = 0; !feof(fp); meta.n_fields++) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (meta.n_fields >= allocated - 1) {
			allocated *= 2;
			if (allocated == 0) allocated += FIELD_CHUNK;
			meta.fields = (field *)realloc(meta.fields, allocated * sizeof(field));
		}
		meta.fields[meta.n_fields] = parseMetaField(fp);
		ignore(readSome(LN, fp));
	}
	meta.fields = (field *)realloc(meta.fields, meta.n_fields * sizeof(field));
	return meta;
}

field parseMetaField(FILE *fp) {
	field retr;
	char *label;

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "field-name", "field-name not found.");
	retr.name = readBetween(": ", LN, fp);

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "field-type", "field-type not found.");
	char *w = readWord(fp);
	retr.dtype = str2type(w);

	char *size = readSomeBetween("[", DIGIT, "]", fp);
	if (strlen(size) > 0) retr.size = atoi(size);
	else retr.size = 1;

	return retr;
}

char *parseField(field meta_field, FILE *fp) {
	ignore(readSome(SPACE COMMA, fp));
	char *value = NULL;
	if (meta_field.dtype == Char && meta_field.size == 1)
		value = readSomeBetween(SQUO, LETTER DIGIT SPACE, SQUO, fp);
	else if (meta_field.dtype == Char)
		value = readBetween(DQUO, DQUO, fp);
	else if (meta_field.dtype == Int)
		value = readInt(fp);
	else if (meta_field.dtype == Float || meta_field.dtype == Double)
		value = readFloat(fp);

	return value;
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

type str2type(char *str) {
	if (strcmp(str, "char") == 0) return Char;
	if (strcmp(str, "int") == 0) return Int;
	if (strcmp(str, "float") == 0) return Float;
	if (strcmp(str, "double") == 0) return Double;
	return Void;
}

void assert_str(char *str1, char *str2, char *msg) {
	if (strcmp(str1, str2) != 0) {
		printf("Assertion failed with message: %s\n", msg);
		exit(EXIT_FAILURE);
	}
}

char *readLine(FILE *fp) {
	ignore(readSome(LN, fp));
	return readUntil(LN, fp);
}

char *readWord(FILE *fp) {
	ignore(readUntil(LETTER DIGIT, fp));
	return readSome(LETTER DIGIT, fp);
}

char *readInt(FILE *fp) {
	ignore(readUntil(SIGN DIGIT, fp));
	return readSome(SIGN DIGIT, fp);
}

char *readFloat(FILE *fp) {
	ignore(readUntil(SIGN DIGIT DOT, fp));
	return readSome(SIGN DIGIT DOT, fp);
}

char *readBetween(char *ignore_prefix, char *stop, FILE *fp) {
	ignore(readSome(ignore_prefix, fp));
	char *retr = readUntil(stop, fp);
	getc(fp); // Pula a caractere que ditou a parada do readUntil()
	return retr;
}

char *readSomeBetween(char *prefix, char *some, char *postfix, FILE *fp) {
	char *pre = readOnce(prefix, fp);
	if (strlen(pre) == 0) return "";
	ignore(pre);
	if (feof(fp)) return "";
	char *retr = readSome(some, fp);
	char *post = readOnce(postfix, fp);
	if (strlen(post) == 0) {
		unread(retr, fp);
		ignore(retr);
		return "";
	}
	return retr;
}

char *readUntil(char *stop, FILE *fp) {
	if (feof(fp)) return "";
	char c = getc(fp);

	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL;
	int i = 0;
	for (i = 0; strchr(stop, c) == NULL && !feof(fp); i++, c = getc(fp)) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			// Garante que haverá espaço para o \0
			allocated *= 2;
			if (allocated == 0) allocated += CHUNK;
			string = (char *)realloc(string, allocated);
		}
		string[i] = c; // Escreve a entrada na memória.
	}
	if (c != EOF) ungetc(c, fp);
	if (allocated == 0) return "";
	string[i] = '\0'; // Adiciona '\0' ao final.
	string = (char *)realloc(string, (i + 1) * sizeof(char));
	return string;
}

char *readSome(char *chars, FILE *fp) {
	if (feof(fp)) return "";
	char c = getc(fp);
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL;
	int i = 0;
	for (i = 0; strchr(chars, c) != NULL && !feof(fp); i++, c = getc(fp)) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			// Garante que haverá espaço para o \0
			allocated *= 2;
			if (allocated == 0) allocated += CHUNK;
			string = (char *)realloc(string, allocated);
		}
		string[i] = c; // Escreve a entrada na memória.
	}
	if (c != EOF) ungetc(c, fp);
	if (allocated == 0) return "";
	string[i] = '\0'; // Adiciona '\0' ao final.
	string = (char *)realloc(string, (i + 1) * sizeof(char));
	return string;
}

char *readOnce(char *chars, FILE *fp) {
	if (feof(fp)) return "";
	char c = getc(fp);
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = malloc((strlen(chars) + 1) * sizeof(char));
	int i = 0;
	for (i = 0; chars[i] != '\0' && c == chars[i] && !feof(fp); i++) {
		string[i] = c; // Escreve a entrada na memória.
		c = getc(fp);
	}
	// Se nem todas as caracteres de char *chars forem lidas, devolve todas
	// as caracteres lidas para a fila de leitura e retorna uma string vazia.
	if (strlen(chars) > i) {
		for (--i; i >= 0; i--) ungetc(string[i], fp);
		free(string);
		return "";
	}
	string[i] = '\0'; // Adiciona '\0' ao final.
	if (c != EOF) ungetc(c, fp);
	return string;
}

void ignore(char *str) {
	if (str != NULL && strlen(str) > 0)
		free(str);
}

void unread (char *str, FILE *fp) {
	for (int i = strlen(str) - 1; i >= 0; i--)
		ungetc(str[i], fp);
}
