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
	fd = open("test.txt", O_RDONLY);
	while ((contr = get_next_line(fd, &stringa)) > 0)
		printf("------> new_line = %s\n\n\n", stringa);
	//ret = get_next_line(fd, &stringa);
	//printf("------> new_line = %s\n %d \n\n", stringa, ret);
	//ret = get_next_line(fd, &stringa);
	printf("------> new_line = %s\n %d \n\n", stringa, ret);
	
	return 0;
}
