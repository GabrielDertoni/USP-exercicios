#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parsing.h"
#include "database.h"


// Macros de erro
#define CHR_DIFF -100

enum StreamType { File, String };

typedef struct Stream {
	void *source;
	enum StreamType type;
} stream_t;

typedef struct String {
	char *start;
	char *ptr;
} string_t;

BOOL stend(stream_t input) {
	if (input.type == File) return feof((FILE *)input.source);
	else if (input.type == String){
		string_t *string = (string_t *)input.source;
		return *string->ptr == '\0';
	}
	return TRUE;
}

stream_t fromStdin(void) {
	stream_t retr = {
		.source = (void *)stdin,
		.type = File
	};
	return retr;
}

stream_t fromFile(FILE *fp) {
	stream_t retr = {
		.source = (void *)fp,
		.type = File
	};
	return retr;
}

stream_t fromString(char *str) {
	string_t *string = (string_t *)malloc(sizeof(string_t));
	string->start = str;
	string->ptr = str;
	stream_t retr = {
		.source = (void *)string,
		.type = String
	};
	return retr;
}

int stungetc(stream_t input, int c) {
	if (input.type == File) return ungetc(c, (FILE *)input.source);
	else if (input.type == String){
		string_t *string = (string_t *)input.source;
		if (string->ptr == string->start) return EOF;
		if (*(string->ptr - 1) != c) return CHR_DIFF;
		return *(--string->ptr);
	}
	return EOF;
}

int stgetc(stream_t input) {
	if (input.type == File) return getc((FILE *)input.source);
	else if (input.type == String) return *(((string_t *)input.source)->ptr++);
	return EOF;
}
