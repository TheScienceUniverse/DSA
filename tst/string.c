#include "../inc/test.h"

void test_string (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [String]\n" RESET_STYLE);

	char* text = "Hello, World!\n";
	size_t length = 14;

	String* string = create_string (length, text);
	String* ghost_string = string;

	// printf ("%lu %lu\n", length, sizeof (string -> text));

	TEST (NULL != string, "Address non-null check");
	TEST (length == string -> length, "Allocated block-size check");
	TEST (string == ghost_string, "Address validation check");
	TEST (compare_raw_strings_shh (length, text, string -> length, string -> text), "Content check");

//	void** string_addresses = capture_string_addresses (string);
//	TEST (!is_string_memory_erased (string_addresses), "String existance check");
	TEST (string == ghost_string, "String existance check");
	delete_string (&string);
	TEST (string != ghost_string, "String deletion check");

	//TEST (is_string_memory_erased (string_addresses), "String deletion check");
//	ERASE (&string_addresses, 3 * sizeof (void*));
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
//	TEST (NULL == string, "Address nullify check");
//	TEST (ptr != vptr, "Address validation check");
//	TEST (n != *((int*) vptr), "Content check");

	String* str1 = create_string (5, "Hello");
	String* str2 = create_string (5, "World");
	string = concatenate_strings (2, str1, str2);
	TEST (string -> length == str1 -> length + str2 -> length, "Checked concatenated string lengths");
	ghost_string = create_string (10, "HelloWorld");
	TEST (Cmp_Different != compare_strings (string, ghost_string), "Matched concatenated strings");
	delete_string (&ghost_string);
	delete_string (&string);
	delete_string (&str1);
	delete_string (&str2);

	string = create_string (3, "123");
	ghost_string = string;
	str1 = create_string (3, "321");
	str2 = create_string (3, "123");
	TEST (Cmp_Identical == compare_strings (string, ghost_string), "Matched identical strings");
	TEST (Cmp_Different == compare_strings (string, str1), "Mis-matched different strings");
	TEST (Cmp_Equivalent == compare_strings (string, str2), "Matched equivalent strings");
	delete_string (&string);
	delete_string (&str1);
	delete_string (&str2);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [String]\n" RESET_STYLE);
}
