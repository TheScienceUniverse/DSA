#ifndef DATA_H
#define DATA_H

// ---------- x ----------

#include "string.h"

// ---------- x ----------

typedef enum DATA_TYPE {
	DT_Undefined
	, DT_Empty
	, DT_Binary
	, DT_Character
	, DT_Integer
	, DT_String
	, DT_Address
	, DT_Range
	, DT_Route
	, DT_Key_Value
} Data_Type;

typedef struct DATA {
	Data_Type type;
	size_t size;	// in bytes
	void* address;
} Data;

// ---------- x ----------

Data* create_data (Data_Type data_type, size_t block_size, void* address);
Data* duplicate_data (Data* data);
void display_data (Data* data);
void display_data_details (Data* data);
void display_binary_data (size_t size, BYTE* address);
void delete_data (Data** data_address);
void forget_data (Data** data_address);
// checks related
void copy_data (Data* src_data, Data* dst_data);
void swap_data (Data* data_1, Data* data_2);
Compare_Status compare_data (Data* data_1, Data* data_2);
bool is_data_memory_erased (void** data_addresses);
void** capture_data_addresses (Data* data);
// special type data related
void empty_data (Data* data);
Data* create_empty_data (void);
Data* create_range_data (int start, int end);
void display_range_data (Data* data);
Data* create_address_data (void* address);
Data* create_key_value_data (String* key, Data* value);
void delete_key_value_data (Data** key_value_data_address);
void display_key_value_data (Data* key_value_data);

#endif	// DATA_H
