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

void display_N_characters (char character, size_t repetitions) {
	for (size_t i = 0; i < repetitions; i++) {
		putchar (character);
	}
}

String* create_String (size_t length, char* text) {
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

			copy_raw_bytes (length, (BYTE*) text, (BYTE*)(string -> text));
		}
	}

	return string;
}

String* duplicate_String (String* old_string) {
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

void display_String (String* string) {
	if (string == NULL) {
		// perror ("String does not exist to display!");
		return;
	}

	if (
		0 == string -> length
		|| NULL == string -> text
	) {
		perror ("String text does not exist to display!");
		return;
	}

	display_raw_string (string -> length, string -> text);
}

void display_String_details (String* string) {
	if (NULL == string) {
		perror ("String does not exist to display details!");
		return;
	}

	printf ("String :=> Address: (%p) Length: (%lu) Text: [", string, string -> length);
	display_raw_string (string -> length, string -> text);
	printf ("]");
	putchar ('\n');
}

void delete_String (String** string_address) {
	if (*string_address == NULL) {
		// perror ("String is empty to delete!");
		return;
	}

	String* string = *string_address;

	if (NULL != string && string -> text != NULL && string -> length > 0) {
		log_memory (DS_Raw, (string -> length) * sizeof (char), string -> text, false);
		ERASE (&(string -> text), string -> length);
	}

	string = NULL;

	log_memory (DS_String, sizeof (String), *string_address, false);
	ERASE (string_address, sizeof (String));
}

String* concatenate_Strings (int count, ...) {
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

	String *big_str = create_String (0, "");
	
	big_str -> text = (char*) malloc (sizeof (char) * combined_length);

	if (NULL == big_str -> text) {
		delete_String (&big_str);
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

		copy_raw_bytes (string -> length, (BYTE*)(string -> text), (BYTE*) ptr);
		ptr += string -> length;
	}

    va_end (args);	// clears list

	return big_str;
}

String* append_integer_to_raw_string (char* text, int number) {
	String* string = create_String (0, NULL);
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
	number_str_buffer = NULL;

	return string;
}

bool is_String_memory_erased (void** string_addresses) {
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

void** capture_String_addresses (String* string) {
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

Compare_Status compare_Strings (String* string1, String* string2) {
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

char get_char_at (String* string, size_t index) {
	if (NULL == string) {
		perror ("Given string does not exist to get char at index!");
		return 0;
	}

	if (string -> length < index) {
		perror ("Given index out of bound to get char at index!");
		return 0;
	}

	char* ptr = string -> text;

	for (size_t i = 0; i < index; i++) {
		ptr++;
	}

	return *ptr;
}

ssize_t get_char_first_index (String* string, char character) {
	if (NULL == string) {
		perror ("Given string does not exist to get character's first index!");
		return -1;
	}

	char* ptr = string -> text;
	ssize_t idx = 0;

	for (idx = 0; idx < (ssize_t)(string -> length); idx++) {
		if (character == *ptr++) {
			break;
		}
	}

	if (idx >= (ssize_t)(string -> length)) {
		idx = -1;
	}

	return idx;
}

ssize_t get_char_last_index (String* string, char character) {
	if (NULL == string) {
		perror ("Given string does not exist to get character's last index!");
		return -1;
	}

	char* ptr = string -> text + string -> length - 1;
	ssize_t idx = 0;

	for (idx = (ssize_t)(string -> length) - 1; idx >= 0; idx--) {
		if (character == *ptr--) {
			break;
		}
	}

	if (idx >= (ssize_t)(string -> length)) {
		idx = -1;
	}

	return idx;
}

String* get_sub_String (String* string, ssize_t start_index, ssize_t end_index) {
	/*
	 * Rules:
	 * let str [5] = "01234"	// according to index
	 * substring (1, 3) = "123"	// +ve length => forward direction
	 * substring (4, 1) = "4321"	// -ve length => reverse direction
	 * substring (-10, 10) = "01234"	// max forward limit is string length
	 * substring (10, -10) = "43210"	// -ve start index => lenght - start index
	 * substring (-10, -100) = "0"	// max backward limit is 0
	 * anything else will return NULL
	*/

	if (NULL == string) {
		perror ("Given string does not exist to get sub-str!");
		return NULL;
	}

	int increment = +1;

	if (start_index > end_index) {
	//	end_index = start_index ^ end_index ^ (start_index = end_index);
		increment = -1;
	}

	if (start_index < 0) {
		start_index = 0;
	} else if (start_index >= (ssize_t) string -> length) {
		start_index = string -> length - 1;
	}

	if (end_index < 0) {
		end_index = 0;
	} else if (end_index >= (ssize_t) string -> length) {
		end_index = string -> length - 1;
	}

	size_t length = labs (end_index - start_index) + 1;

	char* src_ptr = string -> text + start_index;

	String* sub_string = create_String (length, NULL);
	sub_string -> text = malloc (length * sizeof (char));
	sub_string -> length = length;

	char* dst_ptr = sub_string -> text;

	for (size_t i = 0; i < length; i++) {
		*dst_ptr++ = *src_ptr;
		src_ptr += increment;
	}

	return sub_string;
}

String* get_sub_Str (String* string, ssize_t start_index, ssize_t length) {
	/*
	 * Rules:
	 * let str [5] = "01234"	// according to index
	 * substr (0, +3) = "012"	// +ve length => forward direction
	 * substr (3, -3) = "321"	// -ve length => reverse direction
	 * substr (0, 10) = "01234"	// max forward limit is string length
	 * substr (-2, -3) = "321"	// -ve start index => lenght - start index
	 * substr (-3, -10) = "210"	// max backward limit is 0
	 * anything else will return NULL
	*/

	if (NULL == string) {
		perror ("Given string does not exist to get sub-str!");
		return NULL;
	}

	if (labs (start_index) >= string -> length) {
		perror ("Given start index is out of bound to get sub-str!");
		return NULL;
	}

	if (0 == length) {
		perror ("Given length is invalid to get sub-str!");
		return NULL;
	}

	if (start_index < 0) {
		start_index += string -> length;
	}

	// setting up the direction
	int increment = +1;	// forward

	if (length > (ssize_t) string -> length - start_index) {
		length = string -> length - start_index;
	} else if (length < 0) {
		length = start_index + 1;
		increment = -1;	// reverse
	}

	char* src_ptr = string -> text + start_index;

	String* sub_str = create_String (length, NULL);
	sub_str -> text = malloc (length * sizeof (char));
	sub_str -> length = length;

	char* dst_ptr = sub_str -> text;

	for (size_t i = 0; i < (size_t) length; i++) {
		*dst_ptr++ = *src_ptr;
		src_ptr += increment;
	}

	return sub_str;
}

String* get_upper_case_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to get upper-case string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to get upper-case string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to get upper-case string!");
		return NULL;
	}

	String* upr_str = duplicate_String (string);
	char* ptr = upr_str -> text;

	for (size_t i = 0; i < string -> length; i++) {
		*ptr = toupper (*ptr);
		ptr++;
	}

	return upr_str;
}

String* get_lower_case_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to get lower-case string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to get lower-case string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to get lower-case string!");
		return NULL;
	}

	String* lwr_str = duplicate_String (string);
	char* ptr = lwr_str -> text;

	for (size_t i = 0; i < string -> length; i++) {
		*ptr = tolower (*ptr);
		ptr++;
	}

	return lwr_str;
}

String* swap_String_case (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to swap string's case!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to swap string's case!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to swap string's case!");
		return NULL;
	}

	String* swp_str = duplicate_String (string);
	char* ptr = swp_str -> text;

	for (size_t i = 0; i < string -> length; i++) {
		if (isupper (*ptr)) {
			*ptr = tolower (*ptr);
		} else if (islower (*ptr)) {
			*ptr = toupper (*ptr);
		}

		ptr++;
	}

	return swp_str;
}

String* capitalize_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to capitalize string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to capitalize string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to capitalize string!");
		return NULL;
	}

	String* cap_str = get_lower_case_String (string);

	*((char*)(cap_str -> text) + 0) = toupper (*((char*)(cap_str -> text) + 0));

	return cap_str;
}

String* get_title_case_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to get title-case string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to get title-case string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to get title-case string!");
		return NULL;
	}

	String* ttl_str = duplicate_String (string);
	char* ptr = ttl_str -> text;
	bool first_letter = true;

	for (size_t i = 0; i < string -> length; i++) {
		if (*ptr == ' ') {
			first_letter = true;
			ptr++;
			continue;
		}

		if (first_letter) {
			first_letter = false;
			*ptr = toupper (*ptr);
		} else {
			*ptr = tolower (*ptr);
		}

		ptr++;
	}

	return ttl_str;
}

String* get_pascal_case_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to get pascal-case string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to get pascal-case string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to get pascal-case string!");
		return NULL;
	}

	size_t valid_char_count = 0;
	size_t i;
	char* src_ptr = string -> text;

	for (i = 0; i < string -> length; i++) {
		if (isalnum (*src_ptr++)) {
			++valid_char_count;
		}
	}

	src_ptr = string -> text;

	String* pcl_str = create_String (0, NULL);
	pcl_str -> text = malloc (valid_char_count * sizeof (char));
	pcl_str -> length = valid_char_count;

	char* dst_ptr = pcl_str -> text;
	bool first_letter = true;

	for (i = 0; i < string -> length; i++) {
		if (!isalnum (*src_ptr)) {
			first_letter = true;
			src_ptr++;
			continue;
		}

		if (first_letter) {
			first_letter = false;
			*dst_ptr++ = toupper (*src_ptr++);
		} else {
			*dst_ptr++ = tolower (*src_ptr++);
		}
	}

	return pcl_str;
}

String* get_camel_case_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to get camel-case string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to get camel-case string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to get camel-case string!");
		return NULL;
	}

	String* cml_str = get_pascal_case_String (string);

	if (NULL != cml_str) {
		*((char*)(cml_str -> text) + 0) = tolower (*((char*)(cml_str -> text) + 0));
	}

	return cml_str;
}

String* get_snake_case_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to get snake-case string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to get snake-case string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to get snake-case string!");
		return NULL;
	}

/*
 * Rules:
 * (A)(1)(A) => (a)_(1)_(a)
 * (A)(@)(A) => (a)_(a)
 * (A)(@)(1)(A) => (a)_(1)_(a)
 * (A)(_)(1) => (a)_(1)
*/

	char* src_ptr = string -> text;
	size_t length = 0;
	size_t i;
	char prev_char = 0;
	char curr_char = 0;

	for (i = 0; i < string -> length; i++) {
		prev_char = curr_char;
		curr_char = *src_ptr++;

		if (isalpha (prev_char) && isalpha (curr_char)) {
			++length;
		}

		if (isdigit (prev_char) && isdigit (curr_char)) {
			++length;
		}

		if (!isalnum (prev_char) && !isalnum (curr_char)) {
			// do nothing
		}

		if (isalpha (prev_char) && isdigit (curr_char)) {
			length += 2;
		}

		if (isdigit (prev_char) && isalpha (curr_char)) {
			length += 2;
		}

		if (!isalnum (prev_char) && isalpha (curr_char)) {
			++length;
		}

		if (isalpha (prev_char) && !isalnum (curr_char)) {
			++length;
		}

		if (!isalnum (prev_char) && isdigit (curr_char)) {
			++length;
		}

		if (isdigit (prev_char) && !isalnum (curr_char)) {
			++length;
		}
	}

	src_ptr = string -> text;

	String* snk_str = create_String (0, NULL);
	snk_str -> text = malloc (length * sizeof (char));
	snk_str -> length = length;

	char* dst_ptr = snk_str -> text;

	for (i = 0; i < string -> length; i++) {
		prev_char = curr_char;
		curr_char = *src_ptr++;

		if (isalpha (prev_char) && isalpha (curr_char)) {
			*dst_ptr++ = tolower (curr_char);
		}

		if (isdigit (prev_char) && isdigit (curr_char)) {
			*dst_ptr++ = curr_char;
		}

		if (!isalnum (prev_char) && !isalnum (curr_char)) {
			// do nothing
		}

		if (isalpha (prev_char) && isdigit (curr_char)) {
			*dst_ptr++ = '_';
			*dst_ptr++ = curr_char;
		}

		if (isdigit (prev_char) && isalpha (curr_char)) {
			*dst_ptr++ = '_';
			*dst_ptr++ = tolower (curr_char);
		}

		if (!isalnum (prev_char) && isalpha (curr_char)) {
			*dst_ptr++ = tolower (curr_char);
		}

		if (isalpha (prev_char) && !isalnum (curr_char)) {
			*dst_ptr++ = '_';
		}

		if (!isalnum (prev_char) && isdigit (curr_char)) {
			*dst_ptr++ = curr_char;
		}

		if (isdigit (prev_char) && !isalnum (curr_char)) {
			*dst_ptr++ = '_';
		}
	}

	return snk_str;
}

String* get_kebab_case_String (String* string) {
	if (NULL == string) {
		perror ("Given string does not exist to get kebab-case string!");
		return NULL;
	}

	if (NULL == string -> text) {
		perror ("Given string's text does not exist to get kebab-case string!");
		return NULL;
	}

	if (0 == string -> length) {
		perror ("Given string is empty to get kebab-case string!");
		return NULL;
	}

/*
 * Rules:
 * (A)(1)(A) => (a)-(1)-(a)
 * (A)(@)(A) => (a)-(a)
 * (A)(@)(1)(A) => (a)-(1)-(a)
 * (A)(_)(1) => (a)-(1)
*/

	char* src_ptr = string -> text;
	size_t length = 0;
	size_t i;
	char prev_char = 0;
	char curr_char = 0;

	for (i = 0; i < string -> length; i++) {
		prev_char = curr_char;
		curr_char = *src_ptr++;

		if (isalpha (prev_char) && isalpha (curr_char)) {
			++length;
		}

		if (isdigit (prev_char) && isdigit (curr_char)) {
			++length;
		}

		if (!isalnum (prev_char) && !isalnum (curr_char)) {
			// do nothing
		}

		if (isalpha (prev_char) && isdigit (curr_char)) {
			length += 2;
		}

		if (isdigit (prev_char) && isalpha (curr_char)) {
			length += 2;
		}

		if (!isalnum (prev_char) && isalpha (curr_char)) {
			++length;
		}

		if (isalpha (prev_char) && !isalnum (curr_char)) {
			++length;
		}

		if (!isalnum (prev_char) && isdigit (curr_char)) {
			++length;
		}

		if (isdigit (prev_char) && !isalnum (curr_char)) {
			++length;
		}
	}

	src_ptr = string -> text;

	String* kbb_str = create_String (0, NULL);
	kbb_str -> text = malloc (length * sizeof (char));
	kbb_str -> length = length;

	char* dst_ptr = kbb_str -> text;

	for (i = 0; i < string -> length; i++) {
		prev_char = curr_char;
		curr_char = *src_ptr++;

		if (isalpha (prev_char) && isalpha (curr_char)) {
			*dst_ptr++ = tolower (curr_char);
		}

		if (isdigit (prev_char) && isdigit (curr_char)) {
			*dst_ptr++ = curr_char;
		}

		if (!isalnum (prev_char) && !isalnum (curr_char)) {
			// do nothing
		}

		if (isalpha (prev_char) && isdigit (curr_char)) {
			*dst_ptr++ = '-';
			*dst_ptr++ = curr_char;
		}

		if (isdigit (prev_char) && isalpha (curr_char)) {
			*dst_ptr++ = '-';
			*dst_ptr++ = tolower (curr_char);
		}

		if (!isalnum (prev_char) && isalpha (curr_char)) {
			*dst_ptr++ = tolower (curr_char);
		}

		if (isalpha (prev_char) && !isalnum (curr_char)) {
			*dst_ptr++ = '-';
		}

		if (!isalnum (prev_char) && isdigit (curr_char)) {
			*dst_ptr++ = curr_char;
		}

		if (isdigit (prev_char) && !isalnum (curr_char)) {
			*dst_ptr++ = '-';
		}
	}

	return kbb_str;
}

String* prepend_chars_to_String (String* string, size_t n, char c) {
	if (NULL == string) {
		perror ("No string is provided to prepend characters to!");
		return NULL;
	}

	String* new_string = create_String (0, NULL);

	new_string -> length = string -> length + n;
	new_string -> text = (char*) malloc ((new_string -> length) * sizeof (char));

	if (NULL == string -> text) {
		perror ("Unable to allocate memory to prepend characters!");
		delete_String (&new_string);
		return NULL;
	}

	log_memory (DS_Raw, (new_string -> length) * sizeof (char), new_string -> text, true);

	char* src_ptr = string -> text;
	char* dst_ptr = new_string -> text;

	for (size_t i = 0; i < n; i++) {
		*dst_ptr++ = c;
	}

	for (size_t i = 0; i < string -> length; i++) {
		*dst_ptr++ = *src_ptr++;
	}

	return new_string;
}

String* append_chars_to_String (String* string, size_t n, char c) {
	if (NULL == string) {
		perror ("No string is provided to prepend characters to!");
		return NULL;
	}

	String* new_string = create_String (0, NULL);

	new_string -> length = string -> length + n;
	new_string -> text = (char*) malloc ((new_string -> length) * sizeof (char));

	if (NULL == string -> text) {
		perror ("Unable to allocate memory to prepend characters!");
		delete_String (&new_string);
		return NULL;
	}

	log_memory (DS_Raw, (new_string -> length) * sizeof (char), new_string -> text, true);

	char* src_ptr = string -> text;
	char* dst_ptr = new_string -> text;

	for (size_t i = 0; i < string -> length; i++) {
		*dst_ptr++ = *src_ptr++;
	}

	for (size_t i = 0; i < n; i++) {
		*dst_ptr++ = c;
	}

	return new_string;
}

String* reverse_String (String* string) {
	if (NULL == string) {
		perror ("String is not provided to reverse!");
		return NULL;
	}

	String* rev_str = duplicate_String (string);

	size_t half_index = (string -> length) >> 1;
	char c;

	if ((string -> length) & 0x1) {
		++half_index;
	}

	char* head_ptr = rev_str -> text;
	char* tail_ptr = rev_str -> text + rev_str -> length - 1;

	for (size_t i = 0; i < half_index; i++) {
		c = *head_ptr;
		*head_ptr = *tail_ptr;
		*tail_ptr = c;

		head_ptr++;
		tail_ptr--;
	}

	return rev_str;
}

String* get_String_from_integer (int number) {
	size_t num_digits = get_number_of_digits (number, 10);
	String* string = create_String (0, NULL);

	string -> text = (char*) malloc (num_digits * sizeof (char));

	if (NULL == string -> text) {
		perror ("Unable to allocate memory to convert integer to string!");
	}

	log_memory (DS_Raw, num_digits * sizeof (char), string -> text, true);
	string -> length = num_digits * sizeof (char);

	char* ptr = string -> text;

	for (size_t i = 0; i < num_digits; i++) {
		*ptr++ = '0' + (number % 10);
		number /= 10;
	}

	String* tmp_str = string;
	string = reverse_String (string);
	delete_String (&tmp_str);

	return string;
}
