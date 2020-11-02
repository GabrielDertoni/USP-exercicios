#include <stdio.h>
#include <stdlib.h>
#include <pgm.h>

void pgm_write(char *fname, byte **mat, int width, int height) {
    FILE *fp = fopen(fname, "w");

    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "255\n");
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++)
            fprintf(fp, "%3u ", mat[i][j]);

        fprintf(fp, "\n");
    }
    fclose(fp);
}
