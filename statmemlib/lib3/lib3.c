#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAGIC_VAL3 0xbadeaffe
static int magic3 = MAGIC_VAL3;

int get_magic_val3 (void)
{
	return magic3;
}
