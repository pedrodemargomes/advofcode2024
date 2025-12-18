#include <stdio.h>
#include <string.h>

struct array {
	unsigned long a[1000];
	unsigned long size;
};

void insert(struct array *a, unsigned long n) {
	a->a[a->size++] = n;
}

unsigned long isInArray(struct array *a, unsigned long n) {
	for (unsigned long i = 0; i < a->size; i++) {
		if (a->a[i] == n)
			return 1;
	}
	return 0;
}

unsigned long calc(struct array *eq, char *ops) {
	unsigned long sum = eq->a[0];
	for (unsigned long i = 0; i < eq->size-1; i++) {
		if (ops[i] == '+')
			sum += eq->a[i+1];
		else
			sum *= eq->a[i+1];
	}
	return sum;
}

void printeq(struct array *eq) {
	for (unsigned long i = 0; i < eq->size; i++)
		printf("%lu ", eq->a[i]);
	printf("\n");
}

unsigned long testeq(unsigned long result, struct array *eq, char *ops, unsigned long index) {
	if (index >= eq->size-1) {
		/*
		for (unsigned long i = 0; i < eq->size-1; i++)
			printf("%c ", ops[i]);
		printf("\n");
		*/


		if (result == calc(eq, ops))
			return 1;
		else
			return 0;
	}
	
	ops[index] = '+';
	if (testeq(result, eq, ops, index+1))
		return 1;
	ops[index] = '*';
	if (testeq(result, eq, ops, index+1))
		return 1;

	return 0;
}

int main(int argv, char *argc[]) {
	char ops[1000];
	char *line = NULL;
	size_t len = 0;
	unsigned long result;
	unsigned long sum = 0;
	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
		
		struct array eq = {.size = 0 };
		char *s = strtok(line, ": ");
		sscanf(s, "%lu", &result);
		s = strtok(NULL, ": ");
		while (s) {
			unsigned long n;
			sscanf(s, "%lu", &n);
			insert(&eq, n);
			s = strtok(NULL, ": ");
		}

		printf("eq.size: %lu\n", eq.size);	
		printeq(&eq);
		unsigned long n = testeq(result, &eq, ops, 0);
		printf("%lu\n", n);
		if (n)
			sum += result;
	}


	printf("sum: %lu\n", sum);
	
	return 0;
}



