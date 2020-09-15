#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <search.h>
#include <sort.h>

#define SEQ_SEARCH 1
#define BIN_IT_SEARCH 2
#define BIN_REC_SEARCH 3

#define MAX_PRINT 50

void printArr(int *arr, int n) {
    int j;
    printf("[ ");
    for (j = 0; j < MAX_PRINT && j < n; j++)
        printf("%d%s", arr[j], j == n-1 ? "" : (j == MAX_PRINT-1) ? "..." : ", ");

    printf(" ]\n");
}

int main(void) {
    int nreg, nsearch, type, key, *result;
    int *(*searchFunc)(int, int*, int*);

    if (!scanf("%d %d", &nreg, &nsearch)) {
        fprintf(stderr, "Error: Number of registers and number of searches needed.\n");
        exit(EXIT_FAILURE);
    }

    
    int *registers = (int *)malloc(nreg * sizeof(int));
    for (int i = 0; i < nreg && scanf(" %d", registers + i); i++);

    radixSort256(registers, registers + nreg);
    for (int i = 0; i < nsearch && scanf(" %d %d", &type, &key); i++) {
        #ifdef DEBUG
            int *seq = seqSearch(key, registers, registers + nreg);
            int *binIt = binItSearch(key, registers, registers + nreg);
            int *binRec = binRecSearch(key, registers, registers + nreg);
            // Pode falhar se houverem múltiplas ocorrências do mesmo número.
            assert(seq == binIt && seq == binRec);
        #endif

        switch (type) {
            case SEQ_SEARCH:
                searchFunc = seqSearch;
                break;
            
            case BIN_IT_SEARCH:
                searchFunc = binItSearch;
                break;

            case BIN_REC_SEARCH:
                searchFunc = binRecSearch;
                break;

            default:
                fprintf(stderr, "Error: Search option not available.\n");
                exit(EXIT_FAILURE);
        }
        result = searchFunc(key, registers, registers + nreg);
        printf("%d\n", result ? (int)(result - registers + 1) : -1);
    }
    free(registers);

    return EXIT_SUCCESS;
}
