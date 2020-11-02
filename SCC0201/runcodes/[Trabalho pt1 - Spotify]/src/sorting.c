#include <stdio.h>
#include <sorting.h>

void swap(elem_t *a, elem_t *b) {
    elem_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void quick_sort_with(elem_t *start, elem_t *end, comp_t comp) {
    if (start >= end - 1) return;
    elem_t *p1 = start + 1, *p2 = end - 1, *pivot = start;

    while (p1 < p2)
        if (comp(*p1, *pivot) >= 0 && comp(*p2, *pivot) < 0)
            swap(p1++, p2--);
        else if (comp(*p1, *pivot) < 0) p1++;
        else if (comp(*p2, *pivot) >= 0) p2--;

    if (comp(*p2, *pivot) < 0) swap(p2, pivot);
    else swap(--p2, pivot);

    quick_sort_with(start, p2, comp);
    quick_sort_with(p2 + 1, end, comp);
}
