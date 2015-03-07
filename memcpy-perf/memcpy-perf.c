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
 * Depending on the CPU using memcpy() has 3 to 6% overhead on x86_64.
 * So it's worth dereferencing if possible.
 *
 * Compile: gcc -O0 -g -Wall -o memcpy-perf memcpy-perf.c
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

static inline int test_deref (void)
{
	struct timeval start, end;
	unsigned long val = 0;
	unsigned long i;
	int ret;

	ret = gettimeofday(&start, NULL);
	if (ret)
		goto err;
	for (i = 0; i < NUM_CYCLES; i++)
		val = *(&i);
	ret = gettimeofday(&end, NULL);
	if (ret)
		goto err;
	sub_timeval(&end, &start);
	printf("deref:    sec %lu, usec %lu\n",
		end.tv_sec, end.tv_usec);

	/* just avoid a compiler warning */
	if (val == 0)
		ret = -1;

	return ret;
err:
	perror("gettimeofday");
	return ret;
}

static inline int test_memcpy (void)
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

	for (j = 0; j < 3; j++) {
		ret = test_memcpy();
		if (ret)
			goto err;
		ret = test_deref();
		if (ret)
			goto err;
	}
	return 0;
err:
	return -1;
}
