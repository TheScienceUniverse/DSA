#include "../inc/node.h"

Node* create_node (Node_Type type) {
	Node* node = (Node*) malloc (sizeof (Node));

	if (node != NULL) {
		log_memory (DS_Node, sizeof (Node), node, true);

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
				node -> address_list = create_list (3);		// 1 parent address, multiple (default = 2) child addresses
				break;
			case N_Graph:
				node -> address_list = create_list (0);		// should store route table (data as well as address to go to other adjacent node)
				break;
			default:
				break;
		}
	}

	if (N_Undefined != node -> type) {
		prepare_node_address_list (node);
	}

	return node;
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

void prepare_node_address_list (Node* node) {
	if (NULL == node) {
		perror ("Node does not exist to prepare address list!\n");
		exit (EXIT_FAILURE);
	}

	List* list = node -> address_list;

	if (NULL == list) {
		perror ("Node's address list does not exist to prepare!\n");
		exit (EXIT_FAILURE);
	}

	Chunk* chunk = list -> head_chunk;

	if (NULL == chunk) {
		perror ("Node's address-list's chunk does not exist to prepare!\n");
		exit (EXIT_FAILURE);
	}

	Data* default_data = create_data (DT_Address, sizeof (Node*), NULL);

	for (size_t i = 0; i < chunk -> capacity; i++) {
		copy_data (default_data, chunk -> first_data_address + i);
	}

	delete_data (&default_data);
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

Node* duplicate_node (Node* node) {
	if (node == NULL) {
		perror ("Node does not exist to Duplicate!\n");
		return NULL;
	}

	Node* new_node = create_node (node -> type);
	new_node -> name = duplicate_string (node -> name);
	new_node -> data = duplicate_data (node -> data);

	if (NULL != node -> address_list) {
		new_node -> address_list = duplicate_list (node -> address_list);
	}

	return new_node;
}

void display_node (Node* node) {
	if (node == NULL) {
		perror ("Node doesn't exist to display");
		return;
	}

	printf ("(");

	if (NULL == node -> name) {
		display_data (node -> data);
	} else {
		display_string (node -> name);
	}

	printf (")");
}

void display_special_node (Node* node) {
	if (node == NULL) {
		perror ("Node doesn't exist to display");
		return;
	}

	printf ("**(");

	if (NULL != node -> name) {
		display_string (node -> name);
	} else {
		printf ("anonymous");	
	}

	printf (")**\n");
}

void display_node_details (Node* node) {
	if (node == NULL) {
		perror ("Node doesn't exist to display details");
		return;
	}

	printf ("Node :=> Type: (");

	switch (node -> type) {
		case N_Undefined:
			printf ("Undefined");
			break;
		case N_LinkedList:
			printf ("Linked-List");
			break;
		case N_Stack:
			printf ("Stack");
			break;
		case N_Queue:
			printf ("Queue");
			break;
		case N_Tree:
			printf ("Tree");
			break;
		case N_Graph:
			printf ("Graph");
			break;
		default:
			break;
	}

	printf (") Address: (");
	printf ("%p", node);
	printf (") Name: (\"");
	
	if (NULL != node -> name) {
		display_string (node -> name);
	} else {
		printf ("anonymous");	
	}

	printf ("\") Data: (");
	display_data (node -> data);
	printf (") ");

	if (NULL != node -> address_list) {
		printf ("Address list: ");
		display_list (node -> address_list);
	}

	printf ("\n");
}

void delete_node (Node** node_address) {
	if (*node_address == NULL) {
		// perror ("Node doesn't exist to delete!");
		return;
	}

	Node* node = *node_address;

	delete_string (&node -> name);
	delete_data (&node -> data);

	if (N_Undefined != node -> type) {
		delete_list (&node -> address_list);
	}

	node = NULL;

	log_memory (DS_Node, sizeof (Node), *node_address, false);
	ERASE (node_address, sizeof (Node));
}

void delete_temporary_node (Node** node_address) {
	Node* node = *node_address;

	forget_data (&(node -> data));
	forget_list (&(node -> address_list));

	log_memory (DS_Node, sizeof (Node), node, false);
	ERASE (node_address, sizeof (Node));
}

Compare_Status compare_nodes (Node* node_1, Node* node_2) {
	if (node_1 == node_2) {
		return Cmp_Identical;
	}

	if (NULL == node_1) {
		perror ("Node-1 does not exist to compare");
		exit (EXIT_FAILURE);
	}

	if (NULL == node_2) {
		perror ("Node-2 does not exist to compare");
		exit (EXIT_FAILURE);
	}

	Compare_Status cmp_stat = Cmp_Equivalent;

	if (node_1 -> type != node_2 -> type) {
		cmp_stat = Cmp_Different;
	}

	if (Cmp_Different == compare_strings (node_1 -> name, node_2 -> name)) {
		cmp_stat = Cmp_Different;
	}

	if (Cmp_Different == compare_data (node_1 -> data, node_2 -> data)) {
		cmp_stat = Cmp_Different;
	}

	return cmp_stat;
}

void clear_node_address_list (Node* node) {
	if (NULL == node) {
		perror ("Node does not exist to prepare address list!\n");
		exit (EXIT_FAILURE);
	}

	clear_list (node -> address_list);
	defragment_list (node -> address_list);
}