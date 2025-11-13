#ifndef BARE_LIST_H
#define BARE_LIST_H

// ---------- x ----------

#include "data.h"

// ---------- x ----------

typedef struct BARE_LIST {
	size_t item_count;
	size_t capacity;
	void** item_addresses;	// addresses of Data pointers --default casting should be to Data**
} Bare_List;

// ---------- x ----------

Bare_List* create_Bare_List (size_t item_count);
Bare_List* duplicate_Bare_List (Bare_List* list);
void display_Bare_List (Bare_List* list);
void display_Bare_List_details (Bare_List* list);
void display_Bare_List_addresses (Bare_List* list);
void forget_Bare_List (Bare_List** list_address);
void delete_Bare_List (Bare_List** list_address);
void add_to_Bare_List (Bare_List* list, Data* data, bool data_copy_needed);
size_t search_in_address_Bare_List (Bare_List* list, void* address);
bool remove_address_from_Bare_List (Bare_List* list, void* address);
size_t calculate_Bare_List_capacity (size_t item_count);

#endif	// BARE_LIST_H