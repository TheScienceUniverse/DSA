#include "../include/basic.h"
#include <assert.h>

int main (void) {
	int x = 10;
	
	assert (x == 10);
	printf ("Test 1: Successful!\n");

	assert(x == 11);
	printf ("Test 2: Successful!\n");
	
	return 0;
}
