#include <stdio.h>
#include <math.h>

int main() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	if (a == 0 || b == 0 || c == 0) {
		printf("NAO");
		return 0;
	}

	// Se o triângulo é retângulo, então o teorema de pitágoras vale.
	// A hipotenusa de um triângulo é sempre o maior lado.
	int hi, ca, co;
	if (a > b) {
		if (a > c) {
		   	hi = a;
			ca = b;
			co = c;
		} else {
			hi = c;
			ca = a;
			co = b;
		}
	} else {
		if (b > c) {
			hi = b;
			ca = a;
			co = c;
		} else {
			hi = c;
			ca = a;
			co = b;
		}
	}

	// Soma dos quadrados dos catetos.
	double sq_sum = pow((double)ca, 2) + pow((double)co, 2); 
	// Quadrado da hipotenusa.
	double sq_hi = pow((double)hi, 2);
	
	double eps = 1e-7; // Valor muito pequeno para reduzir imprecisão de ponto flutuante.
	if (fabs(sq_sum - sq_hi) < eps)
		printf("SIM");
	else
		printf("NAO");

	return 0;
}
