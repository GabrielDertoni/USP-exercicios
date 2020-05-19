#include <stdio.h>
#include <stdlib.h>

void sortWith(void **begin, void **end, int (*compare)(void *a, void *b)) {
	// Range [start, end)
	// compare -> 1: a > b, -1: a < b, 0: a = b
	if (end - begin <= 1) return;

	void **p1 = begin + 1;
	void **p2 = end - 1;
	while(p1 != p2) {
		if (compare(*p1, *begin) > 0 && compare(*p2, *begin) <= 0) {
			void *temp = *p1;
			*p1 = *p2;
			*p2 = temp;
		}
		if (compare(*p1, *begin) <= 0) p1++;
		else if (compare(*p2, *begin) > 0) p2--;
	}
	if (compare(*p1, *begin) > 0) p1--;
	void *temp = *p1;
	*p1 = *begin;
	*begin = temp;
	sortWith(begin, p1, compare);
	sortWith(p1 + 1, end, compare);
}
