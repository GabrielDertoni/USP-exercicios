#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "test_utils.h"
#include <colors.h>
#include <generic.h>
#include <json_model.h>

#define END_FLAG "__END_JSON__"

bool test_json_parse_model() {
    #pragma pack(1)
    struct nested_nested {
        char *inner_inner;
        double other_key;
    };

    #pragma pack(1)
    struct nested {
        struct nested_nested inner_key;
    };

    #pragma pack(1)
    struct json_num_arr {
        double *vec;
        int size;
    };

    #pragma pack(1)
    struct obj {
        double number_here;
        double huge_number;
        struct nested nested_obj;
        struct json_num_arr arrays;
    };

    char *test;
    char *endptr;
    struct obj data;

    generic_struct_t *gen = GEN_STRUCT(4,
       GEN_SFIELD("number_here", GEN_DOUBLE),
       GEN_SFIELD("huge_number", GEN_DOUBLE),
       GEN_SFIELD("nested_obj" , GEN_STRUCT(1,
         GEN_SFIELD("inner_key", GEN_STRUCT(2,
            GEN_SFIELD("inner_inner", GEN_STRING),
            GEN_SFIELD("other_key"  , GEN_DOUBLE)
         ))
       )),
       GEN_SFIELD("arrays!"    , GEN_STRUCT(2,
         GEN_SFIELD("vec", GEN_POINTER(GEN_DOUBLE)),
         GEN_SFIELD("size", GEN_INT)
       ))
    );

    test = "{\n"
    "\t\"number_here\": 17,\n"
    "\t\"huge_number\": 29147124124014,\n"
    "\t\"nested_obj\": {\"inner_key\": {\"inner_inner\": \"value\", \"other_key\": 69}},\n"
    "\t\"arrays!\": [1,2,3,4,5],\n"
    "}" END_FLAG;

    assert_eq(json_parse_model(test, &endptr, &data, gen, PARSE_EXACTLY), PARSER_SUCCESS);

    assert_eq(data.number_here, 17);
    assert_eq(data.huge_number, 29147124124014);
    assert_eq(strcmp(data.nested_obj.inner_key.inner_inner, "value"), 0);
    assert_eq(data.nested_obj.inner_key.other_key, 69);
    assert_eq(data.arrays.size, 5);

    double *vec = (double *)data.arrays.vec;
    assert_eq(vec[0], 1);
    assert_eq(vec[1], 2);
    assert_eq(vec[2], 3);
    assert_eq(vec[3], 4);
    assert_eq(vec[4], 5);
    gfree(&data, gen);

    generic_free(gen);

    return true;
}

bool test_json_parse_model_counting() {
    char *test;
    char *endptr;
    
    test = "{ \
        \"lat\": \"-37.3159\", \
        \"lng\": \"81.1496\" \
    }" END_FLAG;
    assert_eq(json_parse_model(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    test = "{ \
    \"id\": 1, \
    \"name\": \"Leanne Graham\", \
    \"username\": \"Bret\", \
    \"email\": \"Sincere@april.biz\", \
    \"address\": { \
        \"street\": \"Kulas Light\", \
        \"suite\": \"Apt. 556\", \
        \"city\": \"Gwenborough\", \
        \"zipcode\": \"92998-3874\", \
        \"geo\": { \
            \"lat\": \"-37.3159\", \
            \"lng\": \"81.1496\" \
        } \
    }, \
    \"phone\": \"1-770-736-8031 x56442\", \
    \"website\": \"hildegard.org\", \
    \"company\": { \
        \"name\": \"Romaguera-Crona\", \
        \"catchPhrase\": \"Multi-layered client-server neural-net\", \
            \"bs\": \"harness real-time e-markets\" \
        } \
    }" END_FLAG;
    assert_eq(json_parse_model(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    return true;
}

bool test_json_parse_model_object() {
    #pragma pack(1)
    struct my_json {
        double a_num;
        char *a_str;
        bool a_bool;
        double *a_num_ptr;
    };

    char *test;
    char *endptr;
    struct my_json json;

    generic_t *my_gen = GEN_STRUCT(4,
        GEN_SFIELD("a_num", GEN_DOUBLE),
        GEN_SFIELD("a_str", GEN_STRING),
        GEN_SFIELD("a_bool", GEN_BOOL),
        GEN_SFIELD("a_num_ptr", GEN_POINTER(GEN_DOUBLE))
    );

    test = "{ }" END_FLAG;
    assert_eq(json_parse_model_object(test, &endptr, &json, my_gen, PARSE_AT_MOST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(json.a_str, NULL);
    assert_eq(json.a_num_ptr, NULL);
    gfree(&json, my_gen);

    assert_eq(json_parse_model_object(test, &endptr, &json, my_gen, PARSE_AT_LEAST), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "{ \"a_num\": 1234, \"a_str\": \"hello\", \"a_bool\": false, \"a_num_ptr\": 5678 }" END_FLAG;
    assert_eq(json_parse_model_object(test, &endptr, &json, my_gen, PARSE_EXACTLY), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(json.a_num, 1234);
    assert_eq(strcmp(json.a_str, "hello"), 0);
    assert_eq(json.a_bool, false);
    assert_neq(json.a_num_ptr, NULL);
    assert_eq(*json.a_num_ptr, 5678);
    gfree(&json, my_gen);

    generic_free(my_gen);

    return true;
}

// TODO: Add feature where a static array could be used only with the PARSE_AT_MOST flag.
bool test_json_parse_model_array() {
    struct json_num_arr {
        double *vec;
        int size;
    };
    struct json_str_arr {
        char **strings;
        int size;
    };

    char *test;
    char *endptr;
    struct json_num_arr num_arr;
    struct json_str_arr str_arr;

    generic_t *num_gen = GEN_STRUCT(2,
        GEN_SFIELD("vec", GEN_POINTER(GEN_DOUBLE)),
        GEN_SFIELD("size", GEN_INT)
    );

    generic_t *str_gen = GEN_STRUCT(2,
        GEN_SFIELD("strings", GEN_POINTER(GEN_STRING)),
        GEN_SFIELD("size", GEN_INT)
    );

    test = "[1, 2,   3  , 4, 5, 1, 7.8, 0]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, &num_arr, num_gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(num_arr.vec[0], 1  );
    assert_eq(num_arr.vec[1], 2  );
    assert_eq(num_arr.vec[2], 3  );
    assert_eq(num_arr.vec[3], 4  );
    assert_eq(num_arr.vec[4], 5  );
    assert_eq(num_arr.vec[5], 1  );
    assert_eq(num_arr.vec[6], 7.8);
    assert_eq(num_arr.vec[7], 0  );
    gfree(&num_arr, num_gen);

    // Only a single type is allowed inside array using json_parse_model_array.
    test = "[1, 2,   \"hello\"  , 4, 5, 1, 7.8, 0]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, &num_arr, num_gen, PARSE_AT_LEAST), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "[\"hello\", \"world\"]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, &num_arr, num_gen, PARSE_AT_LEAST), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "[1, 2,   3, 4, 5, 1, 7.8, 0]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    test = "[1, 2,   3, 4, 5, 1, 7.8, 0]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, NULL, NULL, PARSE_EXACTLY), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "[\"hello\", \"world\"]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, &str_arr, str_gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(strcmp(str_arr.strings[0], "hello"), 0);
    assert_eq(strcmp(str_arr.strings[1], "world"), 0);

    for (int i = 0; i < str_arr.size; i++)
        free(str_arr.strings[i]);

    gfree(&str_arr, str_gen);

    test = "[1, 2,   3, 4, 5, 1, 7.8, 0]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, &str_arr, str_gen, PARSE_EXACTLY), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "[\"hello\", \"world\"]" END_FLAG;
    assert_eq(json_parse_model_array(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    generic_free(num_gen);
    generic_free(str_gen);

    return true;
}

bool test_json_parse_model_string() {
    char *test;
    char *endptr;
    char *str;
    generic_t *gen = GEN_STRING;

    test = "\"Hello World\"" END_FLAG;
    assert_eq(json_parse_model_string(test, &endptr, &str, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(strcmp(str, "Hello World"), 0);
    gfree(&str, gen);

    test = "\"Incomplete quotes" END_FLAG;
    assert_eq(json_parse_model_string(test, &endptr, &str, gen, PARSE_AT_LEAST), PARSER_FAIL);

    test = "\"Correct escaping \\\"in quotes\\\"\"" END_FLAG;
    assert_eq(json_parse_model_string(test, &endptr, &str, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(strcmp(str, "Correct escaping \\\"in quotes\\\""), 0);
    gfree(&str, gen);

    test = "\"Parsing only at least\"" END_FLAG;
    assert_eq(json_parse_model_string(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    test = "\"Parsing exactly\"" END_FLAG;
    assert_eq(json_parse_model_string(test, &endptr, NULL, NULL, PARSE_EXACTLY), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    generic_free(gen);

    return true;
}

bool test_json_parse_model_number() {
    char *test;
    char *endptr;
    double num;
    generic_t *gen = GEN_DOUBLE;

    test = "1234" END_FLAG;
    assert_eq(json_parse_model_number(test, &endptr, &num, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(num, 1234);

    test = "0.56789" END_FLAG;
    assert_eq(json_parse_model_number(test, &endptr, &num, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(num, 0.56789);

    test = "1.45e-3" END_FLAG;
    assert_eq(json_parse_model_number(test, &endptr, &num, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(num, 0.00145);

    test = "hello" END_FLAG;
    assert_eq(json_parse_model_number(test, &endptr, &num, gen, PARSE_AT_LEAST), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "1234" END_FLAG;
    assert_eq(json_parse_model_number(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    test = "1234" END_FLAG;
    assert_eq(json_parse_model_number(test, &endptr, NULL, NULL, PARSE_EXACTLY), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    generic_free(gen);

    return true;
}

bool test_json_parse_model_bool() {
    char *test;
    char *endptr;
    bool boolean;
    generic_t *gen = GEN_BOOL;

    test = "true" END_FLAG;
    assert_eq(json_parse_model_bool(test, &endptr, &boolean, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(boolean, true);

    test = "true" END_FLAG;
    assert_eq(json_parse_model_bool(test, &endptr, &boolean, gen, PARSE_EXACTLY), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(boolean, true);

    test = "false" END_FLAG;
    assert_eq(json_parse_model_bool(test, &endptr, &boolean, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(boolean, false);

    test = "tru" END_FLAG;
    assert_eq(json_parse_model_bool(test, &endptr, &boolean, gen, PARSE_AT_LEAST), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "false" END_FLAG;
    assert_eq(json_parse_model_bool(test, &endptr, NULL, NULL, PARSE_EXACTLY), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "false" END_FLAG;
    assert_eq(json_parse_model_bool(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    generic_free(gen);

    return true;
}

bool test_json_parse_model_null() {
    char *test;
    char *endptr;
    double *arbitrary_ptr = (double *)0x1234;
    generic_t *gen = GEN_POINTER(GEN_DOUBLE);

    test = "null" END_FLAG;
    assert_eq(json_parse_model_null(test, &endptr, &arbitrary_ptr, gen, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);
    assert_eq(arbitrary_ptr, NULL);

    test = "nu" END_FLAG;
    assert_eq(json_parse_model_null(test, &endptr, &arbitrary_ptr, gen, PARSE_AT_LEAST), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "nu" END_FLAG;
    assert_eq(json_parse_model_null(test, &endptr, NULL, NULL, PARSE_EXACTLY), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    test = "null" END_FLAG;
    assert_eq(json_parse_model_null(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    generic_free(gen);

    return true;
}

bool test_json_parse_model_undefined() {
    char *test;
    char *endptr;

    test = "undefined" END_FLAG;
    assert_eq(json_parse_model_undefined(test, &endptr, NULL, NULL, PARSE_AT_LEAST), PARSER_SUCCESS);
    assert_eq(strcmp(endptr, END_FLAG), 0);

    test = "undefied" END_FLAG;
    assert_eq(json_parse_model_undefined(test, &endptr, NULL, NULL, PARSE_EXACTLY), PARSER_FAIL);
    assert_eq(strcmp(endptr, test), 0);

    return true;
}

int main() {
    TEST_SETUP();

    test_fn(test_json_parse_model_undefined());
    test_fn(test_json_parse_model_null());
    test_fn(test_json_parse_model_bool());
    test_fn(test_json_parse_model_number());
    test_fn(test_json_parse_model_string());
    test_fn(test_json_parse_model_array());
    test_fn(test_json_parse_model_object());
    test_fn(test_json_parse_model_counting());
    test_fn(test_json_parse_model());

    TEST_TEARDOWN();
    return EXIT_SUCCESS;
}
