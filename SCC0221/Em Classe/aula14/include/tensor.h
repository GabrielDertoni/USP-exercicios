#ifndef _TENSOR_H_
#define _TENSOR_H_

typedef union {
	int i;
	long li;
	long long lli;
	float f;
	double lf;
	char c;
	char *str;
} data_t;

typedef enum {
	Void,
	Int,
	Long,
	LongLong,
	Float,
	Double,
	Char,
	String
} type_t;

typedef struct {
	int ndims;
	int *shape;
	type_t dtype;
	data_t *arr;
} tensor_t;


data_t indexT(const tensor_t tensor, const int *indexes);
data_t indexMat(const tensor_t tensor, const int row, const int col);
int strcompare(char *str1, char *str2);
int compareTypes(data_t a, data_t b, type_t dtype);
int intCompare(void *a, void *b);

#endif
