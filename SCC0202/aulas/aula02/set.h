#ifndef SET
#define SET

#include <stdbool.h>

typedef struct {
  int *vec;
  unsigned int size;
  unsigned long allocated;
} set_t;

// Faz o conjunto vazio ser o valor para a variável conjunto A
void make_set(set_t *data);

// Toma os argumentos A e B que são conjuntos e retorna A u B à variável C
void union_set(const set_t *a, const set_t *b, set_t *uni);

// Toma os argumentos A e B que são conjuntos e retorna A ^ B à variável C
void intersection_set(const set_t *a, const set_t *b, set_t *intersection);

// Toma os argumentos A e B que são conjuntos e retorna A - B à variável C
void diff_set(const set_t *a, const set_t *b, set_t *diff);

// Toma o conjunto A e o objeto x cujo tipo é o tipo do elemento de A e retorna
// um valor booleano  true se x Î A e false caso contrário
bool is_member(int x, const set_t *a);

// Toma o conjunto A e o objeto x cujo tipo é o tipo do elemento de A e faz x
// um membro de A. O novo valor de A = A u {x}. Se x já é um membro de A, então
// a operação insere não muda A
void insert_set(int x, set_t *a);

// Remove o objeto x, cujo tipo é o tipo do elemento de A, de A. O novo valor
// de A = A - {x}. Se x não pertence a A então a operação remove não altera A
void remove_set(int x, set_t *a);

// Seta o valor da variável conjunto A = ao valor da variável conjunto B
void assign_set(set_t *a, const set_t *b);

// Retorna o valor mínimo no conjunto A. Por exemplo: Min({2,3,1}) = 1 e
// Min({‘a’,’b’,’c’}) = ‘a’
int min_set(const set_t *a);

// Similar a Min(A) só que retorna o máximo do conjunto
int max_set(const set_t *a);

// Retorna true se e somente se os conjuntos A e B consistem dos mesmos
// elementos
bool equal_set(const set_t *a, const set_t *b);

// Libera a memória usada por A
void free_set(set_t *a);

// Imprime os elementos do conjunto.
void print_set(const set_t *a);

#endif
