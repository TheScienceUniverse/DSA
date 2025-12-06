#include "../inc/test.h"

void test_Iterator (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Iterator]\n" RESET_STYLE);

	List* list = create_List (10);

	int i;
	Data* data = create_empty_Data ();

	data -> type = DT_Integer;
	data -> size = sizeof (int);
	data -> address = &i;

	for (i = 0; i < 20; i++) {
		insert_Data_into_List (list, data);
	}

	data -> address = NULL;
	empty_Data (data);
	delete_Data (&data);

//	display_List (list);

	Iterator* iterator = create_Iterator (list, +1);
	TEST (NULL != iterator, "Created iterator");

//	display_iterator_details (iterator);


	TEST (0 == iterator -> chunk -> id, "Matched chunk-id from iterator");

	data = list -> head_chunk -> first_data_address;
	TEST (Cmp_Different != compare_Data (data, iterator -> data), "Matched first data from list and iterator");

	move_Iterator (iterator);

	data = list -> head_chunk -> first_data_address + 1; // should not fail as minimum chunk size is 10
	TEST (Cmp_Different != compare_Data (data, iterator -> data), "Matched second data from list and iterator");

	TEST (+1 == iterator -> stride, "Checked default stride value");
	update_Iterator_stride (iterator, +5);
	TEST (+5 == iterator -> stride, "Checked updated stride value");


	data = get_List_Data_at_index (list, 6);
	move_Iterator (iterator);
	TEST (Cmp_Different != compare_Data (data, iterator -> data), "Matched step (1 + 5) data from list and iterator");
	delete_Data (&data);


	data = get_List_Data_at_index (list, 12);	// 1 + 5 + 6 > 10
	update_Iterator_stride (iterator, 6);
	TEST (6 == iterator -> stride, "Matched updated stride (+6) from iterator");
	move_Iterator (iterator);
	TEST (1 == iterator -> chunk -> id, "Matched expected forward chunk id (1) from iterator");
	TEST (Cmp_Different != compare_Data (data, iterator -> data), "Matched further data (6 + 6) from list and iterator");
	delete_Data (&data);

/*
	data = get_List_Data_at_index (list, 7);	// 12 - 5 < 10
	update_Iterator_stride (iterator, -5);
	TEST (-5 == iterator -> stride, "Matched updated stride (-5) from iterator");
	move_Iterator (iterator);
	TEST (0 == iterator -> chunk -> id, "Matched expected backward chunk id (0) from iterator");
	TEST (Cmp_Different != compare_Data (data, iterator -> data), "Matched backward data (12 - 5) from list and iterator");
	delete_Data (&data);
*/

	delete_Iterator (&iterator);
	TEST (NULL == iterator, "Deleted iterator");
	delete_List (&list);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Iterator]\n" RESET_STYLE);
}
