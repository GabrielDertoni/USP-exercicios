#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bigint.h>

// O maior número que pode caber num único nó da lista encadeada.
#define CELL_MAX 100000000000000000LL

// CELL_MAX = 10^MAX_POW. Representa o número de dígitos armazenados em um
// único nó da lista encadeada.
#define MAX_POW 17

typedef struct _num_node num_node_t;
typedef long long int digit_t;

// Um nó na lista duplamente encadeada que forma o tipo big_int_t. Um único nó
// pode armazenar MAX_POW digitos. Isso é feito para obter maior eficiência de
// memória.
struct _num_node {
    digit_t digits;
    num_node_t *next;
    num_node_t *prev;
};

struct _big_int {
    num_node_t *head;
    short int sign; // Indica se o número é positivo ou negativo.
    uint ndigits;
};

big_int_t *big_int_create() {
    big_int_t *num = (big_int_t *)malloc(sizeof(big_int_t));
    // Começa como número indefinido
    num->head = NULL;
    num->ndigits = 0;
    num->sign = 1;
    return num;
}

void big_int_delete(big_int_t *num) {
    for (num_node_t *node = num->head->next; node && node != num->head;) {
        num_node_t *tmp = node->next;
        free(node);
        node = tmp;
    }
    free(num->head);
    free(num);
}

big_int_t *big_int_from_int(int i) {
    big_int_t *num = big_int_create();
    num->sign = i >= 0 ? 1 : -1;
    num_node_t *node = (num_node_t *)malloc(sizeof(num_node_t));
    node->digits = (digit_t)abs(i);
    node->prev = node;
    node->next = node;
    num->head = node;

    return num;
}


big_int_t *big_int_from_str(char *str) {
    big_int_t *num = big_int_create();
    num_node_t *next = NULL;
    int str_start = 0;
    int i = strlen(str) - 1;

    switch(str[0]) {
        case '-':
            num->sign = -1;
            str_start++;
        break;

        case '+':
            str_start++;

        default:
            num->sign = 1;
    }

    while (i >= str_start) {
        num_node_t *node = (num_node_t *)malloc(sizeof(num_node_t));
        node->digits = 0;
        node->prev = NULL;
        node->next = next;

        digit_t curr_pow = 1;
        for (int j = 0; str[i] && j < MAX_POW; i--, j++) {
            node->digits += (str[i] - '0') * curr_pow;
            curr_pow *= 10;
        }

        if (next != NULL)
            next->prev = node;
        else
            num->head = node;

        next = node;
        num->ndigits++;
    }
    num->head->next = next;
    next->prev = num->head;

    num->head = next;

    return num;
}

// NOTE: Não há suporte para adição de números negativos.
big_int_t *big_int_sum(big_int_t *a, big_int_t *b) {
    big_int_t *result = big_int_create();
    num_node_t *next = NULL;
    int carry = 0, i = 0;

    num_node_t *na = a->head->prev, *nb = b->head->prev;
    do {
        num_node_t *node = (num_node_t *)malloc(sizeof(num_node_t));
        node->digits = carry;
        node->prev = NULL;
        node->next = next;

        if (i < a->ndigits) {
            node->digits += na->digits;
            na = na->prev;
        }

        if (i < b->ndigits) {
            node->digits += nb->digits;
            nb = nb->prev;
        }

        if ((carry = node->digits / CELL_MAX))
            node->digits %= CELL_MAX;

        if (!next) result->head = node;

        i++;
        next = node;
    } while (carry || i < a->ndigits || i < b->ndigits);

    result->ndigits = i;
    result->head->next = next;
    next->prev = result->head;

    result->head = next;

    return result;
}

int big_int_compare(big_int_t *a, big_int_t *b) {
    if (a->ndigits != b->ndigits) return a->ndigits - b->ndigits;

    num_node_t *na = a->head, *nb = b->head;
    for (int i = 0;
         i < a->ndigits && na->digits == nb->digits;
         na = na->next, nb = nb->next, i++);

    if (na->digits > nb->digits) return 1;
    else if (na->digits < nb->digits) return -1;
    else return 0;
}

void big_int_print(big_int_t *num) {
    if (num->sign < 0) printf("-");
    printf("%lld", llabs(num->head->digits));
    for (num_node_t *n = num->head->next; n != num->head; n = n->next)
        printf("%0*lld", MAX_POW, llabs(n->digits));
}

void big_int_println(big_int_t *num) {
    big_int_print(num);
    printf("\n");
}


