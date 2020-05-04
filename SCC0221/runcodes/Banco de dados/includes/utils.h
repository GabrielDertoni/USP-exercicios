#ifndef _DB_UTILS_
#define _DB_UTILS_

// Macros para tipo booleano.
#define BOOL short int
#define TRUE 1
#define FALSE 0

// Macros para função readLine.
#define CHUNK 128

// Macros para parsing.
#define LN "\r\n"
#define SPACE " "

void sortWith(void **list, int start, int end, int (*compare)(void *a, void *b));

#endif
