#ifndef LIST_H
#define LIST_H

// ---------- x ----------

#include "chunk.h"

// ---------- x ----------

typedef struct LIST {
	size_t item_count;
	size_t chunk_count;
	Chunk* head_chunk;
	Chunk* tail_chunk;
} List;

// ---------- x ----------

List* create_list (size_t expected_capacity);
void delete_list (List** list_address);
List* duplicate_list (List* list);
void forget_list (List** list_address);
void set_list_chunk_cap_count (size_t expected_item_count, size_t* chunk_capacity, size_t* chunk_count);
void display_list_details (List* list);
void display_list (List* list);
void insert_data_into_list (List* list, Data* data);
List* search_data_in_list (List* list, Data* data);
void delete_data_from_list (List* list, Data* data);

#endif	// LIST_H
