#ifndef HELPERS_H
#define HELPERS_H

#define CHUNK 128

#define LN "\r\n"

int maybeReallocate(void **ptr, int size, int allocated);
int ignoreSome(char *chars, FILE *fp);
char *readUntil(char *stop, FILE *fp);
char *readLine(FILE *fp);

#endif
