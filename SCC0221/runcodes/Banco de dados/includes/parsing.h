#ifndef _DB_PARSING_
#define _DB_PARSING_

#include <stdio.h>
#include "utils.h"

// Enum que representa os diferentes tipos de campo.
typedef enum Type { Void, Char, Int, Float, Double } type;
// Struct de campo, utilizado para armazenar as informaçoes sobre um
// campo.
typedef struct Field {
	char *name;
	type dtype;
	int size;
} field;

// Struct de metadados, utilizado para armazenar os metadados do
// banco de dados.
typedef struct Metadata {
	char *filename;
	field *key;
	int n_fields;
	field **fields;
} metadata;

/*----- Parsing -----*/

// Lê, a partir de um arquivo, metadados e gera um struct de metadados de
// acordo com o formato:
// filename: <nome do arquivo>
// key-name: <nome da chave>
// key-type: <tipo da chave>[<tamanho da chave>]
// field-name: <nome do campo>
// field-type: <tipo do campo>[<tamanho do campo>]
// (...)
metadata *parseMetadata(FILE *fp);
// Lê um único campo com nome, tipo e tamanho de um arquivo de acordo com
// o formato:
// field-name: <nome do campo>
// field-type: <tipo do campo>[<tamanho do campo>]
field *parseField(FILE *fp);
// Pula qualquer caractere dentro de ignore até que uma caractere
// que não exista em ignore seja encontrada. Retorna o número de
// caracteres ignoradas.
int skip(char *ignore, FILE *fp);

/*----- Conversão -----*/

// Converte uma string para um type (enum).
type str2type(char *str);

/*-----  Tipos de caractere. -----*/

BOOL isWord(int c);
BOOL isLine(int c);
BOOL isLetter(int c);
BOOL isDigit(int c);
BOOL isSpace(int c);
BOOL isPartOfNumber(int c);

/*----- Funções de leitura. -----*/

// Lê uma linha (ignora !isLine(c) antes de ler).
char *readLine(FILE *fp);

// Lê uma palavra (ignora !isWord(c) antes de ler).
char *readWord(FILE *fp);

// Lê um inteir (ignora !isPartOfNumber(c) antes de ler).
char *readInt(FILE *fp);

// Lê enquanto condition(c) for verdadeiro.
char *readWhile(BOOL (*condition)(int), FILE *fp);

// Ignora qualquer caractere dentro de ignore_prefix antes de ler,
// lê até que alguma caractere dentro de stop seja encontrada.
char *readBetween(char *ignore_prefix, char *stop, FILE *fp);
//int parseMetadata(char *filename);

/*----- Manipulação de erros. -----*/

// Se sertifica que str1 == srt2, se não forem iguais, sai do programa
// e imprime msg.
void assert_str(char *str1, char *str2, char *msg);

#endif
