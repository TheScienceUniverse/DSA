#include "./include/basic.h"
#include "./include/string.h"
#include <stdio.h>

int main (void) {
	int* ptr = (int*) malloc (sizeof (int));
	void* ref_ptr = ptr;

	*ptr = 10;

	printf ("ptr: %p\n", ptr);
	printf ("ref_ptr: %p\n", ref_ptr);
	printf ("ref_ptr val: %d\n", *((int*) ref_ptr));

	ERASE (&ptr);

	printf ("ptr: %p\n", ptr);
	printf ("ref_ptr: %p\n", ref_ptr);
	printf ("ref_ptr val: %d\n", *((int*) ref_ptr));

	String* string = create_string (14, "Hello, World!\n");
	printf ("string: %p\n", string);
	display_string_properties (string);
	delete_string (&string);
	printf ("string: %p\n", string);


	return 0;
}
