#include <stdio.h>

int main(int argc, char *argv[]) {
	float value;
	printf("Insira o valor do salário bruto\n");
	scanf("%f", &value);
	
	printf("O valor a receber será de R$ ");
	if (value > 900)
		printf("%.2f\n", value * .93 + 35);
	else if (value >= 600)
		printf("%.2f\n", value * .93 + 50);
	else if (value > 350)
		printf("%.2f\n", value * .93 + 75);
	else
		printf("%.2f\n", value * .93 + 100);
		
	return 0;
}
