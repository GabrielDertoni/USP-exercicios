#include <stdio.h>
#include <stdlib.h>

#define BOOL int // Define que o "tipo" booleano na verdade é um inteiro.
#define FALSE 0 // Define valor de false.
#define TRUE 1 // Define valor de true.
#define CHUNK 10 // Define o tamanho dos pedaços na qual a memória deve ser alocada.

BOOL endInput(char c); // Retorna se a caracter é um indicador de final de entrada.
char *readInput(); // Lê uma entrada inteira como uma string.
int strLength(char *str); // Mede o comprimento da string.
int power(int a, int b); // calcula a^b.
double floorDouble(double val); // Arredonda para baixo um double.
double absDouble(double val); // Calcula o valor absoluto de um double.

// Lê um inteiro da entrada padrão.
int readInt() {
	char *input = readInput();
	int len = strLength(input);
	int result = 0;
	int i, sign;

	if (input[0] == '-') {
		i = 1;
		sign = -1;
	} else {
		i = 0;
		sign = 1;
	}
	// Compõe o número a partir da entrada.
	for (; i < len; i++)
		result += sign * (input[i] - 48) * power(10, len - i - 1);

	return result;
}

// Lê um double da entrada padrão.
double readDouble() {
	char *input = readInput(); // Entrada como string.
	int len = strLength(input);
	int i, sign, decimal;
	double result;

	if (input[0] == '-') {
		i = 1;
		sign = -1;
	} else {
		i = 0;
		sign = 1;
	}

	// Encontra a posição do '.'
	for (decimal = 0; input[decimal] != '.' && decimal < len; decimal++);

	// Compõe o número a partir da entrada.
	for (result = 0; i < len; i++)
		if (i < decimal)
			result += sign * (input[i] - 48) * power(10, decimal - i - 1);
		else if (i > decimal)
			result += sign * ((double)(input[i] - 48) / (double)power(10, i - decimal));

	return result;
}

// Imprime um inteiro. Apesar de não ser uma função requisitada, ela compõe printDouble(),
// o que a torna necessária. int log representa o número de casas (na prática seria o
// log10(val) arredondado para cima) que devem ser impressas. Caso seja menor ou igual a 0,
// a função utilizará o mínimo número possível de casas.
void printInt(int val, int log) {
	// Se o número for negativo, coloque o sinal de negativo na tela.
	if (val < 0) putc('-', stdout);

	// Calcula a magnetude do número, 123 possui magnetude 100, por exemplo.
	int mag;
	if (log <= 0)
		for (mag = 1; abs(val) >= mag * 10; mag *= 10);
	else
		 mag = power(10, log - 1);

	// A cada iteração, imprime a casa mais significativa, depois a próxima, ...
	for (int n = abs(val); mag > 0; n %= mag, mag /= 10)
		putc((n / mag) % 10 + 48, stdout); // Imprime o digito atual mais significativo
}

// Imprime um valor double na tela com duas casas de precisão.
void printDouble(double val) {
	// Se o número for negativo, coloque o sinal de negativo na tela.
	if (val < 0) putc('-', stdout);

	// Torna o número que será impresso como inteiro (deixa tod depois da vírgula).
	double decimal = absDouble(val) * 100;
	// Arredonda o número para duas casas decimais.
	if (decimal - floorDouble(decimal) >= 0.5) decimal++;

	printInt((int)decimal / 100, -1); // Imprime a parte inteira.
	putc('.', stdout);
	printInt((int)decimal % 100, 2); // Imprime a parte decimal.
}

int main(int argc, char *argv[]) {
	int n = readInt();

    // Cálculo do denominador da equação de média harmônica amortizada.
	double den = 0;
	for (int i = 0; i < n; i++) {
		double t;
		t = readDouble();
		den += 1 / (t + 1); 
	}
	printDouble(n / den - 1);

	return 0;
}

// Função que retorna o floor() do double fornecido. A implementação é exagerada e
// provavelmente ineficiente, mas foi uma boa oportunidade para aplicar os conhecimentos
// sobre o protocolo IEEE 754. Para poder manipular um double bit a bit, memória na heap
// é alocada e ponteiros de tipos diferentes apontam para essa memória sendo que o de
// tipo long int pode alterar os bits de forma individual.
double floorDouble(double val) {
	void *p = malloc(sizeof(double)); // Aloca memória na heap.
	long int *lip = (long int *)p; // Ponteiro p interpretado como long int *
	double *dp = (double *)p; // Ponteiro p interpretado como double *

	*dp = val; // Através da interpretação em double, armazena o valor na memória alocada.

	// Separa a parte do sinal do double.
	long int s = *lip & 0x8000000000000000;

	// Pega somente os bits do expoente do double.
	long int e = *lip & 0x7ff0000000000000;
	// Desloca os bits para que fiquem logo no começo do número.
	e = e >> 52;
	// Subrai 1023 do expoente para obter seu real valor.
	e = e - 0x3ff;

	// Caso o expoente seja positivo (existem números antes da vírgula)
	// pegue somente esses números antes da vírgula
	if (e > 0) {

		// Prepara uma máscara binária com a quantidade de bits expressada
		// pelo expoente.
		long int mask = 0;
		for (int i = 0; i < e; i++) {
			long int temp = 1;
			mask += temp << i;
		}
		// Desloca a máscara para o canto esquerdo da mantissa.
		mask = mask << (52 - e);

		// Guarda na memória as casas antes da vírgula mascaradas juntamente
		// com o expoente original (adicionado com o bitwise or).
		*lip = ((*lip) & mask) | ((e + 0x3ff) << 52);

		// Restitui o sinal ao número.
		*lip = *lip | s;

		// Armazena o resultado em outra varíavel para que a memória possa ser liberada.
		double result = *dp;
		free(p); // Garante que memória alocada, será liberada.

		return result; // Retorna o resultado.
	}

	// Se o expoente estiver zerado, significa que o valor é 1 ou -1.
   	if (e == 0) {
		free(p); // Libera a memória.
		// Verifica o bit de sinal para saber se ele está setado para 1 ou 0.
		if (s >> 63) return -1;
		return 1;
	}

	free(p); // Libera a memória.
	return 0; // Como não há casas antes da vírgula, retorne 0.
}

double absDouble(double val) {
	return val < 0 ? -val : val;
}

BOOL endInput(char c) {
	return c == '\n' || c == '\r' || c == ' ' || c == EOF;
}

// Armazena os conteúdos da entrada padrão numa string. Essa string é alocada
// de forma dinâmica, entretanto, não há como garantir que essa alocação será
// exatamente do tamanho da entrada, portanto, até para precisar de menos 
// utilizações do realloc, a memória é alocada em pedaços de tamanho fixo
// (tamanho setado em CHUNK). Portanto, o máximo de memória que pode ficar sem
// utilização é CHUNK - 1, ao benefício de menos realloc().
char *readInput() {
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = CHUNK + 1;
	char *string = (char *)malloc(allocated); // Aloca chunk de memória.
	char c = getc(stdin);

	while(endInput(c)) c = getc(stdin);

	for (int i = 0; !endInput(c); i++) {
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
		c = getc(stdin);

		if (endInput(c))
			string[i + 1] = '\0'; // Adiciona '\0' ao final.
	}
	return string;
}

int strLength(char *str) {
	int len;
	for (len = 0; str[len] != '\0'; len++);
	return len;
}

int power(int a, int b) {
	int result = 1;
	for (int i = 0; i < b; i++) result *= a;
	return result;
}
