#ifndef BARE_LIST_H
#define BARE_LIST_H

// ---------- x ----------

#include "data.h"

// ---------- x ----------

typedef struct BARE_LIST {
	size_t item_count;
	void** item_addresses;	// addresses of Data pointers --default casting should be to Data**
} Bare_List;

// ---------- x ----------

Bare_List* create_bare_list (size_t item_count);
Bare_List* duplicate_bare_list (Bare_List* list);
void display_bare_list (Bare_List* list);
void display_bare_list_addresses (Bare_List* list);
void forget_bare_list (Bare_List** list_address);
void delete_bare_list (Bare_List** list_address);
void add_to_bare_list (Bare_List* list, void* data, bool data_copy_needed);
size_t search_in_address_bare_list (Bare_List* list, void* address);
bool remove_address_from_bare_list (Bare_List* list, void* address);

#endif	// BARE_LIST_H