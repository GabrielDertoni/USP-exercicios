#include <stdio.h>

int main(int argc, char *argv[]) {
	float price;
	printf("Insira o preço atual do produto\n");
	scanf("%f", &price);

	float discount;
	if (price > 100)
		discount = .15;
	else if (price > 30)
		discount = .1;
	else
		discount = 0;

	printf("O desconto será de R$ %.2f, e o novo preço de R$ %.2f\n", price * discount, price * (1 + discount));
	return 0;
}
