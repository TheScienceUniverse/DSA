#include "../include/test.h"

void test_string (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [String]\n" RESET_STYLE);

	char* str = "Hello, World!\n";
	size_t len = 14;

	String* string = create_string (len, str);
	String* s = string;

	// printf ("%lu %lu\n", len, sizeof (string -> address));

	TEST (string != NULL, "Address non-null check");
	TEST (len == string -> length, "Allocated block-size check");
	TEST (len * sizeof (char) == sizeof (string -> address), "");
	TEST (string == s, "Address validation check");
	TEST (compare_raw_strings_shh (len, str, string -> length, string -> address), "Content check");
/*
	BYTE* ptr_b = (void*) string;
	BYTE* ptr_adr = (void*) (string -> address);
	BYTE* ptr_b_f = (void*) string;

	for (size_t i = 0; i < sizeof (String); i++) {
		printf("%02x ", *ptr_b);
		ptr_b = ptr_b + 1;
	}

	printf("\n");

	delete_string (&string);

	for (size_t i = 0; i < sizeof (size_t); i++) {
		printf("%02x ", *ptr_adr);
		ptr_adr = ptr_adr + 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof (String); i++) {
		printf ("%02x ", *ptr_b_f);
		ptr_b_f = ptr_b_f + 1;
	}

	printf("\n");
*/
//	TEST (NULL == string, "Address nullified check");
//	TEST (sizeof (int*) == sizeof (string), "De-allocated block-size check");
	TEST (NULL == string, "Address nullify check");
//	TEST (ptr != vptr, "Address validation check");
//	TEST (n != *((int*) vptr), "Content check");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [String]\n" RESET_STYLE);
}
