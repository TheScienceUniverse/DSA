# Node

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)
- chunk.h (memory segmenting features)
- list.h (dynamic list features)

## Defined Datatypes

### Node_Type

```
typedef enum NODE_TYPE {
	N_Undefined
	, N_LinkedList
	, N_Stack
	, N_Queue
	, N_Tree
	, N_Graph
} Node_Type;
```

Defined with eunmerated list `enum NODE_TYPE` having options as follows

- `N_Undefined`: unknown or random node type
- `N_LinkedList`: unit of linked-list
- `N_Stack`: unit of stack
- `N_Queue`: unit of queue
- `N_Tree`: unit of tree
- `N_Graph`: unit of graph

### Node

```
typedef struct NODE {
	Node_Type type;
	String* name;
	List* address_list;
	Data* data;
} Node;
```

Defined with structure object `struct NODE` having properties as follows

- `type`: (possibly 8 bits) - type of node's data structure
- `name`: (String) - reference to name or id String
- `address_list`: (List) - reference to List of adjacent nodes
- `data`: (Data) - reference to stored Data

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create node

`Node* create_node (Node_Type type);`

Creates node of given type.
Returns reference to created node.

#### Prepare node address list

`void prepare_node_address_list (Node* node);`

Prepares node's address list based upon node's type.
Clears list if not empty.
Returns nothing.

#### Duplicate node

`Node* duplicate_node (Node* node);`

Duplicates node with all property values.
Returns reference to new node.

#### Delete node

`void delete_node (Node** node_address);`

Deletes given node from memory.
Returns nothing.

#### Set node name

`void set_node_name (Node* node, size_t name_length, char* name_address);`

Set node's name with creating duplicate of provided name or id.
Returns nothing.

#### Set node data

`void set_node_data (Node* node, Data* data);`

Set node's data with creating duplicate of provided data.
Returns nothing.

#### Display node

`void display_node (Node* node);`

Prints node's name or data if name is not available.
Returns nothing.

#### Display special node

`void display_special_node (Node* node);`

Prints node's name or 'anonymous' if name is not available.
Prints with star guards.
Returns nothing.

#### Display node details

`void display_node_details (Node* node);`

Prints node's all property values.
Returns nothing.

#### Delete temporary node

`void delete_temporary_node (Node** node_address);`

Forgets the given node's properties and deletes it.
Returns nothing.

#### Compare nodes

`Compare_Status compare_nodes (Node* node_1, Node* node_2);`

Compares all property values of given two nodes.
Returns comparison status.

#### Clear node address list

`void clear_node_address_list (Node* node);`

Clears given node's address list.
Returns nothing.

