#include "../inc/bare_list.h"

Bare_List* create_Bare_List (size_t item_count) {
	Bare_List* list = (Bare_List*) malloc (sizeof (Bare_List));

	if (list == NULL) {
		return NULL;
	}

	log_memory (DS_Bare_List, sizeof (Bare_List), list, true);

	list -> item_count = 0;
	list -> capacity = 0;
	list -> item_addresses = NULL;

	size_t capacity = calculate_Bare_List_capacity (item_count);
	list -> capacity = capacity;

	list -> item_addresses = (void**) malloc (capacity * sizeof (void*));
	log_memory (DS_Raw, capacity * sizeof (void*), list -> item_addresses, true);

	return list;
}

size_t calculate_Bare_List_capacity (size_t item_count) {
	const size_t MIN_CHUNK_CAP = 10;	// minimum chunk capacity
	const size_t MAX_CHUNK_CAP = 1000;	// maximum chunk capacity

	size_t digit_count = get_number_of_digits (item_count, 10);
	size_t capacity = exponentiate (10, digit_count);

	if (item_count > capacity) {
		capacity *= 10;
	}

	if (((capacity - item_count) / digit_count) < 50) {
		capacity >>= 1;	// capacity /= 2
	}

	if (MIN_CHUNK_CAP > capacity) {
		capacity = MIN_CHUNK_CAP;
	} else if (MAX_CHUNK_CAP < capacity) {
		capacity = MAX_CHUNK_CAP;
	}

	return capacity;
}

Bare_List* duplicate_Bare_List (Bare_List* old_list) {
	if (old_list == NULL) {
		perror ("Bare_List does not exist to Duplicate!");
		return NULL;
	}

	Bare_List* new_list = create_Bare_List (old_list -> item_count);

	if (new_list != NULL) {
		for (size_t i = 0; i < new_list -> item_count; i++) {
			*(new_list -> item_addresses + i) = *(old_list -> item_addresses + i);
		}
	}

	return new_list;
}

void display_Bare_List (Bare_List* list) {
	if (list -> item_count == 0) {
		perror ("Bare_List is Empty!");
		return;
	}

	Data* data;

	printf ("Bare_List (%lu) : [", list -> item_count);

	for (size_t i = 0; i < list -> item_count; i++) {
		data = *(list -> item_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		display_Data (data);
	}

	printf ("]\n");
}

void display_Bare_List_details (Bare_List* list) {
	if (list -> item_count == 0) {
		perror ("Bare_List is Empty!");
		return;
	}

	Data* data;

	printf ("Bare_List :=> Item-Count: %zu, Capacity: %zu, Conetent: [", list -> item_count, list -> capacity);

	for (size_t i = 0; i < list -> item_count; i++) {
		data = *(list -> item_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		display_Data (data);
	}

	printf ("]\n");
}

void display_Bare_List_addresses (Bare_List* list) {
	if (list == NULL) {
		//perror ("Bare_List does not exist to display!");
		return;
	}

	if (list -> item_count == 0) {
		//perror ("Bare_List is Empty to display!");
		return;
	}

	void* address;

	printf ("Bare_List (%lu) : [", list -> item_count);

	for (size_t i = 0; i < list -> item_count; i++) {
		address = *(list -> item_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		printf ("%p", address);
	}

	printf ("]");
}

void forget_Bare_List (Bare_List** list_address) {
	if (*list_address == NULL) {
		perror ("Bare_List does not exist to Forget!");
		return;
	}

	Bare_List* list = *list_address;

	for (size_t i = 0; i < list -> item_count; i++) {
		*(list -> item_addresses + i) = NULL;
	}
}

void delete_Bare_List (Bare_List** list_address) {
	if (*list_address == NULL) {
		perror ("Bare_List does not exist to Delete!");
		return;
	}

	Bare_List* list = *list_address;
	__attribute__((unused)) Data* data;

	for (size_t i = 0; i < list -> item_count; i++) {
		data = *(list -> item_addresses + i);
		delete_Data (&data);
	}

	log_memory (DS_Raw, (list -> capacity) * sizeof (void*), list -> item_addresses, false);
	ERASE (&(list -> item_addresses), (list -> capacity) * sizeof (void*));

	list = NULL;

	log_memory (DS_Bare_List, sizeof (Bare_List), *list_address, false);
	ERASE (list_address, sizeof (Bare_List));
}

void add_to_Bare_List (Bare_List* list, Data* data, bool data_copy_needed) {
	if (list == NULL) {
		perror ("Bare_List does not exist to add data!");
		return;
	}

	list -> item_addresses = (void**) realloc (list -> item_addresses, (list -> item_count + 1) * sizeof (void*));

	if (data_copy_needed) {
		*(list -> item_addresses + list -> item_count) = duplicate_Data (data);
	} else {
		*(list -> item_addresses + list -> item_count) = data;
	}

	++ list -> item_count;
}

bool remove_address_from_Bare_List (Bare_List* list, void* address) {	// this does not hard delete memory data, just forgets or removes the address from list
	int index = search_in_address_Bare_List (list, address);

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

size_t search_in_address_Bare_List (Bare_List* list, void* address) {
	if (list == NULL) {
		perror ("Bare_List does not exist to search address in");
		return -1;
	}

	if (list -> item_count == 0) {
		perror ("Bare_List is empty to search address in");
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
}