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

int numLines;
int table[1000][100];

int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;
	int count = 0;

	int i = 0;
	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
		int j = 0;
		char *s = strtok(line, " ");
		while (s) {
			sscanf(s, "%d", &table[i][j]);
			s = strtok(NULL, " ");
			j++;
		}
		table[i][j] = -1;
		i++;
	}
	numLines = i;

	for(int i = 0; i < numLines; i++) {
		int j = 1;
		int sent = -10000;
		int safe = 1; 
		while (table[i][j] != -1) {
			int dif = ABS(table[i][j]-table[i][j-1]);
			if (sent == -10000)
				sent = table[i][j]-table[i][j-1];
			else {
				if ( (sent > 0 && table[i][j]-table[i][j-1] < 0) || (sent < 0 && table[i][j]-table[i][j-1] > 0) ) {
					safe = 0;
					break;
				}
			}
			if (dif < 1 || dif > 3) {
				safe = 0;
				break;
			}
			j++;
		}
		if (safe) {
			printf("safe\n");
			count++;
		} else
			printf("unsafe\n");
	}

	printf("count = %d\n", count);
	return 0;
}



