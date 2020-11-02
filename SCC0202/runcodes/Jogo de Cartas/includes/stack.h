#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

#define STACK_OP_SUCCESS 1
#define STACK_ERROR_NO_STACK -1
#define STACK_ERROR_EMPTY -2

#define CHUNK 32

// Tipo do elemento pertencente a pilha (pode ser modificado e recompilado).
typedef int elem_t;

// Typedef de acesso a struct de pilha.
typedef struct _stack stack_t;

// Cria uma pilha com n espaços alocados.
stack_t *createStack(int n);

// Libera a memória utilizada 
void deleteStack(stack_t *stack);

// Insere um elemento no topo da pilha e
// aloca mais espaço conforme o necessário.
void pushStack(stack_t *stack, elem_t val);

// Remove e retorna o elemento do topo da pilha e
// libera memória conforme o necessário.
elem_t popStack(stack_t *stack);

// Retorna sem remover o elemento no topo da pilha.
elem_t peakStack(stack_t *stack);

// Verifica se a pilha está vazia.
bool isEmptyStack(stack_t *stack);

// Retorna o tamanho da pilha (número de elementos usados,
// não de elementos alocados).
unsigned int getStackSize(stack_t *stack);

#endif
