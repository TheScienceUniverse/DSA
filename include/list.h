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
Data* get_list_data_at_index (List* list, size_t index);
size_t get_first_list_index_of_data (List* list , Data* data);
size_t get_last_list_index_of_data (List* list , Data* data);
void insert_into_list_at_index (List* list, Data* data, size_t index);
void insert_all_into_list (List* original_list, List* source_list);
void insert_all_into_list_from_index (List* list, List* from_list, size_t from_index);
List* get_sub_list (List* list, size_t start_index, size_t end_index);

#endif	// LIST_H
