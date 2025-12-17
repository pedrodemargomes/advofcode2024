#include <stdio.h>
#include <string.h>

int count = 0;
int numLines;
int numCol;
char table[1000][1000];

void print() {
	printf("table: numLines %d numCol: %d\n", numLines, numCol);
	for (int i = 0 ; i < numLines; i++)
		printf("%s", table[i]);
}

int check(int ii, int jj) {
	if (ii+1 >= numLines || ii-1 < 0 || jj+1 >= numCol || jj-1 < 0)
		return 0;

	if ( ((table[ii-1][jj-1] == 'M' && table[ii+1][jj+1] == 'S') || (table[ii-1][jj-1] == 'S' && table[ii+1][jj+1] == 'M')) && 
		( (table[ii+1][jj-1] == 'M' && table[ii-1][jj+1] == 'S') || (table[ii+1][jj-1] == 'S' && table[ii-1][jj+1] == 'M'))
	) {
		printf("xmax %d %d\n", ii, jj);
		return 1;
	}
	return 0;
}

void processTable() {
	for (int i = 0 ; i < numLines; i++) {
		for (int j = 0; j <  strlen(table[i]); j++) {
			if (table[i][j] == 'A') {
				count += check(i, j);
			}
		}
	}
}




int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;

	int i = 0;
	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
		strcpy(table[i], line);
		i++;
	}
	numLines = i;
	numCol = strlen(table[0]) - 1;

	processTable();
	//print();

	printf("count: %d\n", count);
	return 0;
}



