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

Data* create_Data (Data_Type data_type, size_t block_size, void* address);
Data* duplicate_Data (Data* data);
void display_Data (Data* data);
void display_Data_details (Data* data);
void display_binary_data (size_t size, BYTE* address);
void delete_Data (Data** data_address);
void forget_Data (Data** data_address);
// checks related
void copy_Data (Data* src_data, Data* dst_data);
void swap_Data (Data* data_1, Data* data_2);
Compare_Status compare_Data (Data* data_1, Data* data_2);
bool is_Data_memory_erased (void** data_addresses);
void** capture_Data_addresses (Data* data);
// special type data related
void empty_Data (Data* data);
Data* create_empty_Data (void);
Data* create_range_Data (int start, int end);
void display_range_Data (Data* data);
Data* create_address_Data (void* address);
Data* create_key_value_Data (String* key, Data* value);
void delete_key_value_Data (Data** key_value_data_address);
void display_key_value_Data (Data* key_value_data);

#endif	// DATA_H
