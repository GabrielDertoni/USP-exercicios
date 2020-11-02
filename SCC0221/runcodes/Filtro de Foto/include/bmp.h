#ifndef _BMP_
#define _BMP_

#define ERROR_FILE -100
#define ERROR_READ -200
#define ERROR_WRITE -300
#define ERROR_NOT_BMP -201
#define SUCCESS 0

typedef struct {
	char signature[3];
	int file_size;
	int reserved;
	int offset;
	int size_snd_header;
	int width;
	int height;
	short int n_planes;
	short int bits_per_pixel;
	int compression;
	int img_size;
	int horizontal_ppm;
	int vertical_ppm;
	int n_used_colors;
	int n_important_colrs;
} BMP_HEADER;

typedef struct {
	short int r;
	short int g;
	short int b;
} RGB;

int readBMPHeader(BMP_HEADER *header, FILE *fp);
int getNColors(BMP_HEADER *header);
RGB *readBMPPallete(BMP_HEADER *header, FILE *fp);
int *readBMPData(BMP_HEADER *header, FILE *fp);
RGB *invertBMPPallete(RGB *pallete, BMP_HEADER *header);
RGB *negativeBMPPallete(RGB *pallete, BMP_HEADER *header);
void printBMPHeader(BMP_HEADER *header);
void printLineSums(int *data, BMP_HEADER *header);
void printBMPPallete(RGB *pallete, BMP_HEADER *header);
int writeBMPHeader(BMP_HEADER *metadata, FILE *out_fp);
int writeBMPPallete(RGB *pallete, BMP_HEADER *metadata, FILE *out_fp);
int writeBMPData(int *data, BMP_HEADER *metadata, FILE *out_fp);
int getPaddedWidth(BMP_HEADER *header);

#endif
