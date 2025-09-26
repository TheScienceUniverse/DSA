#ifndef ITERATOR_H
#define ITERATOR_H

// ---------- x ----------

#include "list.h"

// ---------- x ----------

typedef struct ITERATOR {
	List* list;
	Chunk* chunk;
	size_t list_data_index;
	size_t chunk_data_index;
	ssize_t stride;	// number of index steps // forward (+ve), backward (-ve)
	Data* data;
} Iterator;

// ---------- x ----------

Iterator* create_iterator (List* list, ssize_t stride);
void display_iterator_details (Iterator* iterator);
void delete_iterator (Iterator** iterator_address);
void update_iterator_stride (Iterator* iterator, ssize_t stride);
void move_iterator (Iterator* iterator);

// ---------- x ----------

#endif	// ITERATOR_H
