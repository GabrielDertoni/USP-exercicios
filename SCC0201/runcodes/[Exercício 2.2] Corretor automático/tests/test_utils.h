#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define CHECKPOINT ({ last_line = __LINE__; last_fname = __FILE__; })

#define assert_eq(a, b) ({ \
    CHECKPOINT; \
    if (a != b) { \
        fprintf(stderr, YELLOW "Expected " #a " to equal " #b ". (%s:%d)" RESET "\n", __FILE__, __LINE__); \
        return false; \
    } \
})

#define assert_neq(a, b) ({ \
    CHECKPOINT; \
    if (a == b) { \
        fprintf(stderr, YELLOW "Expected " #a " to differ from " #b ". (%s:%d)" RESET "\n", __FILE__, __LINE__); \
        return false; \
    } \
})

#define test_fn(func) ({ \
    CHECKPOINT; \
    if (!func) { \
        fprintf(stderr, RED "Test: " #func " failed." RESET "\n"); \
        TEST_TEARDOWN(); \
        exit(0); \
    } else \
        fprintf(stdout, GREEN "Test: " #func " succeeded." RESET "\n"); \
})

#define bench(func) ({ \
    clock_t __stime = clock(); \
    func; \
    printf(CYAN #func " took %lf milliseconds" RESET "\n", (double)(clock() - __stime) / (double)(CLOCKS_PER_SEC / 1000)); \
})

#define TEST_SETUP() ({ CHECKPOINT; test_setup(); })
#define TEST_TEARDOWN() ({ CHECKPOINT; test_teardown(); })

static int last_line = 0;
static char *last_fname = NULL;

void segfault_handler(int signal) {
    printf("Segfault incoming! Last checkpoint was at (%s:%d)\n",
           last_fname ? last_fname : "none", last_line);
    exit(signal);
}

void test_setup() {
    signal(SIGSEGV, segfault_handler);
    printf("\n---------- Testing: %s ----------\n", last_fname);
}

void test_teardown() {
    /* Nothing yet, but something could be placed here */
}

#endif
