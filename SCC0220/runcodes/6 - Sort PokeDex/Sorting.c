#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Sorting.h"

// Aplica um offset em "addr" por n bytes.
#define memoff(addr, n) ((void *)((byte_t *)(addr) + (n)))

// Troca o conteúdo do ponteiro a com o conteúdo do ponteiro b, sendo que ambos
// os conteúdos possuem tamanho elsize.
#define swap(a, b, elsize) ({ \
    byte_t __t[elsize]; \
    /* Variáveis temporárias que existem apenas para garantir que "a" e "b" serão
       apenas calculados uma vez. Se a = ptr++, por exemplo, usar "a" diretamente
       multiplas vezes na macro resultaria na operação "++" sendo repetida várias
       vezes. */ \
    __typeof__(a) __a = (a); \
    __typeof__(b) __b = (b); \
    memcpy(__t, __a, elsize); \
    memcpy(__a, __b, elsize); \
    memcpy(__b, __t, elsize); \
})

// Parâmetros para Tim Sort.
#define MIN_MERGE 64
#define TIM_MAX_RUNS 85

// Typedef interno utilizado apenas para poder se referir a um tipo de tamanho 1.
typedef unsigned char byte_t;

void quick_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp) {
    if (nmemb <= 1) return;

    void *p1 = memoff(vec, elsize), *p2 = memoff(vec, (nmemb - 1) * elsize);

    // Estratégia de escolha de pivot: sempre o primeiro elemento do vetor.
    void *pivot = vec;

    while (p1 < p2) {
        if (comp(p1, pivot) >= 0 && comp(p2, pivot) < 0) {
            swap(p1, p2, elsize);
            p1 = memoff(p1, elsize);
            p2 = memoff(p2, -elsize);

        } else if (comp(p1, pivot) < 0) {
            p1 = memoff(p1, elsize);

        } else if (comp(p2, pivot) >= 0) {
            p2 = memoff(p2, -elsize);
        }
    }

    if (comp(p2, pivot) < 0) {
        swap(p2, pivot, elsize);
    
    } else {
        p2 = memoff(p2, -elsize);
        swap(p2, pivot, elsize);
    }

    const size_t nleft = (p2 - vec) / elsize;
    quick_sort_with(vec, nleft, elsize, comp);
    quick_sort_with(memoff(p2, elsize), nmemb - nleft - 1, elsize, comp);
}

void make_max_heap_with(void *vec, size_t root, size_t nmemb, size_t elsize, comp_t comp) {
    size_t largest = root;
    size_t left = root * 2 + 1;
    size_t right = left + 1;

    void *leftPtr = memoff(vec, left * elsize);
    void *rightPtr = memoff(vec, right * elsize);

    if (left < nmemb && comp(leftPtr, memoff(vec, largest * elsize)) > 0)
        largest = left;

    if (right < nmemb && comp(rightPtr, memoff(vec, largest * elsize)) > 0)
        largest = right;

    if (largest != root) {
        swap(memoff(vec, root * elsize), memoff(vec, largest * elsize), elsize);
        make_max_heap_with(vec, largest, nmemb, elsize, comp);
    }
}

void heap_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp) {
    // Construct the initial heap.
    for (int i = nmemb / 2 - 1; i >= 0; i--)
        make_max_heap_with(vec, i, nmemb, elsize, comp);

    // Heap sort.
    for (int i = nmemb; i >= 1; i--) {
        make_max_heap_with(vec, 0, i, elsize, comp);
        swap(vec, memoff(vec, (i - 1) * elsize), elsize);
    }
}

void merge_with(void *start, void *mid, void *end, size_t elsize, comp_t comp) {
    void *auxorig = malloc(end - start);
    void *startPtr = start, *midPtr = mid, *aux = auxorig;

    while (startPtr < mid && midPtr < end) {
        if (comp(startPtr, midPtr) <= 0) {
            memcpy(aux, startPtr, elsize);
            startPtr = memoff(startPtr, elsize);
        } else {
            memcpy(aux, midPtr, elsize);
            midPtr = memoff(midPtr, elsize);
        }
        aux = memoff(aux, elsize);
    }

    if (startPtr < mid) 
        memcpy(aux, startPtr, mid - startPtr);

    memcpy(start, auxorig, midPtr - start);
    free(auxorig);
}

// Necessária para binary_insertion_sort_with(). Retorna o primeiro elemento dentro
// de um vetor `vec` de `nmemb` elementos, para o qual a comparação com `search`
// seja > 0. Mesmo que upper_bound() na C++ STL.
void *upper_bound(void *search, void *vec, size_t nmemb, size_t elsize, comp_t comp) {
    size_t p, step, start = 0;
    while (nmemb > 0) {
        step = nmemb / 2;
        p = start + step;
        if (comp(search, vec + p * elsize) >= 0) {
            start = p + 1;
            nmemb -= step + 1;
        } else {
            nmemb = step;
        }
    }
    return vec + start * elsize;
}

// Primeiro encontra o lugar onde o elemento será inserido, em seguida insere.
// Como upper_bound() é O(log n), não são necessárias menos comparações que o
// insertion sort tradicional. Mas o tempo de execução ainda é O(n^2).
void binary_insertion_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp) {
    void *bound;
    for (size_t i = 1; i < nmemb; i++) {
        bound = upper_bound(vec + i * elsize, vec, i, elsize, comp);
        for (void *ptr = vec + i * elsize; ptr > bound; ptr -= elsize)
            swap(ptr, ptr - elsize, elsize);
    }
}

// Encontra o tamanho de mínimo que uma run pode ter baseado no tamanho da entrada.
inline static uint tim_minrun(size_t n) {
    uint r = 0;
    while (n >= MIN_MERGE) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

// Inverte um vetor `vec` de `nmemb` elementos.
inline static void reverse_vec(void *vec, size_t nmemb, size_t elsize) {
    for (int i = 0; i < nmemb / 2; i++)
        swap(vec + i * elsize, vec + (nmemb - i - 1) * elsize, elsize);
}

// Retorna 1 se `a` > 0, -1 se `a` < 0 e 0 se `a` = 0.
inline static int sign(int a) { return a > 0 ? 1 : (a == 0 ? 0 : -1); }

// Encontra o tamanho de uma run dentro de um vetor `start` de `nmemb` elementos.
// Se a dieração for decrescente, inverte o vetor.
static size_t find_run(void *start, size_t nmemb, size_t elsize, comp_t comp) {
    if (nmemb == 1) return 1;
    size_t end = 1;
    int dir = 0;
    void *ptr;
    for (ptr = start + elsize;
         end < nmemb && (dir = comp(ptr - elsize, ptr)) == 0;
         ptr += elsize, end++);

    while (end < nmemb - 1 && sign(dir) == sign(comp(ptr, ptr + elsize)))
         ptr += elsize, end++;

    // If the order is reversed, reverse the subarray.
    if (dir > 0) reverse_vec(start, end + 1, elsize);
    return end + 1;
}

// Struct usado para armazenar uma run.
struct tim_run {
    size_t start;
    uint size;
};

// Se as invariantes da stack forem violadas, junta as runs do topo da stack.
static void tim_merge(void *vec, size_t elsize, comp_t comp, struct tim_run *s, uint *sz) {
    uint n = *sz;
    bool inv1 = true;
    bool inv2 = false;
    while (n > 1 && !(inv1 && inv2)) {
        inv1 = s[n-2].size > s[n-1].size;
        inv2 = n < 3 || s[n-3].size > s[n-2].size + s[n-1].size;
        if (n >= 3 && !(inv1 && inv2)) {
            // TODO: replace with a more efficient merge algorithm.
            // TODO: add galloping to merge.
            if (s[n-1].size < s[n-3].size) {
                // Merge Y + X
                merge_with(vec + s[n-2].start * elsize,
                           vec + s[n-1].start * elsize,
                           vec + (s[n-1].start + s[n-1].size) * elsize,
                           elsize, comp);

                s[n-2].size += s[n-1].size; // start is the same.
            } else {
                // Merge Z + Y
                merge_with(vec + s[n-3].start * elsize,
                           vec + s[n-2].start * elsize,
                           vec + (s[n-2].start + s[n-2].size) * elsize,
                           elsize, comp);

                s[n-3].size += s[n-2].size; // start is the same.
                s[n-2] = s[n-1]; // Copy X one position down the stack.
            }
            n--; // One value was popped from the stack.
        } else if (!inv1) {
            // Merge X + Y
            merge_with(vec + s[n-2].start * elsize,
                       vec + s[n-1].start * elsize,
                       vec + (s[n-1].start + s[n-1].size) * elsize,
                       elsize, comp);

            s[n-2].size += s[n-1].size;
            n--;
        }
    }
    *sz = n;
}

// Junta todas as runs restantes na stack.
static void tim_merge_force(void *vec, size_t elsize, comp_t comp, struct tim_run *s, uint *sz) {
    uint n;
    for (n = *sz; n > 1; n--) {
        merge_with(vec + s[n-2].start * elsize,
                   vec + s[n-1].start * elsize,
                   vec + (s[n-1].start + s[n-1].size) * elsize,
                   elsize, comp);

        s[n-2].size += s[n-1].size;
    }
    *sz = n;
}

// Source: "https://pt.wikipedia.org/wiki/Timsort"
void tim_sort_with(void *vec, size_t nmemb, size_t elsize, comp_t comp) {
    if (nmemb < MIN_MERGE)
        return binary_insertion_sort_with(vec, nmemb, elsize, comp);

    uint minrun = tim_minrun(nmemb);
    void *run_ptr = vec;

    struct tim_run stack[TIM_MAX_RUNS];
    uint stack_sz = 0;

    for (int i = 0; i < nmemb;) {
        uint run_size = find_run(run_ptr, nmemb - i, elsize, comp);

        // Push into the stack.
        stack[stack_sz].start = i;
        if (run_size >= minrun || i + run_size == nmemb) {
            stack[stack_sz].size = run_size;
        } else {
            stack[stack_sz].size = i + minrun < nmemb ? minrun : nmemb - i;
            binary_insertion_sort_with(run_ptr, stack[stack_sz].size, elsize, comp);
        }
        i += stack[stack_sz].size;
        run_ptr += stack[stack_sz].size * elsize;
        stack_sz++;

        tim_merge(vec, elsize, comp, stack, &stack_sz);
    }
    tim_merge_force(vec, elsize, comp, stack, &stack_sz);
}
