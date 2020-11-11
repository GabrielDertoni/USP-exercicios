#ifndef __BIGINT_H__
#define __BIGINT_H__

// O tipo acessível por usuários que permite números inteiros de tamanho
// arbitrário.
typedef struct _big_int big_int_t;

// Cria (aloca) um big_int_t sem nenhum valor dentro, como um número indefinido.
big_int_t *big_int_create();

// Libera o conteúdo de um big_int_t.
void big_int_delete(big_int_t *num);

// Cria um big_int_t a partir de uma string com os digitos decimais.
big_int_t *big_int_from_str(char *str);

// Soma dois números big_int_t. NOTE: Não há suporte para soma de negativos.
big_int_t *big_int_sum(big_int_t *a, big_int_t *b);

// Compara dois big_int_t e retorna algo > 0 se a > b, algo < 0 se a < b e 0
// se a = b.
int big_int_compare(big_int_t *a, big_int_t *b);

// Cria um big_int_t a partir de um inteiro comum.
big_int_t *big_int_from_int(int i);

// Imprime um big_int_t (sem '\n' no final).
void big_int_print(big_int_t *num);

// Imprime um big_int_t (com '\n' no final).
void big_int_println(big_int_t *num);

#endif
