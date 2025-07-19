#ifndef STRING_H
#define STRING_H

#include "basic.h"

// ---------- x ----------

typedef struct STRING {
	size_t length;
	char* address;
} String;

// ---------- x ----------

void display_raw_string (size_t length, char* address);		// prints string // takes length and address pointer
bool compare_raw_strings_shh (size_t length1, char* string1, size_t length2, char* string2);
char* char_array_to_pointer (size_t length, char* address);	// converts character array to string object
void copy_raw_char_stream (size_t len, void* src_addr, void* dst_addr);

String* create_string (size_t length, char* address);		// creates string object // pass NULL as argument if empty string to be created
void delete_string (String** string_address);				// frees string object from memory
String* duplicate_string (String* string);
void display_string_properties (String* string);			// prints whole description
void display_string (String* string);						// prints only string part
String* concatenate_strings (int input_count, ...);			// concatenates multiple string objects
bool are_strings_equal (String* string1, String* string2);	// checks if strings are same by value or not, does not check by address
String* append_integer_to_raw_string (char* str, int number);
BYTE match_strings (String string1, String string2);
bool is_string_memory_erased (void** string_addresses);
void** capture_string_addresses (String* string);

void display_N_characters (char character, size_t repetitions);

Compare_Status compare_strings (String* string1, String* string2);

#endif	// STRING_H