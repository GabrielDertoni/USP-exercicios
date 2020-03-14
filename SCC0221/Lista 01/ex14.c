#include <stdio.h>

int main(int argc, char *argv[]) {
	float value;
	printf("Insira o valor do salário atual\n");
	scanf("%f", &value);

	printf("O valor do salário reajustado será de ");
	if (value > 1000)
		printf("R$ %.2f\n", value * 1.05);
	else if (value >= 800)
		printf("R$ %.2f\n", value * 1.1);
	else if (value > 700)
		printf("R$ %.2f\n", value * 1.2);
	else if (value > 500)
		printf("R$ %.2f\n", value * 1.3);
	else if (value > 300)
		printf("R$ %.2f\n", value * 1.4);
	else
		printf("R$ %.2f\n", value * 1.5);

	return 0;
}
