#include "../inc/test.h"

void test_HashMap (void) {
	display_unit_test_message ("HashMap", true);

	HashMap* hashmap = create_HashMap (10);

	int n = 100;
	uint32_t x = 0x0A1B2C4D;
	String* key;
	Data* value;

	key = create_String (5, "key-0");
	value = create_Data (DT_Integer, sizeof (int), &n);
//	printf ("hash = %" priu32 "\n", hash_djb2 (key));
	add_to_HashMap (hashmap, key, value);
//	delete_Data (&value);
	delete_String (&key);

	key = create_String (5, "key-2");
	*((int*)(value -> address)) = -200;
//	n = -200;
//	value = create_Data (DT_Integer, sizeof (int), &n);
	add_to_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	key = create_String (5, "key-0");
	value = create_Data (DT_String, 5, "value");
	add_to_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	key = create_String (5, "key-5");
	value = create_Data (DT_Binary, 4, &x);
	add_to_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	display_HashMap (hashmap);
	delete_HashMap (&hashmap);

	display_unit_test_message ("HashMap", false);
}
