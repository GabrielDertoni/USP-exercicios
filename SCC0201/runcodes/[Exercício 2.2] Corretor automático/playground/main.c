#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <parsing_utils.h>
#include <json.h>

void interactive_json() {
    char *fjson = readline(stdin);
    json_value_t *json;
    if (json_parse_file(fjson, &json) != PARSER_SUCCESS) {
        fprintf(stderr, "Error while reading json file...\n");
        free(fjson);
        exit(1);
    }

    printf("SUCCESS!!!\n\n");

    char *line;
    while ((line = readline(stdin))) {
        char *ptr = line;
        if (!parse_string("json", &ptr)) {
            printf("No json object with this name was loaded\n");
            continue;
        }
        json_value_t *val = json_js_index(json, ptr);

        if (!val) {
            printf("value not contained in json structure\n");
        } else {
            printf("json%s = ", ptr);
            switch (val->type) {
                case JSON_OBJECT:
                    printf("(object)");
                    break;

                case JSON_ARRAY:
                    printf("(array)");
                    break;

                case JSON_STRING:
                    printf("%s", as_str(val)->content);
                    break;

                case JSON_NUMBER:
                    printf("%lf", as_num(val)->number);
                    break;

                case JSON_BOOL:
                    printf("%s", as_bool(val)->value ? "true" : "false");
                    break;

                case JSON_UNDEFINED:
                    printf("undefined");
                    break;

                case JSON_NULL:
                    printf("null");
                    break;
            }
            printf("\n");
        }
        free(line);
    }

    json_value_delete(json);
    free(fjson);

}

int main(void) {
    interactive_json();

    return 0;
}
