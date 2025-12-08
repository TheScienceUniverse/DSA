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
	put_into_HashMap (hashmap, key, value);
//	delete_Data (&value);
	delete_String (&key);

	key = create_String (5, "key-2");
	*((int*)(value -> address)) = -200;
//	n = -200;
//	value = create_Data (DT_Integer, sizeof (int), &n);
	put_into_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	key = create_String (5, "key-0");
	value = create_Data (DT_String, 5, "value");
	put_into_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	key = create_String (5, "key-5");
	value = create_Data (DT_Binary, 4, &x);
	put_into_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	key = create_String (6, "key-04");
	value = create_Data (DT_Binary, 4, &x);
	put_into_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	n = -500;
	key = create_String (7, "key-000");
	value = create_Data (DT_Integer, sizeof (int), &n);
	put_into_HashMap (hashmap, key, value);
	delete_Data (&value);
	delete_String (&key);

	display_HashMap (hashmap);

	size_t bucket_index, linked_list_index;
	key = create_String (5, "key-2");
	Data* kv_data = get_reference_from_HashMap (hashmap, key);
	display_key_value_Data (kv_data);
	ENDL();
	get_location_from_HashMap (hashmap, key, &bucket_index, &linked_list_index);
	printf ("bucket index = %zd, linked_list index = %zd\n", bucket_index, linked_list_index);
	delete_String (&key);

	display_HashMap (hashmap);

	key = create_String (5, "key-2");
	delete_from_HashMap (hashmap, key);
	delete_String (&key);

	key = create_String (6, "key-04");
	delete_from_HashMap (hashmap, key);
	delete_String (&key);

	key = create_String (5, "key-0");
	value = get_value_from_HashMap (hashmap, key);
	display_Data_details (value);
	delete_Data (&value);
	delete_String (&key);

	key = create_String (5, "key-0");
	delete_from_HashMap (hashmap, key);
	delete_String (&key);

	display_HashMap (hashmap);
	delete_HashMap (&hashmap);

	display_unit_test_message ("HashMap", false);
}
