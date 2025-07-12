# Stack

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)
- chunk.h (memory segmenting features)
- list.h (dynamic list features)
- node.h (node unit features)

## Defined Datatypes

```
typedef struct STACK {
	String* name;
	size_t size;
	Node* top_node;
} Stack;
```

Defined with structure object `struct STACK` having properties as follows

- `name`: (32/64 bits) - reference to name or id String
- `size`: (32 bits) - total number of nodes
- `top_node`: (32/64 bits) - reference to top Node

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create stack

`Stack* create_stack (void);`

Creates stack dynamic object.
Returns reference to created stack.

#### Delete stack

`void delete_stack (Stack** stack_address);`

Deletes the provided stack from memory using Erase and free utility.
Returns nothing.

#### Display stack

`void display_stack (Stack* stack);`

Prints formantted stack Data one upon another.
Returns nothing.

#### Display stack details

`void display_stack_details (Stack* stack);`

Prints all values of properties of given stack one upon another.
Returns nothing.

#### Push node onto stack

`void push_node_onto_stack (Stack* stack, Node* node);`

Attach node at the top of the stack.
Returns nothing.

#### Pop node from stack

`Node* pop_node_from_stack (Stack* stack);`

Detach node from the top of the stack.
Returns the popped node.

#### Peek data from stack

`void peek_data_from_stack (Stack* stack);`

Prints top node Data.
Returns nothing.

#### Push data onto stack

`void push_data_onto_stack (Stack* stack, Data* data);`

Creates node having provided Data, then attach the node at the top of the stack.
Returns nothing.

#### Pop data from stack

`Data* pop_data_from_stack (Stack* stack);`

Detach node at the top of the stack, then unlinks the Data the node is having.
Returns the detached Data.

