/*
 * allocate a small amount of memory (4 bytes) as zero,
 * set the magic value and sleep for ugtrain/scanmem testing
 */

#include <stdlib.h>
#include <unistd.h>

#define MAGIC_VALUE 0xdeadbeef

int main (void)
{
	int *data = (int *) calloc(1, sizeof(int));

	if (!data)
		return -1;
	*data = MAGIC_VALUE;
	while (1) {
		sleep(1);
		if (*data != MAGIC_VALUE)
			return -1;
	}
	return 0;
}
