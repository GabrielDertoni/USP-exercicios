#include <stdio.h>

void sort(int *v) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++) {
			if (v[j] > v[j + 1]) {
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
}
void printm(int m[5][4]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++)
			printf("%d  ", m[i][j]);

		printf("\n");
	}
}
void printm_reversed(int m[5][4]) {
	for (int i = 4; i >= 0; i--) {
		for (int j = 3; j >= 0; j--)
			printf("%d  ", m[i][j]);

		printf("\n");
	}
}
int main() {
	int m[5][4];
	printf("Digite os valores dos 5 grupos:\n");
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 4; j++)
			scanf("%d", &m[i][j]);

	printf("Digitado:\n");
	printm(m);

	for (int i = 0; i < 5; i++)
		sort(m[i]);	

	printf("Ordem creascente:\n");
	printm(m);

	printf("Ordem descrescente:\n");
	printm_reversed(m);

	return 0;
}
