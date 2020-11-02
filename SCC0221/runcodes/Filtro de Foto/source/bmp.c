#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bmp.h"

int readBMPHeader(BMP_HEADER *header, FILE *fp) {
	rewind(fp); // Garante que fp aponta para o iníco do arquivo.
	if (fread((void *)&header->signature, 2, 1, fp) != 1) return ERROR_READ;
	if (strcmp(header->signature, "BM")) return ERROR_NOT_BMP;
	if (fread((void *)&header->file_size, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->reserved, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->offset, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->size_snd_header, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->width, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->height, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->n_planes, 2, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->bits_per_pixel, 2, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->compression, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->img_size, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->horizontal_ppm, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->vertical_ppm, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->n_used_colors, 4, 1, fp) != 1) return ERROR_READ;
	if (fread((void *)&header->n_important_colrs, 4, 1, fp) != 1) return ERROR_READ;

	return SUCCESS;
}

int getNColors(BMP_HEADER *header) {
	int n_colors;
	if (header->n_used_colors) // Caso n_colors != 0, aloca o suficiente para essas cores
		n_colors = header->n_used_colors;
	else // Caso n_colors == 0 (automático), usar 2^bits_per_pixel
		n_colors = 1L << header->bits_per_pixel;

	return n_colors;
}

int getPaddedWidth(BMP_HEADER *header) {
	return header->width % 4 == 0 ? header->width : header->width + 4 - header->width % 4;
}

RGB *readBMPPallete(BMP_HEADER *header, FILE *fp) {
	fseek(fp, 14 + header->size_snd_header, SEEK_SET);

	int n_colors = getNColors(header);
	RGB *pallete = (RGB *)malloc(n_colors * sizeof(RGB));

	for (int i = 0; i < n_colors; i++) {
		fread((void *)&pallete[i].b, 1, 1, fp);
		fread((void *)&pallete[i].g, 1, 1, fp);
		fread((void *)&pallete[i].r, 1, 1, fp);
		fseek(fp, ftell(fp) + 1, SEEK_SET); // Pula o valor reservado.
	}
	return pallete;
}

int *readBMPData(BMP_HEADER *header, FILE *fp) {
	fseek(fp, header->offset, SEEK_SET);
	int *data = (int *)malloc(header->img_size * sizeof(int));
	int width = getPaddedWidth(header);
	for (int i = 0; i < header->height; i++)
		for (int j = 0; j < width; j++)
			if (j < header->width)
				fread((void *)&data[i * width + j], header->bits_per_pixel / 8, 1, fp);
			else {
				// Seta o valor de data nesse índice para 0 e não lê o lixo (padding)
				data[i * width + j] = 0;
				fseek(fp, ftell(fp) + header->bits_per_pixel / 8, SEEK_SET);
			}

	return data;
}
int writeBMPHeader(BMP_HEADER *header, FILE *fp) {
	//rewind(fp); // Garante que fp aponta para o iníco do arquivo.
	if (fwrite((void *)&header->signature, 2, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->file_size, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->reserved, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->offset, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->size_snd_header, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->width, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->height, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->n_planes, 2, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->bits_per_pixel, 2, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->compression, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->img_size, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->horizontal_ppm, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->vertical_ppm, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->n_used_colors, 4, 1, fp) != 1) return ERROR_WRITE;
	if (fwrite((void *)&header->n_important_colrs, 4, 1, fp) != 1) return ERROR_WRITE;

	return SUCCESS;
}
int writeBMPPallete(RGB *pallete, BMP_HEADER *header, FILE *fp) {
	//fseek(fp, 14 + header->size_snd_header, SEEK_SET);

	int n_colors = getNColors(header);
	for (int i = 0; i < n_colors; i++) {
		if (fwrite((void *)&pallete[i].b, 1, 1, fp) != 1) return ERROR_WRITE;
		if (fwrite((void *)&pallete[i].g, 1, 1, fp) != 1) return ERROR_WRITE;
		if (fwrite((void *)&pallete[i].r, 1, 1, fp) != 1) return ERROR_WRITE;
		fputc(0, fp); // Escreve um 0 no campo reservado.
	}
	return SUCCESS;
}
int writeBMPData(int *data, BMP_HEADER *header, FILE *fp) {
	//fseek(fp, header->offset, SEEK_SET);
	for (int i = 0; i < header->img_size; i++)
		if (fwrite((void *)&data[i], header->bits_per_pixel / 8, 1, fp) != 1)
			return ERROR_WRITE;

	return SUCCESS;
}

RGB *invertBMPPallete(RGB *pallete, BMP_HEADER *header) {
	int n_colors = getNColors(header);
	RGB *new_pallete = (RGB *)malloc(n_colors * sizeof(RGB));
	for (int i = 0; i < n_colors; i++) {
		new_pallete[i].r = 255 - pallete[i].r;
		new_pallete[i].g = 255 - pallete[i].g;
		new_pallete[i].b = 255 - pallete[i].b;
	}

	return new_pallete;
}

RGB *negativeBMPPallete(RGB *pallete, BMP_HEADER *header) {
	int n_colors = getNColors(header);
	RGB *new_pallete = (RGB *)malloc(n_colors * sizeof(RGB));
	for (int i = 0; i < n_colors; i++) {
		int avg = (pallete[i].r + pallete[i].g + pallete[i].b) / 3;
		new_pallete[i].r = avg;
		new_pallete[i].g = avg;
		new_pallete[i].b = avg;
	}
	return new_pallete;
}

void printBMPHeader(BMP_HEADER *header) {
	printf("CABECALHO:\n");
	printf("Iniciais: %s\n", header->signature);
	printf("Tamanho do arquivo: %d\n", header->file_size);
	printf("Reservado: %d\n", header->reserved);
	printf("Deslocamento, em bytes, para o inicio da area de dados: %d\n", header->offset);
	printf("Tamanho em bytes do segundo cabecalho: %d\n", header->size_snd_header);
	printf("Resolucao: %d x %d\n", header->width, header->height);
	printf("Numero de planos: %hd\n", header->n_planes);
	printf("Bits por pixel: %hd\n", header->bits_per_pixel);
	printf("Compressao usada: %d\n", header->compression);
	printf("Tamanho imagem: %d\n", header->img_size);
	printf("Resolucao horizontal: %d pixel por metro\n", header->horizontal_ppm);
	printf("Resolucao Vertical: %d pixel por metro\n", header->vertical_ppm);
	printf("Numero de cores usadas: %d\n", header->n_used_colors);
	printf("Numero de cores importantes: %d\n", header->n_important_colrs);
}

void printLineSums(int *data, BMP_HEADER *header) {
	int width = getPaddedWidth(header);
	for (int i = header->height - 1; i >= 0; i--) {
		long long sum = 0;
		for (int j = 0; j < width; j++)
			sum += data[i * width + j];

		sum -= width - header->width;
		printf("Soma linha %d: %lld\n", header->height - i - 1, sum);
	}
}

void printBMPPallete(RGB *pallete, BMP_HEADER *header) {
	int n_colors = getNColors(header);
	for (int i = 0; i < n_colors; i++) {
		printf("Paleta[%d]: R:%hd G:%hd B:%hd\n", i, pallete[i].r, pallete[i].g, pallete[i].b);
	}
}
