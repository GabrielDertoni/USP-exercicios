#ifndef __HELPER_H__
#define __HELPER_H__

#include <stdio.h>

#define swap(a, b) ({ \
    elem_t tmp = *(a); \
    *(a) = *(b); \
    *(b) = tmp; \
})


// Para alocação de memória
#define CHUNK 16

#define lower(chr) ((chr) >= 'A' && (chr) <= 'Z' ? (chr) + 32 : (chr))

typedef char *elem_t;
typedef int (*comp_t)(elem_t, elem_t);

int reverseStrCompare(elem_t a, elem_t b);
// void swap(elem_t *a, elem_t *b);

void *maybeRealloc(void *ptr, const size_t used, size_t *alloc);
char *readline(FILE *fp);

#endif
