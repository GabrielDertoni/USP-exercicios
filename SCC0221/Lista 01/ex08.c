#include <stdio.h>

int main(int argc, char *argv[]) {
	float value;
	printf("Digite o valor do salario em:\n");
	scanf("%f", &value);	

	printf("O salario reajustado: R$ ");
	if (value > 300)
		printf("%.2f\n", value * 1.15);
	else {
		printf("%.2f\n", value * 1.35);
	}
	return 0;
}
