#ifndef STREAM_H
#define STREAM_H

#include "basic.h"

// ---------- x ----------

typedef struct STREAM {
	size_t length;
	uint8_t* base_addr;
} Stream;

// ---------- x ----------

void copy_raw_byte_stream (size_t length, BYTE* src_addr, BYTE* dst_addr);
bool compare_raw_byte_stream (size_t length, BYTE* base_addr_1, BYTE* base_addr_2);

Stream* create_Stream (size_t length, BYTE* data);	// pass NULL as for text argument to create empty stream
void delete_Stream (Stream** stream_address);				// frees stream object from memory
Stream* duplicate_Stream (Stream* stream);
void display_Stream (Stream* stream);						// prints bytes in hexadecimal
void display_Stream_bits (Stream* stream);						// prints bytes in hexadecimal
void display_Stream_details (Stream* stream);
Compare_Status compare_Stream (Stream* stream1, Stream* stream2);

#endif	// STREAM_H