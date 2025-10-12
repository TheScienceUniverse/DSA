#include "../inc/chunk.h"

Chunk* create_chunk (size_t chunk_id, size_t capacity) {
	Chunk* chunk = (Chunk*) malloc (sizeof (Chunk));

	if (chunk == NULL) {
		return NULL;
	}

	log_memory (DS_Chunk, sizeof (Chunk), chunk, true);

	chunk -> id = 0;
	chunk -> capacity = 0;
	chunk -> data_count = 0;
	chunk -> first_data_address = NULL;
	chunk -> next_chunk = NULL;
	chunk -> previous_chunk = NULL;

	if (capacity == 0) {
		return chunk;
	}

	chunk -> id = chunk_id;
	chunk -> capacity = capacity;
	chunk -> first_data_address = (Data*) calloc (capacity, sizeof (Data));

	if (chunk -> first_data_address == NULL) {
		perror ("Unable to allocate memory!\n");
		exit (EXIT_FAILURE);
	}

	log_memory (DS_Raw, capacity * sizeof (Data), chunk -> first_data_address, true);

	return chunk;
}

Chunk* duplicate_chunk (Chunk* old_chunk) {
	if (old_chunk == NULL) {
		perror ("Chunk does not exist to Duplicate!");
		return NULL;
	}

	Chunk* new_chunk = create_chunk (old_chunk -> id, old_chunk -> capacity);
	new_chunk -> data_count = old_chunk -> data_count;

	for (size_t i = 0; i < new_chunk -> capacity; i++) {
		copy_data (old_chunk -> first_data_address + i, new_chunk -> first_data_address + i);
	}

	return new_chunk;
}

void display_chunk (Chunk* chunk) {
	if (chunk == NULL) {
		perror ("Chunk does not exist to display!");
		return;
	}

	Data* data;

	printf ("[ ");

	for (size_t i = 0; i < chunk -> capacity; i++) {
		data = chunk -> first_data_address + i;

		if (i != 0) {
			printf (" | ");
		}

		display_data (data);
	}

	printf (" ]");
}

void display_chunk_details (Chunk* chunk) {
	if (chunk == NULL) {
		perror ("Chunk does not exist to display details!");
		return;
	}

	Data* data;

	printf ("Chunk :=> Address: (%p)", chunk);
	printf (", Id: (%lu)", chunk -> id);
	printf (", Capacity: (%lu)", chunk -> capacity);
	printf (", Data count: (%lu)", chunk -> data_count);
	printf (", Previous: (%p)", chunk -> previous_chunk);
	printf (", Next: (%p)", chunk -> next_chunk);

	for (size_t i = 0; i < chunk -> capacity; i++) {
		data = chunk -> first_data_address + i;

		if (i != 0) {
			printf (" | ");
		}

		display_data (data);
	}

	printf (" ]\n");
}

void display_linked_chunks (Chunk* chunk) {
	Chunk* c = chunk;
	bool multiple = false;

	while (c != NULL) {
		if (multiple) {
			printf ("---");
		}

		display_chunk (c);
		c = c -> next_chunk;
		multiple = true;
	}
}

void display_linked_chunks_guarded (Chunk* chunk) {
	printf ("----------\n");
	display_linked_chunks (chunk);
	printf ("----------\n");
}

void delete_chunk (Chunk** chunk_address) {
	if (*chunk_address == NULL) {
		perror ("Chunk does not exist to Delete!");
		return;
	}

	Chunk* chunk = *chunk_address;

	/* Unlink and re-link chunk in betwwen the chunk-list */
	Chunk* previous_chunk = chunk -> previous_chunk;
	Chunk* next_chunk = chunk -> next_chunk;

	if (previous_chunk != NULL) {
		previous_chunk -> next_chunk = next_chunk;
	}

	if (next_chunk != NULL) {
		next_chunk -> previous_chunk = previous_chunk;
	}

	previous_chunk = NULL;
	next_chunk = NULL;

	chunk -> previous_chunk = NULL;
	chunk -> next_chunk = NULL;

	log_memory (DS_Raw, (chunk -> capacity) * sizeof (Data), chunk -> first_data_address, false);
	ERASE (&(chunk -> first_data_address), sizeof (Data) * (chunk -> capacity));

	chunk = NULL;

	log_memory (DS_Chunk, sizeof (Chunk), *chunk_address, false);
	ERASE (chunk_address, sizeof (Chunk));
}

/*
void forget_chunk (Chunk** chunk_address) {
	if (*chunk_address == NULL) {
		perror ("Chunk does not exist to Forget!");
		return;
	}

	Chunk* chunk = *chunk_address;

	for (size_t i = 0; i < chunk -> item_count; i++) {
		*(chunk -> item_addresses + i) = NULL;
	}
}
*/

Compare_Status compare_chunks (Chunk* chunk_1, Chunk* chunk_2) {
	if (chunk_1 == chunk_2) {
		return Cmp_Identical;
	}

	if (NULL == chunk_1) {
		perror ("Chunk-1 does not exist to compare with");
		exit (EXIT_FAILURE);
	}

	if (NULL == chunk_2) {
		perror ("Chunk-2 does not exist to compare with");
		exit (EXIT_FAILURE);
	}

	if (chunk_1 -> data_count != chunk_2 -> data_count) {
		return Cmp_Different;
	}

	Compare_Status cmp_stat = Cmp_Equivalent;

	for (size_t i = 0; i < chunk_1 -> data_count; i++) {
		if (Cmp_Different == compare_data (chunk_1 -> first_data_address + i, chunk_2 -> first_data_address + i)) {
			cmp_stat = Cmp_Different;
			break;
		}
	}

	return cmp_stat;
}

Chunk* extend_chunk (Chunk* chunk) {
	Chunk* last_chunk = get_last_chunk_reference (chunk);

	Chunk* new_chunk = create_chunk (last_chunk -> id + 1, last_chunk -> capacity);
	last_chunk -> next_chunk = new_chunk;
	new_chunk -> previous_chunk = last_chunk;

	return new_chunk;
}

Chunk* reduce_chunk (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Chunk does not exist!\n");
		return NULL;
	}

	if (0 == chunk -> id && chunk == get_first_chunk_reference (chunk)) {
		return chunk;
	}

	Chunk* last_chunk = get_last_chunk_reference (chunk);
	Chunk* penultimate_chunk = last_chunk -> previous_chunk;	// [Latin] "paene" (almost), "ultima" (last)

	penultimate_chunk -> next_chunk = NULL;
	last_chunk -> previous_chunk = NULL;

	delete_chunk (&last_chunk);

	return penultimate_chunk;
}

void insert_data_into_chunk (Chunk* chunk, Data* data) {
	if (chunk == NULL) {
		perror ("Provided chunk does not exist to insert into!\n");
		return;
	}

	if (data == NULL) {
		perror ("Provided data does not exist to insert!\n");
		return;
	}

	Chunk* last_chunk = get_last_chunk_reference (chunk);

	if (last_chunk -> capacity == last_chunk -> data_count) {
		last_chunk = extend_chunk (last_chunk);
	}

	copy_data (data, last_chunk -> first_data_address + last_chunk -> data_count++);
}

Data* remove_data_from_chunk (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Provided chunk does not exist to remove from!\n");
		return NULL;
	}

	Chunk* last_chunk = get_last_chunk_reference (chunk);
	Chunk* first_chunk = get_first_chunk_reference (chunk);

	if (
		last_chunk == first_chunk
		&& last_chunk -> data_count == 0
	) {
		return NULL;
	}

	Data* data = last_chunk -> first_data_address + last_chunk -> data_count - 1;
	Data* real_data = duplicate_data (data);
	empty_data (data);

	-- (last_chunk -> data_count);

	if (
		last_chunk -> id != 0
		&& last_chunk -> data_count == 0
	) {
		last_chunk = reduce_chunk (last_chunk);
	}

	return real_data;
}

Chunk* get_first_chunk_reference (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Provided chunk does not exist!\n");
		return NULL;
	}

	Chunk *first_chunk = chunk;

	if (NULL == chunk -> previous_chunk) {
		return chunk;
	}

	while (NULL != first_chunk -> previous_chunk) {
		first_chunk = first_chunk -> previous_chunk;
	}

	return first_chunk;
}

Chunk* get_last_chunk_reference (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Provided chunk does not exist!\n");
		return NULL;
	}

	if (NULL == chunk -> next_chunk) {
		return chunk;
	}

	Chunk *last_chunk = chunk;

	while (NULL != last_chunk -> next_chunk) {
		last_chunk = last_chunk -> next_chunk;
	}

	return last_chunk;
}

void reduce_unused_chunks (Chunk* chunk) {
	Chunk* last_chunk = get_last_chunk_reference (chunk);
	Chunk* penultimate_chunk = last_chunk -> previous_chunk;

	while (
		0 != last_chunk -> id
		&& NULL != penultimate_chunk
	) {
		if (0 != last_chunk -> data_count) {
			break;
		}

		penultimate_chunk = last_chunk -> previous_chunk;
		reduce_chunk (last_chunk);
		last_chunk = penultimate_chunk;
	}
}

void clear_chunk_residue_data (Chunk* chunk) {
	if (NULL == chunk) {
		perror ("Provided chunk does not exist to clear data from index!\n");
		exit (EXIT_FAILURE);
	}

	size_t i = chunk -> data_count - 1;
	Data* data = chunk -> first_data_address + i;

	for ( ; i < chunk -> data_count; i++) {
		empty_data (data);
	}
}
