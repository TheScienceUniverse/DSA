#include "../inc/list.h"

List* create_List (size_t item_count) {
	List* list = (List*) malloc (sizeof (List));

	auto size_t chunk_capacity = 0;
	auto size_t chunk_count = 0;

	if (list == NULL) {
		return NULL;
	}

	log_memory (DS_List, sizeof (List), list, true);

	list -> item_count = 0;
	list -> chunk_count = 0;
	list -> head_chunk = NULL;
	list -> tail_chunk = NULL;

	if (item_count == 0) {
		return list;
	}

	set_List_Chunk_cap_count (item_count, &chunk_capacity, &chunk_count);

	list -> head_chunk = create_Chunk (0, chunk_capacity);	// first (0th) and default chunk
	list -> tail_chunk = list -> head_chunk;
	list -> chunk_count = 1;

	return list;
}

List* duplicate_List (List* old_list) {
	if (NULL == old_list) {
		perror ("Old List does not exist to duplicate list from!\n");
		exit (EXIT_FAILURE);
	}

	List* new_list = create_List (0);
	new_list -> head_chunk = NULL;
	new_list -> tail_chunk = NULL;

	Chunk* old_chunk = old_list -> head_chunk;
	Chunk* new_chunk = NULL;
	Chunk* tmp_chunk;

	while (old_chunk != NULL) {
		tmp_chunk = duplicate_Chunk (old_chunk);
		old_chunk = old_chunk -> next_chunk;
		tmp_chunk -> previous_chunk = new_chunk;

		if (NULL == new_list -> head_chunk) {
			new_list -> head_chunk = tmp_chunk;
		}

		if (NULL == new_chunk) {
			new_chunk = tmp_chunk;
			continue;
		}

		new_chunk -> next_chunk = tmp_chunk;
		new_chunk = new_chunk -> next_chunk;
	}

	new_list -> tail_chunk = new_chunk;
	new_list -> head_chunk -> previous_chunk = NULL;
	new_list -> tail_chunk -> next_chunk = NULL;
	new_list -> item_count = old_list -> item_count;

	return new_list;
}

void display_List (List* list) {
	if (NULL == list) {
		perror ("List does not exist to Display!");
		return;
	}

	display_linked_Chunks (list -> head_chunk);
}

void display_List_details (List* list) {
	if (NULL == list) {
		perror ("List does not exist to Display details!");
		return;
	}

	printf ("List :=> Address: (%p) Size: (%lu) Elements: ", list, list -> item_count);
	display_linked_Chunks (list -> head_chunk);
	putchar ('\n');
}

void display_List_subset (List* list, size_t start_index, size_t end_index) {
	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* chunk_data;
	bool first_item = true;

	// move to start position
	while (
		list_data_index < start_index
	) {
		++chunk_data_index;
		++list_data_index;

		if (
			NULL != chunk
			&& chunk -> capacity == chunk_data_index
		) {
			chunk = chunk -> next_chunk;
			chunk_data_index = 0;
		}
	}

	// print metadata
	printf ("List [%zu] (%zu - %zu) => ", list -> item_count, start_index, end_index);

	// start printing data
	while (list_data_index <= end_index) {
		chunk_data = chunk -> first_data_address + chunk_data_index;

		if (!first_item) {
			putchar (',');
		} else {
			first_item = false;
		}

		printf (" (%zu) ", list_data_index);
		display_Data (chunk_data);

		++chunk_data_index;
		++list_data_index;

		if (
			NULL != chunk
			&& chunk -> capacity == chunk_data_index
		) {
			chunk = chunk -> next_chunk;
			chunk_data_index = 0;
		}
	}

	ENDL();
}

void delete_List (List** list_address) {
	if (*list_address == NULL) {
		perror ("List does not exist to Delete!");
		return;
	}

	List* list = *list_address;

	if (NULL != list -> head_chunk) {
		delete_linked_Chunks (&(list -> head_chunk));
	}

	list -> item_count = 0;
	list -> chunk_count = 0;
	list -> head_chunk = NULL;
	list -> tail_chunk = NULL;

	list = NULL;

	log_memory (DS_List, sizeof (List), *list_address, false);
	ERASE (list_address, sizeof (List));
}

void forget_List (List** list_address) {
	if (NULL != list_address) {
		list_address = NULL;
	}
}

void set_List_Chunk_cap_count (size_t item_count, size_t* chunk_capacity, size_t* chunk_count) {
	if (5 >= item_count) {
		*chunk_capacity = item_count;
		*chunk_count = 1;
		return;
	}

	const size_t MIN_CHUNK_CAP = 10;	// minimum chunk capacity
	const size_t MAX_CHUNK_CAP = 1000;	// maximum chunk capacity

	size_t digit_count = get_number_of_digits (item_count, 10);
	size_t capacity = exponentiate (10, digit_count);

	if (item_count > capacity) {
		capacity *= 10;
	}

	if ((capacity - item_count) / digit_count < 50) {
		capacity /= 2;
	}

	if (MIN_CHUNK_CAP > capacity) {
		capacity = MIN_CHUNK_CAP;
	} else if (MAX_CHUNK_CAP < capacity) {
		capacity = MAX_CHUNK_CAP;
	}

	*chunk_capacity = capacity;
	*chunk_count = item_count / capacity;

	if (0 == *chunk_count) {
		*chunk_count = 1;
	}
}

bool is_List_empty (List* list) {
	if (NULL == list) {
		perror ("List does not exist to check emptiness!");
		return false;
	}

	return 0 == list -> item_count;
}

bool compare_Lists (List* list_1, List* list_2) {
	if (NULL == list_1) {
		perror ("List-1 does not exist to compare with!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == list_2) {
		perror ("List-2 does not exist to compare with!\n");
		exit (EXIT_FAILURE);
	}

	if (list_1 -> item_count != list_2 -> item_count) {
		return false;
	}

	size_t total_item_count = list_1 -> item_count;
	Chunk* chunk_1 = list_1 -> head_chunk;
	Chunk* chunk_2 = list_2 -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_1_data_index = 0;
	size_t chunk_2_data_index = 0;
	Data* data_1 = NULL;
	Data* data_2 = NULL;
	bool compare_status = true;

	for ( ; list_data_index < total_item_count; list_data_index++) {
		data_1 = chunk_1 -> first_data_address + chunk_1_data_index++;
		data_2 = chunk_2 -> first_data_address + chunk_2_data_index++;

		if (Cmp_Different == compare_Data (data_1, data_2)) {
			compare_status = false;
			break;
		}

		if (chunk_1 -> capacity == chunk_1_data_index) {
			chunk_1_data_index = 0;
			chunk_1 = chunk_1 -> next_chunk;
		}

		if (chunk_2 -> capacity == chunk_2_data_index) {
			chunk_2_data_index = 0;
			chunk_2 = chunk_2 -> next_chunk;
		}
	}

	return compare_status;
}

bool does_List_contain_Data (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to search data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search inside list\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* list_data = NULL;
	bool search_status = false;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		list_data = chunk -> first_data_address + chunk_data_index++;

		if (Cmp_Different == compare_Data (data, list_data)) {
			search_status = true;
			break;
		}

		if (chunk -> capacity == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	return search_status;
}

void insert_Data_into_List (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to insert data into!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to insert into list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	insert_Data_into_Chunk (chunk, data);
	list -> tail_chunk = get_last_Chunk_reference (chunk);
	list -> item_count++;
}

List* search_Data_in_List (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to search data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search from list!\n");
		exit (EXIT_FAILURE);
	}

	List* index_list = create_List (list -> item_count / 4);
	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* index_data = create_empty_Data ();
	Data* chunk_data;

	index_data -> type = DT_Integer;
	index_data -> size = sizeof (list_data_index);
	index_data -> address = &list_data_index;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;

		if (
			Cmp_Identical == compare_Data (data, chunk_data)
			|| Cmp_Equivalent == compare_Data (data, chunk_data)
		) {
			insert_Data_into_List (index_list, index_data);
		}

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	index_data -> size = 0;
	index_data -> address = NULL;

	delete_Data (&index_data);

	return index_list;
}

void delete_Data_from_List (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to delete from list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	Data* deleted_data = remove_Data_from_Chunk (chunk);
	delete_Data (&deleted_data);
	list -> tail_chunk = get_last_Chunk_reference (chunk);
}

Data* remove_Data_from_List (List* list) {
	if (NULL == list) {
		perror ("List does not exist to delete data from!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;
	Data* deleted_data = remove_Data_from_Chunk (chunk);
	chunk = NULL;	// data removal may "reduce" chunk

	list -> tail_chunk = get_last_Chunk_reference (list -> head_chunk);
	list -> item_count--;

	return deleted_data;
}

Data* get_List_Data_at_index (List* list, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to get data from!\n");
		exit (EXIT_FAILURE);
	}

	if (index >= list -> item_count) {
		perror ("List Index out of bound!\n");
		exit (EXIT_FAILURE);
	}

	Data* data = NULL;
	Chunk* chunk = list -> head_chunk;

	while (index >= chunk -> capacity) {
		chunk = chunk -> next_chunk;
		index -= chunk -> capacity;
	}

	data = chunk -> first_data_address + index;
	return duplicate_Data (data);
}

void put_List_Data_at_index (List* list, Data* data, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to put Data into at index!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == list) {
		perror ("Data does not exist to put into List at index!\n");
		exit (EXIT_FAILURE);
	}

	if (index >= list -> item_count) {
		perror ("List Index out of bound to put Data into List at index!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> head_chunk;

	while (index >= chunk -> capacity) {
		chunk = chunk -> next_chunk;
		index -= chunk -> capacity;
	}

	(chunk -> first_data_address + index) -> address = data -> address;
}

size_t get_first_List_index_of_Data (List* list , Data* data) {
	if (NULL == list) {
		perror ("List does not exist to get data index from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to get index from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* chunk_data = NULL;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;

		if (
			Cmp_Identical == compare_Data (data, chunk_data)
			|| Cmp_Equivalent == compare_Data (data, chunk_data)
		) {
			break;
		}

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	return list_data_index;
}

size_t get_last_List_index_of_Data (List* list , Data* data) {
	if (NULL == list) {
		perror ("List does not exist to get data index from!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
//		perror ("List is empty to get index from list!\n");
		return -1;
	}

	if (NULL == data) {
		perror ("Data does not exist to get index from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = list -> item_count - 1;
	Chunk* chunk = list -> tail_chunk;
	size_t chunk_data_index = chunk -> data_count - 1;
	Data* chunk_data = NULL;

	for ( ; list_data_index != (size_t)(-1) && list_data_index < list -> item_count; list_data_index--) {
		chunk_data = chunk -> first_data_address + chunk_data_index--;

		if (Cmp_Different != compare_Data (data, chunk_data)) {
			break;
		}

		if ((size_t)(-1) == chunk_data_index) {	// -1 = 0xffffffff
			chunk = chunk -> previous_chunk;

			if (NULL != chunk) {
				chunk_data_index = chunk -> data_count - 1;
			}
		}
	}

	return list_data_index;
}

void insert_into_List_at_index (List* list, Data* data, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to insert data at index!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to insert into list at index!\n");
		exit (EXIT_FAILURE);
	}

	if (index >= list -> item_count) {
		perror ("Index out of bound to insert data into list at index!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> tail_chunk;

	if (chunk -> capacity == chunk -> data_count) {
		chunk = extend_Chunk (chunk);
		chunk -> previous_chunk = list -> tail_chunk;
		list -> tail_chunk = chunk;
	}

	size_t list_data_index = list -> item_count;
	size_t chunk_data_index = chunk -> data_count;
	Data* left_data = NULL;
	Data* right_data = chunk -> first_data_address + chunk_data_index--;

	for ( ; list_data_index > index; list_data_index--) {
		if (
			0 == chunk_data_index
			|| chunk -> capacity < chunk_data_index
		) {
			chunk = chunk -> previous_chunk;
			chunk_data_index = chunk -> data_count - 1;
		}

		left_data = chunk -> first_data_address + chunk_data_index--;

		right_data -> type = left_data -> type;
		right_data -> size = left_data -> size;
		right_data -> address = left_data -> address;

		left_data -> address = NULL;

		right_data = left_data;	// pointer exchange
	}

	copy_Data (data, right_data);

	list -> tail_chunk -> data_count++;
	list -> item_count++;
}

void insert_all_into_List (List* list, List* from_list) {
	if (NULL == list) {
		perror ("List does not exist to insert data from new list!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == from_list) {
		perror ("Data does not exist to insert into list at index!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = from_list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* data = chunk -> first_data_address;

	for ( ; list_data_index < from_list -> item_count; list_data_index++) {
		if (chunk -> capacity == chunk_data_index) {
			chunk = chunk -> next_chunk;
			chunk_data_index = 0;
		}

		data = chunk -> first_data_address + chunk_data_index++;
		insert_Data_into_List (list, data);
	}
}

void insert_all_into_List_from_index (List* list, List* from_list, size_t from_index) {
	if (NULL == list) {
		perror ("List does not exist to insert data at index!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == from_list) {
		perror ("New list does not exist to insert from, from index!\n");
		exit (EXIT_FAILURE);
	}

	if (from_index >= list -> item_count) {
		perror ("Index out of bound to insert data into list at index!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = from_list -> head_chunk;
	Data* chunk_data = NULL;

	for ( ; list_data_index < from_list -> item_count; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;
		insert_into_List_at_index (list, chunk_data, from_index++);

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}
}

List* get_sub_List (List* list, size_t start_index, size_t end_index) {
	if (NULL == list) {
		perror ("List does not exist to create sub-list!\n");
		exit (EXIT_FAILURE);
	}

	if (start_index > list -> item_count) {
		perror ("Start index out of bound to create sub-list!\n");
		exit (EXIT_FAILURE);
	}

	if (end_index > list -> item_count) {
		perror ("End index out of bound to create sub-list!\n");
		exit (EXIT_FAILURE);
	}

	List* sub_list = create_List (list -> head_chunk -> capacity / 2);	// to reduce the chunk size
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* chunk_data = NULL;

	// move to start position
	for ( ; list_data_index < start_index; list_data_index++) {
		if (chunk -> data_count == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	// start copying data
	for ( ; list_data_index <= end_index; list_data_index++) {
		chunk_data = chunk -> first_data_address + chunk_data_index++;
		insert_Data_into_List (sub_list, chunk_data);

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	return sub_list;
}

void delete_from_List_at_index (List* list, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
		// perror ("List is empty to delete data from index!\n");
		return;
	}

	if (index > list -> item_count) {
		perror ("Index out of bound to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* left_data = NULL;
	Data* right_data = NULL;

	// move to start position
	for ( ; list_data_index < index; list_data_index++) {
		if (chunk -> capacity - 1 == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	left_data = chunk -> first_data_address + chunk_data_index;
//printf ("list-index: %ld chunk-index: %ld\n");
//printf ("Left data: ");
//display_data (left_data);
//ENDL();
	// start copying data
	for ( ; list_data_index < list -> item_count; list_data_index++) {
		if (chunk -> capacity == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}

		right_data = chunk -> first_data_address + chunk_data_index++;
		empty_Data (left_data);
		copy_Data (right_data, left_data);
		left_data = right_data;
	}

	empty_Data (right_data);

	chunk -> data_count--;
	list -> item_count--;

	if (0 == chunk -> data_count) {
		list -> tail_chunk = reduce_Chunk (chunk);
	}
}

Data* remove_from_List_at_index (List* list, size_t index) {
	if (NULL == list) {
		perror ("List does not exist to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	if (index > list -> item_count) {
		perror ("Index out of bound to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* left_data = NULL;
	Data* right_data = NULL;
	Data* index_data = NULL;

	// move to start position
	for ( ; list_data_index < index; list_data_index++) {
		if (chunk -> data_count == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

	left_data = chunk -> first_data_address + chunk_data_index;

	index_data = create_empty_Data ();	
	index_data -> type = left_data -> type;
	index_data -> size = left_data -> size;
	index_data -> address = left_data -> address;
	left_data -> address = NULL;
	empty_Data (left_data);

	// start copying data
	for ( ; list_data_index < list -> item_count; list_data_index++) {

		if (chunk -> data_count == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}

		right_data = chunk -> first_data_address + chunk_data_index++;

		left_data -> type = right_data -> type;
		left_data -> size = right_data -> size;
		left_data -> address = right_data -> address;

		left_data = right_data;
	}

	right_data -> address = NULL;
	empty_Data (right_data);

	chunk -> data_count--;
	list -> item_count--;

	if (
		0 == chunk -> data_count
		&& 0 != chunk -> id
	) {
		list -> tail_chunk = reduce_Chunk (chunk);
	}

	return index_data;
}

void clear_List (List* list) {
	if (NULL == list) {
		perror ("List does not exist to clear!\n");
		exit (EXIT_FAILURE);
	}

	clear_linked_Chunks (list -> head_chunk);
	list -> item_count = 0;
}

void delete_first_instance_from_List (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data's first instance from!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
		perror ("List is empty to delete data's first instance from!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search and delete first instance from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Chunk* chunk = list -> head_chunk;
	Data* left_data = NULL;
	Data* right_data = NULL;
	Compare_Status cmp_stat;

	// move to first instance position
	for ( ; list_data_index < list -> item_count; list_data_index++) {
		left_data = chunk -> first_data_address + chunk_data_index;
		cmp_stat = compare_Data (left_data, data);

		if (
			Cmp_Identical == cmp_stat
			|| Cmp_Equivalent == cmp_stat
		) {
			break;
		}

		if (chunk -> capacity == chunk_data_index++) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}
	}

display_Data_details (left_data);
printf ("%p\n", left_data -> address);
	log_memory (DS_Raw, left_data -> size, left_data -> address, false);
	ERASE (&(left_data -> address), left_data -> size);
	//	empty_Data (left_data);

	// start copying data
	for ( ; list_data_index < list -> item_count; list_data_index++) {

		if (chunk -> capacity == chunk_data_index) {
			chunk_data_index = 0;
			chunk = chunk -> next_chunk;
		}

		right_data = chunk -> first_data_address + chunk_data_index++;

		left_data -> address = NULL;

put_s ("before: ");
printf ("%p (%p)", left_data, left_data -> address);
printf ("\t%p (%p)\n", right_data, right_data -> address);

//		empty_Data (left_data);
//		copy_Data (right_data, left_data);


		left_data -> type = right_data -> type;
		left_data -> size = right_data -> size;
		left_data -> address = right_data -> address;

		right_data -> address = NULL;

put_s ("after: ");
printf ("%p (%p)", left_data, left_data -> address);
printf ("\t%p (%p)\n", right_data, right_data -> address);

		left_data = right_data;
	}

right_data = chunk -> first_data_address + chunk_data_index++;
printf ("%p\n", right_data -> address);
//	empty_Data (right_data);

	chunk -> data_count--;
	list -> item_count--;

	if (
		0 == chunk -> data_count
		&& 0 != chunk -> id
	) {
		list -> tail_chunk = reduce_Chunk (chunk);
	}
}

void delete_last_instance_from_List (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data's last instance from!\n");
		exit (EXIT_FAILURE);
	}

	if (0 == list -> item_count) {
		// perror ("List is empty to delete data's last instance from!\n");
		return;
	}

	if (NULL == data) {
		perror ("Data does not exist to search and delete last instance from list!\n");
		exit (EXIT_FAILURE);
	}

	size_t index = get_last_List_index_of_Data (list, data);

	if ((size_t)(-1) != index) {
		delete_from_List_at_index (list, index);
	}
}

void delete_all_instances_from_List (List* list, Data* data) {
	if (NULL == list) {
		perror ("List does not exist to delete data from index!\n");
		exit (EXIT_FAILURE);
	}

	if (NULL == data) {
		perror ("Data does not exist to search an delete from list!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> head_chunk;
	size_t list_data_index = 0;
	size_t chunk_data_index = 0;
	Data* left_data = NULL;
	Data* right_data = NULL;
	Compare_Status compare_status;
	size_t instance_count = 0;
	bool copy_flag = false;

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		copy_flag = true;

		left_data = chunk -> first_data_address + chunk_data_index;
		compare_status = compare_Data (data, left_data);

		right_data = chunk -> first_data_address + chunk_data_index++ + instance_count;

		compare_status = compare_Data (data, right_data);

		if (
			Cmp_Identical == compare_status
			|| Cmp_Equivalent == compare_status
		) {
			// empty_data (left_data);
			copy_flag = false;
			++instance_count;
			--chunk_data_index;
		}

		if (
			right_data != left_data
			&& instance_count > 0
			&& copy_flag
		) {
			copy_Data (right_data, left_data);
			empty_Data (right_data);
		}
	}

	for ( ; list_data_index < list -> item_count; list_data_index++) {
		left_data = chunk -> first_data_address + chunk_data_index++;
		empty_Data (left_data);
	}

	chunk -> data_count -= instance_count;
	list -> item_count -= instance_count;

	if (
		0 == chunk -> data_count
		&& 0 != chunk -> id
	) {
		list -> tail_chunk = reduce_Chunk (chunk);
	}
}

void defragment_List (List* list) {
	Chunk* chunk = list -> tail_chunk;
	Chunk* prev_chunk = chunk -> previous_chunk;

	while (
		NULL != chunk
		&& 0 != chunk -> id
	) {
		if (0 != chunk -> data_count) {
			continue;
		}

		prev_chunk = chunk -> previous_chunk;

		if (list -> item_count > chunk -> capacity) {
			list -> item_count -= chunk -> capacity;
		}

		delete_Chunk (&chunk);
		chunk = prev_chunk;
	}

	list -> tail_chunk = get_last_Chunk_reference (list -> head_chunk);
}

List* create_address_List (size_t capacity) {
	if (0 == capacity) {
		return NULL;
	}

	List* addr_list = create_List (capacity);
	Data* addr_data = create_address_Data (NULL);

	for (size_t i = 0; i < capacity; i++) {
		insert_Data_into_List (addr_list, addr_data);
	}

	delete_Data (&addr_data);

	return addr_list;
}