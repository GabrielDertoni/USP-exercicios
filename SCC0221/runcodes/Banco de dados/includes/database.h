#ifndef _DB_DATABASE_
#define _DB_DATABASE_

#include "utils.h"
#include "parsing.h"

typedef struct Entry {
	void *key;
	long long offset;
} entry_t;

typedef struct Database {
	metadata meta;
	FILE *fp;
	long long size;
	long long allocated;
	entry_t **index;
} database_t;

/*----- Mais alto nível -----*/

// Performa operação insert. Insere um campo no registro
// de banco de dados e atualiza database_t *db. char **data
// deve ser um vetor de strings, cada uma com o valor correspondente
// a um campo diferente.
void insert(database_t *db, char **data);
// Performa operação index. Cria um ídice a partir do struct db.
void create_index(database_t db);

/*----- Manipulação do struct de banco de dados -----*/

// Cria um struct database_t e o retorna, abre o arquivo de
// registros no modo append e carrega o índice na memória.
// Se o índice não estiver de acordo com o registro, recria o
// índice.
database_t open_databse(metadata meta);
// Fecha o arquivo do banco de dados e libera a memória.
void close_database(database_t *db);

/*----- Escrita e leitura -----*/

// Lê o arquivo meta.filename e armazena todos os pares chave-offset para
// cada entrada no banco de dados. Retorna como um índice fora de ordem.
entry_t **reg2index(metadata meta);
// Carrega um índice a partir de um arquivo dentro do parâmetro ptr.
// Retorna o número de entradas lidas.
long long load_index(entry_t ***ptr, metadata meta);
// Armazena o valor de um campo (condido em char *data), convertido para
// seu tipo (dtype) e tamanho (size) e armazena esses dados em ptr.
void setField(void *ptr, char *data, type dtype, int size);
// Escreve o valor de um campo (condito em char *data), convertido para seu
// tipo (dtype) e tamanho (size) e armazena esses dados no arquivo fp.
void writeField(char *data, type dtype, int size, FILE *fp);
void *readRow(long foffset, database_t db);

/*----- Auxiliáres -----*/

// Retorna o tamanho, em bytes, do conjunto de todos os campos (uma
// linha na "tabela" do banco de dados).
long long sizeofRow(metadata meta);
// Recebe uma string (char *data), um tipo e tamanho. Converte essa
// string para o tipo primitivo indicado por dtype e size, aloca
// memória o suficiente para armazenar esse tipo, e retorna um void *
// que aponta para uma região da memória que contém os dados convertidos.
void *strtoa(char *data, type dtype, int size);
// Retorna o nome do arquivo do índice (muda a extenção do filename dentro
// do meta para .idx).
char *index_name(metadata meta);
// Compara dois valores de acordo com dtype. (converte para o tipo correspondente
// primitiov e faz a comparação), retorna 1 caso a > b, -1 caso a < b e 0 caso
// a == b
int compareTypes(void *a, void *b, type dtype, int size);
// Recebe dois ponteiros que serão convertidos para (entry_t *) e compara as
// chaves de cada uma considerando-as como int. (utilizado com sortWith).
int compareIntKeys(void *a, void *b);
int sizeofType(type dtype);

#endif
