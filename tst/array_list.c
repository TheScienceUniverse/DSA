#include "../inc/test.h"

void test_ArrayList (void) {
	display_unit_test_message ("Array List", true);

	Data* data;
	uint32_t x = 0xa1b2c3d4;
	int n = 100;
	char* str = "Hello, World!";

	ArrayList* array_list = create_ArrayList (0);
	TEST (NULL != array_list, "Created array list");

	display_ArrayList (array_list);

	for (int i = 0; i < 3; i++) {
		data = create_Data (DT_Binary, sizeof (uint32_t), &x);
		add_to_ArrayList (array_list, data);
		TEST ((size_t)(3 * i + 1) == array_list -> item_count, "Expected item count (3i+1) in array_list");
		TEST (Cmp_Equivalent == compare_Data (data, (Data*)(array_list -> container) + 0), "Compared inserted data with expected data");
		delete_Data (&data);

		data = create_Data (DT_Integer, sizeof (int), &n);
		add_to_ArrayList (array_list, data);
		TEST ((size_t)(3 * i + 2) == array_list -> item_count, "Expected item count (3i+2) in bare array_list");
		TEST (Cmp_Equivalent == compare_Data (data, (Data*)(array_list -> container) + 1), "Compared inserted data with expected data");
		delete_Data (&data);

		data = create_Data (DT_String, 5, str);
		add_to_ArrayList (array_list, data);
		TEST ((size_t)(3 * i + 3) == array_list -> item_count, "Expected item count (3i+3) in bare array_list");
		TEST (Cmp_Equivalent == compare_Data (data, (Data*)(array_list -> container) + 2), "Compared inserted data with expected data");
		delete_Data (&data);
	}

	n = 500;
	data = create_Data (DT_Integer, sizeof (int), &n);
	add_to_ArrayList (array_list, data);
	TEST (10 == array_list -> item_count, "Expected item count (10) in bare array_list");
	TEST (Cmp_Equivalent == compare_Data (data, (Data*)(array_list -> container) + 9), "Compared inserted data with expected data");

	*(int*)(data -> address) = 1000;
	add_to_ArrayList (array_list, data);
	TEST (11 == array_list -> item_count, "Expected item count (11) in bare array_list");
	TEST (Cmp_Equivalent == compare_Data (data, (Data*)(array_list -> container) + 10), "Compared inserted data with expected data");
	delete_Data (&data);

	data = get_ArrayList_Data_at_index (array_list, 5);
	TEST (Cmp_Equivalent == compare_Data (data, (Data*)(array_list -> container) + 5), "Compared search by index data with expected data");
	delete_Data (&data);

//	display_ArrayList (array_list);

	delete_ArrayList (&array_list);
	TEST (NULL == array_list, "Deleted array list");

	display_unit_test_message ("Array List", false);
}
