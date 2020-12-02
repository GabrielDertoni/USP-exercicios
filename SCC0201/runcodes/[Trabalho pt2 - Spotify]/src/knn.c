#include <stdlib.h>
#include <math.h>
#include <utils.h>
#include <spotify.h>
#include <knn.h>

#define KEY_MULTIPLYER 100000

// NOTE: Isso gera uma matriz no qual uma metada é igual a outra visto que
// dist(a, b) = dist(b, a). Isso indica que existe a possibilidade de uma
// outra implementação mais otimizada que utiliza apenas metade do espaço.
double **calculate_distance_matrix(track_t **tracks, int n_tracks) {
    double **mat = (double **)malloc(n_tracks * sizeof(double *));

    for (int i = 0; i < n_tracks; i++) {
        mat[i] = (double *)malloc(n_tracks * sizeof(double *));

        for (int j = 0; j < n_tracks; j++)
            if (i > j)
                mat[i][j] = mat[j][i];
            else if (i == j)
                mat[i][j] = 0;
            else
                mat[i][j] = spotify_euclidean_distance(tracks[i], tracks[j]);
    }

    return mat;
}

void free_distance_matrix(double **mat, int n_tracks) {
    for (int i = 0; i < n_tracks; i++)
        free(mat[i]);

    free(mat);
}

static uint get_indexed_double_key(void *el, void *arg) {
    double *distances = (double *)arg;
    double val = distances[*(uint *)el];
    return (uint)(val * KEY_MULTIPLYER);
}

uint *sort_indices(double *values, int size) {
    uint *sorted = (uint *)malloc(size * sizeof(uint));
    for (int i = 0; i < size; i++)
        sorted[i] = i;

    radix256_sort_with((void *)sorted, size, sizeof(uint),
                       get_indexed_double_key, values);
    return sorted;
}
