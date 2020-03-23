#include <stdio.h>

int main(int argc, char *argv[]) {
	/* 
	 * Algorítmo para criptografar e decriptografar mensagens de acordo com a cifra
	 * de César.
	 * Presupostos do programa: A mensagem deve se resumir a apenas caracteres presentes
	 * na tabela ASCII. Caracteres não de a-z ou A-Z não serão convertidos na cifra.
	 */
	int mode, key; // Armazenam se o programa vai decriptografar ou criptografar
	               // e também a chave de criptografia para essa operação.
	char c; // Próxima caracter lida.
	int conv; // Número que armazena o fator de conversão (necessário para incluir o caso
	          // de caracteres maiúsculas). Essa variável assumirá valor 96 se c for minúscula
			  // e 64 se for maiúscula. Dessa forma, é possivel converter facilmente de qualquer
			  // c para um valor de 0 a 25 representando a caracter.

	scanf("%d %d ", &mode, &key); // Lê o modo e a chave da entrada padrão. (o " " ao fim
	                              // limpa a entrada padrão do próximo \n, \r e/ou \0

	// For roda enquanto não houver terminador de string (\n \r \0) e em cada iteração lê
	// uma nova caracter da entrada padão. 
	for (c = getc(stdin); c != '\n' && c != '\r' && c != '\0' && c != EOF; c = getc(stdin))
		// Apenas converter o caracter se ele for entre A-Z ou a-z
		if ((c >= 65 && c <= 90) || (c >= 97 && c <= 123))
			if (mode == 1)
				// Se o modo for 1 (criptografar): calcular o valor da caracter (de 0 a 25), adicionar
				// a chave, garantir que o resultado será menor ou igual a 25 ( % 26), converter
				// novamente na tabela ASCII para caracter.
				putc(((c & 31) - 1 + key) % 26 + 1 | (c & 96), stdout);
			else
				// Se o modo for 2 (decriptografar): se a chave for muito grande e ouver necessidade
				// de começar a partir de z para baixo, imprimir <caracter> - <chave> + 26. Se não
				// imprimir <caracter> - <chave>.
				putc((c & 31) - 1 < key ? c - key + 26 : ((c & 31) - 1 - key) % 26 + 1 | (c & 96), stdout);
		else
			// Caso qualquer outro caracter seja lido, imprime ele sem alteração.
			putc(c, stdout);

	return 0;
}
