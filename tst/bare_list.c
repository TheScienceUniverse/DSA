#include "../inc/test.h"

void test_Bare_List (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Bare List]\n" RESET_STYLE);

	Data* data;
	uint32_t x = 0xa1b2c3d4;
	int n = 100;
	char* str = "Hello, World!";

	Bare_List* list = create_Bare_List (0);
	TEST (NULL != list, "Created bare list");

	data = create_Data (DT_Binary, sizeof (uint32_t), &x);
	add_to_Bare_List (list, data, true);
	TEST (1 == list -> item_count, "Expected item count (1) in bare list");
	TEST (Cmp_Equivalent == compare_Data (data, *(list -> item_addresses + 0)), "Compared inserted data with expected data");
	delete_Data (&data);

	data = create_Data (DT_Integer, sizeof (int), &n);
	add_to_Bare_List (list, data, true);
	TEST (2 == list -> item_count, "Expected item count (2) in bare list");
	TEST (Cmp_Equivalent == compare_Data (data, *(list -> item_addresses + 1)), "Compared inserted data with expected data");
		delete_Data (&data);

	data = create_Data (DT_String, 5, str);
	add_to_Bare_List (list, data, true);
	TEST (3 == list -> item_count, "Expected item count (3) in bare list");
	TEST (Cmp_Equivalent == compare_Data (data, *(list -> item_addresses + 2)), "Compared inserted data with expected data");
	delete_Data (&data);

	delete_Bare_List (&list);
	TEST (NULL == list, "Deleted bare list");


/*
List2* duplicate_list2 (List2* list);
void forget_list2 (List2** list_address);
void add_data_to_list2 (List2* list, void* data, bool data_copy_needed);
void display_list2_properties (List2* list);
void display_list2 (List2* list);
void display_list2_addresses (List2* list);
size_t search_in_address_list2 (List2* list, void* address);
bool remove_address_from_list2 (List2* list, void* address);
*/

	/*...*/
//	printf("%lu\n", sysconf(_SC_PAGESIZE) / sizeof(void*));

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Bare List]\n" RESET_STYLE);
}
