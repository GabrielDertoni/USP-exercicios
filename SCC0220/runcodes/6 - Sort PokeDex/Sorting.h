#ifndef __SORTING_H__
#define __SORTING_H__

#include <stdlib.h>

// Ponteiro de função que comapra dois elementos de um vetor. Deve retornar > 0
// se o primeiro for maior que o segundo, < 0 se o segundo for maior e = 0 se os
// dois forem iguais.
typedef int (*comp_t)(void *, void *);

/**
 * Funções de ordenação:
 *
 * Nomenclatura: <algoritmo>_sort_with
 * Utiliza <algoritmo> sort como estratégia para ordenar algum vetor de elementos
 * arbitrários dado uma função de comparação.
 *
 * Parâmetros:
 * vec - o vetor a ser ordenado. [mut ref]
 * nmemb - o número de elementos no vetor.
 * elsize - o tamanho de cada elemento (em bytes).
 * comp - a função de comparação de dois ponteiros de elementos.
 */

void quick_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp);

void heap_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp);

void merge_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp);

void tim_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp);

#endif
