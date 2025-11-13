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

Iterator* create_Iterator (List* list, ssize_t stride);
void display_Iterator_details (Iterator* iterator);
void delete_Iterator (Iterator** iterator_address);
void update_Iterator_stride (Iterator* iterator, ssize_t stride);
void move_Iterator (Iterator* iterator);

// ---------- x ----------

#endif	// ITERATOR_H
