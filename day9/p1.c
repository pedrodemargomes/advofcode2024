#include <stdio.h>
#include <string.h>

struct space {
	int id;
	int size;
	int isFile;
};

struct array {
	struct space a[30000];
	int size;
};

void insert(struct array *a, struct space n) {
	a->a[a->size++] = n;
}

void printSpace(struct space s) {
	printf("id: %d size: %d isFile: %d\n", s.id, s.size, s.isFile);
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

		printSpace(s);
	}

	int end = disk.size-1;
	if (!disk.a[end].isFile)
		end--;	
	printf("end: %d\n", end);
	
	int pos = 0;
	unsigned long checksum = 0;

	int f = 0;
	while (f <= end) {
		if (f % 2 == 0) {
			for(int k = 0; k < disk.a[f].size; k++) {
				printf("%d", disk.a[f].id);
				checksum += disk.a[f].id * pos++;						
			}
			f++;
		} else {
			if (disk.a[f].size == disk.a[end].size) {
				for(int k = 0; k < disk.a[end].size; k++) {
					printf("%d", disk.a[end].id);
					checksum += disk.a[end].id * pos++;
				}

				f++;
				end -= 2;
			} else if (disk.a[f].size < disk.a[end].size) {
				for(int k = 0; k < disk.a[f].size; k++) {
					printf("%d", disk.a[end].id);
					checksum += disk.a[end].id * pos++;
				}
				disk.a[end].size -= disk.a[f].size;
				f++;
			} else {
				for(int k = 0; k < disk.a[end].size; k++) {
					printf("%d", disk.a[end].id);
					checksum += disk.a[end].id * pos++;
				}
				disk.a[f].size -= disk.a[end].size;
				end -= 2;

			}
		}
	}
	printf("\nchecksum: %lu\n", checksum);

	return 0;
}
