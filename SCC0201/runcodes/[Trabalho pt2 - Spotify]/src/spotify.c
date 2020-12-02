#include <stdlib.h>
#include <math.h>
#include <csv.h>
#include <spotify.h>

double spotify_euclidean_distance(track_t *a, track_t *b) {
    return sqrt((a->acousticness     - b->acousticness    ) * (a->acousticness     - b->acousticness    ) +
                (a->danceability     - b->danceability    ) * (a->danceability     - b->danceability    ) +
                (a->energy           - b->energy          ) * (a->energy           - b->energy          ) +
                (a->instrumentalness - b->instrumentalness) * (a->instrumentalness - b->instrumentalness) +
                (a->liveness         - b->liveness        ) * (a->liveness         - b->liveness        ) +
                (a->loudness         - b->loudness        ) * (a->loudness         - b->loudness        ) +
                (a->speechiness      - b->speechiness     ) * (a->speechiness      - b->speechiness     ) +
                (a->tempo            - b->tempo           ) * (a->tempo            - b->tempo           ) +
                (a->time_signature   - b->time_signature  ) * (a->time_signature   - b->time_signature  ));
}

spotify_data_t *spotify_load_csv(char *fname) {
    csv_t *csv = csv_model(track_t);

    // Espelha o struct track_t no csv para poder carregar os dados diretamente
    // no tipo track_t. Dessa forma, cada linha do CSV já fica armazenado como um
    // track_t.
    csv_add_column(csv, "track_name"      , TYPE_STRING);
    csv_add_column(csv, "track_id"        , TYPE_STRING);
    csv_add_column(csv, "album_name"      , TYPE_STRING);
    csv_add_column(csv, "album_id"        , TYPE_STRING);
    csv_add_column(csv, "artist_name"     , TYPE_STRING);
    csv_add_column(csv, "artist_id"       , TYPE_STRING);
    csv_add_column(csv, "release_date"    , TYPE_STRING);
    csv_add_column(csv, "length"          , TYPE_INTEGER);
    csv_add_column(csv, "popularity"      , TYPE_INTEGER);
    csv_add_column(csv, "acousticness"    , TYPE_DOUBLE);
    csv_add_column(csv, "danceability"    , TYPE_DOUBLE);
    csv_add_column(csv, "energy"          , TYPE_DOUBLE);
    csv_add_column(csv, "instrumentalness", TYPE_DOUBLE);
    csv_add_column(csv, "liveness"        , TYPE_DOUBLE);
    csv_add_column(csv, "loudness"        , TYPE_DOUBLE);
    csv_add_column(csv, "speechiness"     , TYPE_DOUBLE);
    csv_add_column(csv, "tempo"           , TYPE_DOUBLE);
    csv_add_column(csv, "time_signature"  , TYPE_INTEGER);

    csv_load(csv, fname);

    return csv;
}

track_t **spotify_get_tracks(spotify_data_t *data) {
    return (track_t **)csv_get_values(data);
}

uint spotify_get_size(spotify_data_t *data) {
    return csv_get_rows(data);
}

void spotify_data_destroy(spotify_data_t *data) {
    csv_destroy(data);
}
