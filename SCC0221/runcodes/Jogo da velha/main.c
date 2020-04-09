#include <stdio.h>

#define CELL int

#define NONE 0 // 0 -> lugar não preenchido
#define X 1 // 1 -> X (jogada do jogador 1)
#define O 2 // 2 -> O (jogada do jogador 2)
#define TIE 3

CELL gameWinner(CELL state[3][3]);
void printGame(CELL state[3][3]);

int main(int argc, char *argv[]) {
	// Inicializa o tabuleiro em branco
	CELL state[3][3];
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			state[row][column] = NONE;
	
	printGame(state);
	printf("Jogo da velha!\n");

	CELL turn; // Armazena o número do jogador da vez.
	CELL winner;
	for (winner = NONE, turn = X; winner == NONE; winner = gameWinner(state)) {
		printf("Escolha um número para jogar, jogador %c!\n", turn == X ? 'X' : 'O');
		int play; // Armazena a jogada feita.
		do {
			scanf(" %d", &play);
			play--; // o número da jogada pode ser de 1 a 9, mas em programa, é mais
			        // utilizar números de 0 a 8 para isso.
			if (state[play / 3][play % 3] != NONE)
				printf("Jogada inválida! Escolha outra casa.\n");

		} while(state[play / 3][play % 3] != NONE); // Garante que a jogada será feita em
		                                            // alguma casa livre.
		state[play / 3][play % 3] = turn; // Registra a jogada.

		// Atualiza a vez dos jogadores.
		if (turn == X) turn = O;
		else turn = X;

		printGame(state);
	}

	if (winner == TIE)
		printf("Deu velha!");
	else
		printf("Fim do jogo! O jogador %c venceu!", winner == X ? 'X' : 'O');

	return 0;
}

CELL gameWinner(CELL state[3][3]) {
	// Verifica se algum jogador ganhou com uma linha.
	for (int row = 0; row < 3; row++)
		if (state[row][0] != NONE &&
			state[row][0] == state[row][1] &&
			state[row][0] == state[row][2])
			return state[row][0];

	// Verifica se algum jogador ganhou com uma coluna.
	for (int column = 0; column < 3; column++)
		if (state[0][column] != NONE &&
			state[0][column] == state[1][column] &&
			state[0][column] == state[2][column])
			return state[0][column];

	// Verifica se algum jogador ganhou com uma diagonal.
	if (state[0][0] != NONE
		&& state[0][0] == state[1][1]
		&& state[0][0] == state[2][2])
		return state[0][0];

	if (state[0][2] != NONE
		&& state[0][2] == state[1][1]
		&& state[0][2] == state[2][0])
		return state[0][2];

	// Verifica se ainda há casas vazias para se jogar.
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			if (state[row][column] == NONE) return NONE;

	// Se não há vencedores, mas todas as casas estão ocupadas, é um empate.
	return TIE;
}

void printGame(CELL state[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++)
			if (state[row][column] == NONE)
				printf("%d   |", row * 3 + column + 1);
			else if (state[row][column] == X)
				printf("X   |");
			else
				printf("O   |");

		printf("\n----+----+-----\n");
	}
}
