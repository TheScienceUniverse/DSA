#include "../inc/hashmap.h"

HashMap* create_HashMap (size_t capacity) {
	if (0 == capacity) {
		return NULL;
	}

	HashMap* hashmap = malloc (sizeof (HashMap));

	if (NULL == hashmap) {
		perror ("Unable to allocate memory for hashmap!");
		return NULL;
	}

	log_memory (DS_HashMap, sizeof (HashMap), hashmap, true);

	hashmap -> capacity = capacity;
	hashmap -> buckets = create_address_List (capacity);
	hashmap -> item_count = 0;
	hashmap -> bucket_count = capacity;

	if (NULL == hashmap -> buckets) {
		perror ("Unable to create list for hashmap!");
		hashmap -> capacity = 0;
		hashmap -> bucket_count = 0;
		return hashmap;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);

	for (size_t i = 0; i < capacity - 1; i++) {
		iterator -> data -> address = create_Linked_List ();
		move_Iterator (iterator);
	}

	iterator -> data -> address = create_Linked_List ();

	delete_Iterator (&iterator);

	return hashmap;
}

void display_HashMap (HashMap* hashmap) {
	if (NULL == hashmap) {
		perror ("Hashmap does not exist to display!");
		return;
	}

	printf ("HashMap (%zu / %zu) => \n", hashmap -> item_count, hashmap -> bucket_count);

	if (NULL == hashmap -> buckets) {
		perror ("Unable to display key-value pair list!");
		return;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);
	size_t i;

	for (i = 0; i < hashmap -> capacity - 1; i++) {
		printf ("\tBucket-[%zu] -> ", i);
		display_Linked_List (iterator -> data -> address);
		move_Iterator (iterator);
		ENDL();
	}

	printf ("\tBucket-[%zu] -> ", i);
	display_Linked_List (iterator -> data -> address);
	ENDL();

	delete_Iterator (&iterator);
}

void display_HashMap_details (HashMap* hashmap) {
	if (NULL == hashmap) {
		perror ("Hashmap does not exist to display!");
		return;
	}

	printf ("HashMap => item-count: %zu, bucket-count: %zu\n", hashmap -> item_count, hashmap -> bucket_count);

	if (NULL == hashmap -> buckets) {
		perror ("Unable to display key-value pair list!");
		return;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);
	size_t i;

	for (i = 0; i < hashmap -> capacity - 1; i++) {
		printf ("\tBucket-[%zu] (%p): ", i, iterator -> data -> address);
		display_Linked_List (iterator -> data -> address);
		move_Iterator (iterator);
		ENDL();
	}

	printf ("\tBucket-[%zu] (%p): ", i, iterator -> data -> address);
	display_Linked_List (iterator -> data -> address);
	ENDL();

	delete_Iterator (&iterator);
}

void delete_HashMap (HashMap** hashmap_address) {
	HashMap* hashmap = *hashmap_address;

	if (NULL == hashmap) {
		perror ("HashMap does not exist to delete!");
		return;
	}

	if (NULL == hashmap -> buckets) {
		perror ("HashMap bucket-list does not exist to delete!");
		return;
	}

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);
	Linked_List* linked_list;

	for (size_t i = 0; i < hashmap -> capacity - 1; i++) {
		linked_list = iterator -> data -> address;
		delete_Linked_List (&linked_list);
		iterator -> data -> address = NULL;
		move_Iterator (iterator);
	}

	linked_list = iterator -> data -> address;
	delete_Linked_List (&linked_list);
	iterator -> data -> address = NULL;

	delete_Iterator (&iterator);
	delete_List (&(hashmap -> buckets));
	hashmap = NULL;

	log_memory (DS_HashMap, sizeof (HashMap), *hashmap_address, false);
	ERASE (hashmap_address, sizeof (HashMap));
}

uint32_t hash_djb2 (String* key) {
	// fast & efficient string hashing by Daniel J. Bernstein
	uint32_t hash = 5381;
	// 5381 => prime number for spreading and mixing 1's faster and better
	// 33 => magic number, 33 = 32 + 1 = (2 ^ 5) + 1
	char* c_ptr = key -> text;

	for (size_t i = 0; i < key -> length; i++) {
		// hash = hash * 33 + c;	// slow multiplication
		hash = ((hash << 5) + hash) + *c_ptr++;
	}

	return hash;
}

void add_to_HashMap (HashMap* hashmap, String* key, Data* value) {
	if (NULL == hashmap) {
		perror ("HashMap does not exist to insert key-value into!");
		return;
	}

	if (NULL == hashmap -> buckets) {
		perror ("HashMap buckets do not exist!");

		return;
	}

	hashmap -> item_count++;

	uint32_t hash = hash_djb2 (key);
//	printf ("hash = %" PRIu32 "\n", hash);	// PRIu32 macro from inttypes.h expands depending on compiler and system
	hash %= 10;
//	printf ("hash = %" PRIu32 "\n", hash);

	Iterator* iterator = create_Iterator (hashmap -> buckets, 1);

	for (size_t i = 0; i < hash; i++) {
		move_Iterator (iterator);
	}

	Linked_List* linked_list = iterator -> data -> address;

	delete_Iterator (&iterator);

	Data* data = create_key_value_Data (key, value);

	Node* node = create_Node (N_LinkedList);
	set_Node_Data (node, data);

	attach_Node_at_first (linked_list, node);

	delete_Node (&node);

	delete_key_value_Data (&data);

	linked_list = NULL;
}
