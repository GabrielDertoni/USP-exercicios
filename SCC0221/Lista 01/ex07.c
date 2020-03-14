#include <stdio.h>

int main(int argc, char *argv[]) {
	float value;
	printf("Digite o valor do salario em:\n");
	scanf("%f", &value);	

	if (value >= 500)
		printf("O salario nao recebeu reajuste.\n");
	else {
		printf("O salario foi reajustado para o valor de R$ %.2f\n", value * 1.3);
	}
	return 0;
}
