#include <stdio.h>
#include <stdbool.h>

// Function that returns the length of a string.
int length(char *string) {
	int count = 0;
	while (string[count] != '\0') count++;
	return count;
}

// Function that returns the upper case of a character.
char toUpperCase(char c) {
	if (c >= 97) return c - 32;
	else return c;
}

// Function that returns if two strings are the same (not case-sensitive).
bool equal(char *str1, char *str2) {
	int i;
	for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
		if (toUpperCase(str1[i]) != toUpperCase(str2[i])) return false;

	return str1[i] == str2[i];
}

// Function that returns wich string comes before in the alphabetical order.
bool smaller(char *str1, char *str2) {
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (toUpperCase(str1[i]) < toUpperCase(str2[i]))
			return true;
		else if (toUpperCase(str1[i]) > toUpperCase(str2[i]))
			return false;

		i++;
	}
	return str1[i] == '\0';
}

// Function that returns the sum of the values of each character. (A = 0, Z = 25)
int sum(char *string) {
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++)
		count += toUpperCase(string[i]) - 'A';

	return count;
}

// Function that returns the number of times a given character appears in a string.
int occurrences(char *string, char c) {
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++)
		if (toUpperCase(string[i]) == toUpperCase(c)) count++;

	return count;
}

// Function that returns the first index of a character in a given string or -1 otherwise.
int indexOf(char *string, char c) {
	int i = 0;
	while (toUpperCase(string[i]) != toUpperCase(c) && string[i] != '\0') i++;
	if (string[i] != '\0') return i;
	else return -1;
}

int main() {
	int op;
	char w1[20], w2[20];

	scanf("%d %s %s", &op, w1, w2);

	switch(op) {
		case 1:
			if (length(w1) > length(w2)) printf("1");
			else if (length(w2) > length(w1)) printf("2");
			else printf("0");
		break;
		case 2:
			if (equal(w1, w2)) printf("0");
			else printf("%d", smaller(w1, w2) ? 1 : 2);
		break;
		case 3:
			if (sum(w1) > sum(w2)) printf("1");
			else if (sum(w2) > sum(w1)) printf("2");
			else printf("0");
		break;
		case 4:
		{
			char c;
			scanf(" %c", &c);
			if (occurrences(w1, c) > occurrences(w2, c)) printf("1");
			else if (occurrences(w1, c) < occurrences(w2, c)) printf("2");
			else printf("0");
		break;
		}
		case 5:
		{
			char c;
			scanf(" %c", &c);
			if (indexOf(w1, c) < indexOf(w2, c)) printf("1");
			else if (indexOf(w1, c) > indexOf(w2, c)) printf("2");
			else printf("0");
		}
	}

	return 0;
}
