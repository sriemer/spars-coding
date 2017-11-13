/*
 * Reserve a magic string in static memory, put a static memory
 * pointer to it and sleep for ugtrain/scanmem testing.
 *
 * Ugtrain example config:
 *
 * # 0x601048 points to 0x601038 containing 'data'
 * Strptr 0x601048 cstrp watch
 */

#include <stdlib.h>
#include <unistd.h>

static char data[] = "deadbeef";
static char **ref = (char **) &data;

int main (void)
{
	while (1) {
		sleep(1);
		if (data[0] != 'd' || (long)ref != (long)&data)
			return -1;
	}
	return 0;
}
