#include <stdio.h>
#include <string.h>

#define ABS(x) ((x)<0)? (-(x)):(x) 

void qsort(int *v, int begin, int end) {
	if (end - begin <= 1)
		return;

	int j = begin;
	int piv = v[end-1];
	printf("piv: %d\n", piv);
	for(int i = begin; i < end-1; i++) {
		if (v[i] <= piv) {
			int aux = v[j];
			v[j] = v[i];
			v[i] = aux;
			j++;
		}
	}
	int aux = v[j];
	v[j] = v[end-1];
	v[end-1] = aux;
	
	qsort(v, begin, j);
	qsort(v, j+1, end);
}

int hash[99999];

int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;
	int count = 0;
	int l1[1000], l2[1000];

	int i = 0;
	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
		sscanf(line, "%d   %d", &l1[i], &l2[i]);
		i++;
	}


	for(int j = 0; j < i; j++) {
		hash[l2[j]]++;
	}

	for(int j = 0; j < i; j++) {
		count += l1[j]*hash[l1[j]];
	}

	printf("count = %d\n", count);
	return 0;
}



