#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int width, height, padding;
	scanf("%d %d", &width, &height);
	
	unsigned short **img = (unsigned short **)malloc(height * sizeof(unsigned short *));
	for (int i = 0; i < height; i++) {
		img[i] = (unsigned short *)malloc(width * sizeof(unsigned short));
		for (int j = 0; j < width; j++)
			scanf("%hu", &img[i][j]);
	}

	scanf("%d", &padding);
	for (int i = 0; i < height + 2 * padding; i++) {
		for (int j = 0; j < width + 2 * padding; j++)
			if (i < padding || i >= height + padding || j < padding || j >= width + padding) printf("0 ");
			else printf("%hu ", img[i - padding][j - padding]);

		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			printf("%hu ", img[i][j]);

		printf("\n");
	}

	
	return 0;
}
