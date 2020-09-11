#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <args.h>

#define time_fn(f, args...) ({ \
    clock_t start_time = clock(); \
    f(args); \
    clock_t end_time = clock(); \
    (end_time - start_time) / (double)CLOCKS_PER_SEC; \
})

// Vetor com elementos [start, end)
void bubble_sort(int *start, int *end) {
    int n = end - start;                    // 2a
    for (int i = n; i > 0; i--)             // 1. a + c 2... (n - 1)(c + 2a)
        for (int j = 0; j < i; j++)         // n(a + c) + n(n - 1)(c + 2a) / 2
            if (start[j + 1] < start[j]) {  // n(n + 1)(2p + a + c) / 2
                int tmp = start[j + 1];     // n(n + 1)(p + 2a) / 2
                start[j + 1] = start[j];    // n(n + 1)(p + 2a) / 2
                start[j] = tmp;             // n(n + 1)(p + a) / 2
            }
}
// somando:
// s(n) = 2a + (a + c) + (n - 1)(c + 2a) + n(a + c) + n(n - 1)(c + 2a) / 2 +
//        n(n + 1)(2p + a + c) / 2 + n(n + 1)(p + 2a) / 2 + n(n + 1)(p + 2a) / 2 +
//        n(n + 1)(p + a) / 2
// simplificando:
// s(n) = 4an^2 + cn^2 + (5/2)pn^2 + 5an + 2cn + (5/2)pn + a
//
// s(n) = a + 2nc + 2na + n^2(c)/2 + n^2(a) - nc/2 + n^2(p) + n^2(a)/2 + n^2(c)/2 +
//        np + na/2 + nc/2 + n^2(p)/2 + n^2(a) + np/2 + na + n^2(p)/2 + n^2(a) +
//        np/2 + na + n^2(p)/2 + n^2(a)/2 + np/2 + na/2
// s(n) = a + 2nc + 5na + n^2(c) + 4n^2(a) + 2n^2(p) + n^2(p)/2 +
//        2np + np/2
// s(n) = 4an^2 + cn^2 + (5/2)pn^2 + 5an + 2cn + (5/2)pn + a

// Vetor com elementos [start, end)
void reverse(int *start, int *end) {
    while (end > start) {           // nc/2
        int tmp = *start;           // n(p + a)/2
        *(start++) = *(--end);      // n(2p + 4a)/2
        *end = tmp;                 // n(p + a)/2
    }
}
// somando:
// r(n) = nc/2 + n(p + a) / 2 + n(2p + 4a) / 2 + n(p + a) / 2
// simplificando:
// r(n) = (nc + 4np + 6na) / 2
//
// r(n) = nc/2 + np/2 + na/2 + 2np/2 + 4na/2 + np/2 + na/2
// r(n) = (nc + np + na + 2np + 4na + np + na) / 2
// r(n) = (nc + 4np + 6na) / 2

void print_usage_exit() {
        printf("Usage: algostat ALGORITHM -n NUMBER [-o]\n");
        printf("ALGORITHM:\tOne of reverse or sort.\n");
        printf("-n NUMBER:\tThe number of inputs to read from stdin.\n");
        printf("-o, --out:\tPrint outputs to stdout.\n");
        exit(EXIT_SUCCESS);
}

void print_time(double time) {
    printf("Took: %.17lf seconds\n", time);
}

void print_vec(int *vec, int n) {
    for (int i = 0; i < n; i++) printf("%d ", vec[i]);
    printf("\n");
}

int *read_inputs(int n) {
    int *inputs = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf(" %d", inputs + i);
    return inputs;
}

int main(int argc, char *argv[]) {
    int n;
    int *inputs;
    double time;
    bool pout = false;
    int argpos;

    // Arguments handling
    if (argc < 4) print_usage_exit();

    if (find_arg("-h", argc, argv) > 0 || find_arg("--help", argc, argv) > 0)
        print_usage_exit();

    argpos = find_arg("-n", argc, argv);
    if (argpos < 0 || (n = atoi(argv[argpos + 1])) <= 0)
        print_usage_exit();

    if (find_arg("-o", argc, argv) > 0 || find_arg("--out", argc, argv) > 0)
        pout = true;

    inputs = read_inputs(n);
    if (find_arg("reverse", argc, argv) > 0)
        time = time_fn(reverse, inputs, inputs + n);
    else if (find_arg("sort", argc, argv) > 0)
        time = time_fn(bubble_sort, inputs, inputs + n);
    else print_usage_exit();

    if (pout) print_vec(inputs, n);

    print_time(time);
    free(inputs);

    return EXIT_SUCCESS;
}
