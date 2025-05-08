# String

## Included Libraries

This includes all the following required language libraries as well as basic utility functions

- basic.h (all required features)

## Defined Datatypes

### String

```
typedef struct STRING {
	size_t length;
	char* address;
} String;
```

Defined with `struct STRING` to store following properties.

- `length`: (32 bits) - length of the string
- `address`: (32/64 bits) - first data address (pointer) that have the actual data in memory

## Procedures and Functions

### Raw string (character stream) related functions

#### Display raw string

`void display_raw_string (size_t length, char* address);`

Prints raw string characters with given length.
Returns nothing.

#### Compare raw strings silently

`bool compare_raw_strings_shh (size_t length1, char* string1, size_t length2, char* string2);`

Checks if given two raw strings along with their lengths are equivalent or not.
Returns truth value.

#### Chararacter static array to dynamic array

`char* char_array_to_pointer (size_t length, char* address);`

Creates dynamic memory from static memory of given length.
Returns pointer to the dynamic (heap) memory.

#### Copy raw character stream

`void copy_raw_char_stream (size_t len, void* src_addr, void* dst_addr);`

Copies raw string from source address to destination address up to given length number of bytes.
Returns nothing.

### String object related functions

#### Create string

`String* create_string (size_t length, char* address);`

Creates String object from given length and byte stream address.
Returns String object.

#### Delete string

`void delete_string (String** string_address);`

Erases the existence if the String object from heap with Erase utility.
Returns nothing.

#### Duplicate string

`String* duplicate_string (String* string);`

Duplicates the given String object.
Return new String object.

#### Display string properties

`void display_string_properties (String* string);`

Prints description or all the properties of given String object.

#### display string

`void display_string (String* string);`

Prints just the character stream from the String object.

#### Concatenate strings

`void concatenate_strings (int input_count, ...);`

Creates new string with given number of subsequent strings provided. It's a variadic function.

#### Are strings equal

`bool are_strings_equal (String* string1, String* string2);`

Checks if provided two strings are same by value or not.
Does not check by address.

#### Append integer to raw string

`String* append_integer_to_raw_string (char* str, int number);`

Appends integer number to raw string to create object named id's.

#### match strings

`BYTE match_strings (String string1, String string2);`

Matches two given strings.

#### Is string memory erased

`bool is_string_memory_erased (void** string_addresses);`

Checks if the string memory is erased.

#### Capture string addresses

`void** capture_string_addresses (String* string);`

Duplicates and holds the string address ultil cleared.
Returns pointer to pointer to string.

#### Display N characters

`void display_N_characters (char character, size_t repetitions);`

Prints given character on terminal console N number of repeatations.

