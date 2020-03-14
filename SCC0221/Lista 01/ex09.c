#include <stdio.h>

int main(int argc, char *argv[]) {
	float value;
	printf("Insira o saldo medio\n");
	scanf("%f", &value);

	float credit;
	if (value > 400)
		credit = value * 1.3;
	else if (value > 300)
		credit = value * 1.25;
	else if (value > 200)
		credit = value * 1.2;
	else
		credit = value * 1.1;

	printf("O credito oferecido sera de R$ %.2f, o saldo medio foi de R$ %.2f\n", credit, value);	
	return 0;
}
