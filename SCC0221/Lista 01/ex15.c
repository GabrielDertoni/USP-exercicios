#include <stdio.h>

int main(int argc, char *argv[]) {
	int type;
	float value;
	printf("Insira o tipo de investimento\n");
	printf("1 - Poupança\n");
	printf("2 - Fundos de renda fixa\n");
	scanf("%d", &type);
	printf("Insira o valor do investimento\n");
	scanf("%f", &value);

	switch(type) {
		case 1:
			printf("Após um mês, o valor corrigido será de R$ %.2f\n", value * 1.03);
		break;
		case 2:
			printf("Após um mês, o valor corrigido será de R$ %.2f\n", value * 1.04);
		break;
		default:
			printf("Erro: tipo de investimento não reconhecido\n");
	}
	return 0;
}
