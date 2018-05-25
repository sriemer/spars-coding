#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAGIC_VAL2 0xc0cac01a
static int magic2 = MAGIC_VAL2;

int get_magic_val2 (void)
{
	return magic2;
}
