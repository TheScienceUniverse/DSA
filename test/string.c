#include "../include/test.h"
#include "../include/basic.h"
#include "../include/string.h"

/*
void display_raw_string (int length, char* address);		// prints string // takes length and address pointer
char* char_array_to_pointer (int length, char* address);	// converts character array to string object
String* create_string (int length, char* address);			// creates string object // pass NULL as argument if empty string to be created
String* duplicate_string (String* string);
void delete_string (String** string_address);				// frees string object from memory
void display_string (String* string);						// prints only string part
void display_string_properties (String* string);			// prints whole description
void concatenate_strings (int input_count, ...);			// concatenates multiple string objects
bool are_strings_equal (String* string1, String* string2);	// checks if strings are same by value or not, does not check by address
String* append_integer_to_raw_string (char* str, int number);
*/

bool compare_raw_strings_shh (size_t length1, char* string1, size_t length2, char* string2) {
	if (length1 != length2) {
		return false;
	}

	if (string1 == string2) {
		return true;
	}

	bool result = true;
	char* c1 = string1;
	char* c2 = string2;

	for (size_t i = 0; i < length1; ++i) {
		if (*c1 != *c2) {
			result = false;
			break;
		}

		++c1;
		++c2;
	}

	return result;
}

void test_string (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [String]\n" RESET_STYLE);

	char* str = "Hello, World!\n";
	size_t length = 14;

	String* string = create_string (length, str);
	void* ptr = string;

	TEST (string != NULL, "Address non-null check");
 	TEST (length == string -> length, "Allocated block-size check");
	TEST (string == ptr, "Address validation check");
	TEST (compare_raw_strings_shh (length, str, string -> length, string -> address), "Content check");

	delete_string (&string);

	TEST (NULL == string, "Address nullified check");
//	TEST (sizeof (int*) == sizeof (string), "De-allocated block-size check");
//	TEST (NULL == ptr, "Address nullify check");
//	TEST (ptr != vptr, "Address validation check");
//	TEST (n != *((int*) vptr), "Content check");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [String]\n" RESET_STYLE);
}
