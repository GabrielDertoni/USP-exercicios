#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	float height;
	char sex;
	printf("Insira seu sexo (H: homem, M: mulher)\n");
	scanf("%c", &sex);
	printf("Insira sua altura (em metros)\n");
	scanf("%f", &height);

	switch (sex) {
		case 'H':
			printf("O peso ideal é de ");
			printf("%.2f kg\n", 72.7 * height - 58);
		break;
		case 'M':
			printf("O peso ideal é de ");
			printf("%.2f kg\n", 62.1 * height - 44.7);
		break;
		default:
			printf("Erro: sexo não reconhecido, digite H: homeme, M: mulher\n");
	}
	return 0;
}
