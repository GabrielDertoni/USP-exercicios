#include <stdio.h>

double min(double a, double b) {
	if (a < b) return a;
	else return b;
}
int main() {
	double a, b, c, d;
	scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

	// Encontra o menor dos valores e subtrai da soma dos elementos antes da divisão para a média
	double res = (a + b + c + d - min(min(a, b), min(c, d))) / 3;
	printf("%.4lf", res);

	return 0;
}
