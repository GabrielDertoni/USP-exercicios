#include <stdio.h>

int main() {
	int n, i, j;
	int c, count; // Variáveis que contam o número naturais
	              // iterados e de múltiplos impressos.

	// Lê variáveis da entrada padrão.
	scanf("%d %d %d", &n, &i, &j);

	// Itera por todos os naturais, até que suficientes números
	// múltiplos tenham side encontrados.
	for (c = 0, count = 0; count < n; c++)
		if (c % i == 0 || c % j == 0) {
			printf("%d\n", c);
			count++;
		}

	return 0;
}
