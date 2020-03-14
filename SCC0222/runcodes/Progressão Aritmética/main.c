#include <stdio.h>

int main() {
	long int a1, r, n;
	scanf("%ld", &a1);
	scanf("%ld", &r);
	scanf("%ld", &n);

	long int an = a1 + r * (n - 1);
	long int sn = ((a1 + an) * n) / 2;
	printf("%ld\n", an);
	printf("%ld\n", sn);
	return 0;
}
