# Iterator

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)
- chunk.h (memory segmenting features)
- list.h (dynamic list features)

## Defined Datatypes

```
typedef struct ITERATOR {
	List* list;
	Chunk* chunk;
	size_t list_data_index;
	size_t chunk_data_index;
	ssize_t stride;	// number of index steps // forward (+ve), backward (-ve)
	Data* data;
} Iterator;
```

Defined with structure object `struct ITERATOR` having properties as follows

- `list`: (32/64 bits) - reference to list it's for
- `chunk`: (32/64 bits) - reference to chunk it's pointing to
- `list_data_index`: (32 bits) - index of list it's pointing to
- `chunk_data_index`: (32 bits) - index of chunk it's pointing to
- `stride`: (1 + 31 bits) - number of index steps / hops, +ve means forward, -ve means backward
- `data`: (32/64 bits) - reference to the data it is pointing to, for faster access

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create iterator

`Iterator* create_iterator (List* list, ssize_t stride);`

Creates iterator with given list and stride.
Returns reference to the iterator.

#### Delete iterator

`void delete_iterator (Iterator** iterator_address);`

Deletes the provided iterator using Erase and free utility.
Returns nothing.

#### Display iterator details

`void display_iterator_details (Iterator* iterator);`

Prints all property values of given iteratior in terminal console.
Returns nothing.

#### Update iterator stride

`void update_iterator_stride (Iterator* iterator, ssize_t stride);`

Changes stride value of given iterator.
Returns nothing.

#### Move iterator

`void move_iterator (Iterator* iterator);`

Move iterator according to stride and index and also updates it's data reference.
Returns nothing.

