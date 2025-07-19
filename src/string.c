#include "../inc/string.h"

void display_raw_string (size_t length, char* address) {
	for (size_t i = 0; i < length; i++) {
		printf ("%c", *(address + i));
	}
}

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

char* char_array_to_pointer (size_t length, char* str) {
	char* string = (char*) malloc (length);
	string = memcpy (string, str, length);
	return string;
}

void copy_raw_char_stream (size_t len, void* src_addr, void* dst_addr) {
	BYTE *b_src = src_addr;
	BYTE *b_dst = dst_addr;

	while (len--) {
		*b_dst = *b_src;
		++b_dst;
		++b_src;
	}
}

String* create_string (size_t len, char* str) {
	String* string = (String*) malloc (sizeof (String));

	if (string != NULL) {
		log_memory (DS_String, sizeof (String), string, true);

		string -> length = 0;
		string -> address = NULL;
	}

	if (len > 0 && str != NULL) {
		string -> length = len;
		string -> address = (char*) malloc (len * sizeof (char));

		if (string -> address != NULL) {
			log_memory (DS_Raw, len * sizeof (char), string -> address, true);

			copy_raw_char_stream (len, str, string -> address);
		}
	}

	return string;
}

void delete_string (String** string_address) {
	if (*string_address == NULL) {
		// perror ("String is empty to delete!");
		return;
	}

	String* string = *string_address;

	if (string -> address != NULL && string -> length > 0) {
		log_memory (DS_Raw, (string -> length) * sizeof (char), string -> address, false);
		ERASE (&(string -> address), string -> length);
	}

	string = NULL;

	log_memory (DS_String, sizeof (String), *string_address, false);
	ERASE (string_address, sizeof (String));
}

void display_string_properties (String* string) {
	printf ("String [%zu]: ", string -> length);
	display_string (string);
	printf ("\n");
}

void display_string (String* string) {
	if (string == NULL) {
		// perror ("String does not exist to display!");
		return;
	}

	display_raw_string (string -> length, string -> address);
}

String* duplicate_string (String* old_string) {
	if (old_string == NULL) {
		return NULL;
	}

	String* new_string = (String*) malloc (sizeof (String));

	if (new_string != NULL) {
		new_string -> length = 0;
		new_string -> address = NULL;
	}

	if (old_string -> length > 0 && old_string -> address != NULL) {
		new_string -> length = old_string -> length;
		new_string -> address = malloc (old_string -> length);

		if (new_string -> address != NULL) {
			new_string -> address = memcpy (new_string -> address, old_string -> address, new_string -> length);
		}
	}

	return new_string;
}

String* concatenate_strings (int count, ...) {
	if (
		count < 2
		|| count > 10
	) {
		perror ("Number of strings out of accepted bound [2-10]!");
		return NULL;
	}

	size_t combined_length = 0;

	va_list args;
	va_start (args, count);	// initialize list

	String* string;

	for (int i = 0; i < count; i++) {
		string = va_arg (args, String*);

		if (NULL == string) {
			continue;
		}

		combined_length += string -> length;
	}

    va_end (args);	// clears list

	String *big_str = create_string (0, "");
	
	big_str -> address = (char*) malloc (sizeof (char) * combined_length);

	if (NULL == big_str -> address) {
		delete_string (&big_str);
		perror ("Unable to allocate sufficient memory of combined length!");
		return NULL;
	}

	big_str -> length = combined_length;

	char* c_ptr = big_str -> address;	// character pointer

	va_start (args, count);	// initialize list

	for (int i = 0; i < count; i++) {
		string = va_arg (args, String*);

		if (NULL == string) {
			continue;
		}

		copy_byte_stream (string -> length, (BYTE*)(string -> address), (BYTE*)(c_ptr));
		c_ptr += string -> length;
	}

    va_end (args);	// clears list

	return big_str;
}

bool are_strings_equal (String* string1, String* string2)  {
	if (string1 == NULL || string2 == NULL) {
		perror ("One or Both given string does not exist");
		return false;
	}

	bool result = true;
	size_t i;

	if (string1 -> length != string2 -> length) {
		result = false;
	} else {
		for (i = 0; i < string1 -> length; i++) {
			if (*(string1 -> address + i) != *(string2 -> address + i)) {
				result = false;
				break;
			}
		}
	}

	return result;
}

String* append_integer_to_raw_string (char* str, int number) {
	String* string = create_string (0, NULL);
	int str_length = (str == NULL) ? 0 : strlen (str);

	char* number_str_buffer = NULL;
	ssize_t number_str_length = snprintf (NULL, 0, "%d", number);
	number_str_buffer = malloc (number_str_length + 1);
	snprintf (number_str_buffer, number_str_length + 1, "%d", number);

	string -> length = str_length + number_str_length;
	string -> address = malloc (string -> length);

	char* ptr = string -> address;

	ptr = memcpy (ptr, str, str_length);
	ptr += str_length;
	ptr = memcpy (ptr, number_str_buffer, number_str_length);

	free (number_str_buffer);

	return string;
}

bool is_string_memory_erased (void** string_addresses) {
	if (NULL == string_addresses) {
		return false;
	}

	bool status = true;

	if (
		!check_mem_zero (*(string_addresses + 0), sizeof (void*))
		&& !check_mem_zero (*(string_addresses + 1), sizeof (void*))
		&& !check_mem_zero (*(string_addresses + 2), sizeof (void*))
	) {
		status = false;
	}

	return status;
}

void** capture_string_addresses (String* string) {
	if (NULL == string) {
		return NULL;
	}

	void** addresses = malloc (3 * sizeof (void*));
	log_memory (DS_Raw, 3 * sizeof (void*), addresses, true);

	*(addresses + 0) = &(string);	// base address
	*(addresses + 1) = &(string -> length);
	*(addresses + 2) = &(string -> address);

	return addresses;
}

void display_N_characters (char character, size_t repetitions) {
	for (size_t i = 0; i < repetitions; i++) {
		putchar (character);
	}
}
