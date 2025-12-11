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

List* create_List (size_t expected_capacity);
List* duplicate_List (List* list);
void display_List (List* list);
void display_List_details (List* list);
void display_List_subset (List* list, size_t start_index, size_t end_index);
void delete_List (List** list_address);
void forget_List (List** list_address);
// list configuration related
void set_List_Chunk_cap_count (size_t expected_item_count, size_t* chunk_capacity, size_t* chunk_count);
// checks related
bool is_List_empty (List* list);
bool compare_Lists (List* list_1, List* list_2);
bool does_List_contain_Data (List* list, Data* data);
// data processing related
void insert_Data_into_List (List* list, Data* data);
List* search_Data_in_List (List* list, Data* data);
void delete_Data_from_List (List* list, Data* data);
Data* remove_Data_from_List (List* list);
Data* get_List_Data_at_index (List* list, size_t index);
void put_List_Data_at_index (List* list, Data* data, size_t index);
size_t get_first_List_index_of_Data (List* list , Data* data);
size_t get_last_List_index_of_Data (List* list , Data* data);
void insert_into_List_at_index (List* list, Data* data, size_t index);
void insert_all_into_List (List* original_list, List* source_list);
void insert_all_into_List_from_index (List* list, List* from_list, size_t from_index);
List* get_sub_List (List* list, size_t start_index, size_t end_index);
void delete_from_List_at_index (List* list, size_t index);
Data* remove_from_List_at_index (List* list, size_t index);
void clear_List (List* list);
void delete_first_instance_from_List (List* list, Data* data);
void delete_last_instance_from_List (List* list, Data* data);
void delete_all_instances_from_List (List* list, Data* data);
void defragment_List (List* list);
List* create_address_List (size_t capacity);

#endif	// LIST_H
