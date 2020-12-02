#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <parsing.h>

struct _slice {
    char *ptr;
    size_t size;
};

slice_t subslice(const slice_t input, const int start, const int end) {
    int s = start, e = end;
    if (s < 0) s = input.size + s + 1;
    if (e < 0) e = input.size + e + 1;
    assert(e >= s);
    assert(s <= input.size);
    assert(e - s <= input.size);

    slice_t slice = {
        .ptr  = input.ptr + s,
        .size = e - s,
    };
    return slice;
}

char *slice_to_string(const slice_t input) {
    char *str = (char *)malloc((input.size + 1) * sizeof(char));
    memcpy(str, input.ptr, input.size);
    str[input.size] = '\0';
    return str;
}


parse_result_t mk_result(const slice_t parsed, const slice_t next) {
    parse_result_t result = {
        .parsed = parsed,
        .next   = next,
    };
    return result;
}
parse_result_t slice_split_to_parse(const slice_t slice, const size_t split) {
    return mk_result(subslice(slice, 0, split), subslice(slice, split, -1));
}

parse_result_t slice_to_parse(const slice_t slice) {
    return mk_result(subslice(slice, 0, 0), slice);
}

parse_result_t parse_until(const char *stop, const parse_result_t input) {
    slice_t next = input.next;
    int i;
    for (i = 0; i < next.size && !strchr(stop, next.ptr[i]); i++);
    return slice_split_to_parse(next, i);
}

parse_result_t parse_string(const char *string, const parse_result_t input) {
    slice_t next = input.next;
    int len = strlen(string), i;
    for (i = 0; i < next.size && i < len && next.ptr[i] == string[i]; i++);
    return slice_split_to_parse(next, i);
}

parse_result_t parse_some(const char *chars, const parse_result_t input) {
    slice_t next = input.next;
    int i;
    for (i = 0; i < next.size && strchr(chars, next.ptr[i]); i++);
    return slice_split_to_parse(next, i);
}

parse_result_t parse_while(int (*precondition)(int), const parse_result_t input) {
    slice_t next = input.next;
    int i;
    for (i = 0; i < next.size && precondition(next.ptr[i]); i++);
    return slice_split_to_parse(next, i);
}

parse_result_t parse_split(const char *separators, const parse_result_t input) {
    parse_result_t result = parse_until(separators, input);
    result.next = parse_some(separators, result).next;
    return result;
}

parse_result_t parse_line(const parse_result_t input) {
    parse_result_t result;
    result = parse_some("\r\n", input);
    result = parse_until("\r\n", result);
    return result;
}

parse_result_t parse_inside(const parse_result_t input) {
    return slice_to_parse(input.parsed);
}

slice_t parse_get_value(const parse_result_t input) {
    return input.parsed;
}

slice_t parse_get_unconsumed(const parse_result_t input) {
    return input.next;
}

size_t unparsed_get_size(const parse_result_t input) {
    return input.next.size;
}

size_t parse_get_size(const parse_result_t input) {
    return input.parsed.size;
}

char *parse_to_string(const parse_result_t input) {
    return slice_to_string(input.parsed);
}

int parse_to_int(const parse_result_t input) {
    int sign = 1, value = 0;
    size_t i;
    parse_result_t token;

    token = parse_while(isspace, parse_inside(input));
    token = parse_string("-", token);
    if (token.parsed.size == 1) sign = -1;
    else token = parse_string("+", token);

    token = parse_while(isdigit, token);
    
    for (i = 0; i < token.parsed.size && value < INT_MAX / 10; i++) {
        value *= 10;
        value += token.parsed.ptr[i] - '0';
    }
    return sign * value;
}

float parse_to_float(const parse_result_t input) {
    return (float)parse_to_double(input);
}

double parse_to_double(const parse_result_t input) {
    // Copies string data onto the stack (no need for heap allocation).
    char buff[input.parsed.size + 1];
    buff[input.parsed.size] = '\0';
    memcpy(buff, input.parsed.ptr, input.parsed.size * sizeof(char));

    double num = strtod(buff, NULL);

    return num;
}

