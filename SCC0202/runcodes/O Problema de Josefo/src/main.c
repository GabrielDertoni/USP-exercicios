#include <stdio.h>
#include <stdlib.h>
#include <list.h>

#define MAIN_DEBUG
#include <debug.h>


int main() {
  int t;
  scanf(" %d", &t);

  for (int i = 0; i < t; i++) {
    int n, k;
    scanf(" %d %d", &n, &k);
    k--; // Converte de posição para índice.
    list_t *list = listCreate();
    for (int j = 0; j < n; j++) 
      listAppend(list, j + 1);
    
    nodeConnect(listGetLastNode(list), listGetHeadNode(list)); // Torna a lista circular.
    for (node_t *node = listGetNodeAt(list, k); listGetSize(list) > 1;) {
      node_t *next = listRemoveNode(list, node);
      for (int j = 0; j < k && next; j++, next = nodeGetNext(next));
      nodeDestroy(node); // Libera o nó recentemente deletado.
      node = next;
    }
    
    printf("Caso %d: %d\n", i + 1, nodeGetValue(listGetHeadNode(list)));
    listDestroy(list);
  }
}