#include "./inc/basic.h"
#include "./inc/string.h"
#include "./inc/data.h"
#include "./inc/list.h"
#include "./inc/iterator.h"

void collect_garbage_memory (void);
void display_log_entry (Data* entry);

int main (int argc, char* argv[]) {
	if (argc < 2) {
		perror ("No option is given!");
		return EXIT_FAILURE;
	}

	if (compare_raw_strings_shh (4, argv [1], 4, "show")) {
		display_memory_log ();
	}

	if (compare_raw_strings_shh (5, argv [1], 5, "clear")) {
//		display_memory_log ();
		collect_garbage_memory ();
	}

	return EXIT_SUCCESS;
}

void collect_garbage_memory (void) {
	FILE* file = fopen ("./log/memory.log", "rb");

	if (NULL == file) {
		perror ("Error opening memory file!");
		return;
	}

	fseek (file, 0, SEEK_END);
	size_t file_size = ftell (file);
	rewind (file); // or use "fseek (file, 0, SEEK_SET);"
	printf ("Log size: %zu bytes\n", file_size);

	size_t segment_size = sizeof (char)		// newline character
						+ sizeof (void*)	// address pointer
						+ sizeof (size_t)	// data size
						+ sizeof (DS_Type)	// data-structure type
						+ sizeof (bool);	// allocate flag
	size_t entry_count = file_size / segment_size;
	printf ("Number of entries: %zu\n", entry_count);

	char c;
	size_t read_size __attribute__((__unused__));

	size_t entry_length = sizeof (void*) + sizeof (size_t) + sizeof (DS_Type);
	BYTE entry [entry_length] = {};
	bool allocate_flag;
	List* list = create_list (10);

	int DTC [DS_Type_Count] = {};	// DataStructure-Type-Count
	DS_Type ds_type = *((DS_Type*)(entry + sizeof (void*) + sizeof (size_t)));

	Data* data = create_empty_data ();
	data -> type = DT_Binary;
	data -> size = entry_length;
	data -> address = entry;

	size_t index;

	while (entry_count-- && (c = fgetc (file)) != EOF) {
		read_size = fread (entry, entry_length, 1, file);
		read_size = fread (&allocate_flag, sizeof (bool), 1, file);

//		display_raw_bytes (entry_length, entry);
//		printf ("\t%c", (allocate_flag) ? 'I' : 'D');
//		ENDL();
//		display_log_entry (data);
//		ENDL();

		if (allocate_flag) {
			insert_data_into_list (list, data);

			if (ds_type < DS_Type_Count) {
				++ DTC [ds_type];
			}
		} else {
			index = get_last_list_index_of_data (list, data);
//			printf ("Found index: %zd\n", index);

			if ((size_t)(-1) == index) {
//				display_raw_bytes (entry_length, entry);
//				display_log_entry (data);
			} else {
				delete_from_list_at_index (list, index);
//				delete_last_instance_from_list (list, data);

				if (ds_type < DS_Type_Count) {
					-- DTC [ds_type];
				}
			}
		}
/*
		Chunk* chunk = list -> head_chunk;
		printf ("List's count: %zu\n", list -> item_count);
		printf ("Chunk's count: %zu\n", chunk -> data_count);
*/
//		display_list (list);
//		ENDL();
	}

	fclose (file);

	printf ("Leftout address count: %lu\n", list -> item_count);

	for (int i = 0; i < DS_Type_Count; i++) {
		putchar ('(');
		display_data_structure_type (i);
		printf (": %d), ", DTC [i]);
	}

	ENDL();

	data -> type = DT_Undefined;
	data -> size = 0;
	data -> address = NULL;
	delete_data (&data);

	delete_list (&list);
}

void display_log_entry (Data* entry) {
	if (NULL == entry) {
		perror ("Entry data NULL to display");
		return;
	}

	if (
		DT_Binary != entry -> type
		|| (sizeof (void*) + sizeof (DS_Type) + sizeof (size_t)) != entry -> size
	) {
		perror ("Not a log entry!");
		return;
	}

	void* address = NULL;
	copy_raw_bytes (sizeof (void*), (BYTE*)(entry -> address), (BYTE*) &address);
	printf ("%p", address);

	size_t size = *((size_t*)(entry -> address + sizeof (void*)));
	printf ("\t%zu\t", size);	// "%018p"

	DS_Type type = *((DS_Type*)(entry -> address + sizeof (void*) + sizeof (size_t)));
	display_data_structure_type (type);
	ENDL();
}
