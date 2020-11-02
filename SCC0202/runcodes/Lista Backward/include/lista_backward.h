#ifndef __LISTA_BACKWARD_H__
#define __LISTA_BACKWARD_H__

#include <stdio.h>

#define assert(af, msg) ({ \
    if (!(af)) { \
        printf("Assertion '" #af "' failed at %s:%d. With message '%s'", __FILE__, __LINE__, msg); \
    } \
})

#define assert_eq(left, right, msg) ({ \
    if ((left) != (right)) { \
        printf("Assertion failed: '" #left " != " #right "' failed at %s:%d. With message '%s'\n", __FILE__, __LINE__, msg); \
    } \
})

#define assert_neq(left, right, msg) ({ \
    if ((left) == (right)) { \
        printf("Assertion failed: '" #left " == " #right "' failed at %s:%d. With message '%s'\n", __FILE__, __LINE__, msg); \
    } \
})

typedef struct _lista_backward lista_backward_t;
typedef struct _no no_t;

no_t *no_criar(int chave, int tempo, no_t *ant, no_t *back);
no_t *no_proximo(no_t *no);
no_t *no_anterior(no_t *no);
no_t *no_back(no_t *no);
int no_chave(no_t *no);
int no_tempo(no_t *no);
void no_destruir(no_t *no);

lista_backward_t *lista_backward_criar();
no_t *lista_backward_ini(lista_backward_t *l);
no_t *lista_backward_fim(lista_backward_t *l);
no_t *lista_backward_inserir(lista_backward_t *l, int chave, int back, int tempo);
no_t *lista_backward_encontrar(lista_backward_t *l, int chave);
void lista_backward_remover_no(lista_backward_t *l, no_t *no);
no_t *lista_backward_remover(lista_backward_t *l, int chave);
void lista_backward_destruir(lista_backward_t *l);
void lista_backward_imprimir(lista_backward_t *l);

#endif
