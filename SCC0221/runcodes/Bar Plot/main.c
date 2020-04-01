#include <stdio.h>
#include <stdlib.h>

int main() {
	int n_labels;
	int n_inputs;
	int *histogram;
	int i, j, input;
	
	scanf("%d %d", &n_labels, &n_inputs);

	histogram = (int *)malloc(n_labels * sizeof(int));
	for (i = 0; i < n_inputs; i++) {
		scanf("%d", &input);
		histogram[input]++;
	}

	for (i = 0; i < n_labels; i++) {
		printf("%d - ", i);
		for (j = 0; j < histogram[i]; j++)
			printf("#");

		printf("\n");
	}

	return 0;
}
