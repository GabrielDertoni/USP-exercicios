#include <stdio.h>
#include <stdlib.h>
#include <args.h>


int gen_random(int min, int max) {
    return min + rand() % (max - min);
}

void print_usage_exit() {
    printf("USAGE: ./numgen NUMBER [-r MIN MAX] [-s SEPARATOR]\n");
    printf("NUMBER:      \tThe number of random numbers to generate.\n");
    printf("-r MIN MAX:  \tThe minimum and maximum numbers for the generator.\n");
    printf("-s SEPARATOR:\tThe separator that will be between the numbers.\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    int n, min = 0, max = RAND_MAX;
    char *separator = " ";
    int argpos;

    if (argc < 2) print_usage_exit();

    n = atoi(argv[1]);
    if ((argpos = find_arg("-r", argc, argv)) > 0 && argpos + 2 < argc) {
        min = atoi(argv[argpos + 1]);
        max = atoi(argv[argpos + 2]);
    }

    if ((argpos = find_arg("-s", argc, argv)) > 0 && argpos + 1 < argc)
        separator = argv[argpos + 1];

    for (int i = 0; i < n; i++)
        printf("%d%s", gen_random(min, max), i != n - 1 ? separator : "");
    printf("\n");

    return EXIT_SUCCESS;
}
