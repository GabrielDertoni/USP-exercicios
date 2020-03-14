#include <stdio.h>

int main(int argc, char *argv[]) {
	int min;
	for (int i = 0; i < 3; i++) {
		printf("Insira o %io numero:\n", i + 1);
		int num;
		scanf("%i", &num);
		if (i == 0 || num < min)
			min = num;
	}
	printf("O menor numero foi: %i\n", min);
}
