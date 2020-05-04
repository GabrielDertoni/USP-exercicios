#include <stdio.h>
#include <stdlib.h>
#include "util.h"

// Implementação de Quick Sort geral para quaquer lista de ponteiros e qualquer função de
// comparação. Essa função de comparação deve receber os dois elementos a serem comparados como void *
// e retornar 1 caso a > b, -1 caso 1 a < b e 0 caso a = b. Start representa o índice de início para
// a ordenação da lista, e end o final.
void sortWith(void **list, int start, int end, int (*compare)(void *a, void *b)) {
	// Range (start]
	// compare -> 1: a > b, -1: a < b, 0: a = b
	if (abs(start - end) <= 1) return;

	void *pivot = list[start];
	int p1 = start + 1;
	int p2 = end;
	while(p1 != p2) {
		// If the pointer from the left side is bigger than the pivot and the pointer from
		// the right is smaller or equal to the pivot, swap them.
		if (compare(list[p1], pivot) == 1 && compare(list[p2], pivot) != 1) {
			void *temp = list[p1];
			list[p1] = list[p2];
			list[p2] = temp;
		}
		// Usa else if para garantir que ambos os índices não avancem ao mesmo tempo, o que
		// pularia a verificação de p1 == p2 em alguns casos.
		if (compare(list[p1], pivot) == -1) p1++;
		else if (compare(list[p2], pivot) == 1) p2--;
	}
	if (compare(list[p1], pivot) == 1) {
		void *temp = list[p1 - 1];
		list[p1 - 1] = pivot;
		list[start] = temp;
		sortWith(list, start, p1 - 1, compare);
		sortWith(list, p1, end, compare);
	} else {
		void *temp = list[p1];
		list[p1] = pivot;
		list[start] = temp;
		sortWith(list, start, p1, compare);
		sortWith(list, p1 + 1, end, compare);
	}
}
