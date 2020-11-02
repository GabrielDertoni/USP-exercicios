#include <stdio.h>
#include <stdlib.h>
#include <lista_backward.h>

struct _lista_backward {
    no_t *ini;
    no_t *fim;
    unsigned int nelem;
};

struct _no {
    no_t *prox;
    no_t *ant;
    no_t *back;
    int chave;
    int tempo;
};


no_t *no_proximo(no_t *no) {
    return no->prox;
}

no_t *no_anterior(no_t *no) {
    return no->ant;
}

no_t *no_back(no_t *no) {
    return no->back;
}

int no_chave(no_t *no) {
    return no->chave;
}

int no_tempo(no_t *no) {
    return no->tempo;
}

no_t *no_criar(int chave, int tempo, no_t *ant, no_t *back) {
    no_t *no = (no_t *)malloc(sizeof(no_t));
    assert_neq(no, NULL, "Allocation on node failed.");

    no->prox = NULL;
    no->ant = ant;
    no->chave = chave;
    no->back = back;
    no->tempo = tempo;

    return no;
}

void no_destruir(no_t *no) {
    free(no);
}

lista_backward_t *lista_backward_criar() {
    lista_backward_t *l = (lista_backward_t *)malloc(sizeof(lista_backward_t));
    assert_neq(l, NULL, "Newly created list may not be NULl.");

    l->ini = NULL;
    l->fim = NULL;
    l->nelem = 0;
    return l;
}

no_t *lista_backward_ini(lista_backward_t *l) {
    return l->ini;
}

no_t *lista_backward_fim(lista_backward_t *l) {
    return l->fim;
}

no_t *lista_backward_inserir(lista_backward_t *l, int chave, int back, int tempo) {
    assert_neq(l, NULL, "Impossible to insert in NULL list.");
    no_t *no_back = back == 0 ? NULL : l->fim;
    for (int i = 1; i < back && no_back; i++, no_back = no_back->ant);

    no_t *no = no_criar(chave, tempo, l->fim, no_back);

    if (!l->nelem)
        l->ini = no;
    else
        l->fim->prox = no;

    l->fim = no;
    l->nelem++;

    return no;
}

no_t *lista_backward_encontrar(lista_backward_t *l, int chave) {
    no_t *no;
    for (no = l->ini; no && no->chave != chave; no = no->prox);
    return no;
}

void lista_backward_remover_no(lista_backward_t *l, no_t *no) {
    if (l->ini == no)
        l->ini = no->prox;

    if (l->fim == no)
        l->fim = no->ant;

    if (no->ant)
        no->ant->prox = no->prox;

    if (no->prox)
        no->prox->ant = no->ant;

    for (no_t *no_ptr = no->prox; no_ptr; no_ptr = no_ptr->prox)
        if (no_ptr->back == no)
            no_ptr->back = NULL;

    l->nelem--;
}

no_t *lista_backward_remover(lista_backward_t *l, int chave) {
    assert_neq(l, NULL, "Impossible to remove from NULL list.");
    no_t *remove = lista_backward_encontrar(l, chave);
    if (!remove) return NULL;
    lista_backward_remover_no(l, remove);
    return remove;
}

void lista_backward_imprimir(lista_backward_t *l) {
    if (l->ini == 0) {
        printf("[]");
        return;
    }
    printf("[ %d", l->ini->chave);
    for (no_t *ptr = l->ini->prox; ptr; ptr = ptr->prox)
        printf(", %d", ptr->chave);

    printf(" ]\n");
}

void lista_backward_destruir(lista_backward_t *l) {
    if (l->ini != NULL)
        for (no_t *ptr = l->ini; ptr;) {
            no_t *tmp = ptr->prox;
            no_destruir(ptr);
            ptr = tmp;
        }

    free(l);
}

