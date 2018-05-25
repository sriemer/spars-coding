/* Test static memory in two libraries */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "lib1/lib1.h"
#include "lib2/lib2.h"

int main (void)
{
	while (1) {
		int val1 = get_magic_val1();
		int val2 = get_magic_val2();

		printf("Val1: 0x%x, Val2: 0x%x\n", val1, val2);
		sleep(1);
	}
	return 0;
}
