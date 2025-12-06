#ifndef HASHMAP_H
#define HASHMAP_H

// ---------- x ----------

#include "list.h"
#include "linked_list.h"
#include "iterator.h"

// ---------- x ----------

typedef struct HASHMAP {
	size_t capacity;
	size_t item_count;
	size_t bucket_count;
	List* buckets;
} HashMap;

// ---------- x ----------

HashMap* create_HashMap (size_t capacity);
HashMap* duplicate_HashMap (HashMap* hashmap);
void display_HashMap (HashMap* hashmap);
void display_HashMap_details (HashMap* hashmap);
void delete_HashMap (HashMap** hashmap_address);
uint32_t hash_djb2 (String* key);
void add_to_HashMap (HashMap* hashmap, String* key, Data* value);

#endif	// HASH_MAP_H
