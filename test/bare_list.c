#include "../include/test.h"

void test_bare_list (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Bare List]\n" RESET_STYLE);

	Data* data;
	uint32_t x = 0xa1b2c3d4;
	int n = 100;
	char* str = "Hello, World!";

	Bare_List* list = create_bare_list (10);
	
	data = create_data (DT_Binary, sizeof (uint32_t), &x);
	add_to_bare_list (list, data, true);
	delete_data (&data);

	data = create_data (DT_Integer, sizeof (int), &n);
	add_to_bare_list (list, data, true);
	delete_data (&data);

	data = create_data (DT_String, sizeof (str), str);
	add_to_bare_list (list, data, true);
	delete_data (&data);

	delete_bare_list (&list);



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
