#include <stdio.h>
#include <string.h>

int numLines;
char map[10000][10000];
char mapOrig[10000][10000];

int walkint(int posi, int posj) {
	if (map[posi][posj] == '9') {
		//map[posi][posj] = -20; 
		return 1;
	}
	
	char p = map[posi][posj];

	int c = 0;
	if (map[posi][posj+1] == p+1)
		c += walkint(posi, posj+1);
	if (map[posi][posj-1] == p+1)
		c += walkint(posi, posj-1);
	if (map[posi+1][posj] == p+1)
		c += walkint(posi+1, posj);
	if (map[posi-1][posj] == p+1)
		c += walkint(posi-1, posj);
	
	return c;
}

void printMap() {
	for(int i = 0;i < numLines; i++) {
		for(int j = 0;j < strlen(map[1]); j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;
	
	int i = 1;
	memset(&map[0][0], -20, 10000*sizeof(int));
	for (;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
				
		printf("%s", line);
		strcpy(&map[i][1], line);
		map[i][0] = -20;
		map[i][strlen(line)] = -20;
		i++;
	}
	memset(&map[i][0], -20, 10000*sizeof(char));
	i++;
	numLines = i;

	memcpy(mapOrig, map, 10000*10000*sizeof(char));

	printMap();	


	int count = 0;
	for(int i = 1;i < numLines-1; i++) {
		for(int j = 0;j < strlen(map[1]); j++) {
			if (map[i][j] == '0') {
				int w = walkint(i,j);
				memcpy(map, mapOrig, 10000*10000*sizeof(char));
				printf("i: %d j: %d tr: %d\n", i, j, w);
				count += w;
			}
		}
	}

	printf("count: %d\n", count);
	return 0;
}
