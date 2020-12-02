#ifndef __PARSING_H__
#define __PARSING_H__

#include <stdlib.h>

typedef struct {
    char *ptr;
    size_t size;
} slice_t;

typedef struct {
    slice_t parsed;
    slice_t next;
} parse_result_t;

// Operações em slices.
slice_t subslice(const slice_t input, const int start, const int end);
char *slice_to_string(const slice_t input);

// Funções para criação de parse_result_t.
parse_result_t mk_result(const slice_t parsed, const slice_t next);
parse_result_t slice_to_parse(const slice_t slice);

// Funções para parsing. Toda função de formato parse_<leitura> tenta performar a 
// leitura na string parser_get_unconsumed(input)
parse_result_t parse_until(const char *stop, const parse_result_t input);
parse_result_t parse_string(const char *string, const parse_result_t input);
parse_result_t parse_some(const char *chars, const parse_result_t input);
parse_result_t parse_while(int (*precondition)(int), const parse_result_t input);
parse_result_t parse_split(const char *separators, const parse_result_t input);
parse_result_t parse_line(const parse_result_t input);
parse_result_t parse_inside(const parse_result_t input);

// Acesso aos valores do parser_result_t. Toda função de formato parser_get_<coisa>
// retorna <coisa> que é uma informação armazenada em input.
slice_t parse_get_value(const parse_result_t input);
slice_t parse_get_unconsumed(const parse_result_t input);
size_t unparsed_get_size(const parse_result_t input);
size_t parse_get_size(const parse_result_t input);

// Conversão de parser para algo. Toda função no formato parser_to_<tipo> tenta
// converter o valor de retorno de parser_get_value em <tipo>.
char *parse_to_string(const parse_result_t input);
int parse_to_int(const parse_result_t input);
float parse_to_float(const parse_result_t input);
double parse_to_double(const parse_result_t input);

#endif
