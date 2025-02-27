#include "../include/test.h"

void test_chunk (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Chunk]\n" RESET_STYLE);

	Chunk* chunk = create_chunk (0, 10);
//	display_chunk_properties (chunk);

	uint16_t x = 0x0ff0;
	int n = 0;
	char* str = "HelloWorld";
	Data* data;

	for (int i = 0; i < 200; i++) {
		x ^= 0xffff;
		data = create_data (DT_Binary, sizeof (uint16_t), &x);
		insert_data_into_chunk (chunk, data);
		delete_data (&data);

		n += 10;
		data = create_data (DT_Integer, sizeof (int), &n);
		insert_data_into_chunk (chunk, data);
		delete_data (&data);

		data = create_data (DT_String, 5, str);
		insert_data_into_chunk (chunk, data);
		delete_data (&data);
	}

	display_linked_chunks (chunk);

	for (int i = 0; i < 300; i++) {
		data = delete_data_from_chunk (chunk);
		// display_data (data);
		delete_data (&data);
	}

	display_linked_chunks (chunk);

	for (int i = 0; i < 500; i++) {
		data = delete_data_from_chunk (chunk);
		// display_data (data);
		delete_data (&data);
	}

	display_linked_chunks (chunk);

	delete_chunk (&chunk);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Chunk]\n" RESET_STYLE);
}
