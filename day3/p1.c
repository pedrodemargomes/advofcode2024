#include <stdio.h>
#include <string.h>

struct String {
	char *str;
	unsigned int pos;
	unsigned int len;
};

int next(struct String *s) {
	if (s->pos++ < s->len)
		return 0;
	return 1;
}

int expectNum(struct String *s, int *n) {
	int d3,d2,d1;
	d1 = d2 = d3 = -1;
	if (s->str[s->pos] < 0x30 || s->str[s->pos] > 0x39 ) {
		return 1;
	}
	d3 = s->str[s->pos] - 0x30;
	if (next(s))
		return 1;
	if (s->str[s->pos] < 0x30 || s->str[s->pos] > 0x39 )
		goto out;
	d2 = (s->str[s->pos] - 0x30);
	if (next(s))
		return 1;
	if (s->str[s->pos] < 0x30 || s->str[s->pos] > 0x39 )
		goto out;
	d1 = (s->str[s->pos] - 0x30);
	if (next(s))
		return 1;

out:
	*n = d3;
	if (d1 != -1 && d2 != -1)
		*n = 100*d3 + 10*d2 + d1;
	else if (d2 != -1)
		*n = 10*d3 + d2;
	else
		*n = d3;

	return 0;
}

int expect(struct String *s, char c) {
	int ret = 0;
	if (s->str[s->pos] != c)
		ret = 1;
	return ret;
}

unsigned long parse(char *str) {
	struct String s = {
		.str = str,
		.pos = 0,
		.len = strlen(str)
	};

	unsigned long sum = 0;

	int n1,n2;
	while (s.pos < s.len) {
		if (expect(&s, 'm')) {
			next(&s);
			continue;
		}
		if (next(&s))
			continue;
		if (expect(&s, 'u'))
			continue;
		if (next(&s))
			continue;
		if (expect(&s, 'l'))
			continue;
		if (next(&s))
			continue;
		if (expect(&s, '('))
			continue;
		if (next(&s))
			continue;
		if (expectNum(&s, &n1))
			continue;
		if (expect(&s, ','))
			continue;
		if (next(&s))
			continue;
		if (expectNum(&s, &n2))
			continue;
		if (expect(&s, ')'))
			continue;
		if (next(&s))
			continue;

		printf("%d x %d = %d\n", n1, n2, n1*n2);
		sum += n1 * n2;
	}
	printf("sum: %lu\n", sum);
	return sum;
}

int main(int argv, char *argc[]) {
	char *line = NULL;
	size_t len = 0;
	unsigned long count = 0;

	int i = 0;
	for(;;) {
		getline(&line, &len, stdin);
		if (*line == '\n')
			break;
		//printf("%s", line);
		
		count += parse(line);

		
		i++;
	}


	printf("i: %d count = %lu\n", i, count);
	return 0;
}



