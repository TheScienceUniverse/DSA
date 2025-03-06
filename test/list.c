#include "../include/test.h"

void test_list (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [List]\n" RESET_STYLE);

	List* list = create_list (100);
//	display_chunk_properties (chunk);

	uint16_t x = 0x0ff0;
	int n = 0;
	char* str = "HelloWorld";
	Data* data;

	TEST (NULL != list, "List created");
	TEST (0 == list -> item_count, "List has no items");
	TEST (NULL != list -> head_chunk, "List has starting buffer chunk");
	TEST (0 == list -> head_chunk -> id, "List has start id check");
	TEST (50 == list -> head_chunk -> capacity, "List has first chunk with default capacity");
	TEST (list -> tail_chunk == list -> head_chunk, "List last chunk is same as the first chunk");
	TEST (0 == list -> head_chunk -> data_count, "List default data count check");
	TEST (list -> head_chunk == list -> tail_chunk, "List's first chunk is the last chunk");

	for (int i = 0; i < 10; i++) {
		x ^= 0xffff;
		data = create_data (DT_Binary, sizeof (uint16_t), &x);
		insert_data_into_list (list, data);
		delete_data (&data);

		n += 10;
		data = create_data (DT_Integer, sizeof (int), &n);
		insert_data_into_list (list, data);
		delete_data (&data);

		data = create_data (DT_String, 5, str);
		insert_data_into_list (list, data);
		delete_data (&data);
	}

//	display_linked_chunks (list -> head_chunk);
//	printf ("list item count: %lu\n", list -> item_count);

	TEST (30 == list -> item_count, "List filled with data");

	data = create_data (DT_String, 5, str);
	List* index_list = search_data_in_list (list, data);
	delete_data (&data);

/*
void insert_data_into_list (List* list, void* data);
size_t search_data_in_list (List* list, Data* data);
bool remove_data_from_list (List* list, Data* address);
*/
/*	List* last_chunk = get_last_chunk (chunk);

	TEST (NULL != last_chunk, "Last chunk exists");
	TEST (0 < last_chunk -> id, "Data inserted into chunk");
	TEST (59 == last_chunk -> id, "Last chunk id check");
	TEST (10 == last_chunk -> data_count, "Last chunk filled with data");

	for (int i = 0; i < 300; i++) {
		data = delete_data_from_chunk (chunk);
		// display_data (data);
		delete_data (&data);
	}

	last_chunk = get_last_chunk (chunk);

	TEST (NULL != last_chunk, "Last chunk exists");
	TEST (29 == last_chunk -> id, "Last chunk id check");
	TEST (0 < last_chunk -> id, "Data deleted from chunk");
	TEST (10 == last_chunk -> data_count, "Last chunk filled with data");

	for (int i = 0; i < 500; i++) {
		data = delete_data_from_chunk (chunk);
		// display_data (data);
		delete_data (&data);
	}

	// display_linked_chunks (chunk);
	last_chunk = get_last_chunk (chunk);

	TEST (NULL != last_chunk, "Last chunk exists");
	TEST (0 == last_chunk -> id, "Last chunk id check");
	TEST (0 == last_chunk -> id, "All chunks empty");
	TEST (0 == last_chunk -> data_count, "Last chunk empty");

	delete_chunk (&chunk);
*/
//	printf("%lu\n", sysconf(_SC_PAGESIZE) / sizeof(void*));


	delete_list (&list);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [List]\n" RESET_STYLE);
}
