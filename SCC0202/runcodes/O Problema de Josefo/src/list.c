#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <debug.h>

struct _node {
  elem_t element;
  node_t *next;
};

struct _list {
  node_t *head;
  int size;
};

list_t *listCreate() {
  list_t *list = (list_t *)malloc(sizeof(list_t));
  list->head = NULL;
  list->size = 0;
  return list;
}

node_t *listGetLastNode(list_t *list) {
  node_t *node = list->head;
  if (node == NULL) return NULL;
  while (node->next != NULL) node = node->next;
  return node;
}

node_t *listAppend(list_t *list, elem_t element) {
  node_t *last = listGetLastNode(list);
  node_t *next = (node_t *)malloc(sizeof(node_t));
  next->element = element;
  next->next = NULL;

  if (!last)
    list->head = next;
  else
    last->next = next;
  
  list->size++;
  return next;
}

node_t *listRemoveAt(list_t *list, int index) {
  if (!list->size) return NULL;
  if (index == 0) {
    node_t *rmNode = list->head;
    list->head = rmNode->next;
    list->size--;
    return rmNode;
  }
  node_t *prevNode = list->head;
  for (int i = 0; i < index - 1; i++, prevNode = prevNode->next);
  node_t *rmNode = prevNode->next;
  prevNode->next = rmNode->next;
  list->size--;
  return rmNode;
}

node_t *listRemoveNode(list_t *list, node_t *node) {
  if (node == NULL) return NULL;
  // Procura pelo nó anterior ao node.
  node_t *prev;
  for (prev = list->head; prev->next && prev->next != node && prev->next != list->head; prev = prev->next);
  if (!prev->next) return NULL;
  prev->next = node->next;
  if (node == list->head) list->head = node->next;
  list->size--;
  return node->next;
}

node_t *listGetHeadNode(list_t *list) {
  return list->head;
}

node_t *listGetNodeAt(list_t *list, int index) {
  if (list->size == 0) return NULL;
  if (index == 0) return list->head;
  node_t *node = list->head;
  for (int i = 0; i < index && node != NULL; i++, node = node->next);
  return node;
}

int listGetSize(list_t *list) {
  return list->size;
}

void listDestroy(list_t *list) {
  node_t *node = list->head;
  for (int i = 0; i < list->size; i++, node = node->next)
    nodeDestroy(node);
  
  free(list);
}

void listPrint(list_t *list) {
  if (list->size == 0) {
    printf("[]\n");
    return;
  }

  printf("[%d", list->head->element);
  node_t *node = list->head->next;
  for (int i = 1; node != NULL && i < list->size; node = node->next, i++)
    printf(", %d", node->element);

  printf("]\n");
}

elem_t nodeGetValue(node_t *node) {
  return node->element;
}

void nodeConnect(node_t *node1, node_t *node2) {
  node1->next = node2;
}

node_t *nodeGetNext(node_t *node) {
  return node->next;
}

void nodeDestroy(node_t *node) {
  free(node);
}