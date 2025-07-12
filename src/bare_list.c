#include "../inc/bare_list.h"

Bare_List* create_bare_list (size_t item_count) {
	Bare_List* list = (Bare_List*) malloc (sizeof (Bare_List));

	if (list == NULL) {
		return NULL;
	}

	log_memory (DS_Bare_List, sizeof (Bare_List), list, true);

	list -> item_count = 0;
	list -> item_addresses = NULL;

	if (item_count < 10) {
		while (item_count--) {
			add_to_bare_list (list, NULL, false);
		}
	} else {
		list -> item_count = item_count;
		list -> item_addresses = (void**) malloc (list -> item_count * sizeof (void*));

		log_memory (DS_Raw, item_count * sizeof (void*), list -> item_addresses, true);
	}

	return list;
}

Bare_List* duplicate_bare_list (Bare_List* old_list) {
	if (old_list == NULL) {
		perror ("Bare_List does not exist to Duplicate!");
		return NULL;
	}

	Bare_List* new_list = create_bare_list (old_list -> item_count);

	if (new_list != NULL) {
		for (size_t i = 0; i < new_list -> item_count; i++) {
			*(new_list -> item_addresses + i) = *(old_list -> item_addresses + i);
		}
	}

	return new_list;
}

void forget_bare_list (Bare_List** list_address) {
	if (*list_address == NULL) {
		perror ("Bare_List does not exist to Forget!");
		return;
	}

	Bare_List* list = *list_address;

	for (size_t i = 0; i < list -> item_count; i++) {
		*(list -> item_addresses + i) = NULL;
	}
}

void delete_bare_list (Bare_List** list_address) {
	if (*list_address == NULL) {
		perror ("Bare_List does not exist to Delete!");
		return;
	}

	Bare_List* list = *list_address;
	__attribute__((unused)) Data* data;

	for (size_t i = 0; i < list -> item_count; i++) {
		data = *(list -> item_addresses + i);

		log_memory (DS_Raw, (list -> item_count) * sizeof (void*), list -> item_addresses, false);
		ERASE (list -> item_addresses, (list -> item_count) * sizeof (void*));
	}

	list = NULL;

	log_memory (DS_Bare_List, sizeof (Bare_List), *list_address, false);
	ERASE (list_address, sizeof (Bare_List));
}

void add_to_bare_list (Bare_List* list, void* data, bool data_copy_needed) {
	if (list == NULL) {
		perror ("Bare_List does not exist to add data!");
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

void display_bare_list (Bare_List* list) {
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

		display_data (data);
	}

	printf ("]\n");
}

void display_bare_list_addresses (Bare_List* list) {
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

bool remove_address_from_bare_list (Bare_List* list, void* address) {	// this does not hard delete memory data, just forgets or removes the address from list
	int index = search_in_address_bare_list (list, address);

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

size_t search_in_address_bare_list (Bare_List* list, void* address) {
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