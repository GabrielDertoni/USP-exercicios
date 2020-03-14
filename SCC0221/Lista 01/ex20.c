#include <stdio.h>

int main(int argc, char *argv[]) {
	int age;	
	printf("Insira a idade do nadador\n");
	scanf("%d", &age);

	printf("A categoria do nadador é ");
	if (age > 30)
		printf("sênior\n");
	else if (age >= 16)
		printf("adulto\n");
	else if (age >= 11)
		printf("adolescente\n");
	else if (age >= 8)
		printf("juvenul\n");
	else if (age >= 5)
		printf("infantil\n");
	else
		printf("não categorizado\n");

	return 0;
}
