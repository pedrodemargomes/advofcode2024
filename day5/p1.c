#include <stdio.h>
#include <string.h>

struct array {
	int a[100];
	int size;
};

void insert(struct array *a, int n) {
	a->a[a->size++] = n;
}

int isInArray(struct array *a, int n) {
	for (int i = 0; i < a->size; i++) {
		if (a->a[i] == n)
			return 1;
	}
	return 0;
}

struct array rules[100];
int nums[1000];

int check() {
	for (int i = 0; nums[i] != -1; i++) {
		if (rules[nums[i]].size == 0)
			continue;
		//printf("i: %d rule: %d\n", i, rules[nums[i]].size);
		int found = 0;
		for (int j = i+1; nums[j] != -1; j++) {
			//printf("j: %d\n", j);
			if ( isInArray(&rules[nums[i]], nums[j])) {
				found = 1;
				break;
			}
		}
		if (found)
			return 0;
	}
	return 1;
}

int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;

	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
		int a, b;
		sscanf(line, "%d|%d", &a, &b);
		insert(&rules[b], a);

	}

	int sum = 0;
	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;

		int j = 0;	
		char *s = strtok(line, ",");
		while (s) {
			int n;
			sscanf(s, "%d", &n);
			nums[j++] = n;
			s = strtok(NULL, ",");
		}
		nums[j++] = -1;

		for (int k = 0; k < 10; k++)
			printf("%d ", nums[k]);
		printf("\n");
		
		if (check()) {
			printf("valid\n");
			int k;
			for (k = 0; nums[k] != -1; k++) {}
			sum += nums[k/2];
		
		} else 
			printf("invalid\n");
	}


	printf("sum: %d\n", sum);
	return 0;
}



