# Basic

## Included Libraries

This includes all the following required language libraries

- stdio.h (input/output features)
- stdlib.h (memory management)
- stdint.h (guranteed memory size)
- ctype.h (character classification)
- string.h (byte stream management)
- stdarg.h (variadic functions)
- stdbool.h (boolean definitions)
- unistd.h ()
- math.h (mathematical features)

## Defined Datatypes

### BYTE

Defined with _unsigned character_ type to use all bits.
It is expected to have 8 bits (but not guranteed always).

### Compare_Status

```
typedef enum COMPARE_STATUS {
	Cmp_Identical
	, Cmp_Equivalent
	, Cmp_Different
} Compare_Status;
```

Defined with structured enumeration list having values as following

0. `Cmp_Itentical`: identical for exactly same memory address pointer
1. `Cmp_Equivalent`: for same data value but stored in different memory addresses
2. `Cmp_Different`: aperently different pointer as well as data value

## Procedures and Functions

### Basic memory utility functions

There are following basic memory related helper utility functions and procedures.

#### Clear memory in range

    `void fill_mem_zero (void* base_address, size_t num_bytes);`

To fill values with zero starting from given memory address upto next num_bytes.
It returns noting.

#### Check if memory in range are cleared

`bool check_mem_zero (void* base_address, size_t num_bytes);`

To check if starting from given memory address upto next number of bytes are all filled with zero.
It returns decision as either true or false after checking.

#### Copy Bit Stream

`void copy_byte_stream (size_t length, BYTE* src_addr, BYTE* dst_addr);`

To copy values from one memory address to another of given length.
It returns noting.

#### Display Byte Stream

`void display_byte_stream (size_t num_bytes, BYTE* base_address);`

To print byte stream as hexadecimal values on terminal screen from given memory address up to next number of bytes.
It returns nothing.

#### Get number of digits

`size_t get_number_of_digits (size_t number, size_t base)`

To calculate number of digits in a given positive integer number with given base.
Returns number of bytes.

#### Exponentiate positive number

`size_t exponentiate (size_t base, size_t power);`

To calculate exponentiation of given number and the exponent or the power.
Returns the calculated exponentiate.

## Template definition (pre-processor macros)

### Erase Macro

This is an updated version of free (stdlib.h) to avoid dangling pointer. It's requesting library to free the memory at the given pointer's address; as well as setting the value to NULL to avoid double free issue, because free will skip if the value is NULL.
Could not fill the deleted memory zero to the given pointer address of given length because it will corrupt re-usable free-list of library.

