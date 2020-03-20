#include <stdio.h>

double power(double a, int b) {
	int abs_b = b < 0 ? -b : b;
	double result = 1;
	for (int i = 0; i < abs_b; i++)
		result *= a;

	if (b < 0) return 1 / result;
	else return result;
}

int main() {
	double a;
	int b;
	scanf("%lf %d", &a, &b);

	printf("%.4lf", power(a, b));

	return 0;
}
