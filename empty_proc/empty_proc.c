#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;

	while (argv[0][i]) {
		argv[0][i] = '\0';
		i++;
	}
	while (1)
		sleep(1);
	return 0;
}
