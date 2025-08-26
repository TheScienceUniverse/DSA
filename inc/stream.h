#ifndef STREAM_H
#define STREAM_H

#include "basic.h"

// ---------- x ----------

typedef struct STREAM {
	size_t length;
	uint8_t* base_addr;
} Stream;

// ---------- x ----------

Stream* create_stream (size_t length, BYTE* data);	// pass NULL as for text argument to create empty stream
void delete_stream (Stream** stream_address);				// frees stream object from memory
void copy_raw_byte_stream (size_t length, BYTE* src_addr, BYTE* dst_addr);
Stream* duplicate_stream (Stream* stream);
void display_stream (Stream* stream);						// prints bytes in hexadecimal
void display_stream_bits (Stream* stream);						// prints bytes in hexadecimal
void display_stream_details (Stream* stream);
bool compare_raw_byte_stream (size_t length, BYTE* base_addr_1, BYTE* base_addr_2);
Compare_Status compare_stream (Stream* stream1, Stream* stream2);

#endif	// STREAM_H