#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <helpers.h>
#include <bubble.h>
#include <insertion.h>
#include <merge.h>

typedef enum { BUBBLE = 1, INSERTION, MERGE } sort_t;

void sortAlgorithmWith(sort_t algorithm, elem_t *start, elem_t *end, comp_t comp) {
    switch (algorithm) {
        case BUBBLE:
            bubbleSortWith(start, end, comp);
            break;
        
        case INSERTION:
            insertionSortWith(start, end, comp);
            break;
        
        case MERGE:
            mergeSortWith(start, end, comp);
            break;
        
        default:
            fprintf(stderr, "Código de algoritmo de ordenação não identificado.");
            exit(EXIT_FAILURE);
            break;
    }
}

char *toLower(char *string) {
    for (char *ptr = string; *ptr; ptr++)
        *ptr = lower(*ptr);
    return string;
}

int main(void) {
    char *line = readline(stdin);
    char *parsePtr = line;
    char *fname = strdup(strsep(&parsePtr, " "));
    sort_t algorithm = atoi(strsep(&parsePtr, "\r\n"));
    free(line);

    FILE *fp = fopen(fname, "r");
    char **words = NULL;
    size_t alloc = 0;
    int n;
    for (n = 0; (line = readline(fp)); n++) {
        words = maybeRealloc(words, n * sizeof(char *), &alloc);
        words[n] = toLower(line);
    }
    free(fname);
    fclose(fp);

    #ifdef MEASURE_TIME
        char **copy = (char **)malloc(n * sizeof(char *));
        clock_t start_time, time_avg;
        time_avg = 0;
        char *algoName = algorithm == BUBBLE ? "Bubble" : (algorithm == INSERTION ? "Insertion" : "Merge");
        printf("Running %s Sort\n", algoName);
        printf("[....................]\r[");
        fflush(stdout);
        for (int t = 0; t < 10; t++) {
            memcpy((void *)copy, words, n * sizeof(char *));
            start_time = clock();
            sortAlgorithmWith(algorithm, copy, copy + n, reverseStrCompare);
            time_avg += clock() - start_time;
            printf("==");
            fflush(stdout);
        }
        printf("\nTook %0.4lf\n", (double)time_avg / (10.0 * (double)CLOCKS_PER_SEC));
    #else
        sortAlgorithmWith(algorithm, words, words + n, reverseStrCompare);
    #endif

    for (int i = 0; i < n; i++) {
        #ifndef MEASURE_TIME
            printf("%s\n", words[i]);
        #endif
        free(words[i]);
    }
    free(words);

    return EXIT_SUCCESS;
}
