#ifndef DATA_H
#define DATA_H

// ---------- x ----------

#include "string.h"

// ---------- x ----------

typedef enum DATA_TYPE {
	DT_Undefined
	, DT_Binary
	, DT_Character
	, DT_Integer
	, DT_String
	, DT_Address
	, DT_Range
	, DT_Route
} Data_Type;

typedef struct DATA {
	Data_Type type;
	size_t size;
	void* address;
} Data;

// ---------- x ----------

Data* create_data (Data_Type data_type, size_t block_size, void* address);
void delete_data (Data** data_address);
Data* duplicate_data (Data* data);
void forget_data (Data** data_address);
void display_data_properties (Data* data);
void display_data (Data* data);
void display_binary_data (size_t size, BYTE* address);
Data* create_range_data (int start, int end);
void display_range_data (Data* data);
bool are_data_equal (Data* data1, Data* data2);
void copy_data (Data* src_data, Data* dst_data);
void empty_data (Data* data);

#endif	// DATA_H
