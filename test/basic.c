#include "../include/test.h"

void test_basic (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Basic]\n" RESET_STYLE);

	const int n = 100;

	int* ptr = malloc (sizeof (int));
	*ptr = n;

	void* vptr = ptr;

	TEST (sizeof (int*) == sizeof (ptr), "Allocated block-size check");
	TEST (NULL != ptr, "Address non-null check");
	TEST (ptr == vptr, "Address validation check");
	TEST (n == *ptr, "Content check");

	ERASE (&ptr, sizeof (int));

	TEST (sizeof (int*) == sizeof (ptr), "De-allocated block-size check");
	TEST (NULL == ptr, "Address nullify check");
	TEST (ptr != vptr, "Address validation check");
	TEST (n != *((int*) vptr), "Content check");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Basic]\n" RESET_STYLE);
}
