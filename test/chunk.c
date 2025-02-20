#include "../include/test.h"

void test_chunk (void) {
	printf (BOLD_YELLOW "Unit test starts..." BOLD_MAGENTA " [Chunk]\n" RESET_STYLE);

	Chunk* chunk = create_chunk (0, 10);
	display_chunk_properties (chunk);

	uint16_t x = 0x0ff0;
	int n = 10;
	char* str = "Hello, World!";
	Data* data;

	for (int i = 0; i < 3; i++) {
		data = create_data (DT_Binary, sizeof (uint16_t), &x);
		insert_data_into_chunk (chunk, data);
		delete_data (&data);

		data = create_data (DT_Integer, sizeof (int), &n);
		insert_data_into_chunk (chunk, data);
		delete_data (&data);

		data = create_data (DT_String, sizeof (str), str);
		insert_data_into_chunk (chunk, data);
		delete_data (&data);

		display_chunk (chunk);
	}

	data = create_data (DT_Binary, sizeof (uint16_t), &x);
	insert_data_into_chunk (chunk, data);
	delete_data (&data);

	data = create_data (DT_Integer, sizeof (int), &n);
	insert_data_into_chunk (chunk, data);
	delete_data (&data);

	display_chunk (chunk);

/*void delete_chunk (Chunk** chunk_address);
void display_chunk_properties (Chunk* chunk);
void display_chunk (Chunk* chunk);
Chunk* duplicate_chunk (Chunk* chunk);
void forget_chunk (Chunk** chunk_address);
Chunk* extend_chunk (Chunk* chunk);
void insert_data_into_chunk (Chunk* chunk, Data* data);
Data* delete_data_from_chunk (Chunk* chunk);
*/

//	printf("%lu\n", sysconf(_SC_PAGESIZE) / sizeof(void*));

	delete_chunk (&chunk);

	printf (BOLD_YELLOW "...Unit test ends!" BOLD_MAGENTA " [Chunk]\n" RESET_STYLE);
}
