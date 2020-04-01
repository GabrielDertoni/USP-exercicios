#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int columns, rows; // Número de linhas e colunas da matriz.
	int *mat; // Vetor que armazena os valores da matriz.
	int det; // Determinante.
	int i; // Índice para iterar por todos os elementos da matriz.
	
	// Recebe a entrada de linhas e colunas.
	scanf("%d %d", &columns, &rows);
	// Verifica se a matriz é de ordem válida.
	if (columns > 3 || columns < 1 || rows > 3 || rows < 1)
		printf("Entradas invalidas!\n");
	else if (columns != rows) // Verifica se a matriz possui determinante.
		printf("A matriz de entrada nao possui determinante!\n");
	else {
		// Calcula a determinante com métodos que variam de acordo com a ordem da matriz.
		mat = (int *)malloc(columns * rows * sizeof(int));
		for (i = 0; i < columns * rows; i++)
			scanf(" %d", mat + i);

		if (columns == 1)
			det = mat[0];
		else if (columns == 2)
			det = mat[0] * mat[3] - mat[1] * mat[2];
		else
			det = (mat[0] * mat[4] * mat[8] +
			       mat[1] * mat[5] * mat[6] +
			       mat[2] * mat[3] * mat[7]) -
			      (mat[2] * mat[4] * mat[6] +
			       mat[0] * mat[5] * mat[7] +
				   mat[1] * mat[3] * mat[8]);

		printf("O determinante da matriz de entrada equivale a %d e tem ordem %d\n", det, columns);
	}


	return 0;
}
