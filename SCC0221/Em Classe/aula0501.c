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
void print_group(int *v) {
	for (int i = 0; i < 4; i++)
		printf("%d ", v[i]);

	printf("\n");
}
void print_reverse_group(int *v) {
	for (int i = 3; i >= 0; i--)
		printf("%d ", v[i]);

	printf("\n");
}
void read_group(int *v) {
	scanf("%d %d %d %d", &v[0], &v[1], &v[2], &v[3]);
}
int main() {
	int v1[4], v2[4], v3[4], v4[4], v5[4];

	printf("Insira os valores do grupo 1: ");
	read_group(v1);

	printf("Insira os valores do grupo 2: ");
	read_group(v2);

	printf("Insira os valores do grupo 3: ");
	read_group(v3);

	printf("Insira os valores do grupo 4: ");
	read_group(v4);

	printf("Insira os valores do grupo 5: ");
	read_group(v5);

	printf("Ordem digitada:\n");
	print_group(v1);
	print_group(v2);
	print_group(v3);
	print_group(v4);
	print_group(v5);

	sort(v1);
	sort(v2);
	sort(v3);
	sort(v4);
	sort(v5);

	printf("Ordem creascente:\n");
	print_group(v1);
	print_group(v2);
	print_group(v3);
	print_group(v4);
	print_group(v5);

	printf("Ordem decrescente:\n");
	print_reverse_group(v1);
	print_reverse_group(v2);
	print_reverse_group(v3);
	print_reverse_group(v4);
	print_reverse_group(v5);

	return 0;
}
