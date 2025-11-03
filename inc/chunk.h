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
Chunk* duplicate_chunk (Chunk* chunk);
void display_chunk (Chunk* chunk);
void display_chunk_details (Chunk* chunk);
void display_linked_chunks (Chunk* chunk);
void display_linked_chunks_guarded (Chunk* chunk);
void delete_chunk (Chunk** chunk_address);
void forget_chunk (Chunk** chunk_address);
size_t count_linked_chunks (Chunk* chunk);
void delete_linked_chunks (Chunk** chunk_address);
// checks related
Compare_Status compare_chunks (Chunk* chunk_1, Chunk* chunk_2);
// manipulation related
Chunk* extend_chunk (Chunk* chunk);	// returns last empty-chunk address
Chunk* reduce_chunk (Chunk* chunk);	// returns last empty-chunk address
// data proceccing related
void insert_data_into_chunk (Chunk* chunk, Data* data);
Data* remove_data_from_chunk (Chunk* chunk);
Chunk* get_first_chunk_reference (Chunk* chunk);
Chunk* get_last_chunk_reference (Chunk* chunk);
void reduce_unused_chunks (Chunk* chunk);
void clear_chunk_residue_data (Chunk* chunk);

#endif	// CHUNK_H
