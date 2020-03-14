#include <stdio.h>

/*
 * Programa da 1a aula de Lab de ICC.
 * Exercício: ANO BISEXTO
 *
 * Recebe como entrada um ano e responde SIM
 * caso esse ano seja bisexto e responde NAO
 * caso contrário.
 */

int main() {
	int year;
	scanf("%d", &year);

	if (year % 4 == 0)
		printf("SIM");
	else
		printf("NAO");

	return 0;
}
