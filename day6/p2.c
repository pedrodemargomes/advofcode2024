#include <stdio.h>
#include <string.h>

int numLines;
char map[10000][10000];
char mapOrig[10000][10000];

void print() {
	for (int i = 1; i < numLines-1; i++)
		printf("%s\n", map[i]);
	printf("\n");
}

int _walk(int posi, int posj) {
	int count = 0;
	char old = 'I';
	for (;;) {
		if (old == 'F')
			return count;

		if (old == '.')
			count++;

		if (old == map[posi][posj]) {
			return -1;
		}

		if (map[posi][posj] == '^') {
			if (map[posi-1][posj] == '#') {
				old = map[posi][posj];
				map[posi][posj] = '>';
			} else {
				posi = posi-1;
				old = map[posi][posj];
				map[posi][posj] = '^';
			}
			continue;
		}
		
		if (map[posi][posj] == '>') {
			if (map[posi][posj+1] == '#') {
				old = map[posi][posj];
				map[posi][posj] = 'v';
			} else {
				posj = posj+1;
				old = map[posi][posj];
				map[posi][posj] = '>';
			}
			continue;
		}
	
		if (map[posi][posj] == 'v') {
			if (map[posi+1][posj] == '#') {
				old = map[posi][posj];
				map[posi][posj] = '<';
			} else {
				posi = posi+1;
				old = map[posi][posj];
				map[posi][posj] = 'v';
			}
			continue;
		}
		
		if (map[posi][posj] == '<') {
			if (map[posi][posj-1] == '#') {
				old = map[posi][posj];
				map[posi][posj] = '^';
			} else {
				posj = posj-1;
				old = map[posi][posj];
				map[posi][posj] = '<';
			}
			continue;
		}
	
	}
}

int walk() {
	int posi, posj;
	for (posi = 0; posi < numLines; posi++) {
		for (posj = 0; posj < strlen(map[posi]); posj++) {
			if (map[posi][posj] == '^')
				goto outloop;
		}
	}
outloop:
	return _walk(posi, posj); 
}


int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;
	
	memset(&map[0][0], 'F', 10000);
	int i = 1;
	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
		strcpy(&map[i][1], line);
		map[i][0] = 'F';
		map[i][strlen(line)] = 'F';
		map[i][strlen(line)+1] = '\0';
		i++;
	}
	memset(&map[i++][0], 'F', 10000);
	numLines = i;

	memcpy(mapOrig, map, 10000*10000*sizeof(char));		

	int count = 0;	
	for (int i = 1; i < numLines-1; i++) {
		for (int j = 0; j < strlen(mapOrig[i]); j++) {
			if (mapOrig[i][j] == '.') {
				memcpy(map, mapOrig, 10000*10000*sizeof(char));		
				map[i][j] = '#';
				if (walk() == -1)
					count++;
				printf("count: %d i: %d j: %d\n", count, i, j);
			}
		}
	}

	printf("count: %d\n", count);
	return 0;
}



