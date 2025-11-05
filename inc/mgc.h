/* # Memory-Garbage-Collector # DO NOT USE IF NOT REQUIRED # */

#ifndef MGC_H
#define MGC_H

#include "./inc/basic.h"
#include "./inc/stream.h"
#include "./inc/string.h"
#include "./inc/data.h"
#include "./inc/chunk.h"
#include "./inc/bare_list.h"
#include "./inc/list.h"
#include "./inc/iterator.h"
#include "./inc/node.h"
#include "./inc/linked_list.h"
#include "./inc/stack.h"
#include "./inc/queue.h"
#include "./inc/tree.h"
#include "./inc/graph.h"

void manage_memory (void);
List* collect_garbage_memory (void);
void display_garbage_memory (List* list);
void delete_garbage_memory (List* list);
void display_log_entry (void* address, size_t size, DS_Type ds_type);
void delete_log_entry (void* address, size_t size, DS_Type ds_type);
void delete_data_structure (DS_Type ds_type, BYTE* address, size_t size);

#endif	// MGC_H
