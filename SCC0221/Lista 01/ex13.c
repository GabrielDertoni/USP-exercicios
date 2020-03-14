#include <stdio.h>

int main(int argc, char *argv[]) {
	float price;
	printf("Insira o preço do produto\n");	
	scanf("%f", &price);

	float newprice;
	if (price > 100)
		newprice = price * 1.15;
	else if (price > 50)
		newprice = price * 1.1;
	else
		newprice = price * 1.05;

	printf("O novo preço será de R$ %.2f e sua classificação é ", newprice);
	if (newprice > 200)
		printf("muito caro\n");
	else if (newprice > 120)
		printf("caro\n");
	else if (newprice > 80)
		printf("normal\n");
	else
		printf("barato\n");

	return 0;
}
