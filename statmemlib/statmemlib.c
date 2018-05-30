/*
 * Test static memory in three libraries,
 * one of them loaded later with dlopen()
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

#include "lib1/lib1.h"
#include "lib2/lib2.h"

int main (void)
{
	int secs_to_load = 5;
	void *lib3_handle = NULL;
	int (*get_magic_val3)(void) = NULL;

	while (1) {
		int val1 = get_magic_val1();
		int val2 = get_magic_val2();
		int val3;

		if (secs_to_load > 0) {
			secs_to_load--;
		} else if (secs_to_load == 0) {
			secs_to_load--;
			lib3_handle = dlopen("lib3/lib3.a", RTLD_LAZY);
			if (lib3_handle)
				get_magic_val3 = (int (*)(void)) dlsym(lib3_handle, "get_magic_val3");
			else
				fprintf(stderr, "%s\n", dlerror());
		}

		printf("Val1: 0x%x, Val2: 0x%x\n", val1, val2);
		if (get_magic_val3) {
			val3 = get_magic_val3();
			printf("Val3: 0x%x\n", val3);
		}
		sleep(1);
	}
	return 0;
}
