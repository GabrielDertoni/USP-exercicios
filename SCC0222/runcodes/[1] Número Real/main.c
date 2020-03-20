#include <stdio.h>
#include <math.h>

int main() {
	float num;
	scanf("%f", &num);

	printf("%d\n", (int)num);
	printf("%.4lf\n", num - floor(num));
	printf("%d\n", (int)roundf(num));

	return 0;
}
