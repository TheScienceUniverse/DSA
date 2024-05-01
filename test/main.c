#include "../include/basic.h"
#include <assert.h>

int main (void) {
	int* ptr = (int*) malloc (sizeof (int));
	void* ref_ptr = ptr;

	*ptr = 10;

	assert (ptr != NULL);
	printf ("Test 1: Successful!\n");

	assert (*((int*) ptr) == 10);
	printf ("Test 2: Successful!\n");

	assert (ref_ptr != NULL);
	printf ("Test 3: Successful!\n");

	assert (*((int*) ref_ptr) == 10);
	printf ("Test 4: Successful!\n");

	ERASE (&ptr);

	assert (ptr != NULL);
	printf ("Test 1: Successful!\n");

	assert (*((int*) ptr) == 10);
	printf ("Test 2: Successful!\n");

	assert (ref_ptr != NULL);
	printf ("Test 3: Successful!\n");

	assert (*((int*) ref_ptr) == 10);
	printf ("Test 4: Successful!\n");

	return 0;
}
