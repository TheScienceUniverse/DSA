#ifndef STRING_H
#define STRING_H

#include "basic.h"

// ---------- x ----------

typedef struct STRING {
	size_t length;
	char* text;
} String;

// ---------- x ----------

// raw string (sequence of characters) related
void display_raw_string (size_t length, char* text);
bool compare_raw_strings_shh (size_t length1, char* string1, size_t length2, char* string2); // compares silently and provides truth value
char* char_array_to_pointer (size_t length, char* text);	// allocates dynamic memory from static / dynamic memory
void display_N_characters (char character, size_t repetitions);

// String object related
String* create_string (size_t length, char* text);	// pass NULL as for text argument to create empty string
String* duplicate_string (String* string);
void display_string (String* string);						// prints only text part
void display_string_details (String* string);
void delete_string (String** string_address);				// frees string object from memory
// concatenation
String* concatenate_strings (int input_count, ...);			// concatenates count numbers of String objects
String* append_integer_to_raw_string (char* str, int number);
// string checks
bool is_string_memory_erased (void** string_addresses);
void** capture_string_addresses (String* string);
Compare_Status compare_strings (String* string1, String* string2);
// character position related
char get_char_at (String* string, size_t index);	// 0 based index
ssize_t get_char_first_index (String* string, char character);
ssize_t get_char_last_index (String* string, char character);
// subset related
String* get_sub_string (String* string, ssize_t start_index, ssize_t end_index);	// inclusive end_index
String* get_sub_str (String* string, ssize_t start_index, ssize_t length);
// letter case related
String* get_upper_case_string (String* string);
String* get_lower_case_string (String* string);
String* swap_string_case (String* string);
String* capitalize_string (String* string);
String* get_title_case_string (String* string);
String* get_pascal_case_string (String* string);
String* get_camel_case_string (String* string);
String* get_snake_case_string (String* string);
String* get_kebab_case_string (String* string);

#endif	// STRING_H