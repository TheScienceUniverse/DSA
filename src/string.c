#include "../inc/string.h"

void display_raw_string (size_t length, char* text) {
	char* ptr = text;

	for (size_t i = 0; i < length; i++) {
		printf ("%c", *ptr++);
	}
}

bool compare_raw_strings_shh (size_t length1, char* text1, size_t length2, char* text2) {
	if (length1 != length2) {
		return false;
	}

	if (text1 == text2) {
		return true;
	}

	bool result = true;
	char* c1 = text1;
	char* c2 = text2;

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
	char* text = (char*) malloc (sizeof (char) * length);
	text = memcpy (text, str, length);
	return text;
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

String* create_string (size_t length, char* text) {
	String* string = (String*) malloc (sizeof (String));

	if (string != NULL) {
		log_memory (DS_String, sizeof (String), string, true);

		string -> length = 0;
		string -> text = NULL;
	}

	if (length > 0 && text != NULL) {
		string -> length = length;
		string -> text = (char*) malloc (length * sizeof (char));

		if (string -> text != NULL) {
			log_memory (DS_Raw, length * sizeof (char), string -> text, true);

			copy_raw_char_stream (length, text, string -> text);
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

	if (string -> text != NULL && string -> length > 0) {
		log_memory (DS_Raw, (string -> length) * sizeof (char), string -> text, false);
		ERASE (&(string -> text), string -> length);
	}

	string = NULL;

	log_memory (DS_String, sizeof (String), *string_address, false);
	ERASE (string_address, sizeof (String));
}

void display_string (String* string) {
	if (string == NULL) {
		// perror ("String does not exist to display!");
		return;
	}

	display_raw_string (string -> length, string -> text);
}

void display_string_details (String* string) {
	if (NULL == string) {
		perror ("String does not exist to display details!");
		return;
	}

	printf ("String :=> Address: (%p) Length: (%lu) Text: [", string, string -> length);
	display_raw_string (string -> length, string -> text);
	printf ("]");
	putchar ('\n');
}

String* duplicate_string (String* old_string) {
	if (old_string == NULL) {
		return NULL;
	}

	String* new_string = (String*) malloc (sizeof (String));

	if (new_string != NULL) {
		new_string -> length = 0;
		new_string -> text = NULL;
	}

	if (old_string -> length > 0 && old_string -> text != NULL) {
		new_string -> length = old_string -> length;
		new_string -> text = malloc (old_string -> length);

		if (new_string -> text != NULL) {
			new_string -> text = memcpy (new_string -> text, old_string -> text, new_string -> length);
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
	
	big_str -> text = (char*) malloc (sizeof (char) * combined_length);

	if (NULL == big_str -> text) {
		delete_string (&big_str);
		perror ("Unable to allocate sufficient memory of combined length!");
		return NULL;
	}

	big_str -> length = combined_length;

	char* ptr = big_str -> text;

	va_start (args, count);	// initialize list

	for (int i = 0; i < count; i++) {
		string = va_arg (args, String*);

		if (NULL == string) {
			continue;
		}

		copy_byte_stream (string -> length, (BYTE*)(string -> text), (BYTE*) ptr);
		ptr += string -> length;
	}

    va_end (args);	// clears list

	return big_str;
}

String* append_integer_to_raw_string (char* text, int number) {
	String* string = create_string (0, NULL);
	int text_length = (text == NULL) ? 0 : strlen (text);

	char* number_str_buffer = NULL;
	ssize_t number_str_length = snprintf (NULL, 0, "%d", number);
	number_str_buffer = malloc (number_str_length + 1);
	snprintf (number_str_buffer, number_str_length + 1, "%d", number);

	string -> length = text_length + number_str_length;
	string -> text = malloc (string -> length);

	char* ptr = string -> text;

	ptr = memcpy (ptr, text, text_length);
	ptr += text_length;
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
	*(addresses + 2) = &(string -> text);

	return addresses;
}

void display_N_characters (char character, size_t repetitions) {
	for (size_t i = 0; i < repetitions; i++) {
		putchar (character);
	}
}

Compare_Status compare_strings (String* string1, String* string2) {
	if (string1 == string2) {
		return Cmp_Identical;
	}

	if (string1 == NULL || string2 == NULL) {
		perror ("One or Both given string does not exist");
		return Cmp_Different;
	}

	if (string1 -> length != string2 -> length) {
		return Cmp_Different;
	}

	Compare_Status cmp_stat = Cmp_Equivalent;
	char* ptr1 = string1 -> text;
	char* ptr2 = string2 -> text;

	for (size_t i = 0; i < string1 -> length; i++) {
		if (*ptr1++ != *ptr2++) {
			cmp_stat = Cmp_Different;
			break;
		}
	}

	return cmp_stat;
}
