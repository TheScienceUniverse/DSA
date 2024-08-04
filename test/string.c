#include "../include/test.h"
#include "../include/basic.h"
#include "../include/string.h"

void test_string (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [String]\n" RESET_STYLE);

	char* str = "Hello, World!\n";
	size_t len = 14;

	String* string = create_string (len, str);
	void* ptr = string;

	printf ("%lu %lu\n", len, sizeof (string -> address));

	TEST (string != NULL, "Address non-null check");
	TEST (len == string -> length, "Allocated block-size check");
	TEST (len * sizeof (char) == sizeof (string -> address), "");
	TEST (string == ptr, "Address validation check");
	TEST (compare_raw_strings_shh (len, str, string -> length, string -> address), "Content check");

	delete_string (&string);

	TEST (NULL == string, "Address nullified check");
//	TEST (sizeof (int*) == sizeof (string), "De-allocated block-size check");
//	TEST (NULL == ptr, "Address nullify check");
//	TEST (ptr != vptr, "Address validation check");
//	TEST (n != *((int*) vptr), "Content check");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [String]\n" RESET_STYLE);
}
