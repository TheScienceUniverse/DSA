#include "../include/basic.h"
#include "../include/string.h"

int main (void) {
	int* ptr = (int*) malloc (sizeof (int));
	void* ref_ptr = ptr;

	*ptr = 10;

	assert (ptr != NULL);
	printf ("Number Test 1: Success!\n");

	assert (*((int*) ptr) == 10);
	printf ("Number Test 2: Success!\n");

	assert (ref_ptr != NULL);
	printf ("Number Test 3: Success!\n");

	assert (*((int*) ref_ptr) == 10);
	printf ("Number Test 4: Success!\n");

	ERASE (&ptr);

	assert (ptr == NULL);
	printf ("Number Test 1: Success!\n");

//	assert (*((int*) ptr) == 10);
//	printf ("Number Test 2: Success!\n");

	assert (ref_ptr != NULL);
	printf ("Number Test 3: Success!\n");

	assert (*((int*) ref_ptr) != 10);
	printf ("Number Test 4: Success!\n");

	String* string = create_string (14, "Hello, World!\n");
	assert (string != NULL);
	printf ("String Test 1: Success! -- mem alloc\n");
	delete_string (&string);
	assert (string == NULL);
	printf ("String Test 2: Success! -- mem de-alloc\n");


	return 0;
}
