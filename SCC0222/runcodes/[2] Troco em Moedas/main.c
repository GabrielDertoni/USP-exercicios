#include <stdio.h>

void change(int price, int *real1, int *cents50, int *cents25, int *cents10, int *cents5, int *cent1) {
	int temp = price;
	for (*real1 = 0; temp >= 100; temp -= 100) (*real1)++;
	for (*cents50 = 0; temp >= 50; temp -= 50) (*cents50)++;
	for (*cents25 = 0; temp >= 25; temp -= 25) (*cents25)++;
	for (*cents10 = 0; temp >= 10; temp -= 10) (*cents10)++;
	for (*cents5 = 0; temp >= 5; temp -= 5) (*cents5)++;
	for (*cent1 = 0; temp >= 1; temp -= 1) (*cent1)++;
}

int main() {
	int price;
	int real1, cents50, cents25, cents10, cents5, cent1;

	scanf("%d", &price);
	change(price, &real1, &cents50, &cents25, &cents10, &cents5, &cent1);

	printf("O valor consiste em %d moedas de 1 real\n", real1);
	printf("O valor consiste em %d moedas de 50 centavos\n", cents50);
	printf("O valor consiste em %d moedas de 25 centavos\n", cents25);
	printf("O valor consiste em %d moedas de 10 centavos\n", cents10);
	printf("O valor consiste em %d moedas de 5 centavos\n", cents5);
	printf("O valor consiste em %d moedas de 1 centavo\n", cent1);

	return 0;
}
