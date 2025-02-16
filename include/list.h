#ifndef LIST_H
#define LIST_H

// ---------- x ----------

#include "data.h"

// ---------- x ----------

typedef struct LIST {
	size_t item_count;
	void** item_addresses;	// addresses of Data pointers --default casting should be to Data**
} List;

// ---------- x ----------

List* create_list (size_t item_count);
List* duplicate_list (List* list);
void forget_list (List** list_address);
void delete_list (List** list_address);
void add_to_list (List* list, void* data, bool data_copy_needed);
void display_list (List* list);
void display_list_addresses (List* list);
size_t search_in_address_list (List* list, void* address);
bool remove_address_from_list (List* list, void* address);

#endif	// LIST_H