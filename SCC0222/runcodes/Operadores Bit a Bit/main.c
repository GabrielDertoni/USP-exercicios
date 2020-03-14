#include <stdio.h>

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	
	printf("%d\n", a & b); // Bitwise AND
	printf("%d\n", a | b); // Bitwise OR
	printf("%d\n", a ^ b); // Bitwise XOR
	printf("%d\n", ~a); // Bitwise Complement (a)
	printf("%d\n", ~b); // Bitwise Complement (b)
	printf("%d\n", a >> 2); // Bitwise shift right
	printf("%d\n", b << 2); // Bitwise shift left

	return 0;
}
