#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <stdio.h>

// Macro para alocação de memória
#define CHUNK 32

// Tipos que podem ser modificados para reutilização.
typedef void *elem_t;
typedef int (*comp_t)(elem_t, elem_t);

// Garante que ptr terá um espaço a mais alocado que used
void *maybeRealloc(void *ptr, const size_t used, size_t *alloc);
// Lê exatamente uma linha do arquivo.
char *readline(FILE *fp);

#endif
