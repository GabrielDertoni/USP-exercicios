#include <stdlib.h>
#include <string.h>
#include <helpers.h>
#include <merge.h>

void merge(elem_t *start, elem_t *mid, elem_t *end) {
    elem_t *auxorig = (elem_t *)malloc((end - start) * sizeof(elem_t));
    elem_t *startPtr = start, *midPtr = mid, *aux = auxorig;

    while (startPtr < mid && midPtr < end)
        if (*startPtr < *midPtr)
            *(aux++) = *(startPtr++);
        else
            *(aux++) = *(midPtr++);

    if (startPtr < mid) 
        memcpy(aux, startPtr, (mid - startPtr) * sizeof(elem_t));

    memcpy(start, auxorig, (midPtr - start) * sizeof(elem_t));
    free(auxorig);
}

void mergeSort(elem_t *start, elem_t *end) {
    if (start >= end - 1) return;
    elem_t *mid = start + (end - start) / 2;
    mergeSort(start, mid);
    mergeSort(mid, end);
    merge(start, mid, end);
}

void mergeWith(elem_t *start, elem_t *mid, elem_t *end, comp_t comp) {
    elem_t *auxorig = (elem_t *)malloc((end - start) * sizeof(elem_t));
    elem_t *startPtr = start, *midPtr = mid, *aux = auxorig;

    while (startPtr < mid && midPtr < end)
        if (comp(*startPtr, *midPtr) < 0)
            *(aux++) = *(startPtr++);
        else
            *(aux++) = *(midPtr++);

    if (startPtr < mid) 
        memcpy(aux, startPtr, (mid - startPtr) * sizeof(elem_t));

    memcpy(start, auxorig, (midPtr - start) * sizeof(elem_t));
    free(auxorig);
}

void mergeSortWith(elem_t *start, elem_t *end, comp_t comp) {
    if (start >= end - 1) return;
    elem_t *mid = start + (end - start) / 2;
    mergeSortWith(start, mid, comp);
    mergeSortWith(mid, end, comp);
    mergeWith(start, mid, end, comp);
}
