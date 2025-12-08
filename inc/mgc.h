/* # Memory-Garbage-Collector # DO NOT USE IF NOT REQUIRED # */

#ifndef MGC_H
#define MGC_H

#include "basic.h"
#include "stream.h"
#include "string.h"
#include "data.h"
#include "chunk.h"
#include "bare_list.h"
#include "list.h"
#include "iterator.h"
#include "node.h"
#include "linked_list.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "graph.h"

void manage_memory (void);
List* collect_garbage_memory (void);
void display_garbage_memory (List* list);
void delete_garbage_memory (List* list);
void display_log_entry (void* address, size_t size, DS_Type ds_type);
void delete_log_entry (void* address, size_t size, DS_Type ds_type);
void delete_data_structure (DS_Type ds_type, BYTE* address, size_t size);
void display_size_chart (void);

#endif	// MGC_H
