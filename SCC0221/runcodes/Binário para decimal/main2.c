#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char bin[30]; // Define a cadeia de caracteres (string) que armazenará os digitos binários.
	int i, j; // Índices para serem utilizados nas estruturas de repetição.
	int len; // Número que representa o tamanho real da string (caracteres diferentes de '\0').
	int temp; // Variável que armazena o valor de um bit como inteiro (redundante).
	int power; // Potência de 2.
	int num; // Variável que armazena o valor do número em decimal.

	memset(bin, '\0', 30 * sizeof(char));
	scanf(" %s", bin); // Lê número binário como string.

	// Calcula o comprimento da string.
	for (len = 0; bin[len] != '\0'; len++);

	// Transfere o número binário para decimal.
	for (i = 0, num = 0; i < len; i++) {
		temp = bin[i] - 48; // Transforma char em int pela tabela ASCII (48 = '0').

		// Calcula 2^(len - i - 1). Ou seja 2 elevado à potência que representa a
		// posição do bit da direita para a esquerda. (de 0 a len - 1).
		for (power = 1, j = 0; j < len - i - 1; j++) power *= 2;

		num += temp * power; // Adiciona o bit multiplicado pelo valor de sua respectiva posição.
							 // Valores das posições: (...) 256 128 64 32 16 8 4 2 1.
	}

	printf("%d", num); // Imprime na tela o número fornecido na entrada só que em decimal.

	return 0;
}
