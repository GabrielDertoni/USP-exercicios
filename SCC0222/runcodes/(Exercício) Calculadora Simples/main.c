#include <stdio.h>

int main() {
	double a, b;
	char op;

	scanf("%lf %c %lf", &a, &op, &b);
	switch (op) {
		case '+':
			printf("%.6f", a + b);
		break;
		case '-':
			printf("%.6f", a - b);
		break;
		case '*':
			printf("%.6f", a * b);
		break;
		case '/':
			printf("%.6f", a / b);
		break;
		case '%':
			printf("%.6f", 100 * a / b);
		break;
	}

	return 0;
}
