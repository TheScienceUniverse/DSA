#include "../inc/test.h"

void test_stream (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Stream]\n" RESET_STYLE);

	char* text = "Hello, World!\n";
	size_t length = 14;

	Stream* stream = create_stream (length, (BYTE*) text);
	Stream* ghost_stream = stream;

	// printf ("%lu %lu\n", length, sizeof (stream -> text));

	// display_stream_details (stream);

	TEST (NULL != stream, "Checked address non-null");
	TEST (length == stream -> length, "Checked block-size allocation");
	TEST (stream == ghost_stream, "Checked address validation");
	TEST (compare_raw_byte_stream (length, (BYTE*) text, stream -> base_addr), "Matched expected content");

//	void** stream_addresses = capture_stream_addresses (stream);
//	TEST (!is_stream_memory_erased (stream_addresses), "Stream existance check");
	TEST (stream == ghost_stream, "Checked Stream existance");
	delete_stream (&stream);
	TEST (stream != ghost_stream, "Checked Stream deletion");

	//TEST (is_stream_memory_erased (stream_addresses), "Stream deletion check");
//	ERASE (&stream_addresses, 3 * sizeof (void*));
/*
	BYTE* ptr_b = (void*) stream;
	BYTE* ptr_adr = (void*) (stream -> address);
	BYTE* ptr_b_f = (void*) stream;

	for (size_t i = 0; i < sizeof (Stream); i++) {
		printf("%02x ", *ptr_b);
		ptr_b = ptr_b + 1;
	}

	printf("\n");

	delete_stream (&stream);

	for (size_t i = 0; i < sizeof (size_t); i++) {
		printf("%02x ", *ptr_adr);
		ptr_adr = ptr_adr + 1;
	}

	printf("\n");

	for (size_t i = 0; i < sizeof (Stream); i++) {
		printf ("%02x ", *ptr_b_f);
		ptr_b_f = ptr_b_f + 1;
	}

	printf("\n");
*/
//	TEST (NULL == stream, "Address nullified check");
//	TEST (sizeof (int*) == sizeof (stream), "De-allocated block-size check");
//	TEST (NULL == stream, "Address nullify check");
//	TEST (ptr != vptr, "Address validation check");
//	TEST (n != *((int*) vptr), "Content check");
/*
	Stream* str1 = create_stream (5, "Hello");
	Stream* str2 = create_stream (5, "World");
	stream = concatenate_streams (2, str1, str2);
	TEST (stream -> length == str1 -> length + str2 -> length, "Checked concatenated stream lengths");
	ghost_stream = create_stream (10, "HelloWorld");
	TEST (Cmp_Different != compare_streams (stream, ghost_stream), "Matched concatenated streams");
	delete_stream (&ghost_stream);
	delete_stream (&stream);
	delete_stream (&str1);
	delete_stream (&str2);
	stream = create_stream (5, "Radar");
	TEST (1 == get_char_first_index (stream, 'a'), "Matched first index of character in given Stream");
	TEST (3 == get_char_last_index (stream, 'a'), "Matched last index of character in given Stream");
	delete_stream (&stream);
*/
	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Stream]\n" RESET_STYLE);
}
