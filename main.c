#include "./include/basic.h"

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

	return 0;
}
