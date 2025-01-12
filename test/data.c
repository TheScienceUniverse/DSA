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
//	void* ptr = data;

	TEST (data != NULL, "Address non-null check");
	TEST (DT_String == data -> type, "Datatype match check");

	delete_data (&data);

	TEST (NULL == data, "Address nullified check");
//	TEST (sizeof (int*) == sizeof (string), "De-allocated block-size check");
//	TEST (NULL == ptr, "Address nullify check");
//	TEST (ptr != vptr, "Address validation check");
//	TEST (n != *((int*) vptr), "Content check");

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Data]\n" RESET_STYLE);
}
