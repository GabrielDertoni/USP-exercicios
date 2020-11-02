#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// Macro para parsing
#define LN "\r\n"
// Macro para quantidade de alocação.
#define CHUNK 32
// Macros para obter valor mínimo e máximo.
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
// Macros para booleano.
#define BOOL short int
#define TRUE 1
#define FALSE 0

// Ordena um vetor de strings usando quick sort.
void sort(char **begin, char **end);
// Verifica se uma string é palíndromo.
BOOL isPalindrome(char *str);
// Calcula a similaridade entre duas palavras.
int wordSimilarity(char *str1, char *str2);
// Se size <= allocated, realoque a memória apontada por ptr. Retorna
// o novo tamanho alocado.
int maybeReallocate(void **ptr, int size, int allocated);
// Lê sem gravar na memória uma sequência de caracteres que estejam
// contidas em chars. Retorna o número de caracteres ignoradas.
int ignoreSome(char *chars, FILE *fp);
// Lê e armazena dinamicamente caracteres até que um caracter que 
// esteja contido em stop seja encontrado. Retorna o que foi lido.
char *readUntil(char *stop, FILE *fp);
// Lê uma linha (até encontrar um \n, \r ou EOF)
char *readLine(FILE *fp);

int main(int argc, char *argv[]) {
	// Lê o nome do arquivo de entrada.
	char *fname = readLine(stdin);
	FILE *fp = fopen(fname, "r");
	// Garante que o arquivo existe e pode ser aberto.
	if (!fp) {
		fprintf(stderr, "Erro: Arquivo não encontrado.\n");
		exit(EXIT_FAILURE);
	}

	// Lê os padrões regex e a palavra.
	char *patt1 = readLine(stdin);
	char *patt2 = readLine(stdin);
	char *patt3 = readLine(stdin);
	char *word  = readLine(stdin);

	// Compila todas as expreções regulares.
	regex_t exp1, exp2, exp3;
	if (regcomp(&exp1, patt1, REG_EXTENDED)) {
		fprintf(stderr, "Erro: patt1 não pode ser compilado.\n");
		exit(EXIT_FAILURE);
	}
	if (regcomp(&exp2, patt2, REG_EXTENDED)) {
		fprintf(stderr, "Erro: patt2 não pode ser compilado.\n");
		exit(EXIT_FAILURE);
	}
	if (regcomp(&exp3, patt3, REG_EXTENDED)) {
		fprintf(stderr, "Erro: patt3 não pode ser compilado.\n");
		exit(EXIT_FAILURE);
	}

	// Variáveis que armazenam os valores que devem ser impressos.
	int npalindromes = 0, npatt1 = 0, closest_score = 0;
	char *longest = NULL, *shortest = NULL, *closest = NULL, *longestp2 = NULL;
	int np3words = 0, p3allocated = 0; // Garantem alocação dinâmica para p3words.
	char **p3words = NULL; // Vetor de strings com todas as ocorrências de P3
	// Garantem que todas as linhas lidas podem ser armazenadas na Heap dinamicamente.
	char *line;
	int nlines, allocated;
	char **lines = NULL;
	// Lê todas as linhas do arquivo de entrada (para quando readLine() retorna "")
	for(nlines = 0; strlen(line = readLine(fp)); nlines++) {
		// Atualiza todas as variáveis com os valores a serem impressos para cada nova leitura.

		if (!longest || strlen(line) > strlen(longest))
			longest = line;
		
		if (!shortest || strlen(line) < strlen(shortest))
			shortest = line;
		
		// Atualiza a palavra mais próxima de word caso: nenhuma palavra ainda tenha sido definida,
		// uma plavra mais próxima de acordo com sua pontuação de similaridade seja encontrada ou
		// uma plavra com a mesma pontuação de similaridade seja encontrada entretanto a nova palavra
		// for menor que a anterior.
		if (!closest ||
			closest_score < wordSimilarity(line, word) ||
			(closest_score == wordSimilarity(line, word) && strlen(closest) > strlen(line)))
		{
			closest = line;
			closest_score = wordSimilarity(closest, word);
		}

		if (isPalindrome(line)) npalindromes++;

		if (!regexec(&exp1, line, 0, NULL, 0)) npatt1++;

		if (!regexec(&exp2, line, 0, NULL, 0) &&
			(!longestp2 || strlen(line) > strlen(longestp2)))
			longestp2 = line;

		if (!regexec(&exp3, line, 0, NULL, 0)) {
			p3allocated = maybeReallocate((void **)&p3words, np3words * sizeof(char *), p3allocated);
			p3words[np3words++] = line;
		}
		allocated = maybeReallocate((void **)&lines, nlines * sizeof(char *), allocated);
		lines[nlines] = line;
	}
	lines = (char **)realloc(lines, nlines * sizeof(char *));
	// Ordena as palavras dentro do vetor p3words.
	sort(p3words, p3words + np3words);
	// Imprime as informações requisitadas.
	printf("%d\n", nlines);
	printf("%s\n", shortest ? shortest : "");
	printf("%s\n", longest ? longest : "");
	printf("%d\n", npatt1);
	printf("%d\n", npalindromes);
	printf("%s\n", longestp2 ? longestp2 : "");
	for (int i = 0; i < np3words; i++) printf("%s\n", p3words[i]);
	printf("%s\n", closest ? closest : "");

	fclose(fp);
	free(fname);
	free(patt1);
	free(patt2);
	free(patt3);
	free(word);
	regfree(&exp1);
	regfree(&exp2);
	regfree(&exp3);
	// Libera todas as linhas em lines. Isso inclui todos o endereço de memória
	// que shortest, longest, longestp2, closest ou qualquer elemento de p3words
	// possa apontar.
	while(--nlines) free(lines[nlines]);
	free(lines);
	free(p3words);

	return EXIT_SUCCESS;
}

BOOL isPalindrome(char *str) {
	int len = strlen(str), i;
	for (i = 0; i < len / 2 && str[i] == str[len - i - 1]; i++);
	return i == len / 2;
}

// Para um determinado offset em str2, calcular o número de caracteres iguais e na mesma posição
// entre str1 e str2.
int wordOffsetScore(char *str1, char *str2, int offset) {
	int score = 0;
	for (int i = offset; i < MIN(strlen(str1), offset + strlen(str2)); i++)
		if (str1[i] == str2[i - offset]) score++;
	return score;
}

// Calcula a similaridade entre duas palavras, isto é, o maior número de caracteres iguais e na
// mesma posição para todos os possíveis offsets (positivos) de str2.
int wordSimilarity(char *str1, char *str2) {
	int score = 0;
	for (int i = 0; i < strlen(str1); i++)
		score = MAX(score, wordOffsetScore(str1, str2, i));

	return score;
}

int maybeReallocate(void **ptr, int size, int allocated) {
	if (size >= allocated) {
		if ((allocated *= 2) <= 0) allocated = CHUNK;
		*ptr = realloc(*ptr, allocated);
	}
	return allocated;
}

int ignoreSome(char *chars, FILE *fp) {
	char c; int i;
	for (i = 0; !feof(fp) && strchr(chars, c = getc(fp)); i++);
	ungetc(c, fp);
	return i;
}

char *readUntil(char *stop, FILE *fp) {
	char c;
	int i, allocated;
	char *string = NULL;
	for (i = 0, allocated = 0; !feof(fp) && !strchr(stop, c = getc(fp)); i++) {
		allocated = maybeReallocate((void **)&string, i, allocated - 1);
		string[i] = c;
	}
	if (allocated == 0) return "";
	ungetc(c, fp);
	string[i] = '\0';
	return (char *)realloc(string, (i + 1) * sizeof(char));
}

char *readLine(FILE *fp) {
	ignoreSome(LN, fp); // Ignora alguns \r ou \n
	return readUntil(LN, fp); // Retorna que for lido até o próximo \r, \n ou EOF
}

// Implementação de quick sort. begin deve ser um ponteiro para o primeiro elemento
// do vetor, end deve ser um ponteiro para a posição após o último elemento do vetor.
void sort(char **begin, char **end) {
	// Range [start, end)
	if (end - begin <= 1) return;

	char **p1 = begin + 1;
	char **p2 = end - 1;
	while(p1 != p2) {
		if (strcmp(*p1, *begin) > 0 && strcmp(*p2, *begin) <= 0) {
			char *temp = *p1;
			*p1 = *p2;
			*p2 = temp;
		}
		if (strcmp(*p1, *begin) <= 0) p1++;
		else if (strcmp(*p2, *begin) > 0) p2--;
	}
	if (strcmp(*p1, *begin) > 0) p1--;
	char *temp = *p1;
	*p1 = *begin;
	*begin = temp;
	sort(begin, p1);
	sort(p1 + 1, end);
}
