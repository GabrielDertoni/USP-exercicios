#include <stdio.h>

int main(int argc, char *argv[]) {
	char c;
	int num;

	c = getc(stdin);
	for (num = 0; c != '\n' && c != '\r' && c != '\0'; c = getc(stdin)) {
		num = num << 1; // Desloca todos os bits uma casa para a esquerda.
		num += c - 48; // Adiciona (no último bit) um 0 ou 1, dependendo da entrada.
	}

	printf("%d", num); // Imprime na tela o número fornecido na entrada só que em decimal.

	return 0;
}
