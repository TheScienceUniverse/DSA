#include "../inc/test.h"

void test_data (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Data]\n" RESET_STYLE);

	char* str = "Hello, World!\n";
	size_t len = 14;

	Data* data = create_data (DT_String, len, str);
	Data* ghost_data = data;

	TEST (NULL != data, "Checked non-nullified address");
	TEST (DT_String == data -> type, "Matched data-type");

	TEST (ghost_data == data, "Checked non-nullified address");
	delete_data (&data);
	TEST (ghost_data != data, "Checked address nullification");

	String* key = create_string (6, "amount");
	int n = 100;
	Data* value = create_data (DT_Integer, sizeof (int), &n);
	data = create_key_value_data (key, value);
	TEST (NULL != data && DT_Key_Value == data -> type, "Created existence of key-value pair data");
	TEST (Cmp_Equivalent == compare_strings (key, (String*)(data -> address)), "Checked key from key-value pair data");
	TEST (Cmp_Equivalent == compare_data (value, (Data*)((String*)(data -> address) + 1)), "Checked value from key-value pair data");
	delete_key_value_data (&data);
	TEST (NULL == data, "Checked key-value pair deletion");
	delete_data (&value);
	delete_string (&key);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Data]\n" RESET_STYLE);
}
