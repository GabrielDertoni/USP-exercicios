#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "en_US.UTF-8");
	int n_labels;
	int n_inputs;
	int *histogram;
	int i, j, input, max, biggest_lbl, bar_sz;
	
	scanf("%d %d", &n_labels, &n_inputs);

	histogram = (int *)malloc(n_labels * sizeof(int));
	for (i = 0; i < n_inputs; i++) {
		scanf("%d", &input);
		histogram[input]++;
	}

	for (i = 0; i < n_inputs; i++)
		if (i == 0 || histogram[i] > max)
			max = histogram[i];

	if (argc == n_labels + 1) {
		for (i = 0; i < argc - 1; i++)
			if (i == 0 || biggest_lbl < strlen(argv[i + 1]))
				biggest_lbl = strlen(argv[i + 1]);
	} else
		biggest_lbl = (int)log10((double)(n_labels - 1)) + 1;

	bar_sz = biggest_lbl + 6 + max;

	printf("+");
	for (i = 0; i < bar_sz; i++)
		printf("-");

	printf("+\n");
	printf("|");
	for (i = 0; i < bar_sz / 2 - 4; i++)
		printf(" ");

	printf("Histogram");
	for (i = 0; i < bar_sz / 2 - 5 + (bar_sz % 2); i++)
		printf(" ");

	printf("|\n");

	printf("+");
	for (i = 0; i < bar_sz; i++)
		printf("-");

	printf("+\n");

	for (i = 0; i < n_labels; i++) {
		if (argc == n_labels + 1) {
			printf("|");
			for (j = 0; j < biggest_lbl - strlen(argv[i + 1]); j++)
				printf(" ");

			printf(" %s: ", argv[i + 1]);
		} else
			printf("| %*d: ", biggest_lbl, i);

		for (j = 0; j < max; j++)
			if (j < histogram[i])
				wprintf(L"\x2588");
			else
				printf(" ");

		printf("   |\n");
	}

	printf("+");
	for (i = 0; i < bar_sz; i++)
		printf("-");

	printf("+\n");

	return 0;
}
