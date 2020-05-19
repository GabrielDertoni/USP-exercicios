#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned short red;
	unsigned short green;
	unsigned short blue;
} color_t;

color_t *readPallete();
color_t mixColors(color_t color1, color_t color2);
void printPallete(color_t *pallete);

int main(int argc, char *argv[]) {
	int p1, p2, p3;
	scanf("%d %d %d", &p1, &p2, &p3);

	color_t *pallete = readPallete();

	printf("Start:\n");
	printPallete(pallete);

	color_t mixed = mixColors(pallete[p1], pallete[p2]);
	pallete[p3].red   += mixed.red;
	pallete[p3].green += mixed.green;
	pallete[p3].blue  += mixed.blue;

	printf("\nResult:\n");
	printPallete(pallete);

	free(pallete);
	
	return EXIT_SUCCESS;
}

color_t *readPallete() {
	color_t *mat = (color_t *)malloc(6 * sizeof(color_t));
	for (int i = 0; i < 6; i++)
		scanf("%hu %hu %hu", &mat[i].red, &mat[i].green, &mat[i].blue);

	return mat;
}

color_t mixColors(color_t color1, color_t color2) {
	color_t newColor = {
		.red   = color1.red   / 2 + color2.red   / 2,
		.green = color1.green / 2 + color2.green / 2,
		.blue  = color1.blue  / 2 + color2.blue  / 2
	};
	return newColor;
}

void printPallete(color_t *pallete) {
	for (int i = 0; i < 6; i++)
		printf("Color(%d): [\t%hu\t%hu\t%hu\t]\n", i, pallete[i].red, pallete[i].green, pallete[i].blue);
}
