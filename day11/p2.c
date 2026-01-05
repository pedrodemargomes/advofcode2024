#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 100000

struct array {
	unsigned long a[MAXSIZE];
	unsigned long size;
};

void insert(struct array *a, unsigned long n) {
	if (a->size >= MAXSIZE) {
		printf("array is full\n");
		return;
	}
	a->a[a->size++] = n;
}

void insertAt(struct array *a, unsigned long n, int index) {
	a->size++;
	for(int i = a->size-1; i > index; i--) {
		a->a[i] = a->a[i-1];
	}
	a->a[index] = n;
}

int numDigits(unsigned long n) {
	int i = 0;
	while (n) {
		n = n / 10;
		i++;
	}
	return i;
}

unsigned long firstHalf(unsigned long n) {
	int i = numDigits(n);
	i = i/2;
	for (int j = 0; j < i; j++)
		n = n / 10;
	return n;
}

unsigned long secondHalf(unsigned long n) {
	int i = numDigits(n);
	i = i/2;
	unsigned long h = 0;
	unsigned long p = 1;
	for (int j = 0; j < i; j++) {
		h += (n % 10)*p;
		p *= 10;
		n = n / 10;
	}
	return h;
}

struct array stones;
struct array stonesaux;
struct array newstones;
unsigned long *mem[76];

unsigned long blink(int step, unsigned long n) {
	if (!step)
		return 1;

	printf("n: %lu step: %d\n", n, step);
	if (n < 9000000000 && mem[step][n])
		return mem[step][n];
	unsigned long r = 0;

	if (n == 0)
		r += blink(step-1, 1);
	else if (numDigits(n) % 2 == 0) {
		r += blink(step-1, firstHalf(n));
		r += blink(step-1, secondHalf(n));
	} else 
		r += blink(step-1, n*2024);

	printf("n: %lu\n", n);
	if (n < 9000000000)
		mem[step][n] = r;
	return r;
}

void print(struct array *ar) {
	for(int i = 0; i < ar->size; i++)
		printf("%lu ", ar->a[i]);
	printf("\n");
}

int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;
	unsigned long n;


	for (int i = 0; i < 76; i++) {
		mem[i] = malloc(9000000000*sizeof(unsigned int));
		printf("%p\n", &mem[i]);
	}

	getline(&line, &len, stdin);

	char *s = strtok(line, " ");
	do {
		sscanf(s, "%lu", &n);
		insert(&stones, n);
		s = strtok(NULL, " ");
	} while (s);

	unsigned long count = 0;
	for (int i = 0; i < stones.size; i++) {
		printf("i: %d\n", i);
		count += blink(75, stones.a[i]);
	}

	//print(&stones);
	
	printf("\nsize: %lu\n", count);
	return 0;
}
