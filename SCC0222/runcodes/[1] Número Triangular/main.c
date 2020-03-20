#include <stdio.h>
#include <math.h>

int main() {
	int num;
	scanf("%d", &num);

	int triangular = 1; // Armazena um número triangular.
	int i = 2;
	for (; triangular < num; i++) {
		triangular += i;
	}
	if (triangular == num) {
		printf("SIM\n");

		// Calcula e imprime o próximo número triangular.
		int next_triangular = triangular + i;
		printf("%d\n", next_triangular);

		// Verifica se a soma do próximo número triangular com o número
		// fornecido na entrada é quadrado (se sua raiz quadrada é inteira).
		double sum = num + next_triangular;
		if (sqrt(sum) == floor(sqrt(sum)))
			printf("SIM");
		else
			printf("NAO");
	} else
		printf("NAO");

	return 0;
}
