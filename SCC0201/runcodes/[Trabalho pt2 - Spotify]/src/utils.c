#include <stdlib.h>
#include <string.h>
#include <utils.h>

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

void radix256_sort_with(void *vec, size_t nmemb, size_t elsize, get_key_t get_key, void *arg) {
    void *output = malloc(nmemb * elsize);
    uint *count = (uint *)malloc(256 * sizeof(uint));
    for (int shift = 0; shift < 32; shift += 8) {
        // Zero the counts.
        memset(count, 0, 256 * sizeof(uint));

        // Counts
        for (int i = 0; i < nmemb; i++) {
            uint key = get_key(memoff(vec, i * elsize), arg);
            count[(key >> shift) & 0xff]++;
        }

        // Prefix sum
        for (int i = 1; i < 256; i++)
            count[i] += count[i - 1];

        // Replacing
        for (int i = nmemb - 1; i >= 0; i--) {
            void *el = memoff(vec, i * elsize);
            uint key = get_key(el, arg);
            uint idx = --count[(key >> shift) & 0xff];
            memcpy(memoff(output, idx * elsize), el, elsize);
        }

        void **tmp = vec;
        vec = output;
        output = tmp;
    }
    free(output);
    free(count);
}

void *binary_search(void *search, void *vec, size_t nmemb, size_t elsize, comp_t comp) {
    if (nmemb == 0) return NULL;

    void *pivot = memoff(vec, (nmemb / 2) * elsize);
    int comparison = comp(search, pivot);

    if (comparison  < 0)
        return binary_search(search, vec,
                             nmemb / 2,
                             elsize, comp);

    if (comparison  > 0)
        return binary_search(search, memoff(pivot, elsize),
                             nmemb / 2 + nmemb % 2 - 1,     // Ajuste para números pares.
                             elsize, comp);

    return pivot;
}

char *readline(FILE *fp) {
    char *str = NULL;
    int i, c;
    size_t alloc;
    // Consome os primeiros \r\n
    while (strchr("\r\n", c = getc(fp)) && !feof(fp));
    // Consome até o próximo \r\n
    for (i = 0, alloc = 0; !strchr("\r\n", c) && !feof(fp); i++, c = getc(fp)) {
        if ((i + 1) * sizeof(char) >= alloc) {
            if ((alloc *= 2) == 0) alloc = 32 * sizeof(char);
            str = (char *)realloc((void *)str, alloc);
        }
        str[i] = c;
    }

    if (c != EOF) ungetc(c, fp);
    if (alloc == 0) return NULL;
    str[i] = '\0';
    return realloc(str, (i + 1) * sizeof(char));
}

