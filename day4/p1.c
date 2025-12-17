#include <stdio.h>
#include <string.h>

int count = 0;
int numLines;
int numCol;
char table[1000][1000];
int check[1000][1000];

void print() {
	printf("table: numLines %d numCol: %d\n", numLines, numCol);
	for (int i = 0 ; i < numLines; i++)
		printf("%s", table[i]);
}

int checkBackDown(int ii, int jj) {
	if (ii+3 >= numLines)
		return 0;
	if (jj-3 < 0)
		return 0;

	if ( table[ii+1][jj-1] == 'M' && table[ii+2][jj-2] == 'A' && table[ii+3][jj-3] == 'S') {
		printf("back down: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii+1][jj-1]++;
		check[ii+2][jj-2]++;
		check[ii+3][jj-3]++;
		return 1;
	}
	return 0;
}

int checkBackUp(int ii, int jj) {
	if (ii-3 < 0)
		return 0;
	if (jj-3 < 0)
		return 0;

	if ( table[ii-1][jj-1] == 'M' && table[ii-2][jj-2] == 'A' && table[ii-3][jj-3] == 'S') {
		printf("back up: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii-1][jj-1]++;
		check[ii-2][jj-2]++;
		check[ii-3][jj-3]++;
		return 1;
	}
	return 0;
}

int checkFrontUp(int ii, int jj) {
	if (ii-3 < 0)
		return 0;
	if (jj+3 >= numCol)
		return 0;

	if ( table[ii-1][jj+1] == 'M' && table[ii-2][jj+2] == 'A' && table[ii-3][jj+3] == 'S') {
		printf("front up: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii-1][jj+1]++;
		check[ii-2][jj+2]++;
		check[ii-3][jj+3]++;
		return 1;
	}
	return 0;
}

int checkFrontDown(int ii, int jj) {
	if (ii+3 >= numLines)
		return 0;
	if (jj+3 >= numCol)
		return 0;

	if ( table[ii+1][jj+1] == 'M' && table[ii+2][jj+2] == 'A' && table[ii+3][jj+3] == 'S') {
		printf("front down: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii+1][jj+1]++;
		check[ii+2][jj+2]++;
		check[ii+3][jj+3]++;
		return 1;
	}
	return 0;
}

int checkDown(int ii, int jj) {
	if (ii+3 >= numLines)
		return 0;

	if ( table[ii+1][jj] == 'M' && table[ii+2][jj] == 'A' && table[ii+3][jj] == 'S') {
		printf("down: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii+1][jj]++;
		check[ii+2][jj]++;
		check[ii+3][jj]++;
		return 1;
	}
	return 0;
}

int checkUp(int ii, int jj) {
	if (ii-3 < 0)
		return 0;
	if ( table[ii-1][jj] == 'M' && table[ii-2][jj] == 'A' && table[ii-3][jj] == 'S') {
		printf("up: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii-1][jj]++;
		check[ii-2][jj]++;
		check[ii-3][jj]++;
		return 1;
	}
	return 0;
}

int checkFront(int ii, int jj) {
	if (jj + 3 >= numCol)
	       return 0;	
	if (!strncmp(&table[ii][jj], "XMAS", 4)) {
		printf("front: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii][jj+1]++;
		check[ii][jj+2]++;
		check[ii][jj+3]++;
		return 1;
	}
	return 0;
}

int checkBack(int ii, int jj) {
	if (jj -3 < 0)
		return 0;
	if (!strncmp(&table[ii][jj-3], "SAMX", 4)) {
		printf("back: %d %d\n", ii, jj);
		check[ii][jj]++;
		check[ii][jj-1]++;
		check[ii][jj-2]++;
		check[ii][jj-3]++;
		return 1;
	}
	return 0;
}

void processTable() {
	for (int i = 0 ; i < numLines; i++) {
		for (int j = 0; j <  strlen(table[i]); j++) {
			if (table[i][j] == 'X') {
				count += checkFront(i, j);
				count += checkBack(i, j);
				count += checkUp(i, j);
				count += checkDown(i, j);
				count += checkFrontUp(i, j);
				count += checkFrontDown(i, j);
				count += checkBackDown(i, j);
				count += checkBackUp(i, j);
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



