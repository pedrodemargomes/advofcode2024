#include <stdio.h>
#include <string.h>

struct space {
	int id;
	int size;
	int isFile;
	int visited;
};

struct array {
	struct space a[30000];
	int size;
};

void insert(struct array *a, struct space n) {
	a->a[a->size++] = n;
}

void insertAt(struct array *a, struct space n, int index) {
	a->size++;
	for(int i = a->size-1; i > index; i--) {
		a->a[i] = a->a[i-1];
	}
	a->a[index] = n;
}

void printSpace(struct space s) {
	printf("id: %d size: %d isFile: %d\n", s.id, s.size, s.isFile);
}

void printDisk(struct array *d) {
	for (int i = 0; i < d->size; i++) {
		for (int j = 0; j < d->a[i].size; j++) {
			if (!d->a[i].isFile)
				printf(".");
			else
				printf("%d", d->a[i].id);
		}
	}
	printf("\n");
}

struct array disk;

int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;
	
	getline(&line, &len, stdin);

	int id = 0;
	for (int i = 0; i < strlen(line)-1; i++) {
		int n = line[i]-0x30;
		struct space s = {
			.size = n,
			.isFile = (i % 2 == 0),
			.id = (i % 2 == 0) ? id++ : -1
		};
		insert(&disk, s);

		//printSpace(s);
	}

	int end = disk.size-1;
	if (!disk.a[end].isFile)
		end--;	
	printf("end: %d\n", end);
	

	while (end > 0) {
		if (!disk.a[end].isFile && !disk.a[end].visited)
			goto cont;
		disk.a[end].visited = 1;
		for (int i = 0; i < end;i++) {
			if (!disk.a[i].isFile && disk.a[i].size >= disk.a[end].size) {
				disk.a[i].isFile = 1;
				disk.a[i].id = disk.a[end].id;
				int szEnd = disk.a[end].size;
				disk.a[end].isFile = 0;
				if (disk.a[i].size > szEnd) {
					struct space rest = {
						.id = -1,
						.isFile = 0,
						.size = disk.a[i].size - szEnd
					};
					
					insertAt(&disk, rest, i+1);
				}
				disk.a[i].size = szEnd;
				
				break;
			}
		}

	cont:
		end--;
	}

	//printDisk(&disk);

	int pos = 0;
	unsigned long checksum = 0;
	for (int i = 0; i < disk.size; i++) {
		for (int j = 0; j < disk.a[i].size; j++) {
			if (disk.a[i].isFile)
				checksum += pos*disk.a[i].id;
			pos++;
		}
	}

	printf("\nchecksum: %lu\n", checksum);

	return 0;
}
