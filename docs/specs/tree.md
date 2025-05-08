# Tree

## Included Libraries

- basic.h (all required library features)
- string.h (String features)
- data.h (general Data features)
- chunk.h (memory segmenting features)
- list.h (dynamic list features)
- node.h (node unit features)
- stack.h (stack features)
- queue.h (queue features)

## Defined Datatypes

```
typedef struct TREE {
	Node* root_node;
	size_t node_count;
	size_t breadth;
	size_t height;
} Tree;
```

Defined with structure object `struct TREE` having properties as follows

- `root_node`: (32/64 bits) - reference to base or root Node
- `node_count`: (32 bits) - total number of nodes
- `breadth`: (32 bits) - width of the tree
- `height`: (32 bits) - height of the tree

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Create tree

`Tree* create_tree (void);`

Creates empty tree object.
Returns reference to created tree.

#### Duplicate tree

`Tree* duplicate_tree (Tree* source_tree);`

Creates a replica of tree along with all nodes.
Returns new tree.

#### Delete tree

`void delete_tree (Tree** tree_address);`

Deletes tree along with all attached nodes using Erase and free utility.
Returns nothing.

#### Display tree

`void display_tree (Tree* tree);`

Prints the tree in terminal console.
Returns nothing.

#### Set tree root node

`void set_tree_root_node (Tree* tree, Node* root_node);`

Set the node as tree's root node.
Returns nothing.

#### Get Nth child node

`Node* get_Nth_child_node (Node* parent_node, size_t child_number);`

Gets duplicate of Nth child node.
Returns reference to the fetched node.

#### Get first child node

`Node* get_first_child_node (Node* parent_node);`

Gets duplicate of first child node.
Returns reference to the fetched node.

#### Get last child node

`Node* get_last_child_node (Node* parent_node);`

Gets duplicate of last child node.
Returns reference to the fetched node.

#### Get parent node

`Node* get_parent_node (Node* child_node);`

Gets duplicate of parent child node.
Returns reference to the fetched node.

#### Append child node

`void append_child_node (Tree* tree, Node* parent_node, Node* child_node);`

Given the parent node and child node, creates a copy of child node and adds the address reference to parents children list.
Returns nothing.

#### Append sibling node

`void append_sibling_node (Tree* tree, Node* node, Node* sibling_node);`

Append node to the given node's parent.
Returns nothing.

#### Push tree node to stack

`void push_tree_node_to_stack (Stack* stack, Node* tree_node);`

Push just the reference to the given node's address to stack, not the whole node.
Returns nothing.

#### Enqueue tree node to queue

`void enqueue_tree_node_to_queue (Queue* queue, Node* node);`

Insert just the reference to the given node's adderess to queue, not the whole node.
Returns nothing.

#### Display relation with root

`void display_relation_with_root (Tree* tree, Node* node);`

Prints successive nodes towards root node one by one.
Returns nothing.

#### Display child node list

`void display_child_node_list (Node* parent_node);`

Prints list of child nodes.
Returns nothing.

#### Search tree by node name

`Node* search_tree_by_node_name (Tree* tree, String* node_name);`

Searches node in the given tree with it's name.
Returns reference to the first occurrence.

#### Display sub tree

`void display_sub_tree (Tree* tree, Node* node);`

Prints sub tree structure in terminal console.
Returns nothing.

#### Count tree nodes

`size_t count_tree_nodes (Tree* tree);`

Count tree nodes one by one.
Returns counted number of nodes.

#### Delete node from tree

`void delete_node_from_tree (Tree* tree, Node* node);`

Deletes given node from tree using Erase and free utility.
Deleted node is replaced by the middle child.
Returns nothing.

#### Create sub tree from node

`Tree* create_sub_tree_from_node (Node* node);`

Creates a replica with given tree and starting from given node.
Returns reference to the created tree.

#### Detach node from parent

`void detach_node_from_parent (Node* child_node);`

Removes given node from given parent node.
Returns reference to the removed node.

#### Print node depth whitespace

`void print_node_depth_whitespace (size_t node_depth);`

Prints number of whilespace characters (tabs) according to node's depth/height.
Returns nothing.

#### Get tree node depth

`size_t get_tree_node_depth (Tree* tree, Node* tree_node);`

Travarses to all nodes and get maximum depth (or height) of tree.
Returns calculated maximum depth or height.

#### Delete tree nodes by name

`void delete_tree_nodes_by_name (Tree* tree, String* node_name);`

Deletes all nodes having name as given.
Returns nothing.

#### Display tree node

`void display_tree_node (Node* node);`

Prints nodes in structured way.
Returns nothing.

#### Export tree data for web view

`void export_tree_data_for_web_view (Tree* tree);`

Exports tree to web scripts (HTML, CSS, JS).
Returns nothing.

#### Display path towards root

`void display_path_towards_root (Tree* tree, Node* node);`

Prints intermediate nodes starting from given node towards root node.
Returns nothing.

#### Remove child node

`Node* remove_child_node (Tree* tree, Node* parent_node);`

Given parent node, remove last child node.
Returns reference to the removed node.

#### Does tree contain node

`bool does_tree_contain_node (Tree* tree, Node* node);`

Checks the node count in the given tree.
Returns truth value.

