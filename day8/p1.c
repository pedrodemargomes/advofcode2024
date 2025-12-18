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

int numLines;
char map[10000][10000];
char mapAnt[10000][10000];
struct array antenas[200];

void printMap() {
	for (int i = 0; i < numLines; i++)
		printf("%s", map[i]);
}

void printMapAnt() {
	for (int i = 0; i < numLines; i++)
		printf("%s", mapAnt[i]);
}


void plotAnt(int ai, int aj, int bi, int bj) {
	int di, dj;
	
	di = ai-bi;
	dj = aj-bj;
	
	if (ai-di != bi && aj-dj != bj) {
		if (ai-di >= 0 && aj-dj >= 0)
			mapAnt[ai-di][aj-dj] = '#';
	} else {
		if (ai+di < numLines && aj+dj >= 0)
			mapAnt[ai+di][aj+dj] = '#';
	}

	if (bi+di != ai && bj+dj != aj) {
		mapAnt[bi+di][bj+dj] = '#';
	} else {
		if (bi-di >= 0 && bj-dj >= 0)
			mapAnt[bi-di][bj-dj] = '#';
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

	for (int i = 0; i < numLines; i++) {
		for (int j = 0; j < strlen(map[i])-1; j++) {
			if (map[i][j] != '.') {
				struct pos p = {
					.i = i,
					.j = j
				};
				insert(&antenas[(int)map[i][j]], p);
			}	
		}	
	}

	for(int k = 0; k < 200; k++) {
		for (int i = 0; i < antenas[k].size; i++) {
			for (int j = 0; j < antenas[k].size; j++) {
				if (i != j) {
					struct pos a = antenas[k].a[i];
					struct pos b = antenas[k].a[j];
					plotAnt(a.i, a.j, b.i, b.j);
				}	
			}
		}
	}

	printMapAnt();

	//printf("%d\n", antenas[(int)'b'].size);
	
	return 0;
}



