#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parsing.h"
#include "../include/bmp.h"

int main(int argc, char *argv[]) {
	char *filepath = readLine(stdin);

	// Verifica se a extenção é de fato .bmp
	char *ext = filepath + strlen(filepath) - 1;
	while(ext != filepath && *ext != '.') ext--;
	if (strcmp(ext, ".bmp")) {
		printf("Arquivo nao eh do formato BMP");
		exit(EXIT_SUCCESS);
	}

	FILE *fp = fopen(filepath, "rb");

	// Caso o arquivo não possa ser aberto, finalize o programa.
	if (!fp) {
		printf("Erro no arquivo\n");
		exit(EXIT_SUCCESS);
	}

	BMP_HEADER *metadata = (BMP_HEADER *)malloc(sizeof(BMP_HEADER));
	// Falha caso o arquivo não possua a assinatura correta;
	if (readBMPHeader(metadata, fp) == ERROR_NOT_BMP) {
		printf("Arquivo nao eh do formato BMP");
		exit(EXIT_SUCCESS);
	}
	printBMPHeader(metadata);

	RGB *pallete = readBMPPallete(metadata, fp);

	printf("PALETA ORIGINAL:\n");
	printBMPPallete(pallete, metadata);

	int op;
	scanf(" %d", &op);

	RGB *new_pallete;
	if (op == 1) new_pallete = invertBMPPallete(pallete, metadata);
	else new_pallete = negativeBMPPallete(pallete, metadata);

	printf("PALETA NOVA:\n");
	printBMPPallete(new_pallete, metadata);
	
	int *data = readBMPData(metadata, fp);
	printLineSums(data, metadata);

	char *suffix = op == 1 ? "Negativo" : "PretoBranco";
	char *out_filename = (char *)malloc((strlen(filepath) + strlen(suffix) + 1) * sizeof(char));
	sprintf(out_filename, "%.*s%s%s", (int)(ext - filepath), filepath, suffix, ext);
	printf("%s\n", out_filename);

	FILE *out_fp = fopen(out_filename, "wb");
	writeBMPHeader(metadata, out_fp);
	writeBMPPallete(new_pallete, metadata, out_fp);
	writeBMPData(data, metadata, out_fp);
	fclose(out_fp);

	free(data);
	free(new_pallete);
	free(pallete);
	free(metadata);
	free(filepath);
	fclose(fp);

	return EXIT_SUCCESS;
}
