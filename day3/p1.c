#include <stdio.h>
#include <string.h>

struct String {
	char *str;
	unsigned int pos;
	unsigned int len;
};

int next(struct String *s) {
	if (++s->pos < s->len)
		return 0;
	return 1;
}

int expectNum(struct String *s, int *n) {
	if (s->str[s->pos] < 0x30 || s->str[s->pos] > 0x39 ) {
		next(s);
		return 1;
	}
	*n = s->str[s->pos] - 0x30;
	if (next(s))
		return 1;
	if (s->str[s->pos] < 0x30 || s->str[s->pos] > 0x39 )
		goto out;
	*n += 10*(s->str[s->pos] - 0x30);
	if (next(s))
		return 1;
	if (s->str[s->pos] < 0x30 || s->str[s->pos] > 0x39 )
		goto out;;
	*n += 100*(s->str[s->pos] - 0x30);
	if (next(s))
		return 1;
	
out:
	return 0;
}

int expect(struct String *s, char c) {
	int ret = 0;
	if (s->str[s->pos] != c)
		ret = 1;
	if (next(s))
		return 1;
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
		if (expect(&s, 'm'))
			goto end;
		if (expect(&s, 'u'))
			goto end;
		if (expect(&s, 'l'))
			goto end;
		if (expect(&s, '('))
			goto end;
		if (expectNum(&s, &n1))
			goto end;
		if (expect(&s, ','))
			goto end;
		if (expectNum(&s, &n2))
			goto end;
		if (expect(&s, ')'))
			goto end;
		
		//printf("%d x %d = %d\n", n1, n2, n1*n2);
		sum += n1 * n2;
	end:	
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



