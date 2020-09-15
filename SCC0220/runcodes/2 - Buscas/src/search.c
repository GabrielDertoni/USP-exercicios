#include <stdio.h>
#include <stdlib.h>

int *seqSearch(int key, int *start, int *end) {
    while (start != end--)
        if (key == *end) return end;

    return NULL;
}

int *binItSearch(int key, int *start, int *end) {
    int *pivot = start + (end - start) / 2;
    for (int *i = start, *j = end; i < j; pivot = i + (j - i) / 2)
        if (key == *pivot)
            return pivot;
        else if (key > *pivot)
            i = pivot + 1;
        else
            j = pivot;

    return NULL;
}

int *binRecSearch(int key, int *start, int *end) {
    if (start >= end) return NULL;
    int *pivot = start + (end - start) / 2;
    if (key == *pivot)
        return pivot;
    else if (key > *pivot)
        return binRecSearch(key, pivot + 1, end);
    else
        return binRecSearch(key, start, pivot);
}
