#include <stdio.h>
#include <math.h>

int main() {
	float a1, q, n;
	scanf("%f", &a1);
	scanf("%f", &q);
	scanf("%f", &n);

	float an = a1 * pow(q, n - 1);
	float sn = (a1 * (pow(q, n) - 1)) / (q - 1);
	printf("%.2f\n", an);
	printf("%.2f", sn);
	return 0;
}
