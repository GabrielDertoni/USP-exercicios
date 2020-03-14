#include <stdio.h>
#include <math.h>

int main() {
	int n;
	scanf("%d", &n);

	// Se a quantidade de pontos for muito pequena, impossibilitando
	// o cálculo da distância, imprime 0.
	if (n <= 1) {
		printf("0.0000");
		return 0;
	}

	// pxs armazena todas as coordenadas x dos pontos
	// pys armazena todas as coordenadas y dos pontos
	double pxs[n], pys[n];
	double dist = 0; // Armazena a soma das distâncias.
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", pxs+i, pys+i);

		if (i > 0) {
			double dx = pxs[i] - pxs[i - 1];
			double dy = pys[i] - pys[i - 1];
			dist += sqrt(pow(dx, 2) + pow(dy, 2));
		}
	}
	printf("%.4f", dist);

	return 0;
}
