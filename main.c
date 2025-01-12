#include "./include/basic.h"
/*#include "./include/string.h"
#include "./include/data.h"
#include "./include/list.h"
#include "./include/node.h"
#include "./include/linked_list.h"
*/
int main (void) {
	printf("hello\n");
/*	int* ptr = (int*) malloc (sizeof (int));
	void* ref_ptr = ptr;

	*ptr = 10;

	printf ("ptr: %p\n", ptr);
	printf ("ref_ptr: %p\n", ref_ptr);
	printf ("ref_ptr val: %d\n", *((int*) ref_ptr));

	ERASE (&ptr);

	printf ("ptr: %p\n", ptr);
	printf ("ref_ptr: %p\n", ref_ptr);
	printf ("ref_ptr val: %d\n", *((int*) ref_ptr));

	String* string = create_string (14, "Hello, World!\n");
	printf ("string: %p\n", string);
	display_string_properties (string);
	delete_string (&string);
	printf ("string: %p\n", string);

	int n = 10;
	Data* data = create_data (DT_Integer, sizeof (n), &n);
	display_data_properties (data);
	delete_data (&data);

	List* list = create_list (0);
	data = create_data (DT_Integer, sizeof (n), &n);
	add_to_list (list, data, true);
	display_list (list);
	delete_list (&list);
	delete_data (&data);

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

*/
	return 0;
}
