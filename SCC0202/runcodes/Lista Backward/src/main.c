#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ler_comando.h>
#include <lista_backward.h>

void imprimir_lista(lista_backward_t *lista) {
    for (no_t *ptr = lista_backward_ini(lista); ptr; ptr = no_proximo(ptr)) {
        no_t *back;
        if ((back = no_back(ptr))) {
            // Mede posição de back na lista.
            int dist = 0;
            for (no_t *tmp = lista_backward_ini(lista); tmp != back && tmp; tmp = no_proximo(tmp))
                dist++;

            printf("[%d,%d,%d] ", no_chave(ptr), no_tempo(ptr), dist);
        } else {
            printf("[%d,%d] ", no_chave(ptr), no_tempo(ptr));
        }
    }
    if (lista_backward_ini(lista) == NULL)
        printf("-1");

    printf("\n");
}

int main(void) {
    lista_backward_t *lista = lista_backward_criar();

    for (int continuar = true, tempo = 0; continuar; tempo++) {
        Comando *comando = ler_comando();
        if (comando == NULL) {
            printf("Comando desconecido\n");
            break;
        }

        switch (comando->tipo) {
            case INSERIR:
            {
                ComandoInserir *inserir = (ComandoInserir *)comando;
                lista_backward_inserir(lista, inserir->chave, inserir->back, tempo);
                break;
            }

            case REMOVER:
            {
                ComandoRemover *remover = (ComandoRemover *)comando;
                no_t *removido = lista_backward_remover(lista, remover->chave);
                no_destruir(removido);
                break;
            }

            default:
                continuar = false;
        }
        free(comando);
    }
    imprimir_lista(lista);
    lista_backward_destruir(lista);

    return EXIT_SUCCESS;
}
