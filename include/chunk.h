#ifndef CHUNK_H
#define CHUNK_H

// ---------- x ----------

#include "data.h"

// ---------- x ----------

typedef struct CHUNK {
	size_t id;
	size_t capacity;
	size_t data_count;
	Data** data_addresses;
	struct CHUNK* next_chunk;
} Chunk;

// ---------- x ----------

Chunk* create_chunk (size_t chunk_id, size_t item_count);
void delete_chunk (Chunk** chunk_address);
void display_chunk_properties (Chunk* chunk);
void display_chunk (Chunk* chunk);
Chunk* duplicate_chunk (Chunk* chunk);
void forget_chunk (Chunk** chunk_address);
Chunk* extend_chunk (Chunk* chunk);		// returns last chunk address
Chunk* reduce_chunk (Chunk* chunk);		// returns last chunk address
void insert_data_into_chunk (Chunk* chunk, Data* data);
Data* delete_data_from_chunk (Chunk* chunk);

#endif	// CHUNK_H
