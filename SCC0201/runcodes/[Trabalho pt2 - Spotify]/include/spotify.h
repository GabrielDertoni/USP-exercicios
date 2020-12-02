/**
 * Módulo Spotify
 *
 * Esse módulo é específico para os dados fornecidos pela API do spotify em formato
 * CSV. Sendo assim, ele define tipos de dados que espelham essa API. Para isso
 * o módulo utiliza o csv.h que é genérico para todo CSV.
 */

#ifndef __SPOTIFY_H__
#define __SPOTIFY_H__

#include <csv.h>

// Espelhamento dos dados de uma única música.
typedef struct {
    char *name;
    char *id;
    char *album_name;
    char *album_id;
    char *artist_name;
    char *artist_id;
    char *release_date;
    int length;
    int popularity;
    double acousticness;
    double danceability;
    double energy;
    double instrumentalness;
    double liveness;
    double loudness;
    double speechiness;
    double tempo;
    int time_signature;
} track_t;

// Disponibiliza o tipo spotify_data_t como um handle em torno do tipo csv_t mas
// que restringe acesso a funcionalidades desnecessárias nesse contexto.
typedef csv_t spotify_data_t;

// Calcula a distância euclidiana entre duas músicas utilizando os 9 últimos
// atributos de track_t.
double spotify_euclidean_distance(track_t *a, track_t *b);

// Carrega os dados do CSV a partir de um arquivo e retorna o ponto de acesso.
spotify_data_t *spotify_load_csv(char *fname);

// Libera os dados alocados para o carregamento do CSV.
void spotify_data_destroy(spotify_data_t *data);

// Retorna todas as músicas contidas no dataset como um vetor de ponteiro às músicas.
track_t **spotify_get_tracks(spotify_data_t *data);

// Retorna a quantidade de músicas contidas no dataset.
uint spotify_get_size(spotify_data_t *data);

#endif
