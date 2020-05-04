#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parsing.h"

#define FIELD_CHUNK 10

metadata *parseMetadata(FILE *fp) {
	metadata *meta = (metadata *)malloc(sizeof(metadata));
	char *label;

	// Lê o nome do arquivo.
	label = readWord(fp);
	assert_str(label, "filename", "filename not found.");
	meta->filename = readBetween(": ", LN, fp);

	meta->key = (field *)malloc(sizeof(field));

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "key-name", "key-name not found.");
	meta->key->name = readWord(fp);

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "key-type", "key-type not found.");
	meta->key->dtype = str2type(readWord(fp));

	char *size = readBetween("[", "]" LN, fp);
	if (strlen(size) > 0) meta->key->size = atoi(size);
	else meta->key->size = 1;

	int allocated = 0;
	for (meta->n_fields = 0; !feof(fp); meta->n_fields++) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (meta->n_fields >= allocated - 1) {
			// Garante que haverá espaço para o \0
			if (allocated == 0) allocated++;
			allocated += FIELD_CHUNK;
			meta->fields = (field **)realloc(meta->fields, allocated * sizeof(field *));
		}
		meta->fields[meta->n_fields] = parseField(fp);
		skip(LN, fp);
	}
	return meta;
}

field *parseField(FILE *fp) {
	field *retr = (field *)malloc(sizeof(field));
	char *label;

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "field-name", "field-name not found.");
	retr->name = readWord(fp);

	label = readBetween(LN SPACE, ":", fp);
	assert_str(label, "field-type", "field-type not found.");
	retr->dtype = str2type(readWord(fp));

	char *size = readBetween("[", "]" LN, fp);
	if (strlen(size) > 0) retr->size = atoi(size);
	else retr->size = 1;

	return retr;
}
/*
int main(int argc, char *argv[]) {
	metadata meta = *parseMetadata("meta.txt");
	printf("filename: %s\n", meta.filename);
	printf("key-name: %s\n", meta.key->name);
	printf("key-type: %s\n", meta.key->dtype == Char ? "Char" : "Other");
	printf("key-size: %d\n", meta.key->size);
	for (int i = 0; i < meta.n_fields; i++) {
		printf("field-name: %s\n", meta.fields[i]->name);
		printf("field-type: %d\n", meta.fields[i]->dtype);
		printf("field-size: %d\n", meta.fields[i]->size);
	}
	return EXIT_SUCCESS;
}
*/
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

BOOL isLine(int c) { return !(c == '\n' || c == '\r'); }
BOOL isLetter(int c) { return (c >= 65 && c <= 90) || (c >= 97 && c <= 122); }
BOOL isDigit(int c) { return c >= 48 && c <= 57; }
BOOL isWord(int c) { return isLetter(c) || isDigit(c); }
BOOL isSpace(int c) { return c == ' '; }
BOOL isPartOfNumber(int c) { return isDigit(c) || c == '.' || c == '-'; }

char *readLine(FILE *fp) {
	if (feof(fp)) return "";
	char c;
	// Clears the buffer.
	do c = getc(fp);
	while(!isLine(c) && !feof(fp));

	if (feof(fp)) return "";
	ungetc(c, fp);

	return readWhile(isLine, fp);
}
char *readWord(FILE *fp) {
	if (feof(fp)) return "";
	char c;
	do c = getc(fp);
	while(!isWord(c) && !feof(fp));

	if(feof(fp)) return "";
	ungetc(c, fp);
	
	return readWhile(isWord, fp);
}
int skip(char *ignore, FILE *fp) {
	int count = 0;
	char c;
	do {
		c = getc(fp);
		count++;
	} while(strchr(ignore, c) != NULL);
	if (c != EOF) ungetc(c, fp);
	return count;
}
char *readInt(FILE *fp) {
	if (feof(fp)) return "";
	char c;
	do c = getc(fp);
	while (!isPartOfNumber(c) && !feof(fp));

	if (feof(fp)) return "";
	ungetc(c, fp);

	return readWhile(isPartOfNumber, fp);
}
char *readBetween(char *ignore_prefix, char *stop, FILE *fp) {
	if (feof(fp)) return "";
	char c;
	BOOL ignore;
	do c = getc(fp);
	while(strchr(ignore_prefix, c) != NULL && !feof(fp));

	if (feof(fp)) return "";

	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL;
	int i = 0;
	for (i = 0; strchr(stop, c) == NULL && !feof(fp); i++, c = getc(fp)) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			// Garante que haverá espaço para o \0
			if (allocated == 0) allocated++;
			allocated += CHUNK;
			string = (char *)realloc(string, allocated);
		}
		string[i] = c; // Escreve a entrada na memória.
	}
	if (allocated == 0) return "";
	string[i] = '\0'; // Adiciona '\0' ao final.
	string = (char *)realloc(string, (i + 1) * sizeof(char));
	return string;
}
char *readWhile(BOOL (*condition)(int), FILE *fp) {
	if (feof(fp)) return "";
	char c = getc(fp);
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = 0;
	char *string = NULL;
	int i = 0;
	for (i = 0; condition(c) && !feof(fp); i++, c = getc(fp)) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			// Garante que haverá espaço para o \0
			if (allocated == 0) allocated++;
			allocated += CHUNK;
			string = (char *)realloc(string, allocated);
		}
		string[i] = c; // Escreve a entrada na memória.
	}
	if (allocated == 0) return "";
	string[i] = '\0'; // Adiciona '\0' ao final.
	string = (char *)realloc(string, (i + 1) * sizeof(char));
	if (c != EOF) ungetc(c, fp);
	return string;
}
