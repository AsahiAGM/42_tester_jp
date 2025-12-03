#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

#define ANSI_GREEN "\x1b[32m" 
#define ANSI_RESET "\x1b[0m" 

int main(void)
{
	char *line;

	write(STDOUT_FILENO, ANSI_GREEN, strlen(ANSI_GREEN)); write(1, "<< stdin test >>\n", 17); write(STDOUT_FILENO, ANSI_RESET, strlen(ANSI_RESET));
    line = get_next_line(0);
	printf("%s", line);
    free(line);
	line = NULL;

	printf("\n");
}