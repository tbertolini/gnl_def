#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	char *stringa;
	int fd;
	int contr;
	fd = open("test.txt", O_RDONLY);
	while ((contr = get_next_line(fd, &stringa)) > 0)
		printf("------> new_line = %s\n\n\n", stringa);
	get_next_line(fd, &stringa);
	printf("------> new_line = %s\n\n\n", stringa);
	//printf("------> new_line = %s\n\n\n", stringa);
	//get_next_line(fd, &stringa);
	//printf("------> new_line = %s\n\n\n", stringa);
	//get_next_line(fd, &stringa);
	//printf("------> new_line = %s\n\n\n", stringa);
	
	return 0;
}
