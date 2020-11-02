#include <stdio.h>
#include <stdlib.h>
#include <pgm.h>

void rec_func(byte p, int x, int y, byte **mat, int n, int t) {
    if (x < 0 || x >= n || y < 0 || y >= n) return;
    byte v = mat[x][y];
    if (p != v && abs(p - v) <= t) {
        mat[x][y] = p;
        rec_func(p, x + 1, y, mat, n, t);
        rec_func(p, x - 1, y, mat, n, t);
        rec_func(p, x, y + 1, mat, n, t);
        rec_func(p, x, y - 1, mat, n, t);
    }
}

void rec_func_wrapper(int x, int y, byte **mat, int n, int t) {
    rec_func(mat[x][y], x + 1, y, mat, n, t);
    rec_func(mat[x][y], x - 1, y, mat, n, t);
    rec_func(mat[x][y], x, y + 1, mat, n, t);
    rec_func(mat[x][y], x, y - 1, mat, n, t);
}

int main(int argc, char *argv[]) {
    int n, x, y, t;
    byte **matrix;

    scanf(" %d %d %d %d", &n, &x, &y, &t);

    srand(t);
    matrix = (byte **)malloc(n * sizeof(byte *));

    for (int i = 0; i < n; i++) {
        matrix[i] = (byte *)malloc(n * sizeof(byte));
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() % 256;
    }

    #ifdef DEBUG
        pgm_write("input.pgm", matrix, n, n);
    #else
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%u\t", (unsigned char)matrix[i][j]);
            printf("\n");
        }
        printf("\n");
    #endif

    rec_func_wrapper(x, y, matrix, n, t);

    #ifndef DEBUG
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%u\t", (unsigned char)matrix[i][j]);
            printf("\n");
        }
    #else
        pgm_write("output.pgm", matrix, n, n);
    #endif

    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);

    return EXIT_SUCCESS;
}

