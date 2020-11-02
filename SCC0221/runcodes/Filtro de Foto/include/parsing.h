#ifndef _PARSING_
#define _PARSING_

// Macros para quantidade de alocação.
#define CHUNK 32

char *readLine(FILE *fp);
char *readUntil(char *stop, FILE *fp);
int maybeReallocate(void **ptr, int size, int allocated);

#endif
