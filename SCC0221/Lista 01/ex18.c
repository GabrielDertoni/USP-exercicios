#include <stdio.h>

int main(int argc, char *argv[]) {
	int age;
	printf("Insira a idade\n");	
	scanf("%d", &age);

	if (age >= 18)
		printf("A pessoa já atingiu a maioridade\n");
	else
		printf("A pessoa ainda não atingiu a maioridade\n");

	return 0;
}
