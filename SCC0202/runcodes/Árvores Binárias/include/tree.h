#ifndef __TREE_H__
#define __TREE_H__

#define NULL_VALUE -1

typedef int elem_t;
typedef struct _binary_tree_node tree_node_t;
typedef struct _binary_tree tree_t;

typedef enum {
    ROOT,
    NODE,
    LEAF
} node_type_t;

tree_t *tree_create();
void tree_delete(tree_t *tree);
tree_node_t *tree_search(tree_t *tree, elem_t value);
tree_node_t *tree_insert_right(tree_t *tree, elem_t parent, elem_t value);
tree_node_t *tree_insert_left(tree_t *tree, elem_t parent, elem_t value);
tree_node_t *tree_search_parent(tree_t *tree, elem_t value);
tree_node_t *tree_get_root(tree_t *tree);

int tree_node_get_height(tree_node_t *node);
int tree_node_get_degree(tree_node_t *node);
elem_t tree_node_get_value(tree_node_t *node);
tree_node_t *tree_node_get_left(tree_node_t *node);
tree_node_t *tree_node_get_right(tree_node_t *node);
node_type_t tree_get_node_type(tree_t *tree, tree_node_t *node);

tree_node_t *tree_node_create(elem_t value);
void tree_node_delete(tree_node_t *node);


#endif
