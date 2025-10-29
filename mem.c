#include "./inc/basic.h"
#include "./inc/stream.h"
#include "./inc/string.h"
#include "./inc/data.h"
#include "./inc/chunk.h"
#include "./inc/bare_list.h"
#include "./inc/list.h"
#include "./inc/iterator.h"
#include "./inc/node.h"
#include "./inc/linked_list.h"
#include "./inc/stack.h"
#include "./inc/queue.h"
#include "./inc/tree.h"
#include "./inc/graph.h"

void collect_garbage_memory (void);
void display_log_entry (void* address, size_t size, DS_Type ds_type);
void delete_data_structure (DS_Type ds_type, BYTE* address, size_t size);

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
//	printf ("Log size: %zu bytes\n", file_size);

	size_t segment_size = sizeof (char)		// newline character
						+ sizeof (void*)	// address pointer
						+ sizeof (size_t)	// data size
						+ sizeof (DS_Type)	// data-structure type
						+ sizeof (bool);	// allocate flag
	size_t entry_count = file_size / segment_size;
//	printf ("Number of entries: %zu\n", entry_count);

	char c;
	size_t read_size __attribute__((__unused__));

	size_t entry_length = sizeof (void*) + sizeof (size_t) + sizeof (DS_Type);
	BYTE entry [entry_length] = {};
	bool allocate_flag;
	List* list = create_list (10);

	int DTC [DS_Type_Count] = {};	// DataStructure Type Counts array-map
	__attribute__((unused)) void** ds_address_ptr = (void**) entry;
//	copy_raw_bytes (sizeof (void*), (BYTE*)(entry), (BYTE*) ds_address_ptr);
//	size_t* ds_size_ptr = (size_t*)(entry + sizeof (void*));
	DS_Type* ds_type_ptr = (DS_Type*)(entry + sizeof (void*) + sizeof (size_t));

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
//		display_log_entry (*ds_address_ptr, *ds_size_ptr, *ds_type_ptr);
//		ENDL();

		if (allocate_flag) {
			insert_data_into_list (list, data);

			if (*ds_type_ptr < DS_Type_Count) {
				++ DTC [*ds_type_ptr];
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

				if (*ds_type_ptr < DS_Type_Count) {
					-- DTC [*ds_type_ptr];
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

//	display_list_subset (list, 0, 19);

	void* ds_entry;
	__attribute__((unused)) size_t ds_size;
	__attribute__((unused)) DS_Type ds_type;

	Iterator* iterator = create_iterator (list, 1);

	for (size_t i = 0; i < list -> item_count; i++) {
//		printf ("%zu: ", i);
//		display_data (iterator -> data);
//		ENDL();

		ds_entry = iterator -> data -> address;
		// copy_raw_bytes (sizeof (void*), (BYTE*) ds_entry, (BYTE*) ds_address_ptr);
		ds_address_ptr = ds_entry;
		ds_size = *((size_t*)(ds_entry + sizeof (void*)));
		ds_type = *((DS_Type*)(ds_entry + sizeof (void*) + sizeof (size_t)));

//		display_raw_bytes (entry_length, ds_entry);
//		ENDL();
//		display_log_entry (*ds_address_ptr, ds_size, ds_type);

//		** UNABLE to delete after program ends
//		delete_data_structure (ds_type, address, size);

		move_iterator (iterator);
	}

	delete_iterator (&iterator);
	delete_list (&list);
//	ENDL();
}

void display_log_entry (void* address, size_t size, DS_Type ds_type) {
	if (NULL == address) {
		perror ("Entry data NULL to display!");
		return;
	}

	printf ("%p", address);	// %018p
	printf ("\t%zu\t", size);
	display_data_structure_type (ds_type);
	ENDL();
/*
	printf ("Data :=> ");

	switch (ds_type) {
		case DS_Raw:
			display_raw_bytes (size, address);
			break;
		case DS_Stream:
			display_raw_bytes (size, address);
//			display_stream ((Stream*) address);
			break;
		case DS_String:
			display_raw_bytes (size, address);
//			display_string ((String*) address);
			break;
		case DS_Data:
			display_raw_bytes (size, address);
//			display_data ((Data*) address);
			break;
		case DS_Bare_List:
			delete_bare_list ((Bare_List**) &address);
			break;
		case DS_Chunk:
			delete_chunk ((Chunk**) &address);
			break;
		case DS_List:
			delete_list ((List**) &address);
			break;
		case DS_Iterator:
			delete_iterator ((Iterator**) &address);
			break;
		case DS_Node:
			delete_node ((Node**) &address);
			break;
		case DS_Linked_List:
			delete_linked_list ((Linked_List**) &address);
			break;
		case DS_Stack:
			delete_stack ((Stack**) &address);
			break;
		case DS_Queue:
			delete_queue ((Queue**) &address);
			break;
		case DS_Tree:
			delete_tree ((Tree**) &address);
			break;
		case DS_Graph:
//			delete_graph ((Graph**) &address);
			break;
		default:
			break;
	}
*/
//	ENDL();
}

void delete_log_entry (void* address, size_t size, DS_Type ds_type) {
	if (NULL == address) {
		perror ("Entry data NULL to display!");
		return;
	}

	if (
		DS_Raw != ds_type
		|| (sizeof (void*) + sizeof (DS_Type) + sizeof (size_t)) != size
	) {
		perror ("Not a log entry!");
		return;
	}

	printf ("%p", address);
	printf ("\t%zu\t", size);	// "%018p"
//	display_data_structure_type (type);
	ENDL();

	switch (ds_type) {
		case DS_Raw:
			ERASE (&address, sizeof (void*));
			log_memory (DS_Raw, size, address, false);
			break;
		case DS_Stream:
			delete_stream ((Stream**) &address);
			break;
		case DS_String:
			delete_string ((String**) &address);
			break;
		case DS_Data:
			delete_data ((Data**) &address);
			break;
		case DS_Bare_List:
			delete_bare_list ((Bare_List**) &address);
			break;
		case DS_Chunk:
			delete_chunk ((Chunk**) &address);
			break;
		case DS_List:
			delete_list ((List**) &address);
			break;
		case DS_Iterator:
			delete_iterator ((Iterator**) &address);
			break;
		case DS_Node:
			delete_node ((Node**) &address);
			break;
		case DS_Linked_List:
			delete_linked_list ((Linked_List**) &address);
			break;
		case DS_Stack:
			delete_stack ((Stack**) &address);
			break;
		case DS_Queue:
			delete_queue ((Queue**) &address);
			break;
		case DS_Tree:
			delete_tree ((Tree**) &address);
			break;
		case DS_Graph:
//			delete_graph ((Graph**) &address);
			break;
		default:
			break;
	}
}
