#include "../inc/test.h"

void test_list (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [List]\n" RESET_STYLE);

	List* list = create_list (100);
//	display_chunk_properties (chunk);

	uint16_t x = 0x37bf; // 0x0ff0;	// 3, 7, 11 (b), 16 (f)
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

	// display_list (list);
	// printf ("list item count: %lu\n", list -> item_count);

	TEST (30 == list -> item_count, "List filled with data");

	data = create_data (DT_String, 5, str);
	List* index_list = search_data_in_list (list, data);
	// display_list (index_list);
	TEST (NULL != index_list, "Received search index-list result");
	TEST (10 == index_list -> item_count, "Matched count of searched data");
	delete_list (&index_list);
	delete_data (&data);


	data = get_list_data_at_index (list, 10);
	TEST (NULL != data, "Fetched data with given index exists");
	TEST (40 == *((int*)(data -> address)), "Fetched data matched with value");
	// display_data (data);
	delete_data (&data);


	data = create_data (DT_String, 5, str);
	TEST (2 == get_first_list_index_of_data (list, data), "Matched first index of given data");
	TEST (30 == get_last_list_index_of_data (list, data), "Matched last index of given data");
	delete_data (&data);


	char* test_str = "XOXOX";
	data = create_data (DT_String, 5, test_str);
	insert_into_list_at_index (list, data, 10);
	Data* test_data = get_list_data_at_index (list, 10);
	TEST (Cmp_Equivalent == compare_data (data, test_data), "Matched inserted data with expected data at position");
	// display_list (list);
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

	TEST (NULL != test_list, "Created test list");
	TEST (10 == test_list -> item_count, "Created test list with expected number of data");
	// display_list (test_list);


	insert_all_into_list (list, test_list);
	TEST (40 == list -> item_count + test_list -> item_count, "Test list appended into the original list");
	data = get_list_data_at_index (list, 31);
	TEST (0 == *((int*)(data -> address)), "Checked inserted first data from list");
	delete_data (&data);
	data = get_list_data_at_index (list, 40);
	TEST (-90 == *((int*)(data -> address)), "Checked inserted last data from list");
	delete_data (&data);
	// display_list (list);

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
	// display_list (test_list);
	TEST (NULL != test_list, "Created test list");
	TEST (10 == test_list -> item_count, "Created test list with expected number of data");


	insert_all_into_list_from_index (list, test_list, 20);
	// display_list (list);
	data = get_list_data_at_index (list, 20);
	TEST ('a' == *((char*)(data -> address)), "Checked inserted list's first data from original list");
	delete_data (&data);
	data = get_list_data_at_index (list, 29);
	TEST ('j' == *((char*)(data -> address)), "Checked inserted list's last data from original list");
	delete_data (&data);

	delete_list (&test_list);


	test_list = get_sub_list (list, 10, 20);
	TEST (NULL != test_list, "Created test list");
	TEST (11 == test_list -> item_count, "Created test list with expected number of data");
	data = get_list_data_at_index (list, 10);
	test_data = get_list_data_at_index (test_list, 0);
	TEST (Cmp_Equivalent == compare_data (data, test_data), "Matched first data of sub-list to copy index from equivalent original list");
	delete_data (&test_data);
	delete_data (&data);
	data = get_list_data_at_index (list, 19);
	test_data = get_list_data_at_index (test_list, 10);
	TEST (Cmp_Equivalent == compare_data (data, test_data), "Matched last data of sub-list to copy index from equivalent original list");
	delete_data (&test_data);
	delete_data (&data);
	//display_list (test_list);
	delete_list (&test_list);


	delete_from_list_at_index (list, 10);
	data = get_list_data_at_index (list, 10);
	TEST ('g' != *((char*)(data -> address)), "Deleted data in the original list");
	delete_data (&data);
	// display_list (list);


	test_data = get_list_data_at_index (list, 25);
	data = remove_from_list_at_index (list, 25);
	TEST (Cmp_Equivalent == compare_data (data, test_data), "Matched removed data from original list");
	// display_list (list);
	// display_data_details (data);
	delete_data (&data);
	delete_data (&test_data);


	test_list = get_sub_list (list, 0, 30);
	TEST (0 != test_list -> item_count, "Checked item-count in sample list before clearing list");
	clear_list (test_list);
	TEST (0 == test_list -> item_count, "Checked item-count in sample list after clearing list");
	// display_list (test_list);
	delete_list (&test_list);


	data = create_data (DT_String, 5, str);
	delete_first_instance_from_list (list, data);
	// display_list (list);
	delete_last_instance_from_list (list, data);
	// display_list (list);
	delete_data (&data);


	data = create_data (DT_String, 5, str);
	delete_all_instances_from_list (list, data);
	// display_list (list);
	delete_data (&data);


	TEST (true == is_list_empty (list), "List non-emptiness check");
	delete_list (&list);


	list = create_list (0);
	TEST (true == is_list_empty (list), "List emptiness check");
	delete_list (&list);


	list = create_list (30);
	test_list = create_list (10);

	for (i = 0; i < 10; i++) {
		x ^= 0xffff;
		data = create_data (DT_Binary, sizeof (uint16_t), &x);
		insert_data_into_list (list, data);
		insert_data_into_list (test_list, data);
		delete_data (&data);

		n += 10;
		data = create_data (DT_Integer, sizeof (int), &n);
		insert_data_into_list (list, data);
		insert_data_into_list (test_list, data);
		delete_data (&data);

		data = create_data (DT_String, 5, str);
		insert_data_into_list (list, data);
		insert_data_into_list (test_list, data);
		delete_data (&data);
	}

	TEST (compare_lists (list, test_list), "Checked lists are equivalent or not");
	delete_list (&test_list);


	n += 10;
	data = create_data (DT_Integer, sizeof (int), &n);
	TEST (does_list_contain_data (list, data), "Found expected data");
	*((int*)(data -> address)) = 1000;
	TEST (does_list_contain_data (list, data), "Not found unexpected data");

	delete_data (&data);
	delete_list (&list);


	list = create_list (2);
	// display_list (list);
	n = -100;
	data = create_data (DT_Integer, sizeof (int), &n);
	TEST (2 == list -> head_chunk -> capacity, "Checked small list chunk size");
	insert_data_into_list (list, data);
	*((int*)(data -> address)) = +100;
	insert_data_into_list (list, data);
	TEST (2 == list -> item_count, "Matched small list item count");
	// display_list (list);

	*((int*)(data -> address)) = -200;
	insert_data_into_list (list, data);
	*((int*)(data -> address)) = +200;
	insert_data_into_list (list, data);
	// display_list (list);
	test_list = duplicate_list (list);
	// display_list (test_list);
	TEST (Cmp_Equivalent == compare_lists (list, test_list), "Matched duplicate list with original list");
	delete_list (&test_list);

	delete_data (&data);
	delete_list (&list);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [List]\n" RESET_STYLE);
}
