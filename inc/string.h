#ifndef STRING_H
#define STRING_H

#include "basic.h"

// ---------- x ----------

typedef struct STRING {
	size_t length;
	char* text;
} String;

// ---------- x ----------

void display_raw_string (size_t length, char* text);		// prints string // takes length and text pointer
bool compare_raw_strings_shh (size_t length1, char* string1, size_t length2, char* string2);
char* char_array_to_pointer (size_t length, char* text);	// converts character array to text object
void copy_raw_char_stream (size_t len, void* src_addr, void* dst_addr);
void display_N_characters (char character, size_t repetitions);

String* create_string (size_t length, char* text);	// pass NULL as for text argument to create empty string
void delete_string (String** string_address);				// frees string object from memory
String* duplicate_string (String* string);
void display_string (String* string);						// prints only text part
void display_string_details (String* string);
String* concatenate_strings (int input_count, ...);			// concatenates multiple string objects
String* append_integer_to_raw_string (char* str, int number);
bool is_string_memory_erased (void** string_addresses);
void** capture_string_addresses (String* string);
Compare_Status compare_strings (String* string1, String* string2);
char get_char_at (String* string, size_t index);	// 0 based index
ssize_t get_char_first_index (String* string, char character);
ssize_t get_char_last_index (String* string, char character);
String* get_sub_string (String* string, ssize_t start_index, ssize_t end_index);	// inclusive end_index
String* get_sub_str (String* string, ssize_t start_index, ssize_t length);
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