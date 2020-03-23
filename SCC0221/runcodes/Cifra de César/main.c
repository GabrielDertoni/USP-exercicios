#include <stdio.h>

int main(int argc, char *argv[]) {
	/* 
	 * Algorítmo para criptografar e decriptografar mensagens de acordo com a cifra
	 * de César.
	 *
	 * Presupostos do programa: A mensagem deve se resumir a apenas caracteres presentes
	 * na tabela ASCII. Caracteres não de a-z ou A-Z não serão convertidos na cifra.
	 *
	 * Detalhes da implementação: para calcular um valor de 0 a 25 com base na caracter
	 * independente de ser maiúscula ou minúscula, o método utilizado leva vantagem da
	 * forma como o protocolo ASCII funciona. Como 01000001 corresponde a 'A' e 01100001
	 * corresponde a 'a', fica claro que o terceiro bit da esquerda para a direita controla
	 * se a caractere é maiúscula ou minúscula. Ou seja, ao fazer um 01100001 & 00011111,
	 * por exemplo, eliminamos esses três primeiros bits da frente e o resultado será 00000001.
	 * Portanto, 65 & 31 = 1 e 97 & 31 = 1. Dessa forma pode-se transformar qualquer caractere
	 * num número que a representa de 1 a 26. Para converter, após a cifra, de volta para
	 * uma caractere maiúscula ou minúscula (o que depende da caractere original), basta fazer
	 * o contrário, 01100001 & 01100000 = 01100000 ou 01000001 & 01100000 = 01000000, ou seja,
	 * agora os três primeiros bits foram isolados. Por fim, basta fazer um or entre o resultado
	 * da cifra (número de 1 a 26) e (<caractere> & 96). Dessa forma, por exemplo:
	 * 00000101 | (01100011 & 01100000) = 011000101, ou seja, adicionamos os três primeiros bits
	 * da caractere original (que diz se ela é maiúscula ou não) aos bits finais do resultado da
	 * cifra. Conversões similares ocorrem ao decriptografar a cifra.
	 */
	int mode, key; // Armazenam se o programa vai decriptografar ou criptografar
	               // e também a chave de criptografia para essa operação.
	char c;

	scanf("%d %d ", &mode, &key);
	// Laço de repetição que itera por todas as caracteres na entrada.
	for (c = getc(stdin); c != '\n' && c != '\r' && c != '\0' && c != EOF; c = getc(stdin))
		// Apenas converter o caracter se ele for entre A-Z ou a-z
		if ((c >= 65 && c <= 90) || (c >= 97 && c <= 123))
			if (mode == 1)
				// Se o modo for 1 (criptografar): calcular o valor da caracter (de 0 a 25), adicionar
				// a chave, garantir que o resultado será menor ou igual a 25 ( % 26), converter
				// novamente na tabela ASCII para caracter.
				putc((((c & 31) - 1 + key) % 26 + 1) | (c & 96), stdout);
			else
				// Se o modo for 2 (decriptografar): se a chave for muito grande e ouver necessidade
				// de começar a partir de z para baixo, imprimir <caracter> - <chave> + 26. Se não
				// imprimir <caracter> - <chave>.
				putc((c & 31) - 1 < key ? c - key + 26 : (((c & 31) - 1 - key) % 26 + 1) | (c & 96), stdout);
		else
			// Caso qualquer outro caracter seja lido, imprime ele sem alteração.
			putc(c, stdout);

	return 0;
}
