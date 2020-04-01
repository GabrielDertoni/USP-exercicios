#include <stdio.h>

int main() {
	short int x, y; // Variáveis que armazenam a direção no eixo x e y do robô.
	                // Podem assumir valores de -1, 0, 1. O 0 indica que não há
					// componente nesse eixo.
	char c; // Caracter que armazena o próximo comando

	// Inicializa a direção no norte (y = 1, "para cima").
	x = 0;
	y = 1;

	// Itera por todas as caracteres na entrada.
	for (c = getc(stdin); c != '\n' && c != EOF; c = getc(stdin))
		if (c == 'D')
			if (x == 0) {
				x = y;
				y = 0;
			} else {
				y = -x;
				x = 0;
			}
		else
			if (x == 0) {
				x = -y;
				y = 0;
			} else {
				y = x;
				x = 0;
			}

	if (x == 0)
		if (y == 1)
			printf("Norte");
		else
			printf("Sul");
	else if (x == 1)
		printf("Leste");
	else
		printf("Oeste");

	return 0;
}
