/**
 * Módulo CSV.
 *
 * Esse módulo é genérico para qualquer CSV. Ele pode ser utilizado para carregar
 * CSVs de maneira rápida e eficiente e consegue armazenar cada linha do CSV num
 * formato que modela algum struct.
 *
 * Note que:
 *  - Antes de carregar o CSV, todas as colunas devem ter sido registradas.
 *  - O CSV deve ter uma primeira linha de header que define o nome de cada coluna.
 *  - Cada coluna deve ter exatamente um tipo.
 *  - Todas as linhas devem possuir valores para todas as colunas.
 */

#ifndef __CSV_H__
#define __CSV_H__

#include <stdlib.h>
#include <stdbool.h>
#include <parsing.h>

#define csv_model(structure) csv_create(sizeof(structure));

// Tipo incompleto de acesso ao Tipo Abstrato de Dado csv_t.
typedef struct _csv csv_t;

// Todos os tipos primitivos suportados. Todos os tipos que uma célula do CSV
// pode assumir.
typedef enum {
    TYPE_INTEGER,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_GENERIC,
    TYPE_NOTHING
} primitive_type_t;

/**
 * Cria o TAD csv_t.
 *
 * @param elsize - o tamanho do struct a ser espelhado. Valor máximo da soma dos
 *                 tamanhos de todas as colunas.
 * @return o TAD csv sem nenhuma coluna nem nenhuma linha lida. [ownership]
 */
csv_t *csv_create(size_t elsize);

/**
 * Libera a memória alocada pelo csv.
 *
 * @param csv - o csv a ser liberado. [ownership]
 */
void csv_destroy(csv_t *csv);

/**
 * Registra uma nova coluna para o csv.
 *
 * @param csv - o csv no qual se deseja registrar a nova coluna. [mut ref]
 * @param column_name - O nome da coluna (mesmo nome que aparece no header). [ref]
 * @param type - o tipo primitivo da coluna.
 */
void csv_add_column(csv_t *csv, const char *column_name, const primitive_type_t type);

/**
 * Carrega um arquivo csv a partir de seu nome.
 *
 * @param csv - o csv sobre o qual carregar os dados. [mut ref]
 * @param fname - o nome do arquivo. [ref]
 */
void csv_load(csv_t *csv, const char *fname);

/* Acesso a informações contidas em csv_t. */

/**
 * Retorna os dados carregados.
 *
 * @param csv - o csv do qual pegar os dados. [ref]
 * @return vetor de valores armazenados empacotados de acordo com as colunas
 *         registradas. Pode ser convertido para um vetor do struct espelhado. [ref]
 */
void **csv_get_values(csv_t *csv);

/**
 * Retorna o número de linhas lidas.
 *
 * @param csv - o csv para o acesso do número de linhas. [ref]
 * @return o número de linhas lidas.
 */
uint csv_get_rows(csv_t *csv);

/**
 * Retorna o índice de uma coluna com determinado nome.
 *
 * @param csv - o csv no qual o índice será baseado. [ref]
 * @param field_name - o nome do campo a ser procurado. [ref]
 * @return o índice desejado ou -1 caso field_name não seja uma das colunas.
 */
int csv_get_field_index(csv_t *csv, char *field_name);

/* Outros */

/**
 * Converte um tipo primitivo em uma string que o representa.
 *
 * @param type - o tipo a ser convertido em string.
 * @return a string que representa o tipo. [ref]
 */
char *type_to_string(primitive_type_t type);

/**
 * Imprime o header do CSV gerado a partir das colunas registradas e seus tipos.
 *
 * @param csv - o csv utilizado para a impressão. [ref]
 */
void csv_print_header(csv_t *csv);

#endif
