#include <stdio.h>
#include <stdlib.h>

#define CHUNK 20
#define BOOL short int
#define TRUE 1
#define FALSE 0

typedef struct Book {
	char *name;
	int days;
} book_t;

// Retorna o índice de um livro com determinado nome dentro do
// vetor de book_t. Caso não encontre o livro, retornará -1.
int bookIndex(book_t *books, int n_books, char *name);
// Retorna o índice de um valor inteiro dentro de um vetor de int.
// Caso o valor não seja encontrado, retornará -1.
int intIndex(int value, int array[], int arr_len);
// Verifica se duas strings são iguais.
BOOL strequal(char *str1, char *str2);
// Remove um item de um vetor em qualquer posição e faz as alterações
// necessárias
void pop(int index, int array[], int arr_len);
char *readInput(); // Lê uma linha. (práticamente uma cópia exata da implementação em
                   // SCC0222/[2] Média Harmônica com Funções Básicas)

int main(int argc, char *argv[]) {
	int n, op; // Declara as variáveis de número total de livros e operação.
	int n_rented = 0; // Número de livros alugados.

	// Vetor que contém índices (do vetor de livros) dos
	// livros que foram alugados. index_rented = [1, 2] 
	// signfica que os livros alguados foram books[1] e books[2].
	int index_rented[10]; 
	book_t *books; // Vetor que contém todos os livros da biblioteca.
	BOOL exit = FALSE; // Denota se o programa deve terminar.

	scanf("%d", &n); // Lê o número de livros e em seguida seus nomes e dias de aluguel máximo.
	books = (book_t *)malloc(n * sizeof(book_t));
	for (int i = 0; i < n; i++) {
		//books[i].name = (char *)malloc(CHUNK * sizeof(char));
		//scanf(" %[^(\r\n)]", books[i].name);
		books[i].name = readInput();
		scanf("%d", &books[i].days);
	}

	while (!exit) { // Repete enquanto o usuário não utilizar a opção 4.
		scanf("%d", &op);
		switch(op) {
			case 1: // Buscar um livro para alugar.
			{
				//char search[CHUNK];
				printf("Digite o livro que voce procura:\n");
				//scanf(" %[^(\r\n)]", search);
				char *search = readInput();
				int index = bookIndex(books, n, search);
				if (index >= 0)
					if (n_rented < 10)
						if (intIndex(index, index_rented, n_rented) < 0) {
							printf("%s alugado com sucesso\n", search);
							index_rented[n_rented++] = index; // Adiciona o índice de um livro como alguado.
						} else printf("Livro ja alugado\n");
					else printf("Voce ja tem 10 livros alugados\n");
				else printf("Livro nao encontrado na biblioteca\n");
				break;
			}
			case 2: // Mostrar livros alugados.
				if (n_rented > 0) {
					printf("Voce tem %d livro(s) alugado(s)\n", n_rented);
					for (int i = 0; i < n_rented; i++) {
						printf("Livro nome: %s\n", books[index_rented[i]].name);
						printf("Devolve-lo daqui %d dias\n", books[index_rented[i]].days);
					}
				} else printf("Voce nao tem livros alugados\n");
				break;

			case 3: // Devolver um livro.
			{
				//char name[CHUNK];
				printf("Digite o livro que deseja devolver:\n");
				//scanf(" %[^(\r\n)]", name);
				char *name = readInput();
				int index = bookIndex(books, n, name);
				int rent_index = intIndex(index, index_rented, n_rented);
				if (rent_index >= 0) {
					printf("Livro %s foi devolvido com sucesso\n", books[index].name);
					pop(rent_index, index_rented, n_rented--); // Remove o livro da lista de alugados.
				} else printf("Voce nao possui esse livro\n");
				break;
			}
			case 4: // Fechar o programa.
				printf("Programa finalizado\n");
				exit = TRUE;
		}
	}

	return 0;
}

BOOL strequal(char *str1, char *str2) {
	if (*str1 != '\0' && *str2 != '\0')
		if (*str1 == *str2) return strequal(str1 + 1, str2 + 1);
		else return FALSE;
	else return *str1 == *str2;
}
int intIndex(int value, int array[], int arr_len) {
	for (int i = 0; i < arr_len; i++)
		if (array[i] == value) return i;

	return -1;
}
int bookIndex(book_t *books, int n_books, char *name) {
	for (int i = 0; i < n_books; i++)
		if (strequal(books[i].name, name)) return i;

	return -1;
}
void pop(int index, int array[], int arr_len) {
	for (int i = index + 1; i < arr_len; i++)
		array[i - 1] = array[i];
}
// Retorna TRUE caso c seja uma caractere de término de entrada (no caso, linha).
BOOL endInput(char c) {
	return c == '\n' || c == '\r';
}
char *readInput() {
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = CHUNK + 1;
	char *string = (char *)malloc(allocated); // Aloca chunk de memória.
	char c = getchar();

	while(endInput(c)) c = getchar(); // Limpa o buffer de entrada.

	for (int i = 0; !endInput(c) && c != EOF; i++) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (i >= allocated - 1) {
			allocated += CHUNK;
			char *temp = (char *)realloc(string, allocated);
			// Caso o realloc mude o ponteiro de posição pois falhou em alocar
			// memória na mesma região, libera a memória alocada anteriormente.
			if (temp != string)
				free(string);

			string = temp;
		}
		string[i] = c; // Escreve a entrada na memória.
		c = getchar();

		if (endInput(c))
			string[i + 1] = '\0'; // Adiciona '\0' ao final.
	}
	return string;
}
