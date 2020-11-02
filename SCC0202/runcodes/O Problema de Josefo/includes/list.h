#ifndef __LIST_H__
#define __LIST_H__

typedef int elem_t;
typedef struct _list list_t;
typedef struct _node node_t;


// Funções para listas.
list_t *listCreate();
node_t *listGetLastNode(list_t *list);
node_t *listAppend(list_t *list, elem_t element);
// Remove o nó no índice index e retorna o nó removido.
node_t *listRemoveAt(list_t *list, int index);
// Remove o nó se ele pertence à lista e retorna o nó que fica em seu lugar.
node_t *listRemoveNode(list_t *list, node_t *node);
int listGetSize(list_t *list);
node_t *listGetHeadNode(list_t *list);
node_t *listGetNodeAt(list_t *list, int index);
void listDestroy(list_t *list);
void listPrint(list_t *list);

// Funções para nós.
elem_t nodeGetValue(node_t *node);
void nodeConnect(node_t *node1, node_t *node2);
node_t *nodeGetNext(node_t *node);
void nodeDestroy(node_t *node);

#endif