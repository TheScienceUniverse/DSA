#include "./include/basic.h"
#include "./include/string.h"
#include "./include/data.h"
#include "./include/list.h"

int main (void) {
	int* ptr = (int*) malloc (sizeof (int));
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

	return 0;
}
