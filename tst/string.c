#include "../inc/test.h"

void test_String (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [String]\n" RESET_STYLE);

	char* text = "Hello, World!\n";
	size_t length = 14;

	String* string = create_String (length, text);
	String* ghost_string = string;

	// printf ("%lu %lu\n", length, sizeof (string -> text));

	TEST (NULL != string, "Address non-null check");
	TEST (length == string -> length, "Allocated block-size check");
	TEST (string == ghost_string, "Address validation check");
	TEST (compare_raw_strings_shh (length, text, string -> length, string -> text), "Content check");

//	void** string_addresses = capture_string_addresses (string);
//	TEST (!is_string_memory_erased (string_addresses), "String existance check");
	TEST (string == ghost_string, "String existance check");
	delete_String (&string);
	TEST (string != ghost_string, "String deletion check");

	//TEST (is_String_memory_erased (string_addresses), "String deletion check");
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

	delete_String (&string);

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

	String* str1 = create_String (5, "Hello");
	String* str2 = create_String (5, "World");
	string = concatenate_Strings (2, str1, str2);
	TEST (string -> length == str1 -> length + str2 -> length, "Checked concatenated string lengths");
	ghost_string = create_String (10, "HelloWorld");
	TEST (Cmp_Different != compare_Strings (string, ghost_string), "Matched concatenated strings");
	delete_String (&ghost_string);
	delete_String (&string);
	delete_String (&str1);
	delete_String (&str2);

	string = create_String (3, "123");
	ghost_string = string;
	str1 = create_String (3, "321");
	str2 = create_String (3, "123");
	TEST (Cmp_Identical == compare_Strings (string, ghost_string), "Matched identical strings");
	TEST (Cmp_Different == compare_Strings (string, str1), "Mis-matched different strings");
	TEST (Cmp_Equivalent == compare_Strings (string, str2), "Matched equivalent strings");
	delete_String (&string);
	delete_String (&str1);
	delete_String (&str2);

	string = create_String (5, "12345");
	TEST ('3' == get_char_at (string, 2), "Matched get char at given index in a string");
	delete_String (&string);

	String* str = NULL;

	string = create_String (5, "abcde");
	str = get_sub_String (string, 1, 3);
	TEST (true == compare_raw_strings_shh (3, "bcd", 3, str -> text), "Matched sub-string (\"abcde\", 1, 3) = \"bcd\"");
	delete_String (&str);
	str = get_sub_String (string, 4, 1);
	TEST (true == compare_raw_strings_shh (4, "edcb", 4, str -> text), "Matched sub-string (\"abcde\", 4, 1) = \"edcb\"");
	delete_String (&str);
	str = get_sub_String (string, -10, 10);
	TEST (true == compare_raw_strings_shh (5, "abcde", 5, str -> text), "Matched sub-string (\"abcde\", -10, 10) = \"abcde\"");
	delete_String (&str);
	str = get_sub_String (string, 10, -10);
	TEST (true == compare_raw_strings_shh (5, "edcba", 5, str -> text), "Matched sub-string (\"abcde\", 10, -10) = \"edcba\"");
	delete_String (&str);
	str = get_sub_String (string, -10, -100);
	TEST (true == compare_raw_strings_shh (1, "a", 1, str -> text), "Matched sub-string (\"abcde\", -10, -100) = \"a\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (5, "01234");
	str = get_sub_Str (string, 1, 3);
	TEST (true == compare_raw_strings_shh (3, "123", 3, str -> text), "Matched sub-str (\"01234\", 1, 3) = \"123\"");
	delete_String (&str);
	str = get_sub_Str (string, -1, 3);
	TEST (true == compare_raw_strings_shh (1, "4", 1, str -> text), "Matched sub-str (\"01234\", -1, 3) = \"4\"");
	delete_String (&str);
	str = get_sub_Str (string, 2, -3);
	TEST (true == compare_raw_strings_shh (3, "210", 3, str -> text), "Matched sub-str (\"01234\", 2, -3) = \"210\"");
	delete_String (&str);
	str = get_sub_Str (string, -2, -3);
	TEST (true == compare_raw_strings_shh (4, "3210", 4, str -> text), "Matched sub-str (\"01234\", -2, -3) = \"3210\"");
	delete_String (&str);
	str = get_sub_Str (string, 2, 100);
	TEST (true == compare_raw_strings_shh (3, "234", 3, str -> text), "Matched sub-str (\"01234\", 2, 100) = \"234\"");
	delete_String (&str);
	str = get_sub_Str (string, -4, -100);
	TEST (true == compare_raw_strings_shh (2, "10", 2, str -> text), "Matched sub-str (\"01234\", -4, -100) = \"10\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (4, "Fun_1");
	str = get_upper_case_String (string);
	TEST (true == compare_raw_strings_shh (4, "FUN_1", 4, str -> text), "Matched upper-case (\"Fun_1\") = \"FUN_1\"");
	delete_String (&str);
	str = get_lower_case_String (string);
	TEST (true == compare_raw_strings_shh (4, "fun_1", 4, str -> text), "Matched lower-case (\"Fun_1\") = \"fun_1\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (5, "HE1lo");
	str = swap_String_case (string);
	TEST (true == compare_raw_strings_shh (5, "he1LO", 5, str -> text), "Matched swap-case (\"HE1lo\") = \"he1LO\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (5, "heLLo");
	str = capitalize_String (string);
	TEST (true == compare_raw_strings_shh (5, "Hello", 5, str -> text), "Matched capitalize string (\"heLLo\") = \"Hello\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (12, "heLLo, wOrLd");
	str = get_title_case_String (string);
	TEST (true == compare_raw_strings_shh (12, "Hello, World!", 12, str -> text), "Matched title case string (\"heLLo, wOrLd\") = \"Hello, World\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (12, "clAsS@1_nAmE");
	str = get_pascal_case_String (string);
	TEST (true == compare_raw_strings_shh (10, "Class1Name", 10, str -> text), "Matched pascal case string (\"clAsS#1_nAmE\") = \"Class1Name\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (15, "vaRiAbLe#1_nAmE");
	str = get_camel_case_String (string);
	TEST (true == compare_raw_strings_shh (13, "variable1Name", 13, str -> text), "Matched camel case string (\"vaRiAbLe#1_nAmE\") = \"variable1Name\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (16, "DO_fuNC@$01 nAmE");
	str = get_snake_case_String (string);
	TEST (true == compare_raw_strings_shh (15, "do_func_01_name", 15, str -> text), "Matched snake case string (\"DO_fuNC@$01 nAmE\") = \"do_func_01_name\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (16, "DO-fuNC@$01 nAmE");
	str = get_kebab_case_String (string);
	TEST (true == compare_raw_strings_shh (15, "do-func-01-name", 15, str -> text), "Matched kebab case string (\"DO-fuNC@$01 nAmE\") = \"do-func-01-name\"");
	delete_String (&str);
	delete_String (&string);

	string = create_String (5, "Radar");
	TEST (1 == get_char_first_index (string, 'a'), "Matched first index of character in given String");
	TEST (3 == get_char_last_index (string, 'a'), "Matched last index of character in given String");
	delete_String (&string);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [String]\n" RESET_STYLE);
}
