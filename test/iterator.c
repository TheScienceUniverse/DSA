#include "../include/test.h"

void test_iterator (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Iterator]\n" RESET_STYLE);

	List* list = create_list (10);

	int i;
	Data* data = create_empty_data ();

	data -> type = DT_Integer;
	data -> size = sizeof (int);
	data -> address = &i;

	for (i = 0; i < 20; i++) {
		insert_data_into_list (list, data);
	}

	data -> address = NULL;
	empty_data (data);
	delete_data (&data);

	display_list (list);

	Iterator* iterator = create_iterator (list, +1);
	TEST (NULL != iterator, "Created iterator");

	display_iterator_details (iterator);


	TEST (0 == iterator -> chunk -> id, "Matched chunk-id from iterator");

	data = list -> head_chunk -> first_data_address;
	TEST (Cmp_Different != compare_data (data, iterator -> data), "Matched first data from list and iterator");

	move_iterator (iterator);

	data = list -> head_chunk -> first_data_address + 1; // should not fail as minimum chunk size is 10
	TEST (Cmp_Different != compare_data (data, iterator -> data), "Matched second data from list and iterator");

	TEST (+1 == iterator -> stride, "Checked default stride value");
	update_iterator_stride (iterator, +5);
	TEST (+5 == iterator -> stride, "Checked updated stride value");

	data = get_list_data_at_index (list, 6);
	move_iterator (iterator);
	TEST (Cmp_Different != compare_data (data, iterator -> data), "Matched sixth (1 + 5) data from list and iterator");
	delete_data (&data);

	data = get_list_data_at_index (list, 11);
	display_data (data);
/*	move_iterator (iterator);
	TEST (Cmp_Different != compare_data (data, iterator -> data), "Matched 5th data from list and iterator");
	delete_data (&data);
*/


	delete_iterator (&iterator);
	TEST (NULL == iterator, "Deleted iterator");
	delete_list (&list);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Iterator]\n" RESET_STYLE);
}
