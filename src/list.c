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
	printf ("calculated chunk capacity %lu and count %lu\n", chunk_capacity, chunk_count);

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
/*
List* duplicate_list (List* old_list) {
	if (old_list == NULL) {
		perror ("List does not exist to Duplicate!");
		return NULL;
	}

	List* new_list = create_list (old_list -> item_count);

	if (new_list != NULL) {
		for (size_t i = 0; i < new_list -> item_count; i++) {
			*(new_list -> item_addresses + i) = *(old_list -> item_addresses + i);
		}
	}

	return new_list;
}

void forget_list (List** list_address) {
	if (*list_address == NULL) {
		perror ("List does not exist to Forget!");
		return;
	}

	List* list = *list_address;

	for (size_t i = 0; i < list -> item_count; i++) {
		*(list -> item_addresses + i) = NULL;
	}
}

void add_to_list (List* list, void* data, bool data_copy_needed) {
	if (list == NULL) {
		perror ("List does not exist to add data!");
		return;
	}

	list -> item_addresses = (void**) realloc (list -> item_addresses, (list -> item_count + 1) * sizeof (void*));

	if (data_copy_needed) {
		*(list -> item_addresses + list -> item_count) = duplicate_data (data);
	} else {
		*(list -> item_addresses + list -> item_count) = data;
	}

	++ list -> item_count;
}
*/
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

void insert_data_into_list (List* list, Data* data) {}

size_t search_data_in_list (List* list, Data* data) {}

void remove_data_from_list (List* list, Data* data) {}

/*
void display_list_addresses (List* list) {
	if (list == NULL) {
		//perror ("List does not exist to display!");
		return;
	}

	if (list -> item_count == 0) {
		//perror ("List is Empty to display!");
		return;
	}

	void* address;

	printf ("List (%lu) : [", list -> item_count);

	for (size_t i = 0; i < list -> item_count; i++) {
		address = *(list -> item_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		printf ("%p", address);
	}

	printf ("]");
}

bool remove_address_from_list (List* list, void* address) {	// this does not hard delete memory data, just forgets or removes the address from list
	size_t index = search_in_address_list (list, address);

	if (index < 1) {
		return false;
	}

	void** ptr = list -> item_addresses + index;

	for (size_t i = index; i < list -> item_count - 1; i++) {
		*ptr = *(ptr + 1);
		++ptr;
	}

	-- (list -> item_count);
	*ptr = NULL;

	return true;
}

size_t search_in_address_list (List* list, void* address) {
	if (list == NULL) {
		perror ("List does not exist to search address in");
		return -1;
	}

	if (list -> item_count == 0) {
		perror ("List is empty to search address in");
		return -1;
	}

	size_t i = 0;
	void** p = list -> item_addresses;

	for (i = 0; i < list -> item_count; i++) {
		if (*p == address) {
			break;
		}

		p = p + 1;
	}

	if (i == list -> item_count) {
		i = -1;
	}

	return i;
}*/