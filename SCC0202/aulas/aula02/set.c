#include <stdio.h>
#include <stdlib.h>
#include "set.h"

#define CHUNK 32

void maybe_reallocate(set_t *s, int i) {
    if (i >= s->allocated) {
        s->allocated *= 2;
        if (s->allocated == 0) s->allocated = CHUNK;
        s->vec = realloc((void *)s->vec, s->allocated * sizeof(int));
    }
}

int *binary_search(int val, int *start, int *end) {
    if (start == end) return NULL;
    int *middle = start + (start - end) / 2;
    if (*middle == val) return middle;
    if (*middle > val) return binary_search(val, start, middle);
    return binary_search(val, middle + 1, end);
}

void make_set(set_t *data) {
    data = (set_t *)malloc(sizeof(set_t));
    data->vec = malloc(CHUNK * sizeof(int));
    data->allocated = CHUNK;
    data->size = 0;
}

void union_set(const set_t *a, const set_t *b, set_t *uni) {
    make_set(uni);
    assign_set(uni, a);
    for (int i = 0; i < b->size; i++)
        insert_set(b->vec[i], uni);
}

void intersection_set(const set_t *a, const set_t *b, set_t *intersection) {
    make_set(intersection);
    for (int i = 0; i < a->size; i++)
        if (is_member(a->vec[i], b))
            insert_set(a->vec[i], intersection);
}

void diff_set(const set_t *a, const set_t *b, set_t *diff) {
    make_set(diff);
    assign_set(diff, a);
    for (int i = 0; i < a->size; i++)
        if (is_member(a->vec[i], b))
            remove_set(a->vec[i], diff);
}

bool is_member(int x, const set_t *a) {
    return binary_search(x, a->vec, a->vec + a->size) != NULL;
}

void insert_set(int x, set_t *a) {
    int i;
    // Encontra índice de um elemento maior ou igual a x.
    for (i = 0; i < a->size && a->vec[i] < x; i++);
    // Caso o elemento não exista (seja maior e não igual), shifta o vetor e insere x.
    if (a->vec[i] > x) {
        maybe_reallocate(a, a->size);
        for (int j = a->size; j > i; j--)
            a->vec[j] = a->vec[j - 1];
        a->vec[i] = x;
        a->size++;
    }
}

void remove_set(int x, set_t *a) {
    int *element = binary_search(x, a->vec, a->vec + a->size);
    if (element) {
        long index = element - a->vec;
        a->size--;
        for (int i = index; i < a->size; i++)
            a->vec[i] = a->vec[i + 1];
    }
}

void assign_set(set_t *a, const set_t *b) {
    if (a->allocated != b->allocated)
        a->vec = (int *)realloc(a->vec, b->size * sizeof(int));

    a->size = b->size;
    a->allocated = b->allocated;
    for (int i = 0; i < b->size; i++)
        a->vec[i] = b->vec[i];
}

int min_set(const set_t *a) {
    return a->vec[0];
}

int max_set(const set_t *a) {
    return a->vec[a->size-1];
}

bool equal_set(const set_t *a, const set_t *b) {
    if (a->size == b->size) {
        for (int i = 0; i < a->size; i++)
            if (a->vec[i] != b->vec[i]) return false;

        return true;
    }
    return false;
}

void free_set(set_t *a) {
    free(a->vec);
    free(a);
    a = NULL;
}

void print_set(const set_t *a) {
    printf("Set: ");
    for (int i = 0; i < a->size; i++) printf("%d ", a->vec[i]);
    printf("\n");
}