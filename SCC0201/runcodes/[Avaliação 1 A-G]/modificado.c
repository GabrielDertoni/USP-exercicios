#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int m;
    scanf(" %d", &m);

    double **mat = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++)
        mat[i] = (double *)malloc(m * sizeof(double));
    
    clock_t start_time = clock();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i > j)
                mat[i][j] = mat[j][i] * 2.0;

            else if (i < j)
                mat[i][j] = (i + j) / 4.0;
            
            else if (i == 0)
                mat[i][j] = 0;

            if (i < m - 1) {
                if (j == 0)
                    mat[i + 1][i + 1] = mat[i][j];
                else
                    mat[i + 1][i + 1] += mat[i][j];
            }
        }
    }
    printf("Took: %.17lfs\n", (double)(clock() - start_time) / (double)CLOCKS_PER_SEC);

    for (int i = 0; i < m; i++) {
        // printf("%.2f ", mat[m - 1][i]);
        free(mat[i]);
    }
    printf("\n");
    free(mat);

    return EXIT_SUCCESS;
}