#include <stdio.h>

int main(int argc, char *argv[]) {
	int age;
	float weight;
	printf("Insira a idade\n");
	scanf("%d", &age);
	printf("Insira o peso\n");
	scanf("%f", &weight);

	int risk = 9;
	if (age > 50)
		risk -= 6;
	else if (age >= 20)
		risk -= 3;

	if (weight > 90)
		risk -= 2;
	else if (weight >= 60)
		risk -= 1;

	printf("O grupo de risco é %d\n", risk);
	return 0;
}
