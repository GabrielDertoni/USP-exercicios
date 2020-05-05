#ifndef _DB_UTILS_
#define _DB_UTILS_

// Macros para tipo booleano.
#define BOOL short int
#define TRUE 1
#define FALSE 0


// Ordena uma parte de uma lista de ponteiros void no intervalo de índices 
// (start, end]. (Implementação de Quick Sort).
void sortWith(void **list, int start, int end, int (*compare)(void *a, void *b));

// Performa uma busca binária numa lista de ponteiros void no intervalo de
// índice [start, end]. A busca é feita até que a função int compare (void *a, void *b) retorne 0,
// para tal, a cada iteração da busca binária, essa função é chamada com o primeiro
// argumento sendo o elemento da lista e o segundo o elemento que se procura (void *key).
void *binarySearch(void **list, int start, int end, void *key, int (*compare)(void *a, void *b));

#endif
