#include "../inc/test.h"

void test_List (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [List]\n" RESET_STYLE);

	List* list = create_List (100);
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
		data = create_Data (DT_Binary, sizeof (uint16_t), &x);
		insert_Data_into_List (list, data);
		delete_Data (&data);

		n += 10;
		data = create_Data (DT_Integer, sizeof (int), &n);
		insert_Data_into_List (list, data);
		delete_Data (&data);

		data = create_Data (DT_String, 5, str);
		insert_Data_into_List (list, data);
		delete_Data (&data);
	}

	// display_list (list);
	// printf ("list item count: %lu\n", list -> item_count);

	TEST (30 == list -> item_count, "List filled with data");

	data = create_Data (DT_String, 5, str);
	List* index_list = search_Data_in_List (list, data);
	// display_list (index_list);
	TEST (NULL != index_list, "Received search index-list result");
	TEST (10 == index_list -> item_count, "Matched count of searched data");
	delete_List (&index_list);
	delete_Data (&data);


	data = get_List_Data_at_index (list, 10);
	TEST (NULL != data, "Fetched data with given index exists");
	TEST (40 == *((int*)(data -> address)), "Fetched data matched with value");
	// display_data (data);
	delete_Data (&data);


	data = create_Data (DT_String, 5, str);
	TEST (2 == get_first_List_index_of_Data (list, data), "Matched first index of given data");
	TEST (30 == get_last_List_index_of_Data (list, data), "Matched last index of given data");
	delete_Data (&data);


	char* test_str = "XOXOX";
	data = create_Data (DT_String, 5, test_str);
	insert_into_List_at_index (list, data, 10);
	Data* test_data = get_List_Data_at_index (list, 10);
	TEST (Cmp_Equivalent == compare_Data (data, test_data), "Matched inserted data with expected data at position");
	// display_list (list);
	delete_Data (&test_data);
	delete_Data (&data);


	List* test_list = create_List (10);

	data = create_empty_Data ();
	data -> type = DT_Integer;
	data -> size = sizeof (int);
	data -> address = &i;
	
	for (i = 0; i > -100; i -= 10) {
		insert_Data_into_List (test_list, data);
	}

	data -> address = NULL;
	delete_Data (&data);

	TEST (NULL != test_list, "Created test list");
	TEST (10 == test_list -> item_count, "Created test list with expected number of data");
	// display_list (test_list);


	insert_all_into_List (list, test_list);
	TEST (40 == list -> item_count + test_list -> item_count, "Test list appended into the original list");
	data = get_List_Data_at_index (list, 31);
	TEST (0 == *((int*)(data -> address)), "Checked inserted first data from list");
	delete_Data (&data);
	data = get_List_Data_at_index (list, 40);
	TEST (-90 == *((int*)(data -> address)), "Checked inserted last data from list");
	delete_Data (&data);
	// display_List (list);

	delete_List (&test_list);


	test_list = create_List (10);
	char c = 'a';

	data = create_empty_Data ();
	data -> type = DT_Character;
	data -> size = sizeof (char);
	data -> address = &c;
	
	for ( ; c < 'k'; c++) {
		insert_Data_into_List (test_list, data);
	}

	data -> address = NULL;
	delete_Data (&data);
	// display_List (test_list);
	TEST (NULL != test_list, "Created test list");
	TEST (10 == test_list -> item_count, "Created test list with expected number of data");
//	display_List_details (test_list);

//	display_List_details (list);
	insert_all_into_List_from_index (list, test_list, 20);
//	display_List_details (list);
	data = get_List_Data_at_index (list, 20);
	TEST ('a' == *((char*)(data -> address)), "Checked inserted list's first data from original list");
	delete_Data (&data);
	data = get_List_Data_at_index (list, 29);
	TEST ('j' == *((char*)(data -> address)), "Checked inserted list's last data from original list");
	delete_Data (&data);

	delete_List (&test_list);


	test_list = get_sub_List (list, 10, 20);
	TEST (NULL != test_list, "Created test list");
	TEST (11 == test_list -> item_count, "Created test list with expected number of data");
	data = get_List_Data_at_index (list, 10);
	test_data = get_List_Data_at_index (test_list, 0);
	TEST (Cmp_Equivalent == compare_Data (data, test_data), "Matched first data of sub-list to copy index from equivalent original list");
	delete_Data (&test_data);
	delete_Data (&data);
	data = get_List_Data_at_index (list, 19);
	test_data = get_List_Data_at_index (test_list, 10);
	TEST (Cmp_Equivalent == compare_Data (data, test_data), "Matched last data of sub-list to copy index from equivalent original list");
	delete_Data (&test_data);
	delete_Data (&data);
	//display_List (test_list);
	delete_List (&test_list);


	delete_from_List_at_index (list, 10);
	data = get_List_Data_at_index (list, 10);
	TEST ('g' != *((char*)(data -> address)), "Deleted data in the original list");
	delete_Data (&data);
	// display_list (list);


	test_data = get_List_Data_at_index (list, 25);
	data = remove_from_List_at_index (list, 25);
	TEST (Cmp_Equivalent == compare_Data (data, test_data), "Matched removed data from original list");
	// display_List (list);
	// display_Data_details (data);
	delete_Data (&data);
	delete_Data (&test_data);


	test_list = get_sub_List (list, 0, 30);
	TEST (0 != test_list -> item_count, "Checked item-count in sample list before clearing list");
	clear_List (test_list);
	TEST (0 == test_list -> item_count, "Checked item-count in sample list after clearing list");
	// display_List (test_list);
	delete_List (&test_list);


	data = create_Data (DT_String, 5, str);
	delete_first_instance_from_List (list, data);
	// display_list (list);
	delete_last_instance_from_List (list, data);
	// display_List (list);
	delete_Data (&data);


	data = create_Data (DT_String, 5, str);
	delete_all_instances_from_List (list, data);
	// display_List (list);
	delete_Data (&data);


	TEST (true == is_List_empty (list), "List non-emptiness check");
	delete_List (&list);


	list = create_List (0);
	TEST (true == is_List_empty (list), "List emptiness check");
	delete_List (&list);


	list = create_List (30);
	test_list = create_List (10);

	for (i = 0; i < 10; i++) {
		x ^= 0xffff;
		data = create_Data (DT_Binary, sizeof (uint16_t), &x);
		insert_Data_into_List (list, data);
		insert_Data_into_List (test_list, data);
		delete_Data (&data);

		n += 10;
		data = create_Data (DT_Integer, sizeof (int), &n);
		insert_Data_into_List (list, data);
		insert_Data_into_List (test_list, data);
		delete_Data (&data);

		data = create_Data (DT_String, 5, str);
		insert_Data_into_List (list, data);
		insert_Data_into_List (test_list, data);
		delete_Data (&data);
	}

	TEST (compare_Lists (list, test_list), "Checked lists are equivalent or not");
	delete_List (&test_list);


	n += 10;
	data = create_Data (DT_Integer, sizeof (int), &n);
	TEST (does_List_contain_Data (list, data), "Found expected data");
	*((int*)(data -> address)) = 1000;
	TEST (does_List_contain_Data (list, data), "Not found unexpected data");

	delete_Data (&data);
	delete_List (&list);


	list = create_List (2);
	// display_list (list);
	n = -100;
	data = create_Data (DT_Integer, sizeof (int), &n);
	TEST (2 == list -> head_chunk -> capacity, "Checked small list chunk size");
	insert_Data_into_List (list, data);
	*((int*)(data -> address)) = +100;
	insert_Data_into_List (list, data);
	TEST (2 == list -> item_count, "Matched small list item count");
	// display_list (list);

	*((int*)(data -> address)) = -200;
	insert_Data_into_List (list, data);
	*((int*)(data -> address)) = +200;
	insert_Data_into_List (list, data);
	// display_List (list);
	test_list = duplicate_List (list);
	// display_List (test_list);
	TEST (Cmp_Equivalent == compare_Lists (list, test_list), "Matched duplicate list with original list");
	delete_List (&test_list);

	delete_Data (&data);
	delete_List (&list);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [List]\n" RESET_STYLE);
}
