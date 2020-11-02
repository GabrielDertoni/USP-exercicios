#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int nunique = 0;
  int unique[100];
  int counts[100];

  while (!feof(stdin)) {
    int j, num;
    scanf("%d ", &num);
    for (j = 0; j < nunique && unique[j] != num; j++);
    if (j == nunique) {
      nunique++;
      unique[j] = num;
      counts[j] = 0;
    }
    counts[j]++;
  }

  for (int i = 0; i < nunique; i++) {
    printf("%d (%d)\n", unique[i], counts[i]);
  }

  return EXIT_SUCCESS;
}