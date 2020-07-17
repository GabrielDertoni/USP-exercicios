#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"

char *readWord(FILE *fp) { return readSome(LETTER DIGIT, fp); }
char *readLine(FILE *fp) { return readUntil(LN, fp); }

int maybeReallocate(void **ptr, int size, int allocated) {
	if (size >= allocated) {
		allocated *= 2;
		if (allocated <= 0) allocated += CHUNK;
		*ptr = realloc(*ptr, allocated);
	}
	return allocated;
}

int ignoreUntill(char *stop, FILE *fp) {
	char c;
	int i;
	for (i = 0; !feof(fp) && strchr(stop, c); i++);
	ungetc(c, fp);
	return i;
}

int ignoreSome(char *chars, FILE *fp) {
	char c;
	int i;
	for (i = 0; !feof(fp) && !strchr(chars, c = getc(fp)); i++);
	ungetc(c, fp);
	return i;
}

char *readUntil(char *stop, FILE *fp) {
	char c;
	int i, allocated;
	char *string = NULL;
	for (i = 0, allocated = 0; !feof(fp) && !strchr(stop, c = getc(fp)); i++) {
		allocated = maybeReallocate((void **)&string, i, allocated - 1);
		string[i] = c;
	}
	if (allocated == 0) return "";
	ungetc(c, fp);
	string[i] = '\0';
	return (char *)realloc(string, (i + 1) * sizeof(char));
}

char *readSome(char *chars, FILE *fp) {
	char c;
	int i, allocated;
	char *string = NULL;
	for (i = 0, allocated = 0; !feof(fp) && strchr(chars, c = getc(fp)); i++) {
		allocated = maybeReallocate((void **)&string, i, allocated - 1);
		string[i] = c;
	}
	if (allocated == 0) return "";
	ungetc(c, fp);
	string[i] = '\0';
	return (char *)realloc(string, (i + 1) * sizeof(char));
}

void ignore(char *str) {
	if (str != NULL && strlen(str) > 0)
		free(str);
}
