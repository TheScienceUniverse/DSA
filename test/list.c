#include "../include/test.h"

void test_list (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [List]\n" RESET_STYLE);

	List* list = create_list (100);
//	display_chunk_properties (chunk);

	uint16_t x = 0x0ff0;
	int n = 0;
	char* str = "Hello";
	Data* data;
	int i;

	TEST (NULL != list, "List created");
	TEST (0 == list -> item_count, "List has no items");
	TEST (NULL != list -> head_chunk, "List has starting buffer chunk");
	TEST (0 == list -> head_chunk -> id, "List has start id check");
	TEST (50 == list -> head_chunk -> capacity, "List has first chunk with default capacity");
	TEST (list -> tail_chunk == list -> head_chunk, "List last chunk is same as the first chunk");
	TEST (0 == list -> head_chunk -> data_count, "List default data count check");
	TEST (list -> head_chunk == list -> tail_chunk, "List's first chunk is the last chunk");

	for (i = 0; i < 10; i++) {
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

	display_list (list);
//	printf ("list item count: %lu\n", list -> item_count);

	TEST (30 == list -> item_count, "List filled with data");

	data = create_data (DT_String, 5, str);
	List* index_list = search_data_in_list (list, data);
	delete_data (&data);

	display_list (index_list);
	delete_list (&index_list);

	data = get_list_data_at_index (list, 14);
	display_data (data);
	printf ("\n");

//	printf ("first index: %lu\n", get_first_list_index_of_data (list, data));
//	printf ("first index: %lu\n", get_last_list_index_of_data (list, data));

	delete_data (&data);

	char* test_str = "XOXOX";
	data = create_data (DT_String, 5, test_str);

	insert_into_list_at_index (list, data, 10);
	display_list (list);

	delete_data (&data);


	List* test_list = create_list (10);

	data = create_empty_data ();
	data -> type = DT_Integer;
	data -> size = sizeof (int);
	data -> address = &i;
	
	for (i = 0; i > -100; i -= 10) {
		insert_data_into_list (test_list, data);
	}

	data -> address = NULL;
	delete_data (&data);

	display_list (test_list);

	insert_all_into_list (list, test_list);

	display_list (list);

	delete_list (&test_list);


	test_list = create_list (10);
	char c = 'a';

	data = create_empty_data ();
	data -> type = DT_Character;
	data -> size = sizeof (char);
	data -> address = &c;
	
	for ( ; c < 'k'; c++) {
		insert_data_into_list (test_list, data);
	}

	data -> address = NULL;
	delete_data (&data);
	display_list (test_list);

	insert_all_into_list_from_index (list, test_list, 20);
	display_list (list);
	delete_list (&test_list);

	test_list = get_sub_list (list, 10, 20);
	display_list (test_list);
	delete_list (&test_list);

	delete_from_list_at_index (list, 10);
	display_list (list);

	data = remove_from_list_at_index (list, 25);
	display_list (list);
	display_data_properties (data);
	delete_data (&data);

	test_list = get_sub_list (list, 0, 30);
	clear_list (test_list);
	display_list (test_list);
	delete_list (&test_list);

	data = create_data (DT_String, 5, str);
	delete_first_instance_from_list (list, data);
	display_list (list);
	delete_last_instance_from_list (list, data);
	display_list (list);
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
