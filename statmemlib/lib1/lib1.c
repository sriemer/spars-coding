#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAGIC_VAL1 0xdeadbeef
static int magic1 = MAGIC_VAL1;

int get_magic_val1 (void)
{
	return magic1;
}
