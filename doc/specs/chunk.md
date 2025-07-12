# Chunk

## Included Libraries

This includes all the following required libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)

## Defined Datatypes

### Chunk

```
typedef struct CHUNK {
	size_t id;
	size_t capacity;
	size_t data_count;
	Data* first_data_address;
	struct CHUNK* next_chunk;
	struct CHUNK* previous_chunk;
} Chunk;
```

Defined with structure object `struct CHUNK` having properties as follows

- `id`: (32 bits) - (stores chunk index, zero based)
- `capacity`: (32 bits) - (maximum number of data can be occupied)
- `data_count`: (32 bits) - (number of data stored)
- `first_data_address`: (32/64 bits) - (address of first data position)
- `previous_chunk`: (32/64 bits) - (address of previous chunk)
- `next_chunk`: (32/64 bits) - (address of next chunk)

## Procedures and Functions

### Basic functions

There are following chunk utility functions and procedures.

#### Create chunk

`Chunk* create_chunk (size_t chunk_id, size_t item_count);`

Creates Chunk object with id and number of expected number of data.
It will calculate number of chunks to accommodate the number of Data objects evenly along with some buffer.

#### Delete chunk

`void delete_chunk (Chunk** chunk_address);`

Deletes the created Chunk object memory with Erase and free utility.
Also disconnects chunk from linked chunks.

#### Display chunk details

`void display_chunk_details (Chunk* chunk);`

Prints values of all properties of given chunk object.
Returns nothing.

#### Display chunk

`void display_chunk (Chunk* chunk);`

Prints values of given chunk object.
Returns nothing.

#### Duplicate chunk

`Chunk* duplicate_chunk (Chunk* chunk);`

Returns the newly created chunk's reference or `NULL` in case of failure.

#### Compare chunks

`Compare_Status compare_chunks (Chunk* chunk_1, Chunk* chunk_2);`

Returns compare status for given two chunks.

#### Forget chunk

`void forget_chunk (Chunk** chunk_address);`

Deletes the chunk ignoring the chunks all data segment.
Returns nothing.

#### Extend chunk

`Chunk* extend_chunk (Chunk* chunk);`

Creates and adds in the linked chunks at the end.
Used to optimize memory usage automatically.
Returns last empty-chunk reference.

#### Reduce chunk

`Chunk* reduce_chunk (Chunk* chunk);`

Deletes last chunk only if it has no data stored and not the first chunk (determined by id).
Used to optimize memory usage automatically.
Returns unlinked chunk reference.

#### Insert data into chunk

`void insert_data_into_chunk (Chunk* chunk, Data* data);`

Insert data at the last of last chunk.
Create chunk if last chunk gets full.
Returns nothing.

#### Remove data from chunk

`Data* remove_data_from_chunk (Chunk* chunk);`

Empty the last data of last chunk.
Reduce chunk if last chunk gets empty.
Returns a copy of the deleted data.

#### Display linked chunks

`void display_linked_chunks (Chunk* chunk);`

Prints all linked chunks one after another with special guard.
Returns nothing.

#### Display linked chunks unguarded

`void display_linked_chunks_unguarded (Chunk* chunk);`

Prints all linked chunks one after another without any special character guard.
Returns nothing.

#### Get first chunk

`Chunk* get_first_chunk (Chunk* chunk);`

Returns reference of first chunk of multiple linked chunks.

#### Get last chunk

`Chunk* get_last_chunk (Chunk* chunk);`

Returns reference of last chunk of multiple linked chunks.

#### Reduce unused chunks

`void reduce_unused_chunks (Chunk* chunk);`

Delete all unused or empty chunks one by one from last.
Returns nothing.

