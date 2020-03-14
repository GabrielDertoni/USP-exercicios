#include <stdio.h>

int main(int argc, char *argv[]) {	
	int num1, num2, op;
	printf("Digite o primeiro numero:\n");
	scanf("%d", &num1);
	printf("Digite o segundo numero:\n");
	scanf("%d", &num2);
	printf("Digite o numero da operacao:\n");
	scanf("%d", &op);

	switch(op) {
		case 1:
			printf("media: %.2f\n", ((float)num1 + (float)num2) / 2);
		break;

		case 2:
		{
			int diff;
			if (num1 > num2)
				diff = num1 - num2;
			else
				diff = num2 - num1;
			printf("diferenca: %d\n", diff);
			break;
		}

		case 3:
			printf("produto: %d\n", num1 * num2);
		break;

		case 4:
			if (num2 == 0)
				printf("Erro: divisao por 0.\n");
			else
				printf("divisao: %.2f\n", ((float)num1 / (float)num2));
		break;

		default:
			printf("Erro: operacao invalida.\n");
	}
	return 0;
}
