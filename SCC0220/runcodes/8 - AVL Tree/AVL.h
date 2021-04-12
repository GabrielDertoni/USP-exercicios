/**
 * Avl Tree Module
 *
 * This module implements an Avl Abstract Data Type.
 */

#ifndef __AVL_H__
#define __AVL_H__

#include <stdlib.h>
#include <stdbool.h>

// A node in the AVL tree structure.
typedef struct _avl_node avl_node_t;

// The AVL Abstract Data Type handle.
typedef struct _avl avl_t;

// A function that is able to compare two elements of the AVL.
typedef int (*comp_fn_t)(void *, void *);

// A function that is able to free a single element of the AVL.
typedef void (*free_fn_t)(void *);

// A function that takes as input an element and some aditional optional argument.
typedef void (*elem_fn_t)(void *, void *);

// A function that takes as input a node and some aditional optional argument.
typedef void (*node_fn_t)(avl_node_t *, void *);

/**
 * Creates the AVL Tree Abstract Data Type
 *
 * @param elsize - the size of the elements to be stored in the AVL tree.
 * @param comp - the comparison function to use to construct the structure.
 * @return the newly created avl. [ownership]
 */
avl_t *avl_create(size_t elsize, comp_fn_t comp);

/**
 * Frees the AVL tree data structure and all element in it.
 *
 * @param avl - the AVL tree to delete. [ownership]
 * @param free_fn - a function to free a pointer to the element.
 */
void avl_delete(avl_t *avl, free_fn_t free_fn);

/**
 * Searches for an element in the AVL tree.
 *
 * @param avl - the AVL to search inside. [ref]
 * @param element - the element to search for (with `comp` function). [ref]
 * @return NULL if no element is found and the element if it is. [ref]
 */
void *avl_search(avl_t *avl, void *element);

/**
 * Inserts an element into the AVL tree.
 *
 * @param avl - the AVL tree to insert the element in. [mut ref]
 * @param element - the element to insert. [ref]
 * @return true if the insertion is successfull, false if it is a duplicate.
 */
bool avl_insert(avl_t *avl, void *element);

/**
 * Removes an element from the AVL tree.
 *
 * @param avl - the AVL tree to remove the element from. [mut ref]
 * @param element - the element to search and remove. [ref]
 * @param free_fn - the function to free the found element pointer.
 * @return true if the removal is successfull, false if element is not found.
 */
// bool avl_remove(avl_t *avl, void *element, free_fn_t free_fn);

/**
 * Gets the number of elements in the AVL tree.
 *
 * @param avl - the AVL tree to get the size from. [ref]
 * @return the size of the AVL tree.
 */
size_t avl_get_size(avl_t *avl);

/**
 * Functions of type: avl_<order>_foreach
 *
 * Iterate through every element in the AVL tree according to <order> and then
 * call `func` with an element as its first argument and `args` as the second.
 *
 * @param avl - the AVL tree to traverse. [ref]
 * @param func - the function to call in each element.
 * @param args - optional arguments to be sent to `func`. [mut ref]
 */
void avl_inorder_foreach(avl_t *avl, elem_fn_t func, void *args);
void avl_preorder_foreach(avl_t *avl, elem_fn_t func, void *args);
void avl_postorder_foreach(avl_t *avl, elem_fn_t func, void *args);

/**
 * Functions of type: avl_<order>_foreach_node
 *
 * Iterate through every node in the AVL tree according to <order> and then call
 * `func` with a node as its first argument and `args` as the second.
 *
 * @param avl - the AVL tree to traverse. [ref]
 * @param func - the function to call in each node.
 * @param args - optional arguments to be sent to `func`. [mut ref]
 */
void avl_inorder_foreach_node(avl_t *avl, node_fn_t func, void *args);
void avl_preorder_foreach_node(avl_t *avl, node_fn_t func, void *args);
void avl_postorder_foreach_node(avl_t *avl, node_fn_t func, void *args);

/* Node operations */

int avl_node_height(avl_node_t *node);

/**
 * Get the value of a AVL tree node.
 *
 * @param node - the node to get the value from. [ref]
 * @return the value of the node.
 */
void *avl_node_value(avl_node_t *node);

#endif
