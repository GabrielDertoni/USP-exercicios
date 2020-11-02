#ifndef __SORTING_H__
#define __SORTING_H__

#include <csv.h>

typedef void *elem_t;
typedef int (*comp_t)(elem_t, elem_t);

void quick_sort_with(elem_t *start, elem_t *end, comp_t comp);

#endif
