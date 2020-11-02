#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


// Garante que ao menos "size" está alocado em "ptr".
unsigned long maybeReallocate(void **ptr, unsigned long size, unsigned long allocated);
// Lê e retorna uma string até encontrar um dos caracteres contidos em "stop".
char *readUntil(char *stop, FILE *fp);
// Lê sem retornar caracteres até encontrar um caractere não contido dem "chars".
// Retorna o número de caracteres ignorados.
int ignoreSome(char *chars, FILE *fp);
char *readLine(FILE *fp);
// Abre um arquivo, executa "func" e fecha o arquivo.
void withFile(const char *fpath, const char *mode, void (*func)(FILE *));
void process(FILE *fp); // Função principal do programa.
// Resolve o labirinto. Retorna se foi possível resolvê-lo
bool solve(int n, int m, int x, int y, char **maze);
char **readMaze(unsigned int n, unsigned int m, FILE *fp);
void printMaze(unsigned int n, unsigned int m, char **maze);
void printMazeStats(unsigned int n, unsigned int m, char **maze);

int main(int argc, char *argv[]) {
	char *fname = readLine(stdin);
	withFile(fname, "r", process);
	free(fname);
	return EXIT_SUCCESS;
}

bool solve(int n, int m, int x, int y, char **maze) {
	// Marca o lugar atual.
	maze[y][x] = '*';

	// Se chegou ao final do labirinto, retorne true (resolvido).
	if (x == 0 || x == n - 1 || y == 0 || y == m - 1)
		return true;

	// Se algum dos caminhos possíveis a partir desse caminho resolve o problema, retorne true (resolvido)
	return ((y > 0   && maze[y-1][x] == '.' && solve(n, m, x  , y-1, maze)) ||
			(x < n-1 && maze[y][x+1] == '.' && solve(n, m, x+1, y  , maze)) ||
			(y < m-1 && maze[y+1][x] == '.' && solve(n, m, x  , y+1, maze)) ||
			(x > 0   && maze[y][x-1] == '.' && solve(n, m, x-1, y  , maze)));
}

void process(FILE *fp) {
	unsigned int n, m, x, y;
	fscanf(fp, "%u %u %u %u ", &m, &n, &y, &x);
	char **maze = readMaze(n, m, fp);
	solve(n, m, x, y, maze);
	printMaze(n, m, maze);
	printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
	printMazeStats(n, m, maze);

	while(m) free(maze[--m]);
	free(maze);
}

char **readMaze(unsigned int n, unsigned int m, FILE *fp) {
	char **maze = (char **)malloc(m * sizeof(char *));
	for (int i = 0; i < m; i++) {
		maze[i] = (char *)malloc(n * sizeof(char));
		if (fread((void *)maze[i], sizeof(char), n, fp) != n)
			exit(EXIT_FAILURE);

		ignoreSome("\r\n", fp); // Consome quaisquer \r e/ou \n indesejados
	}
	return maze;
}

void printMazeStats(unsigned int n, unsigned int m, char **maze) {
	printf("Veja abaixo os detalhes da sua fuga:\n");
	int npeople = 0, paths = 0, visited = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++) {
			npeople += maze[i][j] == '#';
			paths += maze[i][j] == '*' || maze[i][j] == '.';
			visited += maze[i][j] == '*';
		}

	double exploration = floor(100 * (double)visited / (double)paths);
	printf("----Pessoas te procurando: %d\n", npeople);
	printf("----Numero total de caminhos validos:   %d\n", paths);
	printf("----Numero total de caminhos visitados: %d\n", visited);
	printf("----Exploracao total do labirinto: %.1lf%%\n", exploration);
}

void printMaze(unsigned int n, unsigned int m, char **maze) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) putchar(maze[i][j]);
		putchar('\n');
	}
}

// Garante que o arquivo será aberto e fechado.
void withFile(const char *fpath, const char *mode, void (*func)(FILE *)) {
	FILE *fp = fopen(fpath, mode);
	func(fp);
	fclose(fp);
}

char *readLine(FILE *fp) { return readUntil("\r\n", fp); }

char *readUntil(char *stop, FILE *fp) {
	char c;
	int i, allocated;
	char *string = NULL;
	for (i = 0, allocated = 0; !strchr(stop, c = getc(fp)) && !feof(fp); i++) {
		allocated = maybeReallocate((void **)&string, i, allocated);
		string[i] = c;
	}
	if (allocated == 0) return "";
	if (c != EOF) ungetc(c, fp);
	string[i] = '\0';
	return (char *)realloc(string, (i + 1)*sizeof(char));
}

int ignoreSome(char *chars, FILE *fp) {
	char c; int i;
	for (i = 0; strchr(chars, c = getc(fp)) && !feof(fp); i++);
	if (c != EOF) ungetc(c, fp);
	return i;
}

unsigned long maybeReallocate(void **ptr, unsigned long size, unsigned long allocated) {
	if (size >= allocated) {
		allocated *= 2;
		if (allocated == 0) allocated += 32;
		*ptr = realloc(*ptr, allocated);
	}
	return allocated;
}
