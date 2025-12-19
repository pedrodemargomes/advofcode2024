#include <stdio.h>
#include <string.h>

struct pos {
	int i;
	int j;
};

struct array {
	struct pos a[1000];
	int size;
};

void insert(struct array *a, struct pos n) {
	a->a[a->size++] = n;
}

int numCols;
int numLines;
char map[10000][10000];
char mapAnt[10000][10000];
struct array antenas[200];

void printMap() {
	for (int i = 0; i < numLines; i++) {
		for (int j = 0; j < numCols; j++)	
			printf("%c", map[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printMapAnt() {
	for (int i = 0; i < numLines; i++) {
		for (int j = 0; j < numCols; j++)	
			printf("%c", mapAnt[i][j]);
		printf("\n");
	}
	printf("\n");
}

int countAnt() {
	int count = 0;
	for (int i = 0; i < numLines; i++)
		for (int j = 0; j < numCols; j++)	
			if (mapAnt[i][j] == '#')
				count++;
	return count;
}

void plotAnt(int ai, int aj, int bi, int bj) {
	int di, dj, diOrig, djOrig;
	
	mapAnt[ai][aj] = '#';
	mapAnt[bi][bj] = '#';

	diOrig = ai-bi;
	djOrig = aj-bj;
	for(int k = 1; k < numLines; k++) {
		di = diOrig * k;
		dj = djOrig * k;

		if (ai-di != bi && aj-dj != bj) {
			if (ai-di >= 0 && aj-dj >= 0)
				mapAnt[ai-di][aj-dj] = '#';
		} else {
			if (ai+di < numLines && aj+dj < numCols)
				mapAnt[ai+di][aj+dj] = '#';
		}

		if (bi+di != ai && bj+dj != aj) {
			if (bi+di < numLines && bj+dj < numCols)
				mapAnt[bi+di][bj+dj] = '#';
		} else {
			if (bi-di >= 0 && bj-dj >= 0)
				mapAnt[bi-di][bj-dj] = '#';
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
		strcpy(&map[i][0], line);
		strcpy(&mapAnt[i][0], line);
		i++;
	}
	numLines = i;
	numCols = strlen(map[0]) -1;
	printf("numLines: %d numCols: %d\n", numLines, numCols);

	for (int i = 0; i < numLines; i++) {
		for (int j = 0; j < numCols; j++) {
			if (map[i][j] != '.') {
				struct pos p = {
					.i = i,
					.j = j
				};
				insert(&antenas[(int)map[i][j]], p);
			}	
		}	
	}

	printMapAnt();
	
	for(int k = 0; k < 200; k++) {
		for (int i = 0; i < antenas[k].size; i++) {
			for (int j = 0; j < antenas[k].size; j++) {
				if (i != j) {
					struct pos a = antenas[k].a[i];
					struct pos b = antenas[k].a[j];
					plotAnt(a.i, a.j, b.i, b.j);
					printMapAnt();
				}	
			}
		}
	}

	printMapAnt();

	printf("count: %d\n", countAnt());
	
	return 0;
}



