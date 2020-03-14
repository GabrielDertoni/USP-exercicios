#include <stdio.h>

void print_bin(int num) {
	if (num != 0) {
		print_bin(num / 2);
		printf("%d", num % 2);
	}
}
int main() {
	int num;
	printf("Digite o número a ser convertido: ");
	scanf("%d", &num);

	printf("O número em binário é: ");
	print_bin(num);
	printf("\n");

	return 0;
}
