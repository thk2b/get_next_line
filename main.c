#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	char *line;
	int s = 0;
	int fd = 0;

	if (argc == 2)
		if((fd = open(argv[1], O_RDONLY))== -1)
		printf("%s\n", strerror(errno));
	while ((s = get_next_line(fd, &line)) == 1)
		puts(line);
	if (s == -1)
		printf("%s\n", strerror(errno));
	return (s);
}
