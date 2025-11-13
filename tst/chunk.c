#include "../inc/test.h"

void test_Chunk (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Chunk]\n" RESET_STYLE);

	Chunk* chunk = create_Chunk (0, 10);
//	display_chunk_properties (chunk);

	uint16_t x = 0x0ff0;
	int n = 0;
	char* str = "HelloWorld";
	Data* data;

	TEST (NULL != chunk, "Chunk created");
	TEST (0 == chunk -> id, "Chunk start id check");
	TEST (10 == chunk -> capacity, "Chunk default capacity check");
	TEST (0 == chunk -> data_count, "Chunk default data count check");

	for (int i = 0; i < 200; i++) {
		x ^= 0xffff;
		data = create_Data (DT_Binary, sizeof (uint16_t), &x);
		insert_Data_into_Chunk (chunk, data);
		delete_Data (&data);

		n += 10;
		data = create_Data (DT_Integer, sizeof (int), &n);
		insert_Data_into_Chunk (chunk, data);
		delete_Data (&data);

		data = create_Data (DT_String, 5, str);
		insert_Data_into_Chunk (chunk, data);
		delete_Data (&data);
	}

	TEST (10 == chunk -> data_count, "Chunk filled with data");

	Chunk* last_chunk = get_last_Chunk_reference (chunk);

	TEST (NULL != last_chunk, "Last chunk exists");
	TEST (0 < last_chunk -> id, "Data inserted into chunk");
	TEST (59 == last_chunk -> id, "Last chunk id check");
	TEST (10 == last_chunk -> data_count, "Last chunk filled with data");

	for (int i = 0; i < 300; i++) {
		data = remove_Data_from_Chunk (chunk);
		// display_data (data);
		delete_Data (&data);
	}

	last_chunk = get_last_Chunk_reference (chunk);

	TEST (NULL != last_chunk, "Last chunk exists");
	TEST (29 == last_chunk -> id, "Last chunk id check");
	TEST (0 < last_chunk -> id, "Data deleted from chunk");
	TEST (10 == last_chunk -> data_count, "Last chunk filled with data");

	for (int i = 0; i < 500; i++) {
		data = remove_Data_from_Chunk (chunk);
		// display_data (data);
		delete_Data (&data);
	}

	// display_linked_chunks (chunk);
	last_chunk = get_last_Chunk_reference (chunk);

	TEST (NULL != last_chunk, "Last chunk exists");
	TEST (0 == last_chunk -> id, "Last chunk id check");
	TEST (0 == last_chunk -> id, "All chunks empty");
	TEST (0 == last_chunk -> data_count, "Last chunk empty");


	Chunk* test_chunk = duplicate_Chunk (chunk);
	TEST (NULL != test_chunk, "Created duplicate chunk");
	TEST (Cmp_Equivalent == compare_Chunks (chunk, test_chunk), "Compared duplicated chunk");
	delete_Chunk (&test_chunk);

	delete_Chunk (&chunk);
	TEST (NULL == chunk, "Deleted chunk");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Chunk]\n" RESET_STYLE);
}
