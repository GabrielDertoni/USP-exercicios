#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int n, m, x, y;
	float speed;
	scanf("%d %d %d %d %f", &n, &m, &x, &y, &speed);

	int base_x, base_y;
	for (int i = 0; i < n * m; i++) {
		int isBase;
		scanf("%d", &isBase);
		if (isBase) {
			base_x = i / m;
			base_y = i % m;
			// Poderia dar um break aqui, mas acho que poderia dar problema
			// já que algumas partes da entrada poderiam não serem consumidas.
		}
	}

	if (sqrt(pow((double)(base_x - x), 2) + pow((double)(base_y - y), 2)) <= speed)
		printf("Voce escapou!");
	else
		printf("Game Over!");
	
	
	return EXIT_SUCCESS;
}
