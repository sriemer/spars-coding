/*
 * allocate a big amount of memory as zero and sleep
 * for scanmem testing
 */

#include <stdlib.h>
#include <unistd.h>

int main (void)
{
	long *data = (long *) calloc(1, 500 * 1024 * 1024);

	if (!data)
		return -1;
	while (1)
		sleep(1);
	return 0;
}
