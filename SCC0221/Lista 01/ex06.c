#include <stdio.h>
#include <math.h>

#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"


int main(int argc, char *argv[]) {
	int num1, num2, op;
	printf("Digite um numero para executar uma das seguintes operacoes:\n");
	printf("1 - a^b\n");
	printf("2 - a^(1/2), b^(1/2)\n");
	printf("3 - a^(1/3), b^(1/3)\n");
	scanf("%d", &op);
	printf("Digite o numero 'a' (inteiro)\n");
	scanf("%d", &num1);
	printf("Digite o numero 'b' (inteiro)\n");
	scanf("%d", &num2);

	switch(op) {
		case 1:
			if (num1 == 0 && num2 == 0)
				printf(RED "Erro" RESET ": 0^0 nao e uma entrada valida.\n");
			else
				printf("a^b: %.1f\n", pow(num1, num2));
		break;

		case 2:
			if (num1 < 0 || num2 < 0)
				printf(RED "Erro" RESET ": ambos numeros devem ser positivos.\n");
			else {
				printf("a^(1/2): %.2f\n", pow(num1, .5));
				printf("b^(1/2): %.2f\n", pow(num2, .5));
			}
		break;

		case 3:
			if (num1 < 0 || num2 < 0)
				printf(RED "Erro" RESET ": ambos numeros devem ser positivos.\n");
			else {
				printf("a^(1/3): %.2f\n", pow(num1, .33333));
				printf("b^(1/3): %.2f\n", pow(num2, .33333));
			}
		break;

		default:
			printf(RED "Erro" RESET ": operacao nao reconhecida.\n");

	}
	return 0;
}
