#include <stdio.h>
#include "colors.h"

int main(int argc, char *argv[]) {
	int code;
	printf("Insira o código do produto\n");
	scanf("%d", &code);

	if (code > 30)
		printf(RED "Código inválido.\n" RESET);	
	else {
		printf("A procedência do produto é do ");
		if (code >= 21)
			printf("Nordeste\n");
		else if (code >= 10)
			printf("Centro-Oeste\n");
		else if (code >= 7)
			printf("Sudeste\n");
		else if (code >= 5)
			printf("Nordeste\n");
		else if (code == 4)
			printf("Oeste\n");
		else if (code == 3)
			printf("Leste\n");
		else if (code == 2)
			printf("Norte");
		else
			printf("Sul");
	}
	return 0;
}
