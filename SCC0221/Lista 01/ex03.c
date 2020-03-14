#include <stdio.h>

int main(int argc, char *argv[]) {
	float num1, num2;
  printf("Insira o primeiro numero:\n");
  scanf("%f", &num1);
	printf("Insira o segundo numero:\n");
	scanf("%f", &num2);

	printf("O menor numero foi: ");
	if (num1 < num2)
		printf("%.1f\n", num1);
	else
		printf("%.1f\n", num2);
	
	return 0;
}
