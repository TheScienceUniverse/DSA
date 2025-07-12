#include "../inc/test.h"

void test_basic (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Basic]\n" RESET_STYLE);

	const int n = 0xf00ff00f;

	int* ptr = malloc (sizeof (int));
	*ptr = n;

	int* ghost_ptr = ptr;

	TEST (NULL != ptr, "Address non-null check");
	TEST (sizeof (int*) == sizeof (ptr), "Allocated block-size check");
	TEST (ptr == ghost_ptr, "Address validation check");
	TEST (n == *ptr, "Content check");

	ERASE (&ptr, sizeof (int));

	TEST (ghost_ptr != ptr, "Address validation check");
	TEST (NULL == ptr, "Address nullification check");
	TEST (n != *((int*) ghost_ptr), "Content check");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Basic]\n" RESET_STYLE);
}
