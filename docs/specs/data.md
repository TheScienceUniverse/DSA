# Data

## Included Libraries

- basic.h (all required basic functionalities)
- string.h (String object functionalities)

## Defined Datatypes

### Data_Type

```
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
} Data_Type;
```

Defined with structured enumeration list `enum DATA_TYPE` having values as folloing

0. `DT_Undefined`: (for unknown data type)
1. `DT_Empty`: (for having no data created or stored; wrapper for `NULL` aka `(void*)(0)`)
2. `DT_Binary`: (for binary data stream, wrapper for `BYTE*`)
3. `DT_Character`: (for single character; wrapper for `char`)
4. `DT_Integer`: (for signed integer number; wrapper for `int`)
5. `DT_String`: (for character stream; wrapper for `char*`)
6. `DT_Address`: (for memory address storing; wrapper for `void*`)
7. `DT_Range`: (for range data)
8. `DT_Route`: (for route storing)

### Data

```
typedef struct DATA {
	Data_Type type;
	size_t size;	// in bytes
	void* address;
} Data;
```

Defined with structure object `struct DATA` having properties as follows

- `type`: (possibly 8 bits) - (stores correct type of stored data)
- `size`: (32 bits) - (stores size of the data in number of bytes)
- `address`: (32/64 bits) - (stores actual data's starting address or created dynamic heap memory address if required)

## Procedures and Functions

### Basic functions

#### Create data

`Data* create_data (Data_Type data_type, size_t block_size, void* address);`

Creates Data object with given data type, block size in bytes to copy and first source data address to copy from.
Returns created Data object; or NULL in case of failure.

#### Delete data

`void delete_data (Data** data_address);`

Delete the created Data object freeing the occupied memory with free & Erase utility.

#### Duplicate data

`Data* duplicate_data (Data* data);`

Duplicates given Data's type, size and memory address.
Returns duplicated Data object.

#### Forget data

`void forget_data (Data** data_address);`

Except the actual data memory, deletes the Data object using delete data functionalities.
Returns nothing.
***Prone to data leak, use carefully.***

#### Display data

`void display_data (Data* data);`

Prints Data object contents depending on the type of it.
Returns nothing.

#### Display data details

`void display_data_details (Data* data);`

Prints Data object all properties as well as data depending on type.
Returns nothing.

#### Display binary data

`void display_binary_data (size_t size, BYTE* address);`

Prints byte stream starting from given address up to number of bytes provided.
Returns nothing.

#### Create range data

`Data* create_range_data (int start, int end);`

Creates range data with given start and end index.
Returns created data.

#### Display range data

`void display_range_data (Data* data);`

Prints range data start and end index.
Returns nothing.

#### Are data equal

`bool are_data_equal (Data* data1, Data* data2);`

Checks and returns truth value for given two data are same or not.
Returns truth value.

#### Copy data

`void copy_data (Data* src_data, Data* dst_data);`

Copy from source Data object to destination Data object.
Returns nothing.

#### Empty data

`void empty_data (Data* data);`

Deletes actual data address depending on type and marks the type as Empty.
Returns nothing.

#### Compare data

`Compare_Status compare_data (Data* data_1, Data* data_2);`

Compares given two Data objects.
Returns if identical, equivalent or different.

#### Create empty data

`Data* create_empty_data (void);`

Creates Data object having Empty data type, no extra memory for any data and zero block size to process.
Returns the empty Data object.

#### Swap data

`void swap_data (Data* data_1, Data* data_2);`

Swaps all the properties of given two Data objects.
Returns nothing.

#### Create address data

`Data* create_address_data (void* address);`

Creates address Data object with Address data type.
The address property can store the pointing memory, there is no need for extra memory.
Returns address Data object.

