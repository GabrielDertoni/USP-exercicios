#include <stdlib.h>
#include <string.h>
#include <helpers.h>
#include <merge3.h>

void merge3With(elem_t *start, elem_t *mid1, elem_t *mid2, elem_t *end, comp_t comp) {
    elem_t *auxorig = (elem_t *)malloc((end - start) * sizeof(elem_t));
    elem_t *startPtr = start, *mid1Ptr = mid1, *mid2Ptr = mid2, *aux = auxorig;

    // Toma conta de juntar as partições, mesmo se startPtr == mid1
    while (mid1Ptr < mid2 && mid2Ptr < end)
        if (startPtr < mid1 && comp(*startPtr, *mid1Ptr) < 0)
            if (comp(*startPtr, *mid2Ptr) < 0)
                *(aux++) = *(startPtr++);
            else
                *(aux++) = *(mid2Ptr++);
        else
            if (comp(*mid1Ptr, *mid2Ptr) < 0)
                *(aux++) = *(mid1Ptr++);
            else
                *(aux++) = *(mid2Ptr++);
    
    // Junta as partições restantes caso mid2Ptr == end
    while (mid1Ptr < mid2 && startPtr < mid1)
        if (comp(*startPtr, *mid1Ptr) < 0)
            *(aux++) = *(startPtr++);
        else
            *(aux++) = *(mid1Ptr++);

    // Junta as partições restantes caso mid1Ptr == mid2
    while (mid2Ptr < end && startPtr < mid1)
        if (comp(*startPtr, *mid2Ptr) < 0)
            *(aux++) = *(startPtr++);
        else
            *(aux++) = *(mid2Ptr++);
    
    while (startPtr < mid1) *(aux++) = *(startPtr++);
    while (mid1Ptr  < mid2) *(aux++) = *(mid1Ptr++);
    while (mid2Ptr  < end ) *(aux++) = *(mid2Ptr++);

    memcpy(start, auxorig, (end - start) * sizeof(elem_t));
    free(auxorig);
}