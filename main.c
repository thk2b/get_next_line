#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

int main(void)
{
	char *line;
	int s;
	while ((s = get_next_line(0, &line)) == 1)
		puts(line);

	printf("%s\n", strerror(s));
}
