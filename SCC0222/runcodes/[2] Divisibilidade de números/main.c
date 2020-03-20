#include <stdio.h>

int main() {
	int vec[31];
	for (int i = 0; i < 31; i++)
		scanf("%d", &vec[i]);

	for (int i = 0; i < 30; i++)
		if (vec[i] % vec[30] == 0) printf("%d\n", vec[i]);

	return 0;
}
