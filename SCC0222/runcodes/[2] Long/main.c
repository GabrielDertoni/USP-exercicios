#include <stdio.h>

int main() {
	long int n; // Declara a variável que armazenará o número long.

	scanf("%ld", &n); // Lê o número da entrada.
	for (int i = 0; i < sizeof(long int); i++)
		// Desloca o byte de interesse para o primeiro e o isola com
		// um bitwise and com 0xff. Imprime o byte como hexadecimal.
		printf("%x\n", (unsigned int)(n >> (i * 8)) & 0xff);

	return 0;
}
