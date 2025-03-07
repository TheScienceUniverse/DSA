#include "../include/list.h"

List* create_list (size_t item_count) {
	List* list = (List*) malloc (sizeof (List));

	auto size_t chunk_capacity = 0;
	auto size_t chunk_count = 0;

	if (list == NULL) {
		return NULL;
	}

	list -> item_count = 0;
	list -> chunk_count = 0;
	list -> head_chunk = NULL;
	list -> tail_chunk = NULL;

	if (item_count == 0) {
		return list;
	}

	set_list_chunk_cap_count (item_count, &chunk_capacity, &chunk_count);
	// printf ("calculated chunk capacity %lu and count %lu\n", chunk_capacity, chunk_count);

	list -> head_chunk = create_chunk (0, chunk_capacity);	// default chunk
	list -> tail_chunk = list -> head_chunk;

	return list;
}

void delete_list (List** list_address) {
	if (*list_address == NULL) {
		perror ("List does not exist to Delete!");
		return;
	}

	List* list = *list_address;
	Chunk* chunk = list -> tail_chunk;

	for (size_t i = 0; i < list -> chunk_count; i++) {
		chunk = reduce_chunk (chunk);
	}

	delete_chunk (&chunk);

	list = NULL;
	ERASE (list_address, sizeof (List));
}

void display_list (List* list) {
	if (list -> item_count == 0) {
		perror ("List is Empty!");
		return;
	}

	Chunk* chunk = list -> head_chunk;

	display_linked_chunks (chunk);
}

void set_list_chunk_cap_count (size_t item_count, size_t* chunk_capacity, size_t* chunk_count) {
	const size_t MIN_CHUNK_CAP = 10;	// minimum chunk capacity
	const size_t MAX_CHUNK_CAP = 1000;	// maximum chunk capacity

	size_t digit_count = get_number_of_digits (item_count, 10);
	size_t capacity = exponentiate (10, digit_count);

	if (item_count > capacity) {
		capacity *= 10;
	}

	if ((capacity - item_count) / digit_count < 50) {
		capacity /= 2;
	}

	if (MIN_CHUNK_CAP > capacity) {
		capacity = MIN_CHUNK_CAP;
	} else if (MAX_CHUNK_CAP < capacity) {
		capacity = MAX_CHUNK_CAP;
	}

	*chunk_capacity = capacity;
	*chunk_count = item_count / capacity;

	if (0 == *chunk_count) {
		*chunk_count = 1;
	}
}

void insert_data_into_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to insert data into!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to insert into list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	insert_data_into_chunk (chunk, data);
	list -> tail_chunk = get_last_chunk (chunk);
	list -> item_count++;
}

List* search_data_in_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to search data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search from list!\n");
		exit (EXIT_FAILURE);
	}

	List* index_list = create_list (list -> item_count / 2);
	Chunk* chunk = list -> head_chunk;
	size_t index = 0;

	for (size_t i = 0; i < list -> item_count; i++) {
		// printf ("list [%lu]: ", i);
		// display_data (chunk -> first_data_address + index++);
		// printf ("\n");

		if (chunk -> data_count == index) {
			index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	return index_list;
}

void delete_data_from_list (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to delete from list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	Data* deleted_data = remove_data_from_chunk (chunk);
	list -> tail_chunk = get_last_chunk (chunk);
}