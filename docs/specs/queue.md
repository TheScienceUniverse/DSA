# Queue

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)
- chunk.h (memory segmenting features)
- list.h (dynamic list features)
- node.h (node unit features)

## Defined Datatypes

```
typedef struct QUEUE {
	String* name;
	size_t size;
	Node* front_node;
	Node* rear_node;
} Queue;
```

Defined with structure object `struct QUEUE` having properties as follows

- `name`: (32/64 bits) - reference to name or id String
- `size`: (32 bits) - total number of nodes
- `front_node`: (32/64 bits) - reference to first Node in line
- `rear_node`: (32/64 bits) - reference to last Node in line

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create queue

`Queue* create_queue (void);`

Creates queue or line object.
Returns reference to the queue object.

#### Delete queue

`void delete_queue (Queue** queue_address);`

Deletes the provided queue in memory with Erase and free utility.
Returns nothing.

#### Display queue

`void display_queue (Queue* queue);`

Prints queue Data in line.
Returns nothing.

#### Display queue details

`void display_queue_details (Queue* queue);`

Prints queue al properties line by line.
Returns nothing.

#### En-queue

`void enqueue (Queue* queue, Node* node);`

Attaches the node at the last of the line.
Returns nothing.

#### De-queue

`Node* dequeue (Queue* queue);`

Detaches the first node in the line.
Returns dequeued node.

#### Peek data from queue

`void peek_data_from_queue (Queue* queue);`

Prints first node's data in line.
Returns nothing.

