#ifndef CHUNK_H
#define CHUNK_H

// ---------- x ----------

#include "data.h"

// ---------- x ----------

typedef struct CHUNK {
	size_t id;
	size_t capacity;
	size_t data_count;
	Data* first_data_address;
	struct CHUNK* next_chunk;
	struct CHUNK* previous_chunk;
} Chunk;

// ---------- x ----------

Chunk* create_chunk (size_t chunk_id, size_t item_count);
void delete_chunk (Chunk** chunk_address);
void display_chunk_details (Chunk* chunk);
void display_chunk (Chunk* chunk);
Chunk* duplicate_chunk (Chunk* chunk);
Compare_Status compare_chunks (Chunk* chunk_1, Chunk* chunk_2);
void forget_chunk (Chunk** chunk_address);
Chunk* extend_chunk (Chunk* chunk);		// returns last empty-chunk address
Chunk* reduce_chunk (Chunk* chunk);		// returns last empty-chunk address
void insert_data_into_chunk (Chunk* chunk, Data* data);
Data* remove_data_from_chunk (Chunk* chunk);
void display_linked_chunks (Chunk* chunk);
Chunk* get_first_chunk (Chunk* chunk);
Chunk* get_last_chunk (Chunk* chunk);

#endif	// CHUNK_H
