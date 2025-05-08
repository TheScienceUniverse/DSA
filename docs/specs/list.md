# List

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)
- chunk.h (memory segmenting features)

## Defined Datatypes

### List

```
typedef struct LIST {
	size_t item_count;
	size_t chunk_count;
	Chunk* head_chunk;
	Chunk* tail_chunk;
} List;
```

Defined with structure object `struct LIST` having properties as follows

- `item_count`: (32 bits) - total number of items stored
- `chunk_count`: (32 bits) - number of chunks
- `head_chunk`: (32/64 bits) - reference to first chunk
- `tail_chunk`: (32/64 bits) - reference to last chunk

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create list

`List* create_list (size_t expected_capacity);`

Create list object with provided expected item capacity.
Breaks the expected big list into small chunks evenly having some buffer.
Returns reference to created list.

#### Delete list

`void delete_list (List** list_address);`

Deletes created list from memory.
Returns nothing.

#### Duplicate list

`List* duplicate_list (List* list);`

Duplicates all properties including chunks containing all data.
Returns reference to the new list.

#### Forget list

`void forget_list (List** list_address);`

Deletes created list from memory ignoring underneath chunks.
Returns nothing.

#### Set list chunk cap count

`void set_list_chunk_cap_count (size_t expected_item_count, size_t* chunk_capacity, size_t* chunk_count);`

Given number of expected item count, calculates and sets vbalues for capacity of each chunk and total number of chunks.
Returns nothing. Sets value at passed addresses.

#### Display list details

`void display_list_details (List* list);`

Prints values of all properties of given list object.
Returns nothing.

#### Display list

`void display_list (List* list);`

Prints values of all properties of given list object.
Returns nothing.

#### Insert data into list

`void insert_data_into_list (List* list, Data* data);`

Inserts given data at the last of given list.
Returns nothing.

#### Search data in list

`List* search_data_in_list (List* list, Data* data);`

Searches given data in given list and prepares an **index-list**.
Returns the newly created index-list.

#### Delete data from list

`void delete_data_from_list (List* list, Data* data);`

Deletes last data from given list.
Returns nothing.

#### Remove data from list

`Data* remove_data_from_list (List* list);`

Deletes last data from given list.
Returns reference to the duplicated data.

#### Get list data at index

`Data* get_list_data_at_index (List* list, size_t index);`

Validates and gets data at given index from list.
Returns data at index.

#### Get first list index of data

`size_t get_first_list_index_of_data (List* list , Data* data);`

#### Get last list index of data

`size_t get_last_list_index_of_data (List* list , Data* data);`

Insert given data to list at given index.
Returns nothing.

#### Insert into list at index

`void insert_into_list_at_index (List* list, Data* data, size_t index);`

Insert given data to list at given index.
Returns nothing.

#### Insert all into list

`void insert_all_into_list (List* original_list, List* source_list);`

Insert all data from one list to another from last index.
Returns nothing.

#### Insert all into list from index

`void insert_all_into_list_from_index (List* list, List* from_list, size_t from_index);`

Insert all data from one list to another from some given index.
Returns nothing.

#### Get list subset

`List* get_sub_list (List* list, size_t start_index, size_t end_index);`

Creates subset of the given list in the given index range.
Returns subset of the list.

#### Delete from list at index

`void delete_from_list_at_index (List* list, size_t index);`

Deletes data from list at given index.
Returns nothing.

#### Remove from list at index

`Data* remove_from_list_at_index (List* list, size_t index);`

Removes data from list at given index.
Returns deleted data.

#### Clear list

`void clear_list (List* list);`

Deletes all data from all chunks from list.
Deletes all chunks except first chunk.
Returns nothing.

#### Delete first instance from list

`void delete_first_instance_from_list (List* list, Data* data);`

Deletes first instance of given data from list.
Returns nothing.

#### Delete last instance from list

`void delete_last_instance_from_list (List* list, Data* data);`

Deletes last instance of given data from list.
Returns nothing.

#### Delete all instances from list

`void delete_all_instances_from_list (List* list, Data* data);`

Deletes all instances of given data from given list.
Returns nothing.

#### Is list empty

`bool is_list_empty (List* list);`

Determined by item count of the given list.
Returns truth value.

#### Compare lists

`bool compare_lists (List* list_1, List* list_2);`

Compares values of all properties of given pair of lists.
Returns truth value.

#### Does list contain data

`bool does_list_contain_data (List* list, Data* data);`

Searches given data inside given list.
Returns truth value.

#### Defragment list

`void defragment_list (List* list);`

Deletes and optimize all list data.
Deletes unused or empty chunks.
Returns nothing.

