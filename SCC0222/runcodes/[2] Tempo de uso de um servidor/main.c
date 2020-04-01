#include <stdio.h>

int main() {
	double val, max_val; // val: valor atual sendo lido.
	                     // max_val: maior valor encontrado.
	int i, max_index; // i: índice atual sendo lido.
	                  // max_index: índice do maior valor encontrado.

	// Itera por todos os meses e encontra o com maior valor.
	for (i = 0; i < 12; i++) {
		scanf("%lf", &val);
		if (i == 0) {
			max_val = val;
			max_index = i;
		} else if (max_val < val) {
			max_val = val;
			max_index = i;
		}
	}
	// Imprime o resultado da busca.
	printf("%d %.2lf", max_index + 1, max_val);


	return 0;
}
