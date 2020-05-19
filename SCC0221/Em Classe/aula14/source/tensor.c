#include <stdio.h>
#include <stdlib.h>
#include "../include/tensor.h"

data_t indexT(const tensor_t tensor, const int *indexes) {
	int idx;
	for (int i = 0; i < tensor.ndims; i++) {
		int mult = 1;
		for (int j = tensor.ndims - i - 1; j > i; j--) mult *= tensor.shape[j];
		idx += indexes[i] * mult;
	}
	return tensor.arr[idx];
}

data_t indexMat(const tensor_t tensor, const int row, const int col) {
	if (tensor.ndims != 2) {
		printf("Error: ndims must equal 2.");
		exit(EXIT_FAILURE);
	}
	int idxs[] = { row, col };
	return indexT(tensor, idxs);
}

int strcompare(char *str1, char *str2) {
	if (*str1 == '\0' && *str2 == '\0') return 0;
	if (*str2 == '\0' || *str1 > *str2) return 1;
	if (*str1 == '\0' || *str1 < *str2) return -1;
	return strcompare(str1 + 1, str2 + 1);
}

int compareTypes(data_t a, data_t b, type_t dtype) {
	switch (dtype) {
		case Int:
			if (a.i > b.i) return 1;
			if (a.i < b.i) return -1;
			return 0;
		case Long:
			if (a.li > b.li) return 1;
			if (a.li < b.li) return -1;
			return 0;
		case LongLong:
			if (a.lli > b.lli) return 1;
			if (a.lli < b.lli) return -1;
			return 0;
		case Float:
			if (a.f > b.f) return 1;
			if (a.f < b.f) return -1;
			return 0;
		case Double:
			if (a.lf > b.lf) return 1;
			if (a.lf < b.lf) return -1;
			return 0;
		case Char:
			if (a.c > b.c) return 1;
			if (a.c < b.c) return -1;
			return 0;
		case String:
			return strcompare(a.str, b.str);
		default:
			return -100;
	}
}

int intCompare(void *a, void *b) {
	data_t dataA = *(data_t *)a;
	data_t dataB = *(data_t *)b;
	return compareTypes(dataA, dataB, Int);
}

void *wrapDims(int ndims, int *shape, data_t *arr) {
	if (ndims == 0) {
		void *result = malloc(sizeof(data_t));
		result = (void *)arr;
		return result;
	}
	void **result = malloc(*shape * sizeof(void *));
	int mult = 1;
	for (int i = ndims - 1; i > 0; i--) mult *= shape[i];
	for (int i = 0; i < *shape; i++)
		result[i] = wrapDims(ndims - 1, shape + 1, arr + mult * i);

	return result;
}

void *tensorWrap(tensor_t tensor) {
	return wrapDims(tensor.ndims, tensor.shape, tensor.arr);
}
