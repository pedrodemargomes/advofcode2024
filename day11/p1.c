#include <stdio.h>
#include <string.h>

struct array {
	unsigned long a[1000000];
	int size;
};

void insert(struct array *a, unsigned long n) {
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

void blink() {
	struct array newstones = {.size = 0};
	for (int i = 0 ; i < stones.size; i++) {
		printf("%lu\n", stones.a[i]);
		if (stones.a[i] == 0)
			insert(&newstones, 1);
		else if (numDigits(stones.a[i]) % 2 == 0) {
			insert(&newstones, firstHalf(stones.a[i]));
			insert(&newstones, secondHalf(stones.a[i]));
		} else 
			insert(&newstones, stones.a[i]*2024);

	}

	memcpy(&stones, &newstones, sizeof(struct array));
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

	getline(&line, &len, stdin);

	char *s = strtok(line, " ");
	do {
		sscanf(s, "%lu", &n);
		insert(&stones, n);
		s = strtok(NULL, " ");
	} while (s);

	for (int i = 0; i < 25; i++)
		blink();	

	print(&stones);
	
	printf("\nsize: %d\n", stones.size);
	return 0;
}
