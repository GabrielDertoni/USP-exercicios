#include <stdio.h>
#include <stdlib.h>

void sortInts(int *begin, int *end);
int *binaryIntSearch(int *begin, int *end, int key);
int *readIntList(int len);

int main(int argc, char *argv[]) {
	int len, key;
	scanf("%d %d", &len, &key);

	int *vec = readIntList(len);
	sortInts(vec, vec + len);
	int *result = binaryIntSearch(vec, vec + len, key);

	if (!result)
		printf("Chave inexistente\n");
	else
		printf("%d\n", (int)(result - vec));

	free(vec);
	
	return EXIT_SUCCESS;
}

int *readIntList(int len) {
	int *vec = (int *)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++)
		scanf("%d", &vec[i]);

	return vec;
}

void sortInts(int *begin, int *end) {
	// Range [start, end)
	// compare -> 1: a > b, -1: a < b, 0: a = b
	if (end - begin <= 1) return;

	int *p1 = begin + 1;
	int *p2 = end - 1;
	while(p1 != p2) {
		if (*p1 > *begin && *p2 <= *begin) {
			int temp = *p1;
			*p1 = *p2;
			*p2 = temp;
		}
		if (*p1 <= *begin) p1++;
		else if (*p2 > *begin) p2--;
	}
	if (*p1 > *begin) p1--;
	int temp = *p1;
	*p1 = *begin;
	*begin = temp;
	sortInts(begin, p1);
	sortInts(p1 + 1, end);
}

int *binaryIntSearch(int *begin, int *end, int key) {
	// Range [start, end)
	if (begin == end) return NULL;
	// Gambiarra equivalente a (start + end) / 2
	int *middle = begin + (int)(end - begin) / 2;
	if (*middle == key)
		return middle;
	else if (*middle > key)
		return binaryIntSearch(begin, middle, key);
	else
		return binaryIntSearch(middle + 1, end, key);
}
