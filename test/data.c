#include "../include/test.h"

/*
Data* create_data (Data_Type data_type, int block_size, void* address);
Data* duplicate_data (Data* data);
void delete_data (Data** data_address);
*/


void test_data (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Data]\n" RESET_STYLE);

	char* str = "Hello, World!\n";
	size_t len = 14;

	Data* data = create_data (DT_String, len, str);
	Data* ghost_data = data;

	TEST (NULL != data, "Address non-null check");
	TEST (DT_String == data -> type, "Datatype match check");

	TEST (ghost_data == data, "Address non-nullified check");
	delete_data (&data);
	TEST (ghost_data != data, "Address nullification check");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Data]\n" RESET_STYLE);
}
