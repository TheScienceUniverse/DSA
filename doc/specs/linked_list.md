# Linked_List

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)
- chunk.h (memory segmenting features)
- list.h (dynamic list features)
- node.h (node unit features)

## Defined Datatypes

```
typedef struct LINKED_LIST {
	String* name;
	size_t size;
	Node* head_node;
	Node* tail_node;
} Linked_List;
```

Defined with structure object `struct LINKED_LIST` having properties as follows

- `name`: (32/64 bits) - reference to name or id String
- `size`: (32 bits) - total number of nodes
- `head_node`: (32/64 bits) - reference to first Node
- `tail_node`: (32/64 bits) - reference to last Node

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create linked list

`Linked_List* create_linked_list (void);`

Creates dynamic linked list.
Returns reference to created linked list.

#### Delete linked list

`void delete_linked_list (Linked_List** linked_list_address);`

Deletes provided linked list from memory with Erase and free methods.
Returns nothing.

#### Display linked list

`void display_linked_list (Linked_List* linked_list);`

Prints values of all properties of given linked list.
Returns nothing.

#### Display linked list details

`void display_linked_list_details (Linked_List* linked_list);`

Prints values of all properties of given linked list.
Returns nothing.

#### Attach node at first

`void attach_node_at_first (Linked_List* linked_list, Node* node);`

Attach node at the begining of linked list.
Returns nothing.

#### Attach node at last

`void attach_node_at_last (Linked_List* linked_list, Node* node);`

Attach node at the end of linked list.
Returns nothing.

#### Detach head from linked list

`Node* detach_head_from_linked_list (Linked_List* linked_list);`

Detach first node from linked list.
Returns the detached node.

#### Detach tail from linked list

`Node* detach_tail_from_linked_list (Linked_List* linked_list);`

Detach last node from linked list.
Returns the detached node.

