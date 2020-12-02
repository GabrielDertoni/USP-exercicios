/**
 * Módulo K-Nearst Neighbours.
 *
 * Esse não se trata de um módulo generalizado, mas específico para esta aplicação.
 * Dessa forma, ele utiliza do módulo spotify e funciona especificamente com os
 * tipos de dados disponibilizados pelo spotify.
 */

#ifndef __KNN_H__
#define __KNN_H__

#include <spotify.h>

/**
 * Calcula a matriz de dissimilaridade entre as músicas.
 *
 * @param tracks - o vetor de ponteiros de track_t (vetor de músicas).
 * @param n_tracks - número de músicas no vetor.
 * @return a matriz de dissimilaridade.
 */
double **calculate_distance_matrix(track_t **tracks, int n_tracks);

/**
 * Libera uma matriz quadrada de doubles de ordem n_tracks.
 *
 * @param mat - a matriz a ser liberada.
 * @param n_tracks - a ordem da matriz.
 */
void free_distance_matrix(double **mat, int n_tracks);

/**
 * Gera um vetor de índices ordenados de acordo com determinados valroes. Se
 * vec = sort_indices(values, size) então values[vec[0]] é o menor dos valoes
 * contidos em "values".
 *
 * @param values - vetor de valores utilizados para comparações.
 * @param size - tamanho do vetor de valoes.
 * @return um vetor de tamanho "size" de tal forma q values[vec[i]] é o i-ésimo
 *         valor de values numa ordenação crescente.
 */
uint *sort_indices(double *values, int size);

#endif
