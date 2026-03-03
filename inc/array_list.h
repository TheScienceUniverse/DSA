#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

// ---------- x ----------

#include "data.h"

// ---------- x ----------

typedef struct ARRAY_LIST {
	size_t item_count;
	size_t capacity;
	void* container;
} ArrayList;

// ---------- x ----------

ArrayList* create_ArrayList (const size_t item_count);
ArrayList* duplicate_ArrayList (const ArrayList* const old_array_list);
void display_ArrayList (const ArrayList* const array_list);
void display_ArrayList_details (const ArrayList* const array_list);
void delete_ArrayList (ArrayList** const array_list_address);
void add_to_ArrayList (ArrayList* const array_list, Data* data);
Data* get_item_from_ArrayList (const ArrayList* const array_list, const size_t index);
size_t calculate_ArrayList_capacity (const size_t item_count);
void extend_ArrayList (ArrayList* const array_list);
Data* get_ArrayList_Data_at_index (const ArrayList* const array_list, const size_t index);

#endif	// BARE_LIST_H