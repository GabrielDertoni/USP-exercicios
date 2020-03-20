#include <stdio.h>

int main() {
	int n, maior_valor, menor_valor;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int entrada;
		scanf("%d", &entrada);
		if (i == 0) {
			menor_valor = entrada;	   
			maior_valor = entrada;
		} else if (entrada < menor_valor) {
			menor_valor = entrada;
		} else if (entrada > maior_valor) {
			maior_valor= entrada;
		}
	}
	printf("max: %d\n", maior_valor);
	printf("min: %d\n", menor_valor);

	return 0;
}
