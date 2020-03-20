#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
	for (int i = 2; i < (int)sqrt((double)n); i++) {
		if (n % i == 0) return false;
	}
	return true;
}

int next_prime(int n) {
	int i = n == 2 ? n + 1 : n + 2;
	// Como o primeiro número primo é o 2, n só pode assumir o valor de, pelo
	// menos 2. Isso significa que o retorno da função será um número maior 
	// que 2. Entretanto, todos os outros primos são ímpares, ou seja, i pode
	// pular os números pares, por isso i += 2.
	while(!is_prime(i)) i += 2;
	return i;
}

int main() {
	int n;
	scanf("%d", &n);

	for (int p = 2; n != 1; p = next_prime(p)) {
		int count;
		for (count = 0; n % p == 0; count++) n /= p;
		if (count > 0) printf("%d %d\n", p, count);
	}

	return 0;
}
