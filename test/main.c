#include "../include/basic.h"
#include "../include/string.h"
#include "../include/data.h"
#include "../include/list.h"
#include "../include/node.h"
#include "../include/linked_list.h"

int main (void) {
	int* ptr = (int*) malloc (sizeof (int));
	void* ref_ptr = ptr;

	*ptr = 10;

	assert (ptr != NULL);
	printf ("Number Test 1: Success!\n");

	assert (*((int*) ptr) == 10);
	printf ("Number Test 2: Success!\n");

	assert (ref_ptr != NULL);
	printf ("Number Test 3: Success!\n");

	assert (*((int*) ref_ptr) == 10);
	printf ("Number Test 4: Success!\n");

	ERASE (&ptr);

	assert (ptr == NULL);
	printf ("Number Test 1: Success!\n");

//	assert (*((int*) ptr) == 10);
//	printf ("Number Test 2: Success!\n");

	assert (ref_ptr != NULL);
	printf ("Number Test 3: Success!\n");

	assert (*((int*) ref_ptr) != 10);
	printf ("Number Test 4: Success!\n");

	String* string = create_string (14, "Hello, World!\n");
	assert (string != NULL);
	printf ("String Test 1: Success! -- mem alloc\n");
	delete_string (&string);
	assert (string == NULL);
	printf ("String Test 2: Success! -- mem de-alloc\n");

	int n = 10;

	Data* data = create_data (DT_Integer, sizeof (n), &n);
	
	assert (data != NULL);
	printf ("Data Test 1: Success! -- mem alloc\n");

	display_data_properties (data);

	delete_data (&data);

	assert (data == NULL);
	printf ("Data Test 2: Success! -- mem de-alloc\n");


	List* list = create_list (3);
	data = create_data (DT_Integer, sizeof (int), &n);
	display_list (list);
	add_to_list (list, data, true);
	display_list (list);
	delete_list (&list);
	display_data (data);

	Node* node = create_node (N_Undefined);
	set_node_name (node, 5, "Node1");
	display_node (node);
	delete_node (&node);

	Linked_List* linked_list = create_linked_list ();
	node = create_node (N_Undefined);
	set_node_name (node, 5, "node1");
	attach_node_at_last (linked_list, node);
	set_node_name (node, 5, "node2");
	attach_node_at_first (linked_list, node);
	display_linked_list (linked_list);
	delete_linked_list (&linked_list);
	delete_node (&node);

	return 0;
}
