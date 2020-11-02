#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void funcao(double **mat, int m, int i) {
    if (i >= m) return;                             // c
    for (int j = 0; j < m; j++) {
        if (i > j) {                                // c
            mat[i][j]= (i+j)/2.0;                   // 2a
        } else if (i < j) {                         // c
            mat[i][j]= (i+j)/4.0;                   // 2a
        } else {
            double soma = 0.0;
            for (int a = 0; a < m; a++) {
                if (i-1 >= 0) soma+= mat[i-1][a];   // 3a + c
            }
            mat[i][j]= soma;
        }
    }
    funcao(mat, m, i + 1);                          // 2a + f(n - 1)
}

int main(void) {
    int m;
    scanf(" %d", &m);

    double **mat = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++)
        mat[i] = (double *)malloc(m * sizeof(double));

    clock_t start_time = clock();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i > j) {
                mat[i][j]= (i+j)/2.0;
            } else if (i < j) {
                mat[i][j]= (i+j)/4.0;
            } else {
                double soma = 0.0;
                for (int a = 0; a < m; a++) {
                    if (i-1 >= 0) soma+= mat[i-1][a];
                }
                mat[i][j]= soma;
            }
        }
    }
    printf("Took: %.17lfs\n", (double)(clock() - start_time) / (double)CLOCKS_PER_SEC);

    for (int i = 0; i < m; i++) {
        // printf("%.2lf ", mat[m - 1][i]);
        free(mat[i]);
    }
    printf("\n");
    free(mat);

    return EXIT_SUCCESS;
}