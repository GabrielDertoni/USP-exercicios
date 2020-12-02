#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_utils.h"
#include <colors.h>
#include <parsing_utils.h>
#include <hashset.h>

bool test_hashset_insert() {
    hashset_t *hashset = hashset_create();
    assert_neq(hashset, NULL);

    int len_alphanum = strlen(ALPHANUM);
    for (int i = 0; i < 1000; i++) {
        char *key = (char *)malloc(100 * sizeof(char));
        for (int j = 0; j < 100; j++) key[j] = ALPHANUM[rand() % len_alphanum];

        assert_eq(hashset_insert(hashset, key), true);
        assert_eq(hashset_contains(hashset, key), true);
    }

    hashset_delete(hashset);
    return true;
}

bool test_hashset_contains() {
    hashset_t *hashset = hashset_create();
    assert_neq(hashset, NULL);

    assert_eq(hashset_insert(hashset, strdup("Hello World")), true);
    assert_eq(hashset_contains(hashset, "Hello World"), true);

    assert_eq(hashset_contains(hashset, "Some non existent key"), false);

    hashset_delete(hashset);
    return true;
}

bool test_hashset_create() {
    hashset_t *hashset = hashset_create();
    assert_neq(hashset, NULL);
    assert_eq(hashset_get_size(hashset), 0);

    hashset_delete(hashset);
    return true;
}

int main(int argc, char *argv[]) {
    TEST_SETUP();

    test_fn(test_hashset_create());
    test_fn(test_hashset_contains());

    TEST_TEARDOWN();
    return EXIT_SUCCESS;
}
