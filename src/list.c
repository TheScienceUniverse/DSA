#include "../include/list.h"

List* create_list (int item_count) {
	List* list = (List*) malloc (sizeof (List));

	if (list == NULL) {
		return NULL;
	}

	list -> item_count = 0;
	list -> item_addresses = NULL;

	if (item_count < 10) {
		while (item_count--) {
			add_to_list (list, NULL, false);
		}
	} else {
		list -> item_count = item_count;
		list -> item_addresses = (void**) malloc (list -> item_count * sizeof (void*));
	}

	return list;
}

List* duplicate_list (List* old_list) {
	if (old_list == NULL) {
		perror ("List does not exist to Duplicate!");
		return NULL;
	}

	List* new_list = create_list (old_list -> item_count);

	if (new_list != NULL) {
		for (int i = 0; i < new_list -> item_count; i++) {
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

	for (int i = 0; i < list -> item_count; i++) {
		*(list -> item_addresses + i) = NULL;
	}
}

void delete_list (List** list_address) {
	if (*list_address == NULL) {
		perror ("List does not exist to Delete!");
		return;
	}

	List* list = *list_address;
	Data* data;
	int i;

	for (i = 0; i < list -> item_count; i++) {
		data = *(list -> item_addresses + i);
		delete_data (&data);
	}

	list = NULL;
	ERASE (list_address);
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

void display_list (List* list) {
	if (list -> item_count == 0) {
		perror ("List is Empty!");
		return;
	}

	int i;
	Data* data;

	printf ("List (%d) : [", list -> item_count);

	for (i = 0; i < list -> item_count; i++) {
		data = *(list -> item_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		display_data (data);
	}

	printf ("]\n");
}

void display_list_addresses (List* list) {
	if (list == NULL) {
		//perror ("List does not exist to display!");
		return;
	}

	if (list -> item_count == 0) {
		//perror ("List is Empty to display!");
		return;
	}

	int i;
	void* address;

	printf ("List (%d) : [", list -> item_count);

	for (i = 0; i < list -> item_count; i++) {
		address = *(list -> item_addresses + i);

		if (i != 0) {
			printf (", ");
		}

		printf ("%p", address);
	}

	printf ("]");
}

bool remove_address_from_list (List* list, void* address) {	// this does not hard delete memory data, just forgets or removes the address from list
	int index = search_in_address_list (list, address);

	if (index < 1) {
		return false;
	}

	int i;
	void** ptr = list -> item_addresses + index;

	for (i = index; i < list -> item_count - 1; i++) {
		*ptr = *(ptr + 1);
		++ptr;
	}

	-- (list -> item_count);
	*ptr = NULL;

	return true;
}

int search_in_address_list (List* list, void* address) {
	if (list == NULL) {
		perror ("List does not exist to search address in");
		return -1;
	}

	if (list -> item_count == 0) {
		perror ("List is empty to search address in");
		return -1;
	}

	int i = 0;
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