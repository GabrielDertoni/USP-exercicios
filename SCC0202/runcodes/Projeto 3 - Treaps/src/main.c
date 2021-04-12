#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils.h>
#include <lltreap.h>

void print_node(lltreap_node_t *node, void *arg);
int int_compare(void *a, void *b);

int main(void) {
    int n;
    scanf(" %d", &n);

    lltreap_t *treap = lltreap_create(sizeof(int), int_compare);
    for (int i = 0; i < n; i++) {
        char *line = readline(stdin);
        char *ptr = line; // Utilizado para strsep.
        char *op = strsep(&ptr, " ");

        if (!strcmp(op, "insercao")) {
            int key      = strtol(strsep(&ptr, " "), NULL, 10);
            int priority = strtol(strsep(&ptr, " "), NULL, 10);

            if (!lltreap_insert_with_priority(treap, &key, priority))
                printf("Elemento ja existente\n");

        } else if (!strcmp(op, "remocao")) {
            int key = strtol(strsep(&ptr, " "), NULL, 10);
            if (!lltreap_remove(treap, &key, free))
                printf("Chave nao localizada\n");

        } else if (!strcmp(op, "buscar")) {
            int key = strtol(strsep(&ptr, " "), NULL, 10);
            printf("%d\n", lltreap_search(treap, &key) ? 1 : 0);

        } else if (!strcmp(op, "impressao")) {
            char *mode = strsep(&ptr, " ");

            if (!strcmp(mode, "ordem"))
                lltreap_inorder_foreach_node(treap, print_node, NULL);

            else if (!strcmp(mode, "posordem"))
                lltreap_postorder_foreach_node(treap, print_node, NULL);

            else if (!strcmp(mode, "preordem"))
                lltreap_preorder_foreach_node(treap, print_node, NULL);

            else if (!strcmp(mode, "largura"))
                lltreap_bfs_foreach_node(treap, print_node, NULL);

            else
                printf("Modo invalido\n");

            printf("\n");

        } else {
            // Nunca deveria ocorrer.
            printf("Operacao invalida\n");
        }

        free(line);
    }

    lltreap_delete(treap, free);
    return EXIT_SUCCESS;
}

void print_node(lltreap_node_t *node, void *arg) {
    printf("(%d, %d) ", *(int *)lltreap_node_value(node), lltreap_node_priority(node));
}

int int_compare(void *a, void *b) {
    return *(int *)a - *(int *)b;
}
