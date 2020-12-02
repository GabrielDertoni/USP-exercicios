#include <stdio.h>
#include <stdlib.h>
#include <tree.h>

const char *node_type_as_string[3] = {
    "raiz",
    "interno",
    "folha"
};

void print_node_info(tree_t *tree, tree_node_t *node) {
    tree_node_t *parent = tree_search_parent(tree, tree_node_get_value(node));

    tree_node_t *left = tree_node_get_left(node);
    tree_node_t *right = tree_node_get_right(node);

    printf("no %d: pai = %d, altura = %d, grau = %d, filhos = (%d,%d), tipo = %s\n",
           tree_node_get_value(node),
           parent ? tree_node_get_value(parent) : -1,
           tree_node_get_height(node),
           tree_node_get_degree(node),
           left ? tree_node_get_value(left) : -1,
           right ? tree_node_get_value(right) : -1,
           node_type_as_string[tree_get_node_type(tree, node)]);
}

void dfs_print_tree_info(tree_t *tree, tree_node_t *node) {
    if (!node) return;
    print_node_info(tree, node);
    dfs_print_tree_info(tree, tree_node_get_left(node));
    dfs_print_tree_info(tree, tree_node_get_right(node));
}

int main(int argc, char *argv[]) {
    int n, id, right, left;
    tree_t *tree = tree_create();

    scanf(" %d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %d %d %d", &id, &left, &right);

        // NULL_VALUE é uma macro que define o valor de nó pai que representa a raiz.
        // Nesse caso, dizemos que se nenhum nó estiver presente na árvore, iremos
        // inserir um nó como raiz.
        if (i == 0)
            tree_insert_right(tree, NULL_VALUE, id);

        // Se o valor recebido for -1, ne adiciona o nó.
        if (left >= 0)
            tree_insert_left(tree, id, left);

        if (right >= 0)
            tree_insert_right(tree, id, right);
    }

    dfs_print_tree_info(tree, tree_get_root(tree));

    tree_delete(tree);

    return EXIT_SUCCESS;
}

