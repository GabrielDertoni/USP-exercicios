#include <stdio.h>

int main(int argc, char *argv[]) {
	float value;
	printf("Insira o valor do salário atual\n");
	scanf("%f", &value);

	printf("O valor do salário reajustado será de ");
	if (value > 900)
		printf("R$ %.2f com aumento de 0\n", value);
	else if (value >= 600)
		printf("R$ %.2f com aumento de %.2f\n", value * 1.05, value * .05);
	else if (value > 300)
		printf("R$ %.2f com aumento de %.2f\n", value * 1.1, value * .1);
	else
		printf("R$ %.2f com aumento de %.2f\n", value * 1.15, value * .15);

	return 0;
}
