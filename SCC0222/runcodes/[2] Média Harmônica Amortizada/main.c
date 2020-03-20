#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);

	// Cálculo do denominador da equação de média harmônica amortizada.
	double den;
	for (int i = 0; i < n; i++) {
		double t;
		scanf("%lf", &t);
		den += 1 / (t + 1);
	}
	printf("%.2lf", n / den - 1);

	return 0;
}
