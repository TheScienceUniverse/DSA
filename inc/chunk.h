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

Chunk* create_Chunk (size_t chunk_id, size_t item_count);
Chunk* duplicate_Chunk (Chunk* chunk);
void display_Chunk (Chunk* chunk);
void display_Chunk_details (Chunk* chunk);
void display_linked_Chunks (Chunk* chunk);
void display_linked_Chunks_guarded (Chunk* chunk);
void delete_Chunk (Chunk** chunk_address);
void forget_Chunk (Chunk** chunk_address);
size_t count_linked_Chunks (Chunk* chunk);
void delete_linked_Chunks (Chunk** chunk_address);
// checks related
Compare_Status compare_Chunks (Chunk* chunk_1, Chunk* chunk_2);
// manipulation related
Chunk* extend_Chunk (Chunk* chunk);	// returns last empty-Chunk address
Chunk* reduce_Chunk (Chunk* chunk);	// returns last empty-Chunk address
// data proceccing related
void insert_Data_into_Chunk (Chunk* chunk, Data* data);
Data* remove_Data_from_Chunk (Chunk* chunk);
Chunk* get_first_Chunk_reference (Chunk* chunk);
Chunk* get_last_Chunk_reference (Chunk* chunk);
void reduce_unused_Chunks (Chunk* chunk);
void clear_Chunk_residue_Data (Chunk* chunk);

#endif	// CHUNK_H
