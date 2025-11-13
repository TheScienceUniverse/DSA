#include "../inc/stream.h"

void copy_raw_byte_stream (size_t length, BYTE* src_addr, BYTE* dst_addr) {
	for (size_t i = 0; i < length; i++) {
		*dst_addr++ = *src_addr++;
	}
}

bool compare_raw_byte_stream (size_t length, BYTE* base_addr_1, BYTE* base_addr_2) {
	if (base_addr_1 == base_addr_2) {
		return true;
	}

	bool result = true;
	BYTE* b1 = base_addr_1;
	BYTE* b2 = base_addr_2;

	for (size_t i = 0; i < length; ++i) {
		if (*b1++ != *b2++) {
			result = false;
			break;
		}
	}

	return result;
}

Stream* create_Stream (size_t length, BYTE* base_addr) {
	Stream* stream = (Stream*) malloc (sizeof (Stream));

	if (stream != NULL) {
		log_memory (DS_Stream, sizeof (Stream), stream, true);

		stream -> length = 0;
		stream -> base_addr = NULL;
	}

	if (length > 0 && base_addr != NULL) {
		stream -> length = length;
		stream -> base_addr = (BYTE*) malloc (length * sizeof (BYTE));

		if (stream -> base_addr != NULL) {
			log_memory (DS_Raw, length * sizeof (BYTE), stream -> base_addr, true);

			copy_raw_byte_stream (length, base_addr, stream -> base_addr);
		}
	}

	return stream;
}

void delete_Stream (Stream** stream_address) {
	if (*stream_address == NULL) {
		// perror ("Stream is empty to delete!");
		return;
	}

	Stream* stream = *stream_address;

	if (stream -> base_addr != NULL && stream -> length > 0) {
		log_memory (DS_Raw, (stream -> length) * sizeof (BYTE), stream -> base_addr, false);
		ERASE (&(stream -> base_addr), stream -> length);
	}

	stream = NULL;

	log_memory (DS_Stream, sizeof (Stream), *stream_address, false);
	ERASE (stream_address, sizeof (Stream));
}

void display_Stream (Stream* stream) {
	if (stream == NULL) {
		return;
	}

	BYTE* ptr = stream -> base_addr;

	for (size_t i = 0; i < stream -> length; i++) {
		printf ("%02x", *ptr++);
	}
}

void display_Stream_details (Stream* stream) {
	if (NULL == stream) {
		perror ("Stream does not exist to display details!");
		return;
	}

	printf ("Stream :=> Address: (%p) Length: (%lu) Data: [", stream, stream -> length);
	display_Stream (stream);
	printf ("]");
	ENDL();
}
/*
 *
Stream* duplicate_stream (Stream* old_stream) {
	if (old_stream == NULL) {
		return NULL;
	}

	Stream* new_stream = (Stream*) malloc (sizeof (Stream));

	if (new_stream != NULL) {
		new_stream -> length = 0;
		new_stream -> base_addr = NULL;
	}

	if (old_stream -> length > 0 && old_stream -> base_addr != NULL) {
		new_stream -> length = old_stream -> length;
		new_stream -> base_addr = malloc (old_stream -> length);

		if (new_stream -> base_addr != NULL) {
			new_stream -> base_addr = memcpy (new_stream -> base_addr, old_stream -> base_addr, new_stream -> length);
		}
	}

	return new_stream;
}

Stream* concatenate_streams (int count, ...) {
	if (
		count < 2
		|| count > 10
	) {
		perror ("Number of streams out of accepted bound [2-10]!");
		return NULL;
	}

	size_t combined_length = 0;

	va_list args;
	va_start (args, count);	// initialize list

	Stream* stream;

	for (int i = 0; i < count; i++) {
		stream = va_arg (args, Stream*);

		if (NULL == stream) {
			continue;
		}

		combined_length += stream -> length;
	}

    va_end (args);	// clears list

	Stream *big_str = create_stream (0, "");
	
	big_str -> base_addr = (char*) malloc (sizeof (char) * combined_length);

	if (NULL == big_str -> base_addr) {
		delete_stream (&big_str);
		perror ("Unable to allocate sufficient memory of combined length!");
		return NULL;
	}

	big_str -> length = combined_length;

	char* ptr = big_str -> base_addr;

	va_start (args, count);	// initialize list

	for (int i = 0; i < count; i++) {
		stream = va_arg (args, Stream*);

		if (NULL == stream) {
			continue;
		}

		copy_raw_bytes (stream -> length, (BYTE*)(stream -> base_addr), (BYTE*) ptr);
		ptr += stream -> length;
	}

    va_end (args);	// clears list

	return big_str;
}

Stream* append_integer_to_raw_stream (char* text, int number) {
	Stream* stream = create_stream (0, NULL);
	int text_length = (text == NULL) ? 0 : strlen (text);

	char* number_str_buffer = NULL;
	ssize_t number_str_length = snprintf (NULL, 0, "%d", number);
	number_str_buffer = malloc (number_str_length + 1);
	snprintf (number_str_buffer, number_str_length + 1, "%d", number);

	stream -> length = text_length + number_str_length;
	stream -> base_addr = malloc (stream -> length);

	char* ptr = stream -> base_addr;

	ptr = memcpy (ptr, text, text_length);
	ptr += text_length;
	ptr = memcpy (ptr, number_str_buffer, number_str_length);

	free (number_str_buffer);

	return stream;
}

bool is_stream_memory_erased (void** stream_addresses) {
	if (NULL == stream_addresses) {
		return false;
	}

	bool status = true;

	if (
		!check_mem_zero (*(stream_addresses + 0), sizeof (void*))
		&& !check_mem_zero (*(stream_addresses + 1), sizeof (void*))
		&& !check_mem_zero (*(stream_addresses + 2), sizeof (void*))
	) {
		status = false;
	}

	return status;
}

void** capture_stream_addresses (Stream* stream) {
	if (NULL == stream) {
		return NULL;
	}

	void** addresses = malloc (3 * sizeof (void*));
	log_memory (DS_Raw, 3 * sizeof (void*), addresses, true);

	*(addresses + 0) = &(stream);	// base address
	*(addresses + 1) = &(stream -> length);
	*(addresses + 2) = &(stream -> base_addr);

	return addresses;
}

void display_N_characters (char character, size_t repetitions) {
	for (size_t i = 0; i < repetitions; i++) {
		putchar (character);
	}
}

Compare_Status compare_streams (Stream* stream1, Stream* stream2) {
	if (stream1 == stream2) {
		return Cmp_Identical;
	}

	if (stream1 == NULL || stream2 == NULL) {
		perror ("One or Both given stream does not exist");
		return Cmp_Different;
	}

	if (stream1 -> length != stream2 -> length) {
		return Cmp_Different;
	}

	Compare_Status cmp_stat = Cmp_Equivalent;
	char* ptr1 = stream1 -> base_addr;
	char* ptr2 = stream2 -> base_addr;

	for (size_t i = 0; i < stream1 -> length; i++) {
		if (*ptr1++ != *ptr2++) {
			cmp_stat = Cmp_Different;
			break;
		}
	}

	return cmp_stat;
}

char get_char_at (Stream* stream, size_t index) {
	if (NULL == stream) {
		perror ("Given stream does not exist to get char at index!");
		return 0;
	}

	if (stream -> length < index) {
		perror ("Given index out of bound to get char at index!");
		return 0;
	}

	char* ptr = stream -> base_addr;

	for (size_t i = 0; i < index; i++) {
		ptr++;
	}

	return *ptr;
}

ssize_t get_char_first_index (Stream* stream, char character) {
	if (NULL == stream) {
		perror ("Given stream does not exist to get character's first index!");
		return -1;
	}

	char* ptr = stream -> base_addr;
	ssize_t idx = 0;

	for (idx = 0; idx < (ssize_t)(stream -> length); idx++) {
		if (character == *ptr++) {
			break;
		}
	}

	if (idx >= (ssize_t)(stream -> length)) {
		idx = -1;
	}

	return idx;
}

ssize_t get_char_last_index (Stream* stream, char character) {
	if (NULL == stream) {
		perror ("Given stream does not exist to get character's last index!");
		return -1;
	}

	char* ptr = stream -> base_addr + stream -> length - 1;
	ssize_t idx = 0;

	for (idx = (ssize_t)(stream -> length) - 1; idx >= 0; idx--) {
		if (character == *ptr--) {
			break;
		}
	}

	if (idx >= (ssize_t)(stream -> length)) {
		idx = -1;
	}

	return idx;
}*/
