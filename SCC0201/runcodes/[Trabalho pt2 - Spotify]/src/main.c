#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <utils.h>
#include <spotify.h>
#include <knn.h>

// Usado para quicksort, compara os track_id dentro de cada track.
int compare_ids(void *a, void *b);

// Usado na busca binária, compara um id (char *) com o track_id de um track_t *.
int compare_id_with_track(void *a, void *b);

int main(void) {
    int q, k;
    char *fname;

    fname = readline(stdin);
    scanf(" %d %d", &q, &k);

    spotify_data_t *data = spotify_load_csv(fname);

    free(fname);

    int n_tracks = spotify_get_size(data);
    track_t **tracks = spotify_get_tracks(data);

    quick_sort_with((void *)tracks, n_tracks, sizeof(void *), compare_ids);

    double **distances = calculate_distance_matrix(tracks, n_tracks);

    for (int i = 0; i < q; i++) {
        char *id = readline(stdin);
        track_t **result = (track_t **)binary_search(id, tracks, n_tracks,
                                                     sizeof(track_t *),
                                                     compare_id_with_track);
        if (!result) {
            // Nunca deveria acontecer.
            printf("A musica consultada não esta contida no dataset!\n");
            continue;
        }
        uint index = result - tracks;
        uint *sorted = sort_indices(distances[index], n_tracks);

        printf("----As %d musicas mais parecidas com %s sao:\n", k, tracks[index]->name);
        for (int j = 0; j < k; j++){
            printf("\t(%d)Artista: %s\n", j, tracks[sorted[j]]->artist_name);
            printf("\t\tMusica: %s\n", tracks[sorted[j]]->name);
            printf("\t\tDissimilaridade: %lf\n", distances[index][sorted[j]]);
            printf("\t\tLink: https://open.spotify.com/track/%s\n", tracks[sorted[j]]->id);
        }
        printf("\n");
        free(sorted);
        free(id);
    }

    free_distance_matrix(distances, n_tracks);
    spotify_data_destroy(data);

    return EXIT_SUCCESS;
}

int compare_id_with_track(void *a, void *b) {
    char *id_a = (char *)a;
    char *id_b = (*(track_t **)b)->id;
    return strcmp(id_a, id_b);
}

int compare_ids(void *a, void *b) {
    char *id_a = (*(track_t **)a)->id;
    char *id_b = (*(track_t **)b)->id;
    return strcmp(id_a, id_b);
}
