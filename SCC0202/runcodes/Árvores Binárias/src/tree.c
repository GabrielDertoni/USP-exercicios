#include <stdio.h>
#include <stdlib.h>
#include <tree.h>

// Macro simples que permite uma definição de max(a, b) genérico todos os tipos
// que podem ser comparados.
#define max(a, b) ({ \
    __typeof__(a) __a = (a); \
    __typeof__(b) __b = (b); \
    __a > __b ? __a : __b; \
 })

struct _binary_tree_node {
    elem_t value;
    tree_node_t *left;
    tree_node_t *right;
};

struct _binary_tree {
    tree_node_t *root;
};

tree_t *tree_create() {
    tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
    tree->root = NULL;
    return tree;
}

static tree_node_t *_tree_search(tree_node_t *root, elem_t value) {
    if (!root)
        return NULL;

    if (root->value == value)
        return root;

    tree_node_t *result;
    if ((result = _tree_search(root->right, value)) ||
        (result = _tree_search(root->left , value))  )
        return result;

    return NULL;
}

tree_node_t *tree_search(tree_t *tree, elem_t value) {
    return _tree_search(tree->root, value);
}

tree_node_t *tree_get_root(tree_t *tree) {
    return tree->root;
}

tree_node_t *tree_node_create(elem_t value) {
    tree_node_t *n = (tree_node_t *)malloc(sizeof(tree_node_t));
    n->right = NULL;
    n->left = NULL;
    n->value = value;

    return n;
}

tree_node_t *tree_insert_right(tree_t *tree, elem_t parent, elem_t value) {
    tree_node_t *parent_node;

    if (parent == NULL_VALUE)
        if (!tree->root)
            return tree->root = tree_node_create(value);
        else
            return NULL;
    else
        if ((parent_node = tree_search(tree, parent)) && !parent_node->right)
            return parent_node->right = tree_node_create(value);
        else
            return NULL;
}

tree_node_t *tree_insert_left(tree_t *tree, elem_t parent, elem_t value) {
    tree_node_t *parent_node;

    if (parent == NULL_VALUE)
        if (!tree->root)
            return tree->root = tree_node_create(value);
        else
            return NULL;
    else
        if ((parent_node = tree_search(tree, parent)) && !parent_node->left)
            return parent_node->left = tree_node_create(value);
        else
            return NULL;
}

static tree_node_t *_tree_search_parent(tree_node_t *root, elem_t value) {
    tree_node_t *result;
    if (!root) return NULL;

    if ((root->left  && root->left->value  == value) ||
        (root->right && root->right->value == value))
        return root;

    if (root->left && (result = _tree_search_parent(root->left, value)))
        return result;

    if (root->right && (result = _tree_search_parent(root->right, value)))
        return result;

    return NULL;
}

tree_node_t *tree_search_parent(tree_t *tree, elem_t value) {
    return _tree_search_parent(tree->root, value);
}

int tree_node_get_height(tree_node_t *node) {
    if (!node) return 0;
    int tmp = 1 + max(tree_node_get_height(node->left),
                   tree_node_get_height(node->right));

    return tmp;
}

int tree_node_get_degree(tree_node_t *node) {
    return (node->right ? 1 : 0) + (node->left ? 1 : 0);
}

elem_t tree_node_get_value(tree_node_t *node) {
    return node->value;
}

// NOTE: Não há garantia de que o nó de fato pertence a árvore, teoricamente essa
// função poderia ser chamada tree = NULL e node como um nó qualquer e o resultado
// seria ou NODE ou LEAF.
node_type_t tree_get_node_type(tree_t *tree, tree_node_t *node) {
    if (tree->root == node) return ROOT;
    if (!node->left && !node->right) return LEAF;
    return NODE;
}

tree_node_t *tree_node_get_right(tree_node_t *node) {
    return node->right;
}

tree_node_t *tree_node_get_left(tree_node_t *node) {
    return node->left;
}

void tree_delete(tree_t *tree) {
    if (!tree) return;
    tree_node_delete(tree->root);
    free(tree);
}

void tree_node_delete(tree_node_t *node) {
    if (!node) return;
    tree_node_delete(node->left);
    tree_node_delete(node->right);
    free(node);
}

