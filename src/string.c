#include "../include/string.h"

void display_raw_string (int length, char* address) {
	for (int i = 0; i < length; i++) {
		printf ("%c", *(address + i));
	}
}

char* char_array_to_pointer (int length, char* str) {
	char* string = (char*) malloc (length);
	string = memcpy (string, str, length);
	return string;
}

String* create_string (int length, char* str) {
	String* string = (String*) malloc (sizeof (String));

	if (string != NULL) {
		string -> length = 0;
		string -> address = NULL;
	}

	if (length > 0 && str != NULL) {
		string -> length = length;
		string -> address = malloc (length);

		if (string -> address != NULL) {
			string -> address = char_array_to_pointer (length, str);
		}
	}

	return string;
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

void delete_string (String** string_address) {
	if (*string_address == NULL) {
		// perror ("String is empty to delete!");
		return;
	}

	String* string = *string_address;

	if (string -> address != NULL) {
		ERASE (&string -> address);
	}

	string = NULL;
	ERASE (string_address);
}

void display_string_properties (String* string) {
	printf ("String [%d]: ", string -> length);
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

void concatenate_strings (int count, ...) {
	printf ("%d\n", count);
	String *string = create_string(0, "");
	display_string(string);
	delete_string (&string);
}

bool are_strings_equal (String* string1, String* string2)  {
	if (string1 == NULL || string2 == NULL) {
		perror ("One or Both given string does not exist");
		return false;
	}

	bool result = true;
	int i;

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