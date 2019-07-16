/* Taken from "Linux Trainer" posted on LinkedIn */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void breakout(void)
{
	system("/bin/sh");
}

void function(void)
{
	void *p;
	printf("function() code starts at address %p\n", function);
	printf("Address of stack variable: %p\n", &p);
	printf("Something that looks like a return address on stack: %p\n", *((&p)+2));
	// Let's change it to point to the start of our sneaky function.
	*((&p)+2) = breakout;
}

int main(void)
{
	printf("main() code starts at address %p\n", main);
	function();
	return 0;
}
