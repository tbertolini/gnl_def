#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int contr;
	char *stringa;
	int fd;
	int ret;
	ret = 0;
	stringa = NULL;
	fd = open("test_file17", O_RDONLY);
	while ((ret = get_next_line(fd, &stringa)) > 0)
		printf("%s\n", stringa);
	printf("%s", stringa);
	return 0;
}
