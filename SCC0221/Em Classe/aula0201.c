#include <stdio.h>

// Returns the number multiplyed by itself power times.
int pow(int num, int power) {
	int result = 1;
	for (int i = 0; i < power; i++) {
		result = result * num; 
	}
	return result;
}

int main() {
	int num;
	printf("Digite o número a ser convertido: ");
	scanf("%d", &num);

	int bin = 0;
	int frac = num;
	int count = 0;
	do {
		bin += pow(10, count) * (frac % 2);
		frac = frac / 2;
		count++;
	} while (frac != 0);
	printf("O número convertido para binário: %d\n", bin);

	return 0;
}
