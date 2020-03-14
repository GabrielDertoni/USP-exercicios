#include <stdio.h>

int main() {
	int num;
	printf("Digite o número a ser convertido: ");
	scanf("%d", &num);

	char bin[sizeof(num) * 8 + 1]; // Tamanho de int (4) * 8 (número de bits por byte) + 1 (\0)
	for (int i = sizeof(num) * 8 - 1; i >= 0; i--, num /= 2) {
		bin[i] = 48 + num % 2; // Converte de inteiro para char ( + 48) ASCII
		// bin[i] = num % 2 == 0 ? '0' : '1';
	}
	bin[sizeof(num) * 8] = '\0'; // Adiociona \0 para denotar o final da string.

	printf("O número convertido para binário: %.8s %.8s %.8s %.8s\n", bin, &bin[8], &bin[16], &bin[24]);
	return 0;
}
