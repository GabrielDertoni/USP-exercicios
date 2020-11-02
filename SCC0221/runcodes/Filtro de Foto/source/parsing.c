#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parsing.h"

char *readLine(FILE *fp) { return readUntil("\r\n", fp); }

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

int maybeReallocate(void **ptr, int size, int allocated) {
	if (size >= allocated) {
		allocated *= 2;
		if (allocated <= 0) allocated += CHUNK;
		*ptr = realloc(*ptr, allocated);
	}
	return allocated;
}

