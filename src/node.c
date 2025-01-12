#include "../include/node.h"

Node* create_node (Node_Type type) {
	Node* node = (Node*) malloc (sizeof (Node));

	if (node != NULL) {
		node -> type = type;
		node -> name = NULL;
		node -> data = NULL;

		switch (node -> type) {		// setting up address list
			case N_Undefined:
				node -> address_list = NULL;
				break;
			case N_LinkedList:
			case N_Stack:
			case N_Queue:
				node -> address_list = create_list (2);		// previous address, next address (default count = 2)
				break;
			case N_Tree:
				node -> address_list = create_list (1);		// parent address + (Optional / zero or more) child addresses (default count = 1)
				break;
			case N_Graph:
				node -> address_list = create_list (0);		// should store route table (data as well as address to go to other adjacent node)
				break;
			default:
				break;
		}
	}

	return node;
}

Node* duplicate_node (Node* node) {
	if (node == NULL) {
		perror ("Node does not exist to Duplicate!\n");
		return NULL;
	}

	Node* new_node = create_node (node -> type);

	if (new_node != NULL) {
		new_node -> type = node -> type;
		new_node -> name = duplicate_string (node -> name);
		new_node -> data = duplicate_data (node -> data);
		new_node -> address_list = duplicate_list (node -> address_list);
	}

	return new_node;
}

void delete_node (Node** node_address) {
	if (*node_address == NULL) {
		perror ("Node doesn't exist to delete!");
		return;
	}

	Node* node = *node_address;

	delete_string (&node -> name);
	delete_list (&node -> address_list);
	delete_data (&node -> data);

	node = NULL;
	ERASE (node_address, sizeof (Node));
}

void set_node_name (Node* node, size_t length, char* name) {
	if (node == NULL) {
		perror ("Error! => Node doesn't exist.\n");
		return;
	}

	if (node -> type == N_Graph) {
		perror ("Can't set graph node name manually!\n");
		return;
	}

	String* string = create_string (length, name);
	node -> name = string;
}

void set_node_data (Node* node, Data* data) {
	if (node == NULL) {
		perror ("Error! => Node doesn't exist to set data\n");
		return;
	}

	if (data == NULL) {
		perror ("Error! => Data doesn't exist to set to node\n");
		return;
	}

	node -> data = duplicate_data (data);
}

void display_node (Node* node) {
	if (node == NULL) {
		perror ("Node doesn't exist to display");
		return;
	}

	printf ("(");
	display_string (node -> name);
	printf (")");
}

void display_special_node (Node* node) {
	if (node == NULL) {
		perror ("Node doesn't exist to display");
		return;
	}

	printf ("**(");
	display_string (node -> name);
	printf (")**\n");
}

void display_node_details (Node* node) {
	if (node == NULL) {
		perror ("Node doesn't exist to display details");
		return;
	}

	printf ("Type : (");

	switch (node -> type) {
		case N_Undefined:
			printf ("Undefined Node");
			break;
		case N_LinkedList:
			printf ("Linked-List Node");
			break;
		case N_Stack:
			printf ("Stack Node");
			break;
		case N_Queue:
			printf ("Queue Node");
			break;
		case N_Tree:
			printf ("Tree Node");
			break;
		case N_Graph:
			printf ("Graph Node");
			break;
		default:
			break;
	}

	printf (") Address : (");
	printf ("%p", node);
	printf (") Name : (\"");
	display_string (node -> name);
	printf ("\") Data : (");
	display_data (node -> data);
	printf (") ");
	display_list_addresses (node -> address_list);
	//printf ("\n");
}

void delete_temporary_node (Node** node_address) {
	Node* node = *node_address;

	forget_data (&(node -> data));
	forget_list (&(node -> address_list));

	ERASE (node_address, sizeof (Node));
}