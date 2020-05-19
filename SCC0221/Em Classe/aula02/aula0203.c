#include <stdio.h>

int main() {
	int num;
	printf("Digite o número a ser convertido: ");
	scanf("%d", &num);

	printf("O número em binário é (ao contrário): ");
	for (; num != 0; num = num / 2)
		printf("%d", num % 2);

	printf("\n");
	return 0;
}
