#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <helpers.h>

int maybeReallocate(void **ptr, int size, int allocated) {
	if (size >= allocated) {
		allocated *= 2;
		if (allocated <= 0) allocated += CHUNK;
		*ptr = realloc(*ptr, allocated);
	}
	return allocated;
}

int ignoreSome(char *chars, FILE *fp) {
	char c;
	int i;
	for (i = 0; strchr(chars, c = getc(fp)) && !feof(fp); i++);
	ungetc(c, fp);
	return i;
}

char *readUntil(char *stop, FILE *fp) {
	char c;
	int i, allocated;
	char *string = NULL;
	for (i = 0, allocated = 0; !strchr(stop, c = getc(fp)) && !feof(fp); i++) {
		allocated = maybeReallocate((void **)&string, i, allocated - 1);
		string[i] = c;
	}
	if (c != EOF) ungetc(c, fp);
	if (allocated == 0) return NULL;
	string[i] = '\0';
	return (char *)realloc(string, (i + 1) * sizeof(char));
}

char *readLine(FILE *fp) {
	ignoreSome(LN, fp);
  return readUntil(LN, fp);
}
