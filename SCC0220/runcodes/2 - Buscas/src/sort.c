#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void radixSort256(int *start, int *end) {
    int n = end - start;
    int *vec = start;
    int *output = (int *)malloc((end - start) * sizeof(int));
    int *count = (int *)malloc(256 * sizeof(int));
    for (int shift = 0; shift < 32; shift += 8) {
        // Zero the counts.
        for (int i = 0; i < 256; i++)
            count[i] = 0;

        // Counts
        for (int i = 0; i < n; i++)
            count[(vec[i] >> shift) & 0xff]++;

        // Prefix sum
        for (int i = 1; i < 256; i++)
            count[i] += count[i - 1];

        // Replacing
        for (int i = n - 1; i >= 0; i--)
            output[--count[(vec[i] >> shift) & 0xff]] = vec[i];

        int *tmp = vec;
        vec = output;
        output = tmp;
    }
    // One more operation required on the signal bit.
    count[0] = count[1] = 0; // Zeroing
    // Counts
    for (int i = 0; i < n; i++)
        count[~(vec[i] >> 31) & 1]++;

    count[1] += count[0]; // Prefix sum

    // Replacing
    for (int i = n - 1; i >= 0; i--)
        output[--count[~(vec[i] >> 31) & 1]] = vec[i];

    memcpy(vec, output, n * sizeof(int));

    free(output);
    free(count);
}
