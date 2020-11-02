#ifndef __SORT_MERGE_H__
#define __SORT_MERGE_H__

#include <helpers.h>

void merge(elem_t *start, elem_t *mid, elem_t *end);
void mergeSort(elem_t *start, elem_t *end);
void mergeWith(elem_t *start, elem_t *mid, elem_t *end, comp_t comp);
void mergeSortWith(elem_t *start, elem_t *end, comp_t comp);

#endif
