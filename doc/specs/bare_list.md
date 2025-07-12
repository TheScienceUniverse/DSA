# Bare_List

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)

## Defined Datatypes

```
typedef struct BARE_LIST {
	size_t item_count;
	void** item_addresses;
} Bare_List;
```

Defined with structure object `struct STACK` having properties as follows

- `item_count`: (32 bits) - total number of nodes
- `item_addresses`: (32/64 bits) - reference to first address of bare-list or array-list

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create bare list

`Bare_List* create_bare_list (size_t item_count);`

Creates consecutive dynamic memory (dynamic Array) to store references of other Data addresses in one place.
Returns reference to the created bare-list or dynamic array-list.

#### Duplicate bare list

`Bare_List* duplicate_bare_list (Bare_List* list);`

Duplicates provided bare-list having identical memory usage.
Returns newly created bare-list.

#### Forget bare list

`void forget_bare_list (Bare_List** list_address);`

Deletes the bare-list from memory using Erase and free utility ignoring the actual memory that stores the address reference array.
Prone to memory leak, handle carefully.
Returns nothing.

#### Delete bare list

`void delete_bare_list (Bare_List** list_address);`

Deletes the bare-list from memory using Erase and free utility.
Returns nothing.

#### Add to bare list

`void add_to_bare_list (Bare_List* list, void* data, bool data_copy_needed);`

Add address reference to the bare-list. Replace list with bigger one if required freeing old one.
Returns nothing.

#### Display bare list

`void display_bare_list (Bare_List* list);`

Prints stored data values of given bare-list of data address references.
Returns nothing.

#### Display bare list addresses

`void display_bare_list_addresses (Bare_List* list);`

Prints bare list stored memory addresses only.
Returns nothing.

#### Search in address bare list

`size_t search_in_address_bare_list (Bare_List* list, void* address);`

Searches given address in given bare-list.
Returns found index value.

#### Remove address from bare list

`bool remove_address_from_bare_list (Bare_List* list, void* address);`

Removes given address from bare-list.
Returns success status.

