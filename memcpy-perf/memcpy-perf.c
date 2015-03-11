/*
 * Test to compare the performance of memcpy() to dereferencing of a long
 * value on CPU architectures which support both.
 *
 * Copyright (c) 2015 Sebastian Parschauer <s.parschauer@gmx.de>
 *
 * License: GPLv2
 *
 * Some CPU architectures like ARM are not able to dereference unaligned
 * memory addresses for int or long values. These have to use memcpy()
 * instead. The question is:
 *
 * What does it cost to always use memcpy() on CPU architectures which
 * support both?
 *
 * Expected result:
 * Really using memcpy() has > 150% overhead on x86_64. This is why GCC
 * replaces it with dereferencing if possible. That's exactly what we want!
 * We can always use memcpy() in the code and GCC will optimize it away.
 *
 * Synthetic tests are really not exactly the same. So always disassemble with
 * "objdump -S" to check what the compiler makes out of your C code!
 *
 * 1. Compile: gcc -O0 -g -Wall -fno-builtin-memcpy -o memcpy-perf memcpy-perf.c
 * 2. run ./memcpy-perf
 * 3. disassemble with "objdump -S ./memcpy-perf | less", search for "memcpy\("
 * 4. Clean up the build and compile without '-fno-builtin-memcpy'
 * 5. run ./memcpy-perf
 * 6. disassemble with "objdump -S ./memcpy-perf | less", search for "memcpy\("
 *
 * Do you see the difference?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/* Try to let this run > 20s per test */
#define NUM_CYCLES 9999999999UL


/* a = a - b */
static void sub_timeval (struct timeval *a, struct timeval *b)
{
	a->tv_sec -= b->tv_sec;
	if (a->tv_usec < b->tv_usec) {
		a->tv_sec--;
		a->tv_usec += 1000000;
	}
	a->tv_usec -= b->tv_usec;
}

static inline int test_deref (unsigned long *usec)
{
	struct timeval start, end;
	unsigned long val = 0;
	unsigned long i, *ip = &i;
	int ret;

	ret = gettimeofday(&start, NULL);
	if (ret)
		goto err;
	for (i = 0; i < NUM_CYCLES; i++)
		val = *ip;
	ret = gettimeofday(&end, NULL);
	if (ret)
		goto err;
	sub_timeval(&end, &start);
	printf("deref:    sec %lu, usec %lu\n",
		end.tv_sec, end.tv_usec);
	*usec = end.tv_sec * 1000000 + end.tv_usec;

	/* just avoid a compiler warning */
	if (val == 0)
		ret = -1;

	return ret;
err:
	perror("gettimeofday");
	return ret;
}

static inline int test_memcpy (unsigned long *usec)
{
	struct timeval start, end;
	unsigned long val = 0;
	unsigned long i;
	int ret;

	ret = gettimeofday(&start, NULL);
	if (ret)
		goto err;
	for (i = 0; i < NUM_CYCLES; i++)
		memcpy(&val, &i, sizeof(long));
	ret = gettimeofday(&end, NULL);
	if (ret)
		goto err;
	sub_timeval(&end, &start);
	printf("memcpy(): sec %lu, usec %lu\n",
		end.tv_sec, end.tv_usec);
	*usec = end.tv_sec * 1000000 + end.tv_usec;

	/* just avoid a compiler warning */
	if (val == 0)
		ret = -1;

	return ret;
err:
	perror("gettimeofday");
	return ret;
}

int main (void)
{
	int j, ret;
	float overhead;

	for (j = 0; j < 3; j++) {
		unsigned long memcpy_usec, deref_usec;

		ret = test_memcpy(&memcpy_usec);
		if (ret)
			goto err;
		ret = test_deref(&deref_usec);
		if (ret)
			goto err;

		overhead = (float) memcpy_usec * 100 / (float) deref_usec - 100;
		printf("memcpy() overhead: %.1f%%\n", overhead);
	}
	return 0;
err:
	return -1;
}
