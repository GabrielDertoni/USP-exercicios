#include <stdio.h>
#include <stdbool.h>
#include "colors.h"

// Verifica se a string1 é a mesma que a string2 e retorna verdadeiro ou falso.
bool str_eq(char string1[], char string2[]) {
	int i = 0;
	while (string1[i] != '\0' && string2[i] != '\0') {
		if (string1[i] != string2[i])
			return false;
		i++;
	}
	return true;
}

int main(int argc, char *argv[]) {
	char password[4];
	printf("Digite a senha (4 caracteres)\n");
	scanf("%s", password);
	if (str_eq(password, "4531"))
		printf("A senha está " GREEN "correta" RESET "!\n");
	else
		printf("A senha está " RED "errada" RESET "!\n");

	return 0;
}
