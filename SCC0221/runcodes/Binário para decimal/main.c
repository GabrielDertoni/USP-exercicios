#include <stdio.h>

int main(int argc, char *argv[]) {
	char bin[30]; // Define a cadeia de caracteres (string) que armazenará os digitos binários.
	int i, num;

	scanf("%s", bin); // Lê número binário como string.
	for (i = 0, num = 0; bin[i] != '\0'; i++) {
		num = num << 1; // Desloca todos os bits uma casa para a esquerda.
		num += bin[i] - 48; // Adiciona (no último bit) um 0 ou 1, dependendo da entrada.
	}

	printf("%d", num); // Imprime na tela o número fornecido na entrada só que em decimal.

	return 0;
}
