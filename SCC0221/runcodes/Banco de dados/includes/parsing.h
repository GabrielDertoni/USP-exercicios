#ifndef _DB_PARSING_
#define _DB_PARSING_

#include <stdio.h>
#include "utils.h"

// Macros para parsing.
#define LN "\r\n"
#define SPACE " "
#define COMMA ","
#define DOT "."
#define SQUO "'"
#define DQUO "\""
#define LLETTER "abcdefghijklmnopqrstuvwxyz"
#define ULETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTER LLETTER ULETTER
#define DIGIT "0123456789"
#define SIGN "-+"

// Macros para quantidade de alocação.
#define CHUNK 32
#define FIELD_CHUNK 10

// Enum que representa os diferentes tipos de campo.
typedef enum Type { Void, Char, Int, Float, Double } type;
// Struct de campo, utilizado para armazenar as informaçoes sobre um
// campo.
typedef struct Field {
	char *name; // Nome do campo.
	type dtype; // Tipo do campo.
	int size; // Tamanho do campo (expresso em múltiplose do tipo.
	          // Ex.: dtype = Int, size = 1 -> 4 bytes)
} field;

// Struct de metadados, utilizado para armazenar os metadados do
// banco de dados.
typedef struct Metadata {
	char *filename; // Nome do arquivo de registro.
	field key; // Chave primária.
	int n_fields; // Número de campos de dados.
	field *fields; // Vetor de structs de cada campo.
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
metadata parseMetadata(FILE *fp);
// Lê um único campo com nome, tipo e tamanho de um arquivo de acordo com
// o formato:
// field-name: <nome do campo>
// field-type: <tipo do campo>[<tamanho do campo>]
field parseMetaField(FILE *fp);

char *parseField(field meta_field, FILE *fp);

/*----- Conversão -----*/

// Converte uma string para um type (enum).
type str2type(char *str);
void *strtoa(char *data, type dtype, int size);

/*----- Funções de leitura. -----*/

// Lê uma linha (ignora !isLine(c) antes de ler).
char *readLine(FILE *fp);

// Lê uma palavra (ignora !isWord(c) antes de ler).
char *readWord(FILE *fp);

// Lê um inteir (ignora !isPartOfNumber(c) antes de ler).
char *readInt(FILE *fp);

// Lê um número de ponto flutuante do arquivo (pode ser de qualquer tamanho, ex.: float, double, etc).
char *readFloat(FILE *fp);

// Lê enquanto nenhuma caracter dentro de char *stop seja encontrada.
char *readUntil(char *stop, FILE *fp);

// Ignora qualquer caractere dentro de ignore_prefix antes de ler,
// lê até que alguma caractere dentro de stop seja encontrada.
char *readBetween(char *ignore_prefix, char *stop, FILE *fp);
// Usa readOnce no prefixo, lê algumas caracteres contidas em char *some e depois
// usa readOnce no sufixo. Caso o prefixo ou sufixo não tenham sido lidos exatamente
// como char *prefix e char *postfix, retorna "". Caso contrário retorna o que foi lido no meio.
char *readSomeBetween(char *prefix, char *some, char *postfix, FILE *fp);
// Lê caracteres enquanto as caracteres lidas estiverem contidas em char *chars.
// Retorna todas as caracteres lidas.
char *readSome(char *chars, FILE *fp);
// Lê do arquivo exatamente o número de caracteres em comum com char *chars.
// Se a leitura conter exatamente essa sequência, nada a menos, retorna essas
// caracteres lidas, senão, devolve todas as caracteres que a função tentou ler
// com ungetc() (não anda com o ponteiro de arquivo para trás), e retorna "".
char *readOnce(char *chars, FILE *fp);
// Libera a memória alocada em char *str.
void ignore(char *str);
// Devolve todas as caracteres em char *str para a fila de leitur com ungetc().
void unread (char *str, FILE *fp);

/*----- Manipulação de erros. -----*/

// Se sertifica que str1 == srt2, se não forem iguais, sai do programa
// e imprime msg.
void assert_str(char *str1, char *str2, char *msg);

#endif
